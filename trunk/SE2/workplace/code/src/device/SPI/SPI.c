/*
#=======================================================================
# SE1   - Sistemas Embebidos 1
#-----------------------------------------------------------------------
# Turma:	LI51N
# Semestre:	Inverno 2010/2011
# Data:		Novembro/2010
#-----------------------------------------------------------------------
# Nome: 	Nuno Cancelo
# Numero:	31401
#-----------------------------------------------------------------------
# Nome:		Nuno Sousa
# Numero:	33595
#-----------------------------------------------------------------------
# LEIC  - Licenciatura em Engenharia Informática e Computadores
# DEETC - Dep. de Eng. Electrónica e Telecomunicações e Computadores
# ISEL  - Instituto Superior de Engenharia de Lisboa
#=======================================================================
**/ 
#include "LPC21XX.h"
#include "SPI.h"
#include "SPI_Public.h"
#include "POWER.h"
#include "startosc.h"
#include "VIC.h"


static void (*spiIRQ)(void) = 0;


/*
 * Remark on Page 158:
 * The following features and registers are available in LPC2104/01, LPC2105/01, 
 * and LPC2106/01 only: 
 * • Transfer width selectable 8 bit to 16 bit (see Table 12–137, bits 11:8). 
 *      Remark: The transfer width is fixed (8 bit) on LPC2104/05/06 and LPC2104/05/06/00 parts.
 * • SSEL pin can be used for a different function when the SPI interface is 
 * used in Master mode only (see Table 12–135). 
 * • SPI can be configured as SSP interface (see Section 13–2). * 
 **/


/*
 * SPI_init();
 * According to the Manual:
 * "The SPI peripheral is configured using the following registers:
 * 1. Power: In the PCONP register (Table 3–27), set bit PCSPI.
 *    Remark: On reset, SPI is enabled (PCSPI = 1). On LPC2104/05/06/01 only, the SPI
 *    shares its pin with the SSP interface. The SSP interface is disabled on reset. 
 *    To use the SPI, the SSP interface must be disabled in the PCONP register 
 *    (Table 3–27),PCSSP = 0.
 * 2. Clock: In Master mode, the SPI clock must be scaled down (see Section 12–6.4).
 * 3. Pins: Select SPI pins in registers PINSEL0/1 (see Section 7–2). 
 *    See Table 12–135 for behavior of the SSEL pin.
 * 4. Interrupts: To enable SPI interrupts, see Section 12–6.5. 
 *    Interrupts are enabled in the VIC using the VICIntEnable register (Table 5–43).
 *    Remark: On LPC2104/05/06/01, the SPI shares an interrupt line with the SSP 
 *    interface in the VIC.
 * U8 clockDivider
 * */
 /**
  * @brief Spi devices init
  * @param devices: pointer to an array of SPI_Devices
  * @param nbrDevices: number of devices in the array
  * @return: @see SPI_ERRORS
  **/
U8 SPI_init( pSPI_Device devices, S32 nbrDevices){
  U32 chipSelect = 0;
  if (devices == 0 || nbrDevices == 0){
    return SPI_INVALID_PARAMETERS;     /* invalid parameters */
  }
  
    
  while (--nbrDevices >=0 ){
    if (devices[nbrDevices].chipSelect & __SPI_PORTS__){
        return SPI_INVALID_PORT; /* invalid device port configuration */
    }
    /* 
     In Master mode, this register must be an even number greater than or equal to 8. (Page 166)
     In Slave mode, the SPI clock rate provided by the master must not exceed 1/8 
     of the peripheral clock. The content of the S0SPCCR register is not relevant.
     */
    if (devices[nbrDevices].role == SPI_MASTER) {
      if (devices[nbrDevices].clock < 8){
        return SPI_INVALID_MASTER_CLOCK_DIVIDER; /* as master divider must be >= 8 */
      }
    }else{
      if (devices[nbrDevices].clock > 7){
        return SPI_INVALID_SLAVE_CLOCK_DIVIDER; /* as slave divider must be < 8 */
      }
    }
    /*Correct the number of bits to transfer by default. When nbrbits is 0, by default will transmit 16 bits each time*/
    if (devices[nbrDevices].nbrbits < 8 && devices[nbrDevices].nbrbits > 0 ){
      return SPI_INVALID_NUMBER_OF_BITS;
    }
    chipSelect |= devices[nbrDevices].chipSelect;
    devices[nbrDevices].started=1;
  }
  /* Config chip select port */  
  gpio_init_PINSEL0(chipSelect);
  gpio_set_direction(chipSelect,GPIO_OUT);

  /* init */
  POWER_Off_Peripherical(PW_SSP);     		/* Ensure SSP is disable */
  POWER_On_Peripherical(PW_SPI);      		/* (1) */
  gpio_init_PINSEL0(__SPI_CONFIG_PORT__); 	/* (3) */
  pSPI->CONTROL &= ~__SPCR_MSTR__;      		/* Set as slave to prevent communications */
  
  return SPI_SUCESS;
}

/*
 4.3.2 Master operation
	The following sequence describes how to process a data transfer with the SPI block when
	it is set up as the master. This process assumes that any prior data transfer has already
	completed.
	1. Set the SPI clock counter register to the desired clock rate.
	2. Set the SPI control register to the desired settings.
	3. Write the data to transmitted to the SPI data register. This write starts the SPI data
	transfer.
	4. Wait for the SPIF bit in the SPI status register to be set to 1. The SPIF bit will be set
	after the last cycle of the SPI data transfer.
	5. Read the SPI status register.
	6. Read the received data from the SPI data register (optional).
	7. Go to step 3 if more data is required to transmit.
	Note: A read or write of the SPI data register is required in order to clear the SPIF status
	bit. Therefore, if the optional read of the SPI data register does not take place, a write to
	this register is required in order to clear the SPIF status bit.
*/
/**
 * @brief Start the device
 * @param device: pointer to the device to be started
 * @return SPI_DEVICE_NOT_STARTED if the device is not started, SPI_SUCESS otherwise. @see SPI_ERRORS
 * */
U8 SPI_start_device(pSPI_Device device){
  U16 clear;
  if (device->started == 0){
    return SPI_DEVICE_NOT_STARTED;
  }
  if (device->role){
    pSPI->CLOCK_COUNTER = device->clock ; /* (2) */
  }
  pSPI->CONTROL = 0;
  /*Setting the IRQ handler in VIC*/
  /*
  if (device->irqHandler){
    pSPI->CONTROL |= __SPINT_INTERRUPT__ << __SPCR_SPIE_SHIFT__;
    VIC_ConfigIRQ(IRQ_SPI_SSP,IRQ_PRIORITY_05,spiIRQ);
  }
  */
  if(device->nbrbits >7 || device->nbrbits == 0 ){
    pSPI->CONTROL |= __SPCR_BIT_ENABLE__;
  }else{
    pSPI->CONTROL &= (~__SPCR_BIT_ENABLE__)&__SPCR_MASK__;
  }
  clear = pSPI->STATUS;
  clear = pSPI->DATA;
  /*setting device parameters*/
  pSPI->CONTROL |= (device->role << __SPCR_MSTR_SHIFT__ | device->nbrbits << __SPCR_BITS_SHIFT__ | device->mode  << __SPCR_CPHA_SHIFT__);
  
  /*enable chipselect*/
  gpio_set(device->chipSelect);
	return SPI_SUCESS;
  
}
/**
 * @brief stop the device
 * @param device: pointer to the device to be stopped
 * */
void SPI_stop_device(pSPI_Device device){
  gpio_clear(device->chipSelect);
  pSPI->CONTROL &= ~__SPCR_MSTR__;	
}

/**
 * @brief Transfer Data
 * @param device: pointer to the device to be stopped
 * @param size: number of bytes to be transmitted
 * @param tx_data: pointer to char buffer with the data to be transmitted
 * @param rx_buffer: pointer to char buffer with the data to be filled with the reception
 * @todo Verify and Test SPI Errors
 * @return SPI_SUCESS
 * */
U8 SPI_transfer(pSPI_Device device, U32 size, const U8 *tx_data, U8 *rx_buffer){
  const U8 *send = tx_data;
  U8 *receive  = rx_buffer;
  
  for(;size;++send,++receive,--size){
    pSPI->DATA = *send;
    
    /*TODO: Verify STATUS ERRORS*/
    while(!(pSPI->STATUS & SPI_TRANSFER_SUCCESS)); /* Wait for transmission is complete */
    
    
    *receive = pSPI->DATA;
  }
  return SPI_SUCESS;
}

/** @todo: Code for Slave mode*/
/*
4.3.3 Slave operation
	The following sequence describes how to process a data transfer with the SPI block when
	it is set up as slave. This process assumes that any prior data transfer has already
	completed. It is required that the system clock driving the SPI logic be at least 8X faster
	than the SPI.
	1. Set the SPI control register to the desired settings.
	2. Write the data to transmitted to the SPI data register (optional). Note that this can only
	be done when a slave SPI transfer is not in progress.
	3. Wait for the SPIF bit in the SPI status register to be set to 1. The SPIF bit will be set
	after the last sampling clock edge of the SPI data transfer.
	4. Read the SPI status register.
	5. Read the received data from the SPI data register (optional).
	6. Go to step 2 if more data is required to transmit.
	Note: A read or write of the SPI data register is required in order to clear the SPIF status
	bit. Therefore, at least one of the optional reads or writes of the SPI data register must
	take place, in order to clear the SPIF status bit. 
 * */
