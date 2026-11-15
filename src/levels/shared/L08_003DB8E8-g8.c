#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; TI128 q[0x260]; } Hero_003DB8E8;

extern u8 g_hero_state[];

/* the object last armed, the frame counter and the mode word */
extern u8 *D_L08_001B0488 __attribute__((sda));
extern s32 D_L08_001B2508;
extern s32 D_L08_001A8F00;

extern s32 mode_get_setting(void);
extern void counter_meter_draw(void);
extern s32 level_set_game_state_pair(s32, void *, s32);

/* Keeps a counter meter object (moby class 2547) next to the hero, showing a count that
   climbs or falls one step at a time. */
/* Follows the hero; every tenth frame steps the shown count towards the live count, and hands
   the meter its update routine while there is anything to show. */
void counter_meter_update(u8 *meter)
{
    s32 *vars = *(s32 **)(meter + 0x68);
    s32 liveCount;
    s32 shownCount;

    qcopy(meter + 0x10, &((Hero_003DB8E8 *)g_hero_state)->q[8]);
    liveCount = mode_get_setting();
    if (meter[0x20] == 0) {
        meter[0x20] = 1;
        vars[0] = liveCount;
        vars[1] = 0;
        meter[0x30] = 0xFF;
        D_L08_001B0488 = meter;
    }
    if (D_L08_001B2508 % 10 == 0) {
        shownCount = vars[0];
        if (shownCount < liveCount) {
            vars[1] = 0;
            vars[0] = shownCount + 1;
        } else if (liveCount < shownCount) {
            vars[0] = shownCount - 1;
        }
    }
    if (liveCount > 0 && D_L08_001A8F00 != 2 && (meter[0x20] == 1 || meter[0x20] == 2)) {
        meter[0x20] = 2;
        level_set_game_state_pair(0, counter_meter_draw, 2);
        return;
    }
    if ((liveCount <= 0 || D_L08_001A8F00 == 2) && meter[0x20] == 2) {
        level_set_game_state_pair(0, 0, 2);
        meter[0x20] = 1;
    }
}
