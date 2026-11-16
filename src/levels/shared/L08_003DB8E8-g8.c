#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; TI128 q[0x260]; } Hero_003DB8E8;

extern u8 g_hero_state[];

/* the object last armed, the frame counter and the mode word */
extern u8 *g_counter_meter_current __attribute__((sda));
extern s32 g_frame_l08_counter;
extern s32 g_cutscene_l08_active_flag;

extern s32 mode_get_setting(void);
extern s32 counter_meter_draw(void);
extern s32 level_set_game_state_pair(s32, void *, s32);

/* Keeps a counter meter object (moby class 2547) next to the hero, showing a count that
   climbs or falls one step at a time. */
/* Follows the hero; every tenth frame steps the shown count towards the live count, and hands
   the meter its update routine while there is anything to show. */
void counter_meter_update(u8 *meter)
{
    s32 *vars = *(s32 **)(meter + 0x68);
    s32 live_count;
    s32 shown_count;

    qcopy(meter + 0x10, &((Hero_003DB8E8 *)g_hero_state)->q[8]);
    live_count = mode_get_setting();
    if (meter[0x20] == 0) {
        meter[0x20] = 1;
        vars[0] = live_count;
        vars[1] = 0;
        meter[0x30] = 0xFF;
        g_counter_meter_current = meter;
    }
    if (g_frame_l08_counter % 10 == 0) {
        shown_count = vars[0];
        if (shown_count < live_count) {
            vars[1] = 0;
            vars[0] = shown_count + 1;
        } else if (live_count < shown_count) {
            vars[0] = shown_count - 1;
        }
    }
    if (live_count > 0 && g_cutscene_l08_active_flag != 2 && (meter[0x20] == 1 || meter[0x20] == 2)) {
        meter[0x20] = 2;
        level_set_game_state_pair(0, counter_meter_draw, 2);
        return;
    }
    if ((live_count <= 0 || g_cutscene_l08_active_flag == 2) && meter[0x20] == 2) {
        level_set_game_state_pair(0, 0, 2);
        meter[0x20] = 1;
    }
}
