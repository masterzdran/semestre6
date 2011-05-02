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
PERIPHERICAL			= $(SOURCE)/peripherical
DEBUGGER			= $(SOURCE)/debugger
TODEPLOY			= $(SOURCE)/deploy
PROGRAM				= $(SOURCE)/program
PCOMPILE			= $(SOURCE)/tests
TARGET				= $(PROJECT_PATH)/target
TEST				= $(PROJECT_PATH)/test
#=======================================================================
MYLIB			= $(SOURCE)/lib
INCLUDE			= $(SOURCE)/include
CLIB			= $(SOURCE)/clib/lib
CINCLUDE		= $(SOURCE)/clib/inc
HEADER			= 
SEARCHLIB		= -I$(MYLIB) -I$(INCLUDE)
#Executables
CC 				= arm-eabi-gcc
AS				= arm-eabi-as
LD				= arm-eabi-ld
AR				= arm-eabi-ar rcs
OPENOCD			= openocd
#Debugger
#DEBUGGER		= arm-eabi-insight
#Commom Options
OUTPUT 				= -o
LDSCRIPT			= -T  
DEBUGSTABS			= --gstabs
DEBUGSYMBOLS		= -g
COPTIONS 			= -Wall -pedantic
COMPILE_ONLY 		= -c 

