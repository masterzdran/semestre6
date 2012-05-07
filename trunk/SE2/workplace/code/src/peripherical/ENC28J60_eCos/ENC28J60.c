#include "ENC28J60.h"
#include "GPIO.h"

/*static pSPI_Device spi;*/
static cyg_spi_lpc2xxx_dev_t *spi_enc28j60_dev;

/*SPI defines*/
#define SPI_DEV (cyg_spi_device *) spi_enc28j60_dev
#define PW_SSP	1<<21
#define PW_SPI	1<<8
#define __SPI_CONFIG_PORT__ 0x5500
#define __SPI_PORTS__		0xff00

 void ENC_init(cyg_spi_lpc2xxx_dev_t *pspi){
	spi_enc28j60_dev=pspi;
	cyg_uint32 aux;

	/*activate gpio for CS, Reset*/
	/*GPIO_INIT_PINSEL0((CS_PIN | RESET));*/

	/*set dir to output for CS and Reset*/
	HAL_READ_UINT32((pGPIO)->IODIR, aux);
	aux = aux | (CS_PIN | RESET);
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE+CYGARC_HAL_LPC2XXX_REG_IODIR, aux);

	/*CS OFF & RESET OFF*/
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IOSET, CS_PIN);
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IOSET, RESET);

	/*Ensure SSP is disable - PIN 21*/
	HAL_READ_UINT32(CYGARC_HAL_LPC2XXX_REG_SCB_BASE + CYGARC_HAL_LPC2XXX_REG_PCONP, aux);
	aux&=~(PW_SSP);
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_SCB_BASE + CYGARC_HAL_LPC2XXX_REG_PCONP, (aux));

	/*Turn SPI on - PIN 8*/
	HAL_READ_UINT32(CYGARC_HAL_LPC2XXX_REG_SCB_BASE + CYGARC_HAL_LPC2XXX_REG_PCONP, aux);
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_SCB_BASE + CYGARC_HAL_LPC2XXX_REG_PCONP, (aux | PW_SPI));

	/*Configure Pinsel0 pins for SPI*/
	//GPIO_INIT_PINSEL0((PINSEL0_SPI_SPP_SSEL|PINSEL0_SPI_SPP_MOSI|PINSEL0_SPI_SPP_MISO|PINSEL0_SPI_SPP_SCK));
	HAL_READ_UINT32(CYGARC_HAL_LPC2XXX_REG_PIN_BASE + CYGARC_HAL_LPC2XXX_REG_PINSEL0, aux);
	aux&=~__SPI_PORTS__;	//clear SPI config pins
	aux|=__SPI_CONFIG_PORT__;
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_PIN_BASE + CYGARC_HAL_LPC2XXX_REG_PINSEL0, aux);

//	 POWER_Off_Peripherical(PW_SSP);     		/* Ensure SSP is disable */
//	 POWER_On_Peripherical(PW_SPI);      		/* (1) */
//	 gpio_init_PINSEL0(__SPI_CONFIG_PORT__); 	/* (3) */
//	 pSPI->CONTROL &= ~__SPCR_MSTR__;      		/* Set as slave to prevent communications */
}


 U8 ENC_test(){
 		U32 size=2;
 		
 		GPIO_INIT_PINSEL0(0x0);
 		GPIO_SET_DIRECTION(1<<8|1<<9,GPIO_OUT)
 		GPIO_CLEAR(1<<8|1<<9);
 		
 		GPIO_SET(1<<8|1<<9);
 		const U8 tx_data[2] = {0x1E, 0xFF};
 		U8 rx_buffer[2] = {0x0, 0x0};
 		/*RESET ENC*/
 		HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IOCLR, RESET);
 		HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IOSET, RESET);

 		/*cyg_thread_delay(500);*/
 		/*READ CONTENT OF ECON2*/
 		cyg_spi_transaction_begin(SPI_DEV);
 	    cyg_spi_transaction_transfer(SPI_DEV, true, size, tx_data, rx_buffer, true);
 	    cyg_spi_transaction_end(SPI_DEV);
 	    return rx_buffer[1];
 }

static inline void do_single_transaction(U32 size, const U8 *tx_data, U8 *rx_buffer){
  /*SPI_start_device(spi);
	SPI_transfer(spi, size, tx_data, rx_buffer);
	SPI_stop_device(spi);*/
	cyg_spi_transaction_begin(SPI_DEV);
   cyg_spi_transaction_transfer(SPI_DEV, true, size,tx_data, rx_buffer, true);
   cyg_spi_transaction_end(SPI_DEV);
}


static inline void do_double_transaction(U8* command, U8 commandSize, U32 dataSize, const U8 *tx_data, U8 *rx_buffer){
  /*SPI_start_device(spi);
    SPI_transfer(spi, commandSize, command, command);
    SPI_transfer(spi, dataSize, tx_data, rx_buffer);
    SPI_stop_device(spi);*/

	cyg_spi_transaction_begin(SPI_DEV);
   cyg_spi_transaction_transfer(SPI_DEV, true, (U32)(commandSize), command, command, false);
   cyg_spi_transaction_transfer(SPI_DEV, true, dataSize, tx_data, rx_buffer, true);
   cyg_spi_transaction_end(SPI_DEV);
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

U16 ENC_read_reg(U8 address, U8 bankID,bool asShort){
    U16 data = 0;
    ENC_bank_select(bankID);
    data = ENC_read_control_register(address);
    return ((asShort)?((ENC_read_control_register(address+1)<<8) + data) : data);
}

void ENC_write_reg(U8 address, U8 bankID,U16 data,bool asShort){
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
