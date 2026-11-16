#include "include_asm.h"

#include "common.h"
extern int g_frame_l20_counter __attribute__((sda));
extern int trooper_spawn_parts_pal(char *, int);
extern void SpawnHealthThresholdEffects_pal(char *);
extern void trooper_count_closer_mates(char *);
extern float fast_subtract_rotations(float, float);
extern float math_approach_target_with_direction_mode(char *, char *, float, float, float, float, int);
extern f32 func_00303270(f32, f32);
extern f32 math_random_float_range(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 FastVecLength(void *);
extern f32 vec_distance_xy(void *, void *);
extern s32 path_check_entry_for_moby(char *, s32);
extern f32 vec_distance_xy(void *, void *);

/* Updates the trooper every frame: its body parts, its aim at the player, and its age counter. */
void trooper_update_body_pal(char *moby_arg) {
    char *moby = moby_arg;
    char *state;
    f32 turn_step;
    f32 turn_error;
    u32 unused;
    u16 age;

    state = *(char **)(moby + 0x68);
    trooper_spawn_parts_pal(moby, 0);
    SpawnHealthThresholdEffects_pal(moby);
    if ((g_frame_l20_counter & 7) == (((s32)moby >> 8) & 7)) {
        trooper_count_closer_mates(moby);
    }
    turn_step = 0.013962637f;
    turn_error = fast_subtract_rotations(*(f32 *)(state + 0x284), *(f32 *)(moby + 0xF8));
    {
        f32 turn_step_b = turn_step;
        math_approach_target_with_direction_mode(state + 0x288, state + 0x28C, turn_error, turn_step, turn_step_b, 0.69813186f, 0);
    }
    *(f32 *)(state + 0x284) = *(f32 *)(moby + 0xF8);
    age = *(u16 *)(moby + 0x96);
    if ((u32)age <= 0xFFFEu) {
        *(u16 *)(moby + 0x96) = age + 1;
    }
}


