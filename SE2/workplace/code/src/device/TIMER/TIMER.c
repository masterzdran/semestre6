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
#include "SCB.h"
#include "TIMER.h"

/**
 * @defgroup TIMER_CONTROL_VALUES
 * @{
 */
#define _Timer0_Capture_MAX 3
#define _Timer1_Capture_MAX 2
#define _Timer0_Match_MAX 2
#define _Timer1_Match_MAX 2
/**
 * @}
 */



/**
 * @brief Initialization of the timer
 * @param timer: pointer to timer structure
 * @param countNbr: value in whitch the timer pr is counting
 * */
void TIMER_init(pLPC_TIMER timer, U32 countNbr){
  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;
  timer->CTCR   |= __CTCR_MODE_0__;
  timer->PR     = countNbr;                           
  timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__; 
}

/**
 * @brief Timer delay. Wait for some time
 * @param timer: pointer to timer structure
 * @param elapse: value to be waited
 * */
void TIMER_delay(pLPC_TIMER timer, U32 elapse){
    U32 time;
    timer->PC = 0;                          
    time = timer_elapsed(timer,0);
    while(timer_elapsed(timer,time)<= elapse);
}
/**
 * @brief Enable of the timer
 * @param timer: timer to be enabled
 */
void TIMER_enable(pLPC_TIMER timer){
	timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__;
}
/**
 * @brief Init of Timer capture
 * @param timer: pointer to timer structure
 * @param channel: valid Timer Capture channel.0-2 in Timer 0, 0-1 in Timer 1
 * @param captureMask: Counting Method
 * @param countNbr: Number of counting
 * @param ctcrFunction: valid value of timer capture mode
 * */

void TIMER_capture_init(pLPC_TIMER timer,U8 channel, U32 captureMask, U32 countNbr,tCtcrFunction ctcrFunction){
  U32 _Timer0_Capture_Mask[3]={PINSEL0_TIMER_0_CAPTURE_0_0,PINSEL0_TIMER_0_CAPTURE_0_1,PINSEL0_TIMER_0_CAPTURE_0_2};
  U32 _Timer1_Capture_Mask[2]={PINSEL0_TIMER_1_CAPTURE_1_0,PINSEL0_TIMER_1_CAPTURE_1_1};

  /*Enable GPIO for Timer Capture or Else*/
  if (timer  == pTIMER0 ){
    if (channel >= _Timer0_Capture_MAX)
      return;
    GPIO_INIT_PINSEL0(_Timer0_Capture_Mask[channel]);
  }else if (timer == pTIMER1){
    if (channel >= _Timer1_Capture_MAX)
      return;
    GPIO_INIT_PINSEL0(_Timer1_Capture_Mask[channel]);
  }else {
    return;
  }
  
  timer->TCR                    = __TCR_DISABLE__|__TCR_RESET_ENABLE__; 
  timer->CCR                    |= (captureMask)<<(3*channel);                         
  if(captureMask & __CAPTURE_INTERRUPT__)
	  timer->IR		= (1<<(channel+4));  
  timer->TCR                    = __TCR_ENABLE__|__TCR_RESET_DISABLE__; 
}
/**
 * @brief Enable of External Match
 * @param timer: pointer to timer structure
 * @param channel: valid Timer Match channel.0-1 in Timer 0, 0-1 in Timer 1
 * @param MatchMask: Counting Method
 * @param countNbr: Number of counting 
 * @param emrFunction: valid value of timer match mode
 * @todo : Working, need to be Generic...
 * 
 * */
void TIMER_ext_match_init(pLPC_TIMER timer,U8 channel, U32 MatchMask, U32 countNbr,tEmrFunction emrFunction){
  U32 _Timer1_Match_Mask[2]={PINSEL0_TIMER_1_MATCH_1_0,PINSEL0_TIMER_1_MATCH_1_1};
  U32 _Timer0_Match_Mask[2]={PINSEL0_TIMER_0_MATCH_0_0,PINSEL0_TIMER_0_MATCH_0_1};
  if (timer  == pTIMER0 ){
    if (channel >= _Timer0_Match_MAX)
      return;
    GPIO_INIT_PINSEL0(_Timer0_Match_Mask[channel]);
  }else if (timer == pTIMER1){
    if (channel >= _Timer1_Match_MAX)
      return;
    GPIO_INIT_PINSEL1(_Timer1_Match_Mask[channel]);
  }else{
    return;
  }

  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;
  *(&(timer->MR0) + channel)    = countNbr;  
  timer->MCR    |= (MatchMask)<<(3*channel);
  timer->EMR    |= (1<<channel) | ((emrFunction << 2*channel)<<4) ;                              
  if(MatchMask & __MATCH_INTERRUPT__)
	  timer->IR		= (1<<channel);
}

/**
 * @brief External Match stop
 * @param timer: pointer to timer structure
 * @param channel: valid Timer Match channel.0-1 in Timer 0, 0-1 in Timer 1
 * @param emrFunction: valid value of timer match mode
 * */
void TIMER_ext_match_stop(pLPC_TIMER timer,U8 channel, U32 emrFunction){
  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;
  timer->EMR    &= ~(1<<channel) | ~((emrFunction << 2*channel)<<4);
  timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__;   
}
/**
 * @brief External Match start
 * @param timer: pointer to timer structure
 * @param channel: valid Timer Match channel.0-1 in Timer 0, 0-1 in Timer 1
 * @param emrFunction: valid value of timer match mode
 * */
void TIMER_ext_match_start(pLPC_TIMER timer,U8 channel, U32 emrFunction){
  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;
  timer->EMR    |= (1<<channel) | ((emrFunction << 2*channel)<<4);
  timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__;   
}


/**
 * @brief Timer match init
 * @param timer:  pointer to timer structure
 * @param timerMatch: Pin enable
 * @param MatchMask: Counting Method
 * @param countNbr: Number of counting 
 * @warning Not Tested:Deprecated
 * */
void TIMER_match_init(pLPC_TIMER timer,TMatch timerMatch, U32 MatchMask, U32 countNbr){
  /*Enable GPIO for Timer Capture or Else*/
  if (timer  == pTIMER0 ){
	  GPIO_INIT_PINSEL0(timerMatch);
  }else if(timer == pTIMER1){
	  GPIO_INIT_PINSEL1(timerMatch);
  }else {
    return;
  }
  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;  
  timer->MCR    = MatchMask;                         	
  timer->PR     = countNbr;                           
  timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__;
}

