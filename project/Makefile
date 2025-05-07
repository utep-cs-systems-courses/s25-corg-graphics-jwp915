# === Configuration ===
CPU         = msp430g2553
CC          = /Applications/ti/msp430-gcc/bin/msp430-elf-gcc
AS          = /Applications/ti/msp430-gcc/bin/msp430-elf-as
OBJCOPY     = /Applications/ti/msp430-gcc/bin/msp430-elf-objcopy

CFLAGS      = -mmcu=$(CPU) -O2 -I/Applications/ti/msp430-gcc/include
LDFLAGS     = -T msp430g2553.ld

# === Source Files ===
SOURCES     = main.c lcd.c delay.asm button.asm buzzer.asm
OBJECTS     = main.o lcd.o delay.o button.o buzzer.o

# === Default Target ===
all: game.elf

# === Link Step ===
game.elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# === Flash Using mspdebug ===
load: game.elf
	sudo mspdebug tilib "prog $^"

# === Clean Build Artifacts ===
clean:
	rm -f *.o *.elf *.hex
