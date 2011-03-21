#include "GPIO.h"
#include "TIMER.h"
#include "RTC.h"
#include "Clock.h"
#include "TYPES.h"
#include "startosc.h"
#include "stdio.h"
#include "I2C.h"
#include "VIC.h"
#include "WATCHDOG.h"
#include "SPI_Public.h"

#define  LCD_MASK   ((U32) 0x7F00)


int main(){
  TIMER_init(pTIMER1,58982400/MICRO);
  TIMER_init(pTIMER0,58982400/MICRO);
  rtc_init();
  VIC_init();
  
  //VIC_ConfigIRQ(__INTERRUPT_TIMER0__,1,timer0isr);
  //WATCHDOG_init(0x0FFFFFFF);  
  //interrupt_enable(); 
  

typedef struct _SPI_DEVICE{
  const void (*irqHandler)(void);	/*função de tratamento de interrupções*/
  U32   clock;		      /*ritmo do sinal de relógio*/  
  U32   chipSelect:4;	  /*define a identificação do periférico*/
  U32   nbrbits:4;		  /*número de bits de u[]ma palavra*/
  U32   mode:2;			    /*modo SPI (CPHA, CPOL). do tipo SPI_MODE*/
  U32   role:1;			    /*qual o papel do periferico: 1- Master; 0- Slave SPI_ROLE*/
  U32   started:1;      /*indicação se o periférico foi préviamente iniciada. Por omissão o mesmo deve estar a 0. Não se garante o comportamento caso na construção se coloque a 1.*/
  U32   byteShift:1;    /*SPI_BYTE_SHIFT*/
}SPI_Device,*pSPI_Device;

  SPI_Device spis[0];
  spis[] = {
    {
      10,   /*clock divider */
      0,    /*id do periferico = 0*/
      8,    /*num bits palavra*/
      0,    /*mode*/
      1,    /*role = master*/
      0,    /*not started yet*/
      0     /*byte shitf ??*/
    }
  };
  
  SPI_init(spis, 1);
  
 
	while(1){
    U8 out_buffer[] = {0x35, 0x7a};
    U8 in_buffer[sizeof(out_buffer)];
    SPI_start_device(spis[0]);
    SPI_transfer(spis[0], sizeof(out_buffer), out_buffer, in_buffer);
    SPI_stop_device(spis[0]);
	
  
  
  
  }
}

