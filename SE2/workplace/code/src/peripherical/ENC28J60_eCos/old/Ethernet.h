#ifndef __ETHERNET_H_
#define __ETHERNET_H_
/*#include "SPI_Public.h"*/
#include <cyg/io/spi_lpc2xxx.h>
#include "TYPES.h"
#include "ENC28J60.h"

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
    cyg_spi_lpc2xxx_dev_t* ethernetDevice;
    ETHERNET_COM_SYSTEM duplex;
    cyg_uint8 mac[MAC_NBR_BYTES];
}ETHERNET_Device,*pETHERNET_Device;


U8 Ethernet_init(pETHERNET_Device ethernetDevice);
/*U32 Ethernet_receive(U8* buffer, U32 buffer_size,U32* read_size);*/

void ethernetIsr(void) __attribute__ ((interrupt));
U32 Ethernet_receive(PU8 buffer, U32 buffer_size);
U8	Ethernet_send(PU8 packet, U16 packet_size);

#endif
