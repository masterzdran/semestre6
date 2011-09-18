
#include <cyg/kernel/kapi.h>
#include <string.h>

#include "uip.h"
#include "uip_arp.h"
#include "tapdev.h"
#include "timer.h"
#include "uip-conf.h"
#include <stdio.h>

#include "TYPES.h"
#include "ENC28J60.h"
#include "Ethernet.h"

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

#ifndef NULL
#define NULL (void *)0
#endif /* NULL */

static struct uip_eth_addr ether_addr = {
  {0x02, 0x6E, 0x75, 0x6E, 0x6F, 00}
};
struct timer periodic_timer, arp_timer;

/*---------------------------------------------------------------------------*/
void uip_setup(){
  uip_ipaddr_t ipaddr;
  timer_set(&periodic_timer, CLOCK_SECOND / 2);
  timer_set(&arp_timer, CLOCK_SECOND * 10);

	diag_printf("Timers set. Tapdev_init starting...\n\r");
  tapdev_init();
	diag_printf("Tapdev_init ended. Starting uip_init...\n\r");
  uip_init();
	diag_printf("uip_init ended. Start set address...\n\r");

  uip_setethaddr(ether_addr);

  uip_ipaddr(ipaddr, 192,168,0,2);
  uip_sethostaddr(ipaddr);
  uip_ipaddr(ipaddr, 192,168,0,1);
  uip_setdraddr(ipaddr);
  uip_ipaddr(ipaddr, 255,255,255,0);
  uip_setnetmask(ipaddr);
	
}
/*---------------------------------------------------------------------------*/
void uip_activity(){
  int i;

  uip_len = Ethernet_receive(uip_buf, UIP_BUFSIZE);
  if (uip_len > 0) {
    if (BUF->type == htons(UIP_ETHTYPE_IP)) {
      uip_arp_ipin();
      uip_input();
			if (uip_len > 0) {
				uip_arp_out();
				//Ethernet_send(uip_buf, uip_len);
				tapdev_send();
			}
		}
		else if (BUF->type == htons(UIP_ETHTYPE_ARP)) {
			uip_arp_arpin();
			if (uip_len > 0) {
				//Ethernet_send(uip_buf, uip_len);
				tapdev_send();
			}
		}
	} else if (timer_expired(&periodic_timer)) {
		timer_reset(&periodic_timer);
		for (i = 0; i < UIP_CONNS; i++) {
			uip_periodic(i);
			if (uip_len > 0) {
				uip_arp_out();
				//Ethernet_send(uip_buf, uip_len);
				tapdev_send();
			}
		}
		for (i = 0; i < UIP_UDP_CONNS; i++) {
			//uip_udp_periodic(i);
			if (uip_len > 0) {
				uip_arp_out();
				//Ethernet_send(uip_buf, uip_len);
				tapdev_send();
			}
		}
		if (timer_expired(&arp_timer)) {
			timer_reset(&arp_timer);
			uip_arp_timer();
		}
	}
}
/*---------------------------------------------------------------------------*/
static void main_application_init() {
	diag_printf("uip_listen(");
	diag_printf("HTONS(1234)");
	diag_printf(")\n\r");
	uip_listen(HTONS(1234));
}
/*---------------------------------------------------------------------------*/
void main_application(void){
	if (uip_newdata())
		uip_send(uip_appdata, uip_datalen());
}
/*---------------------------------------------------------------------------*/
int main(void){
	diag_printf("Test uip\n\r");
	uip_setup();
	diag_printf("uip setup end.\n\r");

	main_application_init();
	diag_printf("main_app initialized\n\r");	
	
	while (1){
		uip_activity();
	}
}
/*---------------------------------------------------------------------------*/


