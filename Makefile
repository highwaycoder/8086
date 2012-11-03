CC=gcc
LD=gcc
CFLAGS=-fms-extensions -std=gnu99 -g -Wall -Wextra -pedantic -Iinclude -DVERSION=1.0
LDFLAGS :=-Xlinker --defsym -Xlinker BUILD_NUMBER=$$(cat build_number)
LDFLAGS += -Xlinker --defsym -Xlinker BUILD_DATE=$$(date +'%Y%m%d')
PROGNAME=8086
OBJS=main.o loaders.o cpu.o bitwise.o

$(PROGNAME): $(OBJS) build_number
	$(LD) $(LDFLAGS) -o $(PROGNAME) $(OBJS)

main.o: main.c include/cpu.h config.h include/errors.h
	$(CC) $(CFLAGS) -o main.o -c main.c

loaders.o: loaders.c include/loaders.h include/cpu.h include/instruction.h
	$(CC) $(CFLAGS) -o loaders.o -c loaders.c

cpu.o:cpu.c include/cpu.h include/loaders.h include/bitwise.h include/cpu.h include/errors.h
	$(CC) $(CFLAGS) -o cpu.o -c cpu.c
	
bitwise.o: bitwise.c include/bitwise.h
	$(CC) $(CFLAGS) -o bitwise.o -c bitwise.c

build_number: $(OBJS)
	@if ! test -f build_number; then echo 0 > build_number; fi
	@echo $$(($$(cat build_number)+1)) > build_number

clean: clean-objs
	rm -f $(PROGNAME)
	
clean-objs:
	rm -f $(OBJS)
