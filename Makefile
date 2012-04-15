CC=gcc
LD=gcc
CFLAGS=-fms-extensions -std=gnu99
LDFLAGS=
PROGNAME=8086
OBJS=instruction.o loaders.o cpu.o

$(PROGNAME): $(OBJS)
	$(LD) $(LDFLAGS) -o $(PROGNAME) main.c $(OBJS)
	
instruction.o: instruction.c include/instruction.h include/cpu.h
	$(CC) $(CFLAGS) -o instruction.o -c instruction.c

loaders.o: loaders.c include/loaders.h include/cpu.h
	$(CC) $(CFLAGS) -o loaders.o -c loaders.c

cpu.o:cpu.c include/cpu.h
	$(CC) $(CFLAGS) -o cpu.o -c cpu.c

clean: clean-objs
	rm -f $(PROGNAME)
	
clean-objs:
	rm -f $(OBJS)
