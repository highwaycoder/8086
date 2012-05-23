#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/cpu.h"
#include "include/loaders.h"
#include "include/errors.h"

cpu_t* new_cpu(void)
{
	cpu_t* rv = malloc(sizeof(cpu_t));
	if(rv != NULL)
	{
		memset(rv,0,sizeof(cpu_t));
		rv->memory_start = malloc(MEMORY_SIZE);
		rv->ip = rv->memory_start;
	}
}

int load_memory(cpu_t* cpu,FILE* ramfile)
{
	if(ramfile == NULL)
	{
		return -1;
	}
	// read the file into memory
	fread(cpu->memory_start,1,MEMORY_SIZE,ramfile);
	return ferror(ramfile);
}

void free_cpu(cpu_t* cpu)
{
	if(cpu==NULL)
		return;
	if(cpu->memory_start != NULL)
		free(cpu->memory_start);
	free(cpu);
	return;
}

void run(cpu_t* cpu)
{
	while(cpu->power == ON && cpu->errno == ENONE)
	{
		step(cpu);
	}
}

void step(cpu_t* cpu)
{
	switch(*cpu->ip)
	{
		// MOV family of instructions
		case 0xB8:
			mov(cpu);
			break;
		default:
			cpu->errno = EUNIMPLEMENTED;
			break;
	}
	#ifdef DEBUG
	dump_state(*cpu);
	#endif
}

void dump_core(cpu_t cpu)
{
	
}

void dump_state(cpu_t cpu)
{
	printf("CPU state:\n");
	printf("Accumulators:\n");
	printf("\tAX: {%.2X %.2X}\n",cpu.ax.h,cpu.ax.l);
	printf("\tBX: {%.2X %.2X}\n",cpu.bx.h,cpu.bx.l);
	printf("\tCX: {%.2X %.2X}\n",cpu.cx.h,cpu.cx.l);
	printf("\tDX: {%.2X %.2X}\n",cpu.dx.h,cpu.dx.l);
	printf("Index Registers:\n");
	printf("\tSI: {%.4X}\n",cpu.si);
	printf("\tDI: {%.4X}\n",cpu.di);
	printf("\tBP: {%.4X}\n",cpu.bp);
	printf("\tSP: {%.4X}\n",cpu.sp);
	printf("Status Register:\n");
	printf("\tCarry: %s\n",     cpu.flags & 0x0001 ? "set" : "unset");
	printf("\tParity: %s\n",    cpu.flags & 0x0004 ? "set" : "unset");
	printf("\tAdjust: %s\n",    cpu.flags & 0x0010 ? "set" : "unset");
	printf("\tZero: %s\n",      cpu.flags & 0x0040 ? "set" : "unset");
	printf("\tSign: %s\n",      cpu.flags & 0x0080 ? "set" : "unset");
	printf("\tTrap: %s\n",      cpu.flags & 0x0100 ? "set" : "unset");
	printf("\tInterrupt: %s\n", cpu.flags & 0x0200 ? "set" : "unset");
	printf("\tDirection: %s\n", cpu.flags & 0x0400 ? "set" : "unset");
	printf("\tOverflow: %s\n",  cpu.flags & 0x0800 ? "set" : "unset");
	
}

void err2str(uint16_t errnum)
{

}
