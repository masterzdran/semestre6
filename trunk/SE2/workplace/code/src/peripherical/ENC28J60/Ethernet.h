#ifndef __ETHERNET_H_
#define __ETHERNET_H_
#include "SPI.h"
#define MAX_FRAME_LEN   1518
#define MAX_TX_RETRY    10

#define __ETHERNET_RX_START_PTR__        0x0000
#define __ETHERNET_RX_END_PTR__          0x0FFF
#define __ETHERNET_TX_START_PTR__        0x1000
#define __ETHERNET_TX_END_PTR__          0x1F00 


#define __ETHERNET_RX_BUFFER_SIZE__   4096
#define __ETHERNET_TX_BUFFER_SIZE__   4096

#define MAC_NBR_BYTES 6
typedef enum{
	ETHERNET_OK=0,
	ETHERNET_NULL_POINTER=1,
	ETHERNET_ZERO_SIZE_PACKET=2,
	ETHERNET_PACKET_TOO_LONG=3,
	ETHERNET_MAC_NULL_POINTER=4,
    ETHERNET_SPI_INIT_ERROR=5
}ETHERNET_ERRORS;

typedef enum{
    ETHERNET_HALF_DUPLEX = 0,
    ETHERNET_FULL_DUPLEX = 1
}ETHERNET_COM_SYSTEM;

typedef struct{
    SPI_Device ethernetDevice;
    ETHERNET_COM_SYSTEM duplex;
    U8 mac[MAC_NBR_BYTES] ;        
}ETHERNET_Device,*pETHERNET_Device;


U8 Ethernet_init(pETHERNET_Device ethernetDevice);
U8 Ethernet_send_buffer(U8* packet, U16 packetsize);
/*U32 Ethernet_receive(U8* buffer, U32 buffer_size,U32* read_size);*/
U32 Ethernet_receive_buffer(U8* buffer, U32 buffer_size);

void ethernetIsr(void) __attribute__ ((interrupt));
U32 Ethernet_receive(U8* buffer, U32 buffer_size);
U8	Ethernet_send(U8* packet, U16 packet_size);

#endif
