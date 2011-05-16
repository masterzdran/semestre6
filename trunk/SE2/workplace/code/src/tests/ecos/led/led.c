#include <cyg/kernel/kapi.h> 
#include <cyg/hal/hal_io.h> //  HAL_WRITE... 
#include <cyg/hal/hal_diag.h> //  HAL_DELAY_US 
#include "chrono.h" 
#define BUZZER_PIN 15 
#define LPC2XXX_PINSEL0_GPIO(p) (~(3 << ((p) << 1))) 


void buzzer_init() { 
	/* programar a direcção */ 
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IOCLR,1 << BUZZER_PIN); 
	cyg_uint32 iodir; 
	HAL_READ_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IODIR, iodir); 
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IODIR, iodir | 1 << BUZZER_PIN); 
	
	/* switch pins to GPIO */ 
	cyg_uint32 pinsel; 
	HAL_READ_UINT32(CYGARC_HAL_LPC2XXX_REG_PIN_BASE + 	CYGARC_HAL_LPC2XXX_REG_PINSEL0, pinsel); 
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_PIN_BASE + 	CYGARC_HAL_LPC2XXX_REG_PINSEL0, pinsel & LPC2XXX_PINSEL0_GPIO(BUZZER_PIN)); 
} 



void buzzer_on(int on, int frequency) { 
	int half_period = 1000000 / frequency / 2; 
	cyg_uint32 initial = chrono_start(), duration = msec2tic(on); 
	// while (chrono_elapsed(initial) < msec2tic(on)) { 
	while (chrono_elapsed(initial) < duration) { 
		HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IOSET, 1 << BUZZER_PIN); 
		HAL_DELAY_US(half_period) ;
		HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IOCLR, 1 << BUZZER_PIN); 
		HAL_DELAY_US(half_period);
	} 
} 
void buzzer_off(int off) { 
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IOCLR, 1 << BUZZER_PIN); 
	cyg_thread_delay(msec2tic(off)); 
}     

void buzzer_sequence(int n, int on, int off, int frequency) { 
	;
} 
int main() { 
    buzzer_init(); 
    buzzer_on(4000, 1000); 
    buzzer_off(4000); 
    buzzer_sequence(6, 100, 500, 1000); 
} 