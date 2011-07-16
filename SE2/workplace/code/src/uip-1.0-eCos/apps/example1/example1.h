#ifndef EXAMPLE1_H
#define EXAMPLE1_H

#include "uipopt.h"

void example1_app(void);

struct example1_state {
  u8_t state;
};

typedef struct example1_state uip_tcp_appstate_t;

#ifndef UIP_APPCALL
#define UIP_APPCALL     example1_app
#endif

#endif
