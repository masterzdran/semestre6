#ifndef ENC28J60_H
#define ENC28J60_H

#define __ENC_READ_BUFFER_MEMORY__		(0x3A)
#define __ENC_WRITE_BUFFER_MEMORY__		(0x7A)
#define __ENC_SYSTEM_RESET_COMMAND__	(0xFF)


#define __ENC_ADDRESS_MASK__			(0x1F)
#define __ENC_OP_CODE_SHIFT__			(0x05)
#define __ENC_OP_CODE_MASK__			(0x3 << __ENC_OP_CODE_SHIFT__)

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


/* ENC28J60 CONTROL REGISTER MAP */
typedef enum{
    ERDPTL	            = 0x00,
    ERDPTH              = 0x01,     
    EWRPTL              = 0x02,     
    EWRPTH              = 0x03,     
    ETxSTL              = 0x04,     
    ETxSTH              = 0x05,     
    ETxNDL              = 0x06,     
    ETxNDH              = 0x07,     
    ERxSTL              = 0x08,     
    ERxSTH              = 0x09,
    ERxNDL              = 0x0A,
    ERxNDH              = 0x0B,
    ERxRDPTL            = 0x0C,
    ERxRDPTH            = 0x0D,
    ERxWRPTL            = 0x0E,
    ERxWRPTH            = 0x0F,
    EDMASTL             = 0x10,
    EDMASTH             = 0x11,
    EDMANDL             = 0x12,
    EDMANDH             = 0x13,
    EDMADSTL            = 0x14,
    EDMADSTH            = 0x15,
    EDMACSL             = 0x16,
    EDMACSH             = 0x17,
    BANK0_NOT_USED1     = 0x18,
    BANK0_NOT_USED2     = 0x19
}BANK0;

typedef enum{
    EHT0	          = 0x00,
    EHT1              = 0x01,     
    EHT2              = 0x02,     
    EHT3              = 0x03,     
    EHT4              = 0x04,     
    EHT5              = 0x05,     
    EHT6              = 0x06,     
    EHT7              = 0x07,     
    EPMM0             = 0x08,     
    EPMM1             = 0x09,
    EPMM2             = 0x0A,
    EPMM3             = 0x0B,
    EPMM4             = 0x0C,
    EPMM5             = 0x0D,
    EPMM6             = 0x0E,
    EPMM7             = 0x0F,
    EPMCSL            = 0x10,
    EPMCSH            = 0x11,
    BANK1_NOT_USED1   = 0x12,
    BANK1_NOT_USED2   = 0x13,
    EPMOL             = 0x14,
    EPMOH             = 0x15,
    BANK1_RESERVED01  = 0x16,
    BANK1_RESERVED02  = 0x17,
    ERxFCON           = 0x18,
    EPKTCNT           = 0x19
}BANK1;

typedef enum{
    MACON1	          = 0x00,
    BANK2_RESERVED01  = 0x01,     
    MACON3            = 0x02,     
    MACON4            = 0x03,     
    MABBIPG           = 0x04,     
    BANK2_NOT_USED1   = 0x05,     
    MAIPGL            = 0x06,     
    MAIPGH            = 0x07,     
    MACLCON1          = 0x08,     
    MACLCON2          = 0x09,
    MAMxFLL           = 0x0A,
    MAMxFLH           = 0x0B,
    BANK2_RESERVED02  = 0x0C,
    BANK2_RESERVED03  = 0x0D,
    BANK2_RESERVED04  = 0x0E,
    BANK2_NOT_USED2   = 0x0F,
    BANK2_RESERVED05  = 0x10,
    BANK2_RESERVED06  = 0x11,
    MICMD             = 0x12,
    BANK2_NOT_USED3   = 0x13,
    MIREGADR          = 0x14,
    BANK2_RESERVED07  = 0x15,
    MIWRL             = 0x16,
    MIWRH             = 0x17,
    MIRDL             = 0x18,
    MIRDH             = 0x19
}BANK2;

typedef enum{
    MAADR5	            = 0x00,
    MAADR6              = 0x01,     
    MAADR3              = 0x02,     
    MAADR4              = 0x03,     
    MAADR1              = 0x04,     
    MAADR2              = 0x05,     
    EBSTSD              = 0x06,     
    EBSTCON             = 0x07,     
    EBSTCSL             = 0x08,     
    EBSTCSH             = 0x09,
    MISTAT              = 0x0A,
    BANK3_NOT_USED01    = 0x0B,
    BANK3_NOT_USED02    = 0x0C,
    BANK3_NOT_USED03    = 0x0D,
    BANK3_NOT_USED04    = 0x0E,
    BANK3_NOT_USED05    = 0x0F,
    BANK3_NOT_USED06    = 0x10,
    BANK3_NOT_USED07    = 0x11,
    EREVID              = 0x12,
    BANK3_NOT_USED08    = 0x13,
    BANK3_NOT_USED09    = 0x14,
    ECOCON              = 0x15,
    BANK3_RESERVED01    = 0x16,
    EFLOCON             = 0x17,
    EPAUSL              = 0x18,
    EPAUSH              = 0x19
}BANK3;

typedef enum{
    SHARED_BANK_RESERVED    = 0x1A,
    EIE                     = 0x1B,
    EIR                     = 0x1C,
    ESTAT                   = 0x1D,
    ECON2                   = 0x1E,
    ECON1                   = 0x1F	
}SHARED_REGISTER_BANK;

typedef enum{
    EIE_RxERIE    = (1 << 0),
    EIE_TxERIE    = (1 << 1),
    EIE_RESERVED  = (1 << 2),
    EIE_TxIE      = (1 << 3),
    EIE_LINKIE    = (1 << 4),
    EIE_DMAIE     = (1 << 5),
    EIE_PKTIE     = (1 << 6),
    EIE_INTIE     = (1 << 7)    
}EIE_REGISTER;

typedef enum{
    EIR_RxERIE    = (1 << 0),
    EIR_TxERIE    = (1 << 1),
    EIR_RESERVED  = (1 << 2),
    EIR_TxIE      = (1 << 3),
    EIR_LINKIE    = (1 << 4),
    EIR_DMAIE     = (1 << 5),
    EIR_PKTIE     = (1 << 6),
    EIR_NOT_USED0 = (1 << 7)    
}EIR_REGISTER;

typedef enum{
    ESTAT_CLKRDY    = (1 << 0),
    ESTAT_TxABRT    = (1 << 1),
    ESTAT_RxBUSY    = (1 << 2),
    ESTAT_NOT_USED  = (1 << 3),
    ESTAT_LATECOL   = (1 << 4),
    ESTAT_RESERVED  = (1 << 5),
    ESTAT_BUFER     = (1 << 6),
    ESTAT_INT       = (1 << 7)    
}ESTAT_REGISTER;

typedef enum{
    ECON1_BSEL0     = (1 << 0),
    ECON1_BSEL1     = (1 << 1),
    ECON1_RxEN      = (1 << 2),
    ECON1_TxRTS     = (1 << 3),
    ECON1_CSUMEN    = (1 << 4),
    ECON1_DMAST     = (1 << 5),
    ECON1_RxRST     = (1 << 6),
    ECON1_TxRST      = (1 << 7)
}ECON1_REGISTER;

typedef enum{
    ECON2_NOT_USED0 = (1 << 0),
    ECON2_NOT_USED1 = (1 << 1),
    ECON2_NOT_USED2 = (1 << 2),
    ECON2_VRPS      = (1 << 3),
    ECON2_RESERVED  = (1 << 4),
    ECON2_PWRSV     = (1 << 5),
    ECON2_PKTDEC    = (1 << 6),
    ECON2_AUTOINC   = (1 << 7)
}ECON2_REGISTER;





#endif
