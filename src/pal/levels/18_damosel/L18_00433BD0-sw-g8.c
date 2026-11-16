#include "include_asm.h"

#include "common.h"
extern void moby_mark_spawned(void *);
extern int snd_is_voice_playing_for_owner(u8 *, int);
extern int PlayMobySound(int, int, u8 *);
extern void snd_stop_voice(int);
extern u8 g_sound_state[];
extern void *part_find_owned_effect_slot(u8 *, int, int);
extern float moby_update_aim_target_strength_pal(u8 *, int);
extern int part_spawn_damage_debris_pal(void *, void *, void *);
extern char *SpawnExplosion_pal(void *, int, int, int, float, float, int, int, int, int, int, int, int, void *);
extern u8 *g_moby_l18_table;
extern void extermibot_destroy_piece_and_parts_pal(u8 *);
extern void extermibot_shrink_piece_and_parts(u8 *, int);
extern void extermibot_advance_piece_to_state(u8 *);
extern void leader_start_moving(u8 *);
extern void leader_steer_pal(u8 *, int, int);
extern int path_step_along_point(u8 *, void *, int, void *, int, float);
extern void vec_random_direction(void *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void part_spawn_masked_debris(u8 *, int, void *, int, float, float, float, float);
extern void anim_start_blended(u8 *, int, int, int);
extern void moby_set_state(u8 *, int, int);
extern int IsPointInCuboid(u8 *, int);
extern u8 g_hero_position[];
extern float moby_get_anim_value(u8 *);
extern int flag_set_first_pending(u8 *);
extern int *g_path_l18_table[];
extern int path_measure_moby_against_entry(void *, int, float);
typedef struct {
    u8 pad00[0x20];
    float health;
    u8 pad24[10];
    u8 state;
    u8 pad2F[0x21];
    float hit[4];
    u8 pad60[0x10];
    float movement[4];
    float velocity[4];
    int ids[6];
    int paths[2];
    short groups[6];
    short waypoint;
    short group;
    int escapePath;
    int trigger;
    u8 padC8[0x14];
    int voice;
} LeaderState;
static inline void ReleaseVoice(u8 *a, LeaderState *s) {
    int slot = s->voice;
    if (slot != -1) {
        u8 *record = g_sound_state + slot * 0x70;
        if (*(u8 **)(record + 0x88) == a && record[0x74])
            snd_stop_voice(slot);
    }
    s->voice = -1;
}
extern u8 *g_level_base_pointer;

void leader_update_pal(u8 *a) {
    LeaderState *s = *(LeaderState **)(a + 0x68);
    float hit;
    float vec[4];

    if (a[0x20] >= 2) {
        if (!snd_is_voice_playing_for_owner(a, s->voice))
            s->voice = PlayMobySound(0, 4, a);
    } else if (snd_is_voice_playing_for_owner(a, s->voice)) {
        ReleaseVoice(a, s);
    }
    hit = moby_update_aim_target_strength_pal(a, part_find_owned_effect_slot(a, 0x10000, 0));
    if (a[0x20] >= 2) {
        s->health -= hit;
        part_spawn_damage_debris_pal(a, s->hit, &s->health);
        if (s->health <= 0.0f || s->state == 2) {
            int i;
            SpawnExplosion_pal(a + 0x10, 1, 0x19, 20, 1.0f, 20.0f, 20, 20, 45, 1, 1, 1, 0, 0);
            for (i = 0; i < 6; i++) {
                if (s->ids[i] != -1)
                    extermibot_destroy_piece_and_parts_pal(g_moby_l18_table + (s->ids[i] << 8));
            }
            if (snd_is_voice_playing_for_owner(a, s->voice))
                ReleaseVoice(a, s);
            vec_random_direction(vec, 0.120000005f, 0.3f);
            FastVecAdd(vec, vec, s->velocity);
            part_spawn_masked_debris(a, 63, vec, 255, 3.0f, 6.0f, 3.0f, 6.0f);
            moby_mark_spawned(a);
            return;
        }
    }
    switch (a[0x20]) {
    case 0: {
        int i;
        int all;
        u8 *base;
        anim_start_blended(a, 1, 0, 0);
        *(int *)(a + 0x48) = 0;
        *(int *)(a + 0x98) = 0;
        *(u16 *)(a + 0x34) = (*(u16 *)(a + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(a, 1, -1);
        s->state = 1;
        ReleaseVoice(a, s);
        base = g_level_base_pointer;
        *(u16 *)(a + 0x34) |= 0x1000;
        all = 1;
        for (i = 0; i < 6; i++) {
            u8 *e;
            if (s->ids[i] == -1)
                continue;
            e = base + (s->ids[i] << 8);
            if (e == 0)
                continue;
            if (e[0x20] == 0xFE)
                continue;
            if (e[0x20] == 0xFD)
                continue;
            all = 0;
            break;
        }
        if (all) {
            moby_mark_spawned(a);
            return;
        }
        break;
    }
    case 1:
        if (s->trigger != -1 && IsPointInCuboid(g_hero_position, s->trigger))
            leader_start_moving(a);
        break;
    case 2: {
        float damage = moby_get_anim_value(a);
        if (flag_set_first_pending(a)) {
            int i;
            a[0xBC] = 0;
            *(float *)(a + 0x48) = 1.0f;
            for (i = 0; i < 6; i++) {
                if (s->ids[i] != -1)
                    extermibot_shrink_piece_and_parts(g_moby_l18_table + (s->ids[i] << 8), (int)a);
            }
        } else if (a[0xBC] == 0) {
            leader_steer_pal(a, 1, 1);
            if (damage > 8.0f) {
                int i;
                a[0xBC] = 1;
                for (i = 0; i < 6; i++) {
                    if (s->ids[i] != -1 && s->groups[i] == s->group) {
                        extermibot_advance_piece_to_state(g_moby_l18_table + (s->ids[i] << 8));
                        s->ids[i] = -1;
                    }
                }
                s->group++;
                *(int *)(a + 0x48) = 0;
            }
        } else if (a[0xBC] == 1) {
            leader_steer_pal(a, 1, 1);
            if (*(u16 *)(a + 0x96) >= 26) {
                a[0xBC] = 2;
                *(float *)(a + 0x48) = 1.0f;
            }
        } else if (a[0xBC] == 2) {
            leader_steer_pal(a, 1, 1);
            if (damage > 59.0f) {
                *(int *)(a + 0x48) = 0;
                moby_set_state(a, a[0x94], -1);
            }
        }
        break;
    }
    case 3:
        if (flag_set_first_pending(a)) {
            s->waypoint = path_measure_moby_against_entry(a + 0x10, s->paths[s->group], 0.0f);
            break;
        } else {
            int id = s->paths[s->group];
            float speed = 5.0f;
            if (s->waypoint == g_path_l18_table[id][0] - 1)
                speed = 0.3f;
            if (!path_step_along_point(a, s->movement, id, &s->waypoint, 0, speed)) {
                if (s->group <= 0 && s->paths[1] != -1)
                    moby_set_state(a, 3, -1);
                else
                    moby_set_state(a, 4, -1);
                moby_set_state(a, 2, -1);
            }
        }
        leader_steer_pal(a, 1, 1);
        break;
    case 4:
        if (flag_set_first_pending(a)) {
            s->waypoint = path_measure_moby_against_entry(a + 0x10, s->escapePath, 0.0f);
            break;
        } else if (!path_step_along_point(a, s->movement, s->escapePath, &s->waypoint, 0, 2.0f)) {
            if (snd_is_voice_playing_for_owner(a, s->voice))
                ReleaseVoice(a, s);
            moby_mark_spawned(a);
            return;
        }
        leader_steer_pal(a, 1, 1);
        break;
    }
    if (*(u16 *)(a + 0x96) <= 0xFFFE)
        (*(u16 *)(a + 0x96))++;
}
