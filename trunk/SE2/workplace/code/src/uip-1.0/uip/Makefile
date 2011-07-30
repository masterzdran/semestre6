BASE_DIR	= ../..
INSTALL_DIR	= $(BASE_DIR)/eCos/

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

APPS   = webserver
CFLAGS = -Wall -g -I../uip -I. -fpack-struct -Os


ifdef APPS
  APPDIRS = $(foreach APP, $(APPS), ../apps/$(APP))
  -include $(foreach APP, $(APPS), ../apps/$(APP)/Makefile.$(APP))
  CFLAGS += $(addprefix -I../apps/,$(APPS))
endif

ifndef CCDEP
  CCDEP = $(CC)
endif
ifndef CCDEPCFLAGS
  CCDEPCFLAGS = $(CFLAGS)
endif
ifndef OBJECTDIR
  OBJECTDIR = obj
endif

ifeq (${wildcard $(OBJECTDIR)},)
  DUMMY := ${shell mkdir $(OBJECTDIR)}
endif


vpath %.c . ../uip ../lib $(APPDIRS)

$(OBJECTDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTDIR)/%.d: %.c
	@set -e; rm -f $@; \
	$(CCDEP) -MM $(CCDEPCFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(OBJECTDIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

UIP_SOURCES=uip.c uip_arp.c uiplib.c psock.c timer.c uip-neighbor.c


ifneq ($(MAKECMDGOALS),clean)
-include $(addprefix $(OBJECTDIR)/,$(UIP_SOURCES:.c=.d) \
                                   $(APP_SOURCES:.c=.d))
endif

uip.a: ${addprefix $(OBJECTDIR)/, $(UIP_SOURCES:.c=.o)}
	$(AR) rcf $@ $^

apps.a: ${addprefix $(OBJECTDIR)/, $(APP_SOURCES:.c=.o)}
	$(AR) rcf $@ $^
