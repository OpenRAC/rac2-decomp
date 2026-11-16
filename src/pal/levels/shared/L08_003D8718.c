#include "include_asm.h"

#include "common.h"
extern void moby_mark_spawned(void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void *SpawnDirectedEffectObject_pal(void *, void *, void *, int);
extern float math_random_float_range(float, float);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_range(int, int);
extern u8 *part_spawn_velocity_particle(void *, void *, int, int, float);
typedef int TI128 __attribute__((mode(TI)));
extern u8 g_unlocked_item_flags[] __attribute__((sda));
extern u8 g_mystic_manipulator_data[] __attribute__((sda));
extern u8 g_player_stats[] __attribute__((sda));
extern u8 g_mystic_state[] __attribute__((sda));
extern u8 g_game_flag_table[];
extern u8 g_request_l08_queue[];

/* Updates an effect object (moby class 2465): when its target is hit it plays an animation, fires a bolt and throws a burst of sparks, and it removes itself when the target is gone. */
void hit_effect_update_pal(u8 *moby)
{
    float direction[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float random_dir[4] __attribute__((aligned(16)));
    u8 *target = *(u8 **)*(u32 *)(moby + 0x68);
    int i;
    if (!target || target[0x20] == 0xFE || target[0x20] == 0xFD) {
        moby_mark_spawned(moby);
        return;
    }
    if ((moby[0x60] & 2) && moby[0x43])
        anim_start_blended_pal(moby, 0, 0, 0);
    if (moby[0xBC]) {
        moby[0xBC] = 0;
        if (moby[0x43] != 1) anim_start_blended_pal(moby, 1, 0, 0);
        vec_build_spherical_offset(direction, 1.2f, *(float *)(moby+0xF8), -*(float *)(moby+0xF4));
        moby_transform_joint_to_world(moby, 0, position);
        SpawnDirectedEffectObject_pal(moby, position, direction, 0x4B);
        i = 4;
        do {
            *(TI128 *)random_dir = 0;
            random_dir[0] = math_random_float_range(-1.0f, 1.0f);
            random_dir[1] = math_random_float_range(-1.0f, 1.0f);
            random_dir[2] = math_random_float_range(-1.0f, 1.0f);
            *(TI128 *)velocity = *(TI128 *)random_dir;
            vec_scale_to_length(velocity, velocity, FastVecLength(direction)*0.5799999f);
            FastVecAdd(velocity, direction, velocity);
            vec_scale_to_length(velocity, velocity, math_random_float_range(0.060000002f, 0.120000005f));
            part_spawn_velocity_particle(position, velocity, 0x5F2F4F6F, math_random_int_range(4,8), 50000.0f);
        } while (--i >= 0);
        vec_scale_to_length(direction, direction, 0.010000001f);
        part_spawn_velocity_particle(position, direction, 0x2F4F7F7F, math_random_int_range(3,6), 500000.0f);
    }
}

