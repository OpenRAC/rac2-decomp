#include "include_asm.h"

#include "common.h"
typedef struct { f32 x, y, z; } V3;
typedef struct { f32 x, y, z, w; } V4;
typedef struct { s8 b00[0x10]; V3 v10; s32 p1c; V4 v20; V4 v30; } Fr;
extern f32 ref_L11_0043A810_00 __attribute__((sda));
extern f32 ref_L11_0043A810_01 __attribute__((sda));
extern f32 ref_L11_0043A810_02 __attribute__((sda));
extern f32 ref_L11_0043A810_03 __attribute__((sda));
extern f32 ref_L11_0043A810_04 __attribute__((sda));
extern void ref_L11_0043A810_05(void *);
extern void ref_L11_0043A810_06(f32 *, s32, void *);
extern f32 ref_L11_0043A810_07(s32, void *);
extern f32 ref_L11_0043A810_08(f32, f32);
extern void ref_L11_0043A810_09(void *, void *, void *, f32);
extern f32 ref_L11_0043A810_10(f32, f32);
extern f32 ref_L11_0043A810_11(f32);
extern void ref_L11_0043A810_12(void *, s32, void *);
extern void ref_L11_0043A810_13(void *, void *);
extern void ref_L11_0043A810_14(s32, void *, f32);

/* Turns the drone's head to aim at the hero, with a small left-right sway while it fires. */
void drone_aim_head_at_hero_pal(void *moby) {
    Fr joint;
    s8 *vars;
    s8 *target;
    f32 horiz_dist;
    f32 pitch, heading, heading_diff, heading_clamped, sway_step, new_sway, sway_limit, sway;
    s16 sway_dir;

    vars = *(s8 **)((s8 *)moby + 0x68);
    ref_L11_0043A810_12(moby, 3, joint.b00);
    target = vars + 0x50;
    ref_L11_0043A810_06(&joint.v10.x, (s32)target, joint.b00);
    horiz_dist = ref_L11_0043A810_07((s32)target, joint.b00);
    ref_L11_0043A810_05(&joint.v20);
    pitch = ref_L11_0043A810_08(joint.v10.z, horiz_dist) + -1.5707964f + ref_L11_0043A810_04;
    joint.v20.y = pitch;
    if (ref_L11_0043A810_01 < pitch) {
        joint.v20.y = ref_L11_0043A810_01;
    } else if (pitch < ref_L11_0043A810_02) {
        joint.v20.y = ref_L11_0043A810_02;
    }
    ref_L11_0043A810_13(&joint.v30, &joint.v20);
    ref_L11_0043A810_14((s32)(vars + 0x270), &joint.v30, ref_L11_0043A810_03);
    ref_L11_0043A810_05(&joint.v20);
    heading = ref_L11_0043A810_08(joint.v10.x, joint.v10.y);
    joint.v20.z = heading;
    heading_diff = ref_L11_0043A810_10(heading, *(f32 *)(moby + 0xF8));
    joint.v20.z = heading_diff;
    heading_clamped = ref_L11_0043A810_11(heading_diff);
    joint.v20.z = heading_clamped;
    joint.v20.z = heading_clamped + *(f32 *)(vars + 0x2DC);
    sway_step = *(f32 *)(vars + 0x2E0) * 0.0003490659f;
    sway_dir = *(s16 *)(vars + 0x2EE);
    sway = *(f32 *)(vars + 0x2DC);
    if (sway_dir == 0) {
        new_sway = sway - sway_step;
    } else {
        new_sway = sway + sway_step;
    }
    sway_limit = ref_L11_0043A810_00;
    *(f32 *)(vars + 0x2DC) = new_sway;
    if ((sway_limit < new_sway) || (sway_limit = -sway_limit, (new_sway < sway_limit))) {
        *(f32 *)(vars + 0x2DC) = sway_limit;
        *(s16 *)(vars + 0x2EE) = (s16)((u16)*(s16 *)(vars + 0x2EE) ^ 1);
    }
    ref_L11_0043A810_13(&joint.v30, &joint.v20);
    ref_L11_0043A810_09(vars + 0x230, vars + 0x230, &joint.v30, 0.0625f);
}
