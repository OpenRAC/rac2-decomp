#include "include_asm.h"
#include "names.h"
typedef struct {
    char pad0[0x80];
    char pos[8];
    float f88;
    char pad1[0x2236];
    unsigned char b22C2;
    char pad2[0x22D];
    unsigned char b24F0;
} L02_003F5710_Hero;
extern L02_003F5710_Hero g_hero_state;
typedef int s32;
extern s32 g_group_max_index[] __attribute__((sda));
extern s32 moby_is_state_six(char *);
extern s32 moby_is_state_one_cleared_vars(char *);
extern s32 math_random_int_below(s32);
extern unsigned char g_game_flag_table[0x100];
extern int g_challenge_score_words[2];
extern int g_player_bolts;
extern int arena_get_challenge_save_index(int);
extern int arena_start_announcer_message(char *, int);
extern void help_unlock_entry(int);
extern int moby_handle_request_slot_state(int);
extern int moby_compute_scaled_entry_value_shifted(int);
extern int moby_compute_scaled_entry_value(int);
extern void module_l00_call_handler_with_arg_4(int);
extern int MemcardSave(int, int);

/* With challenge == 0 and no count yet for func_L02_003F9B70(0), plays the hero's scene 7 with its
   word at +0x22C8 kept; otherwise picks the scene from challenge (6, 0xB or a random one), adds the
   two scores and starts func_L00_0030C7F8(0x168). Then counts the entry. The unit is built with
   -frac2-gcse-unsplit-edges and -frac2-keep-block-order (config/cflags.txt): the high half of
   D_001395B8 is computed in the entry block, and the switch keeps its `b default` with the
   default body last, as in retail. `+= 1` keeps the counter's address out of the call. */
void scene_start_count_views_pal(char *moby, int challenge) {
    char *state = *(char **)(moby + 0x68);
    int saved;
    char *hero;
    int bolts;

    if (challenge == 0 && g_game_flag_table[arena_get_challenge_save_index(0)] == 0) {
        hero = (char *)&g_hero_state;
        saved = *(int *)(hero + 0x22C8);
        arena_start_announcer_message(moby, 7);
        help_unlock_entry(0x26);
        moby_handle_request_slot_state(0x26);
        *(int *)(hero + 0x22C8) = saved;
    } else {
        switch (challenge) {
        case 6:
            arena_start_announcer_message(moby, 8);
            break;
        case 0xB:
            arena_start_announcer_message(moby, 9);
            break;
        default:
            arena_start_announcer_message(moby, math_random_int_below(5) + 2);
            break;
        }
        g_challenge_score_words[1] = g_challenge_score_words[1] + moby_compute_scaled_entry_value_shifted(challenge);
        bolts = moby_compute_scaled_entry_value(challenge);
        *(int *)(state + 0x110) = bolts;
        g_player_bolts = g_player_bolts + bolts;
        module_l00_call_handler_with_arg_4(0x12C);
    }
    g_game_flag_table[arena_get_challenge_save_index(challenge)] += 1;
    MemcardSave(0, -1);
}
