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
extern s32 D_L02_001B35B8[] __attribute__((sda));
extern s32 moby_is_state_six(char *);
extern s32 moby_is_state_one_cleared_vars(char *);
extern s32 math_random_int_below(s32);
extern unsigned char D_001395B8[0x100];
extern int D_001A7A08[2];
extern int g_player_bolts;
extern int arena_get_challenge_save_index(int);
extern int arena_start_announcer_message(char *, int);
extern void help_unlock_entry(int);
extern void moby_handle_request_slot_state(int);
extern int moby_compute_scaled_entry_value_shifted(int);
extern int moby_compute_scaled_entry_value(int);
extern void module_l00_call_handler_with_arg_4(int);
extern void MemcardSave(int, int);

/* With a1 == 0 and no count yet for func_L02_003F9B70(0), plays the hero's scene 7 with its
   word at +0x22C8 kept; otherwise picks the scene from a1 (6, 0xB or a random one), adds the
   two scores and starts func_L00_0030C7F8(0x168). Then counts the entry. The unit is built with
   -frac2-gcse-unsplit-edges and -frac2-keep-block-order (config/cflags.txt): the high half of
   D_001395B8 is computed in the entry block, and the switch keeps its `b default` with the
   default body last, as in retail. `+= 1` keeps the counter's address out of the call. */
void func_US2_L02_003FE240(char *a0, int a1) {
    char *state = *(char **)(a0 + 0x68);
    int saved;
    char *hero;
    int v;

    if (a1 == 0 && D_001395B8[arena_get_challenge_save_index(0)] == 0) {
        hero = (char *)&g_hero_state;
        saved = *(int *)(hero + 0x22C8);
        arena_start_announcer_message(a0, 7);
        help_unlock_entry(0x26);
        moby_handle_request_slot_state(0x26);
        *(int *)(hero + 0x22C8) = saved;
    } else {
        switch (a1) {
        case 6:
            arena_start_announcer_message(a0, 8);
            break;
        case 0xB:
            arena_start_announcer_message(a0, 9);
            break;
        default:
            arena_start_announcer_message(a0, math_random_int_below(5) + 2);
            break;
        }
        D_001A7A08[1] = D_001A7A08[1] + moby_compute_scaled_entry_value_shifted(a1);
        v = moby_compute_scaled_entry_value(a1);
        *(int *)(state + 0x110) = v;
        g_player_bolts = g_player_bolts + v;
        module_l00_call_handler_with_arg_4(0x168);
    }
    D_001395B8[arena_get_challenge_save_index(a1)] += 1;
    MemcardSave(0, -1);
}
