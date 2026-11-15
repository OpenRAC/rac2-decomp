#include "common.h"

extern void euler_rotation_basis(void *, void *);
extern void FastVecScale(void *, void *, float);
extern int FastTweenColor(int, int, float);
extern void moby_set_light_color(void *, int);
extern void vec_decode_byte_color(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void func_002A10E8(void *);

/* Scales the first child by the timer, then places the other three relative to it from their
   stored offsets and rotations; each child takes its colour faded by the same timer. */
void moby_position_effect_children(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char offset[16] __attribute__((aligned(16)));
    char rotation[16] __attribute__((aligned(16)));
    char **slot;
    char *rotations = sub + 0x4C;
    char *offsets = sub + 0x40;
    int i;

    *(unsigned short *)(*(char **)(sub + 0x10) + 0x34) &= 0xFFFE;
    *(unsigned char *)(*(char **)(sub + 0x10) + 0x31) = 1;
    *(int *)(*(char **)(sub + 0x10) + 0x98) = *(int *)(*(int *)(*(char **)(sub + 0x10) + 0x24) + 0x10);
    euler_rotation_basis(*(char **)(sub + 0x10) + 0xC0, *(char **)(sub + 0x10) + 0xF0);
    FastVecScale(*(char **)(sub + 0x10) + 0xC0, *(char **)(sub + 0x10) + 0xC0, *(float *)(sub + 0xC));
    FastVecScale(*(char **)(sub + 0x10) + 0xD0, *(char **)(sub + 0x10) + 0xD0, *(float *)(sub + 0xC));
    moby_set_light_color(*(char **)(sub + 0x10), FastTweenColor(0x80FF8000, *(int *)(sub + 0x30), *(float *)(sub + 0xC)));
    func_002A10E8(*(char **)(sub + 0x10));
    for (i = 1; i < 4; i++, rotations += 4, offsets += 4) {
        int index = i * 4;
        char *children = sub + 0x10;
        slot = (char **)(children + index);
        if (*slot != 0) {
            *(unsigned short *)(*slot + 0x34) &= 0xFFFE;
            *(unsigned char *)(*slot + 0x31) = 1;
            *(int *)(*slot + 0x98) = *(int *)(*(int *)(*slot + 0x24) + 0x10);
            vec_decode_byte_color(offset, offsets);
            matrix_mul_vec3(offset, offset, *(char **)(sub + 0x10) + 0xC0);
            FastVecAdd(*slot + 0x10, *(char **)(sub + 0x10) + 0x10, offset);
            vec_decode_byte_color(rotation, rotations);
            euler_rotation_basis(*slot + 0xC0, rotation);
            multiply_matrix3x3(*slot + 0xC0, *(char **)(sub + 0x10) + 0xC0, *slot + 0xC0);
            moby_set_light_color(*slot, FastTweenColor(0x80FF8000, *(int *)(sub + index + 0x30), *(float *)(sub + 0xC)));
            func_002A10E8(*slot);
        }
    }
}
