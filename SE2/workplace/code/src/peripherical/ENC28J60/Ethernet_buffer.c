#include "Ethernet.h"
#include "ENC28J60.h"
#include "TYPES.h"
#include "BUFFER.h"


#define SINGLE_BYTE	1
#define DOUBLE_BYTE 2
#define TSV_SIZE 7
#define RSV_SIZE 4
#define TRANSMITE_LATE_COLLITION_BUG(A)		((A)[3] & (1 << 5))	
#define MAX_TX_RETRIES				10
#define PROMISCUOUS_MODE 0      /*ERXFCON_REGISTER Enumerator shoul be used to filter packets*/
#define FULL_DUPLEX  0x15
#define HALF_DUPLEX  0x12
#define MAIPGH_HALF_DUPLEX	0x0C12
#define MAIPGH_FULL_DUPLEX	0x12

#define __BUFFER_RX_SIZE__		8192
#define __BUFFER_TX_SIZE__		8192

static BUFFER tx_Buffer;
static BUFFER rx_Buffer;
static pETHERNET_Device ethDevice;
static U8 tx_Buffer_Space[__BUFFER_TX_SIZE__];
static U8 rx_Buffer_Space[__BUFFER_RX_SIZE__];

/**
 * @brief 
 * */
U8 Ethernet_init(pETHERNET_Device ethernetDevice){
	if (&(ethernetDevice->mac) == 0)
		return ETHERNET_MAC_NULL_POINTER;
	
    ethDevice = ethernetDevice;
    /* Definition of Enc28j60 spi default values */
    ethDevice->ethernetDevice.mode       = SPI_PRIOR_TO_FIRST_SCK_RISING_EDGE;
    ethDevice->ethernetDevice.role       = SPI_MASTER;
    ethDevice->ethernetDevice.nbrbits    = 8;
    ethDevice->ethernetDevice.byteShift  = SPI_MSB;
    ethDevice->ethernetDevice.started    = 0;
    
    /*Intialization of spi device of ethernet*/
    if ( SPI_init(&(ethDevice->ethernetDevice),1) != SPI_SUCESS ){
        return ETHERNET_SPI_INIT_ERROR;
    } 
    
	ENC_init(&ethDevice->ethernetDevice);
    /*Reset Enc28j60 to default values*/
    ENC_system_reset_command();
    
    /*6.1 Receive Buffer*/
    /*
	ENC_write_reg(B0_ERXSTL,BANK00,__ETHERNET_RX_START_PTR__,true);
	ENC_write_reg(B0_ERXNDL,BANK00,__ETHERNET_RX_END_PTR__,true);
	ENC_write_reg(B0_ERXRDPTL,BANK00,__ETHERNET_RX_END_PTR__,true);
	*/
	ENC_WRITE_REG16(B0_ERXSTL,BANK00,__ETHERNET_RX_START_PTR__);
	ENC_WRITE_REG16(B0_ERXNDL,BANK00,__ETHERNET_RX_END_PTR__);
	ENC_WRITE_REG16(B0_ERXRDPTL,BANK00,__ETHERNET_RX_END_PTR__);
    
    
    /*
	ENC_write_reg(B1_ERXFCON,BANK01,PROMISCUOUS_MODE,false);
	ENC_write_reg(B3_MAADR1,BANK03,ethernetDevice->mac[0],false);
	ENC_write_reg(B3_MAADR2,BANK03,ethernetDevice->mac[1],false);
	ENC_write_reg(B3_MAADR3,BANK03,ethernetDevice->mac[2],false);
	ENC_write_reg(B3_MAADR4,BANK03,ethernetDevice->mac[3],false);
	ENC_write_reg(B3_MAADR5,BANK03,ethernetDevice->mac[4],false);
	ENC_write_reg(B3_MAADR6,BANK03,ethernetDevice->mac[5],false);
	
	ENC_write_reg(B2_MACON1,BANK02,MACON1_MARXEN,false);
	ENC_write_reg(B2_MACON3,BANK02,MACON3_FRMLNEN + MACON3_TXCRCEN + MACON3_PADCFG0,false);
	ENC_write_reg(B2_MACON4,BANK02,MACON4_DEFER,false);
    */
    /*6.3 Receive Filters*/
    ENC_WRITE_REG8(B1_ERXFCON,BANK01,PROMISCUOUS_MODE);
    
    /*6.5 MAC Initialization Settings*/
	ENC_WRITE_REG8(B3_MAADR1,BANK03,ethernetDevice->mac[0]);
	ENC_WRITE_REG8(B3_MAADR2,BANK03,ethernetDevice->mac[1]);
	ENC_WRITE_REG8(B3_MAADR3,BANK03,ethernetDevice->mac[2]);
	ENC_WRITE_REG8(B3_MAADR4,BANK03,ethernetDevice->mac[3]);
	ENC_WRITE_REG8(B3_MAADR5,BANK03,ethernetDevice->mac[4]);
	ENC_WRITE_REG8(B3_MAADR6,BANK03,ethernetDevice->mac[5]);
	
	ENC_WRITE_REG8(B2_MACON1,BANK02,MACON1_MARXEN);
	ENC_WRITE_REG8(B2_MACON3,BANK02,MACON3_FRMLNEN + MACON3_TXCRCEN + MACON3_PADCFG0);
	ENC_WRITE_REG8(B2_MACON4,BANK02,MACON4_DEFER);
    
	/*ENC_write_reg(B2_MAMXFLL,BANK02,MAX_FRAME_LEN,true);*/
    ENC_WRITE_REG16(B2_MAMXFLL,BANK02,MAX_FRAME_LEN);
    /**
     * @todo
     * Config Full Duplex     
     * *//*
	if ( ethernetDevice->duplex == ETHERNET_FULL_DUPLEX){
        ENC_write_reg(B2_MABBIPG,BANK02,FULL_DUPLEX,false);
        ENC_write_reg(B2_MAIPGL,BANK02,MAIPGH_FULL_DUPLEX,true);
	}else{
        ENC_write_reg(B2_MABBIPG,BANK02,HALF_DUPLEX,false);
        ENC_write_reg(B2_MAIPGL,BANK02,MAIPGH_HALF_DUPLEX,true);
    }
    ENC_write_reg(ECON1,BANK02,ECON1_RXEN,false);	
    */
    if ( ethernetDevice->duplex == ETHERNET_FULL_DUPLEX){
        ENC_WRITE_REG8(B2_MABBIPG,BANK02,FULL_DUPLEX);
        ENC_WRITE_REG16(B2_MAIPGL,BANK02,MAIPGH_FULL_DUPLEX);
	}else{
        ENC_WRITE_REG8(B2_MABBIPG,BANK02,HALF_DUPLEX);
        ENC_WRITE_REG16(B2_MAIPGL,BANK02,MAIPGH_HALF_DUPLEX);
    }
    ENC_WRITE_REG8(ECON1,BANK02,ECON1_RXEN);
	
	/*
	 * Prepare Software Buffer.
	 * */
	 buffer_init(&rx_Buffer,&rx_Buffer_Space,__BUFFER_RX_SIZE__);
	 buffer_init(&tx_Buffer,&tx_Buffer_Space,__BUFFER_TX_SIZE__);
	 
	 
	return ETHERNET_OK;
}

U16 Ethernet_receive(U8* buffer, U16 buffer_size){
	if (buffer== 0)
		return ETHERNET_NULL_POINTER;
	if(buffer_size == 0 )
		return ETHERNET_NULL_POINTER;
	if (buffer_size > MAX_FRAME_LEN)
		return ETHERNET_PACKET_TOO_LONG;	
	buffer_get(rx_Buffer, buffer, buffer_size)
}



U8	Ethernet_send(U8* packet, U16 packet_size){
	if (packet == 0)
		return ETHERNET_NULL_POINTER;
	if(packet_size == 0 )
		return ETHERNET_NULL_POINTER;
	if (packet_size > MAX_FRAME_LEN)
		return ETHERNET_PACKET_TOO_LONG;
	buffer_put(tx_Buffer, packet, packet_size);
}

