TARGET = teste

SRCS = init.c test.c

OBJS = $(SRCS:.c=.o)

CC = avr-gcc
OBJCOPY = avr - objcopy
SIZE = avr- size

MCU = atmega328p
F_CPU = 16000000UL

CFLAGS = -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)

OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	$(SIZE) -C --mcu=$(MCU) $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -o ihex -R .eeprom $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).hex
