#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef signed int s32;
extern void moby_set_state(void *, s32, s32);
extern s32 g_snivelak_attach_rotation __attribute__((sda));
extern s32 g_snivelak_attach_offset __attribute__((sda));
extern s32 g_snivelak_voice_cue_count __attribute__((sda));
extern char g_hero_l16_moby[] __attribute__((nosda));
extern float g_snivelak_hover_height_offset __attribute__((sda));
extern float g_snivelak_hover_limit __attribute__((nosda));
extern void anim_start_blended(void *, s32, s32, void *);
extern s32 FloatToInt(float);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern s32 FastDecTimer(void *);
extern s32 weapon_select_aim_target(void *, s32, float, float, s32, s32);
extern s32 math_random_int_range(s32, s32);

/* func_L16_00413EC8 is defined in L16_00403900.c (this unit has no $gp access for it). */

/* Two timed transitions of the same handle: the first drops the swung state once the
   measured clock passes the level's threshold, the second raises it below the other. */
void snivelak_switch_fly_hover_state_pal(u8 *arg0)
{
    u8 *s0;
    u8 *q;

    s0 = *(u8 **)(arg0 + 0x68);
    if (*(s32 *)(s0 + 0x26C) != 0) {
        if (*(float *)(s0 + 0x264) + g_snivelak_hover_height_offset > g_snivelak_hover_limit) {
            *(s32 *)(s0 + 0x26C) = 0;
            *(s32 *)(s0 + 0x270) = *(u8 *)(arg0 + 0x20);
            *(s32 *)(s0 + 0x274) = *(u8 *)(arg0 + 0x95);
            moby_set_state(arg0, 0x10, 4);
        }
    } else {
        q = g_hero_l16_moby;
        if (*(s32 *)(q + 0x2294) != 0x81
            && *(float *)(s0 + 0x264) + g_snivelak_hover_height_offset < *(float *)(q + 0xD8)) {
            *(s32 *)(s0 + 0x268) = 0;
            *(s32 *)(s0 + 0x26C) = 1;
            if (*(u8 *)(arg0 + 0x43) != 0x16)
                anim_start_blended(arg0, 0x16, 0, 0x19);
            if (*(u8 *)(*(u8 **)(s0 + 0x1F0) + 0x43) == 0xA)
                anim_start_blended(*(u8 **)(s0 + 0x1F0), 0, 0, 0x19);
        }
    }
}
