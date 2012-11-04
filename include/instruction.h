#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <stdint.h>

// again, fuck unions for this kind of work
typedef uint8_t opcode_t;

// a useful macro
#define SET_OPCODE(dest,src) { dest.op = src >> 2; dest.d = (src & 0x2) >> 1; dest.w = src & 0x1; }

static inline unsigned int instruction_length(opcode_t opcode)
{
    unsigned int rv = 0;
    switch(opcode)
    {
        // opcode with zero operands (total instruction length==1)
        
        // opcodes with one operand (total instruction length==2)
        case 0x31: 
        case 0xB8:
        case 0xBF:
            rv = 2;
            break;
        // opcodes with two operands (total instruction length==3)
        default:
            // making the assumption that most instructions take one operand is probably dangerous, but oh well
            rv = 2;
            break;
    }
    return rv;
}

#endif // INSTRUCTION_H
