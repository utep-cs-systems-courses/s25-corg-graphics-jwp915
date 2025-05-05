TOOLCHAIN = /Applications/ti/msp430-gcc/bin
CC = $(TOOLCHAIN)/msp430-elf-gcc
AS = $(TOOLCHAIN)/msp430-elf-as
OBJCOPY = $(TOOLCHAIN)/msp430-elf-objcopy

MCU = msp430g2553
INCLUDEDIR = /Applications/ti/msp430-gcc/include
CFLAGS = -mmcu=$(MCU) -I$(INCLUDEDIR) -O2
ASFLAGS = -mmcu=$(MCU)

SOURCES = main.c lcd.c delay.asm button.asm buzzer.asm
OBJECTS = $(SOURCES:.c=.o)
OBJECTS := $(OBJECTS:.asm=.o)

TARGET = game.elf
BINARY = game.hex

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -T msp430g2553.ld -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

hex: $(TARGET)
	$(OBJCOPY) -O ihex $(TARGET) $(BINARY)

clean:
	rm -f *.o *.elf *.hex

flash:
	mspdebug rf2500 "prog game.hex"
