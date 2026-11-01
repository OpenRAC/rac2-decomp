#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern unsigned char *func_0029EFD0(int);
extern int func_002A0488(void *, int, int, int);
extern float func_002A7878(float, float);
extern void func_002A0F48(void *);

unsigned char *func_PAL_003098C8(char *position, char *vector, int count, int mode, int flag)
{
    unsigned char *p = func_0029EFD0(0x7A);
    char *state;
    float lo;
    float hi;

    if (p != 0) {
        p[0x30] = 0xFF;
        *(short *)(p + 0x32) = 0xFF;
        p[0x31] = 1;
        p[0x23] = 0x80;
        state = *(char **)(p + 0x68);
        func_002A0488(p, 0x7F, 0x7F, 0x7F);
        *(TI128 *)(p + 0x10) = *(TI128 *)position;
        *(TI128 *)state = *(TI128 *)vector;
        lo = 0.12566373f;
        hi = 0.25132746f;
        *(float *)(state + 0x10) = func_002A7878(lo, hi);
        *(float *)(state + 0x14) = func_002A7878(lo, hi);
        *(short *)(state + 0x18) = (short)count;
        *(short *)(state + 0x1A) = (short)count;
        if (mode == 2) {
            mode = 1;
            *(int *)(state + 0x20) = mode;
        }
        if (mode == 0)
            *(float *)(p + 0x2C) *= func_002A7878(0.5f, 0.75f);
        *(float *)(state + 0x1C) = *(float *)(p + 0x2C);
        p[0xBC] = (unsigned char)(mode | (flag << 1));
        func_002A0F48(p);
    }
    return p;
}
