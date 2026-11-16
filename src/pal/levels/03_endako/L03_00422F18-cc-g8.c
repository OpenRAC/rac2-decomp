#include "names.h"
/* func_PAL_L03_00422F18, the PAL copy of func_L03_0041DAD0: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_002B0ED8 becomes func_PAL_002B1A50; rename func_L03_0041E240 becomes func_PAL_L03_00423688. */
#include "common.h"
extern int FloatToInt(float);
extern void moby_set_state(void *, int, int);
extern float g_rivet_bot_rate_c __attribute__((sda));
extern float g_rivet_bot_rate_a __attribute__((sda));
extern float g_rivet_bot_rate_b __attribute__((sda));
extern u8 g_camera_pose_buffer[];
extern void moby_mark_spawned(void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern void moby_update_ground_check(void *);
extern float fast_vec_dist(void *, void *);
extern int moby_apply_damage_to_object_pal(void *, void *, int);
extern int weapon_select_aim_target(void *, int, int, int, float, float);
extern void rivet_bot_mark_stream_pal(u8 *);

typedef struct { u8 pad[0x120]; f32 rate[3]; } RateView;

/* Rivet bot init and hit check: sets it up on its first frame, then marks the stream when it is hit (PAL). */
void rivet_bot_init_check_hit_pal(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);

    if (moby[0x20] == 0) {
        state[0x48] = FloatToInt(20.0f);
        state[0x4A] = FloatToInt(14.399999618530273f);
        state[0x60] = 7;
        *(f32 *)(state + 0x8C) = 0.4000000059604645f;
        *(s32 *)(state + 0x98) = 3;
        *(f32 *)(state + 0x80) = 0.5f;
        *(f32 *)(state + 0x84) = 0.5f;
        *(f32 *)(state + 0x90) = *(f32 *)(moby + 0x18) - 2.0f;
        *(s32 *)(state + 0x138) |= 0x15;
        *(f32 *)(state + 0x134) = 0.05000000074505806f;
        *(f32 *)(state + 0x104) = 0.25f;
        *(f32 *)(state + 0x100) = 0.5f;
        *(f32 *)(state + 0x108) = 0.75f;
        *(f32 *)(state + 0x10C) = 0.75f;
        *(f32 *)(state + 0x110) = 0.7853982448577881f;
        *(f32 *)(state + 0x130) = 0.523598849773407f;
        state[0x28] = 3;
        *(s32 *)(state + 0x1D8) = -1;
        *(s32 *)(state + 0x350) = -1;
        if (*(s32 *)(state + 0x210) == -1) {
            moby_mark_spawned(moby);
            return;
        }
        moby_set_state(moby, 1, 0);
        if (moby[0x43] != 0)
            anim_start_blended_pal(moby, 0, 0, 0);
    }
    if (moby[0x31] != 0) {
        if (fast_vec_dist(moby + 0x10, g_camera_pose_buffer) < 48.0f) {
            moby_update_ground_check(moby);
            moby[0x6F] = 0x2D;
        }
    }
    ((RateView *)state)->rate[2] = g_rivet_bot_rate_c * 0.020000001f;
    ((RateView *)state)->rate[0] = g_rivet_bot_rate_a * 0.00040000002f;
    ((RateView *)state)->rate[1] = g_rivet_bot_rate_b * 0.00040000002f;
    if (moby_apply_damage_to_object_pal(moby, state + 0x50, 0))
        rivet_bot_mark_stream_pal(moby);
    weapon_select_aim_target(moby, *(s32 *)(state + 0x214), 0, 0, 16.0f, 0.0f);
}
