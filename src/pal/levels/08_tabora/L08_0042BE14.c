#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L08_0042BE14);

#include "common.h"
extern s32 D_L08_001B39A0[] MACRO_ADDR;
extern s32 D_L08_001B3A30[] MACRO_ADDR;
extern void func_L08_00429408(s32 a0);
extern void func_PAL_L08_0042ECD0(s32 a0, s32 a1);
extern void func_L08_002F2D10(void (*fn)(void *), void *arg);
extern void func_PAL_L08_0042F658(void *);

/* The spawner's three slots: the first byte of the record says whether the slot is
   empty (0), in use (1) or a finished one (4); a slot whose record is gone is freed. */
void func_PAL_L08_0042E858(char *a0) {
    s32 i;
    s32 k;
    s32 count;
    s32 v;

    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        for (k = 0; k < 3; k++) {
            D_L08_001B39A0[k] = 0;
            D_L08_001B3A30[k] = 0;
        }
        *(u8 *)(a0 + 0x20) = 1;
        *(u8 *)(a0 + 0x30) = 0xFF;
        break;
    case 1:
        count = 0;
        for (i = 0; i < 3; i++) {
            v = D_L08_001B39A0[i];
            if (v == 1) {
                if (*(signed char *)(D_L08_001B3A30[i] + 0x20) < 0) {
                    D_L08_001B39A0[i] = 0;
                    D_L08_001B3A30[i] = 0;
                }
            } else if (v == 4) {
                func_L08_00429408(i);
            } else if (v != 0) {
                func_PAL_L08_0042ECD0(D_L08_001B3A30[i], i);
                count++;
                D_L08_001B39A0[i] = 4;
            }
        }
        if (count != 0) {
            func_L08_002F2D10(func_PAL_L08_0042F658, a0);
        }
        break;
    }
}

