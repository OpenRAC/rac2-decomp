#include "common.h"
extern int D_L01_001B0844 __attribute__((sda));
extern int D_L01_001B0848 __attribute__((sda));
extern int D_L01_001B0888 __attribute__((sda));
extern int D_L01_001B088C __attribute__((sda));
extern int D_L01_001B0874 __attribute__((sda));
extern int D_L01_001B0878 __attribute__((sda));
extern int D_L01_001B087C __attribute__((sda));
extern int D_L01_001B0880 __attribute__((sda));
extern int D_L01_001B0884 __attribute__((sda));
extern float D_L01_001B084C __attribute__((sda));
extern float D_L01_001B0850 __attribute__((sda));
extern float D_L01_001B0854 __attribute__((sda));
extern float D_L01_001B0858 __attribute__((sda));
extern float D_L01_001B085C __attribute__((sda));
extern float D_L01_001B0860 __attribute__((sda));
extern float D_L01_001B0864 __attribute__((sda));
extern float D_L01_001B0868 __attribute__((sda));
extern float D_L01_001B086C __attribute__((sda));
extern float D_L01_001B0870 __attribute__((sda));
extern float D_L01_001B0890 __attribute__((sda));
extern float D_L01_001B083C __attribute__((sda));
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

    for (i = 0; i < D_L01_001B0844; i++) {
        position = moby + 0x10;
        qcopy(pos, position);
        vec_add_random_offset(pos, D_L01_001B084C);
        pos[2] += 0.25f;
        angle = math_random_angle();
        speed = math_random_float_range(D_L01_001B0858, D_L01_001B085C);
        rise = math_random_float_range(D_L01_001B0860, D_L01_001B0864);
        spread = math_random_float_range(0.0f, D_L01_001B0890);
        FastVecScale(vel, base_velocity, spread * 0.016666668f);
        vel[0] += math_fast_sin_or_cos_a(angle) * 0.016666668f * speed;
        vel[1] += math_fast_sin_or_cos_b(angle) * 0.016666668f * speed;
        vel[2] += rise * 0.016666668f;
        qcopy(acc, vel);
        acc[2] -= D_L01_001B0868 * ((float)D_L01_001B0888 * 0.00027777778f);
        for (j = 0; j < D_L01_001B0848; j++) {
            scale = math_random_float_range(0.5f, 1.5f);
            vel[3] = scale * D_L01_001B086C;
            acc[3] = scale * D_L01_001B0870;
            vec_add_random_offset(pos, D_L01_001B0850);
            vec_add_random_offset(acc, D_L01_001B0854 * 0.016666668f);
            start_color = FastTweenColor(D_L01_001B0874, D_L01_001B087C,
                              math_random_float_range(0.0f, 1.0f));
            upperScale = 2.5f;
            end_color = FastTweenColor(D_L01_001B0878, D_L01_001B0880,
                              math_random_float_range(0.0f, 1.0f));
            lifetime = (float)D_L01_001B088C;
            maximum = lifetime * upperScale;
            particle_life = FloatToInt(math_random_float_range(lifetime * 0.5f, maximum));
            part_spawn_trail(pos, vel, acc, start_color, end_color, D_L01_001B0884,
                          D_L01_001B0888, particle_life, -1);
        }
    }
    SpawnExplosionEffects(moby, vars, 0, 4, 0, 0, -1, 0, 0, -1, 1, 0x810001,
                  D_L01_001B083C, *(float *)(vars + 0x18), 4.0f, 2.0f,
                  9.0f, 1.2f, 0.0f);
}
