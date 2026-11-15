#include "names.h"
/* Per-frame counters of an object: bumps +0x96 up to 0x7FFD, counts the frames at +0x1BC
   of its record while +0x31 is clear, hands the record's +0x1B0 to func_00282978, steps
   its +0x1BE counter to 0x78 from stage 3, and from stage 2 sets the follow values. */
#include "include_asm.h"
#include "common.h"

extern int FastDecTimer(short *p);

/* Updates the object each frame: counts how long it has been alive and follows a base height. */
void hover_update_follow_counters(char *moby_in)
{
    char *moby = moby_in;
    char *vars = *(char **)(moby + 0x68);

    if (*(u16 *)(moby + 0x96) < 0x7FFD)
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
    if (*(u8 *)(moby + 0x31) == 0)
        *(u16 *)(vars + 0x1BC) = *(u16 *)(vars + 0x1BC) + 1;
    else
        *(u16 *)(vars + 0x1BC) = 0;
    FastDecTimer((short *)(vars + 0x1B0));
    if (*(u8 *)(moby + 0x20) >= 3) {
        if (*(s16 *)(vars + 0x1BE) < 0x78)
            *(u16 *)(vars + 0x1BE) = *(u16 *)(vars + 0x1BE) + 1;
    }
    if (*(u8 *)(moby + 0x20) >= 2) {
        *(f32 *)(moby + 0x70) = *(f32 *)(vars + 0x1C4) - *(f32 *)(moby + 0x18);
        *(f32 *)(moby + 0x74) = 2.0f;
        *(u8 *)(moby + 0x6F) = *(u8 *)(moby + 0x32);
        *(u8 *)(moby + 0xBD) = 0;
    }
}
