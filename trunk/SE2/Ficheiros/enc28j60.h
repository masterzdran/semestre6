#ifndef ENC28J60_H
#define ENC28J60_H

#define	MAX_FRAME_LEN	1518

/*
 * ENC28J60 Control Registers
 * Control register definitions are a combination of address,
 * bank number, and Ethernet/MAC/PHY indicator bits.
 * - Register address	(bits 0-4)
 * - Bank number	(bits 5-6)
 * - MAC/MII indicator	(bit 7)
 */
#define ADDR_MASK	0x1F
#define BANK_MASK	0x60
#define SPRD_MASK	0x80

/* Bank 0 registers
*/
#define ERDPTL			0x00
#define ERDPTH			0x01
#define EWRPTL			0x02
#define EWRPTH			0x03
#define ETXSTL			0x04
#define ETXSTH			0x05
#define ETXNDL			0x06
#define ETXNDH			0x07
#define ERXSTL			0x08
#define ERXSTH			0x09
#define ERXNDL			0x0A
#define ERXNDH			0x0B
#define ERXRDPTL		0x0C
#define ERXRDPTH		0x0D
#define ERXWRPTL		0x0E
#define ERXWRPTH		0x0F
#define EDMASTL			0x10
#define EDMASTH			0x11
#define EDMANDL			0x12
#define EDMANDH			0x13
#define EDMADSTL		0x14
#define EDMADSTH		0x15
#define EDMACSL			0x16
#define EDMACSH			0x17

#define EIE				0x1B
#define	EIE_INTIE		(1 << 7)
#define	EIE_PKTIE		(1 << 6)
#define	EIE_DMAIE		(1 << 5)
#define	EIE_LINKIE		(1 << 4)
#define	EIE_TXIE		(1 << 3)
#define	EIE_TXERIE		(1 << 1)
#define	EIE_RXERIE		(1 << 0)

#define EIR				0x1C
#define	EIR_PKTIF		(1 << 6)
#define	EIR_DMAIF		(1 << 5)
#define	EIR_LINKIF		(1 << 4)
#define	EIR_TXIF		(1 << 3)
#define	EIR_TXERIF		(1 << 1)
#define	EIR_RXERIF		(1 << 0)

#define ESTAT			0x1D
#define	ESTAT_INT		(1 << 7)
#define ESTAT_BUFER		(1 << 6)
#define	ESTAT_LATECOL	(1 << 4)
#define	ESTAT_RXBUSY	(1 << 2)
#define	ESTAT_TXABRT	(1 << 1)
#define	ESTAT_CLKRDY	(1 << 0)

#define ECON2			0x1E
#define	ECON2_AUTOINC	(1 << 7)
#define	ECON2_PKTDEC	(1 << 6)
#define	ECON2_PWRSV		(1 << 5)
#define	ECON2_VRPS		(1 << 3)

#define ECON1			0x1F
#define	ECON1_TXRST		(1 << 7)
#define	ECON1_RXRST		(1 << 6)
#define	ECON1_DMAST		(1 << 5)
#define	ECON1_CSUMEN	(1 << 4)
#define	ECON1_TXRTS		(1 << 3)
#define	ECON1_RXEN		(1 << 2)
#define	ECON1_BSEL1		(1 << 1)
#define	ECON1_BSEL0		(1 << 0)
#define ECON1_BSEL      (3 << 0)

/* Bank 1 registers
*/
#define EHT0			(0x00 | 0x20)
#define EHT1			(0x01 | 0x20)
#define EHT2			(0x02 | 0x20)
#define EHT3			(0x03 | 0x20)
#define EHT4			(0x04 | 0x20)
#define EHT5			(0x05 | 0x20)
#define EHT6			(0x06 | 0x20)
#define EHT7			(0x07 | 0x20)
#define EPMM0			(0x08 | 0x20)
#define EPMM1			(0x09 | 0x20)
#define EPMM2			(0x0A | 0x20)
#define EPMM3			(0x0B | 0x20)
#define EPMM4			(0x0C | 0x20)
#define EPMM5			(0x0D | 0x20)
#define EPMM6			(0x0E | 0x20)
#define EPMM7			(0x0F | 0x20)
#define EPMCSL			(0x10 | 0x20)
#define EPMCSH			(0x11 | 0x20)
#define EPMOL			(0x14 | 0x20)
#define EPMOH			(0x15 | 0x20)

#define ERXFCON			(0x18 | 0x20)
#define	ERXFCON_UCEN	(1 << 7)
#define	ERXFCON_ANDOR	(1 << 6)
#define	ERXFCON_CRCEN	(1 << 5)
#define	ERXFCON_PMEN	(1 << 4)
#define	ERXFCON_MPEN	(1 << 3)
#define	ERXFCON_HTEN	(1 << 2)
#define	ERXFCON_MCEN	(1 << 1)
#define	ERXFCON_BCEN	(1 << 0)

#define EPKTCNT			(0x19 | 0x20)

/* Bank 2 registers
*/
#define MACON1			(0x00 | 0x40 | SPRD_MASK)
#define	MACON1_TXPAUS	(1 << 3)
#define	MACON1_RXPAUS	(1 << 2)
#define	MACON1_PASSALL	(1 << 1)
#define	MACON1_MARXEN	(1 << 0)

#define MACON3			(0x02 | 0x40 | SPRD_MASK)
#define	MACON3_PADCFG2	(1 << 7)
#define	MACON3_PADCFG1	(1 << 6)
#define	MACON3_PADCFG0	(1 << 5)
#define	MACON3_TXCRCEN	(1 << 4)
#define	MACON3_PHDREN	(1 << 3)
#define	MACON3_HFRMEN	(1 << 2)
#define	MACON3_FRMLNEN	(1 << 1)
#define	MACON3_FULDPX	(1 << 0)

#define MACON4			(0x03 | 0x40 | SPRD_MASK)
#define	MACON4_DEFER	(1 << 6)
#define	MACON4_BPEN		(1 << 5)
#define	MACON4_NOBKOFF	(1 << 4)

#define MABBIPG			(0x04 | 0x40 | SPRD_MASK)
#define MAIPGL			(0x06 | 0x40 | SPRD_MASK)
#define MAIPGH			(0x07 | 0x40 | SPRD_MASK)
#define MACLCON1		(0x08 | 0x40 | SPRD_MASK)
#define MACLCON2		(0x09 | 0x40 | SPRD_MASK)
#define MAMXFLL			(0x0A | 0x40 | SPRD_MASK)
#define MAMXFLH			(0x0B | 0x40 | SPRD_MASK)

#define MICMD			(0x12 | 0x40 | SPRD_MASK)
#define	MICMD_MIISCAN	(1 << 1)
#define	MICMD_MIIRD		(1 << 0)

#define MIREGADR		(0x14 | 0x40 | SPRD_MASK)
#define MIWRL			(0x16 | 0x40 | SPRD_MASK)
#define MIWRH			(0x17 | 0x40 | SPRD_MASK)
#define MIRDL			(0x18 | 0x40 | SPRD_MASK)
#define MIRDH			(0x19 | 0x40 | SPRD_MASK)

/* Bank 3 registers
*/
#define MAADR5			(0x00 | 0x60 | SPRD_MASK) 
#define MAADR6			(0x01 | 0x60 | SPRD_MASK)
#define MAADR3			(0x02 | 0x60 | SPRD_MASK)
#define MAADR4			(0x03 | 0x60 | SPRD_MASK)
#define MAADR1			(0x04 | 0x60 | SPRD_MASK)
#define MAADR2			(0x05 | 0x60 | SPRD_MASK)
#define EBSTSD			(0x06 | 0x60)

#define EBSTCON			(0x07 | 0x60)
#define	EBSTCON_PSV2	(1 << 7)
#define	EBSTCON_PSV1	(1 << 6)
#define	EBSTCON_PSV0	(1 << 5)
#define	EBSTCON_PSEL	(1 << 4)
#define	EBSTCON_TMSEL1	(1 << 3)
#define	EBSTCON_TMSEL0	(1 << 2)
#define	EBSTCON_TME		(1 << 1)
#define	EBSTCON_BISTST	(1 << 0)

#define EBSTCSL			(0x08 | 0x60)
#define EBSTCSH			(0x09 | 0x60)

#define MISTAT			(0x0A | 0x60 | SPRD_MASK)
#define	MISTAT_NVALID	(1 << 2)
#define	MISTAT_SCAN		(1 << 1)
#define	MISTAT_BUSY		(1 << 0)

#define EREVID			(0x12 | 0x60)

#define ECOCON			(0x15 | 0x60)
#define	ECOCON_COCON2	(1 << 2)
#define	ECOCON_COCON1	(1 << 1)
#define	ECOCON_COCON0	(1 << 0)

#define EFLOCON			(0x17 | 0x60)
#define	EFLOCON_FULDPXS	(1 << 2)
#define	EFLOCON_FCEN1	(1 << 1)
#define	EFLOCON_FCEN0	(1 << 0)

#define EPAUSL			(0x18 | 0x60)
#define EPAUSH			(0x19 | 0x60)

/*	PHY Registers
*/
#define PHCON1			0x00
#define	PHCON1_PRST		(1 << 15)
#define	PHCON1_PLOOPBK	(1 << 14)
#define	PHCON1_PPWRSV	(1 << 11)
#define	PHCON1_PDPXMD	(1 << 8)

#define PHSTAT1			0x01
#define	PHSTAT1_PFDPX	(1 << 12)
#define	PHSTAT1_PHDPX	(1 << 11)
#define	PHSTAT1_LLSTAT	(1 << 2)
#define	PHSTAT1_JBSTAT	(1 << 1)

#define PHID1			0x02
#define PHID2			0x03
#define	PHID2_PID24		(1 << 15)
#define	PHID2_PID23		(1 << 14)
#define	PHID2_PID22		(1 << 13)
#define	PHID2_PID21		(1 << 12)
#define	PHID2_PID20		(1 << 11)
#define	PHID2_PID19		(1 << 10)
#define	PHID2_PPN5		(1 << 9)
#define	PHID2_PPN4		(1 << 8)
#define	PHID2_PPN3		(1 << 7)
#define	PHID2_PPN2		(1 << 6)
#define	PHID2_PPN1		(1 << 5)
#define	PHID2_PPN0		(1 << 4)
#define	PHID2_PREV3		(1 << 3)
#define	PHID2_PREV2		(1 << 2)
#define	PHID2_PREV1		(1 << 1)
#define	PHID2_PREV0		(1 << 0)

#define PHCON2			0x10
#define	PHCON2_FRCLNK	(1 << 14)
#define	PHCON2_TXDIS	(1 << 13)
#define	PHCON2_JABBER	(1 << 10)
#define	PHCON2_HDLDIS	(1 << 8)

#define PHSTAT2			0x11
#define	PHSTAT2_TXSTAT	(1 << 13)
#define	PHSTAT2_RXSTAT	(1 << 12)
#define	PHSTAT2_COLSTAT	(1 << 11)
#define	PHSTAT2_LSTAT	(1 << 10)
#define	PHSTAT2_DPXSTAT	(1 << 9)
#define	PHSTAT2_PLRITY	(1 << 5)

#define PHIE			0x12
#define	PHIE_PLNKIE		(1 << 4)
#define	PHIE_PGEIE		(1 << 1)

#define PHIR			0x13
#define	PHIR_PLNKIF		(1 << 4)
#define	PHIR_PGIF		(1 << 2)

#define PHLCON			0x14
#define	PHLCON_LACFG3	(1 << 11)
#define	PHLCON_LACFG2	(1 << 10)
#define	PHLCON_LACFG1	(1 << 9)
#define	PHLCON_LACFG0	(1 << 8)
#define	PHLCON_LBCFG3	(1 << 7)
#define	PHLCON_LBCFG2	(1 << 6)
#define	PHLCON_LBCFG1	(1 << 5)
#define	PHLCON_LBCFG0	(1 << 4)
#define	PHLCON_LFRQ1	(1 << 3)
#define	PHLCON_LFRQ0	(1 << 2)
#define	PHLCON_STRCH	(1 << 1)

#endif

