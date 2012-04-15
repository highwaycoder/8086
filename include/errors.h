#ifndef ERRORS_H
#define ERRORS_H

/* 
 * Notes:
 * flow error is 0Fxx
 *  - overflow is xxx0
 *  - underflow is xxx1
 *  - so *flow can be checked with "((&0xFF00) >> 8) == 0x0F"
 *  - and then over/underflow can be checked with "(&0x1)==1"
 *  - I don't foresee it being used much like this though, but it's
 *    nice to have a convention anyway
 * 
 * errors beginning with BD relate to errors in a program, not errors
 * in the emulator.  For example, if a program uses an opcode that does
 * not exist or is incompatible, BD0C will be set.
 * 
 * errors beginning with EE relate to foreseeable errors with the 
 * emulator and should be reported to someone who seems to know what 
 * they're doing ASAP.  If you can't find someone who seems to know what 
 * they're doing, report them to synirc.net/#tumblrcode and someone 
 * might help you (don't hold your breath though).
 */


enum ERRORS {
	ENONE   	     = 0x0000,
	
	// overflows/underflows
	ESTACK_OVERFLOW  = 0x0F00,
	ESTACK_UNDERFLOW = 0x0F01,
	EIP_OVERFLOW     = 0x0F10,
	EIP_UNDERFLOW    = 0x0F11,
	
	// misc
	EBADOPCODE 		 = 0xBD0C,
	
	// errors we can foresee
	EUNIMPLEMENTED   = 0xEE01,
};


#endif
