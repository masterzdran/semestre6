#include "ENC28J60.h"
#include "SPI.h"

extern SPI_Device spi;

static inline do_single_transaction(U32 size, const U8 *tx_data, U8 *rx_buffer){
    spi_transaction_begin(&spi);
    spi_transaction_transfer(&spi, size, tx_data, rx_buffer);
    spi_transaction_end(&spi);   
}

static inline do_double_transaction(U8 command, U8 commandSize, U32 dataSize, const U8 *tx_data, U8 *rx_buffer){
    spi_transaction_begin(&spi);
    spi_transaction_transfer(&spi, commandSize, command, command);
    spi_transaction_transfer(&spi, dataSize, tx_data, rx_buffer);
    spi_transaction_end(&spi);   
}

/* TABLE 4-1: SPI INSTRUCTION SET FOR THE ENC28J60 */

static U8 ENC_read_control_register(U8 address){
    U8 dummytx[__ENC_READ_BUFFER_SIZE__] = { __ENC_SPI_READ_CONTROL_REGISTER_OP_CODE__ | (address & __ENC_ADDRESS_MASK__)};
    U8 dummyrx[__ENC_READ_BUFFER_SIZE__];
    do_single_transaction(ENC_BUFFER_LEN(address),dummytx,dummyrx);
    return dummyrx[__ENC_READ_BUFFER_SIZE__ - 1];
}
static void ENC_read_buffer_memory(U8* buffer, U32 size){
  U8 command[] = { __ENC_READ_BUFFER_MEMORY__ };
  do_double_transaction(*command,__ENC_READ_BUFFER_MEMORY_SIZE__,size, buffer, buffer);
}
static void ENC_write_control_register(U8 address, U8 data){
  U8 tx_buf[] = {__ENC_SPI_WRITE_CONTROL_REGISTER_OP_CODE__ | (address&__ENC_ADDRESS_MASK__),data};
  do_single_transaction(__ENC_WRITE_CONTROL_MEMORY_SIZE__,tx_buf,tx_buf);
}
static void ENC_write_buffer_memory(U8* data, U32 size){
  U8 command[] = { __ENC_WRITE_BUFFER_MEMORY__};
  do_double_transaction(*command,__ENC_WRITE_BUFFER_MEMORY_SIZE__,size, data, data);
}
static void ENC_bit_field_set(U8 address, U8 data){
    U8 dummytx[]={__ENC_SPI_BIT_FIELD_SET_OP_CODE__| (address&__ENC_ADDRESS_MASK__),data};
    do_single_transaction(__ENC_SPI_BIT_FIELD_SET_SIZE__,dummytx,dummytx);
}
static void ENC_bit_field_clear(U8 address, U8 data){
    U8 dummytx[]={__ENC_SPI_BIT_FIELD_CLEAR_OP_CODE__| (address&__ENC_ADDRESS_MASK__),data};
    do_single_transaction(__ENC_SPI_BIT_FIELD_CLEAR_SIZE__,dummytx,dummytx);
}
static void ENC_system_reset_command(){
    U8 dummyRx[]={__ENC_SYSTEM_RESET_COMMAND__};
    do_single_transaction(__ENC_SYSTEM_RESET_COMMAND_SIZE__,dummyRx,dummyRx);
}

/*------------------------------------------------------------------------------------------*/
static void ENC_bank_select(U8 bankNbr){
    U8 aux = ENC_read_control_register(ECON1);
    aux &= ~ECON1_BSEL;
    aux |= bankNbr & ECON1_BSEL;
    ENC_write_control_register(ECON1,aux);    
}

static U8 ENC_read_reg8(U8 address, U8 bankID){
    ENC_bank_select(bankID);
    return ENC_read_control_register(address);
}

static U16 ENC_read_reg16(U8 address, U8 bankID){
    U16 data = 0;
    ENC_bank_select(bankID);
    data = ENC_read_control_register(address);
    return ((data << 8)+ENC_read_control_register(address+1));    
}

static U16 ENC_read_reg(U8 address, U8 bankID,Bool asShort){
    U16 data = 0;
    ENC_bank_select(bankID);
    data = ENC_read_control_register(address);
    return ((asShort)?((data << 8) + ENC_read_control_register(address+1)) : data);    
}

static void ENC_write_reg8(U8 address, U8 bankID, U8 data){
    ENC_bank_select(bankID);
    ENC_write_control_register(address,data);
}
static void ENC_write_reg16(U8 address, U8 bankID, U16 data){
    ENC_bank_select(bankID);
    ENC_write_control_register(address,data);
    ENC_write_control_register(address + 1, data >> 8);
}
static void ENC_write_reg(U8 address, U8 bankID,U16 data,Bool asShort){
    ENC_bank_select(bankID);
    ENC_write_control_register(address,data);
    if (asShort){
        ENC_write_control_register(address + 1, data >> 8);
    }
}

void ENC_write_physical_register(U8 address, U16 data) {
    ENC_write_reg(MIREGADR,BANK02,address,false);
    ENC_write_reg(MIWRL,BANK02,data,true);
}

U16 read_physical_register(U8 address) {
  U8 aux;
  ENC_write_reg(MIREGADR,BANK02,address,false);
  ENC_bit_field_set(MICMD,MICMD_MIIRD);
  do {
    aux = ENC_read_reg(MISTAT,BANK03,false);
  } while ((aux & MISTAT_BUSY) != 0);
  ENC_bit_field_clear(MICMD,MICMD_MIIRD);
  
  return ENC_read_reg(MIRDL,BANK02,true);
}


void ENC_init(){
    
}