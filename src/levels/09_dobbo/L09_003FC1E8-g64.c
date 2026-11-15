#include "common.h"

/* Draws one beam link: two textured strips (core and glow) along the six path points, and on
 * segment `spark` possibly a pair of spark particles. The width vectors are transformed into a
 * basis built from the link's two end positions. */

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } V;
typedef struct {
    V vertex[4];
    unsigned color[4];
    float uv[4][2];
    unsigned long long flags, texture, mode, blend;
} Packet;
typedef struct { char gap[0xD4]; unsigned char *bank; } SparkBank;
struct SparkOutput { char pad00[16]; float inverse; int pad14; unsigned color; };

extern V D_L09_001B9A00[], D_0018A0E0[];
extern V D_L09_00256310[], D_L09_00255F10[][4];
extern float D_L09_001B37E0[16] MACRO_ADDR;
extern float D_L09_001B1194 __attribute__((sda)), D_L09_001B1198 __attribute__((sda));
extern float D_L09_001B119C __attribute__((sda));
extern SparkBank D_L09_001FF580;
extern void *D_L09_00255E90[16][2];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern unsigned long long func_0027C878(int);
extern float func_002A7878(float, float);
extern int func_L02_002F1658(void);
extern void func_00280B90(void *, int, int);
extern void func_00283098(void *, void *, void *), func_00282FB8(void *, void *, float);
extern float func_00283198(float), func_00283CE0(int), func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern int func_001163B0(void);
extern char *func_L08_0034A078(void *, void *, int, void *);

void func_L09_003FC1E8(int tex0, int tex1, void *points, int inner, int outer, int alpha, int slot, int spark)
{
    Packet packets[2];
    V width, glowWidth, mat[4], axis[3], origin, delta, a, b, velocity;
    int i, saved;
    V *path = points;
    unsigned c = inner * alpha / 100;
    unsigned g = outer * alpha / 100;
    unsigned long long flags, blend, mode;
    float size, initialSize;
    float fraction, r0, r1, r2;
    char *particle;
    V *vel;
    struct SparkOutput *output;

    packets[0].texture = GetEffectTextureDescriptor(tex0);
    packets[0].blend = 0x8000000048ULL;
    packets[0].mode = 0xFF9000000260ULL;
    packets[0].flags = 0;
    packets[0].color[0] = packets[0].color[1] = packets[0].color[2] = packets[0].color[3] = (c << 24) | 0x7F3F40;
    packets[1].texture = GetEffectTextureDescriptor(tex1);
    flags = packets[0].flags;
    blend = packets[0].blend;
    mode = packets[0].mode;
    initialSize = D_L09_001B1198;
    width.q = 0;
    packets[1].blend = blend;
    g = (g << 24) | 0xFFAF10;
    packets[1].color[0] = packets[1].color[1] = packets[1].color[2] = packets[1].color[3] = g;
    packets[1].flags = flags;
    glowWidth.q = 0;
    packets[1].mode = mode;
    packets[0].uv[1][0] = packets[0].uv[0][0] = D_L09_001B37E0[slot];
    packets[0].uv[3][0] = packets[0].uv[2][0] = D_L09_001B37E0[slot] + 1.0f;
    packets[1].uv[0][0] = 1;
    packets[1].uv[0][1] = 0;
    packets[1].uv[1][0] = 1;
    packets[1].uv[1][1] = 1;
    packets[1].uv[2][0] = 0;
    packets[1].uv[2][1] = 0;
    packets[1].uv[3][0] = 0;
    packets[1].uv[3][1] = 1;
    packets[0].uv[0][1] = 0;
    packets[0].uv[1][1] = 1;
    packets[0].uv[2][1] = 0;
    packets[0].uv[3][1] = 1;
    width.f[3] = 1;
    width.f[2] = initialSize;
    glowWidth.f[3] = 1;
    glowWidth.f[2] = initialSize * D_L09_001B119C;
    qcopy(&origin, &D_L09_00255F10[slot][3]);
    {
        V *basis = axis;

        FastVecSub(&delta, &D_L09_00256310[slot], &origin);
        vec_scale_to_length(basis, &delta, 1);
        FastVecCross(&axis[1], &axis[0], D_0018A0E0);
        vec_scale_to_length(&axis[1], &axis[1], -1.0f);
        FastVecCross(&axis[2], &axis[1], &axis[0]);
        qcopy(&packets[0].vertex[0], &width);
        FastVecScale(&packets[0].vertex[1], &packets[0].vertex[0], -1.0f);
        qcopy(&packets[1].vertex[0], &glowWidth);
        FastVecScale(&packets[1].vertex[1], &packets[1].vertex[0], -1.0f);
        transform_vector(&a, &path[1], axis);
        transform_vector(&b, path, axis);
        FastVecSub(&mat[0], &a, &b);
        vec_scale_to_length(&mat[0], &mat[0], 1.0f);
        FastVecSub(&mat[1], D_L09_001B9A00, &a);
        FastVecCross(&mat[2], &mat[1], &mat[0]);
        vec_scale_to_length(&mat[2], &mat[2], 1.0f);
        FastVecCross(&mat[1], &mat[0], &mat[2]);
        qcopy(&mat[3], &b);
        transform_vector(&packets[0].vertex[0], &packets[0].vertex[0], mat);
        transform_vector(&packets[0].vertex[1], &packets[0].vertex[1], mat);
        transform_vector(&packets[1].vertex[0], &packets[1].vertex[0], mat);
        transform_vector(&packets[1].vertex[1], &packets[1].vertex[1], mat);
        for (i = 1; i < 6;) {
            qcopy(&packets[0].vertex[2], &width);
            FastVecScale(&packets[0].vertex[3], &packets[0].vertex[2], -1.0f);
            qcopy(&packets[1].vertex[2], &glowWidth);
            FastVecScale(&packets[1].vertex[3], &packets[1].vertex[2], -1.0f);
            transform_vector(&a, &path[i], axis);
            transform_vector(&b, &path[i - 1], axis);
            FastVecSub(&mat[0], &a, &b);
            vec_scale_to_length(&mat[0], &mat[0], 1.0f);
            FastVecSub(&mat[1], D_L09_001B9A00, &a);
            FastVecCross(&mat[2], &mat[1], &mat[0]);
            vec_scale_to_length(&mat[2], &mat[2], 1.0f);
            FastVecCross(&mat[1], &mat[0], &mat[2]);
            qcopy(&mat[3], &a);
            transform_vector(&packets[0].vertex[2], &packets[0].vertex[2], mat);
            transform_vector(&packets[0].vertex[3], &packets[0].vertex[3], mat);
            transform_vector(&packets[1].vertex[2], &packets[1].vertex[2], mat);
            transform_vector(&packets[1].vertex[3], &packets[1].vertex[3], mat);
            if (i == 1) {
                /* The glow fades out at both ends of the strip. */
                saved = packets[1].color[0];
                packets[1].color[0] = packets[1].color[1] = 0xFFAF10;
                draw_world_quad(&packets[0], 0, 0);
                draw_world_quad(&packets[1], 0, 0);
                packets[1].color[0] = packets[1].color[1] = packets[1].color[2] = packets[1].color[3] = saved;
            } else if (i == 5) {
                saved = packets[1].color[2];
                packets[1].color[2] = packets[1].color[3] = 0xFFAF10;
                draw_world_quad(&packets[0], 0, 0);
                draw_world_quad(&packets[1], 0, 0);
                packets[1].color[0] = packets[1].color[1] = packets[1].color[2] = packets[1].color[3] = saved;
            } else {
                draw_world_quad(&packets[0], 0, 0);
                draw_world_quad(&packets[1], 0, 0);
            }
            qcopy(&packets[0].vertex[0], &packets[0].vertex[2]);
            qcopy(&packets[0].vertex[1], &packets[0].vertex[3]);
            qcopy(&packets[1].vertex[0], &packets[1].vertex[2]);
            qcopy(&packets[1].vertex[1], &packets[1].vertex[3]);
            if (i == spark && func_L02_002F1658()) {
                r0 = func_002A7878(.01f, .08f);
                vel = &velocity;
                r1 = func_002A7940();
                r2 = func_002A7940();
                func_002AF000(vel, r0, r1, r2 * .25f);
                matrix_mul_vec3(vel, vel, &D_L09_00255F10[slot][0]);
                func_00282FB8(vel, vel, 1.0f / 30.0f);
                particle = func_L08_0034A078(&packets[0].vertex[func_001163B0() & 3], vel, alpha * 64 / 100,
                                             D_L09_00255E90[slot][0]);
                if (particle) {
                    particle[2] = *D_L09_001FF580.bank;
                    output = (struct SparkOutput *)(particle + 0x20);
                    output->inverse = 1.0f / IntToFloat(*(short *)(particle + 0xA));
                    output->color = 0x7F3F20;
                    *(float *)(particle + 0xC) = 150000.0f;
                    particle = func_L08_0034A078(&packets[0].vertex[func_001163B0() & 3], vel, alpha * 127 / 100,
                                                 D_L09_00255E90[slot][0]);
                    if (particle) {
                        particle[2] = *D_L09_001FF580.bank;
                        output = (struct SparkOutput *)(particle + 0x20);
                        output->inverse = 1.0f / IntToFloat(*(short *)(particle + 0xA));
                        output->color = 0xFFFFFF;
                        *(float *)(particle + 0xC) = 30000.0f;
                    }
                }
            }
            fraction = IntToFloat(i);
            i++;
            fraction /= IntToFloat(6);
            size = initialSize + (D_L09_001B1194 - initialSize) * func_00283198(fraction * 3.1415927f);
            packets[0].uv[1][0] = packets[0].uv[0][0] = D_L09_001B37E0[slot];
            packets[0].uv[3][0] = packets[0].uv[2][0] = D_L09_001B37E0[slot] + 1;
            packets[0].uv[0][1] = 0;
            packets[0].uv[1][1] = 1;
            packets[0].uv[2][1] = 0;
            packets[0].uv[3][1] = 1;
            width.f[2] = size;
            glowWidth.f[2] = size * D_L09_001B119C;
        }
    }
}
