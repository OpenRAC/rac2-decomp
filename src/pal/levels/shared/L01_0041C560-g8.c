#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void FastVecAdd(void *, void *, void *);
extern float D_L01_001B1A9C __attribute__((sda));
extern float D_L01_001B1AA0 __attribute__((sda));
extern float D_L01_001B1AA4 __attribute__((sda));
extern float D_L01_001B1AA8 __attribute__((sda));
extern unsigned char D_L01_001B1AAC __attribute__((sda));
extern int D_L01_001B1AB0 __attribute__((sda));
extern int D_L01_001B1AB4 __attribute__((sda));
extern float D_L01_001B1AB8 __attribute__((sda));
extern float D_L01_001B1ABC __attribute__((sda));
extern void FastVecScale(void *, void *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_random_direction(void *, float, float);
extern int math_random_int_below(int);
extern void *part_spawn_hero_relative(void *, void *, int, unsigned char, unsigned char, int, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);

/* builds the tilt of a hanging chain over three steps and draws it */
void func_PAL_L01_0041C560(char *a0)
{
    TI128 m, v1, v2;
    int i;
    int b;

    if (*(unsigned char *)(a0 + 0x20) == 1) {
        FastVecScale(&m, a0, 0.0009765625f);
    } else {
        moby_transform_joint_to_world(a0, 0, &m);
    }
    i = 2;
    vec_random_direction(&v1, D_L01_001B1A9C * 0.020000001f, D_L01_001B1AA0 * 0.020000001f);
    b = D_L01_001B1AAC;
    part_spawn_hero_relative(&m, &v1, D_L01_001B1AB0, b, math_random_int_below(255), 0, D_L01_001B1AB8);
    do {
        i--;
        vec_random_direction(&v2, D_L01_001B1AA4 * 0.020000001f, D_L01_001B1AA8 * 0.020000001f);
        FastVecAdd(&v1, &v1, &v2);
        b = D_L01_001B1AAC;
        part_spawn_hero_relative(&m, &v1, D_L01_001B1AB4, b, math_random_int_below(255), 0, D_L01_001B1ABC);
    } while (i >= 0);
}
