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
#															TIMER
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

all: TIMER_LPC.o


TIMER_LPC.o:TIMER_LPC.c TIMER_LPC.h 
	@echo "----------------------------------------------------------------------"
	$(CC)   $(COPTIONS)  $(SEARCHLIB) $(DEBUGSYMBOLS) $(COMPILE_ONLY) $(OUTPUT) $@  $< 
	cp $@ $(MYLIB)/$@
	cp TIMER_LPC.h $(INCLUDE)/
	
clean:
	@echo "----------------------------------------------------------------------"
	rm  TIMER_LPC.o
	rm  $(INCLUDE)/TIMER.h
	
	
clear:
	clear
