#include "include_asm.h"

#include "common.h"
typedef int TI128_00325C50 __attribute__((mode(TI)));
typedef union { TI128_00325C50 q; float f[4]; } Vec_00325C50;
extern void euler_rotation_basis(void *, void *);
extern void moby_copy_joint_transform_to_object(void *, void *, int, int);
extern void multiply_matrix3x3(void *, void *, void *);
extern int math_random_int_below(int);
extern void part_spawn_drifting_puff_pair_pal(void *, int, void *);

void enemy_attach_turn_child_parts_pal(float angle, char *parent, char **children, int randomize, void *effect)
{
    char rotation[0x30] __attribute__((aligned(16)));
    Vec_00325C50 euler;
    Vec_00325C50 position;
    int i;

    euler.q = 0;
    euler.f[2] = angle;
    euler_rotation_basis(rotation, &euler);
    for (i = 1; i >= 0; i--) {
        moby_copy_joint_transform_to_object(parent, *children, (unsigned char)(*children)[0xBC], 0);
        multiply_matrix3x3(*children + 0xC0, *children + 0xC0, rotation);
        if (randomize != 0 && math_random_int_below(6) == 0) {
            qcopy(&position, *children + 0x10);
            part_spawn_drifting_puff_pair_pal(&position, 1, effect);
        }
        children++;
    }
}

