#include "names.h"
/* func_00325C50: func_002833F0 takes (out, in): the angle is the third word of a zeroed
 * euler vector, from which it builds the rotation matrix (the old draft passed the angle
 * as a float argument). The two children are re-read through the cursor at each use,
 * and the position copy is qcopy(). */
#include "common.h"

typedef int TI128_00325C50 __attribute__((mode(TI)));
typedef union { TI128_00325C50 q; float f[4]; } Vec_00325C50;

extern void euler_rotation_basis(void *, void *);
extern void moby_copy_joint_transform_to_object(void *, void *, int, int);
extern void multiply_matrix3x3(void *, void *, void *);
extern int math_random_int_below(int);
extern void part_spawn_drifting_puff_pair(void *, int, void *);

/* Attaches the two child parts to their parent, turns them by the given angle and sometimes puffs out a small effect at each one. */
void enemy_attach_turn_child_parts(float angle, char *parent, char **children, int randomize, void *effect)
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
            part_spawn_drifting_puff_pair(&position, 1, effect);
        }
        children++;
    }
}
