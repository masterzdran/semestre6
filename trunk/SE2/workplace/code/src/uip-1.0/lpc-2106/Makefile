# Copyright (c) 2001, Adam Dunkels.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote
#    products derived from this software without specific prior
#    written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
# GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# This file is part of the uIP TCP/IP stack.
#
# $Id: Makefile,v 1.13 2006/06/11 21:55:03 adam Exp $
#

all: mymain

BASE_DIR	= ../..
INSTALL_DIR	= $(BASE_DIR)/eCos

MYLIB			= $(BASE_DIR)/lib
INCLUDE			= $(BASE_DIR)/include

ECOS_INCLUDE		= $(INSTALL_DIR)/include
ECOS_LIBRARY    	= $(INSTALL_DIR)/lib


SEARCHINCLUDE	= -I$(ECOS_INCLUDE) -I$(INCLUDE) 
SEARCHLIB		= -L$(ECOS_LIBRARY)  -L$(MYLIB)
VPATH 			= $(MYLIB):$(ECOS_LIBRARY):.:../uip
CC = arm-eabi-gcc
GCC = arm-eabi-gcc
LD = arm-eabi-gcc
AR     = arm-eabi-ar

APPS   = webserver

EXTRACFLAGS   = -Wall -ffunction-sections -fdata-sections

LDFLAGS	      = -L$(INSTALL_DIR)/lib -Wl,--gc-sections -Wl,--Map -Wl,basic.map


CFLAGS = -Wall -g -I../uip -I. $(SEARCHINCLUDE) -fpack-struct -Os
-include ../uip/Makefile.include

mymain: $(addprefix $(OBJECTDIR)/, main.o tapdev.o clock-arch.o) apps.a uip.a

clean:
	rm -fr *.o *~ *core uip $(OBJECTDIR) *.a
