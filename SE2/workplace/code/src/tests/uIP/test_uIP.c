#include "test_uIP.h"

#include "GPIO.h"
#include "TYPES.h"
#include "Ethernet.h"
#include "LPC21XX.h"

#include <cyg/hal/hal_io.h>
#include <cyg/infra/diag.h>
#include <cyg/kernel/kapi.h>

#include "timer.h"
#include "uip.h"
#include "uip-conf.h"
#include "uip_arp.h"


#define PACKET_SIZE 1516
static U8 ether_addr[] = {0x02, 0x6E, 0x75, 0x6E, 0x6F, 00};
static U8 packet[PACKET_SIZE];


struct timer periodic_timer, arp_timer;

void uip_setup(){

	ETHERNET_Device eth ={
						NULL,
						ETHERNET_FULL_DUPLEX,
						{0x02, 0x6E, 0x75, 0x6E, 0x6F, 00}
						};

	uip_ipaddr_t ipaddr;
	timer_set(&periodic_timer, CLOCK_SECOND / 2);
	timer_set(&arp_timer, CLOCK_SECOND * 10);

	Ethernet_init(&eth);
	Ethernet_init(&eth);

	uip_init();

	//set mac address
	uip_setdraddr(ether_addr);
	//set ip address
	uip_ipaddr(ipaddr, 192,168,0,2);
	uip_sethostaddr(ipaddr);
	//set gateway address
	uip_ipaddr(ipaddr, 192,168,0,254);
	uip_setdraddr(ipaddr);
	//set subnet mask
	uip_ipaddr(ipaddr, 255, 255, 255, 0);
	uip_setnetmask(ipaddr);
}


#define BUF ((struct uip_eth_hdr *)uip_buf)

void uip_activity() {
	int i;
//	uip_len = Ethernet_receive(uip_buf, UIP_BUFSIZE, CLOCK_SECOND / 2);
	uip_len = Ethernet_receive(uip_buf, UIP_BUFSIZE);
	if (uip_len > 0) {
		if (BUF->type == HTONS(UIP_ETHTYPE_IP)) {
			uip_arp_ipin();
			uip_input();
			if (uip_len > 0) {
				uip_arp_out();
				Ethernet_send(uip_buf, uip_len);
			}
		}
		else if (BUF->type == HTONS(UIP_ETHTYPE_ARP)) {
			uip_arp_arpin();
			if (uip_len > 0) {
				//Ethernet_send(uip_buf, uip_len, 10);
				Ethernet_send(uip_buf, uip_len);
			}
		}
	} else if (timer_expired(&periodic_timer)) {
		timer_reset(&periodic_timer);
		for (i = 0; i < UIP_CONNS; i++) {
			uip_periodic(i);
			if (uip_len > 0) {
				uip_arp_out();
				Ethernet_send(uip_buf, uip_len);
			}
		}
		for (i = 0; i < UIP_UDP_CONNS; i++) {
			//uip_udp_periodic(i);
			if (uip_len > 0) {
				uip_arp_out();
				Ethernet_send(uip_buf, uip_len);
			}
		}
		if (timer_expired(&arp_timer)) {
			timer_reset(&arp_timer);
			uip_arp_timer();
		}
	}
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

static void main_application_init(){
		uip_listen(HTONS(1234));
}
void main_application(void){
	if (uip_newdata())
		uip_send(uip_appdata, uip_datalen());
}

int main(){

	diag_printf("Testing uip\n\r");
	gpio_init();
	//gpio_test();
	//enc_test(1,5,5);
	uip_setup();

	main_application_init();

	while(1){
		uip_activity();
	}
	return 0;
}



