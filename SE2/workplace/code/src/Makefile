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
#						Base Make Source
#=======================================================================
#Shell Path
SHELL			= /bin/sh
#Environmental Paths
SVN_PATH		= ./../..
#=======================================================================
PROJECT_PATH	= $(SVN_PATH)/code
#=======================================================================
include $(PROJECT_PATH)/common.mk
#=======================================================================
#Phony Target
.PHONY 					= clean
.PHONY					= clear
.PHONY					= all
MAKE_DEVICE				= device  
MAKE_PERIPHERICAL		= peripherical 
MAKE_UIP					= uip-1.0/lpc-2106
#=======================================================================

all:
	@$(foreach MPATH, $(MAKE_DEVICE), $(MAKE) -C $(SOURCE)/$(MPATH);)
	@$(foreach MPATH, $(MAKE_PERIPHERICAL), $(MAKE) -C $(SOURCE)/$(MPATH);)
	@echo "=============================================================================================================================================="
	@echo "Compiling the uIP and WebServer example"
	@echo "=============================================================================================================================================="	
	@$(foreach MPATH, $(MAKE_UIP), $(MAKE) -C $(SOURCE)/$(MPATH);)
	cp uip-1.0/lpc-2106/apps.a lib/libapps.a
	cp uip-1.0/lpc-2106/uip.a lib/libuip.a	
clean:
	@$(foreach MPATH, $(MAKE_DEVICE), $(MAKE) -C $(SOURCE)/$(MPATH) clean;)
	@$(foreach MPATH, $(MAKE_PERIPHERICAL), $(MAKE) -C $(SOURCE)/$(MPATH) clean;)
	@echo "=============================================================================================================================================="
	@echo "Cleaning the uIP and WebServer example"
	@echo "=============================================================================================================================================="
	@$(foreach MPATH, $(MAKE_UIP), $(MAKE) -C $(SOURCE)/$(MPATH) clean;)
clear:
	clear

