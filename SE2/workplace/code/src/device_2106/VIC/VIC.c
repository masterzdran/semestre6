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
#include "VIC.h"
#include "SCB.h"
/**
 * @brief VIC init
 * */
void VIC_init(){
    pVIC->IntEnClr                = 0xFFFFFFFF; 	  /*clear all interrupts*/
    pVIC->SoftIntClear            = 0xFFFFFFFF; 	  /*clear all sw interrupts*/
    pVIC->IntSelect               = 0;				      /*select IRQ*/
    /*pVIC->IntEnable               = 0xFFFFFFFF;*/ /*enable all interrupts*/
	/*pVIC_VECTDEFADDR->DefVectAddr = 0;			   */ /*clear old default isr address*/
	/*pVIC_VECTDEFADDR->VectAddr	  = 0;			   */ /*clear old isr address*/
}
/**
 * @brief Disable Irq 
 * @param peripherical: disable interrupt of this peripherical
 * */
void disableIRQ(U8 peripherical){
  pVIC->IntEnClr |=  (1 << peripherical);
}

/**
 * @brief Enable Irq 
 * @param peripherical: enable interrupt of this peripherical
 * */
void enableIRQ(U8 peripherical){
  pVIC->IntEnable |= (1 << peripherical);
}

/**
 * @brief Vectored Interrupt configuration
 * @param peripherical: id of the peripherical @see IRQ_SOURCE
 * @param priority: valid value (0-15)
 * @param (*fx): pointer to the interrupt handler function
 **/
Bool VIC_ConfigIRQ(U8 peripherical, U8 priority,void (*fx)(void)){
  PU32 vicAddr = 0,vicCtrl=0;
  if (priority < 0 || priority > __MAX_INTERRUPT__) return false;
  if (peripherical < 0 || peripherical > __MAX_INTERRUPT__) return false;
  
  disableIRQ(peripherical);
  
  vicAddr = (PU32)(&(pVIC_VECTADDR->VectAddr0) + (U32)priority);
  vicCtrl = (PU32)(&(pVIC_VECTCNT->VectCntl0) + (U32)priority*4); /* x4 beacause the register is one byte */
  *(vicAddr) = (U32)fx;
  *(vicCtrl) = __VIC_ENABLE__|(peripherical&__VIC_VECTCNTL_MASK__);
  
  enableIRQ(peripherical);
 return true;
}

/**
 * @brief CPU interrupt enable
 * */
void interrupt_enable() {
	asm("mrs r0, cpsr");
	asm("bic r0, r0, #(3 << 6)");
	asm("msr cpsr_c, r0");
}
/**
 * @brief CPU interrupt disable
 * */
void interrupt_disable() {
	asm("mrs r0, cpsr");
	asm("orr r0, r0, #(3 << 6)");
	asm("msr cpsr_c, r0");
}
