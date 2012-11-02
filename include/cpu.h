#ifndef CPU_H
#define CPU_H
#include <stdint.h>
#include <stdio.h> // for FILE*

// configuration constants
#define MEMORY_SIZE (1024*1024) // maximum addressable memory is 1MiB
#define MAX_MEMORY (MEMORY_SIZE-1) // highest addressable point

// useful macro for accessing hi/lo accumulator bytes
#define ACC_HI(x) (x >> 8)
#define ACC_LO(x) (x & 0xFF)

typedef enum POWER {
	ON,
	OFF
} power_t;

// fuck unions, let's just use a uint16_t for simplicity's sake
typedef uint16_t acc_t;


typedef struct CPU {
	// accumulators
	acc_t ax;
	acc_t bx;
	acc_t cx;
	acc_t dx;
	
	// index registers
	uint16_t si;
	uint16_t di;
	uint16_t bp;
	uint16_t sp;
	
	// status register
	uint16_t flags;
	
	// segment registers
	uint16_t cs;
	uint16_t ds;
	uint16_t es;
	uint16_t ss;
	
	// instruction pointer
	// must be able to address at least 1MiB of memory 
	// (must be at least 20 bits wide therefore)
	unsigned int ip:20;
	
	// memory is now implemented as an array to protect it (does hurt the stack a bit though)
	uint8_t memory[MEMORY_SIZE];
	
	// cpu error number for debugging purposes
	uint16_t errno;
	
	// power button, useful for shutting down safely
	power_t power;
} cpu_t;

// functions
cpu_t* new_cpu(FILE* bios_file);
int boot_from_floppy(cpu_t* cpu,FILE* ramfile);
void free_cpu(cpu_t* cpu);
void run(cpu_t* cpu);
void step(cpu_t* cpu);
void dump_core(cpu_t cpu);
void dump_state(cpu_t cpu);
char* err2str(uint16_t errnum);

#endif
