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
 * @date November/2010
 * 
 * @file GPIO.h
 * @brief This header file has the needed configuration to work with GPIO ports of LPC2106 from Philips.
 * 
 * */
#ifndef GPIO_H
#define GPIO_H
#include "TYPES.h"
#include "LPC21XX.h"

/**
 * @brief Macro definition of the GPIO fucntions. This definition simplify the function mask of each port, so it could be easy to switch function. @see GPIO Functions
 * @defgroup FUNCTION_MASK
 * @{
 */
#define FUNCTION_0          ((U8)   0x0)
#define FUNCTION_1          ((U8)   0x1)
#define FUNCTION_2          ((U8)   0x2)
#define PORT                ((U8)   0x2)
/**
 * @}
 * */
/**
 * @brief Definition of the direction of the Port. Should be used when working with GPIO methods.
 */
typedef enum _gpio_direction{GPIO_IN=0x0,GPIO_OUT=0x1}GPIO_DIRECTION;

/**
 * @brief Definição das mascaras referentes às funcionalidades do PINSEL0 
 **/
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_0__       (FUNCTION_0 << (PORT * 0))
#define     __PINSEL0_UART_0_TXD__          (FUNCTION_1 << (PORT * 0))
#define     __PINSEL0_PWM_1__               (FUNCTION_2 << (PORT * 0))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_1__       (FUNCTION_0 << (PORT * 1))
#define     __PINSEL0_UART_0_RXD__          (FUNCTION_1 << (PORT * 1))
#define     __PINSEL0_PWM_3__               (FUNCTION_2 << (PORT * 1))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_2__       (FUNCTION_0 << (PORT * 2))
#define     __PINSEL0_I2C_SCL__             (FUNCTION_1 << (PORT * 2))
#define     __PINSEL0_TIMER_0_CAPTURE_0_0__ (FUNCTION_2 << (PORT * 2))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT0_3__        (FUNCTION_0 << (PORT * 3))
#define     __PINSEL0_I2C_SDA__             (FUNCTION_1 << (PORT * 3))
#define     __PINSEL0_TIMER_0_MATCH_0_0__   (FUNCTION_2 << (PORT * 3))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_4__       (FUNCTION_0 << (PORT * 4))
#define     __PINSEL0_SPI_SPP_SCK__         (FUNCTION_1 << (PORT * 4))
#define     __PINSEL0_TIMER_0_CAPTURE_0_1__ (FUNCTION_2 << (PORT * 4))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_5__       (FUNCTION_0 << (PORT * 5))
#define     __PINSEL0_SPI_SPP_MISO__        (FUNCTION_1 << (PORT * 5))
#define     __PINSEL0_TIMER_0_MATCH_0_1__   (FUNCTION_2 << (PORT * 5))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_6__       (FUNCTION_0 << (PORT * 6))
#define     __PINSEL0_SPI_SPP_MOSI__        (FUNCTION_1 << (PORT * 6))
#define     __PINSEL0_TIMER_0_CAPTURE_0_2__ (FUNCTION_2 << (PORT * 6))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_7__       (FUNCTION_0 << (PORT * 7))
#define     __PINSEL0_SPI_SPP_SSEL__        (FUNCTION_1 << (PORT * 7))
#define     __PINSEL0_PWM_2__               (FUNCTION_2 << (PORT * 7))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_8__       (FUNCTION_0 << (PORT * 8))
#define     __PINSEL0_UART_1_TXD__          (FUNCTION_1 << (PORT * 8))
#define     __PINSEL0_PWM_4__               (FUNCTION_2 << (PORT * 8))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_9__       (FUNCTION_0 << (PORT * 9))
#define     __PINSEL0_UART_1_RXD__          (FUNCTION_1 << (PORT * 9))
#define     __PINSEL0_PWM_6__               (FUNCTION_2 << (PORT * 9))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_10__      (FUNCTION_0 << (PORT *10))
#define     __PINSEL0_UART_1_RTS__          (FUNCTION_1 << (PORT *10))
#define     __PINSEL0_TIMER_1_CAPTURE_1_0__ (FUNCTION_2 << (PORT *10))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_11__      (FUNCTION_0 << (PORT *11))
#define     __PINSEL0_UART_1_CTS__          (FUNCTION_1 << (PORT *11))
#define     __PINSEL0_TIMER_1_CAPTURE_1_1__ (FUNCTION_2 << (PORT *11))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_12__      (FUNCTION_0 << (PORT *12))
#define     __PINSEL0_UART_1_DSR__          (FUNCTION_1 << (PORT *12))
#define     __PINSEL0_TIMER_1_MATCH_1_0__   (FUNCTION_2 << (PORT *12))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_13__      (FUNCTION_0 << (PORT *13))
#define     __PINSEL0_UART_1_DTR__          (FUNCTION_1 << (PORT *13))
#define     __PINSEL0_TIMER_1_MATCH_1_1__    (FUNCTION_2 << (PORT *13))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_14__      (FUNCTION_0 << (PORT *14))
#define     __PINSEL0_UART_1_DCD__          (FUNCTION_1 << (PORT *14))
#define     __PINSEL0_EINT_1__              (FUNCTION_2 << (PORT *14))
/*----------------------------------------------------------------------*/
#define     __PINSEL0_GPIO_PORT_0_15__      (FUNCTION_0 << (PORT *15))
#define     __PINSEL0_UART_1_RI__           (FUNCTION_1 << (PORT *15))
#define     __PINSEL0_EINT_2__              (FUNCTION_2 << (PORT *15))
/*----------------------------------------------------------------------*/

/**
 * @brief GPIO data type structure. This struct has the needed fields name to communicate with the lpc registers.
 * @details 
 * IOPIN: GPIO Port Pin value register.
 * IOSET: GPIO Port Output Set register.
 * IODIR: GPIO Port Direction control register.
 * IOCLR: GPIO Port Output Clear register.  
 * Should use gpio_init??????? functions, so this register could be properly read.
 **/ 
typedef struct _GPIO{
	U32 IOPIN;	/* GPIO Port Pin value register.             0xE002 8000*/
	U32 IOSET;	/* GPIO Port Output Set register.            0xE002 8004*/
	U32 IODIR;	/* GPIO Port Direction control register.     0xE002 8008*/
	U32 IOCLR;	/* GPIO Port Output Clear register.          0xE002 800C*/
}LPC_GPIO,*pLPC_GPIO;

U32 gpio_read(U32 mask);
void gpio_clear(U32 mask);
void gpio_set(U32 mask);
void gpio_write(U32 mask, U32 value );
void gpio_init(U32 pinsel0_mask,U32 pinsel1_mask);
void gpio_set_direction(U32 mask, U8 direction);
void gpio_init_PINSEL0(U32 mask);
void gpio_init_PINSEL1(U32 mask);



#endif
