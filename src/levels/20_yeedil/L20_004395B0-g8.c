#include "common.h"

/* 128-bit copies reach lq/sq only through TImode. */
typedef int TI128 __attribute__((mode(TI)));

/* 0x1AEFF0 + 0x2E18 : the three floats the retail reads through $gp here. */
extern float D_L20_001B1E08 __attribute__((sda));

extern float D_L20_001B1E0C __attribute__((sda));

extern float D_L20_001B1E10 __attribute__((sda));

extern void func_00282CF0(void *, void *, void *);

extern void func_002A7750(char *, int, int);

extern void func_002AD6F0(char *, char *, char *, char *);

/* func_L01_0031AB20 takes two pointers, an int ($a2) and three floats ($f12-$f14).
   The floats-then-int spelling follows the level 12 callers; the shared L01 caller
   spells it int-first, and the EE ABI makes the two equivalent. */
extern void func_L01_0031AB20(void *, void *, f32, f32, f32, s32);

/* The three floats of case 1 are read through $gp, and the two 128-bit copies are
   qcopy (retail materialises both addresses: addiu; lq 0; sq 0). */
void func_L20_004395B0(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    TI128 pos;
    TI128 rot;
    TI128 out;

    qcopy(&pos, arg0 + 0x10);
    qcopy(&rot, arg0 + 0xF0);

    switch (*(u8 *)(arg0 + 0x20)) {
    case 0:
        *(u16 *)(arg0 + 0x34) |= 0x1000;
        *(f32 *)(state + 0x84) = 7.0f;
        *(int *)(state + 0xDC) |= 1;
        *(f32 *)(state + 0x88) = *(f32 *)(state + 0xE4);
        func_002A7750(arg0, 1, -1);
        break;
    case 1:
        func_L01_0031AB20(arg0, state + 0x50, D_L20_001B1E08, D_L20_001B1E0C,
                          D_L20_001B1E10, *(s32 *)(state + 0xE0));
        break;
    }
    func_00282CF0(&out, arg0 + 0x10, &pos);
    func_002AD6F0(state + 0xA0, (char *)&out, (char *)&rot, arg0 + 0xF0);
}
