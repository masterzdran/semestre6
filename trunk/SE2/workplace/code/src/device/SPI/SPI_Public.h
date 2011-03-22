#ifndef SPI_PUBLIC_H
#define SPI_PUBLIC_H
#include "TYPES.h"

/**
 * @brief Definition of SPI return Errors
 * */
typedef enum _spi_errors{
	SPI_SUCESS=0,
	SPI_INVALID_PARAMETERS,
	SPI_INVALID_PORT,
	SPI_INVALID_MASTER_CLOCK_DIVIDER,
	SPI_INVALID_SLAVE_CLOCK_DIVIDER,
	SPI_INVALID_NUMBER_OF_BITS,
	SPI_DEVICE_NOT_STARTED
} SPI_ERRORS;

/**
 * @brief Definition of SPI working mode
 * */
typedef enum _spi_mode{
  SPI_PRIOR_TO_FIRST_SCK_RISING_EDGE=0,
  SPI_FIRST_SCK_RISING_EDGE,
  SPI_PRIOR_TO_FIRST_SCK_FALLING_EDGE,
  SPI_FIRST_SCK_FALLING_EDGE
}SPI_MODE;
/**
 * @brief Definition of SPI working Role
 * */
typedef enum _spi_role{
  SPI_SLAVE=0, 
  SPI_MASTER   
}SPI_ROLE;
/**
 * @brief Definition of SPI working Status
 * */
typedef enum _spi_status{
  SPI_SLAVE_ABORT = 0x08,
  SPI_MODE_FAULT  = 0x10,
  SPI_READ_OVERRUN  = 0x20,
  SPI_WRITE_COLLISION = 0x40,
  SPI_TRANSFER_SUCCESS = 0x80  
}SPI_STATUS;
/**
 * @brief Definition of SPI working Shift
 * */			
typedef enum _spi_byte_shift{
  SPI_MSB = 0,
  SPI_LSB  
}SPI_BYTE_SHIFT;

/**
 * @brief Definition of SPI Device structure
 * @param clock: value of the desired clock
 * @param chipSelect: bitmap of the desired device enable bits
 * @param nbrbits: number of bits of the transmission 8-16
 * @param mode: @see SPI_MODE
 * @param role: @see SPI_ROLE
 * @param started: should be 0 when created
 * @param byteShift: @see SPI_BYTE_SHIFT
 * */
typedef struct _SPI_DEVICE{
  const void (*irqHandler)(void);	/*função de tratamento de interrupções*/
  U32   clock;		     			/*ritmo do sinal de relógio*/  
  U32   chipSelect;	  				/*define a identificação do periférico*/
  U32   nbrbits:4;		  			/*número de bits de uma palavra*/
  U32   mode:2;			    		/*modo SPI (CPHA, CPOL). do tipo SPI_MODE*/
  U32   role:1;			    		/*qual o papel do periferico: 1- Master; 0- Slave SPI_ROLE*/
  U32   started:1;      			/*indicação se o periférico foi préviamente iniciada. Por omissão o mesmo deve estar a 0. Não se garante o comportamento caso na construção se coloque a 1.*/
  U32   byteShift:1;    			/*SPI_BYTE_SHIFT*/
}SPI_Device,*pSPI_Device;



U8 SPI_init( pSPI_Device devices, S32 nbrDevices);
U8 SPI_start_device(pSPI_Device device);
void SPI_stop_device(pSPI_Device device);
U8 SPI_transfer(pSPI_Device device, U32 size, const U8 *tx_data, U8 *rx_buffer);


#endif
