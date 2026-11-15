#include "common.h"

extern void func_002833F0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern int func_00283D38(int, int, float);
extern void func_002AEC18(void *, int);
extern void func_002AE838(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_002A10E8(void *);

/* Scales the first child by the timer, then places the other three relative to it from their
   stored offsets and rotations; each child takes its colour faded by the same timer. */
void func_L02_003C9ED0(char *obj)
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
    SetMobyLightColor(*(char **)(sub + 0x10), FastTweenColor(0x80FF8000, *(int *)(sub + 0x30), *(float *)(sub + 0xC)));
    func_002A10E8(*(char **)(sub + 0x10));
    for (i = 1; i < 4; i++, rotations += 4, offsets += 4) {
        int index = i * 4;
        char *children = sub + 0x10;
        slot = (char **)(children + index);
        if (*slot != 0) {
            *(unsigned short *)(*slot + 0x34) &= 0xFFFE;
            *(unsigned char *)(*slot + 0x31) = 1;
            *(int *)(*slot + 0x98) = *(int *)(*(int *)(*slot + 0x24) + 0x10);
            DecodeByteColorVector(offset, offsets);
            matrix_mul_vec3(offset, offset, *(char **)(sub + 0x10) + 0xC0);
            FastVecAdd(*slot + 0x10, *(char **)(sub + 0x10) + 0x10, offset);
            DecodeByteColorVector(rotation, rotations);
            euler_rotation_basis(*slot + 0xC0, rotation);
            multiply_matrix3x3(*slot + 0xC0, *(char **)(sub + 0x10) + 0xC0, *slot + 0xC0);
            SetMobyLightColor(*slot, FastTweenColor(0x80FF8000, *(int *)(sub + index + 0x30), *(float *)(sub + 0xC)));
            func_002A10E8(*slot);
        }
    }
}
