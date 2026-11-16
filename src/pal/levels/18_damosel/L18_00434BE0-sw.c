#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern int IsPointInCuboid(void *, int);
extern u8 g_hero_position[];
extern u8 *protopet_count_group(int, int *);
extern int flag_set_first_pending(void *);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern int PlayMobySound(int, int, void *);
extern void vec_clear_128(void *);
extern void vec_add_random_offset(void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void protopet_launch_shot(void *, void *, void *);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern int projectile_compute_flight_time(float, float, float, float);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern float math_fast_float_g(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float g_leader_vertical_speed_max __attribute__((sda));
extern float g_debris_angle_x_max_deg __attribute__((sda));
extern float g_debris_angle_y_max_deg __attribute__((sda));
extern float g_debris_launch_speed_z __attribute__((sda));
extern float g_debris_velocity_jitter __attribute__((sda));
extern float g_debris_vertical_speed_min __attribute__((sda));
extern float g_debris_vertical_speed_max __attribute__((sda));
extern int g_debris_angle_random_limit __attribute__((sda));
extern float g_debris_wave_scale __attribute__((sda));
extern int g_debris_wave_period __attribute__((sda));
extern float g_debris_wave_amplitude __attribute__((sda));
extern float g_debris_l18_gravity __attribute__((sda));
extern u8 g_debris_spawn_offset[16] __attribute__((sda));
typedef struct {
    float angles[4];
    int firstId,  secondId,  group;
    float restHeight,  verticalSpeed,  period,  amplitude;
    int spawnCount;
} LauncherState;
typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 state;
    u8 pad21[0x47];
    LauncherState *vars;
    u8 pad6c[0x2A];
    u16 timer;
    u8 pad98[0x58];
    float rotation[4];
} LauncherObject;

/* Updates the launcher: it bounces up and down, throws out Protopets on a trigger, and finally wobbles until it settles. (PAL: 50 Hz timings) */
void group_launcher_update_pal(u8 *moby)
{
    float velocity[4], position[4];
    int count1, count2, count, i;
    u8 *protopet;
    LauncherObject *object = (LauncherObject *)moby;
    LauncherState *vars = object->vars;
    float zero, duration;

    switch (object->state) {
    case 0:
        vars->restHeight = object->position[2];
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (vars->firstId != -1 && IsPointInCuboid(g_hero_position, vars->firstId)) {
            protopet_count_group(vars->group, &count1);
            if (count1 >= 4)
                moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            object->rotation[0] = 0;
            object->rotation[1] = 0;
            zero = object->rotation[0];
            object->position[2] = vars->restHeight;
            vars->verticalSpeed += math_random_float_range(zero, g_leader_vertical_speed_max * 0.020000001f);
            vars->angles[0] = math_random_float_range(zero, g_debris_angle_x_max_deg * 0.0003490659f);
            vars->angles[1] = math_random_float_range(zero, g_debris_angle_y_max_deg * 0.0003490659f);
            object->position[2] = vars->restHeight;
            PlayMobySound(0, 0, moby);
        }
        if (object->position[2] >= vars->restHeight) {
            object->position[2] += vars->verticalSpeed;
            vars->verticalSpeed -= g_debris_l18_gravity * 0.00040000002f;
            if (vars->verticalSpeed > 0) {
                object->rotation[0] = FastAddRotations(vars->angles[0], object->rotation[0]);
                object->rotation[1] = FastAddRotations(vars->angles[1], object->rotation[1]);
            } else {
                object->rotation[0] = FastAddRotations(-vars->angles[0], object->rotation[0]);
                object->rotation[1] = FastAddRotations(-vars->angles[1], object->rotation[1]);
            }
        } else {
            moby_set_state(moby, 2, -1);
        }
        if (vars->secondId != -1 && IsPointInCuboid(g_hero_position, vars->secondId)) {
            protopet_count_group(vars->group, &count2);
            if (count2 >= 4)
                moby_set_state(moby, 3, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            object->rotation[0] = 0;
            object->rotation[1] = 0;
            object->position[2] = vars->restHeight;
            count = 50;
            for (i = 0; i < vars->spawnCount && count > 0; i++) {
                protopet = protopet_count_group(vars->group, &count);
                if (protopet) {
                    vec_clear_128(velocity);
                    velocity[2] = g_debris_launch_speed_z * 0.020000001f;
                    vec_add_random_offset(velocity, g_debris_velocity_jitter * 0.020000001f);
                    FastVecAdd(position, moby + 0x10, g_debris_spawn_offset);
                    protopet_launch_shot(protopet, position, velocity);
                    *(u8 **)(protopet + 0xB8) = moby;
                }
            }
            if (i) {
                SpawnExplosion_pal(moby + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1,
                              1.0f, 20.0f, 1, 1, 0, 0);
                PlayMobySound(0, 0, moby);
                vars->verticalSpeed += math_random_float_range(g_debris_vertical_speed_min, g_debris_vertical_speed_max) * 0.020000001f;
                duration = (float)projectile_compute_flight_time(object->position[2], vars->restHeight,
                                                   vars->verticalSpeed, g_debris_l18_gravity * 0.00040000002f);
                vars->angles[0] = (float)math_random_int_below(g_debris_angle_random_limit) * 6.28318548f / duration;
                vars->angles[1] = (float)math_random_int_below(g_debris_angle_random_limit) * 6.28318548f / duration;
                vars->angles[2] = (float)math_random_int_below(g_debris_angle_random_limit) * 6.28318548f / duration;
            }
        }
        if (object->position[2] >= vars->restHeight) {
            object->position[2] += vars->verticalSpeed;
            vars->verticalSpeed -= g_debris_l18_gravity * 0.00040000002f;
            object->rotation[0] = FastAddRotations(vars->angles[0], object->rotation[0]);
            object->rotation[1] = FastAddRotations(vars->angles[1], object->rotation[1]);
            object->rotation[2] = FastAddRotations(vars->angles[2], object->rotation[2]);
        } else {
            moby_set_state(moby, 4, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            vec_clear_128(vars);
            vec_clear_128(moby + 0xF0);
            object->position[2] = vars->restHeight;
            vars->period = IntToFloat(g_debris_wave_period);
            vars->amplitude = g_debris_wave_amplitude;
            PlayMobySound(0, 0, moby);
        }
        if (vars->amplitude >= 0.1f) {
            object->rotation[0] = vars->amplitude * math_fast_sin_or_cos_b(math_fast_float_g(
                IntToFloat(object->timer) * 6.28318548f / vars->period));
            object->rotation[1] = vars->amplitude * math_fast_sin_or_cos_a(math_fast_float_g(
                IntToFloat(object->timer) * 6.28318548f / vars->period));
            vars->amplitude *= g_debris_wave_scale;
            vars->period *= g_debris_wave_scale;
        } else {
            object->rotation[0] = object->rotation[1] = object->rotation[2] = 0.0f;
            moby_set_state(moby, 5, -1);
        }
    }
    if (object->timer <= 0xFFFE)
        ++object->timer;
}
