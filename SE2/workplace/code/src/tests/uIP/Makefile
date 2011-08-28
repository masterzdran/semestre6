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
#															test
#=======================================================================
#Shell Path
SHELL			= /bin/sh
#Environmental Paths
SVN_PATH		= ./../../../..
#=======================================================================
PROJECT_PATH	= $(SVN_PATH)/code
#=======================================================================
include $(PROJECT_PATH)/common.mk
#=======================================================================
#Phony Target
.PHONY 					= clean
.PHONY					= clear
#=======================================================================

all: test_uIP.o

test_uIP.o: test_uIP.c test_uIP.h
	@echo "----------------------------------------------------------------------"
	$(CC)  $(COPTIONS)  $(SEARCHLIB) $(SEARCHINCLUDE) -I$(SVN_PATH)/code/src/uip-1.0/apps/webserver $(DEBUGSYMBOLS) $(COMPILE_ONLY) $(OUTPUT) $@  $<
	cp $@ $(PROGRAM)/$@
	cp test_uIP.h $(INCLUDE)/
	
clean:
	@echo "----------------------------------------------------------------------"
	rm  test_uIP.o
	rm  $(INCLUDE)/test_uIP.h
	
clear:
	clear
