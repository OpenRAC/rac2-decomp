#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef signed int s32;
extern void moby_set_state(void *, s32, s32);
extern s32 D_L16_001B18F0 __attribute__((sda));
extern s32 D_L16_001B18E0 __attribute__((sda));
extern s32 D_L16_001B1704 __attribute__((sda));
extern char D_L16_00189E20[] __attribute__((nosda));
extern float D_L16_001B1708 __attribute__((sda));
extern float D_L16_00189EF8 __attribute__((nosda));
extern void anim_start_blended(void *, s32, s32, void *);
extern s32 FloatToInt(float);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern s32 FastDecTimer(void *);
extern s32 weapon_select_aim_target(void *, s32, float, float, s32, s32);
extern s32 math_random_int_range(s32, s32);

/* func_L16_00413EC8 is defined in L16_00403900.c (this unit has no $gp access for it). */

/* Two timed transitions of the same handle: the first drops the swung state once the
   measured clock passes the level's threshold, the second raises it below the other. */
void func_PAL_L16_00415CD0(u8 *arg0)
{
    u8 *s0;
    u8 *q;

    s0 = *(u8 **)(arg0 + 0x68);
    if (*(s32 *)(s0 + 0x26C) != 0) {
        if (*(float *)(s0 + 0x264) + D_L16_001B1708 > D_L16_00189EF8) {
            *(s32 *)(s0 + 0x26C) = 0;
            *(s32 *)(s0 + 0x270) = *(u8 *)(arg0 + 0x20);
            *(s32 *)(s0 + 0x274) = *(u8 *)(arg0 + 0x95);
            moby_set_state(arg0, 0x10, 4);
        }
    } else {
        q = D_L16_00189E20;
        if (*(s32 *)(q + 0x2294) != 0x81
            && *(float *)(s0 + 0x264) + D_L16_001B1708 < *(float *)(q + 0xD8)) {
            *(s32 *)(s0 + 0x268) = 0;
            *(s32 *)(s0 + 0x26C) = 1;
            if (*(u8 *)(arg0 + 0x43) != 0x16)
                anim_start_blended(arg0, 0x16, 0, 0x19);
            if (*(u8 *)(*(u8 **)(s0 + 0x1F0) + 0x43) == 0xA)
                anim_start_blended(*(u8 **)(s0 + 0x1F0), 0, 0, 0x19);
        }
    }
}
