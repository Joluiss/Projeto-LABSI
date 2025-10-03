TARGET = teste

SRCS = init.c test.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -g

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
