#include "names.h"
typedef int s32;

extern s32 D_L00_001A8FB4;
extern s32 D_L00_001A8FB8;
extern s32 D_L00_001A8FB0;
extern s32 ref_L00_003266D8_00 __attribute__((sda));
extern s32 ref_L00_003266D8_01 __attribute__((sda));
extern s32 D_L00_001B2088 __attribute__((sda));
extern s32 D_L00_001B2084 __attribute__((sda));
extern unsigned char D_L00_002F7530[];
extern unsigned char D_L00_002F7568[];
extern unsigned char D_L00_002F7588[];
extern s32 hud_set_slot_contents(s32, s32, void *, void *, void *, s32, s32);
extern s32 level_raise_record_peak(s32, s32);

/* Counts down the hit streak timers each frame and shows or hides the streak effect while the streak is active. */
void hero_update_hit_streak_effect(void) {
    if (D_L00_001A8FB4 == 0) {
        s32 count = D_L00_001A8FB8 + 1;

        ref_L00_003266D8_00 = count;
        if (count > 10)
            ref_L00_003266D8_00 = 10;
    } else {
        D_L00_001A8FB8 = 0;
    }
    if (D_L00_001A8FB0 != 0) {
        ref_L00_003266D8_01 = D_L00_001A8FB0 - 1;
        if (ref_L00_003266D8_01 == 0)
            D_L00_001A8FB4 = 0;
    }
    if (D_L00_001A8FB4 == 0 || D_L00_001B2088 == 0) {
        D_L00_001B2084 = -1;
    } else {
        if (D_L00_001B2084 == -1)
            D_L00_001B2084 = hud_set_slot_contents(12, 0, D_L00_002F7530, D_L00_002F7568,
                                           D_L00_002F7588, 0, 0);
        else
            level_raise_record_peak(D_L00_001B2084, 10);
    }
}
