#include "include_asm.h"
#include "names.h"

extern int g_player_bolts;
extern int g_bolt_counter_display;
extern int g_bolt_counter_target;
extern int g_bolt_counter_step;
extern int g_bolt_counter_last;
extern int g_bolt_counter_timer;
extern int g_bolt_counter_state[];
extern void func_0029CBA8(int value);

/* Initialize the pair of handles, then clear both sixteen-byte entries. */
/* Resets the bolt counter display to the player's bolt count and clears its two pop-up rows. */
void hud_reset_bolt_counter_display(void) {
    int boltCount = g_player_bolts;
    g_bolt_counter_display = boltCount;
    g_bolt_counter_target = boltCount;
    g_bolt_counter_step = 0;
    func_0029CBA8((int)&g_bolt_counter_display);
    g_bolt_counter_timer = 0;
    g_bolt_counter_last = -1;
    {
        int *row = g_bolt_counter_state;
        int i = 1;
        do {
            *(unsigned short *)((char *)row + 0xE) = 0;
            *row = 0;
            row += 4;
            i--;
        } while (i >= 0);
    }
}
