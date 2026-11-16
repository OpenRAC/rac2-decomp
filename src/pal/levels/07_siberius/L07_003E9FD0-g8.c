#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
extern void SetDeathBits_pal(void *, int, int);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern void *SpawnExplosion_pal(void *, s32, s32, s32, s32, s32, s32, s32, float, float, s32, s32, s32, s32);
extern int moby_transform_point_by_attachment(void *, void *, void *, void *);
extern void part_spawn_masked_debris_pal(void *, int, void *, float, float, float, float, int);
extern void moby_set_state(u8 *, int, int);
extern void moby_mark_spawned(void *);
extern u8 g_sound_state[];
extern u8 g_hero_position[];
extern float g_death_explosion_scale __attribute__((sda));

/* Handles a group member being killed: stops its sound, spawns an explosion and debris, and either respawns it or removes it (PAL: 50 Hz timings). */
void entity_handle_death_or_respawn_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    int slot;
    u8 *sound_slot;
    u8 *moby_pos;
    u8 *parent;
    union { Quad q; f32 f[4]; } explosion_pos;
    f32 push_vel[4] __attribute__((aligned(16)));
    f32 parent_point[4] __attribute__((aligned(16)));
    int count;

    if (vars[0x2E] != 2) {
        SetDeathBits_pal(moby, 0, 1);
    }
    slot = *(s32 *)(vars + 0x264);
    if (slot != -1) {
        sound_slot = g_sound_state + slot * 0x70;
        if (*(u8 **)(sound_slot + 0x88) == moby && sound_slot[0x74] != 0) {
            snd_stop_voice(slot);
        }
    }
    *(s32 *)(vars + 0x264) = -1;
    PlayMobySound(0, 0, moby);
    moby_pos = moby + 0x10;
    explosion_pos.q = 0;
    explosion_pos.f[2] = 0.5f;
    FastVecAdd(&explosion_pos, &explosion_pos, moby_pos);
    SpawnExplosion_pal(&explosion_pos, 0, 0, 0, 0, 0x14, 0x2D, 1, g_death_explosion_scale, 20.0f, 1, 0, 0, *(s32 *)(vars + 0x260));
    FastVecSub(push_vel, moby_pos, g_hero_position);
    push_vel[2] = 0.0f;
    vec_fast_normalize_helper(push_vel, push_vel, 0.080000006f);
    parent = *(u8 **)(vars + 0x260);
    if (parent != 0) {
        moby_transform_point_by_attachment(moby, parent, moby_pos, parent_point);
        FastVecAdd(push_vel, push_vel, parent_point);
    }
    part_spawn_masked_debris_pal(moby, 3, push_vel, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    count = *(u16 *)(vars + 0x21A) - 1;
    *(u16 *)(vars + 0x21A) = count;
    if ((s16)count != -1) {
        *(s16 *)(vars + 0x88) = 0;
        *(s32 *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(moby, 8, 4);
        vars[0x2E] = 1;
        *(f32 *)(vars + 0x20) = *(s16 *)(vars + 0x24);
    } else {
        moby_mark_spawned(moby);
    }
}

extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern void vec_random_direction(void *, float, float);
extern int math_random_int_range(int, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void *part_spawn_hero_relative(void *, void *, int, float, unsigned char, unsigned char, int);
extern float g_particle_pair_height __attribute__((sda));
extern float g_particle_pair_speed __attribute__((sda));
extern float g_particle_pair_lift_speed[] __attribute__((sda));
extern int g_particle_pair_value_range[] __attribute__((sda));
extern float g_particle_pair_scale_range[] __attribute__((sda));
extern int g_particle_pair_kind __attribute__((sda));

/* Emit two particles at opposite local offsets, including platform motion. */
void entity_spawn_particle_pair_pal(char *moby)
{
    float carry_delta[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    int side;

    qzero_nc(angles);
    if (*(void **)(vars + 0x260)) {
        moby_transform_point_and_rotation_by_parent(moby, *(void **)(vars + 0x260), moby + 0x10, angles, carry_delta, angles);
        FastVecSub(carry_delta, carry_delta, moby + 0x10);
    } else {
        qzero_nc(carry_delta);
    }
    for (side = 0; side < 2; side++) {
        int life, random_byte;
        float scale;

        qzero_nc(position);
        position[2] = g_particle_pair_height;
        if (!side)
            position[2] = -position[2];
        vec_random_direction(velocity, g_particle_pair_speed * (0.020000001f),
                      g_particle_pair_lift_speed[0] * (0.020000001f));
        FastVecAdd(velocity, velocity, carry_delta);
        life = ((s32)(math_random_int_range(g_particle_pair_value_range[0], g_particle_pair_value_range[1])) * 5 + 2) / 6;
        matrix_mul_vec3(position, position, moby + 0xC0);
        life = (unsigned char)life;
        FastVecAdd(position, position, moby + 0x10);
        scale = math_random_float_range(g_particle_pair_scale_range[0], g_particle_pair_scale_range[1]);
        random_byte = math_random_int_below(255);
        part_spawn_hero_relative(position, velocity, g_particle_pair_kind, scale, life, (unsigned char)random_byte, 0);
    }
}
