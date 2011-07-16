#include "ENC28J60.h"
#include "SPI.h"



static pSPI_Device spi;
 void ENC_init(pSPI_Device pspi){
	 spi=pspi;
 }

static inline void do_single_transaction(U32 size, const U8 *tx_data, U8 *rx_buffer){
    SPI_start_device(spi);
    SPI_transfer(spi, size, tx_data, rx_buffer);
    SPI_stop_device(spi);   
}

static inline void do_double_transaction(U8* command, U8 commandSize, U32 dataSize, const U8 *tx_data, U8 *rx_buffer){
    SPI_start_device(spi);
    SPI_transfer(spi, commandSize, command, command);
    SPI_transfer(spi, dataSize, tx_data, rx_buffer);
    SPI_stop_device(spi);   
}

/* TABLE 4-1: SPI INSTRUCTION SET FOR THE ENC28J60 */

U8 ENC_read_control_register(U8 address){
    U8 dummytx[__ENC_READ_BUFFER_SIZE__] ;	
    U8 dummyrx[__ENC_WRITE_BUFFER_SIZE__];
	dummytx[0] =  __ENC_SPI_READ_CONTROL_REGISTER_OP_CODE__ | (address & __ENC_ADDRESS_MASK__);
	
    do_single_transaction(ENC_BUFFER_LEN(address),dummytx,dummyrx);
    return dummyrx[ENC_BUFFER_LEN(address) - 1];
}
void ENC_read_buffer_memory(U8* buffer, U32 size){
  U8 command[] = { __ENC_READ_BUFFER_MEMORY__ };
  do_double_transaction(command,__ENC_READ_BUFFER_MEMORY_SIZE__,size, buffer, buffer);
}
void ENC_write_control_register(U8 address, U8 data){
  U8 tx_buf[__ENC_WRITE_CONTROL_MEMORY_SIZE__];
  tx_buf[0] = __ENC_SPI_WRITE_CONTROL_REGISTER_OP_CODE__ | (address&__ENC_ADDRESS_MASK__);
  tx_buf[1] = data;
  do_single_transaction(__ENC_WRITE_CONTROL_MEMORY_SIZE__,tx_buf,tx_buf);
}
void ENC_write_buffer_memory(U8* data, U32 size){
  U8 command[] = { __ENC_WRITE_BUFFER_MEMORY__};
  do_double_transaction(command,__ENC_WRITE_BUFFER_MEMORY_SIZE__,size, data, data);
}
void ENC_bit_field_set(U8 address, U8 data){
    U8 dummytx[__ENC_SPI_BIT_FIELD_SET_SIZE__];
	dummytx[0] = __ENC_SPI_BIT_FIELD_SET_OP_CODE__| (address&__ENC_ADDRESS_MASK__);
	dummytx[1] = data;
    do_single_transaction(__ENC_SPI_BIT_FIELD_SET_SIZE__,dummytx,dummytx);
}
void ENC_bit_field_clear(U8 address, U8 data){
    U8 dummytx[__ENC_SPI_BIT_FIELD_CLEAR_SIZE__];
	dummytx[0] = __ENC_SPI_BIT_FIELD_CLEAR_OP_CODE__| (address&__ENC_ADDRESS_MASK__);
	dummytx[1] = data;
    do_single_transaction(__ENC_SPI_BIT_FIELD_CLEAR_SIZE__,dummytx,dummytx);
}
void ENC_system_reset_command(){
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
/*
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
*/

U16 ENC_read_reg(U8 address, U8 bankID,Bool asShort){
    U16 data = 0;
    ENC_bank_select(bankID);
    data = ENC_read_control_register(address);
    return ((asShort)?((data << 8) + ENC_read_control_register(address+1)) : data);    
}

/*
static void ENC_write_reg8(U8 address, U8 bankID, U8 data){
    ENC_bank_select(bankID);
    ENC_write_control_register(address,data);
}
static void ENC_write_reg16(U8 address, U8 bankID, U16 data){
    ENC_bank_select(bankID);
    ENC_write_control_register(address,data);
    ENC_write_control_register(address + 1, data >> 8);
}
*/

void ENC_write_reg(U8 address, U8 bankID,U16 data,Bool asShort){
    ENC_bank_select(bankID);
    ENC_write_control_register(address,data);
    if (asShort){
        ENC_write_control_register(address + 1, data >> 8);
    }
}

void ENC_write_physical_register(U8 address, U16 data) {
    ENC_write_reg(B2_MIREGADR,BANK02,address,false);
    ENC_write_reg(B2_MIWRL,BANK02,data,true);
}

U16 read_physical_register(U8 address) {
  U8 aux;
  ENC_write_reg(B2_MIREGADR,BANK02,address,false);
  ENC_bit_field_set(B2_MICMD,MICMD_MIIRD);
  do {
    aux = ENC_read_reg(B3_MISTAT,BANK03,false);
  } while ((aux & MISTAT_BUSY) != 0);
  ENC_bit_field_clear(B2_MICMD,MICMD_MIIRD);
  
  return ENC_read_reg(B2_MIRDL,BANK02,true);
}

/*
static inline void Ethernet_prepare(U8* packet, U16 packet_size){
	U8 control = 0x0;
	ENC_write_reg(B0_ETXSTL,BANK00,__ETHERNET_TX_START_PTR__,true);
	ENC_write_reg(B0_ETXNDL,BANK00,__ETHERNET_TX_START_PTR__+ packet_size,true);
	ENC_write_reg(B0_EWRPTL,BANK00,__ETHERNET_TX_START_PTR__,true);
	ENC_write_buffer_memory(&control,SINGLE_BYTE);
	ENC_write_buffer_memory(packet,packet_size);	
}
static inline void Ethernet_start_tx(){
	ENC_bit_field_set(ECON1,ECON1_TXRST);
	ENC_bit_field_clear(ECON1,ECON1_TXRST);
	ENC_bit_field_clear(EIR,EIR_TXERIF|EIR_TXIF);
	ENC_bit_field_set(ECON1,ECON1_TXRTS);	
}
*/
/*
U8 Ethernet_send_buffer(U8* packet, U16 packet_size){
	U8 tsv[TSV_SIZE],aux;
	U8 retry = 0;
	U8 i;
		
	Ethernet_prepare(packet,packet_size);
	
	do{
		Ethernet_start_tx();
		do{
			
            aux = ENC_READ_REG8(EIR,BANK00);
		}while((aux & EIR_TXIF) == 0);
        
		ENC_WRITE_REG16(B0_ERDPTL,BANK00,__ETHERNET_TX_START_PTR__ + packet_size + 1);
		ENC_read_buffer_memory(tsv,TSV_SIZE);
        aux =  ENC_READ_REG8(EIR,BANK00);
	}while((aux & EIR_TXERIF) && TRANSMITE_LATE_COLLITION_BUG(tsv) && (retry++ < MAX_TX_RETRIES) )	;
	return ETHERNET_OK;
}

U32 Ethernet_receive_buffer(U8* buffer, U32 buffer_size){
	U32 read_size=0;
	U8 rsv[RSV_SIZE];
	U32 packet_size = 0;
	U16 rx_next_packet = __ETHERNET_RX_START_PTR__;
	U32 nbr_packets = 0;
	
	/*Evaluate parameters. Then spent time*/
/*	nbr_packets = ENC_read_reg(B1_EPKTCNT,BANK01,false);
	
	if (nbr_packets > 0){
		ENC_write_reg(B0_ERDPTL,BANK00,rx_next_packet,true);
		ENC_read_buffer_memory((U8*)&rx_next_packet,DOUBLE_BYTE);
		ENC_read_buffer_memory(rsv,RSV_SIZE);
		packet_size = ((U16)rsv[1] << 8) + rsv[0];
		read_size = ((buffer_size<packet_size)?buffer_size:packet_size);
		ENC_read_buffer_memory(buffer,read_size);
		ENC_write_reg(B0_ERXRDPTL,BANK00,rx_next_packet,true);
		ENC_bit_field_set(ECON2,ECON2_PKTDEC);
		
	}else{
		read_size = 0;
	}
	/*return ETHERNET_OK;*/
/*	return (read_size);
}
*/


void encIsr(void){
	U32 irq_status = pVIC->IRQStatus;
	if (irq_status & __INTERRUPT_TIMER0_MASK__){

		
		enableIRQ( __INTERRUPT_TIMER0__ );
	}
}


