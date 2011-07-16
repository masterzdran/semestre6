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
#															ENC28J60
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
all: ENC28J60.o ETHERNET.o

ENC28J60.o: ENC28J60.c ENC28J60.h
	$(CC)  $(COPTIONS) $(SEARCHLIB) $(DEBUGSYMBOLS) $(COMPILE_ONLY) $(OUTPUT) $@  $< 
	cp $@ $(MYLIB)/$@
	cp ENC28J60.h $(INCLUDE)/
	
ETHERNET.o: Ethernet.c Ethernet.h	
	$(CC)  $(COPTIONS) $(SEARCHLIB) $(DEBUGSYMBOLS) $(COMPILE_ONLY) $(OUTPUT) $@  $< 
	cp $@ $(MYLIB)/$@
	cp Ethernet.h $(INCLUDE)/

clean:
	rm  ENC28J60.o
	rm  $(INCLUDE)/ENC28J60.h
	rm  ETHERNET.o
	rm  $(INCLUDE)/Ethernet.h

clear:
	clear
