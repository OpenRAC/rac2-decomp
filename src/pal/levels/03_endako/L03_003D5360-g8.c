#include "include_asm.h"
#include "common.h"
extern f32  g_fan_rotation_rate __attribute__((sda));
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern s32  func_31BA30(s32 a0, s32 a1);
extern s32  func_31B9F0(s32 a0);
extern f32  func_2F0000(f32 a0, f32 a1);
extern f32  func_2EF670(f32 a0, f32 a1);
extern f32  func_2EF110(f32 *a0);
extern f32 g_fan_float_table[] __attribute__((sda));
extern f32 g_trail_projectile_scale __attribute__((sda));
typedef struct {
    f32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    f32 f10;
    f32 f14;
    u8  b18;
    u8  b19;
    u16 h1A;
    u16 pad1C;
    u8  b1E;
    u8  b1F;
    u8  pad20[0x10];
    u16 h30;
    u16 h32;
    s32 i34;
} L03_003D21F8_Obj;
extern L03_003D21F8_Obj *g_camera_override_slot __attribute__((sda));
extern u32 g_shared_record_pending;
extern void *cam_alloc_override_slot(s32 size);
extern s32  flag_is_third_pending_set(char *a0);
extern s32  PlayMobySound(s32 a0, s32 a1, char *a2);
extern u8  *g_moby_record_base;
extern u8   g_sound_state[];
extern s32  g_ant_bridge_divisor __attribute__((sda));
extern f32  g_ant_bridge_angle_limit __attribute__((sda));

/* case 0 spawns the object and points the actor at it; case 1 clears the
   object while the state word still reads zero, and clears the word otherwise */
void shared_record_reset_update_pal(char *a0)
{
    char *s0 = a0;

    switch (*(u8 *)(s0 + 0x20)) {
    case 0:
        g_camera_override_slot = cam_alloc_override_slot(4);
        moby_set_state(s0, 1, -1);
        *(u8 *)(s0 + 0x30) = 0xFF;
        break;
    case 1: {
        u32 v = g_shared_record_pending;

        if (v == 0) {
            g_camera_override_slot->f00 = -1.0f;
            g_camera_override_slot->f04 = -1.0f;
            g_camera_override_slot->f08 = -1.0f;
            g_camera_override_slot->f0C = -1.0f;
            g_camera_override_slot->f10 = -1.0f;
            g_camera_override_slot->f14 = -1.0f;
            g_camera_override_slot->b18 = 0;
            g_camera_override_slot->b19 = 0;
            g_camera_override_slot->h1A = 0;
            g_camera_override_slot->b1E = 0;
            g_camera_override_slot->b1F = 0;
            g_camera_override_slot->h30 = 0;
            g_camera_override_slot->i34 = 6;
            g_camera_override_slot->h32 = 100;
        } else {
            g_shared_record_pending = 0;
        }
        break;
    }
    }
}
