/* functional: high. Same reads, writes and calls as retail's executable copy (0x34AA30); data named by the
 * executable's own addresses (lui 0x1B: 0x1AE798, 0x1AE79C, 0x1B23A0, 0x1B23A4), not level 0's copy's. */
#include "common.h"
extern void func_00335E68(char *, int);
extern float *func_00335E10(char *);
extern void func_00336B90(char *, int), func_00336B98(char *, int);
extern void func_00336498(char *, unsigned, unsigned), func_003364B0(char *, unsigned, unsigned);
extern void func_0026F808(int *, int *, int *);
extern int D_001A7A00 MACRO_ADDR, D_001A7A0C MACRO_ADDR;
typedef struct { char pad[0x22b4]; unsigned char mode; char gap[0x277]; int end, start; } StatusGlobals;
extern StatusGlobals D_00189E20;
extern float D_001AE798 MACRO_ADDR, D_001AE79C MACRO_ADDR, D_001B23A4 MACRO_ADDR;
extern int D_001B23A0 MACRO_ADDR;

void func_0034AA30(char *o)
{
    float *out = func_00335E10(o + 0xf4);
    if (D_001A7A00 < 80) {
        struct { int a, b, c; } range;
        float x, y, scale, offsetY;
        int iy, mode;
        func_00335E68(o + 0xf4, 1);
        range.c = 0;
        range.b = D_00189E20.end;
        range.a = D_00189E20.start;
        if (!range.a) func_0026F808(&range.a, &range.b, &range.c);
        func_00336B90(o + 0xf4, range.b - range.a);
        func_00336B98(o + 0xf4, (D_001A7A0C >> 5) - range.a);
        x = D_001AE798 + (*(float **)(o + 8))[0];
        scale = D_001B23A4;
        mode = D_001B23A0;
        offsetY = D_001AE79C;
        out[0] = x;
        y = (offsetY + (*(float **)(o + 8))[1]) * scale + 0.5f;
        if (mode == 1) iy = (int)(y + -5.0f);
        else iy = (int)y;
        out[1] = (float)iy;
        if (D_00189E20.mode == 1) {
            func_00336498(o + 0xf4, 0x60808080, 0x60808080);
            func_003364B0(o + 0xf4, 0x40808080, 0x40808080);
        } else {
            func_00336498(o + 0xf4, 0x8049c1ff, 0x80001eff);
            func_003364B0(o + 0xf4, 0x50f0c070, 0x50f0c070);
        }
    } else {
        func_00335E68(o + 0xf4, 0);
    }
}
