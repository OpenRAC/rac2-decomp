#include "include_asm.h"


typedef unsigned char u8;
extern u8 D_001A63A8_4[];
extern u8 D_00189E20[];

/* shared native body of family cbc1388ebe801e68 */
void func_PAL_L22_003A9808(u8 *a0, int a1) {
    u8 *g = D_001A63A8_4;
    u8 *p = *(u8 **)(a0 + 104);
    int bit;
    if (*(int *)(g + 104) != 0) return;
    if (*(int *)(g + 36) != -1) return;
    if (a1 == *(int *)(p + 1256)) return;
    bit = 1 << a1;
    { u8 *w = p + a1 * 4; *(int *)(g + 36) = (*(int *)(w + 1152) & 0x3fff) + 2000; }
    *(int *)(g + 40) = 0;
    *(int *)(p + 1256) = a1;
    *(int *)(p + 1252) = 1500;
    *(int *)(p + 1248) |= bit;
}

extern int func_002A77E0(int a0);
extern void func_L22_003A64E8(u8 *a0, int a1, int a2);
extern int func_002A77E0(int a0);

/* Arm one animation slot in the range [a1, a2]: a random slot of the range is
 * tried first and the next one after it, wrapping around, until a free slot
 * is found; when every slot of the range is taken, the range is cleared and
 * the last slot tried is armed.
 *
 * The mask lives in the controller at +0x4E0 of the object at +0x68.
 */
void func_PAL_L22_003A9880(u8 *a0, int a1, int a2) {
    u8 *ctl = *(u8 **)(a0 + 0x68);
    int count;
    int rem;
    int i;

    if (a2 < a1)
        return;
    count = a2 - a1 + 1;
    rem = func_002A77E0(count);
    for (i = 0; i < count; i++) {
        int idx = a1 + rem;
        if (((*(int *)(ctl + 0x4E0) >> idx) ^ 1) & 1) {
            func_L22_003A6470(a0, idx);
            return;
        }
        rem = (rem + 1) % count;
    }
    i = 0;
    if (count > 0) {
        int m = *(int *)(ctl + 0x4E0);
        for (; i < count; i++) {
            m &= ~(1 << (a1 + i));
        }
        *(int *)(ctl + 0x4E0) = m;
    }
    func_L22_003A6470(a0, a1 + rem);
}

