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
#ifndef VIC_H
#define VIC_H
#include "TYPES.h"
#include "LPC21XX.h"



/**
 * Estrutura que define os campos dos Vectores de Controlo 
 **/
typedef struct _VIC_VECTCNT{
      U8 VectCntl0;
      U8  DUMMY03;
      U16 DUMMY04;
      U8 VectCntl1;
      U8  DUMMY05;
      U16 DUMMY06;      
      U8 VectCntl2;
      U8  DUMMY07;
      U16 DUMMY08;            
      U8 VectCntl3;
      U8  DUMMY09;
      U16 DUMMY10;            
      U8 VectCntl4;
      U8  DUMMY11;
      U16 DUMMY12;            
      U8 VectCntl5;
      U8  DUMMY13;
      U16 DUMMY14;            
      U8 VectCntl6;
      U8  DUMMY15;
      U16 DUMMY16;            
      U8 VectCntl7;
      U8  DUMMY17;
      U16 DUMMY18;            
      U8 VectCntl8;
      U8  DUMMY19;
      U16 DUMMY20;            
      U8 VectCntl9;
      U8  DUMMY21;
      U16 DUMMY22;            
      U8 VectCntl10;
      U8  DUMMY23;
      U16 DUMMY24;            
      U8 VectCntl11;
      U8  DUMMY25;
      U16 DUMMY26;            
      U8 VectCntl12;
      U8  DUMMY27;
      U16 DUMMY28;
      U8 VectCntl13;
      U8  DUMMY29;
      U16 DUMMY30;
      U8 VectCntl14;
      U8  DUMMY31;
      U16 DUMMY32;
      U8 VectCntl15;
      U8  DUMMY33;
      U16 DUMMY34;  
}LPC_VIC_VECTCNT,*pLPC_VIC_VECTCNT;  

/**
 * Estrutura que define os endereços dos Vectores
 **/
typedef struct _VIC_VECTADDR{
      U32 VectAddr0;
      U32 VectAddr1;
      U32 VectAddr2;
      U32 VectAddr3;
      U32 VectAddr4;
      U32 VectAddr5;
      U32 VectAddr6;
      U32 VectAddr7;
      U32 VectAddr8;
      U32 VectAddr9;
      U32 VectAddr10;
      U32 VectAddr11;
      U32 VectAddr12;
      U32 VectAddr13;
      U32 VectAddr14;
      U32 VectAddr15;
}LPC_VIC_VECTADDR,*pLPC_VIC_VECTADDR;


typedef struct _VIC_DEFVECTADDR{
      U32 VectAddr;
      U32 DefVectAddr;
}LPC_VIC_DEFVECTADDR,*pLPC_VIC_DEFVECTADDR;

/**
 * Estrutura que define os campos do VIC
 * */
typedef struct _VIC{
      U32 IRQStatus;
      U32 FIQStatus;
      U32 RawIntr;  
      U32 IntSelect;
      U32 IntEnable;
      U32 IntEnClr; 
      U32 SoftInt;  
      U32 SoftIntClear;
      U8 Protection;   
      U8  DUMMY01;
      U16 DUMMY02;  
}LPC_VIC,*pLPC_VIC;

/**
 * Definição de macros
 * */
#define __VIC_VECTCNTL_MASK__       (U8) 0x1F
#define __VIC_PROTECTION_MASK__     (U8) 0x01
#define __VIC_ENABLE__              (U8) 0x20
#define __MAX_INTERRUPT__           (U8) 0x0F
/**
 * Fontes de Interrupção
 **/
#define     __INTERRUPT_WDT_MASK__           (U32)   0x00000001
#define     __INTERRUPT_SOFTWARE_MASK__      (U32)   0x00000002
#define     __INTERRUPT_DbgCommRx_MASK__     (U32)   0x00000004
#define     __INTERRUPT_DbgCommTX_MASK__     (U32)   0x00000008
#define     __INTERRUPT_TIMER0_MASK__        (U32)   0x00000010
#define     __INTERRUPT_TIMER1_MASK__        (U32)   0x00000020
#define     __INTERRUPT_UART0_MASK__         (U32)   0x00000040
#define     __INTERRUPT_UART1_MASK__         (U32)   0x00000080
#define     __INTERRUPT_PWM_MASK__           (U32)   0x00000100
#define     __INTERRUPT_I2C_MASK__           (U32)   0x00000200
#define     __INTERRUPT_SPI_SSP_MASK__       (U32)   0x00000400
#define     __INTERRUPT_RESERVED_MASK__      (U32)   0x00000800     
#define     __INTERRUPT_PLL_MASK__           (U32)   0x00001000
#define     __INTERRUPT_RTC_MASK__           (U32)   0x00002000
#define     __INTERRUPT_EINT0_MASK__         (U32)   0x00004000
#define     __INTERRUPT_EINT1_MASK__         (U32)   0x00008000
#define     __INTERRUPT_EINT2_MASK__         (U32)   0x00010000
#define     __INTERRUPT_ALL__                (U32)   0x0001FFFF


/**
 * Valores de cada tipo de interrupção 
 **/
#define     __INTERRUPT_WDT_VALUE__          (U8)    0x0
#define     __INTERRUPT_SOFTWARE_VALUE__     (U8)    0x1
#define     __INTERRUPT_DbgCommRx_VALUE__    (U8)    0x2
#define     __INTERRUPT_DbgCommTX_VALUE__    (U8)    0x3
#define     __INTERRUPT_TIMER0_VALUE__       (U8)    0x4
#define     __INTERRUPT_TIMER1_VALUE__       (U8)    0x5
#define     __INTERRUPT_UART0_VALUE__        (U8)    0x6
#define     __INTERRUPT_UART1_VALUE__        (U8)    0x7
#define     __INTERRUPT_PWM_VALUE__          (U8)    0x8
#define     __INTERRUPT_I2C_VALUE__          (U8)    0x9
#define     __INTERRUPT_SPI_SSP_VALUE__      (U8)    0xA
#define     __INTERRUPT_RESERVED_VALUE__     (U8)    0xB     
#define     __INTERRUPT_PLL_VALUE__          (U8)    0xC
#define     __INTERRUPT_RTC_VALUE__          (U8)    0xD
#define     __INTERRUPT_EINT0_VALUE__        (U8)    0xE
#define     __INTERRUPT_EINT1_VALUE__        (U8)    0xF
#define     __INTERRUPT_EINT2_VALUE__        (U8)    0x10


#define     __INTERRUPT_WDT__          (U8)    0x0
#define     __INTERRUPT_SOFTWARE__     (U8)    0x1
#define     __INTERRUPT_DbgCommRx__    (U8)    0x2
#define     __INTERRUPT_DbgCommTX__    (U8)    0x3
#define     __INTERRUPT_TIMER0__       (U8)    0x4
#define     __INTERRUPT_TIMER1__       (U8)    0x5
#define     __INTERRUPT_UART0__        (U8)    0x6
#define     __INTERRUPT_UART1__        (U8)    0x7
#define     __INTERRUPT_PWM__          (U8)    0x8
#define     __INTERRUPT_I2C__          (U8)    0x9
#define     __INTERRUPT_SPI_SSP__      (U8)    0xA
#define     __INTERRUPT_RESERVED__     (U8)    0xB     
#define     __INTERRUPT_PLL__          (U8)    0xC
#define     __INTERRUPT_RTC__          (U8)    0xD
#define     __INTERRUPT_EINT0__        (U8)    0xE
#define     __INTERRUPT_EINT1__        (U8)    0xF

typedef enum _interrupt_source{
	IRQ_WATCHDOG = 0,
	IRQ_SOFTWARE,
	IRQ_DbgCommRx,
	IRQ_DbgCommTX,
	IRQ_TIMER0,
	IRQ_TIMER1,
	IRQ_UART0,
	IRQ_UART1,
	IRQ_PWM,
	IRQ_I2C,
	IRQ_SPI_SSP,
	IRQ_PLL=0xC,
	IRQ_RTC,
	IRQ_EXT_INT0,
	IRQ_EXT_INT1	
}IRQ_SOURCE;

typedef enum _interrupt_priority{
	IRQ_PRIORITY_00 = 0,
	IRQ_PRIORITY_01
	IRQ_PRIORITY_02
	IRQ_PRIORITY_03
	IRQ_PRIORITY_04
	IRQ_PRIORITY_05
	IRQ_PRIORITY_06
	IRQ_PRIORITY_07
	IRQ_PRIORITY_08
	IRQ_PRIORITY_09
	IRQ_PRIORITY_10
	IRQ_PRIORITY_11
	IRQ_PRIORITY_12
	IRQ_PRIORITY_13
	IRQ_PRIORITY_14
	IRQ_PRIORITY_15
}IRQ_PRIORITY;
/**
 * Assinatura das funções publicas
 * */
Bool VIC_ConfigIRQ(U8 peripherical, U8 priority,void (*fx)(void));
void VIC_init();
void disableIRQ(U8 peripherical);
void enableIRQ(U8 peripherical);
void interrupt_enable();
void interrupt_disable();

#endif
