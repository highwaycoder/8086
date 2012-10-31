#ifndef CPU_H
#define CPU_H
#include <stdint.h>

// configuration constants
#define MEMORY_SIZE (1024*1024) // maximum addressable memory is 1MiB
#define MAX_MEMORY (MEMORY_SIZE-1) // highest addressable point

typedef enum POWER {
	ON,
	OFF
} power_t;

typedef union ACCUMULATOR {		
	uint16_t full;
	
	struct {
		uint8_t h;
		uint8_t l;
	};

} acc_t;


typedef struct CPU {
	// accumulators (accessed with, for example, ax or ax.h / ax.l)
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
	
	// instruction pointer (implemented as a native pointer for shits)
	uint8_t* ip;
	
	// pointer to the start of memory (nothing should alter this pointer - if they do, we're in trouble.)
	uint8_t* memory_start;
	
	// cpu error number for debugging purposes
	uint16_t errno;
	
	// power button, useful for shutting down safely
	power_t power;
} cpu_t;

// functions
cpu_t* new_cpu(void);
int boot_from_floppy(cpu_t* cpu,FILE* ramfile);
void free_cpu(cpu_t* cpu);
void run(cpu_t* cpu);
void step(cpu_t* cpu);
void dump_core(cpu_t cpu);
void dump_state(cpu_t cpu);
void err2str(uint16_t errnum);

#endif
