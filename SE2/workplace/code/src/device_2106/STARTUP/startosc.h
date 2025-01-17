#ifndef STARTOSC_H
#define STARTOSC_H
#include "TYPES.h"
#include "SCB.h"
    
/**
 * @defgroup START_OSC_CONFIG_MACROS
 * @{
 */
#define     PLL_FEED()              {pPLL->FEED = __PLL_FEED_AA__; pPLL->FEED = __PLL_FEED_55__;}
#define		__SYSTEM_CLOCK__		58982400

typedef struct _system_clock{
  U32 cclk;
  U32 fcco;
  U32 sclk;
  U8  div;
  U8  m;
  U8  p;
  U8  DUMMY;  
}SysClockInfo;

/*
 * @}
 * */
void StartOsc(void);
U32 getPeriphericalClock();
#endif
