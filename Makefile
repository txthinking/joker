SRC = $(wildcard *.c)
SRC += $(wildcard lib/sds/*.c)
SRC += $(wildcard lib/str-starts-with.c/src/*.c)
SRC += $(wildcard lib/vec/src/*.c)
OBJS = $(SRC:.c=.o)
CFLAGS = -Ilib -Wall

joker: $(OBJS)
	gcc $(CFLAGS) -o joker $(OBJS)

%.o: %.c
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)
