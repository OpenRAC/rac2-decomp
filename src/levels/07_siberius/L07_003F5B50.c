#include "common.h"
extern u8 *g_moby_l07_array[] __attribute__((sda));
typedef struct { u8 pad[0x34]; f32 y; u8 rest[0x80 - 0x38]; } Record5B50;
extern Record5B50 *D_L07_001B23CC[] __attribute__((sda));
typedef struct {
    u8 pad[0x80];
    f32 position[4];
    f32 rotation[4];
    u8 rest[0x33C - 0xA0];
    u8 *platform;
} Player5B50;
extern Player5B50 D_L07_00189E20;
extern u8 D_L07_001B9200[];
extern f32 D_L07_001B0F3C __attribute__((sda));
extern f32 D_L07_001B0F48 __attribute__((sda));
extern f32 math_fabs(f32);
extern f32 mat_fast_helper_a(f32, f32);
extern u8 *moby_get_private_value_2(void *);
extern s32 IsPointInCuboid(void *, s32);
extern void hero_reset_position_and_direction(void *, void *, s32, s32);
/* Nudges the object up or down in small steps to stay level with the lift beside it. It also turns the player to face it when the player stands on the lift. */
void lift_keep_height(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *lift = g_moby_l07_array[0] + (*(s32 *)(state + 0xE8) << 8);
    f32 heightDiff = *(f32 *)(moby + 0x14) - D_L07_001B23CC[0][*(s32 *)(state + 0xEC)].y;
    f32 step, savedYaw;
    f32 maxStep = 1.0f/6.0f;
    u8 *liftParent;
    if (*(f32 *)(lift + 0x18) < 218.5f) {
        step = heightDiff + 4.0f;
        if (math_fabs(step) < D_L07_001B0F3C) {
            if (step < 0.0f) step = -(step + D_L07_001B0F3C);
            else step = D_L07_001B0F3C - step;
            if (step > maxStep) step = 1.0f/6.0f;
            else if (step < -maxStep) step = -maxStep;
            *(f32 *)(moby + 0x14) += step;
            *(f32 *)(state + 0x54) = 0.0f;
            *(f32 *)(state + 0x64) += step;
        }
    }
    if (*(f32 *)(lift + 0x18) > 199.7f) {
        step = heightDiff - 4.0f;
        if (math_fabs(step) < D_L07_001B0F3C) {
            if (step < 0.0f) step = -(step + D_L07_001B0F3C);
            else step = D_L07_001B0F3C - step;
            if (step > maxStep) step = 1.0f/6.0f;
            else if (step < -maxStep) step = -maxStep;
            *(f32 *)(moby + 0x14) += step;
            *(f32 *)(state + 0x54) = 0.0f;
            *(f32 *)(state + 0x64) += step;
        }
    }
    if (*(f32 *)(lift + 0x18) > 202.0f && *(f32 *)(lift + 0x18) < 204.0f && D_L07_00189E20.platform == lift) {
        liftParent = moby_get_private_value_2(lift);
        if (liftParent != 0 && *(f32 *)(liftParent + 0x18) > 0.0f && !IsPointInCuboid(D_L07_001B9200, *(s32 *)(state + 0xEC))) {
            savedYaw = D_L07_00189E20.rotation[2];
            D_L07_00189E20.rotation[2] = mat_fast_helper_a(D_L07_00189E20.position[0] - *(f32 *)(lift + 0x10), D_L07_00189E20.position[1] - *(f32 *)(lift + 0x14));
            hero_reset_position_and_direction(D_L07_00189E20.position, D_L07_00189E20.rotation, 0x6F, 1);
            D_L07_00189E20.rotation[2] = savedYaw;
            hero_reset_position_and_direction(D_L07_00189E20.position, D_L07_00189E20.rotation, 0, 0);
        }
    }
    if (IsPointInCuboid(moby + 0x10, *(s32 *)(state + 0xEC))) {
        *(f32 *)(moby + 0x18) = *(f32 *)(lift + 0x18) + D_L07_001B0F48;
        *(f32 *)(state + 0x68) = *(f32 *)(moby + 0x18);
        *(f32 *)(state + 0x58) = 0.0f;
    }
}
