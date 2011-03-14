#ifndef SPI_H
#define SPI_H
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

typedef struct _SPI_DEVICE{
  const void (*irqHandler)(void);	/*função de tratamento de interrupções*/
  U8        clock;		/*ritmo do sinal de relógio*/  
  U8        chipSelect:4;	/*define a identificação do periférico*/
  U8        nbrbits:4;		/*número de bits de uma palavra*/
  SPI_MODE  mode:2;			/*modo SPI (CPHA, CPOL).*/
  SPI_ROLE  role:1;			/*qual o papel do periferico: 1- Master; 0- Slave*/
  U8        started:1;  /*indicação se o periférico foi préviamente iniciada. Por omissão o mesmo deve estar a 0. Não se garante o comportamento caso na construção se coloque a 1.*/
}SPI_Device,*pSPI_Device;



#endif
