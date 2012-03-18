#include <cyg/hal/hal_arch.h>		/* For stack size */
#include <cyg/kernel/kapi.h>		/* Kernel API */
#include <cyg/infra/diag.h>			/* For diagnostic printing */

#define THREAD_STACK_SIZE			CYGNUM_HAL_STACK_SIZE_TYPICAL
#define THREAD_PRIORITY			12

int thread_stack[THREAD_STACK_SIZE];

cyg_thread thread_obj;

cyg_handle_t thread_hdl;

void thread(cyg_addrword_t data) {
	diag_printf("thread starting(%d)\n", data);
	while ( 1 ) {
		diag_printf("thread running(%d)\n", data);
	}
}

void cyg_user_start( void ) {

	diag_printf("Hello eCos World!!!\n\n");

	cyg_thread_create(THREAD_PRIORITY, thread, (cyg_addrword_t) 75,
		"Thread name", (void *)thread_stack, THREAD_STACK_SIZE,
		&thread_hdl, &thread_obj);

	cyg_thread_resume (thread_hdl);
}
