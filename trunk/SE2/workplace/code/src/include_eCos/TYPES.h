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
#=====================================================================
*/
#ifndef TYPES_H
#define TYPES_H
#include <cyg/infra/cyg_type.h>

/**
 * Definição de tipos
 * */
typedef CYG_WORD32       U32;
typedef CYG_WORD16       U16;
typedef CYG_BYTE         U8;

typedef cyg_int32 S32;
typedef cyg_int16 S16;
typedef cyg_int8  S8;

typedef U32*    PU32;
typedef U16*   PU16;
typedef U8*    PU8;
typedef volatile void* PVOID;


typedef   U8    byte;
typedef   PU8   Pbyte;
typedef   PU16  PWord;
typedef   PU32  PDWord;

/**
 * @brief Date structure definition
 **/
typedef struct _date{
  U16    year; 
  U8     month;
  U8     day;  
}DATE;
/**
 * @brief Time structure definition 
 **/
typedef struct _time{
  U8     hour;
  U8     minute;
  U8     second;  
}TIME;


/**
 * @brief Date-Time structure definition
 **/
typedef struct _datetime{
  DATE date;
  TIME time;
}DATE_TIME;
#endif
