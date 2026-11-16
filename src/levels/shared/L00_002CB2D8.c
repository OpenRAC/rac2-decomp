#include "include_asm.h"
#include "names.h"
typedef struct {
    char pad0[0x1248];
    int f1248;
    char pad124C[0x22C8 - 0x124C];
    int f22C8;
    char pad22CC[0x24F8 - 0x22CC];
    short h24F8;
    short h24FA;
    char pad24FC[0x2538 - 0x24FC];
    int f2538;
} Hero_2CB2D8;

typedef struct {
    char pad0[0x174];
    unsigned short count;
    char pad176[2];
    unsigned int best;
    unsigned int mask;
} Stats_2CB2D8;

extern Hero_2CB2D8 g_hero_state;
extern Stats_2CB2D8 g_progress_statistics;
extern int g_current_item_slot __attribute__((section(".sdata")));
extern int g_menu_choice_table __attribute__((section(".sdata")));
extern unsigned int g_frame_counter __attribute__((section(".sdata")));
extern int g_current_map_index __attribute__((section(".sdata")));
extern int math_l00_return_argument_2(int);

/* Applies a pending hero change request: counts it in the statistics and switches the hero to the new value. */
void hero_apply_pending_change(void)
{
    int newValue;
    int altValue;

    if (g_hero_state.f2538 == 0)
        return;
    altValue = g_menu_choice_table;
    newValue = g_current_item_slot;
    if (g_hero_state.f1248 == 10)
        newValue = altValue;
    g_hero_state.f2538 = 0;
    if (newValue == 0)
        return;
    if (g_hero_state.f1248 == g_current_item_slot)
        return;
    if (g_progress_statistics.count <= 0xFFFE)
        g_progress_statistics.count++;
    if (g_frame_counter > g_progress_statistics.best)
        g_progress_statistics.best = g_frame_counter;
    g_progress_statistics.mask = g_progress_statistics.mask | (1 << g_current_map_index) | 0x80000000;
    g_hero_state.f22C8 = math_l00_return_argument_2(newValue);
    g_hero_state.h24F8 = 0;
    g_hero_state.h24FA = 0;
}
