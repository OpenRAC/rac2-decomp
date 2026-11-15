#include "include_asm.h"
#include "common.h"

extern s32 D_L08_001A9050 __attribute__((sda));
extern f32 D_L08_001A9054 __attribute__((sda));
extern f32 D_L08_001BE0B0 __attribute__((nosda));

extern void UpdateViewContext();

/* Starts a saved-state hold: remembers a global float and returns 1, or returns 0 if one is already active. */
s32 hero_begin_saved_float_hold(void) {
    if (D_L08_001A9050 != 0)
        return 0;
    D_L08_001A9050 = 1;
    D_L08_001A9054 = D_L08_001BE0B0;
    return 1;
}

/* Ends the saved-state hold: puts the remembered float back and returns 1, or returns 0 if none is active. */
s32 hero_end_saved_float_hold(void) {
    if (D_L08_001A9050 == 0)
        return 0;
    D_L08_001BE0B0 = D_L08_001A9054;
    UpdateViewContext();
    D_L08_001A9050 = 0;
    return 1;
}

/* The level's shared scalars: the aim values the camera reads, and the object
   the level keeps at a fixed place (its flag at +0x86, its target at +0x70). */
extern f32 D_L08_001B00E0 __attribute__((sda));
extern f32 D_L08_001B00E4 __attribute__((sda));
extern f32 D_L08_001B00E8 __attribute__((sda));
extern f32 D_L08_001B00F0 __attribute__((sda));
extern s32 D_L08_001B00F4 __attribute__((sda));
extern f32 D_L08_001B00F8 __attribute__((sda));
extern u8 *D_L08_001B9B50 __attribute__((nosda));

/* The boot's own vector, the one the aim is measured against. */
extern char g_hero_position[] __attribute__((nosda));

extern void follow_camera_set_distance(s32, f32, f32);
extern void follow_camera_set_height(f32, f32);
/* The prototype's order is the one the call site uses: the first float, then the
   flag, then the second float. The registers are the same either way (the int
   in $a0, the floats in $f12 and $f13). */
extern void cam_set_aim_offset_target(f32, s32, f32);
extern void cam_set_tuning_value(f32);
extern void cam_set_speeds_if_nonzero(f32, f32);
extern void cam_set_turn_speeds_if_nonzero(f32, f32);
extern void cam_set_snap_flag(void);
extern void cam_set_lock_flag(void);
extern s32 IsPointInCuboid(void *, s32);
extern f32 IntToFloat(s32);

/* Flags the level's object, feeds the camera its aim values and advances the
   counter the aim is scaled by. */
void cam_update_aim_values(s32 *counter, u8 *moby) {
    u8 *owner;
    f32 fade, scaleA, scaleB, scaleC;

    owner = *(u8 **)((u8 *)moby + 0x68);
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

    fade = IntToFloat(*counter) / IntToFloat(0x5A);
    if (fade > 1.0f)
        fade = 1.0f;

    scaleA = fade * 0.985f + 0.015f;
    scaleB = fade * 0.8f + 0.2f;
    scaleC = fade * 0.044999998062849045f + 0.015f;

    cam_set_speeds_if_nonzero(scaleA, scaleB);
    cam_set_turn_speeds_if_nonzero(scaleC, 0.2f);
    cam_set_snap_flag();

    if (*counter < 0x5A)
        *counter = *counter + 1;
}

extern f32 math_ease_out_quad(f32);

/* Resident data: a pair of floats at 0x189E20 + 0x1FB0, the aim values at
   0x138180 + 0x124, and the mode word at 0x1A79F0. */
extern char g_hero_state[];
extern char g_pad_state[];
extern s32 g_current_map_index;

/* Reads the player's aim and stick values and gives back six values clamped to the range -1 to 1. */
void hero_read_aim_input_values(f32 *outX, f32 *outY, f32 *outZ, f32 *outA, f32 *outB, f32 *outC) {
    char *playerData = (char *)g_hero_state;
    f32 value;
    {
        char *settings = (char *)g_pad_state;
        *outX = -*(f32 *)(playerData + 0x1FB0);
        *outZ = -*(f32 *)(playerData + 0x1FB4);
        *outY = math_ease_out_quad(*(f32 *)(settings + 0x128)) - math_ease_out_quad(*(f32 *)(settings + 0x124));
    }
    if (g_current_map_index == 8 || g_current_map_index == 0x1E || g_current_map_index == 0x15) {
        char *settings = (char *)g_pad_state;
        *outA = *(f32 *)(settings + 0x12C);
        *outC = 0;
    } else {
        char *settings = (char *)g_pad_state;
        *outC = *(f32 *)(settings + 0x12C);
        *outA = 0;
    }
    {
        char *settings = (char *)g_pad_state;
        *outB = math_ease_out_quad(*(f32 *)(settings + 0x138)) - math_ease_out_quad(*(f32 *)(settings + 0x13C));
    }

    value = *outX;
    if (value > 1.0f)
        *outX = 1.0f;
    else if (value < -1.0f)
        *outX = -1.0f;

    value = *outY;
    if (value > 1.0f)
        *outY = 1.0f;
    else if (value < -1.0f)
        *outY = -1.0f;

    value = *outB;
    if (value > 1.0f)
        *outB = 1.0f;
    else if (value < -1.0f)
        *outB = -1.0f;
}
