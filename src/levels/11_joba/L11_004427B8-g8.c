#include "include_asm.h"
#include "names.h"

extern unsigned char g_game_flag_table[0x100];

extern int g_challenge_score_words[2];

extern int g_player_bolts;

extern unsigned char g_item_enabled_flags __attribute__((sda));

extern int g_scene_trigger_flag;

typedef struct {
    char pad0[0x22C8];
    int w22C8;
} L11_004427B8_Hero;

extern L11_004427B8_Hero g_hero_state;

extern int arena_get_challenge_flag_index(int);

extern int arena_queue_voice_line(char *, int);

extern void help_unlock_entry(int);

extern int moby_handle_request_slot_state(int);

extern int math_random_int_below(int);

extern int moby_compute_scaled_entry_value_shifted(int);

extern int moby_compute_scaled_entry_value(int);

extern void module_l00_call_handler_with_arg_4(int);

extern int snd_play_from_global_bank(int, unsigned int, void *);

extern void value_set_entry_by_index(int, int);

extern int MemcardSave(int, int);

/* Starts the next scene for a1 and counts the entry, as func_L02_003FCCA0 does in level 2. For
   a1 == 0 and a1 == 1 with no count yet it plays scene 1 or 3 and keeps the hero's word at
   +0x22C8; otherwise it takes scene func_002A77E0(2) + 0x1E, adds the two scores and starts
   func_L00_0030C7F8(0x168). For a1 == 10
   with the once-only byte clear it sets it, starts func_002E5E58 and raises D_001A903C. */
/* Starts the scene that follows a finished challenge and records that the challenge was done. */
void arena_start_challenge_result_scene(char *obj, int challengeIndex) {
    char *state = *(char **)(obj + 0x68);
    int saved;
    int score;

    if (challengeIndex == 0 && g_game_flag_table[arena_get_challenge_flag_index(0)] == 0) {
        saved = g_hero_state.w22C8;
        arena_queue_voice_line(obj, 1);
        help_unlock_entry(0x13);
        moby_handle_request_slot_state(0x13);
        g_hero_state.w22C8 = saved;
    } else if (challengeIndex == 1 && g_game_flag_table[arena_get_challenge_flag_index(1)] == 0) {
        saved = g_hero_state.w22C8;
        arena_queue_voice_line(obj, 3);
        help_unlock_entry(0x33);
        g_hero_state.w22C8 = saved;
    } else {
        arena_queue_voice_line(obj, math_random_int_below(2) + 0x1E);
        g_challenge_score_words[1] = g_challenge_score_words[1] + moby_compute_scaled_entry_value_shifted(challengeIndex);
        score = moby_compute_scaled_entry_value(challengeIndex);
        *(int *)(state + 0x1E0) = score;
        g_player_bolts = g_player_bolts + score;
        module_l00_call_handler_with_arg_4(0x168);
    }
    if (challengeIndex == 10 && g_item_enabled_flags == 0) {
        g_item_enabled_flags = 1;
        snd_play_from_global_bank(1, 0, 0);
        value_set_entry_by_index(0x1233, -1);
        g_scene_trigger_flag = 1;
    }
    g_game_flag_table[arena_get_challenge_flag_index(challengeIndex)] += 1;
    MemcardSave(0, -1);
}
