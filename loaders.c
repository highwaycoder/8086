#include <stdio.h>
#include "cpu.h"
#include "instruction.h"
#include "loaders.h"

void mov(cpu_t* cpu)
{
	switch(cpu->memory[cpu->ip])
	{
		case 0xB8:
			mov_reg16_imm(&(cpu->ax),cpu->memory[cpu->ip+1]);
			break;
		case 0xBF:
			mov_reg16_imm(&(cpu->di),cpu->memory[cpu->ip+1]);
			break;
	}
	// make sure to increment at the end
	cpu->ip += instruction_length(cpu->memory[cpu->ip]);
}

void mov_reg16_imm(uint16_t* dest,uint16_t src)
{
	// this one is easy because it's a 16 bit immediate value into a 16 bit register
	*dest = src;
}

void mov_regLO_imm(uint16_t* dest,uint8_t src)
{
	*dest = (*dest & 0xFF00) | src;
}

void mov_regHO_imm(uint16_t* dest,uint8_t src)
{
	*dest = (*dest & 0x00FF) | (src << 8);
}

void mov_reg16_reg16(uint16_t* dest,uint16_t src)
{
	*dest = src;
}

void mov_regLO_regLO(uint16_t* dest,uint16_t src)
{
	*dest = (*dest & 0xFF00) | (src & 0x00FF);
}

void mov_regHO_regHO(uint16_t* dest,uint16_t src)
{
	*dest = (*dest & 0x00FF) | (src & 0xFF00);
}

void mov_regLO_regHO(uint16_t* dest,uint16_t src)
{
	*dest = (*dest & 0xFF00) | ((src & 0xFF00) >> 8);
}

void mov_reg16_regHO(uint16_t* dest,uint16_t src)
{
	// this nukes *dest then sets the HO byte to match src's HO byte
	*dest = (*dest & 0x0000) | (src & 0xFF00);
}

void mov_reg16_regLO(uint16_t* dest,uint16_t src)
{
	// same as above, only with LO bytes
	*dest = (*dest & 0x0000) | (src & 0x00FF);
}
