#include <cyg/kernel/kapi.h>
#include <string.h>
#include "timer.h"
#include "uip-conf.h"

#include "uip_arp.h"
#include "uip.h"
#include "Ethernet.h"
#include <time.h>
#include <stdio.h>
#include <cyg/hal/hal_arch.h>	// For stack size
#include <cyg/infra/diag.h>		// For diagnostic printing.
#include "TYPES.h"
struct timer periodic_timer, arp_timer;
void uip_setup() ;
void uip_activity() ;



static void main_application_init() {
uip_listen(HTONS(1234));
}
void main_application(void) {
	if (uip_newdata())
		uip_send(uip_appdata, uip_datalen());
}

static struct uip_eth_addr ether_addr = { {0x02, 0x65, 0x7A, 0x65, 0x71, 00} };

int main(void) {
diag_printf("Test uip\n\r");
uip_setup();
main_application_init();
while (1)
uip_activity();
}


void uip_setup() {
	uip_ipaddr_t ipaddr;
	timer_set(&periodic_timer, CLOCK_SECOND / 2);
	timer_set(&arp_timer, CLOCK_SECOND * 10);
	Ethernet_init(ether_addr.addr);
	uip_init();
	uip_setethaddr(ether_addr);
	uip_ipaddr(ipaddr, 10,0,0,4);
	uip_sethostaddr(ipaddr);
	uip_ipaddr(ipaddr, 10,0,0,0);
	uip_setdraddr(ipaddr);
	uip_ipaddr(ipaddr, 255,255,255,0);
	uip_setnetmask(ipaddr);
}

#define BUF ((struct uip_eth_hdr *)uip_buf)

void uip_activity() {
	int i;
	/* uip_len = Ethernet_receive(uip_buf, UIP_BUFSIZE, CLOCK_SECOND / 2); */
	uip_len = Ethernet_receive(uip_buf, UIP_BUFSIZE);
	if (uip_len > 0) {
		if (BUF->type == htons(UIP_ETHTYPE_IP)) {
			uip_arp_ipin();
			uip_input();
			if (uip_len > 0) {
				uip_arp_out();
				Ethernet_send(uip_buf, uip_len);
			}
		}
		else if (BUF->type == htons(UIP_ETHTYPE_ARP)) {
			uip_arp_arpin();
			if (uip_len > 0) {
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
			uip_udp_periodic(i);
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





#define uip_newdata() (uip_flags & UIP_NEWDATA)

void uip_send(const void * data, int size) {



}
