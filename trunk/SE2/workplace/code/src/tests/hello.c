#include <stdio.h>
#include "GPIO.h"
#include "TIMER.h"
#include "TYPES.h"
#include "Ethernet.h"

#include "LPC21XX.h"
#include <cyg/hal/hal_io.h>
#include <cyg/infra/diag.h>

#define PACKET_SIZE 1516
static U8 ether_addr[] = {0x02, 0x6E, 0x75, 0x6E, 0x6F, 00};
static U8 packet[PACKET_SIZE];


void enc_test(U8 encTest, U8 receiveTest, U8 sendTest)
{
	ETHERNET_Device eth ={
	NULL,
	ETHERNET_FULL_DUPLEX,
	ether_addr
	};

	int i=1;

	while(i)
	diag_printf("LPC2106: ENC28J60-H Ethernet\r\n");

	Ethernet_init(&eth);

	U8 test_result;
	while (encTest--)
		test_result = ENC_test();

	U32 size;
	while (receiveTest--) {
		/*Ethernet_receive(packet, PACKET_SIZE,&size);*/
		while ((size=Ethernet_receive(packet, PACKET_SIZE))) {
			/*Ethernet_receive(packet, PACKET_SIZE,&size);*/
			/*printf("Packet received\r\n\0");
			packet[size]=0;
			printf("%s",packet);*/
			/*echo received packet*/
			diag_printf(packet);
			//Ethernet_send(packet, size);
		}
	}
	char c;
	while (sendTest--) {
		if (1) {
			printf("tx\n\r");
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

static void enc28j60_cs(int select) {
	if (select)
		GPIO_CLEAR(CS_PIN);
	else
		GPIO_SET(CS_PIN);
}

static void spi_enc28j60_cs(int select, int pin) {
	if (select)
		HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE +
				CYGARC_HAL_LPC2XXX_REG_IOCLR, pin);
	else
		HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE +
				CYGARC_HAL_LPC2XXX_REG_IOSET, pin);
}

void gpio_test(){
	/*
	enc28j60_cs(0);
	enc28j60_cs(1);
	enc28j60_cs(0);
	enc28j60_cs(1);
*/

	spi_enc28j60_cs(1, CS_PIN);
	spi_enc28j60_cs(0, CS_PIN);

	spi_enc28j60_cs(1, RESET);
	spi_enc28j60_cs(0, RESET);

}

void gpio_init(){
	cyg_uint32 iodir;
	/*activate gpio for CS, Reset*/
	GPIO_INIT_PINSEL0((CS_PIN | RESET));

	/*set dir to output for CS and Reset*/
	HAL_READ_UINT32((pGPIO)->IODIR, iodir);
	iodir = iodir | (CS_PIN | RESET);
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE+CYGARC_HAL_LPC2XXX_REG_IODIR, iodir);

	/*CS OFF & RESET OFF*/
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IOSET, CS_PIN);
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IOSET, RESET);

}
int main(){
/*
	TIMER_init(pTIMER1,58982400/MICRO);
  TIMER_init(pTIMER0,58982400/MICRO);
	rtc_init();
  VIC_init();
*/

	gpio_init();
	gpio_test();
	enc_test(1,5,5);
	return 0;

}


