#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F413108;

extern s32 D_L12_001B29C8[];

extern float math_random_float_range(char *, float, float);
extern s32 math_random_int_range(s32, s32);
extern void FastVecAdd(void *, void *, char *);
extern void moby_transform_joint_to_world(char *, s32, void *);
extern void part_spawn_scaling(void *, void *, s32, s32, s32, s32, s32, s32);

/* Sprays the flame sprites of the object's grabbed target: while the target is the live flame moby it draws two bursts at each of its two hand points. */
void guard_spray_flame_sprites(char *moby)
{
    V4_F413108 handA, handB, origin, offset;
    char *vars = *(char **)(moby + 0x68);
    char *partner = *(char **)(vars + 0x2F8);
    s32 bigSize, smallSize, partnerState;

    if (partner != 0 && *(short *)(partner + 0xAA) == 0x114B /* moby class 4427 */) {
        partnerState = *(u8 *)(partner + 0x20);
        if (partnerState != 0xFE) {
            if (partnerState != 0xFD) {
                offset.q = 0;
                offset.f[2] = -(math_random_float_range(partner, 1.7f, 3.0f) * 0.016666668f);
                origin.q = offset.q;
                FastVecAdd(&origin, &origin, vars + 0x1A0);
                moby_transform_joint_to_world(*(char **)(vars + 0x2F8), 5, &handA);
                moby_transform_joint_to_world(*(char **)(vars + 0x2F8), 6, &handB);
                if (D_L12_001B29C8[0] & 1) {
                    part_spawn_scaling(&handA, &origin, 0xCF0000FF, 0xCF, math_random_int_range(0x12, 0x16), 0x28, -10, 1);
                    part_spawn_scaling(&handB, &origin, 0xCF0000FF, 0xCF, math_random_int_range(0x12, 0x16), 0x28, -10, 1);
                } else {
                    part_spawn_scaling(&handA, &origin, 0x6000FFFF, 0x80, math_random_int_range(0x14, 0x18), 0x50, -10, 1);
                    part_spawn_scaling(&handB, &origin, 0x6000FFFF, 0x80, math_random_int_range(0x14, 0x18), 0x50, -10, 1);
                }
                bigSize = math_random_int_range(10, 0x19);
                smallSize = math_random_int_range(10, 15);
                part_spawn_scaling(&handA, &origin, 0xEFFF7F4F, 0xFF0000, smallSize, bigSize, -bigSize, 1);
                bigSize = math_random_int_range(10, 0x19);
                smallSize = math_random_int_range(10, 15);
                part_spawn_scaling(&handB, &origin, 0xEFFF7F4F, 0xFF0000, smallSize, bigSize, -bigSize, 1);
            }
        }
    }
}
