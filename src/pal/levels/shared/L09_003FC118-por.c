#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_PAL_F3FC118;

extern s32 g_frame_l09_counter[];

extern float math_random_float_range(char *, float, float);
extern s32 math_random_int_range(s32, s32);
extern void FastVecAdd(void *, void *, char *);
extern void moby_transform_joint_to_world(char *, s32, void *);
extern char *part_spawn_scaling(void *, void *, s32, s32, s32, s32, s32, s32);

/* Sprays the flame sprites of the trooper's grabbed target (PAL). func_PAL_L09_003FC118, the PAL copy of func_L09_003F7840: the same C, where 1/60 becomes 1/50 and the random fifth argument of each burst takes the 5/6 scale. Sprays the flame sprites of the object's grabbed target: while the target is the live flame moby it draws two bursts at each of its two hand points. */
void trooper_draw_flame_sprays_pal(char *moby)
{
    V4_PAL_F3FC118 a, b, velocity, zero;
    char *vars = *(char **)(moby + 0x68);
    char *target = *(char **)(vars + 0x2F8);
    s32 big, small, target_state;

    if (target != 0 && *(short *)(target + 0xAA) == 0xD0E) {
        target_state = *(u8 *)(target + 0x20);
        if (target_state != 0xFE) {
            if (target_state != 0xFD) {
                zero.q = 0;
                zero.f[2] = -(math_random_float_range(target, 1.7f, 3.0f) * 0.020000001f);
                velocity.q = zero.q;
                FastVecAdd(&velocity, &velocity, vars + 0x1A0);
                moby_transform_joint_to_world(*(char **)(vars + 0x2F8), 5, &a);
                moby_transform_joint_to_world(*(char **)(vars + 0x2F8), 6, &b);
                if (g_frame_l09_counter[0] & 1) {
                    part_spawn_scaling(&a, &velocity, 0xCF0000FF, 0xCF, ((s32)math_random_int_range(0x12, 0x16) * 5 + 2) / 6, 0x28, -10, 1);
                    part_spawn_scaling(&b, &velocity, 0xCF0000FF, 0xCF, ((s32)math_random_int_range(0x12, 0x16) * 5 + 2) / 6, 0x28, -10, 1);
                } else {
                    part_spawn_scaling(&a, &velocity, 0x6000FFFF, 0x80, ((s32)math_random_int_range(0x14, 0x18) * 5 + 2) / 6, 0x50, -10, 1);
                    part_spawn_scaling(&b, &velocity, 0x6000FFFF, 0x80, ((s32)math_random_int_range(0x14, 0x18) * 5 + 2) / 6, 0x50, -10, 1);
                }
                big = math_random_int_range(10, 0x19);
                small = math_random_int_range(10, 15);
                part_spawn_scaling(&a, &velocity, 0xEFFF7F4F, 0xFF0000, (small * 5 + 2) / 6, big, -big, 1);
                big = math_random_int_range(10, 0x19);
                small = math_random_int_range(10, 15);
                part_spawn_scaling(&b, &velocity, 0xEFFF7F4F, 0xFF0000, (small * 5 + 2) / 6, big, -big, 1);
            }
        }
    }
}
