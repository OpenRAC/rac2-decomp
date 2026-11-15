/* func_PAL_L30_0041AC18, the PAL copy of func_L30_004158B0: the same C, where 1/60 becomes 0.02,
 * 1/30 becomes 0.04, 2/15 becomes 0.16, 0.0040555559 becomes 0.00584, the ring count 16 becomes 13
 * and particle lifetimes are scaled by 5/6. Each loop has its own counter and the two pairs count up. */
#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef struct {
    short life, initialLife, duration, pad;
    float inner, outer, strength, scale;
    int sound, flash, count0, count1, count2, count3, count4, count5, color;
} ExplosionState;
extern float D_L30_001B1EF8 __attribute__((sda));
extern float D_L30_001B1EFC __attribute__((sda));
extern int D_L30_001B1F00 __attribute__((sda));
extern char D_L30_001A8F20[] __attribute__((sda)) NOT_SDA;
extern unsigned char *D_L30_001FF940[];
extern unsigned char *D_L30_001FFAB0[];
extern struct { char pad[0x140]; float position[4]; } D_L30_001B9C80;
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
extern void part_spawn_shockwave_ring(void *, void *, void *, int, float, int, int, int, int);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern char *SpawnSpinningSparkParticle(void *, float, float, float, int, void *, float, int, int);

void func_PAL_L30_0041AC18(char *obj) {
    float p[4] __attribute__((aligned(16)));
    float v[4] __attribute__((aligned(16)));
    float t[4] __attribute__((aligned(16)));
    ExplosionState *st = *(ExplosionState **)(obj + 0x68);
    float a;
    int i, sign;
    {
        float burstSize, burstSpeed;
        int i;
        char *particle;
        burstSize = D_L30_001B1EF8 * st->scale * 210000.0f;
        burstSpeed = D_L30_001B1EFC * st->scale * 210000.0f;
        particle = part_spawn_gravity_fade(obj + 0x10, D_L30_001A8F20, (D_L30_001B1F00 * 5 + 2) / 6, st->color | 0x7F000000, 0, 100, 0, burstSize, burstSpeed, 0.0f, 0);
        if (particle) particle[2] = D_L30_001FFAB0[0][0];
        particle = part_spawn_gravity_fade(obj + 0x10, D_L30_001A8F20, (D_L30_001B1F00 * 5 + 2) / 6, st->color, 0, 100, 0, burstSize, burstSpeed, 0.0f, 0);
        if (particle) particle[2] = D_L30_001FFAB0[0][0];
        for (i = 0; i < 2; i++) {
            particle = part_spawn_gravity_fade(obj + 0x10, D_L30_001A8F20, (D_L30_001B1F00 * 5 + 2) / 6, st->color | 0x7F000000, 0, 127, 0, burstSize, burstSpeed, 0.0f, 0);
            if (particle) particle[2] = D_L30_001FF940[0x170/4][5];
        }
        for (i = 0; i < 2; i++) {
            particle = part_spawn_gravity_fade(obj + 0x10, D_L30_001A8F20, (D_L30_001B1F00 * 5 + 2) / 6, st->color | 0x7F000000, 0, 127, 0, burstSize, burstSpeed, 0.0f, 0);
            if (particle) particle[2] = D_L30_001FF940[0x170/4][6];
        }
    }
    {
        int i;
        for (i = 0; i < st->count0; i++) {
            float a, direction, size, speed;
            int n, life;
            char *particle;
            a = mat_fast_helper_a(D_L30_001B9C80.position[0] - *(float *)(obj+0x10), D_L30_001B9C80.position[1] - *(float *)(obj+0x14));
            n = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            life = math_random_int_range(30, 50);
            p[0] = *(float *)(obj+0x10) + math_random_signed_float_range(0.0f, 0.1f)*st->scale;
            p[1] = *(float *)(obj+0x14) + math_random_signed_float_range(0.0f, 0.1f)*st->scale;
            p[2] = *(float *)(obj+0x18) + math_random_signed_float_range(0.0f, 0.1f)*st->scale;
            size = math_random_float_range(0.6f, 1.0f)*st->scale;
            speed = math_random_float_range(9.0f, 12.0f)*st->scale;
            direction = FastAddRotations(a, math_random_signed_float_range(0.0f, 1.396263599395752f));
            v[0] = math_fast_sin_or_cos_a(direction)*0.020000001f*speed;
            v[1] = math_fast_sin_or_cos_b(direction)*0.020000001f*speed;
            v[2] = 0.0f;
            speed = math_random_float_range(0.0f, 12.0f)*st->scale;
            v[2] = speed*0.020000001f;
            part_spawn_fading_drift(p,v,(life * 5 + 2) / 6,st->color,n,127,127,size*210000.0f,st->scale*2100.0f,0.00584f,1);
            n *= 2;
            particle = part_spawn_fading_drift(p,v,(life * 5 + 2) / 6,st->color&0xFFFFFF,-n,48,48,size*1260000.0f,st->scale*4200.0f,0.00584f,0);
            if (particle) particle[2] = D_L30_001FF940[0xD4/4][0];
        }
    }
    {
        int i;
        for (i = 0; i < st->count1; i++) {
            float a, direction, size, speed;
            int n, life;
            char *particle;
            a = mat_fast_helper_a(D_L30_001B9C80.position[0] - *(float *)(obj+0x10), D_L30_001B9C80.position[1] - *(float *)(obj+0x14));
            n = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            life = math_random_int_range(30, 50);
            p[0] = *(float *)(obj+0x10) + math_random_signed_float_range(0.0f, 0.1f)*st->scale;
            p[1] = *(float *)(obj+0x14) + math_random_signed_float_range(0.0f, 0.1f)*st->scale;
            p[2] = *(float *)(obj+0x18) + math_random_signed_float_range(0.0f, 0.1f)*st->scale;
            size = math_random_float_range(0.75f, 1.5f)*st->scale;
            speed = math_random_float_range(9.0f, 12.0f)*st->scale;
            direction = FastAddRotations(a, math_random_signed_float_range(0.0f, 1.396263599395752f));
            v[0] = math_fast_sin_or_cos_a(direction)*0.020000001f*speed;
            v[1] = math_fast_sin_or_cos_b(direction)*0.020000001f*speed;
            v[2] = 0.0f;
            speed = math_random_float_range(0.0f, 12.0f)*st->scale;
            v[2] = speed*0.020000001f;
            part_spawn_fading_drift(p,v,(life * 5 + 2) / 6,st->color&0xFFFFFF,n,127,127,size*210000.0f,st->scale*2100.0f,0.00584f,5);
        }
    }
    {
        int i;
        for (i = 0; i < st->count2; i++) {
            float a, direction, size, speed;
            int n, life;
            char *particle;
            a = mat_fast_helper_a(D_L30_001B9C80.position[0] - *(float *)(obj+0x10), D_L30_001B9C80.position[1] - *(float *)(obj+0x14));
            n = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            life = math_random_int_range(30, 50);
            p[0] = *(float *)(obj+0x10) + math_random_signed_float_range(0.0f, 0.1f)*st->scale;
            p[1] = *(float *)(obj+0x14) + math_random_signed_float_range(0.0f, 0.1f)*st->scale;
            p[2] = *(float *)(obj+0x18) + math_random_signed_float_range(0.0f, 0.1f)*st->scale;
            size = math_random_float_range(0.6f, 1.0f)*st->scale;
            speed = math_random_float_range(9.0f, 12.0f)*st->scale;
            direction = FastAddRotations(a, math_random_signed_float_range(0.0f, 1.396263599395752f));
            v[0] = math_fast_sin_or_cos_a(direction)*0.020000001f*speed;
            v[1] = math_fast_sin_or_cos_b(direction)*0.020000001f*speed;
            v[2] = 0.0f;
            speed = math_random_float_range(0.0f, 12.0f)*st->scale;
            v[2] = speed*0.020000001f;
            part_spawn_fading_drift(p,v,(life * 5 + 2) / 6,st->color&0xFFFFFF,n,127,127,size*210000.0f,st->scale*2100.0f,0.00584f,3);
        }
    }
    {
        int i;
        for (i = 0; i < st->count4; i++) {
            float x, y;
            char *particle;
            FastVecScale(p,obj+0xC0,math_random_float_range(15.0f,20.0f)*st->scale*0.020000001f);
            x = math_random_signed_float_range(0.2617994248867035f,1.396263599395752f);
            y = math_random_signed_float_range(0.2617994248867035f,1.396263599395752f);
            math_build_axis_angle_quat(t,obj+0xD0,x);
            vec_rotate_by_quaternion(v,p,t);
            math_build_axis_angle_quat(t,obj+0xC0,y);
            vec_rotate_by_quaternion(v,v,t);
            particle = part_spawn_trail_2(obj+0x10,v,(math_random_int_range(20,35) * 5 + 2) / 6,0.00584f);
            if (particle) {
                int alpha = 0x7F000000;
                *(int *)(particle+12) = *(int *)(particle+4) = st->color|alpha;
            }
        }
    }
    if (st->count5) {
        *(Quadword *)v = 0;
        v[2] = st->scale*0.16000001f;
        *(Quadword *)p = *(Quadword *)v;
        part_spawn_shockwave_ring(obj,obj+0x10,p,13,st->scale*3.5f,(unsigned char)st->color,(unsigned char)(st->color>>8),(unsigned char)(st->color>>16),45);
    }
    SpawnExplosionEffects(obj,D_L30_001A8F20,obj+0x10,0.0f,0.0f,0,0,0,0.0f,0.0f,9.0f,0.0f,-1,st->scale*20.0f,0,0,-1,0,0x810001);
    sign = 1;
    a = mat_fast_helper_a(D_L30_001B9C80.position[0] - *(float *)(obj+0x10), D_L30_001B9C80.position[1] - *(float *)(obj+0x14));
    for (i = 0; i < st->count3; i++) {
        float size, x, y;
        char *particle;
        p[0] = *(float *)(obj+0x10) + math_random_signed_float_range(0.0f,1.0f)*st->scale;
        sign = -sign;
        p[1] = *(float *)(obj+0x14) + math_random_signed_float_range(0.0f,1.0f)*st->scale;
        p[2] = *(float *)(obj+0x18) + math_random_signed_float_range(0.0f,1.0f)*st->scale;
        size = math_random_float_range(0.020000001f,0.040000003f)*st->scale;
        x = math_random_signed_float_range(0.0f,1.396263599395752f);
        y = math_random_signed_float_range(0.0f,1.5707964897155762f);
        vec_build_spherical_offset(v,size,FastAddRotations(a,y),x);
        particle = SpawnSpinningSparkParticle(p,0.0f,1.0f,1.01f,sign,v,st->scale*315000.0f,st->color|0x7F0000,0);
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
