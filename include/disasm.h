#ifndef DISASM_H
#define DISASM_H

#ifndef INSTRUCTION_H
#include "instruction.h"
#endif

void disasm_opcode(opcode_t opcode,char* buf);
void disasm_modrm(uint8_t modrm,char* buf);

#endif
