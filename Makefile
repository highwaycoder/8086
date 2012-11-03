CC=gcc
LD=gcc
CFLAGS=-fms-extensions -std=gnu99 -g -Wall -Wextra -pedantic -Iinclude
LDFLAGS=
PROGNAME=8086
OBJS=main.o loaders.o cpu.o bitwise.o

$(PROGNAME): $(OBJS)
	$(LD) $(LDFLAGS) -o $(PROGNAME) $(OBJS)

main.o: main.c include/cpu.h config.h include/errors.h
	$(CC) $(CFLAGS) -o main.o -c main.c

loaders.o: loaders.c include/loaders.h include/cpu.h include/instruction.h
	$(CC) $(CFLAGS) -o loaders.o -c loaders.c

cpu.o:cpu.c include/cpu.h include/loaders.h include/bitwise.h include/cpu.h include/errors.h
	$(CC) $(CFLAGS) -o cpu.o -c cpu.c
	
bitwise.o: bitwise.c include/bitwise.h
	$(CC) $(CFLAGS) -o bitwise.o -c bitwise.c

clean: clean-objs
	rm -f $(PROGNAME)
	
clean-objs:
	rm -f $(OBJS)
