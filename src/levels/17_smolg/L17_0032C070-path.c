#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern char *D_L17_001FE880[];
/* One storage identity supplies the absolute loop entry and GP backedge load. */
extern int D_L17_001B2748[] __attribute__((sda));
extern void func_002C96F8(float, float, void *, int *, float *, void *);
extern float func_00283CE0(int);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00282E80(void *, void *);
extern float func_00282DF0(void *);
extern float func_002AAA00(void *, float, void *, int, float, float, float);
/* Both declarations preserve the EE interface: a0/a1/a2 and f12/f13/f14/f15,
   with no stack arguments. The pitch call interleaves the two register banks. */
extern float func_002AAA00_pitch(void *, float, void *, float, float, float, int)
    __asm__("func_002AAA00");
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F70(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_002A05A8(void *);
extern void func_002A0F48(void *);
extern float func_00283198(float);
extern float func_00283180(float);

/* A path of D_L17_001FE880. */
typedef struct {
    int count;                  /* 0x00 */
    u8 pad04[0x10 - 0x04];
    Vec points[2];              /* 0x10 */
} ChainPath;

typedef struct ChainMoby ChainMoby;

/* The instance data of a chain link; the first link leads. */
typedef struct {
    int path;                   /* 0x00: index in D_L17_001FE880, -1 for none */
    u8 pad04[0x14 - 0x04];
    float pitchSpeed;           /* 0x14 */
    float headingSpeed;         /* 0x18 */
    ChainMoby *next;            /* 0x1C: the following link */
    float gap;                  /* 0x20: space between two links */
    float halfLength;           /* 0x24: from a link's centre to its hitches */
    u8 pad28[0x34 - 0x28];
    int f34;                    /* 0x34 */
} ChainVars;

struct ChainMoby {
    u8 pad0[0x10];
    Vec position;               /* 0x10 */
    u8 pad20[0x34 - 0x20];
    s16 flags;                  /* 0x34 */
    u8 pad36[0x68 - 0x36];
    ChainVars *vars;            /* 0x68 */
    u8 pad6C[0x78 - 0x6C];
    int color;                  /* 0x78 */
    u8 pad7C[0xB2 - 0x7C];
    s16 uid;                    /* 0xB2 */
    u8 padB4[0xC0 - 0xB4];
    float matrix[3][4];         /* 0xC0 */
    Vec rotation;               /* 0xF0 */
};

/* Puts the leading link at the start of its path, facing along the first
   segment, and lines the following links up behind it. */
int func_L17_003BCC30(ChainMoby *moby)
{
    Vec rear;
    Vec start;
    Vec hitch;
    Vec back;
    float angle;
    int flash;
    ChainVars *vars = moby->vars;
    ChainMoby *link = vars->next;
    ChainPath *path;
    ChainVars *linkVars;

    if (vars->path == -1)
        return 0;
    path = (ChainPath *)D_L17_001FE880[vars->path];
    start.q = path->points[0].q;
    angle = func_00283248(path->points[1].f[0] - path->points[0].f[0],
                          path->points[1].f[1] - path->points[0].f[1]);
    moby->position.q = start.q;
    qzero_nc(&moby->rotation);
    moby->rotation.f[2] = FastAddRotations(angle, 1.5707965f);
    vars->headingSpeed = 0;
    vars->pitchSpeed = 0;

    /* The leader's rear hitch. */
    rear.f[0] = func_00283180(angle) * -vars->halfLength;
    rear.f[1] = func_00283198(angle) * -vars->halfLength;
    rear.f[2] = 0;
    FastVecAdd(&rear, &rear, &moby->position);

    while (link) {
        flash = (D_L17_001B2748[0] + link->uid) % 60 < 15;
        link->color = flash ? 0x80FFFFFF : 0x80404040;
        linkVars = link->vars;

        /* Leave the gap behind the rear hitch, then centre the link behind that. */
        hitch.f[0] = func_00283180(angle) * -vars->gap;
        hitch.f[1] = func_00283198(angle) * -vars->gap;
        hitch.f[2] = 0;
        FastVecAdd(&hitch, &hitch, &rear);
        back.f[0] = func_00283180(angle) * -linkVars->halfLength;
        back.f[1] = func_00283198(angle) * -linkVars->halfLength;
        back.f[2] = 0;
        FastVecAdd(&link->position, &back, &hitch);
        link->position.f[2] = moby->position.f[2];
        link->rotation.f[2] = FastAddRotations(func_00283248(hitch.f[0] - link->position.f[0],
                                                          hitch.f[1] - link->position.f[1]),
                                            1.5707965f);
        link->rotation.f[1] = 0;
        func_002A05A8(link);
        func_002A0F48(link);
        linkVars->f34 = 1;
        link->flags |= 4;

        /* This link's rear hitch, through its new orientation (at the leader's half length). */
        qzero_nc(&rear);
        rear.f[1] = vars->halfLength;
        matrix_mul_vec3(&rear, &rear, link->matrix);
        FastVecAdd(&rear, &rear, &link->position);
        link = linkVars->next;
    }
    return 1;
}

/* Samples the leader's path, then positions and turns each linked follower
   relative to the preceding object's transformed attachment point. */
int func_L17_003BCEC0(char *obj)
{
    Vec anchor, target, other, desired, delta;
    float *heading, *pitch;
    int index;
    int flash;
    float fraction, length, phase, angle;
    float low, middle, high;
    char *ctx = *(char **)(obj + 0x68);
    char *next = *(char **)(ctx + 0x1C);
    char *path, *nctx;

    if (*(int *)ctx == -1)
        return 0;
    path = D_L17_001FE880[*(int *)ctx];
    length = IntToFloat(*(int *)path) * *(float *)(path + 0x1C);
    *(float *)(ctx + 0xC) += *(float *)(ctx + 0x10) * 0.016666668f;
    if (length < *(float *)(ctx + 0xC))
        *(float *)(ctx + 0xC) = length - *(float *)(ctx + 0xC);
    func_002C96F8(*(float *)(ctx + 0xC), *(float *)(path + 0x1C),
                 path, &index, &fraction, obj + 0x10);
    phase = *(float *)(ctx + 0xC) + *(float *)(ctx + 0x28);
    if (length < phase)
        phase -= length;
    func_002C96F8(phase, *(float *)(path + 0x1C), path, &index, &fraction, &target);
    heading = (float *)(obj + 0xF8);
    pitch = (float *)(obj + 0xF4);
    low = 0.00043633237f;
    middle = 0.00087266474f;
    high = 0.052359887f;
    angle = FastAddRotations(func_00283248(target.f[0] - *(float *)(obj + 0x10),
                                      target.f[1] - *(float *)(obj + 0x14)), 1.5707965f);
    func_002AAA00(heading, angle, ctx + 0x18, 0, low, middle, high);
    angle = func_00283248(vec_distance_xy(obj + 0x10, &target),
                         target.f[2] - *(float *)(obj + 0x18));
    func_002AAA00(pitch, angle, ctx + 0x14, 0, low, middle, high);
    qzero_nc(&anchor);
    anchor.f[1] = *(float *)(ctx + 0x24);
    matrix_mul_vec3(&anchor, &anchor, obj + 0xC0);
    FastVecAdd(&anchor, &anchor, obj + 0x10);

    while (next) {
        float *nextHeading, *nextPitch;
        low = 0.00087266474f;
        middle = 0.0017453295f;
        high = 0.10471977f;
        flash = (D_L17_001B2748[0] + *(short *)(next + 0xB2)) % 60 < 15;
        *(int *)(next + 0x78) = flash ? 0x80FFFFFF : 0x80404040;
        nctx = *(char **)(next + 0x68);
        qzero(&other);
        other.f[1] = -*(float *)(ctx + 0x24);
        nextHeading = (float *)(next + 0xF8);
        nextPitch = (float *)(next + 0xF4);
        matrix_mul_vec3(&other, &other, next + 0xC0);
        FastVecAdd(&other, &other, next + 0x10);
        FastVecSub(&desired, &other, &anchor);
        func_00282F70(&desired, &desired, *(float *)(ctx + 0x20));
        FastVecAdd(&desired, &desired, &anchor);
        desired.f[2] = anchor.f[2];
        FastVecSub(&delta, &desired, next + 0x10);
        vec_scale_to_length(&delta, &delta, FastVecLength(&delta) - *(float *)(ctx + 0x24));
        FastVecAdd(next + 0x10, &delta, next + 0x10);
        angle = FastAddRotations(func_00283248(desired.f[0] - *(float *)(next + 0x10),
                                          desired.f[1] - *(float *)(next + 0x14)), 1.5707965f);
        func_002AAA00(nextHeading, angle, nctx + 0x18, 0, low, middle, high);
        angle = func_00283248(vec_distance_xy(next + 0x10, &desired),
                             desired.f[2] - *(float *)(next + 0x18));
        func_002AAA00_pitch(nextPitch, angle, nctx + 0x14, low, middle, high, 0);
        func_002A05A8(next);
        func_002A0F48(next);
        *(int *)(nctx + 0x34) = 1;
        *(short *)(next + 0x34) |= 4;
        qzero_nc(&anchor);
        anchor.f[1] = *(float *)(ctx + 0x24);
        matrix_mul_vec3(&anchor, &anchor, next + 0xC0);
        FastVecAdd(&anchor, &anchor, next + 0x10);
        next = *(char **)(nctx + 0x1C);
    }
    return 1;
}
