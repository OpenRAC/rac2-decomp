#include "common.h"

typedef int BurstVector __attribute__((mode(TI)));
extern float D_L05_001B105C __attribute__((sda));
extern float D_L05_001B1060 __attribute__((sda));
extern float D_L05_001B1064 __attribute__((sda));
extern float D_L05_001B1068 __attribute__((sda));
extern float D_L05_001B106C __attribute__((sda));
extern float D_L05_001B1070 __attribute__((sda));
extern float D_L05_001B1074 __attribute__((sda));
extern char D_L05_001B96C0[];
extern u8 *D_L05_001FF240[] NOT_SDA;
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_002C2210(void *, u32, f32, f32, u32, u32, s32, void *, f32, s32);
extern int func_00283CF0(float);

/* Emits count pairs of sprites (func_002C2210) at a jittered pos, each heading along
   the direction to D_L05_001B96C0 turned by a random angle about the up axis. */
void func_L05_00419F10(float *pos, int count, int color, char *owner)
{
    float dir[4], tmp[4], toward[4], up[4], half[4];
    int i, sign;
    float size, angle;
    char *sprite;

    *(BurstVector *)up = 0;
    up[2] = 1.0f;
    up[3] = 1.0f;
    if (*(int *)(*(char **)(owner + 0x68) + 0x30)) {
        D_L05_001B105C = 0.1f;
        D_L05_001B1060 = 6.0f;
        D_L05_001B1064 = 2.0f;
        D_L05_001B1068 = 10.0f;
    }
    FastVecSub(toward, D_L05_001B96C0, pos);
    vec_scale_to_length(half, toward, 0.5f);
    toward[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878(D_L05_001B1070, D_L05_001B1074);
        sign = func_002A77E0(2);
        if (!sign)
            sign = sign - 1;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(dir, toward, up, angle);
        vec_scale_to_length(dir, dir, func_002A7878(D_L05_001B105C, D_L05_001B1060) * (1.0f / 60.0f));
        dir[2] = func_002A7878(D_L05_001B1064, D_L05_001B1068) * (1.0f / 60.0f);
        FastVecAdd(tmp, pos, half);
        pos[0] += func_002A78D8(0.0f, 0.15f);
        pos[1] += func_002A78D8(0.0f, 0.15f);
        pos[2] += func_002A78D8(0.0f, 0.15f);
        sprite = func_002C2210(pos, 60, size * 0.1f, size, color, 0, sign, dir, D_L05_001B106C, 0);
        if (sprite) {
            sprite[2] = D_L05_001FF240[97][6];
            sprite[9] = FloatToInt(4.0f) + 0x70;
        }
        sprite = func_002C2210(pos, 60, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, dir,
                               D_L05_001B106C, 0);
        if (sprite) {
            sprite[2] = D_L05_001FF240[97][6];
            sprite[9] = FloatToInt(4.0f) + 0x70;
        }
    }
}
