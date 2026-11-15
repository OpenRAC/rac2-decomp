#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_random_direction(void *, float, float);
extern int math_random_int_below(int);
extern void *part_spawn_hero_relative(void *, void *, int, unsigned char, unsigned char, int, float);
extern void FastVecAdd(void *, void *, void *);
extern float D_00189F08 __attribute__((nosda));
extern float ref_L01_00397EB0_00 __attribute__((sda));
extern float ref_L01_00397EB0_01 __attribute__((sda));
extern unsigned char ref_L01_00397EB0_02 __attribute__((sda));
extern int ref_L01_00397EB0_03 __attribute__((sda));
extern float ref_L01_00397EB0_04 __attribute__((sda));
extern float ref_L01_00397EB0_05 __attribute__((sda));
extern float ref_L01_00397EB0_06 __attribute__((sda));
extern int ref_L01_00397EB0_07 __attribute__((sda));
extern float ref_L01_00397EB0_08 __attribute__((sda));
extern void FastVecAdd(void *, void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);

void func_PAL_L01_0039B2D0(char *a0)
{
    TI128 m, v1, v2;
    int i;
    int b;

    if (*(unsigned char *)(a0 + 0x20) == 1) {
        FastVecScale(&m, a0, 0.0009765625f);
    } else {
        moby_transform_joint_to_world(a0, 0, &m);
        if (((float *)&m)[2] < D_00189F08) return;
    }
    i = 2;
    vec_random_direction(&v1, ref_L01_00397EB0_00 * 0.020000001f, ref_L01_00397EB0_01 * 0.020000001f);
    b = ref_L01_00397EB0_02;
    part_spawn_hero_relative(&m, &v1, ref_L01_00397EB0_03, b, math_random_int_below(255), 0, ref_L01_00397EB0_04);
    do {
        i--;
        vec_random_direction(&v2, ref_L01_00397EB0_05 * 0.020000001f, ref_L01_00397EB0_06 * 0.020000001f);
        FastVecAdd(&v1, &v1, &v2);
        b = ref_L01_00397EB0_02;
        part_spawn_hero_relative(&m, &v1, ref_L01_00397EB0_07, b, math_random_int_below(255), 0, ref_L01_00397EB0_08);
    } while (i >= 0);
}
