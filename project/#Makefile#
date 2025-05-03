# Target MCU and Compiler
MCU = msp430g2553
CC = msp430-gcc
AS = msp430-as
LD = msp430-ld
OBJCOPY = msp430-objcopy

CFLAGS = -mmcu=$(MCU) -O2
ASFLAGS = -mmcu=$(MCU)

# Source and Output
SOURCES_C = main.c lcd.c
SOURCES_ASM = delay.asm button.asm buzzer.asm
OBJECTS = $(SOURCES_C:.c=.o) $(SOURCES_ASM:.asm=.o)
TARGET = game.elf
BINARY = game.hex

# Default target
all: $(TARGET)

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble ASM files
%.o: %.asm
	$(CC) $(CFLAGS) -c $< -o $@

# Link everything
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Convert ELF to HEX
hex: $(TARGET)
	$(OBJCOPY) -O ihex $< $(BINARY)

# Flash the device (assumes mspdebug is installed and using rf2500 interface)
flash: hex
	mspdebug rf2500 "prog $(BINARY)"

# Clean build files
clean:
	rm -f *.o *.elf *.hex
