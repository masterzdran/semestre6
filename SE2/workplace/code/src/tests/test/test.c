#include <stdio.h>
#include <cyg/hal/hal_io.h>
#include <cyg/infra/diag.h>
/*
#include "GPIO.h"
#include "TIMER.h"
#include "RTC.h"
#include "TYPES.h"
#include "startosc.h"
#include "stdio.h"
#include "I2C.h"
//#include "VIC.h"
#include "WATCHDOG.h"
#include "SPI.h"
#include "console.h"
#include "Ethernet.h"
*/ 
/*
#define  LCD_MASK   ((U32) 0x7F00)

#define PACKET_SIZE 1516


static U8 ether_addr[] = {0x02, 0x6E, 0x75, 0x6E, 0x6F, 00};
static U8 packet[PACKET_SIZE];


void console_test(){
	
	U8 aux8;
	U32 aux32; 
	U8 hasData; 
	U8 out_buffer[] = {0x35, 0x7a};
	U8 out_buffer2[] = {0x1E , 0xFF}; 
	
   console_init();
  while(1){
	console_printf("LPC2106: ENC28J60-H Ethernet\n");
	console_write_str("------------------|.oOo.|----------------------\n\0");
	console_write_char('S');
	console_write_char('E');
	console_write_char('2');
	console_write_char('\n');
	console_write_str("Nuno & Nuno\n\0");

  }
}

void spi_test(){

  const void (*irqHandler)(void);	
  U32   clock;		     			
  U32   chipSelect;	  				
  U32   nbrbits:4;		  			
  U32   mode:2;			    		
  U32   role:1;			    		
  U32   started:1;      			
  U32   byteShift:1;    			
}SPI_Device,*pSPI_Device;
	
SPI_Device spis[]={ 
	 {
      0,									
      64,               					
      1<<8,             					
      8,                					
      SPI_PRIOR_TO_FIRST_SCK_RISING_EDGE,
      SPI_MASTER,    						
      0,                					
      SPI_MSB           					
	}
};
	
	U8 out_buffer[] = {0x35, 0x7a};
	U8 out_buffer2[] = {0x1E , 0xFF}; 
	U8 in_buffer[] = {0x00, 0x00};
	SPI_init(spis, 1);
	
	while(1){
		gpio_clear(1<<9);        
		gpio_set(1<<9);      

	
		SPI_start_device(&spis[0]);
		SPI_transfer(&spis[0], sizeof(out_buffer), out_buffer, in_buffer);
		SPI_transfer(&spis[0], sizeof(out_buffer2), out_buffer2, in_buffer);
		SPI_stop_device(&spis[0]);
		break;
  }
}

void enc_test(U8 receiveTest, U8 sendTest)
{
	ETHERNET_Device eth ={
	 {
      0,									
      16,               					  
      1<<8,             					
      8,                					
      SPI_PRIOR_TO_FIRST_SCK_RISING_EDGE,   
      SPI_MASTER,    						
      0,                					
      SPI_MSB           					
	},
	ETHERNET_FULL_DUPLEX,
	{0x02, 0x65, 0x7A, 0x65, 0x71, 00}
};
	U32 size;
	console_init();
	console_write_str("LPC2106: ENC28J60-H Ethernet\r\n\0");
	Ethernet_init(&eth);

	while (receiveTest) {
		Ethernet_receive(packet, PACKET_SIZE,&size);
		while ((size=Ethernet_receive(packet, PACKET_SIZE))) {
			Ethernet_receive(packet, PACKET_SIZE,&size);
			console_write_str("Packet received\r\n\0");
			console_dump_hex(packet, size);
		}
	}
	
	while (sendTest) {
		if (console_size() >= 0) {
			char c = console_read_char();
			console_printf("tx\n\r");
			U8 frame[78];
			memcpy(&frame[0], "\xff\xff\xff\xff\xff\xff", 6);
			memcpy(&frame[6], ether_addr, 6);
			frame[12] = (sizeof(frame) - 14) >> 8;
			frame[13] = (sizeof(frame) - 14);
			memset(&frame[14], '2', sizeof(frame) - 14);
			Ethernet_send(frame, sizeof(frame));
		}
	}

}

*/
int main(){
/*
	TIMER_init(pTIMER1,58982400/MICRO);
  TIMER_init(pTIMER0,58982400/MICRO);
	rtc_init();
  VIC_init();

  console_test();
  spi_test();
	enc_test(1,1);
*/
   printf("Hello World!");
	return 0;
}

