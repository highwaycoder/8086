#ifndef BITWISE_H
#define BITWISE_H

#ifndef CPU_H
#error "you must include cpu.h before bitwise.h"
#endif

void xor(cpu_t* cpu);

void xor_reg16_reg16(uint16_t* dest,uint16_t src);
void xor_modrm_reg16(cpu_t* cpu,uint8_t modrm,uint16_t src);

#endif
