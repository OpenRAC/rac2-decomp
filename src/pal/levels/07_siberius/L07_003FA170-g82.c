#include "include_asm.h"

#include "common.h"
extern u8 *D_L07_001B22DC[] __attribute__((sda));
typedef struct { u8 pad[0x34]; f32 y; u8 rest[0x80 - 0x38]; } Record5B50;
extern Record5B50 *D_L07_001B23CC[] __attribute__((sda));
typedef struct {
    u8 pad[0x80];
    f32 position[4];
    f32 rotation[4];
    u8 rest[0x33C - 0xA0];
    u8 *platform;
} Player5B50;
extern Player5B50 D_L07_00189E20;
extern u8 D_L07_001B9200[];
extern f32 D_L07_001B0F3C __attribute__((sda));
extern f32 D_L07_001B0F48 __attribute__((sda));
extern f32 func_00282C48(f32);
extern f32 func_00283248(f32, f32);
extern u8 *func_002AD0B0(void *);
extern s32 func_002ACBC8(void *, s32);
extern void func_PAL_L00_002B9CD8(void *, void *, s32, s32);

void func_PAL_L07_003FA300(u8 *obj)
{
    u8 *state = *(u8 **)(obj + 0x68);
    u8 *other = D_L07_001B22DC[0] + (*(s32 *)(state + 0xE8) << 8);
    f32 diff = *(f32 *)(obj + 0x14) - D_L07_001B23CC[0][*(s32 *)(state + 0xEC)].y;
    f32 step, saved;
    f32 max = 0.20000002f;
    u8 *p;
    if (*(f32 *)(other + 0x18) < 218.5f) {
        step = diff + 4.0f;
        if (func_00282C48(step) < D_L07_001B0F3C) {
            if (step < 0.0f) step = -(step + D_L07_001B0F3C);
            else step = D_L07_001B0F3C - step;
            if (step > max) step = 0.20000002f;
            else if (step < -max) step = -max;
            *(f32 *)(obj + 0x14) += step;
            *(f32 *)(state + 0x54) = 0.0f;
            *(f32 *)(state + 0x64) += step;
        }
    }
    if (*(f32 *)(other + 0x18) > 199.7f) {
        step = diff - 4.0f;
        if (func_00282C48(step) < D_L07_001B0F3C) {
            if (step < 0.0f) step = -(step + D_L07_001B0F3C);
            else step = D_L07_001B0F3C - step;
            if (step > max) step = 0.20000002f;
            else if (step < -max) step = -max;
            *(f32 *)(obj + 0x14) += step;
            *(f32 *)(state + 0x54) = 0.0f;
            *(f32 *)(state + 0x64) += step;
        }
    }
    if (*(f32 *)(other + 0x18) > 202.0f && *(f32 *)(other + 0x18) < 204.0f && D_L07_00189E20.platform == other) {
        p = func_002AD0B0(other);
        if (p != 0 && *(f32 *)(p + 0x18) > 0.0f && !func_002ACBC8(D_L07_001B9200, *(s32 *)(state + 0xEC))) {
            saved = D_L07_00189E20.rotation[2];
            D_L07_00189E20.rotation[2] = func_00283248(D_L07_00189E20.position[0] - *(f32 *)(other + 0x10), D_L07_00189E20.position[1] - *(f32 *)(other + 0x14));
            func_PAL_L00_002B9CD8(D_L07_00189E20.position, D_L07_00189E20.rotation, 0x6F, 1);
            D_L07_00189E20.rotation[2] = saved;
            func_PAL_L00_002B9CD8(D_L07_00189E20.position, D_L07_00189E20.rotation, 0, 0);
        }
    }
    if (func_002ACBC8(obj + 0x10, *(s32 *)(state + 0xEC))) {
        *(f32 *)(obj + 0x18) = *(f32 *)(other + 0x18) + D_L07_001B0F48;
        *(f32 *)(state + 0x68) = *(f32 *)(obj + 0x18);
        *(f32 *)(state + 0x58) = 0.0f;
    }
}
