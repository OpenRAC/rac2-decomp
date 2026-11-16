#include "include_asm.h"

#include "common.h"
typedef unsigned int U128 __attribute__((mode(TI)));
typedef union { U128 q; f32 f[4]; } SplitVector;
typedef struct {
    unsigned char b0, b1, b2, b3;
    int x4;
    unsigned char b8, b9;
    short hA;
    int xC;
    SplitVector v10, v20, v30;
} Particle6DD8;
extern unsigned char *g_part_tex_drifting, *g_part_tex_spark_trail_table;
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int FloatToInt(float f);
typedef int V4_Fc3cb9262 __attribute__((mode(TI)));
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void *part_alloc(int);
extern unsigned char *g_part_tex_drifting;
extern int FloatToInt(float f);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* Spawns a spark trail particle from head_pos along direction, living for life frames. */
char *part_spawn_trail_2_pal(void *head_pos, void *direction, int life, float width)
{
    V4_Fc3cb9262 trail_vec;
    Particle6DD8 *particle;
    int size_byte;
    SplitVector *velocity_slot;

    particle = part_alloc(0x5A);
    if (particle != 0) {
        particle->x4 = 0x7FFFFFFF;
        particle->xC = 0x7FFFFFFF;
        size_byte = FloatToInt(2.0f);
        particle->b9 = (char)(size_byte + 0x20);
        particle->b3 = 0x48;
        particle->b1 = 3;
        particle->b2 = *g_part_tex_spark_trail_table;
        velocity_slot = &particle->v30;
        qcopy_nc(velocity_slot, direction);
        velocity_slot->f[3] = width;
        qcopy_nc(&particle->v10, head_pos);
        vec_scale_to_length(&trail_vec, velocity_slot, 0.9f);
        FastVecSub(&particle->v20, head_pos, &trail_vec);
        particle->hA = life;
        particle->v10.f[3] = 0.05f;
        particle->b8 = (char)(*(unsigned char *)&particle->hA - 0xC);
        particle->v20.f[3] = 2.0f;
    }
    return (char *)particle;
}
