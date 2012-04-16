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

void load_memory(cpu_t* cpu,FILE* ramfile)
{
	// stub
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
}

void dump_core(cpu_t cpu)
{
	
}

void dump_state(cpu_t cpu)
{
	
}

void err2str(uint16_t errnum)
{

}
