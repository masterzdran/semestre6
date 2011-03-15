/**
The following features and registers are available in LPC2104/01, LPC2105/01, and LPC2106/01 only:
  • Fractional baud rate controller: U0FDR (Table 9–82) / U1FDR (Table 10–99).
  • Auto-baud control: U0ACR (Table 9–91) / U1ACR (Table 10–111) and U0IIR/U0IER bits 9:8 (Table 9–84 and Table 9–85) / U1IIR/U1IER bits 9:8 (Table 10–101
and Table 10–102).
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