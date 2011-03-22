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
/**
 * @author Nuno Cancelo, (nuno.cancelo<at>gmail.com)
 * @author Nuno Sousa,   (ng.sousa<at>gmail.com)
 * @date November/2010
 * 
 * @file  LPC2106.h
 * @brief Module to configure GPIO ports of LPC2106 from Philips
 * 
 * */
#ifndef LPC2106_H
#define LPC2106_H
#include "TYPES.h"
/*
 ==============================================================================
 GPIO
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an GPIO structure
 * */
#define       pGPIO 	    ((pLPC_GPIO)	0xE0028000)
/**
 * @brief Definition of one pointer to an PINSEL0 structure
 * */
#define     __PINSEL0__     (*((PDWord)0xE002C000))
/**
 * @brief Definition of one pointer to an PINSEL1 structure
 * */
#define     __PINSEL1__     (*((PDWord)0xE002C004))

/*
 ==============================================================================
 I2C
 ==============================================================================
*/

/**
 * @brief Definition of one pointer to an I2C structure
 * */
#define     pI2C      (((pLPC_I2C) 0xE001C000))

/*
 ==============================================================================
 RTC
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an RTC structure
 * */
#define     pRTC      			(((pLPC_RTC) 0xE0024000))

/*
 ==============================================================================
 SCB
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an External Interrupt structure
 * */
#define    pEXT_INT       ((pLPC_EXT_INT) 0xE01FC140)
/**
 * @brief Definition of one pointer to an Memory Acellator Module structure
 * */
#define    pMAM           ((pLPC_MAM)     0xE01FC000)     
/**
 * @brief Definition of one pointer to an PLL structure
 * */
#define    pPLL           ((pLPC_PLL)     0xE01FC080)  
/**
 * @brief Definition of one pointer to an POWER structure
 * */
#define    pPOWER         ((pLPC_POWER)   0xE01FC0C0)
/**
 * @brief Definition of one pointer to an APB structure
 * */
#define    pAPBDIV        ((pLPC_APB)     0xE01FC100)
/**
 * @brief Definition of one pointer to an SCS structure
 * */
#define    pSCS           ((pLPC_SCS)     0xE01FC1A0)

/*
 ==============================================================================
 SPI
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an SPI structure
 * */
#define pSPI      ((pLPC_SPI)         0xE0020000)
/**
 * @brief Definition of one pointer to an SPI Interrupt structure
 * */
#define pSPIINT   ((pLPC_SPI_INT)     0xE002001C)

/*
 ==============================================================================
 TIMER
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an TIMER(0) structure
 * */
#define pTIMER0 ((pLPC_TIMER) 0xE0004000)
/**
 * @brief Definition of one pointer to an TIMER(1) structure
 * */
#define pTIMER1 ((pLPC_TIMER) 0xE0008000)

/*
 ==============================================================================
 UART
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an UART(0) structure
 * */
#define pUART0              ((pLPC_UART) 0xE0000000)
/**
 * @brief Definition of one pointer to an UART(1) structure
 * */
#define pUART1              ((pLPC_UART) 0xE0010000)

/*
 ==============================================================================
 VIC
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an VIC structure
 * */
#define         pVIC                 ((pLPC_VIC)           0xFFFFF000)
/**
 * @brief Definition of one pointer to an VIC DEFAULT VECTOR structure
 * */
#define         pVIC_VECTDEFADDR     ((pLPC_VIC_DEFVECTADDR)  0xFFFFF030)
/**
 * @brief Definition of one pointer to an VIC VECTOR ADDRESS structure
 * */
#define         pVIC_VECTADDR        ((pLPC_VIC_VECTADDR) 0xFFFFF100)
/**
 * @brief Definition of one pointer to an VIC VECTOR INTERRUPT structure
 * */
#define         pVIC_VECTCNT         ((pLPC_VIC_VECTCNT)  0xFFFFF200)

/*
 ==============================================================================
 WD
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an WATCHDOG structure
 * */
#define pWatchDog     ((pLPC_WATCHDOG)  0xE0000000)

#endif
