#include "include_asm.h"

#include "common.h"
typedef int TI __attribute__((mode(TI)));
typedef union { u8 b[0x30]; u16 h[0x18]; int i[0xC]; float f[0xC]; void *p[0xC]; } View;
typedef union { u8 b[0x40]; float f[0x10]; int i[0x10]; } State;
extern float g_spark_hit_value_a MACRO_ADDR;
extern float g_spark_hit_value_b MACRO_ADDR;
extern int g_frame_l18_counter __attribute__((sda));
typedef union { u8 b[0x48]; int i[0x12]; float f[0x12]; } Params;
extern Params g_spark_params;
extern int g_tether_l18_hit_result NOT_SDA;
extern u8 g_explosion_effect_desc[] MACRO_ADDR;
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
extern void SpawnExplosionEffects_pal(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void moby_mark_spawned(void *);

/* Drifts a spark shot, spawns its effects, and explodes it on contact or timeout unless the hit is its owner. */
void spark_l18_shot_update_pal(u8 *moby) {
    float pos[4] __attribute__((aligned(16)));
    State *vars = *(State **)(moby+0x68);
    int hit_flag;
    FastVecAdd(pos,moby+0x10,vars);
    hit_flag = 0;
    if (g_spark_hit_value_a > 0.9f || g_spark_hit_value_b > 0.9f) hit_flag = 1;
    if (!hit_flag || !(g_frame_l18_counter & 1)) {
        float speed_len = FastVecLength(vars);
        {
        float spawn_pos[4], burst_vel[4], random_dir[4], offset[4];
        *(TI *)random_dir = 0;
        random_dir[0] = math_random_float_range(-1.0f,1.0f);
        random_dir[1] = math_random_float_range(-1.0f,1.0f);
        random_dir[2] = math_random_float_range(-1.0f,1.0f);
        *(TI *)burst_vel = *(TI *)random_dir;
        vec_scale_to_length(burst_vel,burst_vel,math_random_float_range(g_spark_params.f[0],g_spark_params.f[1]) * (0.020000001f));
        FastVecScale(spawn_pos,vars,math_random_float_range(g_spark_params.f[2],g_spark_params.f[3]));
        FastVecAdd(burst_vel,burst_vel,spawn_pos);
        vec_scale_to_length(spawn_pos,vars,math_random_float_range(0.0f,1.0f)*speed_len);
        FastVecAdd(spawn_pos,spawn_pos,moby+0x10);
        part_spawn_burst(moby+0x10,burst_vel,((s32)(g_spark_params.i[4]) * 5 + 2) / 6,g_spark_params.i[5],g_spark_params.i[6],g_spark_params.i[7],g_spark_params.f[8],g_spark_params.f[9],g_spark_params.f[10],g_spark_params.f[11],0.0f);
        *(TI *)offset = 0;
        offset[2] = g_spark_params.f[12];
        *(TI *)random_dir = *(TI *)offset;
        matrix_mul_vec3(random_dir,random_dir,moby+0xC0);
        math_apply_axis_rotation_to_quat(random_dir,random_dir,moby+0xC0,math_random_angle());
        if (func_001163B0() & 1)
            part_spawn_trailing_spark(spawn_pos,random_dir,g_spark_params.i[13],g_spark_params.i[14],(float)g_spark_params.i[15],((s32)(g_spark_params.i[16]) * 5 + 2) / 6,g_spark_params.i[17]);
        }
    }
    {
    View request __attribute__((aligned(16)));
    request.p[4] = moby;
    request.i[5] = 0x10001;
    request.f[7] = vars->f[8];
    request.i[8] = 1;
    qcopy(&request,vars);
    vec_scale_to_length(&request,&request,vars->f[9]);
    request.f[3] = 5627.925f;
    request.b[0x18] = vars->b[0x28];
    request.b[0x19] = vars->b[0x2C];
    request.h[0x1A/2] = *(u16 *)(moby+0xAA);
    if (CollLine(moby+0x10,pos,0,vars->i[4],&request) || coll_test_point(0.2f,pos,0,vars->i[4]) || math_fast_float_d(vars->b+0x34)) {
        if (g_tether_l18_hit_result) {
            if (g_tether_l18_hit_result != vars->i[4]) {
                coll_process_hit(moby+0x10,0,vars->i[4],0.5f,&request);
                SpawnExplosionEffects_pal(moby,g_explosion_effect_desc,0,0.0f,0.0f,0,2,10,0.0f,0.0f,9.0f,0.666f,0,0.0f,0,1,-1,0,0x810001);
                moby_mark_spawned(moby);
                return;
            }
        } else {
            SpawnExplosionEffects_pal(moby,g_explosion_effect_desc,0,0.0f,0.0f,0,2,8,0.0f,0.0f,9.0f,0.5f,0,0.0f,0,1,-1,0,0x810001);
            moby_mark_spawned(moby);
            return;
        }
    }
    }
    qcopy(moby+0x10,pos);
}

