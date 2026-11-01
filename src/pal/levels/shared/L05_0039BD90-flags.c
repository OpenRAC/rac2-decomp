#include "include_asm.h"

#include "common.h"
extern char *func_0029EFD0(int);
struct EffectState98 {
    short timer, duration, delay, pad6;
    float scale2, scale4, fade, scale;
    int visible, pad1c, a2, a3, a4, a5, a6, pad34, pad38, a7;
};
struct Camera98 {
    char pad0[0x140];
    float position[4];
    char pad150[0x10];
    float shake;
    int pad164, duration, timer;
    char pad170[0x200];
    float forward[4];
};
extern struct Camera98 D_L05_001B9580;
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282DD8(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern void func_PAL_L05_0039C0D8(void *, void *);

char *func_PAL_L05_0039BD90(void *position, int shake, int a2, int a3, int a4, int a5, int a6, int a7, float scale)
{
    float direction[4], normal[4], sphere[4], delta[4];
    char *obj;
    struct EffectState98 *state;
    obj = func_0029EFD0(0x12e8);
    if (obj) {
        state = *(struct EffectState98 **)(obj + 0x68);
        *(unsigned char *)(obj + 0x30) = 0xff;
        *(unsigned short *)(obj + 0x32) = 0xff;
        obj[0x20] = 0;
        qcopy(obj + 0x10, position);
        *(float *)(obj + 0x1c) = 1.0f;
        func_00282CF0(direction, D_L05_001B9580.position, obj + 0x10);
        func_00282F20(direction, direction, 1.0f);
        func_002AFFD8(obj + 0x10, normal, 1);
        qcopy(obj + 0xc0, direction);
        func_00282DD8(obj + 0xd0, obj + 0xc0, normal);
        func_00282F20(obj + 0xd0, obj + 0xd0, 1.0f);
        func_00282DD8(obj + 0xe0, obj + 0xd0, obj + 0xc0);
        *(float *)(obj + 0xcc) = *(float *)(obj + 0xdc) = *(float *)(obj + 0xec) = 0.0f;
        state->duration = state->timer = 50;
        state->scale2 = scale * 2.0f;
        state->scale4 = scale * 4.0f;
        state->a2 = a2;
        state->a3 = a3;
        state->a4 = a4;
        state->a5 = a5;
        state->a6 = a6;
        state->a7 = a7;
        state->scale = scale;
        qcopy(sphere, obj + 0x10);
        sphere[3] = scale * 3.0f;
        if (func_00283DB8(sphere, 128.0f) == 1) {
            state->delay = 8;
            state->fade = 0.125f;
            if (func_00282E48(position, D_L05_001B9580.position) < 48.0f && shake) {
                char *camera = (char *)&D_L05_001B9580;
                *(int *)(camera + 0x16c) = 0;
                *(int *)(camera + 0x168) = 33;
                *(float *)(camera + 0x160) = 0.075f;
            }
            if (state->visible) {
                func_00282CF0(delta, obj + 0x10, D_L05_001B9580.position);
                func_00282F20(delta, delta, 1.0f);
                if (1.57079637f - func_002831B0(func_00282DB0(delta, D_L05_001B9580.forward)) < 0.45378566f)
                    state->visible = 1;
                else
                    state->visible = 0;
            }
        } else {
            state->delay = 0;
            state->visible = 0;
        }
        func_PAL_L05_0039C0D8(obj, normal);
    }
    return obj;
}
