SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
CFLAGS = -Ilib -Wall

joker: $(OBJS)
	gcc $(CFLAGS) -o joker $(OBJS)

%.o: %.c
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)
