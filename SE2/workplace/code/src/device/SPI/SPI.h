#ifndef SPI_H
#define SPI_H
#include "TYPES.h"
#include "LPC21XX.h"
typedef struct _SPI{
    U32		CONTROL;
    U32		STATUS;
    U32		DATA;
    U32		CLOCK_COUNTER;
}LPC_SPI,pLPC_SPI;


#endif
