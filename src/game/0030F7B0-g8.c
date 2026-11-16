#include "include_asm.h"
#include "names.h"

extern char g_camera_eye_state[];
extern int math_random_int_below(int);
extern float g_sparkle_time_min __attribute__((sda));
extern float g_sparkle_time_max __attribute__((sda));
extern unsigned char g_sparkle_kind __attribute__((sda));
extern void *g_sparkle_effect_default __attribute__((sda));
extern void *g_sparkle_effect_third __attribute__((sda));
extern void *g_sparkle_effect_alt __attribute__((sda));
extern float g_sparkle_scale __attribute__((sda));
extern float g_sparkle_scale_third __attribute__((sda));
extern char g_hero_state_block[];
extern void FastVecSub(void *, void *, void *);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern float math_random_angle(void);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void *part_spawn_hero_relative(void *, void *, void *, int, int, int, float);

/* Spawns two sparkle effects at the object, using a random spin and a color chosen by its flag. */
void part_spawn_sparkles(unsigned char *object)
{
    char first[16];
    char second[16];
    char third[16];
    unsigned char *state;
    char *basis;
    void *effect;
    unsigned char kind;
    unsigned char random;

    state = *(unsigned char **)(object + 0x68);
    FastVecSub(first, g_camera_eye_state, object + 0x10);
    basis = g_hero_state_block;
    FastVecScale(second, basis,
                  math_random_float_range(g_sparkle_time_min * 0.016666668f,
                               g_sparkle_time_max * 0.016666668f));
    math_apply_axis_rotation_to_quat(third, second, first, math_random_angle());

    effect = state[0x57] != 0 ? g_sparkle_effect_alt : g_sparkle_effect_default;
    kind = g_sparkle_kind;
    random = (unsigned char)math_random_int_below(255);
    part_spawn_hero_relative(object + 0x10, third, effect, kind, random, 1, g_sparkle_scale);

    kind = g_sparkle_kind;
    random = (unsigned char)math_random_int_below(255);
    part_spawn_hero_relative(object + 0x10, third, g_sparkle_effect_third, kind, random, 1, g_sparkle_scale_third);
}

extern char *g_linked_moby_private_data __attribute__((sda));

/* Turns on a flag in the private data of the object stored in D_001AF880, if there is one. */
void moby_set_linked_flag(void)
{
    char *p = g_linked_moby_private_data;
    if (p != 0) {
        char *q = *(char **)(p + 0x68);
        *(int *)(q + 0x28) = 1;
    }
}

extern float g_lock_on_sprite_angle __attribute__((sda));
extern char g_emitter_origin[] __attribute__((sda));
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern int FastTweenColor(int, int, float);
extern void gfx_draw_owner_effect_slots(void *);
extern void gfx_draw_billboard_quad(char *, int, unsigned int, int, float, float, float);

/* Advances the shared angle of the effect, picks the three sprite colours for it and draws
   the three sprites. */
void lock_on_draw_sprites(void *object)
{
    float angle = FastAddRotations(g_lock_on_sprite_angle, 0.125f);
    float scale;
    float size_a;
    float size_b;
    float size_c;
    int colour_a;
    int colour_b;
    int colour_c;

    g_lock_on_sprite_angle = angle;
    scale = math_fast_sin_or_cos_a(angle);
    scale = (scale + 1.0f) * 0.5f;
    size_b = scale * 0.0625f + 0.0625f;
    size_c = scale * 0.19999999f + 0.15f;
    size_a = scale * 0.125f + 0.125f;

    colour_a = FastTweenColor(0x2F007F00, 0x3F007F00, scale);
    colour_b = FastTweenColor(0x2F7F7F7F, 0x5F7F7F7F, scale);
    colour_c = FastTweenColor(0x10003F00, 0x10003F00, scale);

    gfx_draw_owner_effect_slots(object);
    gfx_draw_billboard_quad(g_emitter_origin, 0x31, colour_a, 1, size_a, 0.125f, 0.0f);
    gfx_draw_billboard_quad(g_emitter_origin, 0x31, colour_b, 1, size_b, 0.124f, 0.0f);
    gfx_draw_billboard_quad(g_emitter_origin, 0x0B, colour_c, 1, size_c, 0.123f, 0.0f);
}
