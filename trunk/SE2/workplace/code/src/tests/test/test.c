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
#include "console.h"
#define  LCD_MASK   ((U32) 0x7F00)


static U8 ether_addr[] = {0x02, 0x65, 0x7A, 0x65, 0x71, 00};
static U8 packet[2000];


void console_test(){
	U8 aux8;
	U32 aux32; 
	U8 hasData; 
	U8 out_buffer[] = {0x35, 0x7a};
	U8 out_buffer2[] = {0x1E , 0xFF}; 
   console_init();
  while(1){
	/*console_printf("LPC2106: ENC28J60-H Ethernet\n");*/
	console_write_str("------------------|.oOo.|----------------------\n\0");
	console_write_char('S');
	console_write_char('E');
	console_write_char('2');
	console_write_char('\n');
	console_write_str("Nuno & Nuno\n\0");

  }
}

void main(){

  TIMER_init(pTIMER1,58982400/MICRO);
  TIMER_init(pTIMER0,58982400/MICRO);
  rtc_init();
  VIC_init();

  console_test();  
}

