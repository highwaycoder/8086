#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "include/cpu.h"

cpu_t* new_cpu(void)
{
	cpu_t* rv = malloc(sizeof(cpu_t));
	if(rv != NULL)
	{
		memset(rv,0,sizeof(cpu_t));
		rv->memory_start = malloc(MEMORY_SIZE);
	}
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
	
}

void step(cpu_t* cpu)
{
	
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
