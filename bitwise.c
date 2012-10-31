#include "instruction.h"
#include "cpu.h"
#include "bitwise.h"

void xor(cpu_t* cpu)
{
	switch(cpu->memory[cpu->ip])
	{
		case 0x31:
			xor_modrm_reg16(cpu,cpu->memory[cpu->ip+1],cpu->memory[cpu->ip+2]);
			cpu->ip += instruction_length(0x31);
			break;
	}
}

void xor_modrm_reg16(cpu_t* cpu,uint8_t modrm,uint16_t src)
{
	switch(modrm)
	{
		case 0xC0:
			xor_reg16_reg16(&cpu->ax,src);
			break;
	}
}

void xor_reg16_reg16(uint16_t* dest,uint16_t src)
{
	*dest ^= src;
}
