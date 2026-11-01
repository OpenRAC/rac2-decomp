#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; short h[0x1300]; int i[0x980]; float f[0x980]; void *ptr[0x980]; TI128 q[0x260]; } Hero;
extern char D_00189E20[];
extern char *func_0029EFD0(int);
extern void func_002B37E8(void *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern void func_002AEC48(void *, void *, int, float, float);
extern void func_PAL_002B14F8(void *, void *, int, int, float);
extern void func_PAL_002A7E68(void *, int, int, int);

void func_PAL_L03_003FA9B0(char *entity) {
    char *state = *(char **)(entity + 0x68);
    char *obj = *(char **)(state + 0x2C4);

    if (obj == 0) {
        char *made = func_0029EFD0(0xC49);
        *(char **)(state + 0x2C4) = made;
        if (made != 0) {
            func_002B37E8(made, 0);
        }
        return;
    }
    *(TI128 *)(obj + 0x10) = *(TI128 *)(entity + 0x10);
    *(TI128 *)(obj + 0xF0) = *(TI128 *)(entity + 0xF0);
    if (*(u16 *)(entity + 0x34) & 1) {
        *(u16 *)(obj + 0x34) |= 1;
        (*(char **)(state + 0x2C4))[0x31] = 0;
    } else {
        char *cur;
        *(u16 *)(obj + 0x34) &= 0xFFFE;
        (*(char **)(state + 0x2C4))[0x31] = 1;
        cur = *(char **)(state + 0x2C4);
        *(float *)(state + 0x278) = func_00283BE0(
            func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(float *)(cur + 0x10),
                          ((Hero *)D_00189E20)->f[0x84 / 4] - *(float *)(cur + 0x14)),
            *(float *)(entity + 0xF8));
        func_002AEC48(*(char **)(state + 0x2C4), state + 0x210, 0, 0.0432f, 0.43200004f);
        func_PAL_002B14F8(*(char **)(state + 0x2C4), state + 0x210, 0, 1, 2.5f);
    }
    {
        u8 *last = *(u8 **)(state + 0x2C4);
        if ((last[0x60] & 2) && last[0x43] == 1) {
            func_PAL_002A7E68(last, 0, 0, 8);
        }
    }
}
