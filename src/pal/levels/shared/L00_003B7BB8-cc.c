/* func_PAL_L00_003B7BB8, the PAL copy of func_L00_003B4198: the same C, where rename func_L00_003B4560 becomes func_PAL_L00_003B7FC0; scale age; scale D_L00_001AF8E0 - 30; rewrap D_L00_001AF8E0. */
#include "common.h"

typedef unsigned int TI128 __attribute__((mode(TI)));

/* A quadword vector: .q moves all four floats at once. */
typedef union {
    TI128 q;
    float v[4];
} Vector;

/* A textured quad as func_00280B90 draws it (func_00281DE8 fills the same layout). */
typedef struct {
    Vector corners[4];          /* 0x00 */
    u32 colors[4];              /* 0x40: one per corner */
    float uv[4][2];             /* 0x50: u, v per corner */
    u64 f70;                    /* 0x70 */
    u64 tex0;                   /* 0x78: from func_0027C878 */
    u64 tex1;                   /* 0x80 */
    u64 alpha;                  /* 0x88: GS ALPHA blend (0x48 additive, 0x44 normal) */
} EffectQuad;

/* The moby fields this unit reads. */
typedef struct {
    u8 pad00[0x10];
    Vector position;            /* 0x10 */
    u8 state;                   /* 0x20 */
    u8 pad21[0x68 - 0x21];
    void *vars;                 /* 0x68 */
} Moby;

/* The effect's instance data. */
typedef struct {
    u8 pad00[8];
    short age;                  /* 0x08: frames since the effect started */
} EffectVars;

typedef struct {
    int f00;
    short age;                  /* 0x04: frames */
    u16 f06;
    short active;               /* 0x08 */
    short f0A;
} Ring;

extern Ring g_ring_table[10];
/* These vectors are outside small data even in this unit's G64 profile. */
extern Vector g_camera_l00_position __attribute__((section(".data")));    /* the point the quads face */
extern Vector g_hero_state_block __attribute__((section(".data")));
extern float g_ring_growth_rate[] __attribute__((sda));     /* [0]: 1 / ring growth time */
extern int g_effect_lifetime_frames __attribute__((sda));         /* effect lifetime, frames */
extern int g_ring_start_alpha __attribute__((sda));         /* ring start alpha */
extern u32 g_ring_color __attribute__((sda));         /* ring colour */
extern Vector g_ring_quad_corners[4] __attribute__((sda));   /* unit quad corners */
extern float g_ring_start_size __attribute__((sda));       /* ring start size */
extern float g_ring_end_size __attribute__((sda));       /* ring end size */
extern float g_ring_core_size __attribute__((sda));       /* core size */
extern u32 g_ring_core_alpha_bits __attribute__((sda));         /* core alpha bits */
extern u32 g_ring_core_color __attribute__((sda));         /* core colour */
extern float g_ring_core_view_offset __attribute__((sda));       /* core offset toward the viewer */

extern float IntToFloat(int value);
extern float math_random_signed_float_range(float min, float max);
extern int FloatToInt(float value);
extern u64 GetEffectTextureDescriptor(int texture);
extern void FastVecSub(void *out, void *a, void *b);
extern void FastVecAdd(void *out, void *a, void *b);
extern void vec_scale_to_length(void *out, void *in, float length);
extern void FastVecScale(void *out, float scale, void *in);
extern void FastVecCross(void *out, void *a, void *b);
extern void transform_vector(void *out, void *point, void *matrix);
extern void draw_world_quad(EffectQuad *quad, void *a1, int a2);
extern void mesh_draw_four_signs_pal(Moby *moby, float fade);
extern void jitter_trail_draw(void);

/* Draws the active rings, growing and fading with age, and a flickering core quad, all
   facing D_L00_001B8DC0; the effect fades out over the last 30 frames of its life. */
void draw_timed_quad_effects_pal(Moby *moby)
{
    EffectQuad quad;
    Vector billboard[4];
    Vector corner;
    float fade;
    float t;
    float start_alpha;
    float fade_alpha;
    float size;
    float radius;
    int i;
    int j;
    int k;
    int alpha;
    short age;
    EffectVars *vars = moby->vars;

    if (moby->state != 2) {
        age = vars->age;
        if (age >= (((int)(g_effect_lifetime_frames - 30) * 5 + 2) / 6))
            fade = IntToFloat((((int)(g_effect_lifetime_frames) * 5 + 2) / 6) - age) / IntToFloat(25);
        else
            fade = 1.0f;

        quad.tex0 = GetEffectTextureDescriptor(8);
        quad.alpha = 0x8000000048ULL;
        quad.tex1 = 0xFF9000000260ULL;
        quad.f70 = 0;
        quad.uv[0][0] = 0.0f;
        quad.uv[0][1] = 0.0f;
        quad.uv[1][0] = 0.0f;
        quad.uv[1][1] = 1.0f;
        quad.uv[2][0] = 1.0f;
        quad.uv[2][1] = 0.0f;
        quad.uv[3][0] = 1.0f;
        quad.uv[3][1] = 1.0f;

        /* A matrix facing D_L00_001B8DC0, placed at the moby. */
        FastVecSub(&billboard[0], &g_camera_l00_position, &moby->position);
        vec_scale_to_length(&billboard[0], &billboard[0], 1.0f);
        billboard[3].q = moby->position.q;
        FastVecScale(&billboard[2], -1.0f, &g_hero_state_block);
        FastVecCross(&billboard[1], &billboard[0], &billboard[2]);
        vec_scale_to_length(&billboard[1], &billboard[1], 1.0f);
        FastVecCross(&billboard[2], &billboard[1], &billboard[0]);

        for (i = 0; i < 10; ++i) {
            if (!g_ring_table[i].active)
                continue;
            t = IntToFloat(g_ring_table[i].age) * g_ring_growth_rate[0];
            if (t > 1.0f)
                t = 1.0f;
            size = g_ring_start_size + (g_ring_end_size - g_ring_start_size) * t;
            start_alpha = IntToFloat(g_ring_start_alpha);
            fade_alpha = IntToFloat(g_ring_start_alpha);
            alpha = FloatToInt(fade * (start_alpha + -fade_alpha * t));
            quad.colors[0] = quad.colors[1] = quad.colors[2] = quad.colors[3]
                = (g_ring_color & 0xFFFFFF) | ((u32)alpha << 24);
            for (j = 0; j < 4; ++j) {
                FastVecScale(&corner, size, &g_ring_quad_corners[j]);
                transform_vector(&quad.corners[j], &corner, billboard);
            }
            draw_world_quad(&quad, 0, 0);
        }

        /* The core, normally blended and a little nearer the viewer. */
        quad.tex0 = GetEffectTextureDescriptor(11);
        quad.alpha = 0x8000000044ULL;
        quad.colors[0] = quad.colors[1] = quad.colors[2] = quad.colors[3]
            = (g_ring_core_color & 0xFFFFFF) | g_ring_core_alpha_bits;
        vec_scale_to_length(&billboard[3], &billboard[0], g_ring_core_view_offset);
        FastVecAdd(&billboard[3], &billboard[3], &moby->position);
        radius = g_ring_core_size + math_random_signed_float_range(0.0f, 0.1f);
        for (k = 0; k < 4; ++k) {
            FastVecScale(&corner, radius, &g_ring_quad_corners[k]);
            transform_vector(&quad.corners[k], &corner, billboard);
        }
        draw_world_quad(&quad, 0, 0);
        mesh_draw_four_signs_pal(moby, fade);
    }
    jitter_trail_draw();
}
