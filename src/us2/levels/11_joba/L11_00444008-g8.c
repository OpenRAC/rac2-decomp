#include "include_asm.h"
#include "names.h"

extern unsigned char D_001395B8[0x100];
extern int D_001A7A08[2];
extern int g_player_bolts;
extern unsigned char D_001A7A60 __attribute__((sda));
extern int D_001A903C;
typedef struct {
    char pad0[0x22C8];
    int w22C8;
} L11_004427B8_Hero;
extern L11_004427B8_Hero g_hero_state;
extern int arena_get_challenge_flag_index(int);
extern int arena_queue_voice_line(char *, int);
extern void help_unlock_entry(int);
extern void moby_handle_request_slot_state(int);
extern int math_random_int_below(int);
extern int moby_compute_scaled_entry_value_shifted(int);
extern int moby_compute_scaled_entry_value(int);
extern void func_US2_L00_0030D9F8(int);
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern void func_US2_002B1880(int, int);
extern void MemcardSave(int, int);

/* Starts the next scene for a1 and counts the entry, as func_L02_003FCCA0 does in level 2. For
   a1 == 0 and a1 == 1 with no count yet it plays scene 1 or 3 and keeps the hero's word at
   +0x22C8; otherwise it takes scene func_002A77E0(2) + 0x1E, adds the two scores and starts
   func_US2_L00_0030D9F8(0x168). For a1 == 10
   with the once-only byte clear it sets it, starts func_002E5E58 and raises D_001A903C. */
void func_US2_L11_00444008(char *a0, int a1) {
    char *state = *(char **)(a0 + 0x68);
    int saved;
    int v;

    if (a1 == 0 && D_001395B8[arena_get_challenge_flag_index(0)] == 0) {
        saved = g_hero_state.w22C8;
        arena_queue_voice_line(a0, 1);
        help_unlock_entry(0x13);
        moby_handle_request_slot_state(0x13);
        g_hero_state.w22C8 = saved;
    } else if (a1 == 1 && D_001395B8[arena_get_challenge_flag_index(1)] == 0) {
        saved = g_hero_state.w22C8;
        arena_queue_voice_line(a0, 3);
        help_unlock_entry(0x33);
        g_hero_state.w22C8 = saved;
    } else {
        arena_queue_voice_line(a0, math_random_int_below(2) + 0x1E);
        D_001A7A08[1] = D_001A7A08[1] + moby_compute_scaled_entry_value_shifted(a1);
        v = moby_compute_scaled_entry_value(a1);
        *(int *)(state + 0x1E0) = v;
        g_player_bolts = g_player_bolts + v;
        func_US2_L00_0030D9F8(0x168);
    }
    if (a1 == 10 && D_001A7A60 == 0) {
        D_001A7A60 = 1;
        snd_play_from_global_bank(1, 0, 0);
        func_US2_002B1880(0x1233, -1);
        D_001A903C = 1;
    }
    D_001395B8[arena_get_challenge_flag_index(a1)] += 1;
    MemcardSave(0, -1);
}
