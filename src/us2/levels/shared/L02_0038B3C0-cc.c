#include "names.h"
/* func_US2_L02_0038B3C0, the USA v2.00 copy of func_L02_00389F70: the same C, where rename func_002B0A18 becomes func_US2_002B1880. */

/* One-shot trigger: on the first update it marks the object initialised; once the level's
   counter reaches 14 while the current level (0x1A79F0) is 16, it sets the resident flag at
   0x1A7A6B, makes the two calls RAC2's other copies of this one-shot make, and sets 0x1A903C.
   Built with -mno-split-addresses: retail keeps the absolute loads and stores as assembler
   macros (stores through $at). The counter is small data, so the copy reorg places in the
   first branch's delay slot is gp-relative while the fall-through load stays absolute. */

extern int g_destroyed_target_count __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern unsigned char g_one_shot_trigger_done __attribute__((nosda));
extern int g_one_shot_flag __attribute__((sda));

extern int snd_play_from_global_bank(int, int, void *);
extern void value_set_entry_by_index_us2(int, int);

struct TriggerState {
    unsigned char pad00[0x20];
    unsigned char initialized;
    unsigned char pad21[15];
    unsigned char state;
};

void one_shot_trigger_update_us2(struct TriggerState *self) {
    if (self->initialized == 0) {
        self->state = 0xFF;
        self->initialized = 1;
    }
    if (g_destroyed_target_count < 14)
        return;
    if (g_current_map_index != 16)
        return;
    if (g_one_shot_trigger_done != 0)
        return;
    g_one_shot_trigger_done = 1;
    snd_play_from_global_bank(1, 0, 0);
    value_set_entry_by_index_us2(0x1233, -1);
    g_one_shot_flag = 1;
}
