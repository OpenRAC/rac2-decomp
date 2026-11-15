/* Per-frame counters of an object: bumps +0x96 up to 0x7FFD, counts the frames at +0x1BC
   of its record while +0x31 is clear, hands the record's +0x1B0 to FastDecTimer, steps
   its +0x1BE counter to 0x78 from stage 3, and from stage 2 sets the follow values. */
#include "include_asm.h"
#include "common.h"

extern int func_00282978(short *p);

void func_L08_00425568(char *a0)
{
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);

    if (*(u16 *)(s0 + 0x96) < 0x7FFD)
        *(u16 *)(s0 + 0x96) = *(u16 *)(s0 + 0x96) + 1;
    if (*(u8 *)(s0 + 0x31) == 0)
        *(u16 *)(s1 + 0x1BC) = *(u16 *)(s1 + 0x1BC) + 1;
    else
        *(u16 *)(s1 + 0x1BC) = 0;
    FastDecTimer((short *)(s1 + 0x1B0));
    if (*(u8 *)(s0 + 0x20) >= 3) {
        if (*(s16 *)(s1 + 0x1BE) < 0x78)
            *(u16 *)(s1 + 0x1BE) = *(u16 *)(s1 + 0x1BE) + 1;
    }
    if (*(u8 *)(s0 + 0x20) >= 2) {
        *(f32 *)(s0 + 0x70) = *(f32 *)(s1 + 0x1C4) - *(f32 *)(s0 + 0x18);
        *(f32 *)(s0 + 0x74) = 2.0f;
        *(u8 *)(s0 + 0x6F) = *(u8 *)(s0 + 0x32);
        *(u8 *)(s0 + 0xBD) = 0;
    }
}
