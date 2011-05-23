#=======================================================================
# SE1   - Sistemas Embebidos 1
#-----------------------------------------------------------------------
# Turma:	LI51N
# Semestre:	Inverno 2010/2011
# Data:		Novembro/2010
#-----------------------------------------------------------------------
# Nome: 	Nuno Cancelo
# Numero:	31401
#-----------------------------------------------------------------------
# Nome:		Nuno Sousa
# Numero:	33595
#-----------------------------------------------------------------------
# LEIC  - Licenciatura em Engenharia Informática e Computadores
# DEETC - Dep. de Eng. Electrónica e Telecomunicações e Computadores
# ISEL  - Instituto Superior de Engenharia de Lisboa
#=======================================================================
#						Base Dir MakeFile
#=======================================================================
#Shell Path
SHELL			= /bin/sh
#Environmental Paths
SVN_PATH		= ./..
#=======================================================================
PROJECT_PATH	= $(SVN_PATH)/code
#Phony Target
.PHONY 				= clean
.PHONY				= clear
#=======================================================================
include $(PROJECT_PATH)/common.mk
#=======================================================================
LDS_PATH		=  	$(TODEPLOY)/ldscript
OPENOCD_FILE	=	$(TODEPLOY)/openocd/openocd_lpc2106.cfg
#Set the Correct LdScript
ifdef ROM
LDSCRIPT_FILE	= $(LDS_PATH)/ldscript_rom
EXEC				= rom.elf
END_EXEC		= $(TARGET)/rom.elf
else
LDSCRIPT_FILE	= $(LDS_PATH)/ldscript_ram
EXEC				= ram.elf
END_EXEC		= $(TARGET)/ram.elf
endif
#=======================================================================
#LIBOBJECT =		libc.a libgcc.a  libLPC2106.a libPeripherical.a libDebugger.a
LYBRARIES = 	 -lc -lgcc -lLPC2106  -lPeripherical
OBJECT =		$(MYLIB)/start.o $(PROGRAM)/test.o $(MYLIB)/console.o  $(MYLIB)/BUFFER.o
LD_OPTIONS=		-Ttarget.ld -nostdlib
#$(MYLIB)/BUFFER.o
#=======================================================================
all: $(END_EXEC) 

#Generate the executable
#$(OBJECT)

%.o: %.c
	$(CC) $(COMPILE_ONLY) $(OUTPUT) $*.o $(COPTIONS) $<

OBJECTS = hello.o

$(END_EXEC):  $(OBJECTS)
#	cp src/device/STARTUP/start.o src/lib/start.o
	$(LD) $(OUTPUT) $@ $(LDFLAGS) $(LD_OPTIONS) $(OBJECTS)

#Start the Debugger	
#debug: 
#	@echo "----------------------------------------------------------------------"
#	@echo $(DEBUGGER) $(END_EXEC)
#	$(DEBUGGER) --cd=$(TARGET) --exec=$(EXEC)

#clean files
clean:
	@echo "----------------------------------------------------------------------"


deploy: $(END_EXEC)
	$(OPENOCD) -f $(OPENOCD_FILE) -c "flash write_image erase $^" -c "sleep 100" -c "reset run" -c "shutdown"

clear:
	clear
