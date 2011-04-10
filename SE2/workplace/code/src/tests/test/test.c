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

/*
static U8 ether_addr[] = {0x02, 0x65, 0x7A, 0x65, 0x71, 00};
static U8 packet[2000];
*/


int main(){
	/* U32 aux32; */
	U8 aux8;
	/* U8 hasData; */
  SPI_Device spis[1]= {
    {
      0,
      10,   		/*clock divider */
      1<<8,    		/*id do periferico = GPIO pin 8*/
      8,    		/*num bits palavra*/
      SPI_PRIOR_TO_FIRST_SCK_RISING_EDGE,    /*mode*/
      SPI_MASTER,    /*role = master*/
      0,    		/*not started yet*/
      SPI_MSB     	/*byte shitf ??*/
    }
  };
  

  TIMER_init(pTIMER1,58982400/MICRO);
  TIMER_init(pTIMER0,58982400/MICRO);
  rtc_init();
  VIC_init();
  console_init();

  
  /*
  VIC_ConfigIRQ(__INTERRUPT_TIMER0__,1,timer0isr);
  WATCHDOG_init(0x0FFFFFFF);  
  interrupt_enable(); 
  */


  
  SPI_init(spis, 1);
  
 
  while(1){
	  
/*    U8 out_buffer[] = {0x35, 0x7a};
	U8 out_buffer2[] = {0x1E , 0xFF}; 
	enviar 0x1E ncomo primeiro byte e depois dummy para receber o 0x80
    U8 in_buffer[sizeof(out_buffer)];
    SPI_start_device(&spis[0]);
    SPI_transfer(&spis[0], sizeof(out_buffer), out_buffer, in_buffer);
	gpio_clear(0x100);	
	activar RST do ENC
	SPI_transfer(&spis[0], sizeof(out_buffer2), out_buffer2, in_buffer);
    SPI_stop_device(&spis[0]);
*/
/*	console_printf("LPC2106: ENC28J60-H Ethernet\n\r");
	console_write_char('S');
	console_write_char('E');
	console_write_char('2');
	console_write_char('\n');
	aux32 = console_write_block("SE2\n",4);
	console_printf(" -> %d",(int)aux32);
	console_write_str("Nuno & Nuno");
	console_write_char(console_read_char());
	aux32 = console_read_block(packet, 10);
	hasData = console_size();
	console_write_block(packet, aux32);
	aux8 = (U8) console_read_char();

	console_dump_hex(packet, sizeof(packet));
*/
	aux8 = (U8) console_read_char();
	console_write_char((char) aux8);

  
  }
}

