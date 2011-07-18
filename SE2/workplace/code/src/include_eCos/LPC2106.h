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
#define       pGPIO 	    ((pLPC_GPIO)	CYGARC_HAL_LPC2XXX_REG_IO_BASE)
/**
 * @brief Definition of one pointer to an PINSEL0 structure
 * */
#define     PINSEL0     (CYGARC_HAL_LPC2XXX_REG_PIN_BASE + CYGARC_HAL_LPC2XXX_REG_PINSEL0)
#define     __PINSEL0__     (*((PDWord)		CYGARC_HAL_LPC2XXX_REG_PIN_BASE + CYGARC_HAL_LPC2XXX_REG_PINSEL0))
/**
 * @brief Definition of one pointer to an PINSEL1 structure
 * */
#define     __PINSEL1__     (*((PDWord)		CYGARC_HAL_LPC2XXX_REG_PIN_BASE + CYGARC_HAL_LPC2XXX_REG_PINSEL0))

/*
 ==============================================================================
 I2C
 ==============================================================================
*/

/**
 * @brief Definition of one pointer to an I2C structure
 * */
#define     pI2C      (((pLPC_I2C) CYGARC_HAL_LPC2XXX_REG_I2_BASE))

/*
 ==============================================================================
 RTC
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an RTC structure
 * */
#define     pRTC      			(((pLPC_RTC) CYGARC_HAL_LPC2XXX_REG_RTC_BASE))

/*
 ==============================================================================
 SCB
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an External Interrupt structure
 * */
#define    pEXT_INT       ((pLPC_EXT_INT) CYGARC_HAL_LPC2XXX_REG_SCB_BASE + CYGARC_HAL_LPC2XXX_REG_EXTINT)
/**
 * @brief Definition of one pointer to an Memory Acellator Module structure
 * */
#define    pMAM           ((pLPC_MAM)     CYGARC_HAL_LPC2XXX_REG_SCB_BASE)
/**
 * @brief Definition of one pointer to an PLL structure
 * */
#define    pPLL           ((pLPC_PLL)     CYGARC_HAL_LPC2XXX_REG_SCB_BASE + CYGARC_HAL_LPC2XXX_REG_PLLCON)
/**
 * @brief Definition of one pointer to an POWER structure
 * */
#define    pPOWER         ((pLPC_POWER)   CYGARC_HAL_LPC2XXX_REG_SCB_BASE + CYGARC_HAL_LPC2XXX_REG_PCON)
/**
 * @brief Definition of one pointer to an APB structure
 * */
#define    pAPBDIV        ((pLPC_APB)     CYGARC_HAL_LPC2XXX_REG_SCB_BASE + CYGARC_HAL_LPC2XXX_REG_VPBDIV)
/**
 * @brief Definition of one pointer to an SCS structure
 * */
/*#define    pSCS           ((pLPC_SCS)     CYGARC_HAL_LPC2XXX_REG_SCB_BASE + 0xE01FC1A0)*/

/*
 ==============================================================================
 SPI
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an SPI structure
 * */
#define pSPI      ((pLPC_SPI)         CYGARC_HAL_LPC2XXX_REG_SPI0_BASE)
/**
 * @brief Definition of one pointer to an SPI Interrupt structure
 * */
#define pSPIINT   ((pLPC_SPI_INT)     CYGARC_HAL_LPC2XXX_REG_SPI0_BASE + CYGARC_HAL_LPC2XXX_REG_SPI_SPINT)

/*
 ==============================================================================
 TIMER
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an TIMER(0) structure
 * */
#define pTIMER0 ((pLPC_TIMER) CYGARC_HAL_LPC2XXX_REG_TIMER0_BASE)
/**
 * @brief Definition of one pointer to an TIMER(1) structure
 * */
#define pTIMER1 ((pLPC_TIMER) CYGARC_HAL_LPC2XXX_REG_TIMER1_BASE)

/*
 ==============================================================================
 UART
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an UART(0) structure
 * */
#define pUART0              ((pLPC_UART) CYGARC_HAL_LPC2XXX_REG_UART0_BASE)
/**
 * @brief Definition of one pointer to an UART(1) structure
 * */
#define pUART1              ((pLPC_UART) CYGARC_HAL_LPC2XXX_REG_UART1_BASE)

/*
 ==============================================================================
 VIC
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an VIC structure
 * */
#define         pVIC                 ((pLPC_VIC)           CYGARC_HAL_LPC2XXX_REG_VIC_BASE)
/**
 * @brief Definition of one pointer to an VIC DEFAULT VECTOR structure
 * */
#define         pVIC_VECTDEFADDR     ((pLPC_VIC_DEFVECTADDR)  CYGARC_HAL_LPC2XXX_REG_VIC_BASE + CYGARC_HAL_LPC2XXX_REG_VICVECTADDR)
/**
 * @brief Definition of one pointer to an VIC VECTOR ADDRESS structure
 * */
#define         pVIC_VECTADDR        ((pLPC_VIC_VECTADDR) CYGARC_HAL_LPC2XXX_REG_VIC_BASE + CYGARC_HAL_LPC2XXX_REG_VICVECTADDR0)
/**
 * @brief Definition of one pointer to an VIC VECTOR INTERRUPT structure
 * */
#define         pVIC_VECTCNT         ((pLPC_VIC_VECTCNT)  CYGARC_HAL_LPC2XXX_REG_VIC_BASE +  CYGARC_HAL_LPC2XXX_REG_VICVECTCNTL0)

/*
 ==============================================================================
 WD
 ==============================================================================
*/
/**
 * @brief Definition of one pointer to an WATCHDOG structure
 * */
#define pWatchDog     ((pLPC_WATCHDOG)  CYGARC_HAL_LPC2XXX_REG_WD_BASE)

#endif
