#include "common.h"

extern void moby_set_state(u8 *a0, u8 a1, s32 a2);

extern int snd_play_from_global_bank(int a0, unsigned int a1, void *a2);

extern void value_set_entry_by_index(int a0, int a1);

extern s32 D_L11_001B30C8;

extern s32 D_L11_001AED00 __attribute__((sda));

extern s32 D_L11_001AED04 __attribute__((sda));

extern s32 D_L11_001AED08 __attribute__((sda));

extern s32 D_L11_001A903C;

extern u8 D_001A7A72 NOT_SDA;

extern u8 D_001A7A74 NOT_SDA;

/* Watches a few level counters and, once they pass their limits, switches on two one-time
   flags. */
void level_update_progress_flags(u8 *moby) {
    u8 *self = moby;
    int state = self[0x20];
    int enabled;

    if (state != 1) {
        if (state < 2) {
            if (state == 0) {
                self[0x30] = 0xFF;
                D_L11_001AED08 = 0;
                moby_set_state(self, 1, -1);
            }
        }
        return;
    }
    enabled = D_L11_001AED00;
    if (D_L11_001B30C8 >= 6 && D_L11_001AED04 == 0 &&
        enabled != 0 && D_001A7A72 == 0) {
        D_001A7A72 = 1;
        snd_play_from_global_bank(1, 0, 0);
        value_set_entry_by_index(0x1233, -1);
        D_L11_001A903C = 1;
    }
    if (D_L11_001AED08 < 12)
        return;
    if (D_001A7A74 != 0)
        return;
    D_001A7A74 = 1;
    snd_play_from_global_bank(1, 0, 0);
    value_set_entry_by_index(0x1233, -1);
    D_L11_001A903C = 1;
}
