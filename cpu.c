#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"
#include "loaders.h"
#include "errors.h"
#include "bitwise.h"

cpu_t* new_cpu(FILE* bios_file)
{
  cpu_t* rv = malloc(sizeof(cpu_t));
  if(rv != NULL)
  {
    memset(rv,0,sizeof(cpu_t));
    // now read the BIOS into memory at 0xC0000 to 0xF0000
    fread(rv->memory+0xC0000,0x20000,1,bios_file);
    // now set the instruction pointer to start at the BIOS's start
    rv->ip = 0xC0000;
  }
  rv->power = ON;
  return rv;
}

int boot_from_floppy(cpu_t* cpu,FILE* floppy)
{
  if(floppy == NULL)
  {
    return -1;
  }
  // read the file into memory
  fread(cpu->memory,MEMORY_SIZE,1,floppy);
  return ferror(floppy);
}

// keeping this in even though it's just an alias for free() at the moment
// it may come in handy later, depending what happens to the cpu_t type
void free_cpu(cpu_t* cpu)
{
  if(cpu==NULL)
    return;
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
  switch(cpu->memory[cpu->ip])
  {
    // MOV family of instructions
    case 0xB8:
      mov(cpu);
      break;
    // XOR family
    case 0x31:
      xor(cpu);
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
  //unsigned int start_address = 0;
  //unsigned int i = 0;
  if(coredump == NULL)
  {
      fprintf(stderr,"Could not open core.dmp for writing.  No core dump written.\n");
      return;
  }
  // binary version is more useful at the moment so we can do diffs against the floppy
  fwrite(cpu.memory,MEMORY_SIZE,1,coredump);
  /* ascii version
  #define BYTES_PER_LINE 16
  while(start_address < (MEMORY_SIZE-BYTES_PER_LINE))
  {
      i=0;
      fprintf(coredump,"%.8X: ",start_address);
      while(i<BYTES_PER_LINE)
      {
          fprintf(coredump,"%.2X ",cpu.memory[start_address+i]);
          i++;
      }
      fputc('\n',coredump);
      start_address += BYTES_PER_LINE;
  }
  * */
}

void dump_state(cpu_t cpu)
{
  printf("CPU status:\n");
  printf("\tPower: %s\n",cpu.power==ON?"on":"off");
  printf("Instruction Information:\n");
  printf("\tCurrent Instruction Pointer Address: %.4X.\n",cpu.ip);
  printf("\tInstruction at that address: %.2X\n",cpu.memory[cpu.ip]);
  printf("Accumulators:\n");
  printf("\tAX: {%.2X %.2X}\n",ACC_HI(cpu.ax),ACC_LO(cpu.ax));
  printf("\tBX: {%.2X %.2X}\n",ACC_HI(cpu.bx),ACC_LO(cpu.bx));
  printf("\tCX: {%.2X %.2X}\n",ACC_HI(cpu.cx),ACC_LO(cpu.cx));
  printf("\tDX: {%.2X %.2X}\n",ACC_HI(cpu.dx),ACC_LO(cpu.dx));
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
  printf("Error Status:\n");
  if(cpu.errno)
    printf("\tError: %s\n",err2str(cpu.errno));
  else
    printf("\tClear\n");
  dump_core(cpu);
}

char* err2str(uint16_t errnum)
{
  #define BIGGEST_STRING 46
  char* rv = malloc(BIGGEST_STRING);
  switch(errnum)
  {
      case 0xB007:
        sprintf(rv,"No boot medium found.");
        break;
      case 0xEE01:
        sprintf(rv,"Unimplemented opcode.");
        break;
      case 0x0000:
        sprintf(rv,"Clear");
        break;
      default:
      // maximum strlen here is 46, making this our biggest string
        sprintf(rv,"Unknown (look up manually) (Error number:%.4X)",errnum);
        break;
  }
  return rv;
}
