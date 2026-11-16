#include "include_asm.h"
#include "names.h"

/* func_PAL_L12_00417F48, the PAL copy of func_L12_00413108: the same C, where 1/60 becomes 1/50
   and the fifth argument of each func_002BAE50 call is scaled to 50 Hz. */

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F413108;

extern s32 g_frame_l12_counter[];

extern float math_random_float_range(char *, float, float);
extern s32 math_random_int_range(s32, s32);
extern void FastVecAdd(void *, void *, char *);
extern void moby_transform_joint_to_world(char *, s32, void *);
extern char *part_spawn_scaling(void *, void *, s32, s32, s32, s32, s32, s32);

/* Sprays the flame sprites of the object's grabbed target: while the target is the live flame moby it draws two bursts at each of its two hand points. */
void guard_spray_flame_sprites_pal(char *moby)
{
    V4_F413108 hand_a, hand_b, origin, velocity_tmp;
    char *vars = *(char **)(moby + 0x68);
    char *flame = *(char **)(vars + 0x2F8);
    s32 big, small, flame_state;

    if (flame != 0 && *(short *)(flame + 0xAA) == 0x114B) {
        flame_state = *(u8 *)(flame + 0x20);
        if (flame_state != 0xFE) {
            if (flame_state != 0xFD) {
                velocity_tmp.q = 0;
                velocity_tmp.f[2] = -(math_random_float_range(flame, 1.7f, 3.0f) * 0.020000001f);
                origin.q = velocity_tmp.q;
                FastVecAdd(&origin, &origin, vars + 0x1A0);
                moby_transform_joint_to_world(*(char **)(vars + 0x2F8), 5, &hand_a);
                moby_transform_joint_to_world(*(char **)(vars + 0x2F8), 6, &hand_b);
                if (g_frame_l12_counter[0] & 1) {
                    part_spawn_scaling(&hand_a, &origin, 0xCF0000FF, 0xCF, ((s32)math_random_int_range(0x12, 0x16) * 5 + 2) / 6, 0x28, -10, 1);
                    part_spawn_scaling(&hand_b, &origin, 0xCF0000FF, 0xCF, ((s32)math_random_int_range(0x12, 0x16) * 5 + 2) / 6, 0x28, -10, 1);
                } else {
                    part_spawn_scaling(&hand_a, &origin, 0x6000FFFF, 0x80, ((s32)math_random_int_range(0x14, 0x18) * 5 + 2) / 6, 0x50, -10, 1);
                    part_spawn_scaling(&hand_b, &origin, 0x6000FFFF, 0x80, ((s32)math_random_int_range(0x14, 0x18) * 5 + 2) / 6, 0x50, -10, 1);
                }
                big = math_random_int_range(10, 0x19);
                small = math_random_int_range(10, 15);
                part_spawn_scaling(&hand_a, &origin, 0xEFFF7F4F, 0xFF0000, ((s32)small * 5 + 2) / 6, big, -big, 1);
                big = math_random_int_range(10, 0x19);
                small = math_random_int_range(10, 15);
                part_spawn_scaling(&hand_b, &origin, 0xEFFF7F4F, 0xFF0000, ((s32)small * 5 + 2) / 6, big, -big, 1);
            }
        }
    }
}
