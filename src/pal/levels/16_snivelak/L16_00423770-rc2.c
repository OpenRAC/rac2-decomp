#include "include_asm.h"

#include "common.h"
extern s32 ref_L16_0041EBE8_00(s8 *);
extern void ref_L16_0041EBE8_01(s8 *, s32, s32);
extern f32 ref_L16_0041EBE8_02(f32);
extern void ref_L16_0041EBE8_03(s8 *, f32);
extern f32 ref_L16_0041EBE8_04 __attribute__((sda));
extern f32 ref_L16_0041EBE8_05 __attribute__((sda));
extern f32 ref_L16_0041EBE8_06 __attribute__((sda));
extern f32 ref_L16_0041EBE8_07 __attribute__((sda));
extern f32 ref_L16_0041EBE8_08;
extern f32 g_001B3AAC __attribute__((sda));

/* Swings an object to a set angle with a bounce, then stops once it has settled. */
void swing_to_angle_update_pal(s8 *moby) {
    f32 angle;
    f32 damped_velocity;
    f32 target_angle;
    f32 velocity;
    u8 state;

    state = *(u8 *)(moby + 0x20);
    switch (state) {
    case 0:
        if (ref_L16_0041EBE8_00(moby) != 0) {
            ref_L16_0041EBE8_04 = 0.0f;
            ref_L16_0041EBE8_08 = 0.0f;
            ref_L16_0041EBE8_01(moby, 1, -1);
        }
        break;
    case 1:
        velocity = ref_L16_0041EBE8_08 + (ref_L16_0041EBE8_06 * 6.981318e-06f);
        target_angle = ref_L16_0041EBE8_05 * 0.0174532942473888397216796875f;
        angle = ref_L16_0041EBE8_04 + velocity;
        ref_L16_0041EBE8_08 = velocity;
        ref_L16_0041EBE8_04 = angle;
        if (target_angle <= angle) {
            ref_L16_0041EBE8_04 = target_angle;
            damped_velocity = velocity * ref_L16_0041EBE8_07;
            g_001B3AAC = damped_velocity;
            if (ref_L16_0041EBE8_02(damped_velocity) < 0.0003490659f) {
                ref_L16_0041EBE8_01(moby, 2, -1);
            }
        }
        ref_L16_0041EBE8_03(moby, ref_L16_0041EBE8_04);
        break;
    }
}
