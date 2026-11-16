#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char gap0[0x10];
    float plane[4];
    unsigned char gap20[0x10];
    float (*points)[4];
    unsigned char gap34[0x25];
    unsigned char indices[3];
    unsigned char count;
} OozlaAppendDescriptor164;
typedef struct {
    unsigned char gap0[0x68];
    OozlaAppendDescriptor164 *descriptor;
    unsigned char gap6c[0x54];
    float transform[3][4];
} OozlaAppendObject164;
extern void FastVecSub(float *, const float *, const float *);
extern void matrix_mul_vec3(float *, const float *, const float *);
extern void vec_scale_by_direction(OozlaAppendObject164 *, float *, const float *);
extern void lerp_vector(float *out, float *a, float *b, float t);
extern void vec_scale_to_length(float *out, float *in, float s);
extern void FastVecCross(float *out, float *a, float *b);
extern void cam_compute_view_direction(float *a, float *b, int c);
extern void quaternion_to_rotation_basis(float *a, float *b);
extern void multiply_matrix3x3(float *a, float *b, float *c);
extern void coll_clamp_movement_vector_pal(char *o, float *p, float *v);

void moby_slide_along_hit_points_pal(char *o)
{
    float a[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float h[4] __attribute__((aligned(16)));
    float i[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));
    float f[4] __attribute__((aligned(16)));
    float g[3][4] __attribute__((aligned(16)));
    unsigned char *m = *(unsigned char **)(o + 0x68);
    float *w;

    if (m[0x5C] >= 2) {
        lerp_vector(a, (float *)(*(char **)(m + 0x30) + m[0x59] * 16), (float *)(*(char **)(m + 0x30) + m[0x5A] * 16), 0.5f);
        FastVecSub(b, (float *)(*(char **)(m + 0x30) + m[0x59] * 16), (float *)(*(char **)(m + 0x30) + m[0x5A] * 16));
        matrix_mul_vec3(b, b, (float *)(o + 0xC0));
        w = (float *)(o + 0xC0);
    } else {
        qcopy(a, *(char **)(m + 0x30) + m[0x59] * 16);
        w = (float *)(o + 0xC0);
    }
    matrix_mul_vec3(c, a, w);
    cam_compute_view_direction((float *)(o + 0x10), d, 1);
    FastVecSub(e, a, (float *)(m + 0x20));
    matrix_mul_vec3(e, e, w);
    vec_scale_to_length(e, e, 1.0f);
    FastVecCross(f, e, d);
    vec_scale_to_length(f, f, *(float *)(m + 0x4C));
    coll_clamp_movement_vector_pal(o, (float *)(m + 0x10), f);
    if (m[0x5C] >= 2)
        vec_scale_by_direction(o, (float *)(m + 0x10), b);
    quaternion_to_rotation_basis((float *)(m + 0x10), g[0]);
    multiply_matrix3x3(w, g[0], w);
    matrix_mul_vec3(h, a, w);
    FastVecSub(i, h, c);
    FastVecSub((float *)(o + 0x10), (float *)(o + 0x10), i);
}

