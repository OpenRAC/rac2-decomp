#include "names.h"
/* func_PAL_L30_0041AC18, the PAL copy of func_L30_004158B0: the same C, where 1/60 becomes 0.02,
 * 1/30 becomes 0.04, 2/15 becomes 0.16, 0.0040555559 becomes 0.00584, the ring count 16 becomes 13
 * and particle lifetimes are scaled by 5/6. Each loop has its own counter and the two pairs count up. */
#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef struct {
    short life, initial_life, duration, pad;
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

/* Spawns the particles of a museum explosion: a flash, smoke puffs, sparks, trails, a shockwave ring and spinning embers, sized by the explosion's scale (PAL version). */
void EmitMuseumExplosionParticles_pal(char *obj) {
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    ExplosionState *state = *(ExplosionState **)(obj + 0x68);
    float angle_to_camera;
    int i, sign;
    {
        float burst_size, burst_speed;
        int i;
        char *particle;
        burst_size = g_burst_size_scale * state->scale * 210000.0f;
        burst_speed = g_burst_l30_speed_scale * state->scale * 210000.0f;
        particle = part_spawn_gravity_fade(obj + 0x10, g_particle_spawn_template, (g_burst_particle_texture * 5 + 2) / 6, state->color | 0x7F000000, 0, 100, 0, burst_size, burst_speed, 0.0f, 0);
        if (particle) particle[2] = g_particle_sprite_table[0][0];
        particle = part_spawn_gravity_fade(obj + 0x10, g_particle_spawn_template, (g_burst_particle_texture * 5 + 2) / 6, state->color, 0, 100, 0, burst_size, burst_speed, 0.0f, 0);
        if (particle) particle[2] = g_particle_sprite_table[0][0];
        for (i = 0; i < 2; i++) {
            particle = part_spawn_gravity_fade(obj + 0x10, g_particle_spawn_template, (g_burst_particle_texture * 5 + 2) / 6, state->color | 0x7F000000, 0, 127, 0, burst_size, burst_speed, 0.0f, 0);
            if (particle) particle[2] = g_particle_l30_texture_table[0x170/4][5];
        }
        for (i = 0; i < 2; i++) {
            particle = part_spawn_gravity_fade(obj + 0x10, g_particle_spawn_template, (g_burst_particle_texture * 5 + 2) / 6, state->color | 0x7F000000, 0, 127, 0, burst_size, burst_speed, 0.0f, 0);
            if (particle) particle[2] = g_particle_l30_texture_table[0x170/4][6];
        }
    }
    {
        int i;
        for (i = 0; i < state->count0; i++) {
            float angle_to_camera, direction, size, speed;
            int puff_count, life;
            char *particle;
            angle_to_camera = mat_fast_helper_a(g_camera_l30_state.position[0] - *(float *)(obj+0x10), g_camera_l30_state.position[1] - *(float *)(obj+0x14));
            puff_count = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            life = math_random_int_range(30, 50);
            position[0] = *(float *)(obj+0x10) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
            position[1] = *(float *)(obj+0x14) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
            position[2] = *(float *)(obj+0x18) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
            size = math_random_float_range(0.6f, 1.0f)*state->scale;
            speed = math_random_float_range(9.0f, 12.0f)*state->scale;
            direction = FastAddRotations(angle_to_camera, math_random_signed_float_range(0.0f, 1.396263599395752f));
            velocity[0] = math_fast_sin_or_cos_a(direction)*0.020000001f*speed;
            velocity[1] = math_fast_sin_or_cos_b(direction)*0.020000001f*speed;
            velocity[2] = 0.0f;
            speed = math_random_float_range(0.0f, 12.0f)*state->scale;
            velocity[2] = speed*0.020000001f;
            part_spawn_fading_drift(position,velocity,(life * 5 + 2) / 6,state->color,puff_count,127,127,size*210000.0f,state->scale*2100.0f,0.00584f,1);
            puff_count *= 2;
            particle = part_spawn_fading_drift(position,velocity,(life * 5 + 2) / 6,state->color&0xFFFFFF,-puff_count,48,48,size*1260000.0f,state->scale*4200.0f,0.00584f,0);
            if (particle) particle[2] = g_particle_l30_texture_table[0xD4/4][0];
        }
    }
    {
        int i;
        for (i = 0; i < state->count1; i++) {
            float angle_to_camera, direction, size, speed;
            int puff_count, life;
            char *particle;
            angle_to_camera = mat_fast_helper_a(g_camera_l30_state.position[0] - *(float *)(obj+0x10), g_camera_l30_state.position[1] - *(float *)(obj+0x14));
            puff_count = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            life = math_random_int_range(30, 50);
            position[0] = *(float *)(obj+0x10) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
            position[1] = *(float *)(obj+0x14) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
            position[2] = *(float *)(obj+0x18) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
            size = math_random_float_range(0.75f, 1.5f)*state->scale;
            speed = math_random_float_range(9.0f, 12.0f)*state->scale;
            direction = FastAddRotations(angle_to_camera, math_random_signed_float_range(0.0f, 1.396263599395752f));
            velocity[0] = math_fast_sin_or_cos_a(direction)*0.020000001f*speed;
            velocity[1] = math_fast_sin_or_cos_b(direction)*0.020000001f*speed;
            velocity[2] = 0.0f;
            speed = math_random_float_range(0.0f, 12.0f)*state->scale;
            velocity[2] = speed*0.020000001f;
            part_spawn_fading_drift(position,velocity,(life * 5 + 2) / 6,state->color&0xFFFFFF,puff_count,127,127,size*210000.0f,state->scale*2100.0f,0.00584f,5);
        }
    }
    {
        int i;
        for (i = 0; i < state->count2; i++) {
            float angle_to_camera, direction, size, speed;
            int puff_count, life;
            char *particle;
            angle_to_camera = mat_fast_helper_a(g_camera_l30_state.position[0] - *(float *)(obj+0x10), g_camera_l30_state.position[1] - *(float *)(obj+0x14));
            puff_count = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            life = math_random_int_range(30, 50);
            position[0] = *(float *)(obj+0x10) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
            position[1] = *(float *)(obj+0x14) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
            position[2] = *(float *)(obj+0x18) + math_random_signed_float_range(0.0f, 0.1f)*state->scale;
            size = math_random_float_range(0.6f, 1.0f)*state->scale;
            speed = math_random_float_range(9.0f, 12.0f)*state->scale;
            direction = FastAddRotations(angle_to_camera, math_random_signed_float_range(0.0f, 1.396263599395752f));
            velocity[0] = math_fast_sin_or_cos_a(direction)*0.020000001f*speed;
            velocity[1] = math_fast_sin_or_cos_b(direction)*0.020000001f*speed;
            velocity[2] = 0.0f;
            speed = math_random_float_range(0.0f, 12.0f)*state->scale;
            velocity[2] = speed*0.020000001f;
            part_spawn_fading_drift(position,velocity,(life * 5 + 2) / 6,state->color&0xFFFFFF,puff_count,127,127,size*210000.0f,state->scale*2100.0f,0.00584f,3);
        }
    }
    {
        int i;
        for (i = 0; i < state->count4; i++) {
            float x, y;
            char *particle;
            FastVecScale(position,obj+0xC0,math_random_float_range(15.0f,20.0f)*state->scale*0.020000001f);
            x = math_random_signed_float_range(0.2617994248867035f,1.396263599395752f);
            y = math_random_signed_float_range(0.2617994248867035f,1.396263599395752f);
            math_build_axis_angle_quat(rotation,obj+0xD0,x);
            vec_rotate_by_quaternion(velocity,position,rotation);
            math_build_axis_angle_quat(rotation,obj+0xC0,y);
            vec_rotate_by_quaternion(velocity,velocity,rotation);
            particle = part_spawn_trail_2(obj+0x10,velocity,(math_random_int_range(20,35) * 5 + 2) / 6,0.00584f);
            if (particle) {
                int alpha = 0x7F000000;
                *(int *)(particle+12) = *(int *)(particle+4) = state->color|alpha;
            }
        }
    }
    if (state->count5) {
        *(Quadword *)velocity = 0;
        velocity[2] = state->scale*0.16000001f;
        *(Quadword *)position = *(Quadword *)velocity;
        part_spawn_shockwave_ring(obj,obj+0x10,position,13,state->scale*3.5f,(unsigned char)state->color,(unsigned char)(state->color>>8),(unsigned char)(state->color>>16),45);
    }
    SpawnExplosionEffects(obj,g_particle_spawn_template,obj+0x10,0.0f,0.0f,0,0,0,0.0f,0.0f,9.0f,0.0f,-1,state->scale*20.0f,0,0,-1,0,0x810001);
    sign = 1;
    angle_to_camera = mat_fast_helper_a(g_camera_l30_state.position[0] - *(float *)(obj+0x10), g_camera_l30_state.position[1] - *(float *)(obj+0x14));
    for (i = 0; i < state->count3; i++) {
        float size, x, y;
        char *particle;
        position[0] = *(float *)(obj+0x10) + math_random_signed_float_range(0.0f,1.0f)*state->scale;
        sign = -sign;
        position[1] = *(float *)(obj+0x14) + math_random_signed_float_range(0.0f,1.0f)*state->scale;
        position[2] = *(float *)(obj+0x18) + math_random_signed_float_range(0.0f,1.0f)*state->scale;
        size = math_random_float_range(0.020000001f,0.040000003f)*state->scale;
        x = math_random_signed_float_range(0.0f,1.396263599395752f);
        y = math_random_signed_float_range(0.0f,1.5707964897155762f);
        vec_build_spherical_offset(velocity,size,FastAddRotations(angle_to_camera,y),x);
        particle = SpawnSpinningSparkParticle(position,0.0f,1.0f,1.01f,sign,velocity,state->scale*315000.0f,state->color|0x7F0000,0);
        if (particle) {
            char *sub = particle + 0x20;
            *(short *)(particle+10) = (math_random_int_range(40,70) * 5 + 2) / 6;
            particle[9] = FloatToInt(4.0f)+64;
            *(int *)(sub+4) = 3;
            *(float *)(sub+0x1C) = IntToFloat((math_random_int_range(1,10) * 5 + 2) / 6);
            sub[0xA] = 64;
            sub[0xB] = particle[10];
        }
    }
}
