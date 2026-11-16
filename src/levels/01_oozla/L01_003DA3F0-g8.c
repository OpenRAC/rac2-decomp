#include "common.h"
extern int g_explosion_outer_count __attribute__((sda));
extern int g_explosion_inner_count __attribute__((sda));
extern int g_explosion_particle_life __attribute__((sda));
extern int g_explosion_lifetime __attribute__((sda));
extern int g_explosion_start_color_a __attribute__((sda));
extern int g_explosion_end_color_a __attribute__((sda));
extern int g_explosion_start_color_b __attribute__((sda));
extern int g_explosion_end_color_b __attribute__((sda));
extern int g_explosion_trail_sprite __attribute__((sda));
extern float g_explosion_pos_offset_a __attribute__((sda));
extern float g_explosion_pos_offset_b __attribute__((sda));
extern float g_explosion_accel_jitter __attribute__((sda));
extern float g_explosion_l01_speed_min __attribute__((sda));
extern float g_explosion_l01_speed_max __attribute__((sda));
extern float g_explosion_rise_min __attribute__((sda));
extern float g_explosion_rise_max __attribute__((sda));
extern float g_explosion_gravity __attribute__((sda));
extern float g_explosion_vel_scale __attribute__((sda));
extern float g_explosion_accel_scale __attribute__((sda));
extern float g_explosion_spread_max __attribute__((sda));
extern float g_explosion_particle_size __attribute__((sda));
extern void vec_add_random_offset(void *, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *,void *, float);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern int FloatToInt(float);
extern void *part_spawn_trail(void *,void *,void *,int,int,int,int,int,int);
extern void SpawnExplosionEffects(void *,void *,int,int,int,int,int,int,int,int,int, int, float, float,float, float,float, float,float);
/* Emits randomized particle trails, then the owner's explosion effect. */
/* Sprays random trails of particles, then starts the explosion effect. */
void part_l01_spawn_explosion_particles(u8 *moby, void *base_velocity)
{
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float acc[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby + 0x68);
    int i, j, start_color, end_color, particle_life;
    float angle, speed, rise, spread, scale, lifetime, maximum, upperScale;
    u8 *position;

    for (i = 0; i < g_explosion_outer_count; i++) {
        position = moby + 0x10;
        qcopy(pos, position);
        vec_add_random_offset(pos, g_explosion_pos_offset_a);
        pos[2] += 0.25f;
        angle = math_random_angle();
        speed = math_random_float_range(g_explosion_l01_speed_min, g_explosion_l01_speed_max);
        rise = math_random_float_range(g_explosion_rise_min, g_explosion_rise_max);
        spread = math_random_float_range(0.0f, g_explosion_spread_max);
        FastVecScale(vel, base_velocity, spread * 0.016666668f);
        vel[0] += math_fast_sin_or_cos_a(angle) * 0.016666668f * speed;
        vel[1] += math_fast_sin_or_cos_b(angle) * 0.016666668f * speed;
        vel[2] += rise * 0.016666668f;
        qcopy(acc, vel);
        acc[2] -= g_explosion_gravity * ((float)g_explosion_particle_life * 0.00027777778f);
        for (j = 0; j < g_explosion_inner_count; j++) {
            scale = math_random_float_range(0.5f, 1.5f);
            vel[3] = scale * g_explosion_vel_scale;
            acc[3] = scale * g_explosion_accel_scale;
            vec_add_random_offset(pos, g_explosion_pos_offset_b);
            vec_add_random_offset(acc, g_explosion_accel_jitter * 0.016666668f);
            start_color = FastTweenColor(g_explosion_start_color_a, g_explosion_start_color_b,
                              math_random_float_range(0.0f, 1.0f));
            upperScale = 2.5f;
            end_color = FastTweenColor(g_explosion_end_color_a, g_explosion_end_color_b,
                              math_random_float_range(0.0f, 1.0f));
            lifetime = (float)g_explosion_lifetime;
            maximum = lifetime * upperScale;
            particle_life = FloatToInt(math_random_float_range(lifetime * 0.5f, maximum));
            part_spawn_trail(pos, vel, acc, start_color, end_color, g_explosion_trail_sprite,
                          g_explosion_particle_life, particle_life, -1);
        }
    }
    SpawnExplosionEffects(moby, vars, 0, 4, 0, 0, -1, 0, 0, -1, 1, 0x810001,
                  g_explosion_particle_size, *(float *)(vars + 0x18), 4.0f, 2.0f,
                  9.0f, 1.2f, 0.0f);
}
