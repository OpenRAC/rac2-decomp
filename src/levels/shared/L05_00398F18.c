#include "common.h"
extern char *CreateMoby(int);
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
extern struct Camera98 g_hero_l05_state;
extern void func_306660(void *, void *, void *);
extern void func_3068F8(void *, void *, float);
extern void func_33C3F8(void *, void *, int);
extern void func_306748(void *, void *, void *);
extern int func_307840(void *, float);
extern float func_3067D8(void *, void *);
extern float func_306720(void *, void *);
extern float func_306C38(float);
extern void EmitScaledParticleBurst(void *, void *);
/* Creates a shockwave effect object at a position, may shake the camera when the player is
   close, and checks if it is on screen. */
char *func_L05_00398F18(void *position, int shake, int a2, int a3, int a4, int a5, int a6, int a7, float scale)
{
    float direction[4], normal[4], sphere[4], delta[4];
    char *obj;
    struct EffectState98 *state;
    obj = CreateMoby(0x12e8);
    if (obj) {
        state = *(struct EffectState98 **)(obj + 0x68);
        *(unsigned char *)(obj + 0x30) = 0xff;
        *(unsigned short *)(obj + 0x32) = 0xff;
        obj[0x20] = 0;
        qcopy(obj + 0x10, position);
        *(float *)(obj + 0x1c) = 1.0f;
        func_306660(direction, g_hero_l05_state.position, obj + 0x10);
        func_3068F8(direction, direction, 1.0f);
        func_33C3F8(obj + 0x10, normal, 1);
        qcopy(obj + 0xc0, direction);
        func_306748(obj + 0xd0, obj + 0xc0, normal);
        func_3068F8(obj + 0xd0, obj + 0xd0, 1.0f);
        func_306748(obj + 0xe0, obj + 0xd0, obj + 0xc0);
        *(float *)(obj + 0xcc) = *(float *)(obj + 0xdc) = *(float *)(obj + 0xec) = 0.0f;
        state->duration = state->timer = 60;
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
        if (func_307840(sphere, 128.0f) == 1) {
            state->delay = 10;
            state->fade = 0.1f;
            if (func_3067D8(position, g_hero_l05_state.position) < 48.0f && shake) {
                char *camera = (char *)&g_hero_l05_state;
                *(int *)(camera + 0x16c) = 0;
                *(int *)(camera + 0x168) = 40;
                *(float *)(camera + 0x160) = 0.075f;
            }
            if (state->visible) {
                func_306660(delta, obj + 0x10, g_hero_l05_state.position);
                func_3068F8(delta, delta, 1.0f);
                if (1.57079637f - func_306C38(func_306720(delta, g_hero_l05_state.forward)) < 0.45378566f)
                    state->visible = 1;
                else
                    state->visible = 0;
            }
        } else {
            state->delay = 0;
            state->visible = 0;
        }
        EmitScaledParticleBurst(obj, normal);
    }
    return obj;
}
