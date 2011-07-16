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
**/ 
#ifndef WATCHDOG_H
#define WATCHDOG_H
#include "TYPES.h"
#include "LPC21XX.h"

/**
 * @brief Definition of the Watchdof structure 
 **/
typedef struct _WATCHDOG{
    U8		MODE_REGISTER;
    U8    	DUMMY01[3];
    U32		TIMER_CONSTANT;
    U8		FEED_SEQUENCE;
    U8    	DUMMY03[3];
    U32		TIMER_VALUE;
}LPC_WATCHDOG, *pLPC_WATCHDOG;

/**
 * @defgroup WD_CONFIG_MACRO
 * @{
 * */
#define   __WDEN_MASK__         0x1
#define   __WDRESET_MASK__      0x2
#define   __WDTOF_MASK__        0x4
#define   __WDINT_MASK__        0x8
#define   __WDMOD_MASK__        0xF

#define   __DECREASE_COUNT__        CCLK * 4        
#define   __MIN_DECREASE_COUNT__    CCLK * 256 * 4  

#define   __WDFEED_MASK__     0xF
#define   __WD_FEED_AA__         ((const unsigned char ) 0xAA )
#define   __WD_FEED_55__         ((const unsigned char ) 0x55 )
#define   WD_FEED()              {pWatchDog->FEED_SEQUENCE = __WD_FEED_AA__; pWatchDog->FEED_SEQUENCE = __WD_FEED_55__;}

/**
 * @}
 */
/**
 * @brief Check if WatchDog is running
 */
#define WD_ISRUNNING()           ( pWatchDog->MODE_REGISTER & __WDEN_MASK__ )
/**
 * @brief Enable WatchDog 
 */
#define WD_ENABLE()              ( pWatchDog->MODE_REGISTER |= __WDEN_MASK__ )
/**
 * @brief Disable WatchDog 
 */
#define WD_DISABLE()             ( pWatchDog->MODE_REGISTER &= ~(__WDEN_MASK__) )
/**
 * @brief Enable WatchDog Reset
 */
#define WD_RESET_ENABLE()        ( pWatchDog->MODE_REGISTER |= __WDRESET_MASK__ )
/**
 * @brief Disable WatchDog Reset
 * */
#define WD_RESET_DISABLE()       ( pWatchDog->MODE_REGISTER &= ~(__WDRESET_MASK__) )
/**
 * @brief Verify if WatchDog Comes from an Reset
 * */
#define WD_COME_FROM_RESET()     ( pWatchDog->MODE_REGISTER & __WDTOF_MASK__ )
/**
 * @brief Read Current WatchDog Time
 * */
#define WD_READ_TIME()           ( pWatchDog->TIMER_VALUE)

void WATCHDOG_init(U32 value);
void WD_reset();

#endif
