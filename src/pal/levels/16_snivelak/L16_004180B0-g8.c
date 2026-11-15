#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L16_001B18A0 __attribute__((sda));
extern float D_L16_001B18A4;
extern u32 D_L16_001B18A8 __attribute__((sda));
extern u32 D_L16_001B18AC;
extern u32 D_L16_001B18B0;
extern u32 D_L16_001B18B4;
extern u32 D_L16_001B18B8;
extern u32 D_L16_001B18BC;
extern u32 D_L16_001B18C0 __attribute__((sda));
extern u32 D_L16_001B18C4;
extern u32 D_L16_001B18C8;
extern s32 D_L16_001B2648;

extern void moby_transform_joint_to_world(char *, int, void *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_range(s32, s32);
extern char *part_spawn_scaling(void *, void *, u32, s32, s32, s32, s32, s32);

/* func_PAL_L16_004180B0, the PAL copy of func_L16_00412F48: the same C, where the 60 Hz rate
   becomes 0.02 in the loop and the three random lifetimes take the 50 Hz scale. The burst of
   func_L02_00401D38, from the object's two attachment points (func_0029FCC0) instead of a fixed
   pair of vectors. This unit is built with -fno-sched-interblock: retail keeps i++ and the first
   call's arguments in their own blocks. */
void func_PAL_L16_004180B0(char *a0) {
    float v0[4];
    float v1[4];
    float v2[4];
    s32 i;
    float f;

    for (i = 0; i < 2; i++) {
        *(TI128 *)v2 = 0;
        f = math_random_float_range(D_L16_001B18A0, D_L16_001B18A4);
        v2[2] = -(f * 0.020000001f);
        *(TI128 *)v1 = *(TI128 *)v2;
        moby_transform_joint_to_world(a0, i, v0);
        if (D_L16_001B2648 & 1) {
            part_spawn_scaling(v0, v1, D_L16_001B18A8, D_L16_001B18AC, (math_random_int_range(0x12, 0x16) * 5 + 2) / 6, D_L16_001B18C0, -10, 1);
        } else {
            part_spawn_scaling(v0, v1, D_L16_001B18B0, D_L16_001B18B4, (math_random_int_range(0x14, 0x18) * 5 + 2) / 6, D_L16_001B18C4, -10, 1);
        }
        part_spawn_scaling(v0, v1, D_L16_001B18B8, D_L16_001B18BC, (math_random_int_range(0xA, 0xF) * 5 + 2) / 6, D_L16_001B18C8, -10, 1);
    }
}
