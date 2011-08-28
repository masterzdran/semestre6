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
#=======================================================================
#					Base Make Test
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
MAKEPATHS				= ENC28J60_eCos 

#=======================================================================
#			
#=======================================================================
all: 

	@echo "=================================="
	@echo "Compiling the Program"
	@echo "=================================="	
#$(MAKE) -C lcd-test/
#$(MAKE) -C Tacografo/
#$(MAKE) -C test/
	$(MAKE) -C uIP/

	
clean:
	@echo "=================================="
	@echo "Cleaning the Program"
	@echo "=================================="	
#$(MAKE) -C lcd-test/ clean	
#$(MAKE) -C Tacografo/ clean	
#$(MAKE) -C test/ clean	
	$(MAKE) -C uIP/ clean	
clear:
	clear
