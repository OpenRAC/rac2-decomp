#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    float x, y, z, w;
} Vec4;

/* The resident tuning shared with func_L02_00412808 (see L02_0040A4A8.c): the spark spread and
   fall speed, the two spark sizes, the two spark colours and the two byte ranges of the spark
   kind; then the beam's two widths, its two layer bytes and its two colours. */
typedef struct { float f[4]; } SparkRange;
typedef struct { float f[2]; } SparkSizes;
typedef struct { int i[2]; } SparkColours;
typedef struct { u8 b[4]; } SparkKinds;
typedef struct { float f[2]; } BeamWidths;
typedef struct { u8 b[2]; } BeamLayers;
typedef struct { u32 rgba[2]; } BeamColours;

extern const SparkRange D_L02_001B1C10;
extern const SparkSizes D_L02_001B1C20;
extern const SparkColours D_L02_001B1C28;
extern const SparkKinds D_L02_001B1C30;
extern const BeamWidths D_L02_001B1C38;
extern const BeamLayers D_L02_001B1C40;
extern const BeamColours D_L02_001B1C48;
extern u8 *D_L02_001B368C __attribute__((sda));
extern s32 D_L02_001A8F00 __attribute__((sda));

extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern int func_00283D38(int, int, float);
extern void func_L00_002EBE88(void *, int, int, int, int, int, float, float, float);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern void func_00282D08(void *, void *, void *, float);
extern void func_002C3150(void *, void *, int, int, int, int, float);

/* Draw callback that func_L02_004124A0 registers while the actor's fade (+0xC of its block at
   +0x68) is nonzero. A point 1.5 in front of the actor (matrix at +0xC0, position at +0x10) is
   joined to the target record (D_L02_001B368C, indexed by the block's first word, +0x30) by 13
   evenly spaced points; their z is displaced by sin(phase) * sin(j * pi / 13), the phase starting
   at the block's +0x14 and advancing by 2 * pi / 13 per point. The 13 points are drawn as a
   two-layer ribbon (func_L00_002EBE88) with the two colours faded by +0xC, and while
   D_L02_001A8F00 is zero a spark of the second kind is thrown from a random point on a random
   segment, falling at a speed drawn between the last two range words. */
void func_L02_004129D0(u8 *a0) {
    SparkRange range = D_L02_001B1C10;
    SparkSizes sizes = D_L02_001B1C20;
    SparkColours colours = D_L02_001B1C28;
    SparkKinds kinds = D_L02_001B1C30;
    BeamWidths widths = D_L02_001B1C38;
    BeamLayers layers = D_L02_001B1C40;
    BeamColours beam = D_L02_001B1C48;
    Vec4 pts[13] __attribute__((aligned(16)));
    Vec4 delta __attribute__((aligned(16)));
    Vec4 front __attribute__((aligned(16)));
    Vec4 vel __attribute__((aligned(16)));
    Vec4 spot __attribute__((aligned(16)));
    u8 *state;
    float phase;
    float step;
    float amp;
    float t;
    int i;
    int j;
    int col0;
    int col1;
    int seg;
    int kind;

    amp = 1.0f;
    *(TI128 *)&front = 0;
    front.z = 1.5f;
    state = *(u8 **)(a0 + 0x68);
    func_00283098(&front, &front, a0 + 0xC0);
    func_00282CC0(&front, &front, a0 + 0x10);
    func_00282CF0(&delta, D_L02_001B368C + (*(s32 *)state << 7) + 0x30, &front);
    func_00282D30(&delta, &delta, amp / func_00283CE0(12));
    qcopy(&pts[0], &front);
    for (i = 0; i < 12; i++) {
        Vec4 *p = &pts[i + 1];

        func_00282CC0(p, &pts[i], &delta);
        p->w = widths.f[0];
    }
    phase = *(float *)(state + 0x14);
    step = 1.0f / func_00283CE0(13) * 3.1415927f;
    for (j = 1; j < 13; j++) {
        Vec4 *q = &pts[j];

        t = func_00283198(phase);
        q->z += amp * t * func_00283198((float)j * step);
        phase = func_00283B98(phase, step + step);
    }
    col0 = func_00283D38(beam.rgba[0] & 0xFFFFFF, beam.rgba[0], *(float *)(state + 0xC));
    col1 = func_00283D38(beam.rgba[1] & 0xFFFFFF, beam.rgba[1], *(float *)(state + 0xC));
    func_L00_002EBE88(pts, layers.b[0], layers.b[1], 13, col0, col1, widths.f[0], widths.f[1],
                      *(float *)(state + 0x10));
    if (D_L02_001A8F00 == 0) {
        qzero_nc(&vel);
        seg = func_002A77E0(12);
        t = func_002A7878(0.0f, 1.0f);
        func_00282D08(&spot, &pts[seg], &pts[seg + 1], t);
        vel.z = -(func_002A7878(range.f[2], range.f[3]) * 0.016666668f);
        kind = (u8)func_002A7820(kinds.b[2], kinds.b[3]);
        func_002C3150(&spot, &vel, colours.i[1], kind, (u8)func_002A77E0(255), 0, sizes.f[1]);
    }
}
