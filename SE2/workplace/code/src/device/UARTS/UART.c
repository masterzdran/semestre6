#include "UART.h"
#include "UART_Public.h"
#include "POWER.h"
#include "GPIO.h"
/**
The following features and registers are available in LPC2104/01, LPC2105/01, and LPC2106/01 only:
  • Fractional baud rate controller: U0FDR (Table 9–82) / U1FDR (Table 10–99).
  • Auto-baud control: U0ACR (Table 9–91) / U1ACR (Table 10–111) and U0IIR/U0IER 
    bits 9:8 (Table 9–84 and Table 9–85) / U1IIR/U1IER bits 9:8 (Table 10–101 and Table 10–102).
  • Software flow control: U0TER (Table 9–92) / U1TER (Table 10–112).
*/
/**
  Basic configuration
  The UART0 peripheral is configured using the following registers:
  1. Power: In the PCONP register (Table 3–27), set bit PCUART0.
      Remark: On reset, UART0 is enabled (PCUART0 = 1).
      Remark: On reset, UART1 is enabled (PCUART1 = 1).
  2. Baud rate: In register U0LCR (Table 9–88), set bit DLAB =1. This enables access to
    registers DLL (Table 9–80) and DLM (Table 9–81) for setting the baud rate. Also, if
    needed, set the fractional baud rate in the fractional divider register (Table 9–82).
    -------
    Baud rate: In register U1LCR (Table 10–105), set bit DLAB =1. This enables access
    to registers DLL (Table 10–97) and DLM (Table 10–98) for setting the baud rate. Also,
    if needed, set the fractional baud rate in the fractional divider register (Table 10–99). 
  
  3. UART FIFO: Use bit FIFO enable (bit 0) in register U0FCR (Table 9–87) to enable   FIFO.
     ------
     UART FIFO: Use bit FIFO enable (bit 0) in register U1FCR (Table 10–104) to enable FIFO.
  4. Pins: Select UART pins in registers PINSEL0/1 (see Section 7–2).
  5. Interrupts: To enable UART interrupts set bit DLAB =0 in register U0LCR
    (Table 9–88). This enables access to U0IER (Table 9–84). Interrupts are enabled in
    the VIC using the VICIntEnable register (Table 5–43).
    -----
    Interrupts: To enable UART interrupts set bit DLAB =0 in register U1LCR
    (Table 10–105). This enables access to U1IER (Table 10–101). Interrupts are enabled
    in the VIC using the VICIntEnable register (Table 5–43).
*/
/**
The Divisor Latch Access
Bit (DLAB) is contained in U0LCR[7] and enables access to the Divisor Latches.
The divisor latches are used to determine the baud rate for all UART transfers. When
setting up the part, follow these steps:
1. Set DLAB = 1 in U0LCR (Section 9–5.8).
2. Set baud rate by writing values to registers DLL and DLM at address 0xE000 C000
Section 9–5.3).
3. Set DLAB = 0 in U0LCR (Section 9–5.8).
4. Read at address 0xE000 C000 accesses the U0RBR register (Section 9–5.1).
5. Write at address 0xE000 C000 accesses the U0THR register (Section 9–5.2).
*/
static U32 periphericalClock;

U32 UART_init(pUart uart){
  U32 poweron = 0;
  U32 pinsel = 0;
  U32 clock = 0;
  
  if (uart->uartAddr != pUART0 && uart->uartAddr != pUART1){
    return UART_INVALID_UART_ADDR;
  }
  if(!(uart->bits >= UART_WORD_LENGTH_SELECT_MIN && uart->bits <= UART_WORD_LENGTH_SELECT_MAX)){
    return UART_INVALID_NUMBER_OF_BITS_TRANSMITION;
  }
  if(!(uart->bits >= UART_PARITY_SELECT_MIN && uart->bits <= UART_PARITY_SELECT_MAX)){
    return UART_INVALID_PARITY_TRANSMITION;
  }
  /* Obter o clock dos periféricos */
  periphericalClock = getPeriphericalClock();
  clock = periphericalClock /(16 * (uart->baudrate));
  
  if (uart->uartAddr == pUART0){
    poweron = __PCUART0_ENABLE__;
    pinsel =  UART0_PISEL;   
  }else{
    poweron =  __PCUART1_ENABLE__;
    pinsel =   UART1_PISEL;    
  }

  /*1. Power: In the PCONP register (Table 3–27), set bit PCUART.*/
  pPOWER->POWER_CONTROL_PERIPHERICAL |= poweron;

  /*2. Baud rate: In register U0LCR (Table 9–88), set bit DLAB =1.*/
  uart->uartAddr->LCR = __ULCR_DIVISOR_LATCH_ACCESS_BIT__; /*Reset all values and set DLAB*/
  uart->uartAddr->U1.DLL = clock & DLL_MASK;
  uart->uartAddr->U2.DLM = (clock >> 8) & DLL_MASK;
  
  /*3. UART FIFO: Use bit FIFO enable (bit 0) in register U0FCR (Table 9–87) to enable   FIFO.*/
  uart->uartAddr->U3.FCR = __UFCR__FIFO_ENABLE__;
  
  /*Setting data configuration*/
  uart->uartAddr->LCR |= DATA_CONFIG(uart);

  /*4. Pins: Select UART pins in registers PINSEL0/1 (see Section 7–2).*/
  gpio_init_PINSEL0(pinsel);
  
  /*5. Interrupts: To enable UART interrupts set bit DLAB =0 in register U0LCR*/
  uart->uartAddr->LCR &= ~(__ULCR_DIVISOR_LATCH_ACCESS_BIT__);
  uart->started = 1;
  return UART_SUCCESS;
}

U32 UART_write(pUart uart, const U8 *block, U32 size){
  if(!uart->started){ return UART_NOT_INITIATED;}
  
  for (;size;size--,block++){
    while(!(ULSR_TRANSMITTER_EMPTY(uart)));
    uart->uartAddr->U1.THR = *block;
  }
  return UART_SUCCESS;
}

U32 UART_read(pUart uart,U8 *block, U32 size){
  if(!uart->started){ return UART_NOT_INITIATED;}
  
  for (;size;size--,block++){
    while(!(ULSR_TRANSMITTER_EMPTY(uart)));
    *block = uart->uartAddr->U1.RBR;
  }
  return UART_SUCCESS;  
}
