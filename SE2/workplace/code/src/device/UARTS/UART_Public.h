#ifndef UART_PUBLIC_H
#define SPI_H
#include "TYPES.h"
#include "LPC21XX.h"

typedef enum{
  U_RECEIVE_LINE_STATUS = 3,
  U_RECEIVE_DATA_AVAIABLE = 4,
  U_CHARACTER_TIME_OUT_INDICATOR = 6,
  U_THRE_INTERRUPT = 1,
  U_MODEM_INTERRUPT = 0
}UART_INTERRUPT_IDENTIFICATION;

typedef enum {
  U_TRIGGER_LEVEL_0 = 0,
  U_TRIGGER_LEVEL_1 = 1,
  U_TRIGGER_LEVEL_2 = 2,
  U_TRIGGER_LEVEL_3 = 3
}UART_RX_TRIGGER_LEVEL;

typedef enum {
  U_LENGTH_SELECT_5_BIT = 0,
  U_LENGTH_SELECT_6_BIT = 1,
  U_LENGTH_SELECT_7_BIT = 2,
  U_LENGTH_SELECT_8_BIT = 3
}UART_WORD_LENGTH_SELECT;

#define UART_WORD_LENGTH_SELECT_MIN     (0x0)
#define UART_WORD_LENGTH_SELECT_MAX     (0x3)

typedef enum {
  U_PARITY_SELECT_ODD = 0,
  U_PARITY_SELECT_EVEN = 1,
  U_PARITY_SELECT_FORCED_ONE = 2,
  U_PARITY_SELECT_FORCED_ZERO = 3
}UART_PARITY_SELECT;

#define UART_PARITY_SELECT_MIN        (0x0)
#define UART_PARITY_SELECT_MAX        (0x3)

typedef enum{
  UART_SUCCESS = 0,
  UART_INVALID_UART_ADDR,
  UART_INVALID_NUMBER_OF_BITS_TRANSMITION,
  UART_INVALID_PARITY_TRANSMITION,
  UART_NOT_INITIATED  
}UART_ERRORS;

typedef struct{
  pLPC_UART   uartAddr;
  U32         baudrate;
  U32         bits:2;               /* Should use UART_WORD_LENGTH_SELECT enum */
  U32         parity:2;             /* Should use UART_PARITY_SELECT enum */
  U32         stopbits:1;           /* 0 or 1 */
  U32         started:1;         /* should be initiaded with 0 */
}Uart,*pUart;


U32 UART_init(pUart uart);
U32 UART_write(pUart uart, const U8 *block, U32 size);
U32 UART_read(pUart uart,U8 *block, U32 size);

#endif
