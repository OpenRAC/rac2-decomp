#include "include_asm.h"

#include "common.h"
typedef int BossQuadword __attribute__((mode(TI)));
extern u8 *D_L16_001B2C0C;
extern float D_L16_001B9B00[4];
extern float D_L16_001B18CC __attribute__((sda));
extern float D_L16_001B18D0 __attribute__((sda));
extern float D_L16_001B18D4 __attribute__((sda));
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283248(float, float);
extern u8 *func_0029EFD0(int);
extern void func_002B37E8(u8 *, u8 *);
extern void func_002A7750(u8 *, int, int);
extern void func_00282C90(void *);
extern int func_00283DB8(void *, float);
extern void func_002830C0(void *, void *, void *);
extern float func_00283B98(float, float), func_00283180(float), func_00283198(float);
extern int func_00283CF0(float);
extern void func_0029F338(void *), func_002A0F48(void *);
extern void func_PAL_L16_00418580(u8 *);

/* Creates an aimed projectile or a random trajectory across the arena. */
u8 *func_PAL_L16_00418260(u8 *moby, int aimed)
{
    float position[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *object = func_0029EFD0(0x9b0);
    u8 *motion;
    float angle;
    if (object) {
        func_002B37E8(object, moby);
        func_002A7750(object, 0, -1);
        motion = *(u8 **)(object + 0x68);
        if (aimed) {
            *(BossQuadword *)(object + 0x10) = *(BossQuadword *)D_L16_001B9B00;
            *(float *)(object + 0x18) += 20.0f;
            angle = func_00283B98(func_00283248(*(float *)(*(u8 **)(state + 0x24c) + 0x10) - *(float *)(object + 0x10), *(float *)(*(u8 **)(state + 0x24c) + 0x14) - *(float *)(object + 0x14)), 1.5707964f);
            position[0] = func_00283180(angle) * D_L16_001B18CC;
            position[1] = func_00283198(angle) * D_L16_001B18CC;
            position[2] = 0.0f;
            func_00282CC0(position, position, moby + 0x10);
            position[2] = *(float *)(state + 0x264) + D_L16_001B18D0;
            *(BossQuadword *)(motion + 0x10) = *(BossQuadword *)position;
            func_00282CF0(target, position, object + 0x10);
            func_00282D30(motion, target, 1.0f / D_L16_001B18D4);
            *(int *)(motion + 0x30) = ((s32)(func_00283CF0(D_L16_001B18D4 * 1.2f)) * 5 + 2) / 6;
        } else {
            u8 *scatterState = *(u8 **)(moby + 0x68);
            func_00282C90(position);
            position[0] = func_002A7878(-1.0f, 1.0f);
            position[2] = func_002A7878(-1.0f, 1.0f);
            func_00282C90(target);
            target[0] = func_002A7878(-1.0f, 1.0f);
            target[2] = func_002A7878(-1.0f, 1.0f);
            position[1] = func_002A77E0(2) ? 1.0f : -1.0f;
            target[1] = -position[1];
            func_002830C0(position, position, D_L16_001B2C0C + *(int *)(scatterState + 0x19c) * 128);
            position[3] = 3.0f;
            if (func_00283DB8(position, 255.0f) != -1) { func_0029F338(object); return 0; }
            func_002830C0(target, target, D_L16_001B2C0C + *(int *)(scatterState + 0x19c) * 128);
            *(BossQuadword *)(object + 0x10) = *(BossQuadword *)position;
            *(BossQuadword *)(motion + 0x10) = *(BossQuadword *)target;
            func_00282CF0(motion, target, position);
            func_00282D30(motion, motion, 0.002f);
            *(int *)(motion + 0x30) = 500;
        }
        *(float *)(object + 0xf8) = func_00283248(*(float *)motion, *(float *)(motion + 4));
        *(void (**)(u8 *))(object + 0x64) = func_PAL_L16_00418580;
        func_002A0F48(object);
    }
    return object;
}
