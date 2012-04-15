#include <stdint.h>
#include <stdbool.h>
#include "include/errors.h"
#include "include/cpu.h"
#include "include/instruction.h"
#include "include/loaders.h"

instruction_t get_next_instruction(cpu_t* cpu)
{
  uint8_t* current_cell = cpu->memory_start;
  instruction_t rv;
  bool finished = 0;
  do {
    if(cpu->ip > MAX_MEMORY) {
      cpu->errno = EIP_OVERFLOW;
      return rv;
    }
    current_cell += cpu->ip;
    switch(*current_cell)
    {
      // prefix cases
      case 0x66:
      case 0x67:
        rv.prefix = *current_cell;
        break;
        
        
      // double opcode case
      case 0x0F:
        if(rv.opcode_isbig)
        {
          SET_OPCODE(rv.opcode,*current_cell)
          set_args(&rv,current_cell);
          finished = true;
        }
        else
        {
          rv.opcode_isbig = 1;
          finished = false; // not finished yet
        }
        break;
      // everything else is assumed to be an opcode
      default:
        SET_OPCODE(rv.opcode,*current_cell)
        // set the arguments for the instruction (important!)
        set_args(&rv,current_cell);
        finished = true;
        break;
    }
  } while(!finished);
  
  
  return rv;
}

void perform_instruction(cpu_t* cpu,instruction_t instruction)
{
  opcode_t opcode = instruction.opcode;
  if(instruction.opcode_isbig)
  {
    switch(opcode.op << 2)
    {
      
    }
  }
  else
  {
    switch(opcode.op << 2)
    {
      // MOVs
      case 0xB8:
        mov(cpu,instruction);
        break;
        
      default:
        break;
    }
  }
}

void set_args(instruction_t* instruction, uint8_t* mem_cell)
{
  
}
