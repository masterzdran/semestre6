#ifndef ENC28J60_H
#define ENC28J60_H
#include "TYPES.h"
/*#include "SPI_Public.h"*/
#include <cyg/io/spi_lpc2xxx.h>
#include <cyg/infra/cyg_type.h>

#define CS_PIN 1<<8
#define RESET  1<<9

#define ADDR_MASK	0x1F
#define BANK_MASK	0x60
#define SPRD_MASK	0x80
#define	MAX_FRAME_LEN	1518
/*
#define __ENC_READ_BUFFER_MEMORY__		(0x3A)
#define __ENC_WRITE_BUFFER_MEMORY__		(0x7A)
#define __ENC_SYSTEM_RESET_COMMAND__	(0xFF)
*/

#define __ENC_ADDRESS_MASK__			(0x1F)
#define __ENC_OP_CODE_SHIFT__			(0x05)
#define __OP_CODE_MASK__		        (0x7 << __OP_CODE_SHIFT__)


#define __DEFAULT_DEF_START_BANK_ADDR__ 		(0x0)
#define __DEFAULT_DEF_START_SHARED_BANK_ADDR__ 	(0x1A)
#define __BANK_REGISTER_SHIFT__		(0x5)
#define ECON1_BSEL      (3 << 0)


/**
  * - set BBBX XXXX bits as:
  *  - 001: ETH register
  *  - 010: MAC or MII registers 
  *  - 100: PHY register
  * */

typedef enum{
    ENC_REGISTER_ETH        = (0x001<< __ENC_OP_CODE_SHIFT__),
    ENC_REGISTER_MAC_MII    = (0x002<< __ENC_OP_CODE_SHIFT__),
    ENC_REGISTER_PHY        = (0x004<< __ENC_OP_CODE_SHIFT__)    
}ENC_REGISTER_TYPE;

typedef enum{
	BANK00=0x0,
	BANK01=0x1,
	BANK02=0x2,
	BANK03=0x3
}ENC_BANK_ID;

typedef enum{
        B0_ERDPTL      = 0x00  | ENC_REGISTER_ETH,
        B0_ERDPTH      = 0x01  | ENC_REGISTER_ETH,
        B0_EWRPTL      = 0x02  | ENC_REGISTER_ETH,
        B0_EWRPTH      = 0x03  | ENC_REGISTER_ETH,
        B0_ETXSTL      = 0x04  | ENC_REGISTER_ETH,
        B0_ETXSTH      = 0x05  | ENC_REGISTER_ETH,
        B0_ETXNDL      = 0x06  | ENC_REGISTER_ETH,
        B0_ETXNDH      = 0x07  | ENC_REGISTER_ETH,
        B0_ERXSTL      = 0x08  | ENC_REGISTER_ETH,
        B0_ERXSTH      = 0x09  | ENC_REGISTER_ETH,
        B0_ERXNDL      = 0x0A  | ENC_REGISTER_ETH,
        B0_ERXNDH      = 0x0B  | ENC_REGISTER_ETH,
        B0_ERXRDPTL    = 0x0C  | ENC_REGISTER_ETH,
        B0_ERXRDPTH    = 0x0D  | ENC_REGISTER_ETH,
        B0_ERXWRPTL    = 0x0E  | ENC_REGISTER_ETH,
        B0_ERXWRPTH    = 0x0F  | ENC_REGISTER_ETH,
        B0_EDMASTL     = 0x10  | ENC_REGISTER_ETH,
        B0_EDMASTH     = 0x11  | ENC_REGISTER_ETH,
        B0_EDMANDL     = 0x12  | ENC_REGISTER_ETH,
        B0_EDMANDH     = 0x13  | ENC_REGISTER_ETH,
        B0_EDMADST     = 0x14  | ENC_REGISTER_ETH,
        B0_EDMADSTH    = 0x15  | ENC_REGISTER_ETH,
        B0_EDMACSL     = 0x16  | ENC_REGISTER_ETH,
        B0_EDMACSH     = 0x17  | ENC_REGISTER_ETH
}ENC_BANK0_REGISTER;

typedef enum{
        B1_EHT0     = 0x00  | ENC_REGISTER_ETH,
        B1_EHT1     = 0x01  | ENC_REGISTER_ETH,
        B1_EHT2     = 0x02  | ENC_REGISTER_ETH,
        B1_EHT3     = 0x03  | ENC_REGISTER_ETH,
        B1_EHT4     = 0x04  | ENC_REGISTER_ETH,
        B1_EHT5     = 0x05  | ENC_REGISTER_ETH,
        B1_EHT6     = 0x06  | ENC_REGISTER_ETH,
        B1_EHT7     = 0x07  | ENC_REGISTER_ETH,
        B1_EPMM0    = 0x08  | ENC_REGISTER_ETH,
        B1_EPMM1    = 0x09  | ENC_REGISTER_ETH,
        B1_EPMM2    = 0x0A  | ENC_REGISTER_ETH,
        B1_EPMM3    = 0x0B  | ENC_REGISTER_ETH,
        B1_EPMM4    = 0x0C  | ENC_REGISTER_ETH,
        B1_EPMM5    = 0x0D  | ENC_REGISTER_ETH,
        B1_EPMM6    = 0x0E  | ENC_REGISTER_ETH,
        B1_EPMM7    = 0x0F  | ENC_REGISTER_ETH,
        B1_EPMCSL   = 0x10  | ENC_REGISTER_ETH,
        B1_EPMCSH   = 0x11  | ENC_REGISTER_ETH,
        B1_EPMOL    = 0x14  | ENC_REGISTER_ETH,
        B1_EPMOH    = 0x15  | ENC_REGISTER_ETH,
        B1_ERXFCON  = 0x18  | ENC_REGISTER_ETH,
        B1_EPKTCNT  = 0x19  | ENC_REGISTER_ETH
}ENC_BANK1_REGISTER;

typedef enum{
        B2_MACON1      = 0x00  | ENC_REGISTER_MAC_MII,
        B2_MACON3      = 0x02  | ENC_REGISTER_MAC_MII,
        B2_MACON4      = 0x03  | ENC_REGISTER_MAC_MII,
        B2_MABBIPG     = 0x04  | ENC_REGISTER_MAC_MII,
        B2_MAIPGL      = 0x06  | ENC_REGISTER_MAC_MII,
        B2_MAIPGH      = 0x07  | ENC_REGISTER_MAC_MII,
        B2_MACLCON1    = 0x08  | ENC_REGISTER_MAC_MII,
        B2_MACLCON2    = 0x09  | ENC_REGISTER_MAC_MII,
        B2_MAMXFLL     = 0x0A  | ENC_REGISTER_MAC_MII,
        B2_MAMXFLH     = 0x0B  | ENC_REGISTER_MAC_MII,
        B2_MICMD       = 0x12  | ENC_REGISTER_MAC_MII,
        B2_MIREGADR    = 0x14  | ENC_REGISTER_MAC_MII,
        B2_MIWRL       = 0x16  | ENC_REGISTER_MAC_MII,
        B2_MIWRH       = 0x17  | ENC_REGISTER_MAC_MII,
        B2_MIRDL       = 0x18  | ENC_REGISTER_MAC_MII,
        B2_MIRDH       = 0x19  | ENC_REGISTER_MAC_MII
}ENC_BANK2_REGISTER;

typedef enum{
        B3_MAADR5          = 0x00  | ENC_REGISTER_MAC_MII,
        B3_MAADR6          = 0x01  | ENC_REGISTER_MAC_MII,
        B3_MAADR3          = 0x02  | ENC_REGISTER_MAC_MII,
        B3_MAADR4          = 0x03  | ENC_REGISTER_MAC_MII,
        B3_MAADR1          = 0x04  | ENC_REGISTER_MAC_MII,
        B3_MAADR2          = 0x05  | ENC_REGISTER_MAC_MII,
        B3_EBSTSD          = 0x06  | ENC_REGISTER_ETH,
        B3_EBSTCON         = 0x07  | ENC_REGISTER_ETH,
        B3_EBSTCSL         = 0x08  | ENC_REGISTER_ETH,
        B3_EBSTCSH         = 0x09  | ENC_REGISTER_ETH,
        B3_MISTAT          = 0x0A  | ENC_REGISTER_MAC_MII,
        B3_EREVID          = 0x12  | ENC_REGISTER_ETH,
        B3_ECOCON          = 0x15  | ENC_REGISTER_ETH,
        B3_EFLOCON         = 0x17  | ENC_REGISTER_ETH,
        B3_EPAUSL          = 0x18  | ENC_REGISTER_ETH,
        B3_EPAUSH          = 0x19  | ENC_REGISTER_ETH
}ENC_BANK3_REGISTER;

typedef enum{
	EIE     = 0x1B,
	EIR     = 0x1C,
	ESTAT   = 0x1D,
	ECON2   = 0x1E,
	ECON1   = 0x1F
}ENC_SHARED_REGISTER;

typedef enum{
	BBIPG0 = 1 << 0,
	BBIPG1 = 1 << 1,
	BBIPG2 = 1 << 2,
	BBIPG3 = 1 << 3,
	BBIPG4 = 1 << 4,
	BBIPG5 = 1 << 5,
	BBIPG6 = 1 << 6
}MABBIPG_REGISTER;

/* SPI Operation Codes */
typedef enum {
    __ENC_SPI_READ_CONTROL_REGISTER_OP_CODE__	= (0x0) << __ENC_OP_CODE_SHIFT__,
    __ENC_SPI_READ_BUFFER_MEMORY_OP_CODE__		= (0x1) << __ENC_OP_CODE_SHIFT__,
    __ENC_SPI_WRITE_CONTROL_REGISTER_OP_CODE__	= (0x2) << __ENC_OP_CODE_SHIFT__,
    __ENC_SPI_WRITE_BUFFER_MEMORY_OP_CODE__		= (0x3) << __ENC_OP_CODE_SHIFT__,
    __ENC_SPI_BIT_FIELD_SET_OP_CODE__			= (0x4) << __ENC_OP_CODE_SHIFT__,
    __ENC_SPI_BIT_FIELD_CLEAR_OP_CODE__			= (0x5) << __ENC_OP_CODE_SHIFT__,
    __ENC_SPI_SYSTEM_RESET_COMMAND_OP_CODE__	= (0x7) << __ENC_OP_CODE_SHIFT__
}ENC_SPI_OP_CODE;



#define __ENC_READ_BUFFER_MEMORY__ 		    (__ENC_SPI_READ_BUFFER_MEMORY_OP_CODE__   | 0x1A)
#define __ENC_WRITE_BUFFER_MEMORY__		    (__ENC_SPI_WRITE_BUFFER_MEMORY_OP_CODE__  | 0x1A)
#define __ENC_SYSTEM_RESET_COMMAND__	    (__ENC_SPI_SYSTEM_RESET_COMMAND_OP_CODE__ | 0x1F)
#define __ENC_READ_BUFFER_MEMORY_SIZE__ 	(0x1)
#define __ENC_WRITE_CONTROL_MEMORY_SIZE__	(0x2)
#define __ENC_WRITE_BUFFER_MEMORY_SIZE__	(0x1)
#define __ENV_SYSTEM_RESET_COMMAND_SIZE__	(0x1)
#define __ENC_SPI_BIT_FIELD_CLEAR_SIZE__ 	(0x2)
#define __ENC_SPI_BIT_FIELD_SET_SIZE__  	(0x2)
#define __ENC_SYSTEM_RESET_COMMAND_SIZE__	(0x1)
#define __ENC_READ_BUFFER_SIZE__            (0x3)
#define __ENC_WRITE_BUFFER_SIZE__           (0x3)

#define ENC_BUFFER_LEN(A)           ((A)&ENC_REGISTER_MAC_MII ? 3 : 2)



typedef enum{
	EIE_INTIE 	= (1 << 7),
	EIE_PKTIE 	= (1 << 6),
	EIE_DMAIE	= (1 << 5),
	EIE_LINKIE	= (1 << 4),
	EIE_TXIE	= (1 << 3),
	EIE_TXERIE	= (1 << 1),
	EIE_RXERIE	= (1 << 0)
}EIE_REGISTER;
typedef enum{
	EIR_PKTIF		= (1 << 6),
	EIR_DMAIF		= (1 << 5),
	EIR_LINKIF		= (1 << 4),
	EIR_TXIF		= (1 << 3),
	EIR_TXERIF		= (1 << 1),
	EIR_RXERIF		= (1 << 0),
	EIR_NOT_USED 	= (1 << 7)
}EIR_REGISTER;

typedef enum{
	ESTAT_INT		= (1 << 7),
	ESTAT_BUFER		= (1 << 6),
	ESTAT_RESERVED	= (1 << 5),
	ESTAT_LATECOL	= (1 << 4),
	ESTAT_NOT_USED	= (1 << 3),
	ESTAT_RXBUSY	= (1 << 2),
	ESTAT_TXABRT	= (1 << 1),
	ESTAT_CLKRDY	= (1 << 0)
}ESTAT_REGISTER;

typedef enum{
	ECON2_AUTOINC	= (1 << 7),
	ECON2_PKTDEC	= (1 << 6),
	ECON2_PWRSV		= (1 << 5),
	ECON2_RESERVED 	= (1 << 4),
	ECON2_VRPS	   	= (1 << 3),
	ECON2_NOT_USED 	= (7 << 0)	
}ECON2_REGISTER;

typedef enum{
	ECON1_TXRST		= (1 << 7),
	ECON1_RXRST		= (1 << 6),
	ECON1_DMAST		= (1 << 5),
	ECON1_CSUMEN	= (1 << 4),
	ECON1_TXRTS		= (1 << 3),
	ECON1_RXEN		= (1 << 2),
	ECON1_BSEL1		= (1 << 1),
	ECON1_BSEL0		= (1 << 0)
}ECON1_REGISTER;

typedef enum{
		ERXFCON_UCEN	= (1 << 7),
		ERXFCON_ANDOR	= (1 << 6),
		ERXFCON_CRCEN	= (1 << 5),
		ERXFCON_PMEN	= (1 << 4),
		ERXFCON_MPEN	= (1 << 3),
		ERXFCON_HTEN	= (1 << 2),
		ERXFCON_MCEN	= (1 << 1),
		ERXFCON_BCEN	= (1 << 0)
}ERXFCON_REGISTER;

typedef enum{
		MACON1_TXPAUS	= (1 << 3),
		MACON1_RXPAUS	= (1 << 2),
		MACON1_PASSALL	= (1 << 1),
		MACON1_MARXEN	= (1 << 0)
}MACON1_REGISTER;

typedef enum{
		MACON3_PADCFG2	= (1 << 7),
		MACON3_PADCFG1	= (1 << 6),
		MACON3_PADCFG0	= (1 << 5),
		MACON3_TXCRCEN	= (1 << 4),
		MACON3_PHDREN	= (1 << 3),
		MACON3_HFRMEN	= (1 << 2),
		MACON3_FRMLNEN	= (1 << 1),
		MACON3_FULDPX	= (1 << 0)
}MACON3_REGISTER;

typedef enum{
		MACON4_DEFER	= (1 << 6),
		MACON4_BPEN		= (1 << 5),
		MACON4_NOBKOFF	= (1 << 4)
}MACON4_REGISTER;

typedef enum{
		MICMD_MIISCAN	= (1 << 1),
		MICMD_MIIRD		= (1 << 0)
}MICMD_REGISTER;

typedef enum{
		EBSTCON_PSV2	= (1 << 7),
		EBSTCON_PSV1	= (1 << 6),
		EBSTCON_PSV0	= (1 << 5),
		EBSTCON_PSEL	= (1 << 4),
		EBSTCON_TMSEL1	= (1 << 3),
		EBSTCON_TMSEL0	= (1 << 2),
		EBSTCON_TME		= (1 << 1),
		EBSTCON_BISTST	= (1 << 0)
}EBSTCON_REGISTER;

typedef enum{
		MISTAT_NVALID	= (1 << 2),
		MISTAT_SCAN		= (1 << 1),
		MISTAT_BUSY		= (1 << 0)
}MISTAT_REGISTER;

typedef enum{
		ECOCON_COCON2	= (1 << 2),
		ECOCON_COCON1	= (1 << 1),
		ECOCON_COCON0	= (1 << 0)
}ECOCON_REGISTER;

typedef enum{
		EFLOCON_FULDPXS	= (1 << 2),
		EFLOCON_FCEN1	= (1 << 1),
		EFLOCON_FCEN0	= (1 << 0)
}EFLOCON_REGISTER;

/* ------------------------------------------------------------------ */
/*	PHY Registers
*/
typedef enum{
    PHCON1			= 0x00  | ENC_REGISTER_PHY,
    PHSTAT1			= 0x01  | ENC_REGISTER_PHY,
    PHID1			= 0x02  | ENC_REGISTER_PHY,
    PHID2			= 0x03  | ENC_REGISTER_PHY,
    PHCON2			= 0x10  | ENC_REGISTER_PHY,
    PHSTAT2			= 0x11  | ENC_REGISTER_PHY,
    PHIE			= 0x12  | ENC_REGISTER_PHY,
    PHIR			= 0x13  | ENC_REGISTER_PHY,
    PHLCON			= 0x14  | ENC_REGISTER_PHY
}ENC_PHY_REGISTER;

typedef enum{
    PHCON1_PRST		= (1 << 15),
    PHCON1_PLOOPBK	= (1 << 14),
    PHCON1_PPWRSV	= (1 << 11),
    PHCON1_PDPXMD	= (1 << 8)
}PHCON1_REGISTER;
typedef enum{
    PHSTAT1_PFDPX	= (1 << 12),
    PHSTAT1_PHDPX	= (1 << 11),
    PHSTAT1_LLSTAT	= (1 << 2),
    PHSTAT1_JBSTAT	= (1 << 1)
}PHSTAT1_REGISTER;
typedef enum{
    PHID2_PID24		= (1 << 15),
    PHID2_PID23		= (1 << 14),
    PHID2_PID22		= (1 << 13),
    PHID2_PID21		= (1 << 12),
    PHID2_PID20		= (1 << 11),
    PHID2_PID19		= (1 << 10),
    PHID2_PPN5		= (1 << 9),
    PHID2_PPN4		= (1 << 8),
    PHID2_PPN3		= (1 << 7),
    PHID2_PPN2		= (1 << 6),
    PHID2_PPN1		= (1 << 5),
    PHID2_PPN0		= (1 << 4),
    PHID2_PREV3		= (1 << 3),
    PHID2_PREV2		= (1 << 2),
    PHID2_PREV1		= (1 << 1),
    PHID2_PREV0		= (1 << 0)
}PHID2_REGISTER;

typedef enum{
    PHCON2_FRCLNK	= (1 << 14),
    PHCON2_TXDIS	= (1 << 13),
    PHCON2_JABBER	= (1 << 10),
    PHCON2_HDLDIS	= (1 << 8)
}PHCON2_REGISTER;
typedef enum{
    PHSTAT2_TXSTAT	= (1 << 13),
    PHSTAT2_RXSTAT	= (1 << 12),
    PHSTAT2_COLSTAT	= (1 << 11),
    PHSTAT2_LSTAT	= (1 << 10),
    PHSTAT2_DPXSTAT	= (1 << 9),
    PHSTAT2_PLRITY	= (1 << 5)
}PHSTAT2_REGISTER;
typedef enum{
    PHIE_PLNKIE		= (1 << 4),
    PHIE_PGEIE		= (1 << 1)
}PHIE_REGISTER;
typedef enum{
    PHIR_PLNKIF		= (1 << 4),
    PHIR_PGIF		= (1 << 2)
}PHIR_REGISTER;
typedef enum{
    PHLCON_LACFG3	= (1 << 11),
    PHLCON_LACFG2	= (1 << 10),
    PHLCON_LACFG1	= (1 << 9),
    PHLCON_LACFG0	= (1 << 8),
    PHLCON_LBCFG3	= (1 << 7),
    PHLCON_LBCFG2	= (1 << 6),
    PHLCON_LBCFG1	= (1 << 5),
    PHLCON_LBCFG0	= (1 << 4),
    PHLCON_LFRQ1	= (1 << 3),
    PHLCON_LFRQ0	= (1 << 2),
    PHLCON_STRCH	= (1 << 1)
}PHLCON_REGISTER;


U16 ENC_read_reg(U8 address, U8 bankID,bool asShort);
void ENC_write_reg(U8 address, U8 bankID,U16 data,bool asShort);
void ENC_write_physical_register(U8 address, U16 data);
U16 read_physical_register(U8 address) ;
U8 ENC_read_control_register(U8 address);
void ENC_read_buffer_memory(U8* buffer, U32 size);
void ENC_write_control_register(U8 address, U8 data);
void ENC_write_buffer_memory(U8* data, U32 size);
void ENC_bit_field_set(U8 address, U8 data);
void ENC_bit_field_clear(U8 address, U8 data);
void ENC_system_reset_command();
void ENC_init(cyg_spi_lpc2xxx_dev_t *pspi);

U8 ENC_test();

void encIsr(void) __attribute__ ((interrupt));

#define ENC_WRITE_REG16(A, B, C)  	ENC_write_reg((A), (B),(C),true)
#define ENC_WRITE_REG8(A, B, C)  	ENC_write_reg((A), (B),(C),false)
#define ENC_READ_REG8(A, B) 		ENC_read_reg((A), (B),false)
#define ENC_READ_REG16(A, B) 		ENC_read_reg((A), (B),true)
#endif

