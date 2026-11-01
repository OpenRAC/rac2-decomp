#include "include_asm.h"

typedef int V4_002AE8C0 __attribute__((mode(TI)));
extern int func_002A7820(int, int);
extern float func_002A78D8(float, float);
extern int func_PAL_L01_00323068(char *, float *);
extern float func_002A89A8(char *, int, float);
extern float func_002AA150(float, float, float);
extern void func_002AA800(float *, int, float, float);
extern int func_00282978(char *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00282E80(char *, char *);
typedef struct {
    char reserved_000[0x80];
    float pos[4];
} GameState_189E20;
extern GameState_189E20 D_00189E20;

/* Hand-adapted from func_002AE8C0. */
void func_PAL_L01_0031A4D0(char *obj, char *st, char *ctx)
{
    char *pos;
    float v[4];
    float f;

    int r;

    if (*(short *)(st + 0x28) == 0) {
        *(float *)(st + 0x24) = *(float *)(st + 0x24) + func_002A78D8(0.78539824f, 2.6179941f);
        *(short *)(st + 0x2A) = func_002A7820(*(short *)(st + 0x2C), *(short *)(st + 0x2E));
        *(short *)(st + 0x28) = 1;
    } else {
        func_002AA800((float *)(obj + 0xF8), 0, *(float *)(st + 0x24), *(float *)(st + 0x18));
        if (func_00282978(st + 0x2A) != 0)
            *(short *)(st + 0x28) = 0;
    }
    pos = obj + 0x10;
    *(V4_002AE8C0 *)v = *(V4_002AE8C0 *)pos;
    f = *(float *)(ctx + 0x28);
    *(float *)(ctx + 0x28) = *(float *)(st + 0x14);
    v[0] = v[0] + func_00283180(*(float *)(obj + 0xF8)) * 2.0f;
    v[1] = v[1] + func_00283198(*(float *)(obj + 0xF8)) * 2.0f;
    *(float *)(ctx + 0x28) = f;
    r = func_PAL_L01_00323068(obj, v);
    *(float *)(obj + 0x18) = func_002A89A8(pos, 0, 0.5f);
    f = func_00282E80(pos, st);
    if (r != 0 || *(float *)(st + 0x1C) < f) {
        *(float *)(st + 0x24) = func_00283248(*(float *)(st + 0x0) - *(float *)(obj + 0x10),
                                              *(float *)(st + 0x4) - *(float *)(obj + 0x14));
        *(short *)(st + 0x2A) = func_002A7820(25, 75);
        *(short *)(st + 0x28) = 1;
    } else {
        float limit;

        f = func_00282E80(pos, D_00189E20.pos);
        limit = *(float *)(st + 0x20);
        if (f < limit) {
            f = f / limit;
            *(float *)(st + 0x24) = func_002AA150(*(float *)(st + 0x24),
                    func_00283248(*(float *)(obj + 0x10) - D_00189E20.pos[0],
                                  *(float *)(obj + 0x14) - D_00189E20.pos[1]), f);
        }
    }
}
