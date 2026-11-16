#include "common.h"

typedef struct {
    u8 pad0[0x20];
    u8 state;
    u8 pad21[0xAA - 0x21];
    short oClass;
    u8 padAC[0x100 - 0xAC];
} GrelbinMoby;

extern int g_moby_array_cursor __attribute__((sda));
extern int g_moby_spawn_counter __attribute__((sda));
extern GrelbinMoby *g_moby_l19_array MACRO_ADDR;
extern GrelbinMoby *g_moby_array_limit MACRO_ADDR;
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern int g_warp_triggered_flags[] MACRO_ADDR;
extern int snd_play_from_global_bank(int, int, void *);
extern void value_set_entry_by_index_us2(int, int);

/* USA v2.00's own function, no v1.01 twin: walks the moby list 40 entries per call, counting live
   mobies of classes 0x11C7, 0x1266 and 0xF57. A full pass that finds none sets the flag at
   D_001A7A60[6] and runs the same award sequence as func_L19_00423548, then returns 1. */
int func_US2_L19_0042BBF8(void)
{
    int i;
    GrelbinMoby *moby;

    if (g_item_enabled_flags[6] == 0) {
        for (i = 0; i < 40; i++) {
            moby = g_moby_l19_array + g_moby_array_cursor;
            if (moby->oClass == 0x11C7 || moby->oClass == 0x1266 || moby->oClass == 0xF57) {
                if (moby != 0 && moby->state != 0xFE && moby->state != 0xFD)
                    g_moby_spawn_counter++;
            }
            g_moby_array_cursor++;
            if (g_moby_l19_array + g_moby_array_cursor >= g_moby_array_limit) {
                if (g_moby_spawn_counter == 0) {
                    if (g_item_enabled_flags[6] == 0) {
                        g_item_enabled_flags[6] = 1;
                        snd_play_from_global_bank(1, 0, 0);
                        value_set_entry_by_index_us2(0x1233, -1);
                        g_warp_triggered_flags[0] = 1;
                    }
                    return 1;
                }
                g_moby_array_cursor = 0;
                g_moby_spawn_counter = 0;
            }
        }
    }
    return 0;
}
