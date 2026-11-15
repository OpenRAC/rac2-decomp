#include "common.h"
#include "structs.h"

extern signed char r1_D_001331D8[];

extern char *func_00131540(void);

extern void r1_func_00118CF0(void *);

extern short r1_D_001331D0 NOT_SDA;

extern unsigned char r1_D_001331D6[];

extern void r1_func_00118DC0(void *, int, int);

extern int r1_func_00118DC0_i(void *, int, int) __asm__("r1_func_00118DC0");

extern int func_00131730(int);

extern int func_00131760(int);

/* rac1-decomp src/core/0012CC90.c: func_0012D340 */
/* Checks whether this console is the kind that reports itself with a T in the ROM version. */
int func_001315E0(void) {
    if (r1_D_001331D8[0] == 0) {
        GetRomVersion();
    }
    return r1_D_001331D8[4] == 0x54;
}

extern unsigned char D_00138152 NOT_SDA;

extern void func_0011ACD0(unsigned int *);

/* Gets the console region number from stored data or from the hardware. */
int func_00131620(void) {
    unsigned int local;

    if (IsRomVersionTool() != 0) {
        return D_00138152;
    }
    GetOsdConfigParam(&local);
    return (local >> 1) & 3;
}


/* rac1-decomp src/core/0012CC90.c: func_0012D3F0 */
/* `r` assigned in both arms and returned once: a direct `return
   r1_D_001331D0;` loads straight into $v0 and moves the address to $v1. */
/* Gets the console model or version number. */
int func_00131670(void) {
    unsigned int local;
    unsigned int bits;
    int r;

    if (IsRomVersionTool() != 0) {
        r = r1_D_001331D0;
    } else {
        r1_func_00118CF0(&local);
        bits = (local >> 13) & 7;
        if (bits == 0) {
            r = 0x21C;
        } else {
            r = (int)local >> 21;
        }
    }
    return r;
}


/* rac1-decomp src/core/0012CC90.c: func_0012D448 */
/* One return, and r1_func_00118DC0 returns int. */
/* Gets a single on/off flag from the console hardware info. */
int func_001316C8(void) {
    unsigned char buf[16];
    int r;

    if (IsRomVersionTool() != 0) {
        r = r1_D_001331D6[0];
    } else {
        r1_func_00118CF0(buf);
        if (((*(unsigned int *)buf >> 13) & 7) == 0) {
            r = 0;
        } else {
            r1_func_00118DC0_i(buf + 4, 1, 1);
            r = (buf[4] >> 4) & 1;
        }
    }
    return r;
}

/* rac1-decomp src/core/0012CC90.c: func_0012D4B0 */
/* Turns a normal number (0-99) into a BCD byte. */
int func_00131730(int value) {
    unsigned int v = value & 0xFF;
    return ((v / 10) * 6 + v) & 0xFF;
}

/* rac1-decomp src/core/0012CC90.c: func_0012D4E0 */
/*
 * REVERTED (size mismatch: ours 28 bytes, retail 32). Semantics certain
 * -- BCD byte to binary:
 *
 *   int func_00131760(int arg0) {
 *       unsigned int v = arg0 & 0xFF;
 *       return (v - (v >> 4) * 6) & 0xFF;
 *   }
 *
 * (`unsigned` matters: it gives retail's `srl`, not `sra`.) Everything
 * matches except the multiply: retail uses the generic two-operand
 * `mult $0,$3,$4` followed by `mflo $3`, while this compiler uses the
 * EE three-operand `mult $v1,$v1,$a0` which writes the result directly
 * and needs no mflo -- one instruction fewer, hence 4 bytes short. That
 * is an ISA/codegen choice, not something the source can steer.
 */
/* BCD byte to binary. The product goes through an unsigned char: combine
   folds the multiply into that narrowing copy and re-recognises it as the
   generic LO-destination multiply, which is retail's `mult $0,a,b` +
   `mflo` (the plain int form picks the R5900 three-operand mult). */
/* The product goes through an unsigned char local: that gives retail's
   generic mult $0 + mflo instead of the three-operand mult. */
/* Turns a BCD byte into a normal number. */
int func_00131760(int bcd) {
    unsigned char v = bcd;
    unsigned char t = (v >> 4) * 6;
    return (unsigned char)(v - t);
}
