#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern char *D_L17_001FE880[];
extern int D_L17_001B2748[] __attribute__((sda));
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(void *);
extern float func_00283198(float);
extern float func_00283180(float);
typedef struct {
    int count;                   
    u8 pad04[0x10 - 0x04];
    Vec points[2];               
} ChainPath;
typedef struct ChainMoby ChainMoby;
typedef struct {
    int path;                    
    u8 pad04[0x14 - 0x04];
    float pitchSpeed;            
    float headingSpeed;          
    ChainMoby *next;             
    float gap;                   
    float halfLength;            
    u8 pad28[0x34 - 0x28];
    int f34;                     
} ChainVars;
struct ChainMoby {
    u8 pad0[0x10];
    Vec position;                
    u8 pad20[0x34 - 0x20];
    s16 flags;                   
    u8 pad36[0x68 - 0x36];
    ChainVars *vars;             
    u8 pad6C[0x78 - 0x6C];
    int color;                   
    u8 pad7C[0xB2 - 0x7C];
    s16 uid;                     
    u8 padB4[0xC0 - 0xB4];
    float matrix[3][4];          
    Vec rotation;                
};

/* Puts the leading link at the start of its path, facing along the first
   segment, and lines the following links up behind it. */
int func_PAL_L17_003C07C0(ChainMoby *moby)
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
    moby->rotation.f[2] = func_00283B98(angle, 1.5707965f);
    vars->headingSpeed = 0;
    vars->pitchSpeed = 0;

    /* The leader's rear hitch. */
    rear.f[0] = func_00283180(angle) * -vars->halfLength;
    rear.f[1] = func_00283198(angle) * -vars->halfLength;
    rear.f[2] = 0;
    func_00282CC0(&rear, &rear, &moby->position);

    while (link) {
        flash = (D_L17_001B2748[0] + link->uid) % 50 < 12;
        link->color = flash ? 0x80FFFFFF : 0x80404040;
        linkVars = link->vars;

        /* Leave the gap behind the rear hitch, then centre the link behind that. */
        hitch.f[0] = func_00283180(angle) * -vars->gap;
        hitch.f[1] = func_00283198(angle) * -vars->gap;
        hitch.f[2] = 0;
        func_00282CC0(&hitch, &hitch, &rear);
        back.f[0] = func_00283180(angle) * -linkVars->halfLength;
        back.f[1] = func_00283198(angle) * -linkVars->halfLength;
        back.f[2] = 0;
        func_00282CC0(&link->position, &back, &hitch);
        link->position.f[2] = moby->position.f[2];
        link->rotation.f[2] = func_00283B98(func_00283248(hitch.f[0] - link->position.f[0],
                                                          hitch.f[1] - link->position.f[1]),
                                            1.5707965f);
        link->rotation.f[1] = 0;
        func_PAL_002A0F68(link);
        func_002A0F48(link);
        linkVars->f34 = 1;
        link->flags |= 4;

        /* This link's rear hitch, through its new orientation (at the leader's half length). */
        qzero_nc(&rear);
        rear.f[1] = vars->halfLength;
        func_00283098(&rear, &rear, link->matrix);
        func_00282CC0(&rear, &rear, &link->position);
        link = linkVars->next;
    }
    return 1;
}

extern void func_002C96F8(float, float, void *, int *, float *, void *);
extern float func_00283CE0(int);
extern float func_00282E80(void *, void *);
extern float func_00282DF0(void *);
extern float func_002AAA00(void *, float, void *, int, float, float, float);
extern float func_002AAA00_pitch(void *, float, void *, float, float, float, int)
    __asm__("func_002AAA00");
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F70(void *, void *, float);
extern void func_00282F20(void *, void *, float);

/* Samples the leader's path, then positions and turns each linked follower
   relative to the preceding object's transformed attachment point. */
int func_PAL_L17_003C0A50(char *obj)
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
    length = func_00283CE0(*(int *)path) * *(float *)(path + 0x1C);
    *(float *)(ctx + 0xC) += *(float *)(ctx + 0x10) * 0.020000001f;
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
    low = 0.00062831864f;
    middle = 0.0012566373f;
    high = 0.062831864f;
    angle = func_00283B98(func_00283248(target.f[0] - *(float *)(obj + 0x10),
                                      target.f[1] - *(float *)(obj + 0x14)), 1.5707965f);
    func_002AAA00(heading, angle, ctx + 0x18, 0, low, middle, high);
    angle = func_00283248(func_00282E80(obj + 0x10, &target),
                         target.f[2] - *(float *)(obj + 0x18));
    func_002AAA00(pitch, angle, ctx + 0x14, 0, low, middle, high);
    qzero_nc(&anchor);
    anchor.f[1] = *(float *)(ctx + 0x24);
    func_00283098(&anchor, &anchor, obj + 0xC0);
    func_00282CC0(&anchor, &anchor, obj + 0x10);

    while (next) {
        float *nextHeading, *nextPitch;
        low = 0.0012566373f;
        middle = 0.0025132746f;
        high = 0.12566373f;
        flash = (D_L17_001B2748[0] + *(short *)(next + 0xB2)) % 50 < 12;
        *(int *)(next + 0x78) = flash ? 0x80FFFFFF : 0x80404040;
        nctx = *(char **)(next + 0x68);
        qzero(&other);
        other.f[1] = -*(float *)(ctx + 0x24);
        nextHeading = (float *)(next + 0xF8);
        nextPitch = (float *)(next + 0xF4);
        func_00283098(&other, &other, next + 0xC0);
        func_00282CC0(&other, &other, next + 0x10);
        func_00282CF0(&desired, &other, &anchor);
        func_00282F70(&desired, &desired, *(float *)(ctx + 0x20));
        func_00282CC0(&desired, &desired, &anchor);
        desired.f[2] = anchor.f[2];
        func_00282CF0(&delta, &desired, next + 0x10);
        func_00282F20(&delta, &delta, func_00282DF0(&delta) - *(float *)(ctx + 0x24));
        func_00282CC0(next + 0x10, &delta, next + 0x10);
        angle = func_00283B98(func_00283248(desired.f[0] - *(float *)(next + 0x10),
                                          desired.f[1] - *(float *)(next + 0x14)), 1.5707965f);
        func_002AAA00(nextHeading, angle, nctx + 0x18, 0, low, middle, high);
        angle = func_00283248(func_00282E80(next + 0x10, &desired),
                             desired.f[2] - *(float *)(next + 0x18));
        func_002AAA00_pitch(nextPitch, angle, nctx + 0x14, low, middle, high, 0);
        func_PAL_002A0F68(next);
        func_002A0F48(next);
        *(int *)(nctx + 0x34) = 1;
        *(short *)(next + 0x34) |= 4;
        qzero_nc(&anchor);
        anchor.f[1] = *(float *)(ctx + 0x24);
        func_00283098(&anchor, &anchor, next + 0xC0);
        func_00282CC0(&anchor, &anchor, next + 0x10);
        next = *(char **)(nctx + 0x1C);
    }
    return 1;
}
