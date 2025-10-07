TARGET = teste
AVRDUDE = avrdude

SRCS = init.c main.c  # <--- ATUALIZADO: Inclui os dois ficheiros C

OBJS = $(SRCS:.c=.o)

CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size

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
	$(OBJCOPY) -O ihex -R .eeprom $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).hex
fuses:
	$(AVRDUDE) -p m328p -c usbasp -U lfuse:w:0xFF:m -U hfuse:w:0xDE:m -U efuse:w:0xFD:m
upload: $(TARGET).hex
	$(AVRDUDE) -p m328p -c usbasp -U flash:w:$(TARGET).hex:i