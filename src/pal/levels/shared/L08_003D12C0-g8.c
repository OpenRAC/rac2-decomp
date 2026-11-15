#include "include_asm.h"
#include "common.h"
extern s32 D_L08_001A9050 __attribute__((sda));
extern f32 D_L08_001A9054 __attribute__((sda));
extern f32 D_L08_001BE0B0 __attribute__((nosda));
extern f32 D_L08_001B00E0 __attribute__((sda));
extern f32 D_L08_001B00E4 __attribute__((sda));
extern f32 D_L08_001B00E8 __attribute__((sda));
extern f32 D_L08_001B00F0 __attribute__((sda));
extern s32 D_L08_001B00F4 __attribute__((sda));
extern f32 D_L08_001B00F8 __attribute__((sda));
extern u8 *D_L08_001B9B50 __attribute__((nosda));
extern char g_hero_position[] __attribute__((nosda));
extern void follow_camera_set_distance(s32, f32, f32);
extern void follow_camera_set_height(f32, f32);
extern void cam_set_aim_offset_target(f32, s32, f32);
extern void cam_set_tuning_value(f32);
extern void cam_set_speeds_if_nonzero(f32, f32);
extern void cam_set_turn_speeds_if_nonzero(f32, f32);
extern void cam_set_snap_flag(void);
extern void cam_set_lock_flag(void);
extern s32 IsPointInCuboid(void *, s32);
extern f32 IntToFloat(s32);
extern f32 math_ease_out_quad(f32);
extern s32 g_current_map_index;

/* Flags the level's object, feeds the camera its aim values and advances the
   counter the aim is scaled by. */
void func_PAL_L08_003D12C0(s32 *counter, u8 *arg) {
    u8 *owner;
    f32 t, a, b, c;

    owner = *(u8 **)((u8 *)arg + 0x68);
    if (*(s16 *)((u8 *)D_L08_001B9B50 + 0x86) == 0) {
        *(s32 *)((u8 *)*(u8 **)((u8 *)D_L08_001B9B50 + 0x70) + 0x250) = 2;
    }

    cam_set_aim_offset_target(D_L08_001B00F0, D_L08_001B00F4, D_L08_001B00F8);
    follow_camera_set_distance(0, D_L08_001B00E4, D_L08_001B00E0);

    if (*(s32 *)((u8 *)owner + 0xC8) >= 0 &&
        IsPointInCuboid(g_hero_position, *(s32 *)((u8 *)owner + 0xC8)) != 0) {
        cam_set_tuning_value(0.52359885f);
    }

    follow_camera_set_height(D_L08_001B00E8, 0.003f);
    cam_set_lock_flag();

    t = IntToFloat(*counter) / IntToFloat(0x4B);
    if (t > 1.0f)
        t = 1.0f;

    a = t * 0.985f + 0.015f;
    b = t * 0.8f + 0.2f;
    c = t * 0.044999998062849045f + 0.015f;

    cam_set_speeds_if_nonzero(a, b);
    cam_set_turn_speeds_if_nonzero(c, 0.2f);
    cam_set_snap_flag();

    if (*counter < 0x4B)
        *counter = *counter + 1;
}
