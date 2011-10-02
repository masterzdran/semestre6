#ifndef POWER_H
#define POWER_H
#include "TYPES.h"
#include "SCB.h"
#include "LPC21XX.h"

/**
 * @defgroup POWER_CONTROL_MACROS
 * @{
 * */
#define __PCON_IDL__          0x000001
#define __PCON_PD__           0x000002
#define __PCON_MASK__         0x000003
#define __POWER_MASK__        0x2003BE

/**
 * @}
 */
/**
 * @brief Definition of the valid values that should be used when iteraction with power functions
 * */
typedef enum PowerPeriphericals{
  PW_Timer0		=0x000002,
  PW_Timer1		=0x000004,
  PW_Uart0		=0x000008,
  PW_Uart1		=0x000010,
  PW_PWCLock	=0x000020,
  PW_I2C		=0x000080,
  PW_SPI		=0x000100,
  PW_RTC		=0x000200,
  PW_SSP		=0x200000
} ePWPeripherical;


void POWER_Off_Peripherical(ePWPeripherical peripherical);

void POWER_On_Peripherical(ePWPeripherical peripherical);

void POWER_Down();

void POWER_Idle();
#endif
