#ifndef SPI_H
#define SPI_H
#include "TYPES.h"
typedef struct _SPI_DEVICE{
  U8    port:4;
  U32   clock:20;
  U8    mode:2;
  U8    nbrbits:5;
  const void (*irqHandler)(void);
}SPI_Device,*pSPI_Device;



#endif
