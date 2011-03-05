/**
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
#include "SPI.h"
#include "POWER.H"
#include "startosc.h"
#include "LPC21XX.h"
#include "VIC.h"


static void (*spiIRQ)(void) = NULL;


/*
 * Remark on Page 158:
 * The following features and registers are available in LPC2104/01, LPC2105/01, 
 * and LPC2106/01 only: 
 * • Transfer width selectable 8 bit to 16 bit (see Table 12–137, bits 11:8). 
 *      Remark: The transfer width is fixed (8 bit) on LPC2104/05/06 and LPC2104/05/06/00 parts.
 * • SSEL pin can be used for a different function when the SPI interface is 
 * used in Master mode only (see Table 12–135). 
 * • SPI can be configured as SSP interface (see Section 13–2). * 
 * */


/**
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
void SPI_init(SPI_Device devices[], U32 nbrDevices){
  if (devices == NULL || nbrDevices == 0){
    return;     /* invalid parameters */
  }
  U32 chipSelect = 0;
    
  while (--nbrDevices){
    if (devices[nbrDevices].port && __SPI_CONFIG_PORT__){
        return; /* invalid device port configuration */
    }
    chipSelect |= devices[nbrDevices].port;
  }
  /* Config chip select port */  
  gpio_init_PINSEL0();
  gpio_set_direction(devices[nbrDevices].port,GPIO_OUT);

  /* init */
  POWER_Off_Peripherical(PW_SSP);     /* Ensure SSP is disable */
  POWER_On_Peripherical(PW_SPI);      /* (1) */
  gpio_init_PINSEL0(__SPI_CONFIG_PORT__); /* (3) */
  pSPI->CONTROL = __SPCR_MSTR__;      /* Set as Master */
}

void SPI_select_device(pSPI_Device device){
  /* 
   In Master mode, this register must be an even number greater than or equal to 8. (Page 166)
   In Slave mode, the SPI clock rate provided by the master must not exceed 1/8 
   of the peripheral clock. The content of the S0SPCCR register is not relevant.
   */
  pSPI->CLOCK_COUNTER = device->clock ; /* (2) */
  pSPI->
  
}


void SPI_init_peripherical();

void SPI_write();
void SPI_read();
