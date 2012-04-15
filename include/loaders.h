#ifndef LOADERS_H
#define LOADERS_H

void mov(cpu_t* cpu,instruction_t instruction);
void mov_reg16_imm(acc_t* dest,uint16_t src);
void mov_regLO_imm(acc_t* dest,uint8_t src);
void mov_regHO_imm(acc_t* dest,uint8_t src);
void mov_reg16_reg16(acc_t* dest,acc_t src);
void mov_regLO_regLO(acc_t* dest,acc_t src);
void mov_regHO_regHO(acc_t* dest,acc_t src);
void mov_regLO_regHO(acc_t* dest,acc_t src);
void mov_reg16_regHO(acc_t* dest,acc_t src);
void mov_reg16_regLO(acc_t* dest,acc_t src);


#endif // LOADERS_H
