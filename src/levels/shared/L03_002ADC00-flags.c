#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

typedef union { TI128 quad; float values[4]; } ResidentVector;
extern unsigned char g_hero_state[];
extern void euler_to_matrix(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);

/* Moves the object the hero is holding to a spot just in front of the hero. */
void hero_place_held_object_in_front(void)
{
    ResidentVector offset;
    TI128 matrix[4];
    unsigned char *resident = g_hero_state;
    if (*(short *)(resident + 0x6BC) != 0 && *(int *)(resident + 0x660) == 0) {
        *(float *)(*(unsigned char **)(resident + 0x2290) + 0xF4) = *(float *)(resident + 0x6B0);
        offset.quad = 0;
        offset.values[2] = 2.0f;
        euler_to_matrix(matrix, *(unsigned char **)(resident + 0x2290) + 0xF0);
        transform_vector(&offset, &offset, matrix);
        FastVecAdd(*(unsigned char **)(resident + 0x2290) + 0x10, resident + 0x80, &offset);
    }
}
