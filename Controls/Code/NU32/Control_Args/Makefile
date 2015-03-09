XC32PATH=/opt/microchip/xc32/v1.34/bin
HARMONYPATH=/home/harntson/microchip/harmony/v1_02
NU32PATH=/home/harntson/MechE333/PIC32quickstart
PORTA=/dev/ttyUSB0
PORTB=/dev/ttyUSB1
TERMEMU=screen
#This file is used to:
#	1. compile .c files into .o files
#	2. link the .o files into a .elf binary
#	3. convert the .elf into a .hex
#	4. write the .hex file to the pic using the bootloader utility
# The following must be edited by you so that
# make knows where to find the compiler tools (xc32)
# and the harmony library.
#
# XC32PATH is the path to the xc32 bin directory. This directory contains
# tools such as the compiler (xc32-gcc) and hex converter 
# (xc32-bin2hex)
# Windows example (note the use of slashes not backslashes):
# XC32PATH=C:/Program Files (x86)/Microchip/xc32/v1.34/bin
# Mac example:
# XC32PATH =/Applications/microchip/xc32/v1.34/bin
#
# HARMONYPATH is the path to the harmony framework directory
# Windows example:
# HARMONYPATH=C:/Program Files (x86)/Microchip/harmony/v1_01
# Mac example:
# HARMONYPATH=/Users/kevin/harmony/v1_01
#
# NU32PATH is the path to the nu32utility.
# You compiled this and named it nu32utility
# Example:
# if your nu32utility is in
# /home/student/PIC32/nu32utilty, then
# NU32PATH=/home/student/PIC32
#
# PORTA is the COM port used by programs on the PIC32
# This is the lower numbered port (or the A port on Mac)
# Windows Example:
# PORTA=\\.\COM22
# Mac Example:
# PORTA=/dev/tty.usbserial=00001024A
#
# PORTB is the Serial port for the bootloader
# This is the higher numbered port (or the B port on Mac)
# Windows Example:
# PORTB=\\.\COM23
# Mac Example:
# PORTB=/dev/tty.usbserial-00001024B
#
# TERMEMU is your terminal emulator
# Windows example:
# TERMEMU=C:/Program Files (x86)/PuTTY/putty.exe
# Mac example (screen is pre-installed and already on your execution path 
# so you can safely omit the full path)
# TERMEMU=screen
#END user configurable variables

#the c compiler
CC="$(XC32PATH)/xc32-gcc"

#the hexfile maker
HX="$(XC32PATH)/xc32-bin2hex"

#object dumper
OBJDMP="$(XC32PATH)/xc32-objdump"

#the bootloader utility
WRITE="$(NU32PATH)/nu32utility"

#the linker script
LINKSCRIPT = "NU32bootloaded.ld"
OBJS := $(patsubst %.c, %.o,$(wildcard *.c))
HDRS := $(wildcard *.h)
PROC = 32MX795F512L
CFLAGS=-g -O1 -x c 
TARGET = out

#if on windows use a different RM
ifdef ComSpec
	RM = del /Q
endif

#what to do when make all
.PHONY : all
all : $(TARGET).hex $(TARGET).dis
# Turn the elf file into a hex file.
$(TARGET).hex : $(TARGET).elf
	@echo Creating hex file
	$(HX) $(TARGET).elf

$(TARGET).dis : $(TARGET).elf
	$(OBJDMP) -S $< > $@

# Link all the object files into an elf file.
$(TARGET).elf : $(OBJS)
	@echo Linking elf file
	$(CC) -mprocessor=$(PROC) -o $(TARGET).elf $(OBJS) \
					-L"$(HARMONYPATH)/bin/framework/peripheral" \
					-l:PIC$(PROC)_peripherals.a \
              -Wl,--script=$(LINKSCRIPT),-Map=$(TARGET).map

# Create an object file for each C file.
%.o : %.c $(HDRS)
	@echo Creating object file $@
	$(CC) $(CFLAGS) -c -mprocessor=$(PROC) \
		-I"$(HARMONYPATH)/framework" -I"$(HARMONYPATH)/framework/peripheral" -o $@ $<

.PHONY: clean
# Erase all hex, map, object, and elf files.
clean :
	$(RM) *.hex *.map *.o *.elf *.dep *.dis       

.PHONY: write
# After making, call the NU32utility to program via bootloader.
write : $(TARGET).hex 
	$(WRITE) "$(PORTB)" $(TARGET).hex 

.PHONY: putty
putty :
	"$(TERMEMU)" -serial -sercfg 230400 "$(PORTA)"

.PHONY: screen
screen :
	"$(TERMEMU)" "$(PORTA)" 230400
