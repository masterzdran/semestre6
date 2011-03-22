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
 * @file  POWER.c
 * @brief Module to configure GPIO ports of LPC2106 from Philips
 * 
 * */
#include "POWER.h"

/**
 * @brief Turn off the peripherical device in peripherical.
 * @remarks Should use the appropriate value in enum 'ePWPeripherical', for best accurracy. 
 * @param peripherical: Peripherical to be powered off.
 * */
void POWER_Off_Peripherical(ePWPeripherical peripherical){
    pPOWER->POWER_CONTROL_PERIPHERICAL &= ~peripherical;
}

/**
 * @brief Turn on the peripherical device in  peripherical.
 * @remarks Should use the appropriate value in enum 'ePWPeripherical', for best accurracy. 
 * @param peripherical: Peripherical to be powered on.
 * */
void POWER_On_Peripherical(ePWPeripherical peripherical){
    pPOWER->POWER_CONTROL_PERIPHERICAL|= peripherical;
}

/**
 * @brief Function that powerdown the device. 
 * @details 
 * According to the Manual, page 32:
 * "Power-down mode - when 1, this bit causes the oscillator and all on-chip clocks to be stopped. 
 * A wakeup condition from an external interrupt can cause the oscillator to restart, 
 * the PD bit to be cleared, and the processor to resume execution."
 **/
void POWER_Down(){
    pPOWER->POWER_CONTROL |= __PCON_PD__;
}

/**
 * @brief Function that turn the device into idle mode. 
 * @details 
 * According to the Manual, page 32:
 * "Idle mode - when 1, this bit causes the processor clock to be stopped, 
 * while on-chip peripherals remain active. Any enabled interrupt from a 
 * peripheral or an external interrupt source will cause the processor to 
 * resume execution."
 **/
void POWER_Idle(){
  pPOWER->POWER_CONTROL |= __PCON_IDL__;
}

