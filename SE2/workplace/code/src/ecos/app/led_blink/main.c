/*	Instituto Superior de Engenharia de Lisboa
	Ezequiel Conde, 2011

 	Aplicação de teste do eCos - pisca um led ligado num pino do GPIO.
 */
#include <stdio.h>
#include <cyg/kernel/kapi.h>
#include <cyg/hal/hal_arch.h>	// For stack size
#include <cyg/hal/hal_io.h>		// HAL_WRITE_U32

void light_on(int led) {
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE +
		CYGARC_HAL_LPC2XXX_REG_IOSET, 1 << led);
}

void light_off(int led) {
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE +
		CYGARC_HAL_LPC2XXX_REG_IOCLR, 1 << led);
}

void light_thread(cyg_addrword_t led) {
	int light_state = 0;
	while(1) {
		cyg_thread_delay(CYGNUM_HAL_RTC_DENOMINATOR * 1);
		if (light_state)
			light_off(led);
		else
			light_on(led);
		light_state = ! light_state;
	}
}

static char light_stack[CYGNUM_HAL_STACK_SIZE_TYPICAL];
static cyg_thread light_desc;
static cyg_handle_t light_handle;

void light_init(int led) {
	int aux;
	HAL_READ_UINT32(CYGARC_HAL_LPC2XXX_REG_PIN_BASE +
		CYGARC_HAL_LPC2XXX_REG_PINSEL0, aux);
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_PIN_BASE +
		CYGARC_HAL_LPC2XXX_REG_PINSEL0, aux & ~(3 << (led * 2)));
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE +
		CYGARC_HAL_LPC2XXX_REG_IODIR, 1 << led );
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE +
		CYGARC_HAL_LPC2XXX_REG_IOSET, 1 << led );

	cyg_thread_create(4, light_thread, (cyg_addrword_t) led, "Light thread",
		(void *)light_stack, sizeof(light_stack),
		&light_handle, &light_desc );

	cyg_thread_resume( light_handle );
}

void cyg_user_start(void) {
	light_init(4);
}

