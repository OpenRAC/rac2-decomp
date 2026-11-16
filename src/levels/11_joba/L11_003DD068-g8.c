#include "common.h"

/* Spawns class 0xA77, copies its position and initializes its travel vector. */
extern u8 *CreateMoby(s32 arg0);

extern void moby_init_child_from_parent(void *a0, void *a1);

extern void FastVecSub(f32 *dst, f32 *a, f32 *b);

extern f32 FastVecLength(f32 *a);

extern void vec_scale_to_length(f32 *dst, f32 *a, f32 len);

extern f32 weapon_compute_shot_launch_speed(char *a0, char *a1, s32 a2, f32 f12, f32 f13);

extern f32 g_bomb_velocity_scale __attribute__((sda));

extern f32 g_bomb_speed __attribute__((sda));

typedef int TI128 __attribute__((mode(TI)));

/* Creates a Hoverbike Race Bomb and sets its starting position and travel direction. */
u8 *hoverbike_bomb_spawn(u8 *owner, u8 *start_pos, u8 *target_pos, f32 gravity) {
    u8 *owner_or_vars = owner;
    u8 *start = start_pos;
    u8 *target = target_pos;
    f32 fall_rate = gravity;
    u8 *bomb = CreateMoby(MOBY_CLASS_HOVERBIKE_RACE_BOMB);

    if (bomb != 0) {
        u8 *v1;
        TI128 *dst;
        f32 travel_time;

        v1 = owner_or_vars;
        owner_or_vars = *(u8 **)(bomb + 0x68);
        moby_init_child_from_parent(bomb, v1);
        v1 = *(u8 **)(bomb + 0x24);
        dst = (TI128 *)(bomb + 0x10);

        *(f32 *)(bomb + 0x2C) = *(f32 *)(v1 + 0x24) * g_bomb_velocity_scale;
        *(u16 *)(bomb + 0x34) |= 0x5000;
        *dst = *(TI128 *)start;
        FastVecSub((f32 *)owner_or_vars, (f32 *)target, (f32 *)start);
        *(s32 *)(owner_or_vars + 0x8) = 0;
        travel_time = FastVecLength((f32 *)owner_or_vars) / g_bomb_speed;
        vec_scale_to_length((f32 *)owner_or_vars, (f32 *)owner_or_vars, travel_time);
        *(f32 *)(owner_or_vars + 0x8) = weapon_compute_shot_launch_speed((char *)start, (char *)target, 0, travel_time, -fall_rate);
        *(f32 *)(owner_or_vars + 0xC) = fall_rate;
    }
    return bomb;
}
