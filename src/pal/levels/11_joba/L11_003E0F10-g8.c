#include "names.h"
/* func_PAL_L11_003E0F10, the PAL copy of func_L11_003DD068: the same C, with the speed scaled to 50 Hz. */
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

/* Spawns a hoverbike bomb thrown from a start point to a target (PAL: speed scaled to 50 Hz). */
u8 *hoverbike_bomb_spawn_pal(u8 *parent, u8 *start, u8 *target, f32 gravity_arg) {
    u8 *vars = parent;
    u8 *start_ptr = start;
    u8 *target_ptr = target;
    f32 gravity = gravity_arg;
    u8 *bomb = CreateMoby(MOBY_CLASS_HOVERBIKE_RACE_BOMB);

    if (bomb != 0) {
        u8 *temp;
        TI128 *dst;
        f32 flight_time;

        temp = vars;
        vars = *(u8 **)(bomb + 0x68);
        moby_init_child_from_parent(bomb, temp);
        temp = *(u8 **)(bomb + 0x24);
        dst = (TI128 *)(bomb + 0x10);

        *(f32 *)(bomb + 0x2C) = *(f32 *)(temp + 0x24) * g_bomb_velocity_scale;
        *(u16 *)(bomb + 0x34) |= 0x5000;
        *dst = *(TI128 *)start_ptr;
        FastVecSub((f32 *)vars, (f32 *)target_ptr, (f32 *)start_ptr);
        *(s32 *)(vars + 0x8) = 0;
        flight_time = FastVecLength((f32 *)vars) / ((g_bomb_speed * 5.0f + 2.0f) * 0.16666667f);
        vec_scale_to_length((f32 *)vars, (f32 *)vars, flight_time);
        *(f32 *)(vars + 0x8) = weapon_compute_shot_launch_speed((char *)start_ptr, (char *)target_ptr, 0, flight_time, -gravity);
        *(f32 *)(vars + 0xC) = gravity;
    }
    return bomb;
}
