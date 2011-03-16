#ifndef POWER_H
#define POWER_H
#include "TYPES.h"
#include "SCB.h"

#define pPower    ((pLPC_POWER) 0xE01FC0C0)
/*
typedef struct _POWER{
    U8 POWER_CONTROL;
    U8 DUMMY[3];
    U32 POWER_CONTROL_PERIPHERICAL;
}LPC_POWER,*pLPC_POWER;
*/

#define __PCON_IDL__          0x000001
#define __PCON_PD__           0x000002
#define __PCON_MASK__         0x000003

#define __PCTIM0_ENABLE__     0x000002
#define __PCTIM1_ENABLE__     0x000004
#define __PCUART0_ENABLE__    0x000008
#define __PCUART1_ENABLE__    0x000010
#define __PCPWM0_ENABLE__     0x000020
#define __PCI2C_ENABLE__      0x000080
#define __PCSPI_ENABLE__      0x000100
#define __PCRTC_ENABLE__      0x000200
#define __PCSSP_ENABLE__      0x200000
#define __POWER_MASK__        0x2003BE

typedef enum PowerPeriphericals{
  PW_Timer0=__PCTIM0_ENABLE__,
  PW_Timer1=__PCTIM1_ENABLE__,
  PW_Uart0=__PCUART0_ENABLE__,
  PW_Uart1=__PCUART1_ENABLE__,
  PW_PWCLock=__PCPWM0_ENABLE__,
  PW_I2C=__PCI2C_ENABLE__,
  PW_SPI=__PCSPI_ENABLE__,
  PW_RTC=__PCRTC_ENABLE__,
  PW_SSP=__PCSSP_ENABLE__
} ePWPeripherical;




void POWER_Off_Peripherical(ePWPeripherical peripherical);
void POWER_On_Peripherical(ePWPeripherical peripherical);
void POWER_Down();
void POWER_Idle();
#endif
