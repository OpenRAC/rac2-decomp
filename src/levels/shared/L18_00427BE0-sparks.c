#include "common.h"
typedef int TI __attribute__((mode(TI)));
typedef union { u8 b[0x30]; u16 h[0x18]; int i[0xC]; float f[0xC]; void *p[0xC]; } View;
typedef union { u8 b[0x40]; float f[0x10]; int i[0x10]; } State;
extern float D_L18_001B234C MACRO_ADDR;
extern float D_L18_001B2350 MACRO_ADDR;
extern int D_L18_001B2348 __attribute__((sda));
typedef union { u8 b[0x48]; int i[0x12]; float f[0x12]; } Params;
extern Params D_L18_002BDA10;
extern int D_L18_001BFC18 NOT_SDA;
extern u8 D_L18_001A8F20[] MACRO_ADDR;
extern void FastVecAdd(void *,void *,void *);
extern float FastVecLength(void *);
extern float math_random_float_range(float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecScale(void *,void *,float);
extern void *part_spawn_burst(void *,void *,int,int,int,int,float,float,float,float,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern float math_random_angle(void);
extern void math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern int func_001163B0(void);
extern void *part_spawn_trailing_spark(void *,void *,int,int,float,int,int);
extern int CollLine(void *,void *,int,int,void *);
extern int coll_test_point(float,void *,int,int);
extern int math_fast_float_d(void *);
extern int coll_process_hit(void *,int,int,float,void *);
extern void SpawnExplosionEffects(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void moby_mark_spawned(void *);
/* Per-frame update for moby class 4707 (a spark shot). */
/* Drifts a spark shot, spawns its effects, and explodes it on contact or timeout unless the hit is its owner. */
void spark_l18_shot_update(u8 *o) {
    float pos[4] __attribute__((aligned(16)));
    State *s = *(State **)(o+0x68);
    int flag;
    FastVecAdd(pos,o+0x10,s);
    flag = 0;
    if (D_L18_001B234C > 0.9f || D_L18_001B2350 > 0.9f) flag = 1;
    if (!flag || !(D_L18_001B2348 & 1)) {
        float len = FastVecLength(s);
        {
        float v[4], a[4], b[4], c[4];
        *(TI *)b = 0;
        b[0] = math_random_float_range(-1.0f,1.0f);
        b[1] = math_random_float_range(-1.0f,1.0f);
        b[2] = math_random_float_range(-1.0f,1.0f);
        *(TI *)a = *(TI *)b;
        vec_scale_to_length(a,a,math_random_float_range(D_L18_002BDA10.f[0],D_L18_002BDA10.f[1]) * (1.0f/60.0f));
        FastVecScale(v,s,math_random_float_range(D_L18_002BDA10.f[2],D_L18_002BDA10.f[3]));
        FastVecAdd(a,a,v);
        vec_scale_to_length(v,s,math_random_float_range(0.0f,1.0f)*len);
        FastVecAdd(v,v,o+0x10);
        part_spawn_burst(o+0x10,a,D_L18_002BDA10.i[4],D_L18_002BDA10.i[5],D_L18_002BDA10.i[6],D_L18_002BDA10.i[7],D_L18_002BDA10.f[8],D_L18_002BDA10.f[9],D_L18_002BDA10.f[10],D_L18_002BDA10.f[11],0.0f);
        *(TI *)c = 0;
        c[2] = D_L18_002BDA10.f[12];
        *(TI *)b = *(TI *)c;
        matrix_mul_vec3(b,b,o+0xC0);
        math_apply_axis_rotation_to_quat(b,b,o+0xC0,math_random_angle());
        if (func_001163B0() & 1)
            part_spawn_trailing_spark(v,b,D_L18_002BDA10.i[13],D_L18_002BDA10.i[14],(float)D_L18_002BDA10.i[15],D_L18_002BDA10.i[16],D_L18_002BDA10.i[17]);
        }
    }
    {
    View request __attribute__((aligned(16)));
    request.p[4] = o;
    request.i[5] = 0x10001;
    request.f[7] = s->f[8];
    request.i[8] = 1;
    qcopy(&request,s);
    vec_scale_to_length(&request,&request,s->f[9]);
    request.f[3] = 5627.925f;
    request.b[0x18] = s->b[0x28];
    request.b[0x19] = s->b[0x2C];
    request.h[0x1A/2] = *(u16 *)(o+0xAA);
    if (CollLine(o+0x10,pos,0,s->i[4],&request) || coll_test_point(0.2f,pos,0,s->i[4]) || math_fast_float_d(s->b+0x34)) {
        if (D_L18_001BFC18) {
            if (D_L18_001BFC18 != s->i[4]) {
                coll_process_hit(o+0x10,0,s->i[4],0.5f,&request);
                SpawnExplosionEffects(o,D_L18_001A8F20,0,0.0f,0.0f,0,2,10,0.0f,0.0f,9.0f,0.666f,0,0.0f,0,1,-1,0,0x810001);
                moby_mark_spawned(o);
                return;
            }
        } else {
            SpawnExplosionEffects(o,D_L18_001A8F20,0,0.0f,0.0f,0,2,8,0.0f,0.0f,9.0f,0.5f,0,0.0f,0,1,-1,0,0x810001);
            moby_mark_spawned(o);
            return;
        }
    }
    }
    qcopy(o+0x10,pos);
}
