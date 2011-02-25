/*
#=======================================================================
# SE1   - Sistemas Embebidos 1
#-----------------------------------------------------------------------
# Turma:	LI51N
# Semestre:	Inverno 2010/2011
# Data:		Novembro/2010
#-----------------------------------------------------------------------
# Nome: 	Nuno Cancelo
# Numero:	31401
#-----------------------------------------------------------------------
# Nome:		Nuno Sousa
# Numero:	33595
#-----------------------------------------------------------------------
# LEIC  - Licenciatura em Engenharia Informática e Computadores
# DEETC - Dep. de Eng. Electrónica e Telecomunicações e Computadores
# ISEL  - Instituto Superior de Engenharia de Lisboa
#=======================================================================
*/
#ifndef LPC2106_H
#define LPC2106_H
#include "TYPES.h"
/*
 ==============================================================================
 GPIO
 ==============================================================================
*/
#define       pGPIO 	      ((pLPC_GPIO)	0xE0028000)
#define     __PINSEL0__     (*((PDWord)0xE002C000))
#define     __PINSEL1__     (*((PDWord)0xE002C004))

/*
 ==============================================================================
 I2C
 ==============================================================================
*/
#define     pI2C      (((pLPC_I2C) 0xE001C000))

/*
 ==============================================================================
 RTC
 ==============================================================================
*/
#define     pRTC      			(((pLPC_RTC) 0xE0024000))

/*
 ==============================================================================
 SCB
 ==============================================================================
*/
#define    pEXT_INT       ((pLPC_EXT_INT) 0xE01FC140)
#define    pMAM           ((pLPC_MAM)     0xE01FC000)     
#define    pPLL           ((pLPC_PLL)     0xE01FC080)     
#define    pPOWER         ((pLPC_POWER)   0xE01FC0C0)
#define    pAPBDIV        ((pLPC_APB)     0xE01FC100)
#define    pSCS           ((pLPC_SCS)     0xE01FC1A0)

/*
 ==============================================================================
 SPI
 ==============================================================================
*/
#define pSPI      ((pLPC_SPI) 0xE0020000)
#define pSPIINT   ((pLPC_SPI_INT)     0xE002001C)

/*
 ==============================================================================
 TIMER
 ==============================================================================
*/
#define pTIMER0 ((pLPC_TIMER) 0xE0004000)
#define pTIMER1 ((pLPC_TIMER) 0xE0008000)

/*
 ==============================================================================
 UART
 ==============================================================================
*/
#define pUART0              ((pLPC_UART) 0xE0000000)
#define pUART1              ((pLPC_UART) 0xE0010000)

/*
 ==============================================================================
 VIC
 ==============================================================================
*/
#define         pVIC                 ((pLPC_VIC)           0xFFFFF000)
#define         pVIC_VECTDEFADDR     ((pLPC_VIC_DEFVECTADDR)  0xFFFFF030)
#define         pVIC_VECTADDR        ((pLPC_VIC_VECTADDR) 0xFFFFF100)
#define         pVIC_VECTCNT         ((pLPC_VIC_VECTCNT)  0xFFFFF200)

/*
 ==============================================================================
 VIC
 ==============================================================================
*/
#define pWatchDog     ((pLPC_WATCHDOG)  0xE0000000)

#endif
