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
#ifndef RTC_H
#define RTC_H
#include "TYPES.h"
#include "LPC21XX.h"
#include "SCB.h"
#include <pkgconf/hal_arm_lpc2xxx_p2106.h>


/**
 * @brief Definition of the RTC structure
 * */
typedef struct _RTC{
                      /*SIZE|Description                  |Address    */
    U8     ILR;       /*  02|Interrupt Location Register  |0xE002 4000*/
    U8     DUMMY01[3];
    /*----------------------------------------------------------------*/
    U16    CTC;       /*  15|Clock Tick Counter           |0xE002 4004*/
    U16    DUMMY03;
    /*----------------------------------------------------------------*/
    U8     CCR;       /*  04|Clock Control Register       |0xE002 4008*/
    U8     DUMMY04[3];
    /*----------------------------------------------------------------*/
    U8     CIIR;      /*  08|Counter Increment Interrupt Register|0xE002 400C*/
    U8     DUMMY06[3];
    /*----------------------------------------------------------------*/
    U8     AMR;       /*  08|Alarm Mask Register          |0xE002 4010*/
    U8     DUMMY08[3];
    /*----------------------------------------------------------------*/
    U32    CTIME0;    /*  32|Consolidated Time Register 0 |0xE002 4014*/
    U32    CTIME1;    /*  32|Consolidated Time Register 1 |0xE002 4018*/
    U32    CTIME2;    /*  32|Consolidated Time Register 2 |0xE002 401C*/
    /*----------------------------------------------------------------*/
    U8     SEC;       /*  06|Seconds Counter              |0xE002 4020*/
    U8     DUMMY10[3];
    /*----------------------------------------------------------------*/
    U8     MIN;       /*  06|Minutes Register             |0xE002 4024*/
    U8     DUMMY12[3];
    /*----------------------------------------------------------------*/
    U8     HOUR;      /*  05|Hours Register               |0xE002 4028*/
    U8     DUMMY14[3];
    /*----------------------------------------------------------------*/
    U8     DOM;       /*  05|Day of Month Register        |0xE002 402C*/
    U8     DUMMY16[3];
    /*----------------------------------------------------------------*/
    U8     DOW;       /*  03|Day of Week Register         |0xE002 4030*/
    U8     DUMMY18[3];
    /*----------------------------------------------------------------*/
    U16    DOY;       /*  09|Day of Year Register         |0xE002 4034*/
    U16    DUMMY20;
    /*----------------------------------------------------------------*/
    U8     MONTH;     /*  04|Months Register              |0xE002 4038*/
    U8     DUMMY21[3];
    /*----------------------------------------------------------------*/
    U16    YEAR;      /*  12|Years Register               |0xE002 403C*/
    U16    DUMMY23;  
    /*----------------------------------------------------------------*/
    U32	   DUMMY24[8];
    /*----------------------------------------------------------------*/
    U8     ALSEC;     /*  06|Alarm value for Seconds      |0xE002 4060*/
    U8     DUMMY32[3];
    /*----------------------------------------------------------------*/    
    U8     ALMIN;     /*  06|Alarm value for Minutes     |0xE002 4064*/
    U8     DUMMY34[3];
    /*----------------------------------------------------------------*/
    U8     ALHOUR;    /*  05|Alarm value for Hours       |0xE002 4068*/
    U8     DUMMY36[3];
    /*----------------------------------------------------------------*/
    U8     ALDOM;     /*  05|Alarm value for Day of Month|0xE002 406C*/
    U8     DUMMY38[3];
    /*----------------------------------------------------------------*/
    U8     ALDOW;     /*  03|Alarm value for Day of Week |0xE002 4070*/
    U8     DUMMY40[3];
    /*----------------------------------------------------------------*/
    U16    ALDOY;     /*  09|Alarm value for Day of Year |0xE002 4074*/
    U16    DUMMY42;
    /*----------------------------------------------------------------*/
    U8     ALMON;     /*  04|Alarm value for Months      |0xE002 4078*/
    U8     DUMMY43[3];
    /*----------------------------------------------------------------*/
    U16    ALYEAR;    /*  12|Alarm value for Year        |0xE002 407C*/
    U16    DUMMY45;
    /*----------------------------------------------------------------*/
    U16    PREINT;    /*  13|Prescaler value, integer portion|0xE002 4080*/
    U16    DUMMY46;
    /*----------------------------------------------------------------*/
    U16    PREFRAC;   /*  15|Prescaler value, integer portion|0xE002 4084*/
    U16    DUMMY47;
    /*----------------------------------------------------------------*/
}LPC_RTC,*pLPC_RTC;


/**
 * @defgroup RTC_CONFIG_MACROS
 * @{
 */
#define		__MINUTES_IN_DAY__  1440
#define		__SECONDS_IN_HOUR__	3600
#define		__SECONDS_IN_DAY__	86400

#define PCRTC     0x200
#define __ILR_RTCCIF_DISABLE__     0x0
#define __ILR_RTCCIF_CLEAR__       0x1
#define __ILR_RTCALF_DISABLE__     0x0
#define __ILR_RTCALF_CLEAR__       0x2
#define __CCR_CLKEN_DISABLE__      0x0
#define __CCR_CLKEN_ENABLE__       0x1
#define __CCR_CTCRST_ENABLE__      0x2
#define __CCR_CTCRST_DISABLE__     0x0
#define __CCR_CTTEST__             0x3
/*
#define LPC_PREINT      ((__SYSTEM_CLOCK__ / 32768) - 1)
#define LPC_PREFRAC     (__SYSTEM_CLOCK__ - (((__SYSTEM_CLOCK__ / 32768) - 1) + 1) * 32768)
*/
#define LPC_PREINT      ((CYGNUM_HAL_ARM_LPC2XXX_CLOCK_SPEED / 32768) - 1)
#define LPC_PREFRAC     (CYGNUM_HAL_ARM_LPC2XXX_CLOCK_SPEED - (((CYGNUM_HAL_ARM_LPC2XXX_CLOCK_SPEED / 32768) - 1) + 1) * 32768)

#define __CIIR_IMSEC__          ((U8) 0x1   )
#define __CIIR_IMMIN__          ((U8) 0x1<<1)
#define __CIIR_IMHOUR__         ((U8) 0x1<<2)
#define __CIIR_IMDOM__          ((U8) 0x1<<3)
#define __CIIR_IMDOW__          ((U8) 0x1<<4)
#define __CIIR_IMDOY__          ((U8) 0x1<<5)
#define __CIIR_IMMON__          ((U8) 0x1<<6)
#define __CIIR_IMYEAR__         ((U8) 0x1<<7)

#define __CIIR_MASK__           ((U8) 0xF)

#define __AMRSEC__          0x1<<0
#define __AMRMIN__          0x1<<1
#define __AMRHOUR__         0x1<<2
#define __AMRDOM__          0x1<<3
#define __AMRDOW__          0x1<<4
#define __AMRDOY__          0x1<<5
#define __AMRMON__          0x1<<6
#define __AMRYEAR__         0x1<<7

#define __YEAR_MASK__       0xFFF
#define __MONTH_MASK__      0xF
#define __DAY_MASK__        0x1F
#define __HOUR_MASK__       0x1F
#define __MINUTE_MASK__     0x3F
#define __SECOND_MASK__     0x3F
#define __DOW_MASK__        0x7
#define __DOY_MASK__        0x1FF
#define __DEFAULT_YEAR__    2010
#define __DEFAULT_MONTH__   01
#define __DEFAULT_DAY__     01
#define __DEFAULT_HOUR__    00
#define __DEFAULT_MINUTE__  00
#define __DEFAULT_SECOND__  00
#define __DEFAULT_DOY__     01
#define __DEFAULT_DOW__     05
/**
 * @}
 */
 
 
void rtc_init();
void rtc_initCalendar();
void rtc_setDate(U16 year,U8 month, U8 day);
void rtc_setTime(U8 hour,U8 minute, U8 seconds);
void rtc_setDOW(U8 dow);
void rtc_setDOY(U16 doy);
void rtc_getDate(DATE* date);
void rtc_getTime(TIME* time);
void rtc_setDateTime(DATE_TIME* datetime);
void rtc_getDateTime(DATE_TIME* datetime);


/**
 * @brief MACRO: Set current DAY of MONTH. 
 * */
#define rtc_setDom(A)	  	((pRTC->DOM) = A & __DAY_MASK__)
/**
 * @brief MACRO: Set current MONTH. 
 * */
#define rtc_setMonth(A)		((pRTC->MONTH) = A & __MONTH_MASK__)
/**
 * @brief MACRO: Set current YEAR. 
 * */
#define rtc_setYear(A)		((pRTC->YEAR) = A & __YEAR_MASK__)
/**
 * @brief MACRO: Set current HOUR. 
 * */
#define rtc_setHour(A)		((pRTC->HOUR) = A & __HOUR_MASK__)
/**
 * @brief MACRO: Set current MINUTE. 
 * */
#define rtc_setMin(A)	  	((pRTC->MIN) = A & __MINUTE_MASK__)
/**
 * @brief MACRO: Set current SECOND. 
 * */
#define rtc_setSec(A)	  	((pRTC->SEC) = A & __SECOND_MASK__)
/**
 * @brief MACRO: Get current DAY of MONTH. 
 * */
#define rtc_getDom()	  	((pRTC->CTIME1     )  & __DAY_MASK__)
/**
 * @brief MACRO: Get current MONTH. 
 * */
#define rtc_getMonth()		((pRTC->CTIME1 >> 8)  & __MONTH_MASK__)
/**
 * @brief MACRO: Get current YEAR. 
 * */
#define rtc_getYear()	  	((pRTC->CTIME1>> 16)  & __YEAR_MASK__)
/**
 * @brief MACRO: Get current HOUR. 
 * */
#define rtc_getHour()   	((pRTC->CTIME0 >> 16) & __HOUR_MASK__)
/**
 * @brief MACRO: Get current MINUTE. 
 * */
#define rtc_getMin()	  	((pRTC->CTIME0 >> 8)  & __MINUTE_MASK__)
/**
 * @brief MACRO: Get current SECOND. 
 * */
#define rtc_getSec()	  	(pRTC->CTIME0 & __SECOND_MASK__)

#endif
