#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <stdint.h>

typedef union MOD {
  uint8_t full;
  struct {
    uint8_t mod:2;
    uint8_t reg:3;
    uint8_t  rm:3;
  };
} mod_t;

typedef union OPCODE {
  uint8_t full;
  struct {
    uint8_t op:6;
    uint8_t  d:1;
    uint8_t  w:1;
  };
} opcode_t;

typedef struct INSTRUCTION {
    uint8_t prefix;
    uint8_t opcode_isbig; // 1 if opcode is 0x0FXX, 0 otherwise
    opcode_t opcode;
    mod_t address_mode;
    uint8_t low_disp;
    uint8_t high_disp;
    uint8_t low_data;
    uint8_t high_data;
} instruction_t;

instruction_t get_next_instruction(cpu_t* cpu);
void perform_instruction(cpu_t* cpu,instruction_t instruction);
void set_args(instruction_t* instruction, uint8_t* mem_cell);

// a useful macro
#define SET_OPCODE(dest,src) { dest.op = src >> 2; dest.d = src & 0x2; dest.w = src & 0x1; }

#endif // INSTRUCTION_H
