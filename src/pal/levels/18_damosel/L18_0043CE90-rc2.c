#include "include_asm.h"

#include "common.h"
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3;
extern f32 ref_L18_00437BA8_00(f32);
extern f32 ref_L18_00437BA8_01(f32);
extern f32 ref_L18_00437BA8_02(f32, f32);
extern f32 ref_L18_00437BA8_03(s32);
extern s32 ref_L18_00437BA8_04(s32);
extern s32 ref_L18_00437BA8_05(s32, s32);
extern f32 ref_L18_00437BA8_06(f32, f32);
extern void ref_L18_00437BA8_07(void *, Vec3 *, void *, s32, s32);
extern f32 ref_L18_00437BA8_08 __attribute__((sda));
extern f32 ref_L18_00437BA8_09 __attribute__((sda));
extern f32 ref_L18_00437BA8_10 __attribute__((sda));
extern f32 ref_L18_00437BA8_11 __attribute__((sda));
extern s32 ref_L18_00437BA8_12 __attribute__((sda));

/* Spawns count sparks around a point in a ring, each with a random speed and spin (PAL: 50 Hz speeds). */
void part_l18_spawn_ring_of_sparks_pal(void *pos, s32 count) {
    f32 speed;
    f32 angle_step;
    f32 angle;
    s32 sign;
    s32 remaining;
    s32 spin;
    Vec3 velocity;

    angle_step = 6.2831855f / ref_L18_00437BA8_03(count);
    angle = ref_L18_00437BA8_06(-3.1415927f, 3.1415927f);
    if (count > 0) {
        remaining = count;
        do {
            remaining -= 1;
            speed = ref_L18_00437BA8_06(ref_L18_00437BA8_08, ref_L18_00437BA8_09) * 0.020000001f;
            velocity.x = speed * ref_L18_00437BA8_00(angle);
            velocity.y = speed * ref_L18_00437BA8_01(angle);
            velocity.z = ref_L18_00437BA8_06(ref_L18_00437BA8_10, ref_L18_00437BA8_11) * 0.020000001f;
            sign = ref_L18_00437BA8_04(2);
            spin = ref_L18_00437BA8_05(-2, 2);
            ref_L18_00437BA8_07(pos, &velocity, &ref_L18_00437BA8_12, sign, spin);
            angle = ref_L18_00437BA8_02(angle, angle_step);
        } while (remaining != 0);
    }
}
