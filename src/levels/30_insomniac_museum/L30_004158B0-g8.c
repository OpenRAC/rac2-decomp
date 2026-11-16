#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef struct {
    short life, initialLife, duration, pad;
    float inner, outer, strength, scale;
    int sound, flash, count0, count1, count2, count3, count4, count5, color;
} ExplosionState;
extern float g_burst_size_scale __attribute__((sda));
extern float g_burst_l30_speed_scale __attribute__((sda));
extern int g_burst_particle_texture __attribute__((sda));
extern char g_particle_spawn_template[] __attribute__((sda)) NOT_SDA;
extern unsigned char *g_particle_l30_texture_table[];
extern unsigned char *g_particle_sprite_table[];
extern struct { char pad[0x140]; float position[4]; } g_camera_l30_state;
extern char *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern float mat_fast_helper_a(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern char *part_spawn_fading_drift(void *, void *, int, int, int, int, int, float, float, float, int);
extern void FastVecScale(void *, void *, float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern char *part_spawn_trail_2(void *, void *, int, float);
extern char *part_spawn_shockwave_ring(void *, void *, void *, int, float, int, int, int, int);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern char *SpawnSpinningSparkParticle(void *, float, float, float, int, void *, float, int, int);

/* Spawns all the particles of a museum explosion: flash, sparks, smoke, debris and a shock ring. */
void EmitMuseumExplosionParticles(char *moby) {
    float particle_pos[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    ExplosionState *state = *(ExplosionState **)(moby + 0x68);
    float angle;
    int i, sign;
    {
        float burstSize, burstSpeed;
        int i;
        char *particle;
        burstSize = g_burst_size_scale * state->scale * 210000.0f;
        burstSpeed = g_burst_l30_speed_scale * state->scale * 210000.0f;
        particle = part_spawn_gravity_fade(moby + 0x10, g_particle_spawn_template, g_burst_particle_texture, state->color | 0x7F000000, 0, 100, 0, burstSize, burstSpeed, 0.0f, 0);
        if (particle) particle[2] = g_particle_sprite_table[0][0];
        particle = part_spawn_gravity_fade(moby + 0x10, g_particle_spawn_template, g_burst_particle_texture, state->color, 0, 100, 0, burstSize, burstSpeed, 0.0f, 0);
        if (particle) particle[2] = g_particle_sprite_table[0][0];
        {
            int alpha = 0x7F000000;
            for (i = 1; i >= 0; i--) {
                particle = part_spawn_gravity_fade(moby + 0x10, g_particle_spawn_template, g_burst_particle_texture, state->color | alpha, 0, 127, 0, burstSize, burstSpeed, 0.0f, 0);
                if (particle) particle[2] = g_particle_l30_texture_table[0x170/4][5];
            }
        }
        {
            int alpha = 0x7F000000;
            for (i = 1; i >= 0; i--) {
                particle = part_spawn_gravity_fade(moby + 0x10, g_particle_spawn_template, g_burst_particle_texture, state->color | alpha, 0, 127, 0, burstSize, burstSpeed, 0.0f, 0);
                if (particle) particle[2] = g_particle_l30_texture_table[0x170/4][6];
            }
        }
    }
    for (i = 0; i < state->count0; i++) {
        float angle, direction, size, speed;
        int n, life;
        char *particle;
        angle = mat_fast_helper_a(g_camera_l30_state.position[0] - *(float *)(moby+0x10), g_camera_l30_state.position[1] - *(float *)(moby+0x14));
        n = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
        life = math_random_int_range(30, 50);
        particle_pos[0] = *(float *)(moby+0x10) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
        particle_pos[1] = *(float *)(moby+0x14) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
        particle_pos[2] = *(float *)(moby+0x18) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
        size = math_random_float_range(0.6f, 1.0f)*state->scale;
        speed = math_random_float_range(9.0f, 12.0f)*state->scale;
        direction = FastAddRotations(angle, math_random_signed_float_range(0.0f, 1.396263599395752f));
        velocity[0] = math_fast_sin_or_cos_a(direction)*(1.0f/60.0f)*speed;
        velocity[1] = math_fast_sin_or_cos_b(direction)*(1.0f/60.0f)*speed;
        velocity[2] = 0.0f;
        speed = math_random_float_range(0.0f, 12.0f)*state->scale;
        velocity[2] = speed*(1.0f/60.0f);
        part_spawn_fading_drift(particle_pos,velocity,life,state->color,n,127,127,size*210000.0f,state->scale*2100.0f,0.004055555909872055f,1);
        n *= 2;
        particle = part_spawn_fading_drift(particle_pos,velocity,life,state->color&0xFFFFFF,-n,48,48,size*1260000.0f,state->scale*4200.0f,0.004055555909872055f,0);
        if (particle) particle[2] = g_particle_l30_texture_table[0xD4/4][0];
    }
    for (i = 0; i < state->count1; i++) {
        float angle, direction, size, speed;
        int n, life;
        char *particle;
        angle = mat_fast_helper_a(g_camera_l30_state.position[0] - *(float *)(moby+0x10), g_camera_l30_state.position[1] - *(float *)(moby+0x14));
        n = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
        life = math_random_int_range(30, 50);
        particle_pos[0] = *(float *)(moby+0x10) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
        particle_pos[1] = *(float *)(moby+0x14) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
        particle_pos[2] = *(float *)(moby+0x18) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
        size = math_random_float_range(0.75f, 1.5f)*state->scale;
        speed = math_random_float_range(9.0f, 12.0f)*state->scale;
        direction = FastAddRotations(angle, math_random_signed_float_range(0.0f, 1.396263599395752f));
        velocity[0] = math_fast_sin_or_cos_a(direction)*(1.0f/60.0f)*speed;
        velocity[1] = math_fast_sin_or_cos_b(direction)*(1.0f/60.0f)*speed;
        velocity[2] = 0.0f;
        speed = math_random_float_range(0.0f, 12.0f)*state->scale;
        velocity[2] = speed*(1.0f/60.0f);
        part_spawn_fading_drift(particle_pos,velocity,life,state->color&0xFFFFFF,n,127,127,size*210000.0f,state->scale*2100.0f,0.004055555909872055f,5);
    }
    for (i = 0; i < state->count2; i++) {
        float angle, direction, size, speed;
        int n, life;
        char *particle;
        angle = mat_fast_helper_a(g_camera_l30_state.position[0] - *(float *)(moby+0x10), g_camera_l30_state.position[1] - *(float *)(moby+0x14));
        n = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
        life = math_random_int_range(30, 50);
        particle_pos[0] = *(float *)(moby+0x10) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
        particle_pos[1] = *(float *)(moby+0x14) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
        particle_pos[2] = *(float *)(moby+0x18) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
        size = math_random_float_range(0.6f, 1.0f)*state->scale;
        speed = math_random_float_range(9.0f, 12.0f)*state->scale;
        direction = FastAddRotations(angle, math_random_signed_float_range(0.0f, 1.396263599395752f));
        velocity[0] = math_fast_sin_or_cos_a(direction)*(1.0f/60.0f)*speed;
        velocity[1] = math_fast_sin_or_cos_b(direction)*(1.0f/60.0f)*speed;
        velocity[2] = 0.0f;
        speed = math_random_float_range(0.0f, 12.0f)*state->scale;
        velocity[2] = speed*(1.0f/60.0f);
        part_spawn_fading_drift(particle_pos,velocity,life,state->color&0xFFFFFF,n,127,127,size*210000.0f,state->scale*2100.0f,0.004055555909872055f,3);
    }
    for (i = 0; i < state->count4; i++) {
        float x, y;
        char *particle;
        FastVecScale(particle_pos,moby+0xC0,math_random_float_range(15.0f,20.0f)*state->scale*(1.0f/60.0f));
        x = math_random_signed_float_range(0.2617994248867035f,1.396263599395752f);
        y = math_random_signed_float_range(0.2617994248867035f,1.396263599395752f);
        math_build_axis_angle_quat(temp,moby+0xD0,x);
        vec_rotate_by_quaternion(velocity,particle_pos,temp);
        math_build_axis_angle_quat(temp,moby+0xC0,y);
        vec_rotate_by_quaternion(velocity,velocity,temp);
        particle = part_spawn_trail_2(moby+0x10,velocity,math_random_int_range(20,35),0.004055555909872055f);
        if (particle) *(int *)(particle+12) = *(int *)(particle+4) = state->color|0x7F000000;
    }
    if (state->count5) {
        *(Quadword *)velocity = 0;
        velocity[2] = state->scale*(2.0f/15.0f);
        *(Quadword *)particle_pos = *(Quadword *)velocity;
        part_spawn_shockwave_ring(moby,moby+0x10,particle_pos,16,state->scale*3.5f,(unsigned char)state->color,(unsigned char)(state->color>>8),(unsigned char)(state->color>>16),45);
    }
    SpawnExplosionEffects(moby,g_particle_spawn_template,moby+0x10,0.0f,0.0f,0,0,0,0.0f,0.0f,9.0f,0.0f,-1,state->scale*20.0f,0,0,-1,0,0x810001);
    sign = 1;
    angle = mat_fast_helper_a(g_camera_l30_state.position[0] - *(float *)(moby+0x10), g_camera_l30_state.position[1] - *(float *)(moby+0x14));
    for (i = 0; i < state->count3; i++) {
        float size, x, y;
        char *particle;
        particle_pos[0] = *(float *)(moby+0x10) + math_random_signed_float_range(0.0f,1.0f)*state->scale;
        sign = -sign;
        particle_pos[1] = *(float *)(moby+0x14) + math_random_signed_float_range(0.0f,1.0f)*state->scale;
        particle_pos[2] = *(float *)(moby+0x18) + math_random_signed_float_range(0.0f,1.0f)*state->scale;
        size = math_random_float_range(1.0f/60.0f,1.0f/30.0f)*state->scale;
        x = math_random_signed_float_range(0.0f,1.396263599395752f);
        y = math_random_signed_float_range(0.0f,1.5707964897155762f);
        vec_build_spherical_offset(velocity,size,FastAddRotations(angle,y),x);
        particle = SpawnSpinningSparkParticle(particle_pos,0.0f,1.0f,1.01f,sign,velocity,state->scale*315000.0f,state->color|0x7F0000,0);
        if (particle) {
            char *sub = particle + 0x20;
            *(short *)(particle+10) = math_random_int_range(40,70);
            particle[9] = FloatToInt(4.0f)+64;
            *(int *)(sub+4) = 3;
            *(float *)(sub+0x1C) = IntToFloat(math_random_int_range(1,10));
            sub[0xA] = 64;
            sub[0xB] = particle[10];
        }
    }
}
