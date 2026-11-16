#include "include_asm.h"

#include "common.h"
extern float FastAddRotations(float, float);
extern void FastVecAdd(void *, void *, void *);
extern int coll_test_point(void *, int, char *, float);
extern void moby_set_state(char *, int, int);
extern void FastVecScale(void *, void *, float);
extern void vec_clear_128(void *);
extern float math_random_float_range(float, float);
extern void *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern char *part_find_owned_effect_slot(char *, int, int);
extern int coll_sweep_from_object(void *, void *, float, int, float, float, int, int, int);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void moby_mark_spawned(char *);
extern void gfx_add_draw_callback_third(void *, void *);
extern void part_spawn_two_glow_effects(void);
extern float g_projectile_coll_radius __attribute__((sda));
extern int g_spark_particle_texture __attribute__((sda));
extern char *g_hit_l11_result NOT_SDA;
extern int g_game_mode NOT_SDA;

void thrown_l11_projectile_update_2_pal(char *p)
{
    float next[4], velocity[4], zero[4];
    char *q = *(char **)(p + 0x68);
    char *hit;
    float a, b;
    switch (*(unsigned char *)(p + 0x20)) {
    case 0:
        *(float *)(p + 0xF0) = FastAddRotations(*(float *)(p + 0xF0), *(float *)(q + 0x20) * 0.7f);
        *(float *)(p + 0xF4) = FastAddRotations(*(float *)(p + 0xF4), *(float *)(q + 0x20) * 0.5f);
        *(float *)(p + 0xF8) = FastAddRotations(*(float *)(p + 0xF8), *(float *)(q + 0x20));
        FastVecAdd(next, p + 0x10, q);
        if (coll_test_point(next, 0, p, g_projectile_coll_radius) &&
            g_hit_l11_result && g_hit_l11_result != *(char **)(q + 0x10)) {
            moby_set_state(p, 1, -1);
            return;
        }
        qcopy(p + 0x10, next);
        FastVecScale(velocity, q, -0.5f);
        vec_clear_128(zero);
        a = math_random_float_range(2.5f, 3.0f) * 210000.0f;
        b = math_random_float_range(0.2f, 0.4f) * 210000.0f;
        part_spawn_gravity_fade(p + 0x10, velocity, 15, g_spark_particle_texture, 3, 80, 0, a, b, 0.0f, 0);
        if (*(float *)(q + 0x24) < *(float *)(p + 0x18) && *(float *)(q + 0x24) > 0.0f)
            moby_set_state(p, 2, -1);
        hit = part_find_owned_effect_slot(p, 0x10000, 0);
        if (hit) {
            *(float *)(q + 0x14) -= *(float *)(hit + 0x2C);
            if (*(float *)(q + 0x14) <= 0.0f) moby_set_state(p, 1, -1);
        }
        if (g_game_mode == 111) moby_set_state(p, 2, -1);
        break;
    case 1:
        coll_sweep_from_object(p, p + 0x10, 3.0f, 0x10001, *(float *)(q + 0x18), 1.0f, 0, 1, 0);
        SpawnExplosion_pal(p + 0x10, 1, 2, 2, 5, 10, 2, 1, 3.0f, 0.0f, 0, 1, 0, 0);
        moby_mark_spawned(p);
        return;
    case 2:
        SpawnExplosion_pal(p + 0x10, 0, 10, 2, 10, 5, 2, 1, 2.0f, 0.0f, 0, 1, 0, 0);
        moby_mark_spawned(p);
        return;
    }
    gfx_add_draw_callback_third(part_spawn_two_glow_effects, p);
}

extern char *CreateMoby(int);
extern float math_random_angle(void);
extern void part_l11_spawn_spark_ring_pal(void *, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern float g_swirl_effect_scale __attribute__((sda));
extern int g_swirl_effect_arg __attribute__((sda));
typedef struct {
    float velocity[4];
    char *owner;
    float parameterA;
    float parameterB;
    float heading;
    float turn;
    float parameterD;
} SpawnState;
typedef struct {
    char pad00[0x10];
    float position[4];
    u8 state;
    u8 pad21[2];
    u8 kind;
    char pad24[8];
    float scale;
    u8 opacity;
    u8 enabled;
    u16 alpha;
    u16 flags;
    u16 pad36;
    u64 ownerFlags;
    char pad40[0x28];
    SpawnState *data;
} SpawnObject;

/* Creates the object-type 0xE7B effect for an owner: copies the start velocity and position,
   picks a random heading and turn rate, and registers it. Returns the new object or NULL. */
char *joba_swirl_effect_create_pal(char *owner, void *velocity, void *position, float paramA, float paramB,
                        float scale, float paramD)
{
    SpawnObject *obj = (SpawnObject *)CreateMoby(0xE7B);

    if (obj) {
        SpawnState *state;
        int arg;

        obj->opacity = 255;
        obj->alpha = 255;
        obj->enabled = 1;
        obj->state = 0;
        obj->ownerFlags = *(long long *)(owner + 0x38);
        qcopy(obj->position, position);

        state = obj->data;
        qcopy(state, velocity);
        state->owner = owner;
        state->parameterA = paramA;
        state->parameterB = paramB;
        state->heading = math_random_angle();
        state->turn = math_random_float_range(0.062831864f, 0.12566373f);
        state->parameterD = paramD;

        obj->kind = 255;
        obj->flags = 8;
        arg = g_swirl_effect_arg;
        obj->scale = g_swirl_effect_scale * scale;
        obj->flags = 0x1008;
        part_l11_spawn_spark_ring_pal(obj->position, arg);
        snd_play_from_class_bank(0, 0, (char *)obj, 0xE7B);
    }
    return (char *)obj;
}
