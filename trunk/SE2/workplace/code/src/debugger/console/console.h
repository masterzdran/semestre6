#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdarg.h>
#include <string.h>
#include "TYPES.h"
#include "LPC21XX.h"

void console_init();

void console_write_char(char c);
U32 console_write_block(const char * data, U32 size);
void console_write_str(const char * str);

int console_printf(const char * fmt, ...);
int console_vprintf(const char * fmt, va_list vlp);
void console_dump_hex(U8 * buffer, size_t size);

char console_read_char();
U32 console_read_block(char * buffer, U32 size);
int console_scanf(const char *fmt, ...);

U8 console_size();

#endif