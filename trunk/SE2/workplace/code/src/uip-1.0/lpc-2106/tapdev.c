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
#include <stdio.h>
#include "GPIO.h"
#include "Ethernet.h"


ETHERNET_Device ethernetDevice ={
						NULL,
						ETHERNET_FULL_DUPLEX,
						{0x02, 0x6E, 0x75, 0x6E, 0x6F, 00}
						};


/*---------------------------------------------------------------------------*/
/*void tapdev_init(void){}*/

void tapdev_init(void)
{
	//gpio_init();
	Ethernet_init(&ethernetDevice);
}

/*---------------------------------------------------------------------------*/

void gpio_init(){
	cyg_uint32 iodir;
	/*activate gpio for CS, Reset*/
	GPIO_INIT_PINSEL0((CS_PIN | RESET));

	/*set dir to output for CS and Reset*/
	HAL_READ_UINT32((pGPIO)->IODIR, iodir);
	iodir = iodir | (CS_PIN | RESET);
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE+CYGARC_HAL_LPC2XXX_REG_IODIR, iodir);

	/*CS OFF & RESET OFF*/
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IOSET, CS_PIN);
	HAL_WRITE_UINT32(CYGARC_HAL_LPC2XXX_REG_IO_BASE + CYGARC_HAL_LPC2XXX_REG_IOSET, RESET);
}
/*---------------------------------------------------------------------------*/
/*unsigned int tapdev_read(void){return 0;}*/

unsigned int tapdev_read(void)
{
  int ret = Ethernet_receive(uip_buf, UIP_BUFSIZE);
  if(ret != 0) {
    printf("Ethernet: Ethernet_receive: read\n\r");
  }
  return ret;
}

/*---------------------------------------------------------------------------*/
/*void tapdev_send(void){}*/

void tapdev_send(void)
{
  int ret=Ethernet_send(uip_buf, uip_len);
  if(ret == 0) {
    printf("Ethernet: Ethernet_send: write\n\r");
  }
}

/*---------------------------------------------------------------------------*/
