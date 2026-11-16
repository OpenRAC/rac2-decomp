#include "common.h"






extern float g_hero_l11_position[];

extern float math_random_float_range(float, float);

extern void moby_transform_joint_to_world(void *, int, void *);

extern void FastVecSub(float *, const float *, const float *);

extern void vec_scale_to_length(char *, char *, float);

extern void FastVecAdd(char *, char *, char *);





extern s32 snd_is_voice_playing_for_owner(void *, s32);

extern s32 PlayMobySound(s32, s32, void *);






extern int FloatToInt(float);
extern void snd_stop_voice(int);
extern char g_sound_state[], g_hero_position[];
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern int func_001163B0(void);
extern void FastVecScale(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern u8 *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);

typedef int TI128 __attribute__((mode(TI)));

extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(float *, const float *, const float *);
extern void FastVecAdd(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern char g_sound_state[];

#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern int snd_is_voice_playing_for_owner(void *,int),PlayMobySound(int,int,void *);
extern void snd_stop_voice(int);

extern void part_spawn_beam_hit_sparks(char *,int);

typedef struct {
 u8 pad[0x7e4]; u8 *attached; u8 gap[0x1c]; s16 timer, mode;
} DamoselBeamState;

#undef F
#undef I
#undef H
#undef P

/* func_L18_00433B70 lives in L18_00433B70.c. */

extern float g_joba_spark_speed_min __attribute__((sda));
extern float g_joba_spark_speed_max __attribute__((sda));
extern float g_joba_spark_velocity_z_min __attribute__((sda));
extern float g_joba_spark_velocity_z_max __attribute__((sda));
extern float g_joba_spark_ground_effect_param __attribute__((sda));
extern float g_joba_spark_size_min __attribute__((sda));
extern float g_joba_spark_size_max __attribute__((sda));

/* Sprays a burst of spark particles from a point, flying away from the object in random directions. */
void part_spawn_beam_hit_sparks(char *pos, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    *(TI128 *)axis = 0;
    axis[2] = 1.0f;
    FastVecSub(direction, g_hero_l11_position, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(g_joba_spark_size_min, g_joba_spark_size_max);
        sign = math_random_int_below(2);
        if (sign == 0)
            sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        speed = math_random_float_range(g_joba_spark_speed_min, g_joba_spark_speed_max) * (1.0f / 60.0f);
        vec_scale_to_length((char *)velocity, (char *)velocity, speed);
        velocity[2] = math_random_float_range(g_joba_spark_velocity_z_min, g_joba_spark_velocity_z_max) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += math_random_signed_float_range(0.0f, 0.15f);
        point[1] += math_random_signed_float_range(0.0f, 0.15f);
        point[2] += math_random_signed_float_range(0.0f, 0.15f);
        if (!(func_001163B0() & 1)) {
            FastVecScale(velocity, velocity, 1.5f);
            particle = part_spawn_ground_effect(point, 60, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 0, g_joba_spark_ground_effect_param);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = part_spawn_ground_effect(point, 60, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, g_joba_spark_ground_effect_param);
        } else {
            FastVecSub(extra, g_hero_l11_position, point);
            vec_scale_to_length((char *)extra, (char *)extra, speed);
            FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
            particle = part_spawn_ground_effect(point, 40, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 0, g_joba_spark_ground_effect_param);
            if (particle)
                particle[9] = FloatToInt(4.0f) + 0x70;
            particle = part_spawn_ground_effect(point, 40, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, g_joba_spark_ground_effect_param);
        }
        if (particle)
            particle[9] = FloatToInt(4.0f) + 0x70;
    }
}

