#include "include_asm.h"
#include "names.h"

extern short g_item_menu_table[64][12];

/* Partial view of the resident global at D_001A7A00. Its fields are reached as
   symbol+offset with the section-only small-data model: the assembler expands
   each access to an absolute lui pair ($at for stores), and the compiler keeps
   them out of delay slots. */
typedef struct {
    unsigned char pad0[0x0A];
    unsigned char enabled; /* 0x0A */
    unsigned char pad0B[0x27];
    unsigned char limit; /* 0x32 */
    unsigned char count; /* 0x33 */
} Global001A7A00;
extern Global001A7A00 g_player_stats __attribute__((section(".sdata")));

extern int g_reward_slot_index;
extern unsigned short g_kill_event_counts[][2];
extern void level_forward_value(int);

/* Finds the row of D_00264630 whose first four ids hold the object's id at +0xAA,
   then counts it in column `type` of D_00188510 (capped at 9999). */
void moby_count_kill_or_event(char *moby, int type)
{
    int found = -1, i, j;
    int id = *(short *)(moby + 0xAA);

    for (i = 0; i < 64; i++) {
        for (j = 0; j < 4; j++) {
            if (id == g_item_menu_table[i][j]) {
                found = i;
                break;
            }
        }
        if (found != -1) goto found_it;
    }
    if (found == -1) return;
found_it:
    if (g_player_stats.enabled && g_reward_slot_index == -1 && g_player_stats.limit < 20) {
        g_player_stats.count++;
        if (g_player_stats.count * 2 >= g_player_stats.limit) {
            level_forward_value(180);
            g_player_stats.count = 0;
            g_player_stats.limit++;
        }
    }
    if (type == 0) {
        if (g_kill_event_counts[found][0] < 9999) g_kill_event_counts[found][0]++;
    } else if (type == 1) {
        if (g_kill_event_counts[found][1] < 9999) g_kill_event_counts[found][1]++;
    }
}

