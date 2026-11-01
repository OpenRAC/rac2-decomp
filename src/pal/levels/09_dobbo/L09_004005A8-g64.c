#include "include_asm.h"

#include "common.h"
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
extern char *func_PAL_L08_0034C4A8(void *, void *, int, void *);

void func_PAL_L09_00400D98(int tex0, int tex1, void *points, int inner, int outer, int alpha, int slot, int spark)
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

    packets[0].texture = func_0027C878(tex0);
    packets[0].blend = 0x8000000048ULL;
    packets[0].mode = 0xFF9000000260ULL;
    packets[0].flags = 0;
    packets[0].color[0] = packets[0].color[1] = packets[0].color[2] = packets[0].color[3] = (c << 24) | 0x7F3F40;
    packets[1].texture = func_0027C878(tex1);
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

        func_00282CF0(&delta, &D_L09_00256310[slot], &origin);
        func_00282F20(basis, &delta, 1);
        func_00282DD8(&axis[1], &axis[0], D_0018A0E0);
        func_00282F20(&axis[1], &axis[1], -1.0f);
        func_00282DD8(&axis[2], &axis[1], &axis[0]);
        qcopy(&packets[0].vertex[0], &width);
        func_00282D30(&packets[0].vertex[1], &packets[0].vertex[0], -1.0f);
        qcopy(&packets[1].vertex[0], &glowWidth);
        func_00282D30(&packets[1].vertex[1], &packets[1].vertex[0], -1.0f);
        func_002830C0(&a, &path[1], axis);
        func_002830C0(&b, path, axis);
        func_00282CF0(&mat[0], &a, &b);
        func_00282F20(&mat[0], &mat[0], 1.0f);
        func_00282CF0(&mat[1], D_L09_001B9A00, &a);
        func_00282DD8(&mat[2], &mat[1], &mat[0]);
        func_00282F20(&mat[2], &mat[2], 1.0f);
        func_00282DD8(&mat[1], &mat[0], &mat[2]);
        qcopy(&mat[3], &b);
        func_002830C0(&packets[0].vertex[0], &packets[0].vertex[0], mat);
        func_002830C0(&packets[0].vertex[1], &packets[0].vertex[1], mat);
        func_002830C0(&packets[1].vertex[0], &packets[1].vertex[0], mat);
        func_002830C0(&packets[1].vertex[1], &packets[1].vertex[1], mat);
        for (i = 1; i < 6;) {
            qcopy(&packets[0].vertex[2], &width);
            func_00282D30(&packets[0].vertex[3], &packets[0].vertex[2], -1.0f);
            qcopy(&packets[1].vertex[2], &glowWidth);
            func_00282D30(&packets[1].vertex[3], &packets[1].vertex[2], -1.0f);
            func_002830C0(&a, &path[i], axis);
            func_002830C0(&b, &path[i - 1], axis);
            func_00282CF0(&mat[0], &a, &b);
            func_00282F20(&mat[0], &mat[0], 1.0f);
            func_00282CF0(&mat[1], D_L09_001B9A00, &a);
            func_00282DD8(&mat[2], &mat[1], &mat[0]);
            func_00282F20(&mat[2], &mat[2], 1.0f);
            func_00282DD8(&mat[1], &mat[0], &mat[2]);
            qcopy(&mat[3], &a);
            func_002830C0(&packets[0].vertex[2], &packets[0].vertex[2], mat);
            func_002830C0(&packets[0].vertex[3], &packets[0].vertex[3], mat);
            func_002830C0(&packets[1].vertex[2], &packets[1].vertex[2], mat);
            func_002830C0(&packets[1].vertex[3], &packets[1].vertex[3], mat);
            if (i == 1) {
                /* The glow fades out at both ends of the strip. */
                saved = packets[1].color[0];
                packets[1].color[0] = packets[1].color[1] = 0xFFAF10;
                func_00280B90(&packets[0], 0, 0);
                func_00280B90(&packets[1], 0, 0);
                packets[1].color[0] = packets[1].color[1] = packets[1].color[2] = packets[1].color[3] = saved;
            } else if (i == 5) {
                saved = packets[1].color[2];
                packets[1].color[2] = packets[1].color[3] = 0xFFAF10;
                func_00280B90(&packets[0], 0, 0);
                func_00280B90(&packets[1], 0, 0);
                packets[1].color[0] = packets[1].color[1] = packets[1].color[2] = packets[1].color[3] = saved;
            } else {
                func_00280B90(&packets[0], 0, 0);
                func_00280B90(&packets[1], 0, 0);
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
                func_00283098(vel, vel, &D_L09_00255F10[slot][0]);
                func_00282FB8(vel, vel, 0.040000003f);
                particle = func_PAL_L08_0034C4A8(&packets[0].vertex[func_001163B0() & 3], vel, alpha * 64 / 100,
                                             D_L09_00255E90[slot][0]);
                if (particle) {
                    particle[2] = *D_L09_001FF580.bank;
                    output = (struct SparkOutput *)(particle + 0x20);
                    output->inverse = 1.0f / func_00283CE0(*(short *)(particle + 0xA));
                    output->color = 0x7F3F20;
                    *(float *)(particle + 0xC) = 150000.0f;
                    particle = func_PAL_L08_0034C4A8(&packets[0].vertex[func_001163B0() & 3], vel, alpha * 127 / 100,
                                                 D_L09_00255E90[slot][0]);
                    if (particle) {
                        particle[2] = *D_L09_001FF580.bank;
                        output = (struct SparkOutput *)(particle + 0x20);
                        output->inverse = 1.0f / func_00283CE0(*(short *)(particle + 0xA));
                        output->color = 0xFFFFFF;
                        *(float *)(particle + 0xC) = 30000.0f;
                    }
                }
            }
            fraction = func_00283CE0(i);
            i++;
            fraction /= func_00283CE0(6);
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
