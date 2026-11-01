#include "include_asm.h"

#include "common.h"
extern u8 *D_L06_001B281C MACRO_ADDR;
extern void func_0029FCC0(void *, int, void *);
extern void func_00282F20(char *, char *, float);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_00282D30(char *, char *, float);
extern float func_0029F530(char *);
extern void func_002A8C00(void *, char *, int, void *, float);
extern int func_00277F48(void *, float, int, char *, void *);
extern void *D_L06_001BFC98;
extern void func_0029FCC0(void *, int, void *);
extern void *D_L06_001BFC98;

/* Runs the shared pickup test: when the object is in the given state and the draw is inside the window, aims at the target and, on a hit with the expected tag, hands over to the next state. */
void func_PAL_L06_0045F3F8(char *obj, float lo, char *self, float hi, int kind, int sub, float scale, float reach, float range,
                       int anim, int link, int next, void *tag)
{
    float dir[4] __attribute__((aligned(16)));
    char aim[0x30] __attribute__((aligned(16)));
    float probe[4] __attribute__((aligned(16)));
    float roll = func_0029F530(obj);
    char *vec;

    if (*(u8 *)(obj + 0x20) == kind && *(u8 *)(obj + 0x42) == sub && lo < roll && roll < hi) {
        vec = self + 0xC0;
        func_00282F20((char *)dir, vec, scale);
        dir[2] = 1.0f;
        func_002A8C00(aim, obj, 1, dir, reach);
        func_0029FCC0(obj, 0, probe);
        if (func_00277F48(probe, range, 0x21, obj, aim) != 0 && D_L06_001BFC98 == tag) {
            func_00282D30(vec, vec, -1.0f);
            *(float *)(self + 0xC8) = -0.060000002f;
            if (*(u8 *)(obj + 0x43) != anim)
                func_PAL_002A7E68(obj, anim, link, 5);
            *(u8 *)(obj + 0x20) = next;
        }
    }
}

