#include "common.h"

typedef union { int q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_002B38B8(u8 *);
extern void func_002A7398(u8 *, s32, s32);
extern void func_002A7470(u8 *, s32, s32, s32);
extern void func_00282CC0(void *, void *, void *);
extern void func_L03_003CC478(u8 *, void *, void *, s32);
extern s32 func_00282948(void *);
extern void func_0029F338(u8 *);

void func_L03_003CC238(u8 *object)
{
    Vector position, velocity;
    f32 scale;
    u8 *vars;
    switch (object[0x20]) {
    case 0:
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (func_002B38B8(object) != 0) {
            f32 initial;
            func_002A7750(object, 2, -1);
            func_002A7398(object, 1, 0);
            *(s32 *)(object + 0x98) = 0;
            initial = *(f32 *)(object + 0x2C) / *(f32 *)(*(u8 **)(object + 0x24) + 0x24);
            position.q = 0;
            position.f[2] = initial * 0.05833333730697632f;
            func_L03_003CC478(object, object + 0x10, &position, 0x3C);
        }
        break;
    case 2:
        if ((object[0x60] & 2) != 0) {
            func_002A7750(object, 3, -1);
            if (object[0x43] != 2)
                func_002A7470(object, 2, 0, 1);
        }
        break;
    case 3:
        if (func_002B38B8(object) == 0) {
            func_002A7750(object, 4, -1);
            func_002A7398(object, 3, 0);
            scale = *(f32 *)(object + 0x2C) / *(f32 *)(*(u8 **)(object + 0x24) + 0x24);
            position.q = 0;
            position.f[2] = scale * 3.5f;
            func_00282CC0(&position, &position, object + 0x10);
            velocity.q = 0;
            scale *= 0.05833333730697632f;
            velocity.f[2] = scale;
            func_L03_003CC478(object, &position, &velocity, 0x3C);
            *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
        }
        break;
    case 4:
        if ((object[0x60] & 2) != 0) {
            func_002A7750(object, 1, -1);
            if (object[0x43] != 0)
                func_002A7470(object, 0, 0, 1);
        }
        break;
    case 5:
        vars = *(u8 **)(object + 0x68);
        func_00282CC0(object + 0x10, object + 0x10, vars);
        if (func_00282948(vars + 0x10) != 0)
            func_0029F338(object);
        break;
    }
}
