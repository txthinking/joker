SRC = $(wildcard *.c)
SRC += $(wildcard lib/sds/*.c)
SRC += $(wildcard lib/str-starts-with.c/src/*.c)
OBJS = $(SRC:.c=.o)
CFLAGS = -Ilib -Wall

joker: $(OBJS)
	gcc $(CFLAGS) -o joker $(OBJS)

%.o: %.c
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)

install: joker
	cp -f joker /usr/local/bin/
