#include <stdio.h>
#include <stdlib.h>
#include "include/cpu.h"

int main(int argc, char** argv)
{
	cpu_t* cpu = new_cpu();
	int rv = 0;
	FILE* ramfile = NULL;
	if(cpu == NULL)
	{
		fprintf(stderr,"Couldn't init CPU.  Try again please.\n");
		rv = -1;
	}
	if(argc == 2)
	{
		ramfile = fopen(argv[1],"r");
	}
	rv = load_memory(cpu,ramfile);
	if(!rv)
	{
		run(cpu);
	}
	free_cpu(cpu);
	return 0;
}
