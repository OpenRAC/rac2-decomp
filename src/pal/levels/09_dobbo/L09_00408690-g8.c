#include "names.h"
/* func_PAL_L09_00408690, the PAL copy of func_L09_00403798: the same C, where D_L09_001B13C0 is read as
   a word and scaled to 50 Hz, the func_002A7470 blend times 5 and (in state 8 only) 20 scale, and the
   floats passed to func_002B60B0 and func_00282F20 change. */
#include "common.h"

/* Offsets from the sound-table anchor; the index stride is 0x70. */
typedef struct {
    u8 pad[0x74];
    u8 active;
    u8 pad2[0x13];
    char *owner;
} DobboSoundAnchor;

extern s32 g_dobbo_timer_value __attribute__((sda));
extern int g_dobbo_path_sound __attribute__((sda));
extern char g_str_dobbo_path_debug[], g_hero_position[], g_sound_state[];
extern struct {
    char pad[0x80];
    char position[0x10];
    char pad2[0x240C];
    char *target;
} D_00189E20;
extern int *g_path_l09_table[];

extern void dobbo_update_large_release_record(char *);
extern void dobbo_restore_saved_height(char *);
extern void dobbo_alert_path_enemies(char *);
extern void anim_start_blended(char *, int, int, int);
extern void moby_set_state(char *, int, int);
extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern void enemy_update_wander_heading(char *, char *, char *);
extern float IntToFloat(int);
/* The wrapper replaces the path index with its pointer and forwards the other
   arguments to func_002C9828, then returns a status. */
extern int table_run_entry_by_index(int, int, char *, char *, int, float);
extern int flag_set_first_pending(char *);
extern int PlayMobySound(int, int, char *);
extern int moby_turn_toward_target_and_step(char *, char *, float);
extern float vec_distance_xy(char *, char *);
extern int moby_dispatch_action_by_kind(char *, char *);
extern void STUB_printf(char *, ...);
extern void snd_stop_voice(int);
extern void FastVecSub(void *, void *, void *);
extern void vec_transform_and_set_height(char *, void *, void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void part_spawn_masked_debris(char *, int, void *, u8, float, float, float, float);
extern void SetDeathBits(char *, int, int);
extern void moby_mark_spawned(char *);
extern void dobbo_tick_timers_age_pal(char *);
extern void dobbo_update_height_separation_pal(char *);
extern void part_spawn_bone_sparks(char *);

/* Per-frame update of the Dobbo path enemy (moby class 3415): it waits, follows its path, walks up to the hero, and blows up when hit (PAL: 50 Hz timings). */
void dobbo_path_enemy_update_pal(char *obj)
{
    char *vars = *(char **)(obj + 0x68);
    int state, flags, index;
    int *path;
    float length;
    float away[4];

    dobbo_update_large_release_record(obj);
    dobbo_restore_saved_height(obj);
    state = (u8)obj[0x95];
    switch (state) {
    case 0:
        if (*(int *)(vars + 0x234) == 1 || *(s16 *)(vars + 0x26C)) {
            dobbo_alert_path_enemies(obj);
            if ((u8)obj[0x43] != 2)
                anim_start_blended(obj, 2, 0, 4);
            *(int *)(vars + 0x28C) = *(int *)(vars + 0x244);
            *(float *)(vars + 0x290) = 0;
            *(int *)(vars + 0x138) |= 4;
            moby_set_state(obj, 4, 1);
        }
        break;
    case 2:
        if (*(int *)(vars + 0x234) == 1 || *(s16 *)(vars + 0x26C)) {
            dobbo_alert_path_enemies(obj);
            *(u16 *)(vars + 0x26C) = ((s32)(g_dobbo_timer_value) * 5 + 2) / 6;
            if ((u8)obj[0x43] != state)
                anim_start_blended(obj, 2, 0, 4);
            moby_set_controller_speed_limits(obj, 0.0096f, 0.080000006f, 1.0053098f, 1.0053098f);
            *(int *)(vars + 0x13C) = *(int *)(vars + 0x254);
            *(int *)(vars + 0x28C) = *(int *)(vars + 0x244);
            moby_set_state(obj, 3, 3);
        }
        break;
    case 3:
        if (!*(int *)(vars + 0x234) && !*(s16 *)(vars + 0x26C)) {
            moby_set_controller_speed_limits(obj, 0.0096f, 0.080000006f, 1.0053098f, 1.0053098f);
            if (*(u8 *)(obj + 0x43) != 0)
                anim_start_blended(obj, 0, 0, 20);
            moby_set_state(obj, 2, 2);
        }
        break;
    }

    switch ((u8)obj[0x20]) {
    case 2:
        enemy_update_wander_heading(obj, vars + 0x1F0, vars + 0x100);
        break;
    case 3:
        if (obj[0x60] & 2)
            moby_set_state(obj, 5, -1);
        break;
    case 4:
        if (obj[0x60] & 2) {
            if (*(u8 *)(obj + 0x43) != 0)
                anim_start_blended(obj, 0, 0, 20);
        }
        path = g_path_l09_table[*(int *)(vars + 0x250)];
        length = IntToFloat(*path);
        *(float *)(vars + 0x290) += length / (*(float *)(vars + 0x25C) * 60.0f);
        if (length <= *(float *)(vars + 0x290)) {
            *(float *)(vars + 0x290) = length;
            moby_set_controller_speed_limits(obj, 0.0096f, 0.080000006f, 1.0053098f, 1.0053098f);
            *(int *)(vars + 0x138) &= ~4;
            moby_set_state(obj, 5, 3);
        }
        table_run_entry_by_index(*(int *)(vars + 0x250), 0, obj + 0x10, obj + 0xF0, 0,
                         *(float *)(vars + 0x290));
        break;
    case 5:
        if (obj[0x60] & 2) {
            if (*(u8 *)(obj + 0x43) != 0)
                anim_start_blended(obj, 0, 0, 20);
        }
        enemy_update_wander_heading(obj, vars + 0x1F0, vars + 0x100);
        if (*(s16 *)(vars + 0x26A)) {
            moby_set_controller_speed_limits(obj, 0.0096f, 0.080000006f, 1.0053098f, 1.0053098f);
            if ((u8)obj[0x43] != 2)
                anim_start_blended(obj, 2, 0, 4);
            moby_set_state(obj, 6, -1);
        }
        break;
    case 6:
        if ((obj[0x60] & 2) && (u8)obj[0x42] == 2) {
            if ((u8)obj[0x43] != 3)
                anim_start_blended(obj, 3, 0, 4);
            moby_set_state(obj, 7, -1);
        }
        break;
    case 7:
        if (flag_set_first_pending(obj)) {
            DobboSoundAnchor *entry = (DobboSoundAnchor *)(g_sound_state + *(s16 *)(vars + 0x274) * 0x70);
            if (entry->owner != obj || !entry->active)
                *(s16 *)(vars + 0x274) = PlayMobySound(g_dobbo_path_sound, 4, obj);
        }
        moby_turn_toward_target_and_step(obj, vars + 0x220, 0.0f);
        if (g_hero_state.target == obj || vec_distance_xy(obj + 0x10, g_hero_state.position) < 1.2f) {
            if ((u8)obj[0x43] != 4)
                anim_start_blended(obj, 4, 0, 4);
            moby_set_state(obj, 8, -1);
        }
        break;
    case 8:
        if ((obj[0x60] & 2) && (u8)obj[0x42] == 4) {
            if (*(u8 *)(obj + 0x43) != 0)
                anim_start_blended(obj, 0, 0, 17);
            moby_set_state(obj, 5, -1);
        }
        break;
    case 9:
        flags = moby_dispatch_action_by_kind(obj, vars + 0x50);
        if (flags & 1) {
            STUB_printf(g_str_dobbo_path_debug, *(s16 *)(vars + 0x274), *(s16 *)(obj + 0xB2));
            index = *(s16 *)(vars + 0x274);
            if (index != -1) {
                DobboSoundAnchor *entry = (DobboSoundAnchor *)(g_sound_state + index * 0x70);
                if (entry->owner == obj && entry->active)
                    snd_stop_voice(index);
            }
            *(s16 *)(vars + 0x274) = -1;
            FastVecSub(away, obj + 0x10, g_hero_position);
            vec_transform_and_set_height(obj, away, away, 0, 0.0f);
            vec_scale_to_length(away, away, 0.120000005f);
            part_spawn_masked_debris(obj, 0x3F, away, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
            PlayMobySound(0, 0, obj);
            SetDeathBits(obj, 0, 3);
            moby_mark_spawned(obj);
            return;
        } else if (flags & 2) {
            *(u16 *)(vars + 0x26C) = ((s32)(g_dobbo_timer_value) * 5 + 2) / 6;
            moby_set_state(obj, 5, 3);
            PlayMobySound(3, 0, obj);
        }
        break;
    }

    if ((u8)obj[0x20] != 7) {
        index = *(s16 *)(vars + 0x274);
        if (index != -1) {
            DobboSoundAnchor *entry = (DobboSoundAnchor *)(g_sound_state + index * 0x70);
            if (entry->owner == obj && entry->active)
                snd_stop_voice(index);
        }
        *(s16 *)(vars + 0x274) = -1;
    }
    dobbo_tick_timers_age_pal(obj);
    dobbo_update_height_separation_pal(obj);
    part_spawn_bone_sparks(obj);
}
