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

int boot_from_floppy(cpu_t* cpu,FILE* floppy)
{
  if(floppy == NULL)
  {
    return -1;
  }
  // read the file into memory
  fread(cpu->memory_start,1,MEMORY_SIZE,floppy);
  return ferror(floppy);
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
  FILE* coredump = fopen("core.dmp","w");
  unsigned int start_address = 0;
  unsigned int i = 0;
  if(coredump == NULL)
  {
      fprintf(stderr,"Could not open core.dmp for writing.  No core dump written.\n");
      return;
  }
  #define BYTES_PER_LINE 16
  while(start_address < MEMORY_SIZE-BYTES_PER_LINE)
  {
      fprintf(coredump,"%.8X: ",start_address);
      while(i<BYTES_PER_LINE)
      {
          fprintf(coredump,"%.2X ",cpu.memory_start[start_address+i]);
          i++;
      }
      fputc('\n',coredump);
      start_address += BYTES_PER_LINE;
  }
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
  dump_core(cpu);
}

void err2str(uint16_t errnum)
{
  
}
