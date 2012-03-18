#include "Ethernet.h"
#include "ENC28J60.h"
#include "TYPES.h"
#include "GPIO.h"

#define SINGLE_BYTE	1
#define DOUBLE_BYTE 2
#define TSV_SIZE 7
#define RSV_SIZE 4
#define TRANSMITE_LATE_COLLITION_BUG(A)		((A)[3] & (1 << 5))	
#define MAX_TX_RETRIES				10
#define PROMISCUOUS_MODE 0      /*ERXFCON_REGISTER Enumerator should be used to filter packets*/
#define FULL_DUPLEX  0x15
#define HALF_DUPLEX  0x12
#define MAIPGH_HALF_DUPLEX	0x0C12
#define MAIPGH_FULL_DUPLEX	0x12


static pETHERNET_Device ethDevice;

static void enc28j60_cs(int select) {
	if (select)
		GPIO_CLEAR(CS_PIN);
	else
		GPIO_SET(CS_PIN);
}

static cyg_spi_lpc2xxx_dev_t spi_enc28j60_dev CYG_SPI_DEVICE_ON_BUS(0) =
{
	.spi_device.spi_bus = &cyg_spi_lpc2xxx_bus0.spi_bus,
	.spi_cpha = 0, 			//Clock phase (0 or 1)
	.spi_cpol = 0, 			// Clock polarity (0 or 1)
	.spi_lsbf = 0, 			// MSBF
	.spi_baud = 10000, 		// Clock baud rate
	.spi_cs = enc28j60_cs
};

U8 Ethernet_init(pETHERNET_Device ethernetDevice){
	if (&(ethernetDevice->mac) == 0) return ETHERNET_MAC_NULL_POINTER;
	
    ethDevice = ethernetDevice;

    ethDevice->ethernetDevice=&spi_enc28j60_dev;

    ENC_init(ethDevice->ethernetDevice);

    /*Reset Enc28j60 to default values*/
    /*ENC_system_reset_command();*/

    /*6.1 Receive Buffer*/

	ENC_WRITE_REG16(B0_ERXSTL,BANK00,__ETHERNET_RX_START_PTR__);
	ENC_WRITE_REG16(B0_ERXNDL,BANK00,__ETHERNET_RX_END_PTR__);
	ENC_WRITE_REG16(B0_ERXRDPTL,BANK00,__ETHERNET_RX_END_PTR__);
    
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

    ENC_WRITE_REG16(B2_MAMXFLL,BANK02,MAX_FRAME_LEN);

    if ( ethernetDevice->duplex == ETHERNET_FULL_DUPLEX){
        ENC_WRITE_REG8(B2_MABBIPG,BANK02,FULL_DUPLEX);
        ENC_WRITE_REG16(B2_MAIPGL,BANK02,MAIPGH_FULL_DUPLEX);
	}else{
        ENC_WRITE_REG8(B2_MABBIPG,BANK02,HALF_DUPLEX);
        ENC_WRITE_REG16(B2_MAIPGL,BANK02,MAIPGH_HALF_DUPLEX);
    }

    ENC_WRITE_REG8(ECON1,BANK02,ECON1_RXEN);
	return ETHERNET_OK;
}

static inline void Ethernet_prepare(U8* packet, U16 packet_size){
	U8 control = 0x0;
	ENC_write_reg(B0_ETXSTL,BANK00,__ETHERNET_TX_START_PTR__,true);
	ENC_write_reg(B0_ETXNDL,BANK00,__ETHERNET_TX_START_PTR__+ packet_size,true);
	ENC_write_reg(B0_EWRPTL,BANK00,__ETHERNET_TX_START_PTR__,true);
	ENC_write_buffer_memory(&control,SINGLE_BYTE);
	ENC_write_buffer_memory(packet,packet_size);	
}

static inline void Ethernet_start_tx(){
	ENC_bit_field_set(ECON1,ECON1_TXRST);
	ENC_bit_field_clear(ECON1,ECON1_TXRST);
	ENC_bit_field_clear(EIR,EIR_TXERIF|EIR_TXIF);
	ENC_bit_field_set(ECON1,ECON1_TXRTS);	
}

U8 Ethernet_send(U8* packet, U16 packet_size){
	U8 tsv[TSV_SIZE],aux;
	U8 retry = 0;
	if (packet == 0)
		return ETHERNET_NULL_POINTER;
	if(packet_size == 0 )
		return ETHERNET_NULL_POINTER;
	if (packet_size > MAX_FRAME_LEN)
		return ETHERNET_PACKET_TOO_LONG;
	Ethernet_prepare(packet,packet_size);
	do{
		Ethernet_start_tx();
		do{ aux = ENC_READ_REG8(EIR,BANK00);}while((aux & EIR_TXIF) == 0);

		ENC_bit_field_clear(ECON1,ECON1_TXRTS); /* ?? */
		ENC_WRITE_REG16(B0_ERDPTL,BANK00,__ETHERNET_TX_START_PTR__ + packet_size + 1);
		ENC_read_buffer_memory(tsv,TSV_SIZE);

        aux =  ENC_READ_REG8(EIR,BANK00);
	}while((aux & EIR_TXERIF) && TRANSMITE_LATE_COLLITION_BUG(tsv) && (retry++ < MAX_TX_RETRIES) )	;
	return ETHERNET_OK;
}


U32 Ethernet_receive(U8* buffer, U32 buffer_size){
	U32 read_size=0;
	U8 rsv[RSV_SIZE];
	U32 packet_size = 0;
	U16 rx_next_packet = __ETHERNET_RX_START_PTR__;
	U32 nbr_packets = 0;
	
	if (buffer== 0)
		return ETHERNET_NULL_POINTER;
	if(buffer_size == 0 )
		return ETHERNET_NULL_POINTER;
	if (buffer_size > MAX_FRAME_LEN)
		return ETHERNET_PACKET_TOO_LONG;	
	/*Evaluate parameters. Then spent time*/
	nbr_packets = ENC_READ_REG8(B1_EPKTCNT,BANK01);

	if (nbr_packets > 0){
		ENC_WRITE_REG16(B0_ERDPTL,BANK00,rx_next_packet);
		ENC_read_buffer_memory((U8*)&rx_next_packet,DOUBLE_BYTE);
		ENC_read_buffer_memory(rsv,RSV_SIZE);
		packet_size = ((U16)rsv[1] << 8) + rsv[0];
		read_size = ((buffer_size<packet_size)?buffer_size:packet_size);
		ENC_read_buffer_memory(buffer,read_size);
		ENC_WRITE_REG16(B0_ERXRDPTL,BANK00,rx_next_packet);
		ENC_bit_field_set(ECON2,ECON2_PKTDEC);
		
	}else{
		read_size = 0;
	}
	return (read_size);
}
