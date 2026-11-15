#include "include_asm.h"

typedef unsigned int u32;
typedef short s16;

extern int D_L02_gp10B0 __attribute__((sda));
extern unsigned int D_001B00A4 __attribute__((nosda));

extern int func_002F1BE0(void *);
extern s16 func_0031E7B0(int, unsigned int);
extern void func_00366B30(int, int, void *);

/* When a timer on the enemy runs out, picks a new timer value and sends a notice. */
void func_L02_003CB090(char *self) {
    char *state = *(char **)(self + 0x68);

    if (func_002F1BE0(state + 0x3B4) != 0) {
        *(s16 *)(state + 0x3B4) = func_0031E7B0(D_L02_gp10B0, D_001B00A4);
        func_00366B30(1, 0, self);
    }
}
