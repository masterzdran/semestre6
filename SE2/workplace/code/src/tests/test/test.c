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
#include "Ethernet.h"
#define  LCD_MASK   ((U32) 0x7F00)

#define PACKET_SIZE 1516


static U8 ether_addr[] = {0x02, 0x65, 0x7A, 0x65, 0x71, 00};
static U8 packet[PACKET_SIZE];


void console_test(){
	/*
	U8 aux8;
	U32 aux32; 
	U8 hasData; 
	U8 out_buffer[] = {0x35, 0x7a};
	U8 out_buffer2[] = {0x1E , 0xFF}; 
	*/
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

void spi_test(){
/*
  const void (*irqHandler)(void);	
  U32   clock;		     			
  U32   chipSelect;	  				
  U32   nbrbits:4;		  			
  U32   mode:2;			    		
  U32   role:1;			    		
  U32   started:1;      			
  U32   byteShift:1;    			
}SPI_Device,*pSPI_Device;
*/	
	
SPI_Device spis[]={ 
	 {
      0,									/*função de tratamento de interrupções*/
      10,               					/*ritmo do sinal de relógio*/  
      1<<8,             					/*define a identificação do periférico: BITMAP*/
      8,                					/*número de bits de uma palavra*/
      SPI_PRIOR_TO_FIRST_SCK_RISING_EDGE,   /*modo SPI (CPHA, CPOL). do tipo SPI_MODE*/
      SPI_MASTER,    						/*qual o papel do periferico: 1- Master; 0- Slave SPI_ROLE*/
      0,                					/*indicação se o periférico foi préviamente iniciada. Por omissão o mesmo deve estar a 0. Não se garante o comportamento caso na construção se coloque a 1.*/
      SPI_MSB           					/*SPI_BYTE_SHIFT*/
	}
};
	
	SPI_init(spis, 1);
	while(1){
		U8 out_buffer[] = {0x35, 0x7a};
        U8 out_buffer2[] = {0x1E , 0xFF}; /*enviar 0x1E ncomo primeiro byte e depois dummy para receber o 0x80*/
		U8 in_buffer[sizeof(out_buffer)];
		SPI_start_device(&spis[0]);
		SPI_transfer(&spis[0], sizeof(out_buffer), out_buffer, in_buffer);
        gpio_clear(0x100);      /*activar RST do ENC*/
        SPI_transfer(&spis[0], sizeof(out_buffer2), out_buffer2, in_buffer);
		SPI_stop_device(&spis[0]);
  }
}

void enc_test()
{
	ETHERNET_Device eth ={
	 {
      0,									
      10,               					  
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
	
	while (1) {
		Ethernet_receive(packet, PACKET_SIZE,&size);
		while (size ) {
			Ethernet_receive(packet, PACKET_SIZE,&size);
			console_write_str("Packet received\r\n\0");
			console_dump_hex(packet, size);
		}
	}
}

int main(){

  TIMER_init(pTIMER1,58982400/MICRO);
  TIMER_init(pTIMER0,58982400/MICRO);
  rtc_init();
  VIC_init();

  /* console_test();  */
  /* spi_test(); */
	enc_test();
	return 0;
}

