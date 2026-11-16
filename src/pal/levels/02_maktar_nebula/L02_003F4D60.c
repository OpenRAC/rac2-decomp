#include "include_asm.h"


#include "common.h"
extern char g_camera_l02_position;
extern float fast_vec_dist();
extern void moby_update_ground_check();
extern int FloatToInt(float);
extern float FastAddRotations(float, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int FloatToInt(float);
extern float FastAddRotations(float, float);
extern void enemy_spawn_child_parts(void *, void *, int, int);
extern void enemy_attach_turn_child_parts_pal(float, void *, void *, int, void *);
extern void group_sync_counter(void *, void *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern int moby_apply_damage_to_object_pal(void *, void *, int);
extern void actor_tear_down_pal(char *);
extern void actor_update_loop_effect(char *);
extern char g_zero_l02_vector[] __attribute__((sda));
typedef struct {
    u8 pad0[0x18];
    char *p18;
    u8 pad1c[0xC];
    u8 b28;
    u8 pad29[5];
    u8 b2E;
    u8 pad2f[0x19];
    u8 b48;
    u8 pad49;
    u8 b4A;
    u8 pad4b[0x15];
    u8 x60[0x10];
    u8 b70;
    u8 pad71[0x1F];
    float f90;
    float f94;
    u8 pad98[4];
    float f9C;
    u8 pada0[8];
    int fA8;
    u8 padac[0x44];
    int fF0;
    float fF4;
    u8 padf8[0x18];
    float f110;
    float f114;
    float f118;
    float f11C;
    float f120;
    u8 pad124[0x18];
    float f13C;
    float f140;
    u8 pad144[0x370];
    float f4B4;
    u8 pad4b8[4];
    float f4BC;
    u8 x4C0[0xC];
    float f4CC;
    u8 pad4d0[0xC];
    u8 x4DC[0xE];
    short s4EA;
} St003F1298;
extern u8 g_actor_match_key;

/* Update with a lazy start: the first call (state byte +0x20 still 0) sets the actor up (a random
   sway angle of 15 to 40 degrees, either sign, two random bytes from 15 and 12, its speed and
   timing words), registers it and runs func_PAL_L02_003F5EB0; every call then fires func_002A93B0 when
   the player is within 24 units, turns the angle by the rate at +0x4CC, updates the effect,
   and for a visible actor of state 3 or more looks for the object of class 0xA03 / 0xB89 that
   it is attached to and releases it. */
void swaying_actor_update_pal(char *moby) {
    St003F1298 *state = *(St003F1298 **)(moby + 0x68);
    float sway_angle;

    if (*(u8 *)(moby + 0x20) == 0) {
        state->p18 = (char *)&state->f110;
        sway_angle = math_random_float_range(15.0f, 40.0f) * 0.017453294f;
        state->f4B4 = (math_random_int_below(2) != 0) ? -sway_angle : sway_angle;
        state->b48 = FloatToInt(15.0f);
        state->b4A = FloatToInt(12.0f);
        if (math_random_int_below(2) == 1)
            *(u16 *)(moby + 0x34) |= 0x8000;
        state->f4CC = 8.0f;
        state->f90 = 0.8f;
        state->b70 = 10;
        state->fA8 = 5;
        state->f94 = 0.8f;
        state->f9C = 0.4f;
        state->f118 = 0.4f;
        state->f110 = 0.6f;
        state->f114 = 0.2f;
        state->f11C = 0.4f;
        state->f4BC = 0.0f;
        state->f120 = 1.5707965f;
        state->f140 = 0.52359885f;
        state->f13C = 0.008f;
        state->b28 = 3;
        state->b2E = 1;
        enemy_spawn_child_parts(moby, state->x4C0, 0, 1);
        state->s4EA = 0;
        actor_tear_down_pal(moby);
    }
    if (*(u8 *)(moby + 0x31) != 0) {
        if (fast_vec_dist(moby + 0x10, &g_camera_l02_position) < 24.0f) {
            moby_update_ground_check(moby);
            *(u8 *)(moby + 0x6F) = 0x16;
        }
    }
    state->f4BC = FastAddRotations(state->f4BC, state->f4CC * 0.017453294f);
    enemy_attach_turn_child_parts_pal(state->f4BC, moby, state->x4C0, 1, g_zero_l02_vector);
    group_sync_counter(moby, state->x4DC);
    if (*(u8 *)(moby + 0x31) != 0 && *(u8 *)(moby + 0x20) >= 3) {
        char *hit_slot = part_find_owned_effect_slot(moby, 0x10000, 1);

        if (hit_slot != 0 && *(char **)(hit_slot + 0x20) != 0 && *(u8 *)(moby + 0x31) == 0 &&
            (*(short *)(*(char **)(hit_slot + 0x20) + 0xAA) == 0xA03 ||
             *(short *)(*(char **)(hit_slot + 0x20) + 0xAA) == 0xB89))
            *(int *)(hit_slot + 0x2C) = 0;
        if (moby_apply_damage_to_object_pal(moby, state->x60, 0) == 5) {
            state->fF0 = 0;
            state->fF4 = 1.0053098f;
        }
        if (*(u8 *)(moby + 0x20) >= 2 && state->b2E == 2)
            actor_tear_down_pal(moby);
        actor_update_loop_effect(moby);
    }
}

