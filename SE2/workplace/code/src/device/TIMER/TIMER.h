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
#ifndef TIMER_H
#define TIMER_H
#include "TYPES.h"
#include "LPC21XX.h"
#include "GPIO.h"
#include "startosc.h"

/**
 * @defgroup TIMER_CONFIG_MACRO
 * @{
 */
#define __TCR_DISABLE__                  0x0
#define __TCR_ENABLE__                   0x1
#define __TCR_RESET_DISABLE__            0x0
#define __TCR_RESET_ENABLE__             0x2

#define __CTCR_MODE_0__                  0x0
#define __CTCR_MODE_1__                  0x1
#define __CTCR_MODE_2__                  0x2
#define __CTCR_MODE_3__                  0x3

#define __EMR_M

#define __INTERRUPT_MR0__                 1 << 0
#define __RESET_MR0__                     1 << 1       
#define __STOP_MR0__                      1 << 2
#define __INTERRUPT_MR1__                 1 << 3
#define __RESET_MR1__                     1 << 4
#define __STOP_MR1__                      1 << 5
#define __INTERRUPT_MR2__                 1 << 6
#define __RESET_MR2__                     1 << 7
#define __STOP_MR2__                      1 << 8
#define __INTERRUPT_MR3__                 1 << 9
#define __RESET_MR3__                     1 << 10
#define __STOP_MR3__                      1 << 11

#define __CAPTURE0_RISING_EDGE__          1 << 0
#define __CAPTURE0_FALLING_EDGE__         1 << 1       
#define __CAPTURE0_INTERRUPT__            1 << 2
#define __CAPTURE1_RISING_EDGE__          1 << 3
#define __CAPTURE1_FALLING_EDGE__         1 << 4
#define __CAPTURE1_INTERRUPT__            1 << 5

#define __CAP1_MSK__                      ~(__CAPTURE1_RISING_EDGE__|__CAPTURE1_FALLING_EDGE__|__CAPTURE1_INTERRUPT__)
#define __CAPTURE2_RISING_EDGE__          1 << 6
#define __CAPTURE2_FALLING_EDGE__         1 << 7
#define __CAPTURE2_INTERRUPT__            1 << 8
#define __CAPTURE3_RISING_EDGE__          1 << 9
#define __CAPTURE3_FALLING_EDGE__         1 << 10
#define __CAPTURE3_INTERRUPT__            1 << 11

#define __MATCH_INTERRUPT__                 (1 << 0)
#define __MATCH_RESET__                     (1 << 1)       
#define __MATCH_STOP__                      (1 << 2)

#define __CAPTURE_RISE__                    (1<<0)
#define __CAPTURE_FALL__                    (1<<1)
#define __CAPTURE_INTERRUPT__               (1<<2)

#define SECOND  1
#define MILI    1000
#define MICRO   1000000
#define NANO    1000000000 

/*
 * @}
 * */

/**
 * @brief Definition of the valid timer match pin values. These values should be used when using Timer Match functions
 * */
typedef enum TIMER_MATCH {
  MAT00 =	PINSEL0_TIMER_0_MATCH_0_0,
  MAT01 =	PINSEL0_TIMER_0_MATCH_0_1,
  MAT10 =	PINSEL0_TIMER_1_MATCH_1_0,
  MAT11 =	PINSEL0_TIMER_1_MATCH_1_1
}TMatch;

/**
 * @brief Definition of the valid timer capture pin values. These values should be used when using Timer Capture functions
 * */
typedef enum TIMER_CAPTURE {
  CAP00 = 	PINSEL0_TIMER_0_CAPTURE_0_0,
  CAP01 = 	PINSEL0_TIMER_0_CAPTURE_0_1,
  CAP02 = 	PINSEL0_TIMER_0_CAPTURE_0_2,
  CAP10 = 	PINSEL0_TIMER_1_CAPTURE_1_0,
  CAP11 = 	PINSEL0_TIMER_1_CAPTURE_1_1
}TCapture;

/**
 * @brief Definition of the valid EMR FUNCTION for timer macth pin values. These values should be used when using Timer match functions
 * */
typedef enum EMR_FUNCTION {MATCH_NOTHING=0,MATCH_CLEAR,MATCH_SET,MATCH_TOGGLE} tEmrFunction;

/**
 * @brief Definition of the valid CTCR FUNCTION timer capture pin values. These values should be used when using Timer Capture functions
 * */
typedef enum CTCR_FUNCTION {TIMER_MODE=0,COUNTER_MODE_RISE,COUNTER_MODE_FALL,COUNTER_MODE_BOTH} tCtcrFunction;
/**
 * @brief Definition of the Timer  structure. 
 * */
typedef struct _TIMER{
    U32		IR;             
    U32		TCR;
    U32		TC;
    U32		PR;
    U32		PC;
    U32		MCR;
    U32		MR0;
    U32		MR1;
    U32		MR2;
    U32		MR3;
    U32		CCR;
    U32		CR0;
    U32		CR1;
    U32		CR2;
    U32		CR3;          
    U32		EMR;             
    U32   DUMMY01[12];         
    U32   CTCR;            
}LPC_TIMER,*pLPC_TIMER;




/**
 * @brief Delay of B seconds on Timer A:
 * MACRO Signature: timer_sleep_seconds(pLPC_TIMER timer, U32 elapse)
 * */
#define     timer_sleep_seconds(A,B)            (TIMER_delay(A,((( getPeriphericalClock()/SECOND)/((A)->PR))*B)))

/**
 * @brief Delay of B mili-seconds on Timer A:
 * MACRO Signature: timer_sleep_miliseconds(pLPC_TIMER timer, U32 elapse)
 * */
#define     timer_sleep_miliseconds(A,B)        (TIMER_delay(A,((( getPeriphericalClock()/MILI)/((A)->PR))*B)))

/**
 * @brief Delay of B micro-seconds on Timer A:
 * MACRO Signature: timer_sleep_microseconds(pLPC_TIMER timer, U32 elapse)
 * */
#define     timer_sleep_microseconds(A,B)     	(TIMER_delay(A,((( getPeriphericalClock()/MICRO)/((A)->PR))*B)))

/**
 * @brief Enable of Timer A:
 * MACRO Signature: timer_start(pLPC_TIMER timer)
 * */
#define timer_start(A)                  ((A)->TCR |= __TCR_ENABLE__)

/**
 * @brief Disable of Timer A:
 * MACRO Signature: timer_stop(pLPC_TIMER timer)
 * */
#define timer_stop(A)                   ((A)->TCR &= ~(__TCR_ENABLE__))

/**
 * @brief Elapsed time:
 * MACRO Signature: timer_elapsed(pLPC_TIMER timer, U32 lastTime)
 * */
#define timer_elapsed(A,B)              ((A)->TC - B)

/**
 * @brief Current timer value:
 * MACRO Signature: timer_now(pLPC_TIMER timer)
 * */
#define timer_now(A)					((A)->TC)
/**
 * @brief Reset of the timer value:
 * MACRO Signature: timer_reset(pLPC_TIMER timer)
 * */
#define timer_reset(A)                  {(A)->TCR |= __TCR_RESET_ENABLE__; (A)->TCR &= ~(__TCR_RESET_ENABLE__);}

void TIMER_init(pLPC_TIMER timer, U32 countNbr);
void TIMER_delay(pLPC_TIMER timer, U32 elapse);
void TIMER_capture_init(pLPC_TIMER timer,U8 channel, U32 captureMask, U32 countNbr,tCtcrFunction ctcrFunction);
void TIMER_enable(pLPC_TIMER timer);
void TIMER_ext_match_init(pLPC_TIMER timer,U8 channel, U32 MatchMask, U32 countNbr,tEmrFunction emrFunction);
void TIMER_ext_match_changeTime(pLPC_TIMER timer,U8 channel,U8 up, U8 dif);
void TIMER_ext_match_stop(pLPC_TIMER timer,U8 channel, U32 emrFunction);
void TIMER_ext_match_start(pLPC_TIMER timer,U8 channel, U32 emrFunction);

#endif
