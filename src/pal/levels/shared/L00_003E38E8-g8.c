#include "include_asm.h"

#include "common.h"
extern int g_spider_bot_moby __attribute__((sda));
extern void helper_set_active_flag(void);

/* Writes the object's state byte (7 when use_first_state is zero, 5 otherwise), lets the shared
 * updater run, then writes the caller's value (scaled by 5/6 for 50 Hz) in the object's slot - 8 when it is -1. */
void tracked_moby_set_state_pal(int use_first_state, int slot_value)
{
    char *tracked = (char *)g_spider_bot_moby;
    int value = slot_value;
    char *vars;

    if (tracked == 0)
        return;
    vars = *(char **)(tracked + 0x68);
    if (use_first_state != 0)
        tracked[0x20] = 5;
    else
        tracked[0x20] = 7;
    helper_set_active_flag();
    if (value != -1)
        *(int *)(vars + 0x20) = ((s32)(value) * 5 + 2) / 6;
    else
        *(int *)(vars + 0x20) = 8;
}
