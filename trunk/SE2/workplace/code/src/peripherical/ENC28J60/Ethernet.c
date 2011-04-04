#include "Ethernet.h"
#include "ENC28J60.h"
#include "TYPES.h"
#define SINGLE_BYTE	1
#define DOUBLE_BYTE 2
#define TSV_SIZE 7
#define RSV_SIZE 4
#define TRANSMITE_LATE_COLLITION_BUG(A)		((A)[3] & (1 << 5))	
#define MAX_TX_RETRIES				10
#define PROMISCUOUS_MODE 0
#define FULL_DUPLEX  0x15
#define HALF_DUPLEX  0x12
#define  MAIPGH_HALF_DUPLEX	0x0C12
#define  MAIPGH_FULL_DUPLEX	0x12


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
		do{
			aux = ENC_read_reg(EIR,BANK00,false);
		}while((aux & EIR_TXIF) == 0);
		
		ENC_write_reg(B0_ERDPTL,BANK00,__ETHERNET_TX_START_PTR__ + packet_size + 1,true);
		ENC_read_buffer_memory(tsv,TSV_SIZE);
		aux =  ENC_read_reg(EIR,BANK00,false);
	}while((aux & EIR_TXERIF) && TRANSMITE_LATE_COLLITION_BUG(tsv) && (retry++ < MAX_TX_RETRIES) )	;
	return ETHERNET_OK;
}
U32 Ethernet_receive(U8* buffer, U32 buffer_size,U32* read_size){
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
	nbr_packets = ENC_read_reg(B1_EPKTCNT,BANK01,false);
	
	if (nbr_packets > 0){
		ENC_write_reg(B0_ERDPTL,BANK00,rx_next_packet,true);
		ENC_read_buffer_memory((U8*)&rx_next_packet,DOUBLE_BYTE);
		ENC_read_buffer_memory(rsv,RSV_SIZE);
		packet_size = ((U16)rsv[1] << 8) + rsv[0];
		*read_size = ((buffer_size<packet_size)?buffer_size:packet_size);
		ENC_read_buffer_memory(buffer,*read_size);
		ENC_write_reg(B0_ERXRDPTL,BANK00,rx_next_packet,true);
		ENC_bit_field_set(ECON2,ECON2_PKTDEC);
		
	}else{
		*read_size = 0;
	}
	return ETHERNET_OK;
}

U8 Ethernet_init(U8* mac){
	if (mac == 0)
		return ETHERNET_NULL_POINTER;
	
	ENC_write_reg(B0_ERXSTL,BANK00,__ETHERNET_RX_START_PTR__,true);
	ENC_write_reg(B0_ERXNDL,BANK00,__ETHERNET_RX_END_PTR__,true);
	ENC_write_reg(B0_ERXRDPTL,BANK00,__ETHERNET_RX_END_PTR__,true);
	
	ENC_write_reg(B1_ERXFCON,BANK01,PROMISCUOUS_MODE,false);
	ENC_write_reg(B3_MAADR1,BANK03,mac[0],false);
	ENC_write_reg(B3_MAADR2,BANK03,mac[1],false);
	ENC_write_reg(B3_MAADR3,BANK03,mac[2],false);
	ENC_write_reg(B3_MAADR4,BANK03,mac[3],false);
	ENC_write_reg(B3_MAADR5,BANK03,mac[4],false);
	ENC_write_reg(B3_MAADR6,BANK03,mac[5],false);
	
	ENC_write_reg(B2_MACON1,BANK02,MACON1_MARXEN,false);
	ENC_write_reg(B2_MACON3,BANK02,MACON3_FRMLNEN + MACON3_TXCRCEN + MACON3_PADCFG0,false);
	ENC_write_reg(B2_MACON4,BANK02,MACON4_DEFER,false);
	ENC_write_reg(B2_MAMXFLL,BANK02,MAX_FRAME_LEN,true);
	ENC_write_reg(B2_MABBIPG,BANK02,FULL_DUPLEX,false);
	ENC_write_reg(B2_MAIPGL,BANK02,MAIPGH_FULL_DUPLEX,true);
	ENC_write_reg(ECON1,BANK02,ECON1_RXEN,false);
	return ETHERNET_OK;
}

