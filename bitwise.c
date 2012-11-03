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
		// 0x31C0 is XOR ax,ax.  I think the 0x31 opcode is XOR reg,self
		// ie "clear reg", so I'm going to write a function that does exactly that.
			clear_reg(&cpu->ax);
			break;
	}
}

void clear_reg(uint16_t* dest)
{
	// equivalent to *dest ^= *dest but clearer
	*dest = 0x0;
}

void xor_reg16_reg16(uint16_t* dest,uint16_t src)
{
	*dest ^= src;
}
