#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

typedef struct {
    u8 pad[0x274];
    f32 f274;
    f32 f278;
    f32 f27C;
    s32 i280;
} T_001B99C0;

extern T_001B99C0 D_L16_001B99C0;

extern void func_002A7470(void *, s32, s32, s32);

/* func_L16_002C6378 is in the sibling file L16_002C6378-decider.c (its own profile). */

/* func_L16_002D2D10: 76 bytes against retail's 88 - the divisions and the stores
   are now in retail's order, but retail's pair of `nop`s before each `div.s` is
   missing.  Deposited in nonmatching/levels/func_L16_002D2D10.c. */
/* func_L16_002D2D10 is matched in its own unit, L16_002D2D10.c. */

/* func_L16_002F60B8 is in L16_002F60B8-g8.c. */

/* func_L16_00317C90 is in the sibling file L16_00317C90.c: it needs the -g profile, whose
   line labels let the assembler reproduce the padding before its division. */

/* runs the readiness helper once when the handle is in state 1 with flag 2 set */
void func_L16_003AA0C8(u8 *arg0) {
    if (arg0[0x43] == 1 && (arg0[0x60] & 2) != 0) {
        func_002A7470(arg0, 0, 0, 1);
    }
}


/* func_L16_003AA3F0 is in L16_003AA3F0-g8.c. */

/* func_L16_003D6D00: 368 bytes against retail's 364; the prologue, the frame layout
   and every branch target from +0x44 on are retail's, but the byte test comes out
   as the annulling `bnel` (which repeats the pointer load) instead of retail's plain
   `bnez`, and the pointer and the base land in $s0/$s2 instead of $s2/$s1.
   Deposited in nonmatching/levels/func_L16_003D6D00.c. */

/* func_L16_003E6E08 is in L16_003E6E08-g8.c (vector-copy profile). */

/* func_L16_003E70E0 is defined in L16_002C6378-g8.c (it reads $gp data). */

/* func_L16_003E7248 is defined in L16_003E7248-g8.c (it reads $gp data). */

/* func_L16_003F4FA8 is defined in L16_003F4FA8.c (vector-copy profile). */

extern void func_002A7750(char *, s32, s32);

extern s32 func_002A9640(char *, s32, s32);

extern void func_L16_003F55A0(char *);

extern void func_L16_003F5708(char *);

extern void func_002E5CF8(s32, s32, char *);

extern void func_0029F338(char *);

/* Tears the resident down (state 0) or starts it once the readiness test passes
   (state 1), chosen by the record's own state byte. */
void func_L16_003F54F8(char *a0) {
    char *s0 = a0;

    switch (*(u8 *)(s0 + 0x20)) {
    case 0:
        *(u16 *)(s0 + 0x32) = 0x200;
        *(u16 *)(s0 + 0x34) |= 0x4000;
        func_002A7750(s0, 1, -1);
        break;
    case 1:
        if (func_002A9640(s0, 0x80000, 0) != 0) {
            func_L16_003F55A0(s0);
            func_L16_003F5708(s0);
            func_002E5CF8(0, 0, s0);
            func_0029F338(s0);
        }
        break;
    }
}

/* func_L16_003F55A0 is in L16_003F55A0-g8.c; its division needs -g. */

/* func_L16_003F5708 is in L16_003F5708-g8.c. */
