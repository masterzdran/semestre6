/*
 * Copyright (c) 2001, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: tapdev.c,v 1.8 2006/06/07 08:39:58 adam Exp $
 */


#define UIP_DRIPADDR0   192
#define UIP_DRIPADDR1   168
#define UIP_DRIPADDR2   0
#define UIP_DRIPADDR3   1

#include "uip.h"
/*
#include "Ethernet.h"
ETHERNET_Device ethernetDevice ={
	 {
      0,									
      16,               					  
      1<<8,             					
      8,                					
      SPI_PRIOR_TO_FIRST_SCK_RISING_EDGE,   
      SPI_MASTER,    						
      0,                					
      SPI_MSB           					
	},
	ETHERNET_FULL_DUPLEX,
	{0x02, 0x65, 0x7A, 0x65, 0x71, 00}
};
*/
/*---------------------------------------------------------------------------*/
void tapdev_init(void){}
/*
void tapdev_init(void)
{
	Ethernet_init(ethernetDevice);

}
* */
/*---------------------------------------------------------------------------*/
unsigned int tapdev_read(void){return 0;}
/*
unsigned int tapdev_read(void)
{
  int ret = Ethernet_receive(uip_buf, UIP_BUFSIZE);
  if(ret == 0) {
    console_write_str("Ethernet: Ethernet_receive: read");
  }
  return ret;
}
* */
/*---------------------------------------------------------------------------*/
void tapdev_send(void){}
/*
void tapdev_send(void)
{
  int ret=Ethernet_send(uip_buf, uip_len);
  if(ret == -1) {
    console_write_str("Ethernet: Ethernet_send: write");
  }
}
* */
/*---------------------------------------------------------------------------*/
