CC=gcc
LD=gcc
CFLAGS=-fms-extensions -std=gnu99 -g -Wall -Wextra -pedantic -Iinclude -DVERSION=1.0
LDFLAGS :=-Xlinker --defsym -Xlinker BUILD_NUMBER=$$(cat build_number)
LDFLAGS += -Xlinker --defsym -Xlinker BUILD_DATE=$$(date +'%Y%m%d')
LDFLAGS += -Llib -lui
PROGNAME=8086
OBJS=main.o loaders.o cpu.o bitwise.o disasm.o

# below are listed all the available frontends, the default is 'text'
FRONTEND=text

$(PROGNAME): $(OBJS) lib/libui.a build_number
	$(LD) $(LDFLAGS) -o $(PROGNAME) $(OBJS) lib/libui.a
	
lib/libui.a: frontends/$(FRONTEND)/ui.c include/ui.h | lib
	$(CC) $(CFLAGS) -o frontends/$(FRONTEND)/ui.o -c frontends/$(FRONTEND)/ui.c
	$(AR) rcs $@ frontends/$(FRONTEND)/ui.o

main.o: main.c include/cpu.h config.h include/errors.h
	$(CC) $(CFLAGS) -o main.o -c main.c

loaders.o: loaders.c include/loaders.h include/cpu.h include/instruction.h
	$(CC) $(CFLAGS) -o loaders.o -c loaders.c

cpu.o:cpu.c include/cpu.h include/loaders.h include/bitwise.h include/cpu.h include/errors.h
	$(CC) $(CFLAGS) -o cpu.o -c cpu.c
	
bitwise.o: bitwise.c include/bitwise.h
	$(CC) $(CFLAGS) -o bitwise.o -c bitwise.c

disasm.o: disasm.c include/disasm.h
	$(CC) $(CFLAGS) -o disasm.o -c disasm.c

build_number: $(OBJS)
	@if ! test -f build_number; then echo 0 > build_number; fi
	echo $$(($$(cat build_number)+1)) > build_number

lib:
	mkdir -p lib

clean: clean-objs
	rm -f $(PROGNAME)
	
clean-objs:
	rm -f $(OBJS)
