#ifndef SPI_H
#define SPI_H
#include "TYPES.h"
#include "LPC21XX.h"






#define __SPCR_MASK__     0xF8
#define __SPCR_RESERVED__ 0x07
#define __SPCR_CPHA__     0x08
#define __SPCR_CPOL__     0x10
#define __SPCR_MSTR__     0x20
#define __SPCR_LSBF__     0x40
#define __SPCR_SPIE__     0x80

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


typedef struct _SPI{
    U8		CONTROL;
    U8    DUMMY01[3];
    U8		STATUS;
    U8    DUMMY02[3];
    U8		DATA;
    U8    DUMMY03[3];
    U8		CLOCK_COUNTER;
    U8    DUMMY04[3];
}LPC_SPI,pLPC_SPI;

typedef struct _SPI_INT{
    U8    SPINT;
    U8    DUMMY01[3];
}LPC_SPI_INT,pLPC_SPI_INT;


#endif
