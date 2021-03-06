#     upload your program to the Arduino board.
# Updated 08/06/2012 for JeeNode
# Updated to support Moteino Build

TARGET = $(notdir $(CURDIR))
INSTALL_DIR = /swpkg/avr/arduino-1.0.5
PORT = /dev/ttyBlue
# used for older boards may be depricated...
#AVRDUDE_PROGRAMMER = stk500v1
# used with newer boards
AVRDUDE_PROGRAMMER = arduino
#MCU = atmega168
#MCU = atmega168
MCU = atmega328p
#F_CPU = 16000000L
F_CPU = 16000000
UPLOAD_RATE = 115200


############################################################################
# Below here nothing should be changed...

VERSION=100
ARDUINO = $(INSTALL_DIR)/hardware/arduino/cores/arduino
AVR_TOOLS_PATH = $(INSTALL_DIR)/hardware/tools/avr/bin
#AVR_TOOLS_PATH = /usr/bin
# AVR_TOOLS_PATH = /usr/bin
#AVRDUDE_PATH = $(INSTALL_DIR)/hardware/tools/avr/bin
#AVRDUDE_PATH = /usr/local/bin
AVRDUDE_PATH = /swpkg/avr/current/hardware/tools/
C_MODULES =  \
$(ARDUINO)/wiring_pulse.c \
$(ARDUINO)/wiring_analog.c \
$(ARDUINO)/wiring.c \
$(ARDUINO)/wiring_digital.c \
$(ARDUINO)/WInterrupts.c \
$(ARDUINO)/wiring_shift.c \
# end of C_MODULES

CXX_MODULES = \
$(ARDUINO)/Tone.cpp \
$(ARDUINO)/main.cpp \
$(ARDUINO)/WMath.cpp \
$(ARDUINO)/Print.cpp \
$(ARDUINO)/HardwareSerial.cpp \
$(INSTALL_DIR)/libraries/EEPROM/EEPROM.cpp \
$(INSTALL_DIR)/libraries/Ethernet/EthernetClient.cpp \
$(INSTALL_DIR)/libraries/Ethernet/Ethernet.cpp \
$(INSTALL_DIR)/libraries/Ethernet/EthernetServer.cpp \
$(INSTALL_DIR)/libraries/Firmata/Firmata.cpp \
$(INSTALL_DIR)/libraries/LiquidCrystal/LiquidCrystal.cpp \
$(INSTALL_DIR)/libraries/Servo/Servo.cpp \
$(INSTALL_DIR)/libraries/Stepper/Stepper.cpp \
$(INSTALL_DIR)/libraries/Wire/Wire.cpp  \
$(INSTALL_DIR)/libraries/SoftwareSerial/SoftwareSerial.cpp  \
$(INSTALL_DIR)/libraries/IR/IRremote.cpp  \
$(INSTALL_DIR)/libraries/RFM12B/RFM12B.cpp  \
$(INSTALL_DIR)/libraries/SPIFlash/SPIFlash.cpp  \
$(INSTALL_DIR)/libraries/SPI/SPI.cpp  \
$(INSTALL_DIR)/libraries/RFM69/RFM69.cpp  \
$(INSTALL_DIR)/libraries/LowPower/LowPower.cpp  \
#$(INSTALL_DIR)/libraries/JeeLib/RF12.cpp  \
#$(INSTALL_DIR)/libraries/JeeLib/Ports.cpp  \
# end of CXX_MODULES

CXX_APP = applet/$(TARGET).cpp
MODULES = $(C_MODULES) $(CXX_MODULES)
SRC = $(C_MODULES)
CXXSRC = $(CXX_MODULES) $(CXX_APP)
FORMAT = ihex


# Name of this Makefile (used for "make depend").
MAKEFILE = Makefile

# Debugging format.
# Native formats for AVR-GCC's -g are stabs [default], or dwarf-2.
# AVR (extended) COFF requires stabs, plus an avr-objcopy run.
#DEBUG = stabs
DEBUG =

OPT = s

# Place -D or -U options here
CDEFS = -DF_CPU=$(F_CPU)L -DARDUINO=$(VERSION)
CXXDEFS = -DF_CPU=$(F_CPU)L -DARDUINO=$(VERSION)

#AVR_HEADERS = $(INSTALL_DIR)/hardware/tools/avr/avr/include/avr
AVR_HEADERS = $(INSTALL_DIR)/hardware/arduino/variants/standard/
ARDUINO_LIB_INCLUDES = \
-I$(INSTALL_DIR)/libraries/EEPROM \
-I$(INSTALL_DIR)/libraries/Ethernet \
-I$(INSTALL_DIR)/libraries/Ethernet/utility \
-I$(INSTALL_DIR)/libraries/Firmata \
-I$(INSTALL_DIR)/libraries/LiquidCrystal \
-I$(INSTALL_DIR)/libraries/SPI \
-I$(INSTALL_DIR)/libraries/Servo \
-I$(INSTALL_DIR)/libraries/SoftwareSerial \
-I$(INSTALL_DIR)/libraries/Wire \
-I$(INSTALL_DIR)/libraries/IR \
-I$(INSTALL_DIR)/libraries/RFM12B \
-I$(INSTALL_DIR)/libraries/RFM69 \
-I$(INSTALL_DIR)/libraries/SPIFlash \
-I$(INSTALL_DIR)/libraries/SPI \
-I$(INSTALL_DIR)/libraries/LowPower \
-I$(INSTALL_DIR)/libraries/FoxNet \
-I$(INSTALL_DIR)/libraries/Wire/utility
#-I$(INSTALL_DIR)/libraries/JeeLib \

# Place -I options here
CINCS = -I$(CURDIR) -I$(ARDUINO) $(ARDUINO_LIB_INCLUDES) -I$(AVR_HEADERS)
CXXINCS = -I$(CURDIR) -I$(ARDUINO) $(ARDUINO_LIB_INCLUDES) -I$(AVR_HEADERS)

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
#CSTANDARD = -std=gnu99
CDEBUG = -g$(DEBUG)
#CWARN = -Wall -Wstrict-prototypes
#CWARN = -Wall   # show all warnings
CWARN = -w      # suppress all warnings
####CTUNING = -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CTUNING = -ffunction-sections -fdata-sections
CXXTUNING = -fno-exceptions -ffunction-sections -fdata-sections
#CEXTRA = -Wa,-adhlns=$(<:.c=.lst)

CFLAGS = $(CDEBUG) -O$(OPT) $(CWARN) $(CTUNING) $(CDEFS) $(CINCS) $(CSTANDARD) $(CEXTRA)
CXXFLAGS = $(CDEBUG) -O$(OPT) $(CWARN) $(CXXTUNING) $(CDEFS) $(CINCS)
#ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs
LDFLAGS = -O$(OPT) -lm -Wl,--gc-sections


# Programming support using avrdude. Settings and variables.
AVRDUDE_PORT = $(PORT)
AVRDUDE_WRITE_FLASH = -U flash:w:applet/$(TARGET).hex

#AVRDUDE_FLAGS = -V -F -C $(INSTALL_DIR)/hardware/tools/avr/etc/avrdude.conf \

#AVRDUDE_FLAGS = -F -C /etc/avrdude.conf 
AVRDUDE_FLAGS = -F -C $(INSTALL_DIR)/hardware/tools/avrdude.conf \
-p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) \
-b $(UPLOAD_RATE)

# Program settings
CC = $(AVR_TOOLS_PATH)/avr-gcc
CXX = $(AVR_TOOLS_PATH)/avr-g++
LD = $(AVR_TOOLS_PATH)/avr-gcc
OBJCOPY = $(AVR_TOOLS_PATH)/avr-objcopy
OBJDUMP = $(AVR_TOOLS_PATH)/avr-objdump
AR  = $(AVR_TOOLS_PATH)/avr-ar
SIZE = $(AVR_TOOLS_PATH)/avr-size
NM = $(AVR_TOOLS_PATH)/avr-nm
#AVRDUDE = /usr/bin/avrdude
AVRDUDE = $(AVRDUDE_PATH)/avrdude
REMOVE = rm -f
MV = mv -f

# Define all object files.
OBJ = $(SRC:.c=.o) $(CXXSRC:.cpp=.o) $(ASRC:.S=.o)
OBJ_MODULES = $(C_MODULES:.c=.o) $(CXX_MODULES:.cpp=.o)

# Define all listing files.
LST = $(ASRC:.S=.lst) $(CXXSRC:.cpp=.lst) $(SRC:.c=.lst)

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = $(CFLAGS) -mmcu=$(MCU)
ALL_CXXFLAGS = $(CXXFLAGS) -mmcu=$(MCU)
ALL_ASFLAGS = -x assembler-with-cpp $(ASFLAGS) -mmcu=$(MCU)
ALL_LDFLAGS = $(LDFLAGS) -mmcu=$(MCU)

# Default target.
all: clean applet_files build sizeafter upload



build: elf hex

#applet_files: $(TARGET).pde
applet/$(TARGET).cpp: $(TARGET).cc
	# Here is the "preprocessing".
	# It creates a .cpp file based with the same name as the .pde file.
	# On top of the new .cpp file comes the WProgram.h header.
	# and prototypes for setup() and Loop()
	# Then the .cpp file will be compiled. Errors during compile will
	# refer to this new, automatically generated, file.
	# Not the original .pde file you actually edit...
	test -d applet || mkdir applet
	echo '#include "Arduino.h"' > applet/$(TARGET).cpp
	echo 'void setup();' >> applet/$(TARGET).cpp
	echo 'void loop();' >> applet/$(TARGET).cpp
	cat $(TARGET).cc >> applet/$(TARGET).cpp

elf: applet/$(TARGET).elf
hex: applet/$(TARGET).hex
eep: applet/$(TARGET).eep
lss: applet/$(TARGET).lss
sym: applet/$(TARGET).sym

# Program the device.  
upload: applet/$(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)


	# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) applet/$(TARGET).hex
ELFSIZE = $(SIZE)  applet/$(TARGET).elf
sizebefore:
	@if [ -f applet/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(HEXSIZE); echo; fi

sizeafter:
	@if [ -f applet/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(HEXSIZE); echo; fi


# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
--change-section-address .data-0x800000 \
--change-section-address .bss-0x800000 \
--change-section-address .noinit-0x800000 \
--change-section-address .eeprom-0x810000


coff: applet/$(TARGET).elf
	$(COFFCONVERT) -O coff-avr applet/$(TARGET).elf $(TARGET).cof


extcoff: $(TARGET).elf
	$(COFFCONVERT) -O coff-ext-avr applet/$(TARGET).elf $(TARGET).cof


.SUFFIXES: .elf .hex .eep .lss .sym

.elf.hex:
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

.elf.eep:
	$(OBJCOPY) -O $(FORMAT) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--no-change-warnings \
	--change-section-lma .eeprom=0 $< $@

# Create extended listing file from ELF output file.
.elf.lss:
	$(OBJDUMP) -h -S $< > $@

# Create a symbol table from ELF output file.
.elf.sym:
	$(NM) -n $< > $@

	# Link: create ELF output file from library.
#applet/$(TARGET).elf: $(TARGET).pde applet/core.a
applet/$(TARGET).elf: applet/$(TARGET).o applet/core.a
	$(LD) $(ALL_LDFLAGS) -o $@ applet/$(TARGET).o applet/core.a

applet/core.a: $(OBJ_MODULES)
	@for i in $(OBJ_MODULES); do echo $(AR) rcs applet/core.a $$i; $(AR) rcs applet/core.a $$i; done



# Compile: create object files from C++ source files.
.cpp.o:
	$(CXX) -c $(ALL_CXXFLAGS) $< -o $@

# Compile: create object files from C source files.
.c.o:
	$(CC) -c $(ALL_CFLAGS) $< -o $@


# Compile: create assembler files from C source files.
.c.s:
	$(CC) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
.S.o:
	$(CC) -c $(ALL_ASFLAGS) $< -o $@


# Automatic dependencies
%.d: %.c
	$(CC) -M $(ALL_CFLAGS) $< | sed "s;$(notdir $*).o:;$*.o $*.d:;" > $@

%.d: %.cpp
	$(CXX) -M $(ALL_CXXFLAGS) $< | sed "s;$(notdir $*).o:;$*.o $*.d:;" > $@


# Target: clean project.
clean:
	$(REMOVE) applet/$(TARGET).hex applet/$(TARGET).eep applet/$(TARGET).cof applet/$(TARGET).elf \
	applet/$(TARGET).map applet/$(TARGET).sym applet/$(TARGET).lss applet/core.a \
	$(OBJ) $(LST) $(SRC:.c=.s) $(SRC:.c=.d) $(CXXSRC:.cpp=.s) $(CXXSRC:.cpp=.d)

.PHONY:	all build elf hex eep lss sym program coff extcoff clean applet_files sizebefore sizeafter

#include $(SRC:.c=.d)
#include $(CXXSRC:.cpp=.d)
