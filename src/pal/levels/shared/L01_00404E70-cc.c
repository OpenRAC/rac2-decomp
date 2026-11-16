#include "names.h"
/* func_PAL_L01_00404E70, the PAL copy of func_L01_003FFFE8: the same C, where rename func_L00_002B9D60 becomes func_PAL_L00_002B9CD8; rename func_L00_00303530 becomes func_PAL_L00_00305110; rename func_002F5CC8 becomes func_PAL_002F6C18; rename func_002AF0A8 becomes func_PAL_002AFC10; rename func_L01_002BEB90 becomes func_PAL_L01_002BEC60. */
#include "common.h"

extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern int func_001163B0(void);

extern int g_current_map_index __attribute__((sda));

extern void moby_set_state(char *, int, int);

/* revives the round a moby belongs to and drops what it was carrying */
extern void STUB_printf(void *, int);
extern void moby_mark_spawned(void *);
extern int coll_point_inside_region(void *, int);
extern void FadeToBlack(int);
extern void hero_reset_position_and_direction_pal(void *, void *, int, int);
extern void load_scene_chunk_pal(int, int);
extern int req_push_queue(void *, int);
extern s32 req_launch_queued(void *);
extern void game_set_slowdown_factor_pal(void);
extern int game_is_either_mode_two(void);
extern void moby_mark_flag_and_append_to_list(int);
extern void snd_play_indexed_pal(int);
extern void moby_mark_table_entry_flagged(int);
extern void level_capture_checkpoint_state(void *, void *);
extern void hero_start_move_state_walk_or_run(int);
extern s32 SetHeroMoveState_pal(int, int);
extern void script_queue_keyed_request(int, int);
extern int MemcardSave(int, int);
extern unsigned char g_moby_group_flags[];
extern char g_hero_position[];

/* Level data, at another address in each level that has this function. The trigger flag is
   read at an offset from its owner: retail never moves it into a delay slot. */
extern int ref_L01_003FFFE8_00[] __attribute__((sda));
extern char ref_L01_003FFFE8_01[];
extern char ref_L01_003FFFE8_02[];
extern char ref_L01_003FFFE8_03[];
extern char ref_L01_003FFFE8_04[];
extern char *ref_L01_003FFFE8_05 __attribute__((sda));
extern char ref_L01_003FFFE8_06[];
extern int ref_L01_003FFFE8_07 __attribute__((sda));

/* a trigger moby: reports bad setup, waits to be activated, plays its effects and removes itself */
void activation_trigger_update_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    int active;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        if (*(int *)vars == -1)
            STUB_printf(ref_L01_003FFFE8_01, *(short *)(moby + 0xB2));
        if (*(short *)(vars + 4) == -1)
            STUB_printf(ref_L01_003FFFE8_02, *(short *)(moby + 0xB2));
        if (*(int *)(vars + 8) == -1)
            STUB_printf(ref_L01_003FFFE8_03, *(short *)(moby + 0xB2));
        if (*(unsigned char *)(moby + 0xB0) != 255) {
            if (g_moby_group_flags[*(unsigned char *)(moby + 0xB0) + (g_current_map_index << 4)] & 128) {
                moby_mark_spawned(moby);
                break;
            }
        } else
            STUB_printf(ref_L01_003FFFE8_04, *(short *)(moby + 0xB2));
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        active = 0;
        if (*(unsigned char *)(moby + 0xBC) ||
            (*(int *)vars != -1 && coll_point_inside_region(g_hero_position, *(int *)vars) &&
             (*(int *)(vars + 0x18) || *(int *)(g_hero_position + 0x2C0))))
            active = 1;
        if (active) {
            int ready;

            *(unsigned char *)(moby + 0x30) = 255;
            FadeToBlack(17);
            if (*(int *)(vars + 0xC) != -1) {
                char *spawn_entry = ref_L01_003FFFE8_05 + (*(int *)(vars + 0xC) << 7);

                hero_reset_position_and_direction_pal(spawn_entry + 0x30, spawn_entry + 0x70, 0xffffffff, 1);
            }
            if (*(int *)(vars + 8) != -1)
                load_scene_chunk_pal(*(int *)(vars + 8), 0);
            ready = 1;
            if (g_current_map_index == 8 && *(short *)(vars + 4) == 0) {
                if (req_push_queue(ref_L01_003FFFE8_06, 0x57)) {
                    req_push_queue(ref_L01_003FFFE8_06, 9);
                    req_push_queue(ref_L01_003FFFE8_06, 0x58);
                    req_launch_queued(ref_L01_003FFFE8_06);
                    game_set_slowdown_factor_pal();
                    ref_L01_003FFFE8_07 = 1;
                } else
                    ready = 0;
            }
            if (ready)
                moby_set_state(moby, 3, -1);
        }
        break;
    case 3:
        ref_L01_003FFFE8_00[1] = 1;
        if (!game_is_either_mode_two()) {
            ref_L01_003FFFE8_00[1] = 0;
            if (*(short *)(vars + 6) != -1) {
                moby_mark_flag_and_append_to_list(*(short *)(vars + 6));
                snd_play_indexed_pal(*(short *)(vars + 6));
            }
            moby_set_state(moby, 4, -1);
        }
        break;
    case 4:
        if (*(unsigned char *)(moby + 0xB0) != 255) {
            int group_index = *(unsigned char *)(moby + 0xB0);

            if (!(g_moby_group_flags[group_index + (g_current_map_index << 4)] & 128)) {
                moby_mark_table_entry_flagged(group_index);
                level_capture_checkpoint_state(moby + 0x10, moby + 0xF0);
            }
        }
        hero_start_move_state_walk_or_run(0);
        SetHeroMoveState_pal(0, 1);
        script_queue_keyed_request(*(int *)(vars + 0x14), *(int *)(vars + 0x10));
        MemcardSave(0, -1);
        moby_mark_spawned(moby);
        break;
    }
}

extern void moby_set_state(char *, int, int);

extern float math_fast_sin_or_cos_a(float);
extern float math_random_float_range(float, float);
extern int func_001163B0(void);
typedef struct {
    char data[0x18];
    char *target;
    char end[0x14];
} ParticleEffectSlot;
extern ParticleEffectSlot g_particle_l01_effect_slots[];
extern char g_hero_position[];

