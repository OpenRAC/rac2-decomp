#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));

extern void SetDeathBits(void *, int, int);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern void *SpawnExplosion(void *, s32, s32, s32, s32, s32, s32, s32, float, float, s32, s32, s32, s32);
extern int moby_transform_point_by_attachment(void *, void *, void *, void *);
extern void part_spawn_masked_debris(void *, int, void *, float, float, float, float, int);
extern void moby_set_state(u8 *, int, int);
extern void moby_mark_spawned(void *);
extern u8 g_sound_state[];
extern u8 g_hero_position[];
extern float g_death_explosion_scale __attribute__((sda));

/* Handles the entity's death: stops its sound, spawns an explosion and flying pickups, then
   respawns it with one life fewer or removes it. */
void entity_handle_death_or_respawn(u8 *obj) {
    u8 *vars = *(u8 **)(obj + 0x68);
    int slot;
    u8 *rec;
    u8 *pos;
    u8 *platform;
    union { Quad q; f32 f[4]; } burst_pos;
    f32 impulse[4] __attribute__((aligned(16)));
    f32 carry[4] __attribute__((aligned(16)));
    int lives_left;

    if (vars[0x2E] != 2) {
        SetDeathBits(obj, 0, 1);
    }
    slot = *(s32 *)(vars + 0x264);
    if (slot != -1) {
        rec = g_sound_state + slot * 0x70;
        if (*(u8 **)(rec + 0x88) == obj && rec[0x74] != 0) {
            snd_stop_voice(slot);
        }
    }
    *(s32 *)(vars + 0x264) = -1;
    PlayMobySound(0, 0, obj);
    pos = obj + 0x10;
    burst_pos.q = 0;
    burst_pos.f[2] = 0.5f;
    FastVecAdd(&burst_pos, &burst_pos, pos);
    SpawnExplosion(&burst_pos, 0, 0, 0, 0, 0x14, 0x2D, 1, g_death_explosion_scale, 20.0f, 1, 0, 0, *(s32 *)(vars + 0x260));
    FastVecSub(impulse, pos, g_hero_position);
    impulse[2] = 0.0f;
    vec_fast_normalize_helper(impulse, impulse, 0.06666667f);
    platform = *(u8 **)(vars + 0x260);
    if (platform != 0) {
        moby_transform_point_by_attachment(obj, platform, pos, carry);
        FastVecAdd(impulse, impulse, carry);
    }
    part_spawn_masked_debris(obj, 3, impulse, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    lives_left = *(u16 *)(vars + 0x21A) - 1;
    *(u16 *)(vars + 0x21A) = lives_left;
    if ((s16)lives_left != -1) {
        *(s16 *)(vars + 0x88) = 0;
        *(s32 *)(obj + 0x98) = 0;
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(obj, 8, 4);
        vars[0x2E] = 1;
        *(f32 *)(vars + 0x20) = *(s16 *)(vars + 0x24);
    } else {
        moby_mark_spawned(obj);
    }
}
