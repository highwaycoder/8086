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
		// apparently 0x31C0 is XOR ax,ax which makes sense but doesn't 
		// agree with what I read in the Intel Software Developer's 
		// Manual...
			xor_reg16_reg16(&cpu->ax,cpu->ax);
			break;
	}
}

void xor_reg16_reg16(uint16_t* dest,uint16_t src)
{
	*dest ^= src;
}
