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
#											Base Dir MakeFile
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
.PHONY				= debugger
.PHONY				= peripherical
.PHONY				= device
.PHONY				= program
.PHONY				= deploy
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

VPATH 			= $(MYLIB):$(CLIB):$(libdir)
#VPATH 			= $(MYLIB)
#=======================================================================
LIBOBJECT =		libc.a libgcc.a  libLPC2106.a libPeripherical.a libDebugger.a
OBJECT =		$(MYLIB)/start.o $(PROGRAM)/test.o $(MYLIB)/console.o
#=======================================================================
all: $(END_EXEC) 

#Generate the executable
#$(OBJECT)
$(END_EXEC): program 
	cp src/device/STARTUP/start.o src/lib/start.o
#	$(LD) $(LDSCRIPT) $(LDSCRIPT_FILE) $(OUTPUT) $@  $(MYLIB)/start.o $(PROGRAM)/tacografo.o -L$(MYLIB) -lPeripherical -lLPC2106 -lc -lgcc
	$(LD) $(LDSCRIPT) $(LDSCRIPT_FILE) $(OUTPUT) $@  $(OBJECT) -L$(MYLIB) -lPeripherical -lLPC2106 -lc -lgcc

peripherical: device
	@echo "----------------------------------------------------------------------"
	$(MAKE) -C $(PERIPHERICAL)

debugger: peripherical
	@echo "----------------------------------------------------------------------"
	$(MAKE) -C $(DEBUGGER)

device:
	@echo "----------------------------------------------------------------------"
	$(MAKE) -C $(DEVICE)
	
program:  device peripherical debugger
	@echo "----------------------------------------------------------------------"
	$(MAKE) -C $(PCOMPILE)

#Start the Debugger	
#debug: 
#	@echo "----------------------------------------------------------------------"
#	@echo $(DEBUGGER) $(END_EXEC)
#	$(DEBUGGER) --cd=$(TARGET) --exec=$(EXEC)

#clean files
clean:
	@echo "----------------------------------------------------------------------"
	$(MAKE) -C $(DEVICE) clean
	$(MAKE) -C $(PERIPHERICAL) clean
	$(MAKE) -C $(DEBUGGER) clean	
	$(MAKE) -C $(PCOMPILE) clean

deploy: $(END_EXEC)
	$(OPENOCD) -f $(OPENOCD_FILE) -c "flash write_image erase $^" -c "sleep 100" -c "reset run" -c "shutdown"

clear:
	clear
