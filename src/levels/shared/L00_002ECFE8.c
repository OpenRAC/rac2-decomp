#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
typedef struct {
    Vector4 point[4];
    unsigned int color[4];
    float uv[8];
    unsigned long tag, tex, alpha, test;
} Beam;

extern void func_00281DE8(void *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern void func_00283098(void *, void *, void *);
extern Vector4 D_L00_001B8DC0;

/* Draws a camera-facing quad at each of the given points. */
/* Draw oriented quads at the supplied points. The EE ABI keeps the three
 * float arguments and six integer/pointer arguments in independent banks. */
void func_L00_002ECFE8(float width, float height, float u, char *object,
                        Vector4 *points, int count, unsigned int color0,
                        unsigned int color1, int texture)
{
    Vector4 basis[4];
    Beam beam;
    int i;
    FastVecScale(&basis[0], object + 0xC0, -1.0f);
    FastVecSub(&basis[1], &gCameraPosition_L00, object + 0x10);
    FastVecCross(&basis[2], &basis[1], &basis[0]);
    vec_scale_to_length(&basis[2], &basis[2], width);
    vec_scale_to_length(&basis[0], &basis[0], height);
    basis[0].f[3] = 0; basis[1].f[3] = 0; basis[2].f[3] = 0;
    InitQuadPacketState(&beam, texture, 1, 0x80);
    beam.uv[0] = u; beam.uv[1] = 0; beam.uv[2] = u; beam.uv[3] = 1;
    beam.uv[4] = u + 1; beam.uv[5] = 0; beam.uv[6] = u + 1; beam.uv[7] = 1;
    {
        int j;
        for (j = 0; j < 4; j++) {
            qzero(&beam.point[j]);
            if (j < 2) beam.point[j].f[0] = 0;
            else beam.point[j].f[0] = 1;
            beam.point[j].f[1] = 0;
            beam.point[j].f[2] = (j & 1) ? 1 : -1;
            beam.point[j].f[3] = 1;
            {
                unsigned int color = color1;
                if (j < 2) color = color0;
                beam.color[j] = color;
            }
        }
    }
    for (i = 0; i < count; i++) {
        matrix_mul_vec3(&basis[3], &points[i], object + 0xC0);
        FastVecAdd(&basis[3], &basis[3], object + 0x10);
        basis[3].f[3] = 1;
        draw_world_quad(&beam, basis, 0);
    }
}
