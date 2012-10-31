#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <stdint.h>

// again, fuck unions for this kind of work
typedef uint8_t opcode_t;

// a useful macro
#define SET_OPCODE(dest,src) { dest.op = src >> 2; dest.d = (src & 0x2) >> 1; dest.w = src & 0x1; }

extern inline unsigned int instruction_length(uint8_t opcode)
{
    unsigned int rv = 0;
    switch(opcode)
    {
        case 0xB8:
            rv = 2;
            break;
        case 0x31: 
            rv = 3;
            break;
    }
    return rv;
}

#endif // INSTRUCTION_H
