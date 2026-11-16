#include "common.h"
typedef float Vector[4];
extern void fuse_tick_explode(u8 *);
extern void moby_set_state(u8 *, u8, s32);
extern s32 flag_set_first_pending(u8 *);
extern void anim_start_blended(void *, int, int, int);
extern void swing_update_yaw(s8 *, f32);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern int PlayMobySound(int, int, char *);
extern u8 *spark_shot_spawn(void *, void *, void *, s32);
extern f32 g_turret_yaw_rate __attribute__((sda));
extern s32 g_turret_period __attribute__((sda));
extern Vector g_turret_l07_muzzle_offset __attribute__((sda));
extern f32 g_turret_l07_shot_speed __attribute__((sda));
extern s32 g_frame_l07_counter __attribute__((nosda));

/* Advances the dormant entity through initialization and its firing state. */
/* Updates the turret: sets itself up, plays its shot animation, then fires a projectile at regular intervals. */
void siberius_turret_update(u8 *moby)
{
    u8 *state;
    Vector position, velocity;
    if (moby[0x20] == 1) return;
    state = *(u8 **)(moby + 0x68);
    fuse_tick_explode(moby);
    switch (moby[0x20]) {
    case 0:
        *(f32 *)(state + 0x58) = *(f32 *)(moby + 0x18);
        *(f32 *)(state + 0x60) = *(f32 *)(moby + 0xF8);
        *(s32 *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(moby, 1, -1);
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
            *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
            if (moby[0x43]) anim_start_blended(moby, 0, 0, 1);
        }
        if (moby[0x60] & 2) {
            if (moby[0x43] != 1) anim_start_blended(moby, 1, 0, 1);
            moby_set_state(moby, 3, -1);
        }
        break;
    case 3: {
        s32 period, tick;
        swing_update_yaw((s8 *)moby, g_turret_yaw_rate * 0.0002908882452175f);
        period = g_turret_period;
        tick = g_frame_l07_counter;
        if (tick % period == 0) {
            matrix_mul_vec3(position, g_turret_l07_muzzle_offset, moby + 0xC0);
            FastVecAdd(position, position, moby + 0x10);
            vec_scale_to_length(velocity, moby + 0xC0, g_turret_l07_shot_speed * 0.0166666675359f);
            PlayMobySound(0, 0, (char *)moby);
            spark_shot_spawn(moby, position, velocity, state[0x34]);
        }
        break;
    }
    }
}
