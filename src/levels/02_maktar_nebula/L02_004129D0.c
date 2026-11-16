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

extern const SparkRange g_spark_l02_range_2;
extern const SparkSizes g_spark_sizes;
extern const SparkColours g_spark_colours;
extern const SparkKinds g_spark_kinds;
extern const BeamWidths g_beam_widths;
extern const BeamLayers g_beam_layers;
extern const BeamColours g_beam_colours;
extern u8 *g_matrix_l02_record_table __attribute__((sda));
extern s32 g_arena_state_words __attribute__((sda));

extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float IntToFloat(int);
extern void FastVecScale(void *, void *, float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern int FastTweenColor(int, int, float);
extern void DrawTwoLayerPolylineRibbon(void *, int, int, int, int, int, float, float, float);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern void lerp_vector(void *, void *, void *, float);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);

/* Draw callback that func_L02_004124A0 registers while the actor's fade (+0xC of its block at
   +0x68) is nonzero. A point 1.5 in front of the actor (matrix at +0xC0, position at +0x10) is
   joined to the target record (D_L02_001B368C, indexed by the block's first word, +0x30) by 13
   evenly spaced points; their z is displaced by sin(phase) * sin(j * pi / 13), the phase starting
   at the block's +0x14 and advancing by 2 * pi / 13 per point. The 13 points are drawn as a
   two-layer ribbon (func_L00_002EBE88) with the two colours faded by +0xC, and while
   D_L02_001A8F00 is zero a spark of the second kind is thrown from a random point on a random
   segment, falling at a speed drawn between the last two range words. */
/* Draws a wavy glowing beam from the object to a target object and throws off sparks along it. */
void DrawWavyBeamToTarget(u8 *moby) {
    SparkRange range = g_spark_l02_range_2;
    SparkSizes sizes = g_spark_sizes;
    SparkColours colours = g_spark_colours;
    SparkKinds kinds = g_spark_kinds;
    BeamWidths widths = g_beam_widths;
    BeamLayers layers = g_beam_layers;
    BeamColours beam = g_beam_colours;
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
    state = *(u8 **)(moby + 0x68);
    matrix_mul_vec3(&front, &front, moby + 0xC0);
    FastVecAdd(&front, &front, moby + 0x10);
    FastVecSub(&delta, g_matrix_l02_record_table + (*(s32 *)state << 7) + 0x30, &front);
    FastVecScale(&delta, &delta, amp / IntToFloat(12));
    qcopy(&pts[0], &front);
    for (i = 0; i < 12; i++) {
        Vec4 *p = &pts[i + 1];

        FastVecAdd(p, &pts[i], &delta);
        p->w = widths.f[0];
    }
    phase = *(float *)(state + 0x14);
    step = 1.0f / IntToFloat(13) * 3.1415927f;
    for (j = 1; j < 13; j++) {
        Vec4 *q = &pts[j];

        t = math_fast_sin_or_cos_b(phase);
        q->z += amp * t * math_fast_sin_or_cos_b((float)j * step);
        phase = FastAddRotations(phase, step + step);
    }
    col0 = FastTweenColor(beam.rgba[0] & 0xFFFFFF, beam.rgba[0], *(float *)(state + 0xC));
    col1 = FastTweenColor(beam.rgba[1] & 0xFFFFFF, beam.rgba[1], *(float *)(state + 0xC));
    DrawTwoLayerPolylineRibbon(pts, layers.b[0], layers.b[1], 13, col0, col1, widths.f[0], widths.f[1],
                      *(float *)(state + 0x10));
    if (g_arena_state_words == 0) {
        qzero_nc(&vel);
        seg = math_random_int_below(12);
        t = math_random_float_range(0.0f, 1.0f);
        lerp_vector(&spot, &pts[seg], &pts[seg + 1], t);
        vel.z = -(math_random_float_range(range.f[2], range.f[3]) * 0.016666668f);
        kind = (u8)math_random_int_range(kinds.b[2], kinds.b[3]);
        part_spawn_hero_relative(&spot, &vel, colours.i[1], kind, (u8)math_random_int_below(255), 0, sizes.f[1]);
    }
}
