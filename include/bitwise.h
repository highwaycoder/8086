#ifndef BITWISE_H
#define BITWISE_H

// I've realised that I can exploit header guards to speed up compilation
// I'm not sure how effective it is, because this project hasn't grown
// enough yet but hopefully it'll save some time later on
#ifndef CPU_H
#include "cpu.h"
#endif

void xor(cpu_t* cpu);

void clear_reg(uint16_t* dest);
void xor_reg16_reg16(uint16_t* dest,uint16_t src);
void xor_modrm_reg16(cpu_t* cpu,uint8_t modrm,uint16_t src);

#endif
