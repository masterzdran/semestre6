#ifndef SPI_PUBLIC_H
#define SPI_PUBLIC_H
#include "TYPES.h"

typedef enum _spi_errors{
	SPI_SUCESS=0,
	SPI_INVALID_PARAMETERS,
	SPI_INVALID_PORT,
	SPI_INVALID_MASTER_CLOCK_DIVIDER,
	SPI_INVALID_SLAVE_CLOCK_DIVIDER,
  SPI_DEVICE_NOT_STARTED
} SPI_ERRORS;

typedef enum _spi_mode{
  SPI_Prior_to_first_SCK_rising_edge=0,
  SPI_First_SCK_rising_edge,
  SPI_Prior_to_first_SCK_falling_edge,
  SPI_First_SCK_falling_edge
}SPI_MODE;

typedef enum _spi_role{
  SPI_SLAVE=0, 
  SPI_MASTER   
}SPI_ROLE;

typedef enum _spi_status{
  SPI_SLAVE_ABORT = 0x08,
  SPI_MODE_FAULT  = 0x10,
  SPI_READ_OVERRUN  = 0x20,
  SPI_WRITE_COLLISION = 0x40,
  SPI_TRANSFER_SUCCESS = 0x80  
}SPI_STATUS;
			
typedef enum _spi_byte_shift{
  SPI_MSB = 0,
  SPI_LSB  
}SPI_BYTE_SHIFT;

/*#pragma GCC diagnostic ignored "-Wno-packed-bitfield-compat"*/
typedef struct _SPI_DEVICE{
  const void (*irqHandler)(void);	/*função de tratamento de interrupções*/
  U32   clock;		      /*ritmo do sinal de relógio*/  
  U32   chipSelect:4;	  /*define a identificação do periférico*/
  U32   nbrbits:4;		  /*número de bits de uma palavra*/
  U32   mode:2;			    /*modo SPI (CPHA, CPOL). do tipo SPI_MODE*/
  U32   role:1;			    /*qual o papel do periferico: 1- Master; 0- Slave SPI_ROLE*/
  U32   started:1;      /*indicação se o periférico foi préviamente iniciada. Por omissão o mesmo deve estar a 0. Não se garante o comportamento caso na construção se coloque a 1.*/
  U32   byteShift:1; /*SPI_BYTE_SHIFT*/
}SPI_Device,*pSPI_Device;



#endif
