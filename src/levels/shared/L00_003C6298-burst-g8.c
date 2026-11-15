/* func_L00_003C94D8: a unit of its own for -fno-sched-interblock (retail has no interblock
 * motion in the first loop).  tailW has a lifetime of more than one insn, so loop.c hoists it
 * on its first pass; the 0.05f and 0.5f stores then fit the second pass's threshold. */
#include "common.h"
typedef int BurstQuad __attribute__((mode(TI)));
typedef struct { float x,y,z,w; } BurstVec __attribute__((aligned(16)));
extern char D_0018A550[] NOT_SDA;
typedef struct { char pad[0x110]; BurstVec velocity; char gap[0x220]; int active; } BurstResident;
extern BurstResident g_hero_state NOT_SDA;
typedef struct { char pad[0x16C]; unsigned char *burstColors; } BurstTables;
extern BurstTables D_L00_001FE940;
extern float D_L00_001B00FC __attribute__((sda));
extern float D_L00_001B0100 __attribute__((sda));
extern int D_L00_001B0104 __attribute__((sda));
extern int D_L00_001B010C __attribute__((sda));
extern float D_L00_001B0110 __attribute__((sda));
extern float D_L00_001B0114 __attribute__((sda));
extern float D_L00_001B0118 __attribute__((sda));
extern float D_L00_001B011C __attribute__((sda));
extern float D_L00_001B0120 __attribute__((sda));
extern float D_L00_001B0124 __attribute__((sda));
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
extern char *part_spawn_burst(void *,void *,int,int,int,int,float,float,float,float,float);
/* Spawns a burst of ten shots and ten sparks in a cone from the muzzle of the weapon. */
void weapon_spawn_muzzle_burst(char *object)
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
    object[0xBC]=6;
    math_apply_axis_rotation_to_quat(&saved,D_0018A550,D_0018A550+0x10,0.3490659f);
    qcopy(&start,&saved);
    for(i=0;i<10;i++) {
        BurstParticle *p;
        angle=FastAddRotations(angle,math_random_float_range(0.0f,0.6283186f));
        speed=math_random_float_range(0.10000001f,0.3f);
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
            math_build_axis_angle_quat(&matrix,D_0018A550,angle);
            vec_rotate_by_quaternion(&start,&saved,&matrix);
        }
    }
    math_apply_axis_rotation_to_quat(&saved,D_0018A550,D_0018A550+0x10,D_L00_001B00FC*0.017453294f);
    angle=0.0f;
    qcopy(&start,&saved);
    qzero_nc(&offset);
    if(g_hero_state.active) FastVecScale(&offset,&g_hero_state.velocity,1.7f);
    for(i=9;i>=0;i--) {
        char *p;
        angle=FastAddRotations(angle,math_random_float_range(0.0f,0.6283186f));
        speed=math_random_float_range(D_L00_001B0114*0.016666668f,D_L00_001B0118*0.016666668f);
        FastVecScale(&velocity,&start,speed);
        FastVecAdd(&velocity,&velocity,&offset);
        kind=D_L00_001B010C;
        mode=FloatToInt(math_random_signed_float_range(1.0f,2.0f));
        temp.x=position.x+math_random_signed_float_range(0.0f,D_L00_001B0100);
        temp.y=position.y+math_random_signed_float_range(0.0f,D_L00_001B0100);
        temp.z=position.z+math_random_signed_float_range(0.0f,D_L00_001B0100);
        life=math_random_float_range(D_L00_001B011C,D_L00_001B0120)*210000.0f;
        FastVecSub(&temp,&temp,&velocity);
        p=part_spawn_burst(&temp,&velocity,kind,D_L00_001B0104,0x505050,mode,life,D_L00_001B0124,D_L00_001B0110,0.0f,0.0f);
        if(p) p[2]=D_L00_001FE940.burstColors[1];
        if(math_fabs(angle)>0.00001f) {
            math_build_axis_angle_quat(&matrix,D_0018A550,angle);
            vec_rotate_by_quaternion(&start,&saved,&matrix);
        }
    }
}
