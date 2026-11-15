#include "common.h"

extern void moby_mark_spawned(void *);
extern int snd_is_voice_playing_for_owner(u8 *, int);
extern int PlayMobySound(int, int, u8 *);
extern void snd_stop_voice(int);
extern u8 g_sound_state[];
extern int part_find_owned_effect_slot(u8 *, int, int);
extern float moby_update_aim_target_strength(u8 *, int);
extern void part_spawn_damage_debris(void *, void *, void *);
extern char *SpawnExplosion(void *, int, int, int, float, float, int, int, int, int, int, int, int, void *);
extern u8 *g_moby_l18_table;
extern void extermibot_destroy_piece_and_parts(u8 *);
extern void extermibot_shrink_piece_and_parts(u8 *, int);
extern void extermibot_advance_piece_to_state(u8 *);
extern void leader_start_moving(u8 *);
extern void leader_steer(u8 *, int, int);
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
extern int *D_L18_001FE480[];
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

static inline void ReleaseVoice(u8 *moby, LeaderState *vars) {
    int slot = vars->voice;
    if (slot != -1) {
        u8 *record = g_sound_state + slot * 0x70;
        if (*(u8 **)(record + 0x88) == moby && record[0x74])
            snd_stop_voice(slot);
    }
    vars->voice = -1;
}

/* Updates the leader boss: it takes damage, follows its paths, drops pieces in
   stages, and explodes when its health runs out. */
void leader_update(u8 *moby) {
    LeaderState *vars = *(LeaderState **)(moby + 0x68);
    float hit;
    float vec[4];

    if (moby[0x20] >= 2) {
        if (!snd_is_voice_playing_for_owner(moby, vars->voice))
            vars->voice = PlayMobySound(0, 4, moby);
    } else if (snd_is_voice_playing_for_owner(moby, vars->voice)) {
        ReleaseVoice(moby, vars);
    }
    hit = moby_update_aim_target_strength(moby, part_find_owned_effect_slot(moby, 0x10000, 0));
    if (moby[0x20] >= 2) {
        vars->health -= hit;
        part_spawn_damage_debris(moby, vars->hit, &vars->health);
        if (vars->health <= 0.0f || vars->state == 2) {
            int i;
            SpawnExplosion(moby + 0x10, 1, 0x19, 20, 1.0f, 20.0f, 20, 20, 45, 1, 1, 1, 0, 0);
            for (i = 0; i < 6; i++) {
                if (vars->ids[i] != -1)
                    extermibot_destroy_piece_and_parts(g_moby_l18_table + (vars->ids[i] << 8));
            }
            if (snd_is_voice_playing_for_owner(moby, vars->voice))
                ReleaseVoice(moby, vars);
            vec_random_direction(vec, 0.10000000894069672f, 0.25f);
            FastVecAdd(vec, vec, vars->velocity);
            part_spawn_masked_debris(moby, 63, vec, 255, 3.0f, 6.0f, 3.0f, 6.0f);
            moby_mark_spawned(moby);
            return;
        }
    }
    switch (moby[0x20]) {
    case 0: {
        int i;
        int all;
        u8 *base;
        anim_start_blended(moby, 1, 0, 0);
        *(int *)(moby + 0x48) = 0;
        *(int *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(moby, 1, -1);
        vars->state = 1;
        ReleaseVoice(moby, vars);
        base = g_moby_l18_table;
        *(u16 *)(moby + 0x34) |= 0x1000;
        all = 1;
        for (i = 0; i < 6; i++) {
            u8 *e;
            if (vars->ids[i] == -1)
                continue;
            e = base + (vars->ids[i] << 8);
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
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
    case 1:
        if (vars->trigger != -1 && IsPointInCuboid(g_hero_position, vars->trigger))
            leader_start_moving(moby);
        break;
    case 2: {
        float damage = moby_get_anim_value(moby);
        if (flag_set_first_pending(moby)) {
            int i;
            moby[0xBC] = 0;
            *(float *)(moby + 0x48) = 1.0f;
            for (i = 0; i < 6; i++) {
                if (vars->ids[i] != -1)
                    extermibot_shrink_piece_and_parts(g_moby_l18_table + (vars->ids[i] << 8), (int)moby);
            }
        } else if (moby[0xBC] == 0) {
            leader_steer(moby, 1, 1);
            if (damage > 8.0f) {
                int i;
                moby[0xBC] = 1;
                for (i = 0; i < 6; i++) {
                    if (vars->ids[i] != -1 && vars->groups[i] == vars->group) {
                        extermibot_advance_piece_to_state(g_moby_l18_table + (vars->ids[i] << 8));
                        vars->ids[i] = -1;
                    }
                }
                vars->group++;
                *(int *)(moby + 0x48) = 0;
            }
        } else if (moby[0xBC] == 1) {
            leader_steer(moby, 1, 1);
            if (*(u16 *)(moby + 0x96) >= 31) {
                moby[0xBC] = 2;
                *(float *)(moby + 0x48) = 1.0f;
            }
        } else if (moby[0xBC] == 2) {
            leader_steer(moby, 1, 1);
            if (damage > 59.0f) {
                *(int *)(moby + 0x48) = 0;
                moby_set_state(moby, moby[0x94], -1);
            }
        }
        break;
    }
    case 3:
        if (flag_set_first_pending(moby)) {
            vars->waypoint = path_measure_moby_against_entry(moby + 0x10, vars->paths[vars->group], 0.0f);
            break;
        } else {
            int id = vars->paths[vars->group];
            float speed = 5.0f;
            if (vars->waypoint == D_L18_001FE480[id][0] - 1)
                speed = 0.3f;
            if (!path_step_along_point(moby, vars->movement, id, &vars->waypoint, 0, speed)) {
                if (vars->group <= 0 && vars->paths[1] != -1)
                    moby_set_state(moby, 3, -1);
                else
                    moby_set_state(moby, 4, -1);
                moby_set_state(moby, 2, -1);
            }
        }
        leader_steer(moby, 1, 1);
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            vars->waypoint = path_measure_moby_against_entry(moby + 0x10, vars->escapePath, 0.0f);
            break;
        } else if (!path_step_along_point(moby, vars->movement, vars->escapePath, &vars->waypoint, 0, 2.0f)) {
            if (snd_is_voice_playing_for_owner(moby, vars->voice))
                ReleaseVoice(moby, vars);
            moby_mark_spawned(moby);
            return;
        }
        leader_steer(moby, 1, 1);
        break;
    }
    if (*(u16 *)(moby + 0x96) <= 0xFFFE)
        (*(u16 *)(moby + 0x96))++;
}
