#include "include_asm.h"

#include "common.h"

/* func_PAL_L00_00423418, the PAL copy of func_L00_0041E168: the same C, where the particle life 60 becomes 50,
 * 1/60 becomes 0.02 and the last argument of both particle calls gains * 1.44f. */

extern char g_camera_l00_position[], g_camera_position[];
typedef struct { u8 pad0[4]; u8 flag; u8 pad5[224 - 5]; } Weapon_L00_0041E168;
typedef struct { u8 pad0[0x16]; u8 slot; } Save_L00_0041E168;
extern Weapon_L00_0041E168 g_weapon_l00_table[];
extern Save_L00_0041E168 g_item_slot_to_record;
extern int g_hero_locked_flag MACRO_ADDR;
extern float g_hit_l00_sparks_size_min __attribute__((sda)), g_hit_l00_sparks_size_max __attribute__((sda));
extern float g_hit_l00_sparks_speed_min __attribute__((sda)), g_hit_l00_sparks_speed_max __attribute__((sda));
extern float g_hit_l00_sparks_velocity_z_min __attribute__((sda)), g_hit_l00_sparks_velocity_z_max __attribute__((sda)), g_hit_l00_sparks_ground_param __attribute__((sda));
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern int FloatToInt(float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *part_spawn_ground_effect(void *, int, unsigned int, float, float, int, int, void *, int, float);

/* Sprays a burst of sparks out from a hit point, with a color that depends on the weapon type (PAL: 50 Hz timings). */
void part_l00_spawn_hit_sparks_pal(float *origin, int count, int mode)
{
    float velocity[4] __attribute__((aligned(16)));
    float previous[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float projection[4] __attribute__((aligned(16)));
    float size, rotation;
    int direction;
    unsigned int color;
    char *particle;

    FastVecSub(difference, g_camera_l00_position, origin);
    if (g_hero_locked_flag == 0) {
        difference[2] = 0.0f;
        axis[0] = 0.0f;
        axis[1] = 0.0f;
        axis[2] = 1.0f;
        axis[3] = 1.0f;
    } else {
        FastVecSub(projection, origin, g_camera_position);
        vec_scale_to_length(axis, projection, 1.0f);
        FastVecScale(projection, axis, FastVecDot(axis, difference));
        FastVecSub(difference, difference, projection);
    }
    if (count <= 0)
        return;
    do {
        size = math_random_float_range(g_hit_l00_sparks_size_min, g_hit_l00_sparks_size_max);
        direction = math_random_int_below(2);
        if (direction == 0)
            direction--;
        rotation = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, difference, axis, rotation);
        vec_scale_to_length(velocity, velocity, math_random_float_range(g_hit_l00_sparks_speed_min, g_hit_l00_sparks_speed_max) * 0.020000001f);
        velocity[2] = math_random_float_range(g_hit_l00_sparks_velocity_z_min, g_hit_l00_sparks_velocity_z_max) * 0.020000001f;
        qcopy(previous, origin);
        origin[0] += math_random_signed_float_range(0.0f, 0.15f);
        origin[1] += math_random_signed_float_range(0.0f, 0.15f);
        origin[2] += math_random_signed_float_range(0.0f, 0.15f);
        if (((Weapon_L00_0041E168 *)(g_item_slot_to_record.slot * sizeof(Weapon_L00_0041E168) + (unsigned int)g_weapon_l00_table))->flag)
            color = mode ? 0x802080 : 0x802020;
        else
            color = 0x202080;
        particle = part_spawn_ground_effect(origin, 50, color | 0x7F000000, size * 0.1f, size, 0, direction, velocity, 1, g_hit_l00_sparks_ground_param * 1.44f);
        if (particle)
            particle[9] = FloatToInt(4.0f) + 112;
        particle = part_spawn_ground_effect(origin, 50, 0x7F7F7F7F, size * 0.07f, size * 0.7f, 1, -direction, velocity, 1, g_hit_l00_sparks_ground_param * 1.44f);
        if (particle)
            particle[9] = FloatToInt(4.0f) + 112;
    } while (--count);
}
