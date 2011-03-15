#ifndef UART_H
#define UART_H
#include "TYPES.h"
#include "LPC21XX.h"


typedef struct _UART{
  union{                  /*Addr: 0xE000 C000*/
    U8    RBR;
    U8    THR;
    U8    DLL;
    U32   DUMMY01;        /* 32 bit alignment */
  };
  union{                  /*Addr: 0xE000 C004*/
    U8    DLM;
    U8    IER;
    U32   DUMMY02;        /* 32 bit alignment */
  };
  union{                  /*Addr: 0xE000 C008*/
    U8    IIR;
    U8    FCR;
    U32   DUMMY03;        /* 32 bit alignment */
  };
  U8      LCR ;           /*Addr: 0xE000 C00C*/
  U8      DUMMY04[3];
  U8      MCR;            /*Addr: 0xE000 C010*/ /*Avaiable in UART1*/
  U8      DUMMY05[3];          
  U8      LSR;            /*Addr: 0xE000 C014*/
  U8      DUMMY06[3];
  U8      MSR;            /*Addr: 0xE000 C018*/ /*Avaiable in UART1*/
  U8      DUMMY07[3];
  U8      SCR;            /*Addr: 0xE000 C01C*/
  U8      DUMMY08[3];
  U16     ACR;            /*Addr: 0xE000 C020*/
  U8      DUMMY09[2];
  U32     DUMMY10;        /*Addr: 0xE000 C024*/
  U8      FDR;            /*Addr: 0xE000 C028*/
  U8      DUMMY11[3];     
  U32     DUMMY12;        /*Addr: 0xE000 C02C*/
  U8      TER;            /*Addr: 0xE000 C030*/
  U8      DUMMY13[3];
}LPC_UART,*pLPC_UART;



#endif
