#include "include_asm.h"

typedef int V4_002AE8C0 __attribute__((mode(TI)));
extern int func_002A7820(int, int);
extern float func_002A78D8(float, float);
extern int func_002A7EA0(char *, char *, float *, int, float, float, float, float);
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

/* Runs the timer state, then integrates a copied position vector through two sine helpers
   and applies the result to the object's 0x24 field, either from the target position or from
   the hero position. The unit needs -frac2-qcopy -frac2-qcopy-barrier so the 16-byte copy
   reaches addiu/lq/sq, and -g for the two nops in front of the division. */
void func_PAL_002AF420(char *a0, char *a1, float a2, float a3)
{
    char *obj = a0;
    char *st = a1;
    V4_002AE8C0 *pos;
    float v[4];
    float f;
    float limit;
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
    pos = (V4_002AE8C0 *)(obj + 0x10);
    *(V4_002AE8C0 *)v = *pos;
    v[0] = v[0] + func_00283180(*(float *)(obj + 0xF8)) * *(float *)(st + 0x14);
    v[1] = v[1] + func_00283198(*(float *)(obj + 0xF8)) * *(float *)(st + 0x14);
    r = func_002A7EA0(obj, (char *)pos, v, 0, a2, *(float *)(st + 0x10), a3, 0.52359885f);
    *(float *)(obj + 0x18) = func_002A89A8((char *)pos, 0, 0.5f);
    f = func_00282E80((char *)pos, st);
    if (r == 0 || *(float *)(st + 0x1C) < f) {
        *(float *)(st + 0x24) = func_00283248(*(float *)(st + 0x0) - *(float *)(obj + 0x10),
                                              *(float *)(st + 0x4) - *(float *)(obj + 0x14));
        *(short *)(st + 0x2A) = func_002A7820(25, 75);
        *(short *)(st + 0x28) = 1;
    } else {
        float t;

        f = func_00282E80((char *)pos, D_00189E20.pos);
        limit = *(float *)(st + 0x20);
        if (f < limit) {
            t = f / limit;
            *(float *)(st + 0x24) = func_002AA150(*(float *)(st + 0x24),
                    func_00283248(*(float *)(obj + 0x10) - D_00189E20.pos[0],
                                  *(float *)(obj + 0x14) - D_00189E20.pos[1]), t);
        }
    }
}
