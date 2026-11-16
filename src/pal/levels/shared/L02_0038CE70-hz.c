#include "names.h"
/* func_PAL_L02_0038CE70, the PAL copy of func_L02_00389F70: the same C with the callee is PAL's
   func_PAL_002B1588. */
#include "include_asm.h"

extern int g_destroyed_target_count __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern unsigned char g_one_shot_trigger_done __attribute__((nosda));
extern int g_one_shot_flag __attribute__((sda));

extern int snd_play_from_global_bank(int, int, void *);
extern void value_set_entry_by_index_pal(int, int);

struct TriggerState {
    unsigned char pad00[0x20];
    unsigned char initialized;
    unsigned char pad21[15];
    unsigned char state;
};

/* Fires the one-time reward once enough targets are destroyed on map 16. */
void one_shot_trigger_update_pal(struct TriggerState *self) {
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
    value_set_entry_by_index_pal(0x1233, -1);
    g_one_shot_flag = 1;
}
