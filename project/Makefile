# === Configuration ===
CPU        = msp430g2553
CC         = msp430-elf-gcc
AS         = msp430-elf-gcc
CFLAGS 	   = -mmcu=$(CPU) -Os -I. -I./toy -I./timerLib -I../lcdLib
ASFLAGS    = -mmcu=$(CPU)
LDFLAGS    = -mmcu=$(CPU)
TARGET     = wakedemo.elf

# === File discovery ===
C_SRCS  := $(filter-out wakedemo_off.c toy/buttonMain.c toy/switches.c ../lcdLib/lcddemo.c, $(wildcard *.c toy/*.c timerLib/*.c ../lcdLib/*.c))
S_SRCS  := $(wildcard *.s toy/*.s timerLib/*.s)
OBJS    := $(C_SRCS:.c=.o) $(S_SRCS:.s=.o)

# === Build Rules ===
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -c -o $@ $<

# === Extra Rules ===
load: $(TARGET)
	msp430loader.sh $^

clean:
	rm -f $(OBJS) $(TARGET)
