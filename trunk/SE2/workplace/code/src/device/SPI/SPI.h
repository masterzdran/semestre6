#ifndef SPI_H
#define SPI_H
#include "TYPES.h"
#include "LPC21XX.h"
#include "GPIO.h"






#define __SPCR_MASK__       0xFFC
#define __SPCR_RESERVED__   0xF003
#define __SPCR_BIT_ENABLE__ 0x04
#define __SPCR_CPHA__       0x08
#define __SPCR_CPOL__       0x10
#define __SPCR_MSTR__       0x20
#define __SPCR_LSBF__       0x40
#define __SPCR_SPIE__       0x80
#define __SPCR_BITS__	      0xF00

#define __SPCR_BIT_ENABLE_SHIFT__     2
#define __SPCR_CPHA_SHIFT__     3
#define __SPCR_CPOL_SHIFT__     4
#define __SPCR_MSTR_SHIFT__     5
#define __SPCR_LSBF_SHIFT__     6
#define __SPCR_SPIE_SHIFT__     7
#define __SPCR_BITS_SHIFT__     8

#define __SPSR_MASK__     0xF8
#define __SPSR_RESERVED__ 0x07
#define __SPSR_ABRT__     0x08
#define __SPSR_MODF__     0x10
#define __SPSR_ROVR__     0x20
#define __SPSR_WCOL__     0x40
#define __SPSR_SPIF__     0x80

#define __SPDR_DATA__     0xFF
#define __SPCCR_COUNTER__ 0xFF

#define __SPINT_INTERRUPT__ 0x01
#define __SPINT_RESERVED__  0xFE



#define __SPI_PRIOR_TO_FIRST_SCK_RISING_EDGE__    (0x0 << 3)  /* CPOL = 0, CPHA = 0 */
#define __SPI_FIRST_SCK_RISING_EDGE__             (0x1 << 3)  /* CPOL = 0, CPHA = 1 */
#define __SPI_PRIOR_TO_FIRST_SCK_FALLING_EDGE__   (0x2 << 3)  /* CPOL = 1, CPHA = 0 */
#define __SPI_FIRST_SCK_FALLING_EDGE__            (0x3 << 3)  /* CPOL = 1, CPHA = 1 */

#define __SPI_CONFIG_PORT__               	(__PINSEL0_SPI_SPP_SSEL__|__PINSEL0_SPI_SPP_MOSI__|__PINSEL0_SPI_SPP_MISO__|__PINSEL0_SPI_SPP_SCK__)
#define __SPI_PORTS__               		(1<<4 | 1 << 5 | 1 << 6 | 1 << 7)

typedef struct _SPI{
    U16		CONTROL;
    U8    DUMMY01[2];
    U8		STATUS;
    U8    DUMMY02[3];
    U16		DATA;
    U8    DUMMY03[2];
    U8		CLOCK_COUNTER;
    U8    DUMMY04[3];
}LPC_SPI,*pLPC_SPI;

typedef struct _SPI_INT{
    U8    SPINT;
    U8    DUMMY01[3];
}LPC_SPI_INT,*pLPC_SPI_INT;


#endif
