#include "include_asm.h"

/* func_L02_0033C760 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char *func_002B9030(int);

extern int func_00283CF0(float);

typedef struct {
    u8 pad00[0x78];
    u8 *ids;
} L02_Palette;

extern L02_Palette D_L02_00200080;

char *func_L02_0033C760(TI128 *pos, char *prev, int flag, float scale) {
    char *node = func_002B9030(0x1E);
    char *tail;
    char *ptail;

    if (node != 0) {
        tail = node + 0x20;
        *(int *)(node + 4) = 0x80808080;
        *(u8 *)(node + 9) = FloatToInt(4.0f) + 0x40;
        *(u8 *)(node + 3) = 0x44;
        *(u8 *)(node + 8) = 0x20;
        *(float *)(node + 0xC) = scale * 210000.0f;
        *(u8 *)(node + 1) = 0;
        if (pos != 0) {
            *(TI128 *)(node + 0x10) = *pos;
            *(short *)(tail + 0x1E) = 1;
        } else {
            *(TI128 *)(node + 0x10) = *(TI128 *)(prev + 0x10);
            *(float *)(node + 0x18) -= 0.15f;
            *(short *)(tail + 0x1E) = 0;
        }
        if (flag == 0)
            *(short *)(tail + 0x1E) = 0xFF;
        *(u8 *)(node + 2) = D_L02_00200080.ids[0];
        if (prev != 0) {
            ptail = prev + 0x20;
            if (*(u8 *)(node + 2) == *(u8 *)(prev + 2))
                *(u8 *)(node + 2) = D_L02_00200080.ids[1];
            *(char **)(tail + 0x10) = prev;
            *(char **)(ptail + 0x14) = node;
        } else {
            *(char **)(tail + 0x10) = 0;
        }
    }
    return node;
}
