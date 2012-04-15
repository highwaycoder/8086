#include <stdio.h>
#include <stdlib.h>
#include "include/cpu.h"

int main(int argc, char** argv)
{
	cpu_t* cpu = new_cpu();
	int rv = 0;
	if(cpu == NULL)
	{
		fprintf(stderr,"Couldn't init CPU.  Try again please.\n");
		rv = !0;
	}
	if(!rv)
		run(cpu);
	free_cpu(cpu);
	return 0;
}
