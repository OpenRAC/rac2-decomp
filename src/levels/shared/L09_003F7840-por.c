#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F3F7840;

extern s32 D_L09_001B2388[];

extern float math_random_float_range(char *, float, float);
extern s32 math_random_int_range(s32, s32);
extern void FastVecAdd(void *, void *, char *);
extern void moby_transform_joint_to_world(char *, s32, void *);
extern void part_spawn_scaling(void *, void *, s32, s32, s32, s32, s32, s32);

/* Sprays the flame sprites of the object's grabbed target: while the target is the live flame moby it draws two bursts at each of its two hand points. */
void trooper_draw_flame_sprays(char *moby)
{
    V4_F3F7840 handA, handB, offset, temp;
    char *vars = *(char **)(moby + 0x68);
    char *target = *(char **)(vars + 0x2F8);
    s32 bigSize, smallSize, targetState;

    if (target != 0 && *(short *)(target + 0xAA) == 0xD0E /* Megacorp Trooper Torso */) {
        targetState = *(u8 *)(target + 0x20);
        if (targetState != 0xFE) {
            if (targetState != 0xFD) {
                temp.q = 0;
                temp.f[2] = -(math_random_float_range(target, 1.7f, 3.0f) * 0.016666668f);
                offset.q = temp.q;
                FastVecAdd(&offset, &offset, vars + 0x1A0);
                moby_transform_joint_to_world(*(char **)(vars + 0x2F8), 5, &handA);
                moby_transform_joint_to_world(*(char **)(vars + 0x2F8), 6, &handB);
                if (D_L09_001B2388[0] & 1) {
                    part_spawn_scaling(&handA, &offset, 0xCF0000FF, 0xCF, math_random_int_range(0x12, 0x16), 0x28, -10, 1);
                    part_spawn_scaling(&handB, &offset, 0xCF0000FF, 0xCF, math_random_int_range(0x12, 0x16), 0x28, -10, 1);
                } else {
                    part_spawn_scaling(&handA, &offset, 0x6000FFFF, 0x80, math_random_int_range(0x14, 0x18), 0x50, -10, 1);
                    part_spawn_scaling(&handB, &offset, 0x6000FFFF, 0x80, math_random_int_range(0x14, 0x18), 0x50, -10, 1);
                }
                bigSize = math_random_int_range(10, 0x19);
                smallSize = math_random_int_range(10, 15);
                part_spawn_scaling(&handA, &offset, 0xEFFF7F4F, 0xFF0000, smallSize, bigSize, -bigSize, 1);
                bigSize = math_random_int_range(10, 0x19);
                smallSize = math_random_int_range(10, 15);
                part_spawn_scaling(&handB, &offset, 0xEFFF7F4F, 0xFF0000, smallSize, bigSize, -bigSize, 1);
            }
        }
    }
}
