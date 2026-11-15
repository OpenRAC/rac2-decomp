#include "common.h"

/* The trail drawn behind an object: three textured layers along the 35-entry
 * position ring at D_L00_001B144C. */

typedef int Quad __attribute__((mode(TI)));

typedef union {
    Quad q;
    float f[4];
} TrailVector;

/* A strip packet handed to func_00280B90. */
typedef struct {
    TrailVector v[4];
    int color[4];
    float uv[8];
    long long tag[4];
} TrailPacket;

/* A ring entry is 64 bytes; only its first position is used here. */
typedef struct {
    TrailVector position, other;
    char pad[32];
} TrailPoint;

/* The ring bookkeeping at object +0x68. */
typedef struct {
    TrailVector position;
    char pad[0x34];
    int count;
    int index;
    char pad4C[12];
    float u, v;
} TrailState;

extern TrailPoint *g_lava_gun_ring_entries __attribute__((sda));
extern TrailVector g_camera_l00_position;

extern long long GetEffectTextureDescriptor(int);
extern float math_random_float_range(float low, float high);
extern void draw_world_quad(void *packet, int, int);
extern void FastVecSub(void *dst, void *a, void *b);
extern void FastVecScale(void *dst, void *src, float scale);
extern void FastVecCross(void *dst, void *a, void *b);
extern void vec_scale_to_length(void *dst, void *src, float length);
extern void transform_vector(void *dst, void *src, void *matrix);
/* Not the same function in every level. */
extern void ref_L00_0041B1B8_00(void *packet);

/* Draw the three layers. The outer layer is six times wider, and both widths
 * taper by 0.94 per segment. */
/* Draws a glowing three-layer trail behind an object, following its recent positions. */
void DrawPositionRingTrail(char *self, float width)
{
    TrailPacket core, streak, glow;
    /* func_002830C0 consumes all four consecutive columns. */
    TrailVector basis[4], narrowOffset, wideOffset, first, second;
    TrailState *state = *(TrailState **)(self + 0x68);
    int index, next;
    float half;

    if (state->count == 0) {
        return;
    }

    core.tag[1] = GetEffectTextureDescriptor(10);
    core.tag[2] = 0xFF9000000260LL;
    core.tag[3] = 0x4000000064LL;
    core.color[0] = core.color[1] = core.color[2] = core.color[3] = 0x609F9F9F;
    core.tag[0] = 0;

    streak.tag[1] = GetEffectTextureDescriptor(14);
    streak.tag[2] = 0xFF9000000260LL;
    streak.tag[3] = 0x4000000068LL;
    streak.color[0] = streak.color[1] = streak.color[2] = streak.color[3] = 0x507F7F7F;
    streak.tag[0] = 0;

    glow.tag[1] = GetEffectTextureDescriptor(43);
    glow.tag[2] = 0xFF9000000260LL;
    glow.tag[3] = 0x5000000068LL;
    glow.tag[0] = 0;
    glow.color[0] = glow.color[1] = glow.color[2] = glow.color[3] = 0x55103080;

    half = width * 0.5f;
    narrowOffset.q = 0;
    narrowOffset.f[3] = 1.0f;
    narrowOffset.f[2] = math_random_float_range(half, width);
    wideOffset.q = 0;
    wideOffset.f[3] = 1.0f;
    wideOffset.f[2] = narrowOffset.f[2] * 6.0f;
    ref_L00_0041B1B8_00(&core);

    core.uv[0] = state->u;
    core.uv[1] = state->v;
    core.uv[2] = state->u;
    core.uv[3] = state->v + 1.0f;
    core.uv[4] = state->u + 1.0f;
    core.uv[5] = state->v;
    core.uv[6] = state->u + 1.0f;
    core.uv[7] = state->v + 1.0f;

    streak.uv[0] = state->u;
    streak.uv[1] = 0.0f;
    streak.uv[2] = state->u;
    streak.uv[3] = 1.0f;
    streak.uv[4] = state->u + 1.0f;
    streak.uv[5] = 0.0f;
    streak.uv[6] = state->u + 1.0f;
    streak.uv[7] = 1.0f;

    glow.uv[0] = state->u;
    glow.uv[1] = 0.0f;
    glow.uv[2] = state->u;
    glow.uv[3] = 1.0f;
    glow.uv[4] = state->u + 1.0f;
    glow.uv[5] = 0.0f;
    glow.uv[6] = state->u + 1.0f;
    glow.uv[7] = 1.0f;

    /* Basis at the trail's head. */
    qcopy_nc(&first, &state->position);
    index = state->index;
    qcopy_nc(&second, &g_lava_gun_ring_entries[index].position);
    FastVecSub(&basis[0], &second, &first);
    vec_scale_to_length(&basis[0], &basis[0], 1.0f);
    FastVecSub(&basis[1], &g_camera_l00_position, &first);
    FastVecCross(&basis[2], &basis[1], &basis[0]);
    vec_scale_to_length(&basis[2], &basis[2], 1.0f);
    FastVecCross(&basis[1], &basis[0], &basis[2]);
    qcopy_nc(&basis[3], &first);

    core.v[0].q = narrowOffset.q;
    FastVecScale(&core.v[1], &core.v[0], -1.0f);
    transform_vector(&core.v[0], &core.v[0], &basis[0]);
    transform_vector(&core.v[1], &core.v[1], &basis[0]);
    streak.v[0].q = core.v[0].q;
    streak.v[1].q = core.v[1].q;

    glow.v[0].q = wideOffset.q;
    FastVecScale(&glow.v[1], &glow.v[0], -1.0f);
    transform_vector(&glow.v[0], &glow.v[0], &basis[0]);
    transform_vector(&glow.v[1], &glow.v[1], &basis[0]);

    {
        int i;

        for (i = 1; i < state->count; i++) {
            core.v[2].q = narrowOffset.q;
            FastVecScale(&core.v[3], &core.v[2], -1.0f);
            glow.v[2].q = wideOffset.q;
            FastVecScale(&glow.v[3], &glow.v[2], -1.0f);

            next = index - 1;
            if (next < 0) {
                next = 34;
            }
            first.q = g_lava_gun_ring_entries[index].position.q;
            second.q = g_lava_gun_ring_entries[next].position.q;

            FastVecSub(&basis[0], &second, &first);
            vec_scale_to_length(&basis[0], &basis[0], 1.0f);
            FastVecSub(&basis[1], &g_camera_l00_position, &first);
            FastVecCross(&basis[2], &basis[1], &basis[0]);
            vec_scale_to_length(&basis[2], &basis[2], 1.0f);
            FastVecCross(&basis[1], &basis[0], &basis[2]);
            basis[3].q = first.q;

            transform_vector(&core.v[2], &core.v[2], &basis[0]);
            transform_vector(&core.v[3], &core.v[3], &basis[0]);
            transform_vector(&glow.v[2], &glow.v[2], &basis[0]);
            transform_vector(&glow.v[3], &glow.v[3], &basis[0]);
            streak.v[2].q = core.v[2].q;
            streak.v[3].q = core.v[3].q;

            draw_world_quad(&core, 0, 0);
            draw_world_quad(&streak, 0, 0);
            draw_world_quad(&glow, 0, 0);

            /* Each draw may change its packet; advance each layer separately. */
            core.v[0].q = core.v[2].q;
            core.v[1].q = core.v[3].q;
            qcopy_nc(&streak.v[0], &streak.v[2]);
            qcopy_nc(&streak.v[1], &streak.v[3]);
            glow.v[0].q = glow.v[2].q;
            glow.v[1].q = glow.v[3].q;

            index = index - 1 < 0 ? 34 : index - 1;
            width *= 0.94f;
            half *= 0.94f;
            core.color[0] = core.color[1] = core.color[2];
            streak.color[0] = streak.color[1] = streak.color[2];
            glow.color[0] = glow.color[1] = glow.color[2];
            narrowOffset.f[2] = math_random_float_range(half, width);
            wideOffset.f[2] = narrowOffset.f[2] * 6.0f;
        }
    }

    basis[3].q = second.q;
    transform_vector(&core.v[2], &core.v[2], &basis[0]);
    transform_vector(&core.v[3], &core.v[3], &basis[0]);
}
