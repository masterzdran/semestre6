#include "uip.h"
#include "uip_arp.h"
#include "timer.h"

#include "ethernet.h"

static struct uip_eth_addr ether_addr = {
	{0x02, 0x65, 0x7A, 0x65, 0x71, 00}
};

static struct timer periodic_timer, arp_timer;

void uip_setup(void) {
	uip_ipaddr_t ipaddr;

	timer_set(&periodic_timer, CLOCK_SECOND / 2);
	timer_set(&arp_timer, CLOCK_SECOND * 10);

	ethernet_init(ether_addr.addr);

	uip_init();
	uip_setethaddr(ether_addr);

	uip_ipaddr(ipaddr, 1, 1, 1,30);
	uip_sethostaddr(ipaddr);
	
	uip_ipaddr(ipaddr, 1,1,1,1);
	uip_setdraddr(ipaddr);

	uip_ipaddr(ipaddr, 255,255,255,0);
	uip_setnetmask(ipaddr);
}

#define ETHER ((struct uip_eth_hdr *)&uip_buf[0])

void uip_activity(void) {
	int i;
	uip_len = ethernet_recv(uip_buf, UIP_BUFSIZE, CLOCK_SECOND / 2);
	if (uip_len > 0) {
		if (ETHER->type == htons(UIP_ETHTYPE_IP)) {
			uip_arp_ipin();
			uip_input();
			/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
			if (uip_len > 0) {
				uip_arp_out();
				ethernet_send(uip_buf, uip_len, 10);
			}
		}
		else if (ETHER->type == htons(UIP_ETHTYPE_ARP)) {
			uip_arp_arpin();
			/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
			if (uip_len > 0) {
				ethernet_send(uip_buf, uip_len, 10);
			}
		}
	} else if (timer_expired(&periodic_timer)) {
		timer_reset(&periodic_timer);
		for (i = 0; i < UIP_CONNS; i++) {
			uip_periodic(i);
			/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
			if (uip_len > 0) {
				uip_arp_out();
				ethernet_send(uip_buf, uip_len, 10);
			}
		}

#if UIP_UDP
		for (i = 0; i < UIP_UDP_CONNS; i++) {
			uip_udp_periodic(i);
			/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
			if (uip_len > 0) {
				uip_arp_out();
				ethernet_send(uip_buf, uip_len);
			}
		}
#endif /* UIP_UDP */

		/* Call the ARP timer function every 10 seconds. */
		if (timer_expired(&arp_timer)) {
			timer_reset(&arp_timer);
			uip_arp_timer();
		}
	}
}

/*------------------------------------------------------------------------------
	Log
*/
#include <cyg/infra/diag.h>

void uip_log(char *m) {
  diag_printf("uIP log message: %s\n", m);
}

/*------------------------------------------------------------------------------
	Temporizações
*/
#include <cyg/kernel/kapi.h>

clock_time_t clock_time(void) {
    return cyg_current_time();
}

