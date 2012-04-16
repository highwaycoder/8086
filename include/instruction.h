#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <stdint.h>

typedef union OPCODE {
  uint8_t full;
  struct {
    uint8_t op:6;
    uint8_t  d:1;
    uint8_t  w:1;
  };
} opcode_t;

// a useful macro
#define SET_OPCODE(dest,src) { dest.op = src >> 2; dest.d = (src & 0x2) >> 1; dest.w = src & 0x1; }

#endif // INSTRUCTION_H
