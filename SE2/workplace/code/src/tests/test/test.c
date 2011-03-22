#include "GPIO.h"
#include "TIMER.h"
#include "RTC.h"
#include "TYPES.h"
#include "startosc.h"
#include "stdio.h"
#include "I2C.h"
#include "VIC.h"
#include "WATCHDOG.h"
#include "SPI.h"

#define  LCD_MASK   ((U32) 0x7F00)


int main(){
  SPI_Device spis[1]= {
    {
      0,
      10,   /*clock divider */
      1<<8,    /*id do periferico = GPIO pin 8*/
      8,    /*num bits palavra*/
      SPI_Prior_to_first_SCK_rising_edge,    /*mode*/
      SPI_MASTER,    /*role = master*/
      0,    /*not started yet*/
      SPI_MSB     /*byte shitf ??*/
    }
  };
  TIMER_init(pTIMER1,58982400/MICRO);
  TIMER_init(pTIMER0,58982400/MICRO);
  rtc_init();
  VIC_init();
  
  /*
  VIC_ConfigIRQ(__INTERRUPT_TIMER0__,1,timer0isr);
  WATCHDOG_init(0x0FFFFFFF);  
  interrupt_enable(); 
  */


  
  SPI_init(spis, 1);
  
 
  while(1){
    U8 out_buffer[] = {0x35, 0x7a};
    U8 in_buffer[sizeof(out_buffer)];
    SPI_start_device(&spis[0]);
    SPI_transfer(&spis[0], sizeof(out_buffer), out_buffer, in_buffer);
    SPI_stop_device(&spis[0]);
	
  
  
  
  }
}

