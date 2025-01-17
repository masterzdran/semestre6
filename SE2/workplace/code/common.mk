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
SOURCE				= $(PROJECT_PATH)/src
COLLECTION			= $(SOURCE)/collection
DEVICE				= $(SOURCE)/device
PERIPHERICAL		= $(SOURCE)/peripherical
DEBUGGER			= $(SOURCE)/debugger
TODEPLOY			= $(SOURCE)/deploy
PROGRAM				= $(SOURCE)/program
PCOMPILE			= $(SOURCE)/tests
#=======================================================================
#PECOS				= $(SOURCE)/eCos/
PECOS				= $(SOURCE)/
#=======================================================================
PUIP				= $(SOURCE)/uip-1.0/
#=======================================================================
TARGET				= $(PROJECT_PATH)/target
TEST				= $(PROJECT_PATH)/test
#=======================================================================
MYLIB			= $(SOURCE)/lib
INCLUDE			= $(SOURCE)/include
CLIB			= $(SOURCE)/clib/lib
CINCLUDE		= $(SOURCE)/clib/inc
ECOS_INCLUDE	= $(PECOS)/include_eCos
ECOS_LIBRARY    = $(PECOS)/lib_eCos
ECOS_TESTS		= $(PCOMPILE)/ecos
UIP_INCLUDE		= $(PUIP)/uip
UIP_LIBRARY		= $(PUIP)/lpc-2106
UIP_LPC			= $(PUIP)/lpc-2106
HEADER			= 
SEARCHINCLUDE	= -I$(ECOS_INCLUDE) -I$(INCLUDE) -I$(SOURCE)/include_eCos -I$(UIP_INCLUDE) -I$(UIP_LPC)
SEARCHLIB		= -L$(UIP_LIBRARY) -L$(ECOS_LIBRARY) -L$(SOURCE)/lib
VPATH 			= $(MYLIB):$(ECOS_LIBRARY)

#Executables
CC 				= arm-eabi-gcc
LD 				= arm-eabi-gcc
#AS				= arm-eabi-as
AS				= arm-eabi-gcc
#LD				= arm-eabi-ld
AR				= arm-eabi-ar rcs
OPENOCD			= openocd
#Debugger
#DEBUGGER		= arm-eabi-insight
#Commom Options
OUTPUT 				= -nostdlib  -o
LDSCRIPT			= -T  
DEBUGSTABS			= --gstabs
DEBUGSYMBOLS		= -g
COPTIONS 			= -Wall  -ffunction-sections -fdata-sections -fpack-struct -Wa,-a=$*.lst $(SEARCHINCLUDE)
LDFLAGS 			= $(SEARCHLIB) -Wl,--gc-sections -Wl,--Map -Wl,basic.map
COMPILE_ONLY 		= -c 






