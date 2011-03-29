#include "ENC28J60.h"
#include "SPI.h"
/* TABLE 4-1: SPI INSTRUCTION SET FOR THE ENC28J60 */
void ENC_read_control_register(U8 address);
void ENC_read_buffer_memory();
void ENC_write_control_register(U8 address, pU8 data, U16 size);
void ENC_write_buffer_memory(pU8 data, U16 size);
void ENC_bit_field_set(U8 address, pU8 data, U16 size);
void ENC_bit_field_clear(U8 address, pU8 data, U16 size);


void ENC_system_reset_command(){
    U8 dummyRx=0;
    U8 reset = __ENC_SYSTEM_RESET_COMMAND__;
    SPI_start_device(spi);
    SPI_transfer(spi,1, &reset, &dummyRx);
    SPI_stop_device(spi);
}


