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
#include "GPIO.h"

void gpio_init_PINSEL0(U32 mask){ 
 __PINSEL0__ &= ~mask; 
 __PINSEL0__ |= mask; 
}

void gpio_init_PINSEL1(U32 mask){   
  __PINSEL1__ &= ~mask;
  __PINSEL1__ |= mask;
}

void gpio_init(U32 pinsel0_mask,U32 pinsel1_mask){
  gpio_init_PINSEL0(pinsel0_mask);
  gpio_init_PINSEL1(pinsel1_mask);
} 

void gpio_write(U32 mask, U32 value){
  pGPIO->IOCLR |= mask ;
  pGPIO->IOSET |= mask & value;    
}

void gpio_set_direction(U32 mask, U8 direction){
  if (direction)
    pGPIO->IODIR |= mask;
  else
    pGPIO->IODIR &= ~mask;
}

void gpio_set(U32 mask){
  pGPIO->IOSET |= mask;
}

void gpio_clear(U32 mask){
  pGPIO->IOCLR |= mask ;
}

U32 gpio_read(U32 mask){
    return  pGPIO->IOPIN & mask;
}
