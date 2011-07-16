#include "uip.h"

void example1_init() {
	uip_listen(HTONS(1234));
}

void example1_app(void) {
	if (uip_newdata() || uip_rexmit()) {
		uip_send("ok\n", 3);
	}
}
