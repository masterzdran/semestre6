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
#															Base Make
#=======================================================================
#Shell Path
SHELL			= /bin/sh
#Environmental Paths
SVN_PATH		= ./../../..
#=======================================================================
PROJECT_PATH	= $(SVN_PATH)/code
#=======================================================================
include $(PROJECT_PATH)/common.mk
#=======================================================================
#Phony Target
.PHONY 					= clean
.PHONY					= clear
.PHONY					= all
MAKEPATHS				= LPC2106 TYPES SCB STARTUP GPIO TIMER RTC I2C  VIC WD
#=======================================================================

all: 
	@echo "============================"
	@echo "Compiling the Device Library"
	@echo "============================"	
	@$(foreach MPATH, $(MAKEPATHS), $(MAKE) -C $(DEVICE)/$(MPATH);)
	$(AR) $(MYLIB)/libLPC2106.a $(MYLIB)/*.o
	@rm -rf $(MYLIB)/*.o	

clean:
	@echo "============================"
	@echo "Cleaning the Device Library"
	@echo "============================"	
	@$(foreach MPATH, $(MAKEPATHS), $(MAKE) -C $(DEVICE)/$(MPATH) clean;)
	@rm -rf $(MYLIB)/libLPC2106.a
	
clear:
	clear

