#include "common.h"
extern int FloatToInt(float);
extern void moby_set_state(void *, int, int);
extern float D_L03_001B1BC0 __attribute__((sda));
extern float D_L03_001B1BC4 __attribute__((sda));
extern float D_L03_001B1BC8 __attribute__((sda));
extern u8 D_L03_001B9980[];
extern void moby_mark_spawned(void *);
extern void anim_start_blended(void *, int, int, int);
extern void moby_update_ground_check(void *);
extern float fast_vec_dist(void *, void *);
extern int moby_apply_damage_to_object(void *, void *, int);
extern int weapon_select_aim_target(void *, int, int, int, float, float);
extern void rivet_bot_mark_stream(u8 *);

typedef struct { u8 pad[0x120]; f32 rate[3]; } RateView;

/* Sets up the path robot on its first frame and checks if it was hit. */
void rivet_bot_init_check_hit(u8 *self) {
    u8 *st = *(u8 **)(self + 0x68);

    if (self[0x20] == 0) {
        st[0x48] = FloatToInt(20.0f);
        st[0x4A] = FloatToInt(14.399999618530273f);
        st[0x60] = 7;
        *(f32 *)(st + 0x8C) = 0.4000000059604645f;
        *(s32 *)(st + 0x98) = 3;
        *(f32 *)(st + 0x80) = 0.5f;
        *(f32 *)(st + 0x84) = 0.5f;
        *(f32 *)(st + 0x90) = *(f32 *)(self + 0x18) - 2.0f;
        *(s32 *)(st + 0x138) |= 0x15;
        *(f32 *)(st + 0x134) = 0.05000000074505806f;
        *(f32 *)(st + 0x104) = 0.25f;
        *(f32 *)(st + 0x100) = 0.5f;
        *(f32 *)(st + 0x108) = 0.75f;
        *(f32 *)(st + 0x10C) = 0.75f;
        *(f32 *)(st + 0x110) = 0.7853982448577881f;
        *(f32 *)(st + 0x130) = 0.523598849773407f;
        st[0x28] = 3;
        *(s32 *)(st + 0x1D8) = -1;
        *(s32 *)(st + 0x350) = -1;
        if (*(s32 *)(st + 0x210) == -1) {
            moby_mark_spawned(self);
            return;
        }
        moby_set_state(self, 1, 0);
        if (self[0x43] != 0)
            anim_start_blended(self, 0, 0, 0);
    }
    if (self[0x31] != 0) {
        if (fast_vec_dist(self + 0x10, D_L03_001B9980) < 48.0f) {
            moby_update_ground_check(self);
            self[0x6F] = 0x2D;
        }
    }
    ((RateView *)st)->rate[2] = D_L03_001B1BC0 * 0.01666666753590107f;
    ((RateView *)st)->rate[0] = D_L03_001B1BC4 * 0.00027777778450399637f;
    ((RateView *)st)->rate[1] = D_L03_001B1BC8 * 0.00027777778450399637f;
    if (moby_apply_damage_to_object(self, st + 0x50, 0))
        rivet_bot_mark_stream(self);
    weapon_select_aim_target(self, *(s32 *)(st + 0x214), 0, 0, 16.0f, 0.0f);
}
