#include "include_asm.h"
#include "common.h"

/* func_PAL_L14_0042BC18, the PAL copy of func_L14_004265B8: the same C, where the fade length 0x7D
   becomes 0x68 and both timers take the 50 Hz scale, the fade timer first. */
extern char *g_platform_projection_table __attribute__((sda));
extern unsigned char *g_moby_l14_pool __attribute__((sda));
typedef int PrisonQword __attribute__((mode(TI)));
typedef struct {
    char pad00[0x18];
    int exitTrigger;            /* 0x18 */
    int enterTrigger;           /* 0x1C */
    char pad20[0x10];
    int gateCamera;             /* 0x30 */
    int doorCamera;             /* 0x34 */
    int pad38;
    int lift;                   /* 0x3C: entity index */
    int panel;                  /* 0x40: entity index */
    int beam;                   /* 0x44: entity index */
    int guard;                  /* 0x48: entity index */
    int switchEntity;           /* 0x4C: entity index */
    int door;                   /* 0x50: entity index */
    int text54, text58, text5C; /* 0x54..0x5C */
    int zone60;                 /* 0x60 */
    int text64;                 /* 0x64 */
    float volume;               /* 0x68 */
    int fadeTimer;              /* 0x6C */
    int nextState;              /* 0x70 */
    int waitTimer;              /* 0x74 */
    int fadeLength;             /* 0x78 */
    int music7C, music80, music84, music88; /* 0x7C..0x88 */
    int frames;                 /* 0x8C */
} PrisonLiftState;

/* The 0x100-byte entity record, with only the fields this function uses. */
typedef struct {
    char pad00[0x24];
    char *info;                 /* 0x24 */
    char pad28[0xC];
    unsigned short flags;       /* 0x34 */
    char pad36[0x62];
    int target;                 /* 0x98 */
} PrisonLiftEntity;

extern int g_lift_l14_scene_flag;
extern char g_lift_module_handler_arg[];
extern u8 g_moby_group_flags[];
extern char g_hero_position[];
extern u8 g_hero_state[];
extern int g_current_map_index __attribute__((sda));
extern int g_player_stats __attribute__((sda));
extern int g_hero_mode_state __attribute__((sda));
extern int g_lift_scene_mode __attribute__((sda));
extern int g_lift_scene_count __attribute__((sda));
extern unsigned char g_item_owned_flags[] __attribute__((sda));
extern unsigned char g_help_unlocked_flags[] __attribute__((sda));
extern short g_current_music_id[];
extern int g_pad_held_flags;
extern u8 g_lift_scene_flag;

extern int IsPointInCuboid(void *, int);
extern void hero_reset_position_and_direction_pal(void *, void *, int, int);
extern void moby_activate_group_entities(void *);
extern void moby_set_flag_bit(void *, int);
extern int level_l00_call_module_handler_with_arg_10(int, int);
extern int flag_set_first_pending(void *);
extern void SetHeroMode_pal(int, int, void *);
extern void script_queue_keyed_request(int, int);
extern void part_update_slot_triggered_record_pal(void *);
extern int guard_is_defeated(void *);
extern void moby_mark_table_entry_flagged(int);
extern void level_capture_checkpoint_state(void *, void *);
extern void hero_reset_carried_objects(int); /* the parameter is unused */
extern int lift_is_moving(void *);
extern void lift_request_start(void *);
extern void moby_mark_spawned(void *);
extern void lift_set_moving_state(void *);
extern void moby_set_state(void *, int, int);
extern s32 hero_l00_set_move_state_pal(int, int);
extern int math_fast_float_d(void *);
extern float math_fast_sin_or_cos_b(float);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void snd_queue_level_jingle(char *);

/* Runs the prison lift scene (PAL): sets up the checkpoint by progress, moves the hero through the lift, panel and guard stages, then fades the music and plays the end scene. */
void lift_scene_update_pal(unsigned char *moby) {
    PrisonLiftState *state = *(PrisonLiftState **)(moby + 0x68);
    unsigned char *lift = g_moby_l14_pool + state->lift * 256;
    unsigned char *panel = g_moby_l14_pool + state->panel * 256;
    unsigned char *guard = g_moby_l14_pool + state->guard * 256;
    PrisonQword pos;

    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        state->fadeLength = 0x68;
        if (g_moby_group_flags[state->text5C + g_current_map_index * 16] & 0x80) {
            if (IsPointInCuboid(g_hero_position, state->enterTrigger)) {
                hero_reset_position_and_direction_pal(g_platform_projection_table + state->doorCamera * 128 + 0x30,
                                  g_platform_projection_table + state->doorCamera * 128 + 0x70, 0, 1);
                *(short *)(g_hero_position + 0x247C) = 0;
                g_item_owned_flags[2] = 1;
                g_help_unlocked_flags[2] = 1;
                g_item_owned_flags[3] = 1;
                g_help_unlocked_flags[3] = 1;
            }
            if (g_moby_group_flags[state->zone60 + g_current_map_index * 16] & 0x80) {
                moby_activate_group_entities(moby);
                moby_set_flag_bit(g_moby_l14_pool + state->door * 256, 1);
            }
            moby_set_state(moby, 7, -1);
        } else {
            *(short *)(g_hero_position + 0x247C) = 1;
            g_item_owned_flags[2] = 0;
            g_help_unlocked_flags[2] = 0;
            g_item_owned_flags[3] = 0;
            g_help_unlocked_flags[3] = 0;
            if (g_moby_group_flags[state->text58 + g_current_map_index * 16] & 0x80) {
                moby_activate_group_entities(moby);
                moby_set_state(moby, 5, -1);
            } else if (g_moby_group_flags[state->text64 + g_current_map_index * 16] & 0x80) {
                moby_activate_group_entities(moby);
                moby_set_state(moby, 4, -1);
            } else if (g_moby_group_flags[state->text54 + g_current_map_index * 16] & 0x80) {
                moby_set_state(moby, 3, -1);
            } else if (g_lift_l14_scene_flag != 0) {
                moby_set_state(moby, 1, -1);
            } else {
                moby_set_state(moby, 2, -1);
            }
        }
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, state->enterTrigger)) {
            level_l00_call_module_handler_with_arg_10((int)g_lift_module_handler_arg, 1);
            g_lift_scene_mode = 2;
            g_lift_scene_count = 8;
            if (g_pad_held_flags & 0x10)
                moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            unsigned char *liftNow = g_moby_l14_pool + state->lift * 256;
            hero_reset_position_and_direction_pal(liftNow + 0x10, liftNow + 0xF0, 0x6F, 1);
            SetHeroMode_pal(1, 0x3F, liftNow);
            if (g_current_music_id[0] != state->music7C)
                script_queue_keyed_request(state->music7C, state->music88);
        }
        part_update_slot_triggered_record_pal(moby);
        if (guard_is_defeated(guard)) {
            g_lift_scene_flag = 1;
            moby_mark_table_entry_flagged(state->text54);
            level_capture_checkpoint_state(moby + 0xF0, moby + 0xF0);
            state->nextState = 3;
            moby_set_state(moby, 6, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            hero_reset_carried_objects(0);
            hero_reset_position_and_direction_pal(moby + 0x10, moby + 0xF0, 0, 1);
            moby_activate_group_entities(moby);
            *(int *)(g_hero_state + 0x24CC) = g_player_stats;
            if (g_current_music_id[0] != state->music80)
                script_queue_keyed_request(state->music80, state->music88);
        }
        if (lift_is_moving(g_moby_l14_pool + state->panel * 256)) {
            moby_mark_table_entry_flagged(state->text64);
            level_capture_checkpoint_state(guard + 0x10, guard + 0xF0);
            state->nextState = 4;
            moby_set_state(moby, 6, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            PrisonLiftEntity *beam;
            lift_request_start(panel);
            if (guard != 0 && guard[0x20] != 0xFE && guard[0x20] != 0xFD)
                moby_mark_spawned(guard);
            beam = (PrisonLiftEntity *)(g_moby_l14_pool + state->beam * 256);
            beam->target = 0;
            beam->flags = (beam->flags | 0x41) & ~0x1000;
            hero_reset_position_and_direction_pal(guard + 0x10, guard + 0xF0, 0x6F, 1);
            SetHeroMode_pal(1, 0x3F, lift);
            if (g_current_music_id[0] != state->music7C)
                script_queue_keyed_request(state->music7C, state->music88);
        }
        part_update_slot_triggered_record_pal(moby);
        if (IsPointInCuboid(g_hero_position, state->exitTrigger)) {
            moby_mark_table_entry_flagged(state->text58);
            level_capture_checkpoint_state(&pos, panel + 0xF0);
            state->nextState = 5;
            moby_set_state(moby, 6, -1);
        }
        break;
    case 5:
        if (flag_set_first_pending(moby)) {
            PrisonLiftEntity *beam;
            moby_mark_spawned(lift);
            beam = (PrisonLiftEntity *)(g_moby_l14_pool + state->beam * 256);
            beam->flags = (beam->flags & ~0x41) | 0x1000;
            beam->target = *(int *)(beam->info + 0x10);
            qcopy(&pos, g_platform_projection_table + state->gateCamera * 128 + 0x30);
            if (g_hero_state[0x22B4] == 1)
                hero_reset_carried_objects(0);
            hero_reset_position_and_direction_pal(&pos, g_platform_projection_table + state->gateCamera * 128 + 0x70, 0, 1);
            lift_set_moving_state(panel);
            *(int *)(g_hero_state + 0x24CC) = g_player_stats;
            if (g_current_music_id[0] != state->music80)
                script_queue_keyed_request(state->music80, state->music88);
        }
        if (g_hero_mode_state != 2 && g_moby_l14_pool[state->switchEntity * 256 + 0x20] > 0x80) {
            moby_mark_table_entry_flagged(state->text5C);
            level_capture_checkpoint_state(g_platform_projection_table + state->doorCamera * 128 + 0x30,
                          g_platform_projection_table + state->doorCamera * 128 + 0x70);
            g_item_owned_flags[2] = 1;
            g_help_unlocked_flags[2] = 1;
            g_item_owned_flags[3] = 1;
            g_help_unlocked_flags[3] = 1;
            *(short *)(g_hero_position + 0x247C) = 0;
            moby_set_state(moby, 7, -1);
        }
        break;
    case 6:
        if (flag_set_first_pending(moby)) {
            state->fadeTimer = ((s32)(state->fadeLength) * 5 + 2) / 6 * 2;
            state->waitTimer = ((s32)(state->fadeLength) * 5 + 2) / 6;
            hero_l00_set_move_state_pal(0x6F, 1);
        }
        if (math_fast_float_d(&state->waitTimer))
            moby_set_state(moby, state->nextState, -1);
        break;
    case 7:
        if (flag_set_first_pending(moby))
            state->frames = 0;
        if (g_hero_mode_state != 2 && state->frames >= 6 && g_current_music_id[0] != state->music84)
            script_queue_keyed_request(state->music84, state->music88);
        state->frames++;
        break;
    default:
        break;
    }
    if (state->fadeTimer != 0) {
        math_fast_float_d(&state->fadeTimer);
        state->volume = math_fast_sin_or_cos_b((float)state->fadeTimer * 1.5707964f / (float)state->fadeLength);
        gfx_add_draw_callback_third((void (*)(void *))snd_queue_level_jingle, moby);
    }
}
