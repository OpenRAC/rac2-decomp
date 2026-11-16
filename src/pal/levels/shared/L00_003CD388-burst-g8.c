#include "names.h"
/* func_PAL_L00_003CD388, the PAL copy of func_L00_003C94D8: the same C at 50 Hz, where the speeds
 * and rates scale by 6/5 and the count by 5/6.  A unit of its own for -fno-sched-interblock (retail
 * has no interblock motion in the first loop).  tailW has a lifetime of more than one insn, so
 * loop.c hoists it on its first pass; the 0.05f and 0.5f stores then fit the second pass's
 * threshold.  The second loop counts up: loop.c reverses it, and the reversed counter's 9 lands
 * after the hoisted divisor 6, which is retail's order. */
#include "common.h"
typedef int BurstQuad __attribute__((mode(TI)));
typedef struct { float x,y,z,w; } BurstVec __attribute__((aligned(16)));
extern char g_hero_matrix[] NOT_SDA;
typedef struct { char pad[0x110]; BurstVec velocity; char gap[0x220]; int active; } BurstResident;
extern BurstResident g_hero_state NOT_SDA;
typedef struct { char pad[0x16C]; unsigned char *burstColors; } BurstTables;
extern BurstTables g_effect_definitions;
extern float g_muzzle_burst_rotation_degrees __attribute__((sda));
extern float g_muzzle_burst_jitter __attribute__((sda));
extern int g_muzzle_burst_count __attribute__((sda));
extern int g_muzzle_burst_kind __attribute__((sda));
extern float g_muzzle_burst_param __attribute__((sda));
extern float g_muzzle_burst_speed_min __attribute__((sda));
extern float g_muzzle_burst_speed_max __attribute__((sda));
extern float g_muzzle_burst_life_min __attribute__((sda));
extern float g_muzzle_burst_life_max __attribute__((sda));
extern float g_muzzle_burst_size __attribute__((sda));
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern float math_random_float_range(float,float);
extern float FastAddRotations(float,float);
extern void FastVecScale(void *,void *,float);
typedef struct { int kind, color, pad08, color2; BurstVec position, previous, velocity; } BurstParticle;
extern BurstParticle *part_spawn_streak_effect(void *,void *);
extern float math_fabs(float);
extern void math_build_axis_angle_quat(void *,void *,float);
extern void vec_rotate_by_quaternion(void *,void *,void *);
extern float math_random_signed_float_range(float,float);
extern int FloatToInt(float);
extern void FastVecSub(void *,void *,void *);
extern char *part_spawn_burst_pal(void *,void *,int,int,int,int,float,float,float,float,float);
void weapon_spawn_muzzle_burst_pal(char *object)
{
    BurstVec matrix, start, saved, position, velocity, local, temp, offset;
    float angle, speed, life;
    int i, kind, mode;

    *(BurstQuad *)&local = 0;
    *(BurstQuad *)&saved = 0;
    saved.x=0.3f; saved.y=-1.0f; saved.w=1.0f;
    local.x=0.513f; local.y=-1.0f; local.z=0.183f; local.w=1.0f;
    matrix_mul_vec3(&local,&local,object+0xC0);
    FastVecAdd(&position,object+0x10,&local);
    angle=0.0f;
    object[0xBC]=5;
    math_apply_axis_rotation_to_quat(&saved,g_hero_matrix,g_hero_matrix+0x10,0.3490659f);
    qcopy(&start,&saved);
    for(i=0;i<10;i++) {
        BurstParticle *p;
        angle=FastAddRotations(angle,math_random_float_range(0.0f,0.6283186f));
        speed=math_random_float_range(0.120000005f,0.36f);
        FastVecScale(&velocity,&start,speed);
        p=part_spawn_streak_effect(&position,&velocity);
        if(p) {
            BurstVec *tail;
            float tailW;
            FastVecScale(&velocity,&start,0.75f);
            tail = &p->velocity;
            tailW = 2.0f;
            FastVecAdd(&p->position,&position,&velocity);
            qcopy_nc(&p->previous,&position);
            tail->w=tailW;
            p->position.w=0.05f;
            p->previous.w=0.5f;
            p->color=0x307F7F7F;
            p->color2=0x307F7F7F;
        }
        if(math_fabs(angle)>0.00001f) {
            math_build_axis_angle_quat(&matrix,g_hero_matrix,angle);
            vec_rotate_by_quaternion(&start,&saved,&matrix);
        }
    }
    math_apply_axis_rotation_to_quat(&saved,g_hero_matrix,g_hero_matrix+0x10,g_muzzle_burst_rotation_degrees*0.017453294f);
    angle=0.0f;
    qcopy(&start,&saved);
    qzero_nc(&offset);
    if(g_hero_state.active) FastVecScale(&offset,&g_hero_state.velocity,1.7f);
    for(i=0;i<10;i++) {
        char *p;
        angle=FastAddRotations(angle,math_random_float_range(0.0f,0.6283186f));
        speed=math_random_float_range(g_muzzle_burst_speed_min*0.020000001f,g_muzzle_burst_speed_max*0.020000001f);
        FastVecScale(&velocity,&start,speed);
        FastVecAdd(&velocity,&velocity,&offset);
        kind=((int)(g_muzzle_burst_kind) * 5 + 2) / 6;
        mode=FloatToInt(math_random_signed_float_range(1.0f,2.0f));
        temp.x=position.x+math_random_signed_float_range(0.0f,g_muzzle_burst_jitter);
        temp.y=position.y+math_random_signed_float_range(0.0f,g_muzzle_burst_jitter);
        temp.z=position.z+math_random_signed_float_range(0.0f,g_muzzle_burst_jitter);
        life=math_random_float_range(g_muzzle_burst_life_min,g_muzzle_burst_life_max)*210000.0f;
        FastVecSub(&temp,&temp,&velocity);
        p=part_spawn_burst_pal(&temp,&velocity,kind,g_muzzle_burst_count,0x505050,mode,life,g_muzzle_burst_size,g_muzzle_burst_param,0.0f,0.0f);
        if(p) p[2]=g_effect_definitions.burstColors[1];
        if(math_fabs(angle)>0.00001f) {
            math_build_axis_angle_quat(&matrix,g_hero_matrix,angle);
            vec_rotate_by_quaternion(&start,&saved,&matrix);
        }
    }
}
