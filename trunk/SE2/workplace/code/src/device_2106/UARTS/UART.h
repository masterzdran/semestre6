#ifndef UART_H
#define UART_H
#include "TYPES.h"
#include "LPC21XX.h"
#include "startosc.h"



/*
 * Dividers:
 * D1 = PCLK / (16 * (256 *UnDLM + UnDLL))
 * D2 = D1 * 1 / (1 + DIVADDVAL/MULVAL)
 **/
 
 /*
  * Conditions:
  * The value of MULVAL and DIVADDVAL should comply to the following conditions:
  * 1. 0 < MULVAL ≤ 15
  * 2. 0 ≤ DIVADDVAL < 15
  * 3. DIVADDVAL<MULVAL
  * If DIVADDVAL is zero then the fractional divider is disabled, and the clock will not be divided.
  * */



/*
 Auto-Baud:
ratemin = (2 * PCLK)/(16 * 2^15) <= UART0baud <= (PCLK)/(16 * (2 + databits + paritybits +stopbits)) = ratemax
read page 94
**/
/**
 * @defgroup UART_CONFIG_MACRO
 * @{
 * */
#define DLL_MASK                        (0xFF)
#define __FDR_BAUD_RATE_DIVISOR_VALUE__         (0x0F)
#define __FDR_BAUD_RATE_MULTIPLIER_VALUE__      (0xF0)
#define __FDR_RESERVERD__        ~(0xFF)

#define __UIER_RBR_INTERRUPT__          (0x1 << 0)
#define __UIER_THRE_INTERRUPT__         (0x1 << 1)
#define __UIER_RX_INTERRUPT__           (0x1 << 2)
#define __UIER_U1_MODEM_STATUS_INTERRUPT_ENABLE__ (0x1 << 3)
#define __UIER_U0_RESERVED_INTERRUPT__    ~(0x307)
#define __UIER_U1_RESERVED_INTERRUPT__    ~(0x38F)
#define __UIER_U1_CTS_INTERRUPT_ENABLE__ (0x1 << 7)
#define __UIER_ABEOINTEN_INTERRUPT__    (0x1 << 8)
#define __UIER_ABTOINTEN_INTERRUPT__    (0x1 << 9)

#define __UIIR_INTERRUPT_PENDING__      (0x1 << 0)
#define __UIIR_INTERRUPT_ID__           (0x7 << 1)
#define __UIIR_RESERVED__               ~(0x3CF)
#define __UIIR_FIFO_ENABLE__            (0x3 << 6)
#define __UIIR_END_OF_AUTO_BAUD_INTERRUPT__                (0x1 << 8)
#define __UIIR_AUTO_BAUD_TIME_OUT_INTERRUPT__                (0x1 << 9)

/*Re-read page 88*/

#define __UFCR__FIFO_ENABLE__           (0x1 << 0)
#define __UFCR__RX_FIFO_RESET__         (0x1 << 1)
#define __UFCR__TX_FIFO_RESET__         (0x1 << 2)
#define __UFCR__RESERVED__              (0x7 << 3)
#define __UFCR__RX_TRIGGER_LEVEL__      (0x3 << 6)

#define __ULCR_WORD_LENGTH_SELECT__       (0x3)
#define __ULCR_STOP_BIT_SELECT__          (0x1 << 2)
#define __ULCR_PARITY_ENABLE__            (0x1 << 3)
#define __ULCR_PARITY_SELECT__            (0x3 << 4)
#define __ULCR_BREAK_CONTROL__            (0x1 << 6)
#define __ULCR_DIVISOR_LATCH_ACCESS_BIT__ (0x1 << 7)

#define __UMCR_DTR_CONTROL__              (0x1 << 0)
#define __UMCR_RTS_CONTROL__              (0x1 << 1)
#define __UMCR_RESERVED__                 ~(0xD3)
#define __UMCR_LOOPBACK_MODE_SELECTED__   (0x1 << 4)
#define __UMCR_RTS_ENABLE__               (0x1 << 6)
#define __UMCR_CTS_ENABLE__               (0x1 << 7)

#define __ULSR_RECEIVER_DATA_READY__      (0x1 << 0)
#define __ULSR_OVERRUN_ERROR__            (0x1 << 1)
#define __ULSR_PARITY_ERROR__             (0x1 << 2)
#define __ULSR_FRAMING_ERROR__            (0x1 << 3)
#define __ULSR_BREAK_INTERRUPT__          (0x1 << 4)
#define __ULSR_TRANSMITTER_HOLDING_REGISTER_EMPTY__          (0x1 << 5)
#define __ULSR_TRANSMITTER_EMPTY__         (0x1 << 6)
#define __ULSR_ERROR_IN_RX_FIFO__          (0x1 << 7)

#define __UMSR_DELTA_CTS__                  (0x1 << 0)
#define __UMSR_DELTA_DSR__                  (0x1 << 1)
#define __UMSR_TRAILING_EDGE_RI__           (0x1 << 2)
#define __UMSR_DELTA_DCD__                  (0x1 << 3)
#define __UMSR_CTS__                        (0x1 << 4)
#define __UMSR_DSR__                        (0x1 << 5)
#define __UMSR_RI__                         (0x1 << 6)
#define __UMSR_DCD__                        (0x1 << 7)

#define __UACR_START__                      (0x1 << 0)
#define __UACR_MODE__                       (0x1 << 1)
#define __UACR_AUTO_RESTART__               (0x1 << 2)
#define __UACR_RESERVED__                   ~(0x307)
#define __UACR_END_INTERRUPT_CLEAR__        (0x1 << 8)
#define __UACR_TIME_OUT_INTERRUPT_CLEAR__   (0x1 << 9)

#define __UTER_RESERVED__                   ~(0x1 << 7)
#define __UTER_TXEN__                   ~(0x1 << 7)

#define UART_STOP_BIT_SHIFT           (0x2)
#define UART_PARATY_CONFIG_SHIFT      (0x4)
#define  UART0_PISEL  (PINSEL0_UART_0_RXD|PINSEL0_UART_0_TXD)
#define  UART1_PISEL  (PINSEL0_UART_1_CTS|PINSEL0_UART_1_DCD|PINSEL0_UART_1_DSR|PINSEL0_UART_1_DTR|PINSEL0_UART_1_RI|PINSEL0_UART_1_RTS|PINSEL0_UART_1_RXD|PINSEL0_UART_1_TXD)

/*#define  DATA_CONFIG(A)  ((A)->bits | (A)->stopbits << UART_STOP_BIT_SHIFT | __ULCR_PARITY_ENABLE__ | (A)->parity << UART_PARATY_CONFIG_SHIFT)*/
#define  DATA_CONFIG(A)  ((A)->bits | (A)->stopbits << UART_STOP_BIT_SHIFT | (A)->parity << UART_PARATY_CONFIG_SHIFT)

#define  UART_RECEIVER_DATA_READY(A)                    ((A)->uartAddr->LSR & __ULSR_RECEIVER_DATA_READY__ )
#define  UART_LSR_OVERRUN_ERROR(A)                      ((A)->uartAddr->LSR & __ULSR_OVERRUN_ERROR__)
#define  ULSR_PARITY_ERROR(A)                           ((A)->uartAddr->LSR & __ULSR_PARITY_ERROR__)
#define  ULSR_FRAMING_ERROR(A)                          ((A)->uartAddr->LSR & __ULSR_FRAMING_ERROR__)
#define  ULSR_BREAK_INTERRUPT(A)                        ((A)->uartAddr->LSR & __ULSR_BREAK_INTERRUPT__)
#define  ULSR_TRANSMITTER_HOLDING_REGISTER_EMPTY(A)     ((A)->uartAddr->LSR & __ULSR_TRANSMITTER_HOLDING_REGISTER_EMPTY__)
#define  ULSR_TRANSMITTER_EMPTY(A)                      ((A)->uartAddr->LSR & __ULSR_TRANSMITTER_EMPTY__)
#define  ULSR_ERROR_IN_RX_FIFO(A)                       ((A)->uartAddr->LSR & __ULSR_ERROR_IN_RX_FIFO__)
/**
 * @}
 **/
#endif
