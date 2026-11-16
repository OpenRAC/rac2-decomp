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

/* Per-frame update of a thrown Joba projectile: it spins and flies with a spark trail, then explodes on a hit, when it falls below the floor, or on mode 111 (PAL version). */
void thrown_l11_projectile_update_2_pal(char *moby)
{
    float next_pos[4], velocity[4], unused_zero[4];
    char *vars = *(char **)(moby + 0x68);
    char *effect_slot;
    float size_a, size_b;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(float *)(moby + 0xF0) = FastAddRotations(*(float *)(moby + 0xF0), *(float *)(vars + 0x20) * 0.7f);
        *(float *)(moby + 0xF4) = FastAddRotations(*(float *)(moby + 0xF4), *(float *)(vars + 0x20) * 0.5f);
        *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(moby + 0xF8), *(float *)(vars + 0x20));
        FastVecAdd(next_pos, moby + 0x10, vars);
        if (coll_test_point(next_pos, 0, moby, g_projectile_coll_radius) &&
            g_hit_l11_result && g_hit_l11_result != *(char **)(vars + 0x10)) {
            moby_set_state(moby, 1, -1);
            return;
        }
        qcopy(moby + 0x10, next_pos);
        FastVecScale(velocity, vars, -0.5f);
        vec_clear_128(unused_zero);
        size_a = math_random_float_range(2.5f, 3.0f) * 210000.0f;
        size_b = math_random_float_range(0.2f, 0.4f) * 210000.0f;
        part_spawn_gravity_fade(moby + 0x10, velocity, 15, g_spark_particle_texture, 3, 80, 0, size_a, size_b, 0.0f, 0);
        if (*(float *)(vars + 0x24) < *(float *)(moby + 0x18) && *(float *)(vars + 0x24) > 0.0f)
            moby_set_state(moby, 2, -1);
        effect_slot = part_find_owned_effect_slot(moby, 0x10000, 0);
        if (effect_slot) {
            *(float *)(vars + 0x14) -= *(float *)(effect_slot + 0x2C);
            if (*(float *)(vars + 0x14) <= 0.0f) moby_set_state(moby, 1, -1);
        }
        if (g_game_mode == 111) moby_set_state(moby, 2, -1);
        break;
    case 1:
        coll_sweep_from_object(moby, moby + 0x10, 3.0f, 0x10001, *(float *)(vars + 0x18), 1.0f, 0, 1, 0);
        SpawnExplosion_pal(moby + 0x10, 1, 2, 2, 5, 10, 2, 1, 3.0f, 0.0f, 0, 1, 0, 0);
        moby_mark_spawned(moby);
        return;
    case 2:
        SpawnExplosion_pal(moby + 0x10, 0, 10, 2, 10, 5, 2, 1, 2.0f, 0.0f, 0, 1, 0, 0);
        moby_mark_spawned(moby);
        return;
    }
    gfx_add_draw_callback_third(part_spawn_two_glow_effects, moby);
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
    float parameter_a;
    float parameter_b;
    float heading;
    float turn;
    float parameter_d;
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
    u64 owner_flags;
    char pad40[0x28];
    SpawnState *data;
} SpawnObject;

/* Creates the object-type 0xE7B effect for an owner: copies the start velocity and position,
   picks a random heading and turn rate, and registers it. Returns the new object or NULL. */
char *joba_swirl_effect_create_pal(char *owner, void *velocity, void *position, float param_a, float param_b,
                        float scale, float param_d)
{
    SpawnObject *obj = (SpawnObject *)CreateMoby(0xE7B);

    if (obj) {
        SpawnState *state;
        int arg;

        obj->opacity = 255;
        obj->alpha = 255;
        obj->enabled = 1;
        obj->state = 0;
        obj->owner_flags = *(long long *)(owner + 0x38);
        qcopy(obj->position, position);

        state = obj->data;
        qcopy(state, velocity);
        state->owner = owner;
        state->parameter_a = param_a;
        state->parameter_b = param_b;
        state->heading = math_random_angle();
        state->turn = math_random_float_range(0.062831864f, 0.12566373f);
        state->parameter_d = param_d;

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
