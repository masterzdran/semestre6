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
 * @file  GPIO.c
 * @brief Module to configure GPIO ports of LPC2106 from Philips
 * 
 * */
#include "GPIO.h"
/**
 * @brief Initialization of GPIO port setting the masks of the parameters.
 * @param mask: mask of the bits to be set with the desired GPIO Function (PINSEL0)
 **/
void gpio_init_PINSEL0(U32 mask){ 
 __PINSEL0__ &= ~mask; 
 __PINSEL0__ |= mask; 
}
/**
 * @brief Initialization of GPIO port setting the masks of the parameters.
 * @param mask: mask of the bits to be set with the desired GPIO Function (PINSEL1)
 **/
void gpio_init_PINSEL1(U32 mask){   
  __PINSEL1__ &= ~mask;
  __PINSEL1__ |= mask;
}
/**
 * @brief Initialization of GPIO port setting the masks of the parameters.
 * @param  pinsel0_mask: mask of the bits to be set with the desired GPIO Function (PINSEL0)
 * @param  pinsel1_mask: mask of the bits to be set with the desired GPIO Function (PINSEL1)
 **/
void gpio_init(U32 pinsel0_mask,U32 pinsel1_mask){
  gpio_init_PINSEL0(pinsel0_mask);
  gpio_init_PINSEL1(pinsel1_mask);
} 
/**
 * @brief This method write the value in the bits define by the mask.
 * @param mask: bitmap mask which are needed to be written.
 * @param value: value to be written in the bits of the mask.
 * @warning The 'value' should be set before the be written in the bits of mask. No shift will be made to set the 'value' in the port.
 * @warning Before writing the 'value', the bits defined by the mask will be cleared. All value processing of the return should be made by the calling program.
 **/
void gpio_write(U32 mask, U32 value){
  pGPIO->IOCLR |= mask ;
  pGPIO->IOSET |= mask & value;    
}
/**
 * @brief Define the direction of GPIO port defined by the mask
 * @param mask: bitmap mask of the bit needed to be directed
 * @param direction: Direction of the port. Should use typedef enum _gpio_direction to set an valid value.
 **/ 
void gpio_set_direction(U32 mask, U8 direction){
  if (direction)
    pGPIO->IODIR |= mask;
  else
    pGPIO->IODIR &= ~mask;
}
/**
 * @brief Set bit defined by the 'mask' in gpio port
 * @param mask: bitmap mask with the bits to be setted.
 * @warning The action write 'ONE' the every bit of the mask.
 **/ 
void gpio_set(U32 mask){
  pGPIO->IOSET |= mask;
}

/**
 * @brief clear bits defined by 'mask' of gpio port
 * @param mask: bitmap mask with the bits to be cleared
 * @warning The action write 'ZERO' the every bit of the mask.
 **/ 
void gpio_clear(U32 mask){
  pGPIO->IOCLR |= mask ;
}
/**
 * @brief Read GPIO port defined by 'mask' and return the value read
 * @param mask: bitmap mask with the activated bits of the port to be read
 * @return U32
 **/
U32 gpio_read(U32 mask){
    return  pGPIO->IOPIN & mask;
}
