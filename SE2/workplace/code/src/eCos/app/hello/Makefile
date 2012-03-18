#	Instituto Superior de Engenharia de Lisboa
#	Ezequiel Conde, 2012

#	Makefile para geração de aplicações eCos baseadas em
#	múltiplos ficheiros fonte distribuidos por várias directorias

BASE_DIR	=../../..
INSTALL_DIR	=$(BASE_DIR)/ecos/install/ecos1_install

CC			= $(ECOS_COMMAND_PREFIX)gcc
LD			= $(CC)

include $(INSTALL_DIR)/include/pkgconf/ecos.mak

CFLAGS	= -I$(INSTALL_DIR)/include -I$(UIP)/uip -I$(BASE_DIR)/ecos/mylib -I.
LDFLAGS	= -nostartfiles -L$(INSTALL_DIR)/lib -Ttarget.ld

VPATH	= $(BASE_DIR)/ecos/mylib:

# RULES

.PHONY: all clean

all: main

clean:
	-rm -f main *.o *~

%.o: %.c
	$(CC) -c -o $*.o $(CFLAGS) $(ECOS_GLOBAL_CFLAGS) $<

OBJECTS = main.o 

main: $(OBJECTS)
	$(LD) $(LDFLAGS) $(ECOS_GLOBAL_LDFLAGS) -o $@ $(OBJECTS)
