#include "include_asm.h"
#include "names.h"

/* func_PAL_L12_00417F48, the PAL copy of func_L12_00413108: the same C, where 1/60 becomes 1/50
   and the fifth argument of each func_002BAE50 call is scaled to 50 Hz. */

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
void func_PAL_L12_00417F48(char *obj)
{
    V4_F413108 a, b, org, tmp;
    char *rec = *(char **)(obj + 0x68);
    char *tgt = *(char **)(rec + 0x2F8);
    s32 big, small, st;

    if (tgt != 0 && *(short *)(tgt + 0xAA) == 0x114B) {
        st = *(u8 *)(tgt + 0x20);
        if (st != 0xFE) {
            if (st != 0xFD) {
                tmp.q = 0;
                tmp.f[2] = -(math_random_float_range(tgt, 1.7f, 3.0f) * 0.020000001f);
                org.q = tmp.q;
                FastVecAdd(&org, &org, rec + 0x1A0);
                moby_transform_joint_to_world(*(char **)(rec + 0x2F8), 5, &a);
                moby_transform_joint_to_world(*(char **)(rec + 0x2F8), 6, &b);
                if (D_L12_001B29C8[0] & 1) {
                    part_spawn_scaling(&a, &org, 0xCF0000FF, 0xCF, ((s32)math_random_int_range(0x12, 0x16) * 5 + 2) / 6, 0x28, -10, 1);
                    part_spawn_scaling(&b, &org, 0xCF0000FF, 0xCF, ((s32)math_random_int_range(0x12, 0x16) * 5 + 2) / 6, 0x28, -10, 1);
                } else {
                    part_spawn_scaling(&a, &org, 0x6000FFFF, 0x80, ((s32)math_random_int_range(0x14, 0x18) * 5 + 2) / 6, 0x50, -10, 1);
                    part_spawn_scaling(&b, &org, 0x6000FFFF, 0x80, ((s32)math_random_int_range(0x14, 0x18) * 5 + 2) / 6, 0x50, -10, 1);
                }
                big = math_random_int_range(10, 0x19);
                small = math_random_int_range(10, 15);
                part_spawn_scaling(&a, &org, 0xEFFF7F4F, 0xFF0000, ((s32)small * 5 + 2) / 6, big, -big, 1);
                big = math_random_int_range(10, 0x19);
                small = math_random_int_range(10, 15);
                part_spawn_scaling(&b, &org, 0xEFFF7F4F, 0xFF0000, ((s32)small * 5 + 2) / 6, big, -big, 1);
            }
        }
    }
}
