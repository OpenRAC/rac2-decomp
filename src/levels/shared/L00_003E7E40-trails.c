#include "common.h"

typedef struct { float x, y, z, w; } MmiPoint;
typedef float TrailVector[4] __attribute__((aligned(16)));
typedef char PointExtent[sizeof(MmiPoint) == 16 ? 1 : -1];
extern s32 func_002AB220(u8 *);
extern int func_002A99A0(float, char *, int, MmiPoint *, int);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern u32 func_00283D38(u32, u32, float);
extern int func_002A7820(int, int);
extern void *func_002BAA28(void *, float *, float *, int, int, int, int, int, int);
extern float D_L00_001B0660_gp SDATA(D_L00_001B0660);
extern int D_L00_001B0664_gp SDATA(D_L00_001B0664);
extern float D_L00_001B0668_gp SDATA(D_L00_001B0668);
extern float D_L00_001B0670_gp SDATA(D_L00_001B0670);
extern float D_L00_001B0680_gp SDATA(D_L00_001B0680);
extern int D_L00_001B0690_gp SDATA(D_L00_001B0690);
extern float D_L00_001B066C __attribute__((sda));
extern float D_L00_001B0674 __attribute__((sda));
extern float D_L00_001B0678 NOT_SDA;
extern float D_L00_001B067C __attribute__((sda));
extern float D_L00_001B0684 __attribute__((sda));
extern float D_L00_001B0688 __attribute__((sda));
extern float D_L00_001B068C __attribute__((sda));
extern int D_L00_001B0694 __attribute__((sda));

/* The sampler clamps n to its limit and writes only output[0..n-1]. The
 * constructor consumes all four floats from each endpoint, including size w.
 * Sampled position w is not guaranteed initialized: the constructor transfers
 * it, but the family-2 update adds XYZ only and the normal renderer replaces
 * the output w with zero before consumption. No extra initialization is added.
 * Retail performs the initial zero-z and randomized-w stores before later
 * overwrites; its RNG calls and actual writes are retained without qualifiers.
 * The second radial lower bound is absolute, including at the RNG call site:
 * NOT_SDA plus the standard no-split-addresses profile retains that access. */
void func_L00_003E7E40(unsigned char *object, const unsigned char *info, float opacity)
{
    MmiPoint points[32] __attribute__((aligned(16)));
    TrailVector from, to;
    const unsigned char *model;
    float angle, speed, size;
    u32 original;
    int count, i, color, end_color, duration;
    model = (const unsigned char *)func_002AB220(object);
    if (model == 0)
        return;
    count = func_002A99A0(D_L00_001B0660_gp, (char *)object, 32, points, model[0x19]);
    for (i = 0; i < count; i++) {
        angle = func_002A7940();
        speed = func_002A7878(D_L00_001B0670_gp, D_L00_001B0674) * 0.01666666753590107f;
        from[0] = func_00283180(angle) * speed;
        from[1] = func_00283198(angle) * speed;
        from[2] = 0.0f;
        from[2] = func_002A7878(D_L00_001B0680_gp, D_L00_001B0684) * 0.01666666753590107f;
        from[3] = func_002A7878(0.1f, 0.2f);
        angle = func_00283B98(angle, func_002A7878(120.0f, 240.0f) * 0.01745329424738884f);
        speed = func_002A7878(D_L00_001B0678, D_L00_001B067C) * 0.01666666753590107f;
        to[0] = func_00283180(angle) * speed;
        to[1] = func_00283198(angle) * speed;
        to[2] = 0.0f;
        to[2] = func_002A7878(D_L00_001B0688, D_L00_001B068C) * 0.01666666753590107f;
        to[3] = func_002A7878(0.1f, 0.2f);
        size = func_002A7878(D_L00_001B0668_gp, D_L00_001B066C);
        to[3] = from[3] = size;
        original = *(const u32 *)info;
        color = (int)func_00283D38((original & 0xFFFFFF) | 0x10000000, original, opacity);
        end_color = *(const int *)(info + 8);
        duration = func_002A7820(D_L00_001B0690_gp, D_L00_001B0694);
        func_002BAA28(&points[i], from, to, color, end_color, 5, duration, 10, D_L00_001B0664_gp);
    }
}
