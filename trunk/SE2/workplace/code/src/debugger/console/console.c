/*
#=======================================================================
# SE1   - Sistemas Embebidos 1
#-----------------------------------------------------------------------
# Turma:	LI51N
# Semestre:	Inverno 2010/2011
# Data:		Novembro/2010
#-----------------------------------------------------------------------
# Nome: 	Nuno Cancelo
# Numero:	31401
#-----------------------------------------------------------------------
# Nome:		Nuno Sousa
# Numero:	33595
#-----------------------------------------------------------------------
# LEIC  - Licenciatura em Engenharia Informática e Computadores
# DEETC - Dep. de Eng. Electrónica e Telecomunicações e Computadores
# ISEL  - Instituto Superior de Engenharia de Lisboa
#=======================================================================
**/ 

#include "console.h"
#include "UART.h"
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

static Uart conUart;

#define LINE_BUFFER_SIZE 74
#define BUFFER_SIZE     256
#define READ_BUFFER     10

void console_dump_hex (U8 * buffer, size_t size) {
	U16 total = 0;
	char line[LINE_BUFFER_SIZE], * pl1, * pl2;
	U8 * p = buffer;
	U8 nBytes;
	
	while (size > 0) {
		int i;
		memset(line, ' ', LINE_BUFFER_SIZE - 1);
		pl1 = line;
		pl2 = line + 55;
		line[LINE_BUFFER_SIZE - 3] = '\n';
		line[LINE_BUFFER_SIZE - 2] = '\r';
		line[LINE_BUFFER_SIZE - 1] = '\0';
        
		pl1 += sprintf(pl1, "%04X: ", total);
		nBytes = (size<16)?size:16;
		for (i = 0; i < nBytes; ++i, ++p) {
			pl1 += sprintf(pl1, "%02X ", *p);
			*pl2++ = (isprint(*p) && *p != '\t' &&
				*p != '\r' && *p != '\n' && *p != '\xc') ? *p : '.';
		}
		*pl1 = ' ';
		console_write_block(line, sizeof(line));
		total += nBytes;
		size -= nBytes;
	}
}

int console_printf(const char * fmt, ...) {
	char buf[BUFFER_SIZE];
	va_list vlp;
	size_t r;
	va_start(vlp, fmt);
	if( (r = vsprintf(buf, fmt, vlp)) >= sizeof(BUFFER_SIZE) ){
		console_write_block("ERROR: vsprintf - insufficient buffer size!\r\n", 46);
    }

    console_write_block(buf,r);
	return r;
}

int console_vprintf(const char * fmt, va_list vlp) {
	char buf[BUFFER_SIZE];
	size_t r;
	if( (r = vsprintf(buf, fmt, vlp)) >= BUFFER_SIZE )
		console_write_block("ERROR: vsprintf - insufficient buffer size!\r\n", 46);
	console_write_block(buf, r);
	return r;
}

#include <_stdio.h>

static int scan_read_char(void * str, int ch) {
	static char buffer[READ_BUFFER];
	static int count = 0;
	if (ch == _WANT)
		if (count > 0)
			return buffer[--count];
		else
			return console_read_char();
	else if (ch >= 0)
		buffer[count++] = ch;
	return ch;
}

int console_scanf(const char *fmt, ...) {
	va_list vlp;
	va_start(vlp, fmt);
	return _scanf(scan_read_char, (void *) 0, fmt, vlp);
}

/*---------------------------------------------------------------------------*/

U32 console_write_block(const char* data, U32 size) {
	UART_write(&conUart, (U8*)data, size);
	return size;
}

void console_write_str(const char * str) {
	U32 size =(U32) strlen(str);
  	UART_write(&conUart, (U8*)str, size);
}

void console_write_char(const char c) {
	UART_write(&conUart, (U8*) (&c), 1);
}

char console_read_char() {
	char c; 
	UART_read(&conUart,(U8*)(&c),1);
	return c;
}

U32 console_read_block(char * buffer, U32 size) {
	return UART_read(&conUart, (U8*)buffer, size);
}

/* ***TO DO*** */

U8 console_size() {
	return UART_receiver_data_ready(&conUart);
}
/*
 *   pLPC_UART   uartAddr;
  U32         baudrate;
  U32         bits:2;            
  U32         parity:2;       
  U32         stopbits:1;      
  U32         started:1; 
 * */
void console_init() {

	conUart.uartAddr = pUART0; 
	conUart.baudrate=57600; 
	conUart.bits=U_LENGTH_SELECT_8_BIT; 
	conUart.parity=U_PARITY_SELECT_FORCED_ZERO; 
	conUart.stopbits=ONE_STOP_BIT; 
	conUart.started=0;
    
	UART_init(&conUart);
}

