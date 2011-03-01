/**
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
#include "POWER.h"

void POWER_Off_Peripherical(ePWPeripherical peripherical){
    pPower->POWER_CONTROL_PERIPHERICAL &= ~peripherical;
}
void POWER_On_Peripherical(ePWPeripherical peripherical){
    pPower->POWER_CONTROL_PERIPHERICAL|= peripherical;
}
/**
 * Function that powerdown the device. According to the Manual, page 32:
 * "Power-down mode - when 1, this bit causes the oscillator and all on-chip clocks to be stopped. 
 * A wakeup condition from an external interrupt can cause the oscillator to restart, 
 * the PD bit to be cleared, and the processor to resume execution."
 * */
void POWER_Down(){
    pPower->POWER_CONTROL |= __PCON_PD__;
}
/**
 * Function that turn the device into idle mode. According to the Manual, page 32:
 * "Idle mode - when 1, this bit causes the processor clock to be stopped, 
 * while on-chip peripherals remain active. Any enabled interrupt from a 
 * peripheral or an external interrupt source will cause the processor to 
 * resume execution."
 * */
void POWER_Idle(){
  pPower->POWER_CONTROL |= __PCON_IDL__;
}

