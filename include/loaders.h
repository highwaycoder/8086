#ifndef LOADERS_H
#define LOADERS_H

void mov(cpu_t* cpu);
void mov_reg16_imm(uint16_t* dest,uint16_t src);
void mov_regLO_imm(uint16_t* dest,uint8_t src);
void mov_regHO_imm(uint16_t* dest,uint8_t src);
void mov_reg16_reg16(uint16_t* dest,uint16_t src);
void mov_regLO_regLO(uint16_t* dest,uint16_t src);
void mov_regHO_regHO(uint16_t* dest,uint16_t src);
void mov_regLO_regHO(uint16_t* dest,uint16_t src);
void mov_reg16_regHO(uint16_t* dest,uint16_t src);
void mov_reg16_regLO(uint16_t* dest,uint16_t src);


#endif // LOADERS_H
