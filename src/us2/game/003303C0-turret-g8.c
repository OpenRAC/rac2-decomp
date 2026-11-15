#include "common.h"

/* func_US2_003303C0, the USA v2.00 copy of func_0032F598: the same C, where the aim
   vectors are pts[2] (pts[0] the hit point, pts[1] the origin) without v1.01's two
   untouched vectors in front of them, so the frame's locals start at sp+0, and the
   charge callee is v2.00's func_US2_002FEDD0. A unit of its own (-O2 -G8 -ffast-math).
   The effect's 0x3C store is written last so the scheduler emits retail's store order. */
typedef union { int q __attribute__((mode(TI))); float f[4]; } V598;
typedef struct __attribute__((packed, aligned(4))) { u64 a; u32 b; } P598;
extern P598 D_001B0988;
typedef struct { char pad[0x1A0]; union { unsigned long long held; unsigned int flags[2]; } buttons; int pressed; } Input598;
extern Input598 g_pad_state;
extern char g_sound_state[];
extern char D_001A8BD0[] MACRO_ADDR;
extern int D_001B095C __attribute__((sda));
extern float D_001B0994 __attribute__((sda)),D_001B0998 __attribute__((sda));
extern void moby_transform_joint_point(void *,int,void *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern char *SelectBestTargetInCone(void *,void *,float,float,void *,int,int,int,float,float,float,int,void *);
extern char *moby_get_private_value_0(void *),*slot_get_by_index(int);
extern void FastVecScale(void *,void *,float),FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *),vec_scale_to_length(void *,void *,float),mat_fast_helper_c(void *,void *),matrix_mul_vec3(void *,void *,void *),vec_clear_128(void *),FastVecCross(void *,void *,void *),mat_get_euler_angles(void *,void *),vec_build_spherical_offset(void *,float,float,float),mat_build_rotation_toward_vector(void *,void *,void *,int,float),mat_transform_via_copy(void *,void *);
extern int func_001163B0(void),PlayMobySound(int,int,void *),coll_trace_projectile_to_impact(void *,void *,void *,void *,void *,int,int,float);
extern float math_random_signed_float_range(float,float),FastAddRotations(float,float),math_random_float_range(float,float),math_fast_sin_or_cos_a(float),math_square(float);
extern void SpawnRandomParticlePairs(void *,void *),part_spawn_flash_puffs(void *,void *,float),snd_stop_voice(int),part_spawn_spark_burst_2(void *,void *);
extern void *moby_spawn_directed(void *,void *,void *), *projectile_create(void *,void *,void *,void *);
extern void func_US2_002FEDD0(void *,void *,void *,float,float,float,float,void *);
#define F598(p,o) (*(float *)((p)+(o)))
#define I598(p,o) (*(int *)((p)+(o)))
#define B598(p,o) (*(unsigned char *)((p)+(o)))
void func_US2_003303C0(char *obj)
{
    V598 pts[2]; /* [0] hit point, [1] origin */
    P598 params;
    V598 angles, matrix[3], work[8];
    int output;
    char *rec=*(char **)(obj+0x68);
    char *target,*effect,*other;
    float a,b,old1,old2;
    moby_transform_joint_to_world(obj,0,&pts[1]);
    params=D_001B0988;
    target=SelectBestTargetInCone(&pts[1],obj+0xC0,6.2831855f,6.2831855f,&output,0,0,0,10.0f,0.0f,0.0f,0,&params);
    if (!(g_pad_state.buttons.flags[0]&0x40)) {
        if (target) {
            qcopy(&pts[0],target+0x10);
            other=moby_get_private_value_0(target);
            if (other) {
                FastVecScale(&angles,target+0xE0,F598(other,0x10));
                FastVecAdd(&pts[0],&angles,target+0x10);
            }
            FastVecSub(rec+0x20,&pts[0],&pts[1]);
            vec_scale_to_length(rec+0x20,rec+0x20,1.0f);
            mat_fast_helper_c(matrix,obj+0xC0);
            matrix_mul_vec3(rec+0x20,rec+0x20,matrix);
        } else if (g_pad_state.buttons.flags[0]&0x80) {
            vec_clear_128(rec+0x20); F598(rec,0x20)=1.0f;
        } else if (func_001163B0()%111==0 && !(g_pad_state.buttons.flags[0]&0x80)) {
            float randomAngle, elevation;
            matrix[0].q=0; matrix[0].f[2]=1.0f;
            qcopy(&work[0],rec+0x10);
            FastVecCross(&work[1],&work[0],matrix);
            vec_scale_to_length(&work[1],&work[1],1.0f);
            FastVecCross(&work[2],&work[1],&work[0]);
            work[3].f[0]=0.0f;work[3].f[1]=0.0f;work[3].f[2]=0.0f;work[3].f[3]=1.0f;
            mat_get_euler_angles(&work[0],&angles);
            randomAngle=FastAddRotations(angles.f[2],math_random_signed_float_range(0.78539824f,1.5707965f));
            elevation = math_random_float_range(0.0f,0.4f);
            vec_build_spherical_offset(rec+0x20,1.0f,randomAngle,elevation);
        }
    }
    if (g_pad_state.buttons.held&0xC0)
        mat_build_rotation_toward_vector(rec+0x10,rec+0x10,rec+0x20,0,0.25f);
    else mat_build_rotation_toward_vector(rec+0x10,rec+0x10,rec+0x20,0,0.125f);
    angles.q=0;angles.f[2]=1.0f;
    qcopy(matrix,rec+0x10);
    FastVecCross(&matrix[1],matrix,&angles);
    vec_scale_to_length(&matrix[1],&matrix[1],1.0f);
    FastVecCross(&matrix[2],&matrix[1],matrix);
    effect=slot_get_by_index(I598(rec,0x6C));
    mat_transform_via_copy(effect+0x10,matrix);
    B598(effect,3)=1;
    F598(effect,0x30)=-7.83249f;
    F598(effect,0x34)=1.9025599238414737e-12f;
    F598(effect,0x38)=10014.4f;
    F598(effect,0xC)=1.0f;
    F598(effect,0x20)=1.0f; F598(effect,0x24)=1.0f; F598(effect,0x28)=1.0f; I598(effect,0x2C)=0;
    F598(effect,0x3C)=1.0f;
    if (g_pad_state.buttons.flags[0]&0x80) {
        a=1.0f-math_square((math_fast_sin_or_cos_a(D_001B0994)+1.0f)*0.5f)*0.5f;
        b=1.0f-math_square((math_fast_sin_or_cos_a(D_001B0998)+1.0f)*0.5f)*0.5f;
        effect=slot_get_by_index(I598(rec,0x70));
        other=slot_get_by_index(I598(rec,0x74));
        old1=D_001B0994; old2=D_001B0998;
        F598(effect,0x20)=a; F598(other,0x20)=b;
        D_001B0994=FastAddRotations(old1,0.36651918292045593f);
        D_001B0998=FastAddRotations(D_001B0998,0.36651918292045593f);
        if (old1<0.0f && D_001B0994>=0.0f) {
            moby_transform_joint_to_world(obj,2,&work[0]);
            moby_transform_joint_point(obj,2,&work[4]);
            if (target) {
                FastVecSub(&work[1],&pts[0],&work[0]);
                vec_scale_to_length(&work[1],&work[1],0.25f);
            } else vec_scale_to_length(&work[1],&work[4],0.25f);
            PlayMobySound(6,0,obj);
            SpawnRandomParticlePairs(&work[0],&work[1]);
            moby_spawn_directed(obj,&work[0],&work[1]);
        } else if (old2<0.0f && D_001B0998>=0.0f) {
            moby_transform_joint_to_world(obj,1,&work[0]);
            moby_transform_joint_point(obj,1,&work[1]);
            if (target) {
                FastVecSub(&work[5],&pts[0],&work[0]);
                vec_scale_to_length(&work[5],&work[5],0.25f);
            } else vec_scale_to_length(&work[5],&work[1],0.25f);
            PlayMobySound(6,0,obj);
            SpawnRandomParticlePairs(&work[0],&work[5]);
            moby_spawn_directed(obj,&work[0],&work[5]);
        }
    } else if (g_pad_state.buttons.flags[0]&0x40) {
        float charge;
        char *slot;
        moby_transform_joint_to_world(obj,2,&work[0]);
        moby_transform_joint_to_world(obj,1,&work[1]);
        FastVecAdd(&work[2],&work[0],&work[1]);
        FastVecScale(&work[2],&work[2],0.5f);
        func_US2_002FEDD0(rec,&work[2],0,1.75f,F598(rec,0x7C),0.10000001f,0.00083333335f,obj);
        I598(rec,0x78)=coll_trace_projectile_to_impact(&work[2],rec,rec+0x30,rec+0x40,obj,0,0,0.00083333335f);
        charge=F598(rec,0x7C)+0.065f;
        charge = charge < 6.0f ? charge : 6.0f;
        F598(rec,0x7C)=charge;
        part_spawn_flash_puffs(&work[2],D_001A8BD0,charge);
        slot=g_sound_state+D_001B095C*0x70;
        if (I598(slot,0x88)!=(int)obj || !B598(slot,0x74)) D_001B095C=PlayMobySound(4,4,obj);
        vec_scale_to_length(rec+0x20,rec,1.0f);
        mat_fast_helper_c(&work[3],obj+0xC0);
        matrix_mul_vec3(rec+0x20,rec+0x20,&work[3]);
    }

    if (g_pad_state.pressed&0x40) {
        if (D_001B095C!=-1) {
            char *slot=g_sound_state+D_001B095C*0x70;
            if (I598(slot,0x88)==(int)obj && B598(slot,0x74)) snd_stop_voice(D_001B095C);
        }
        D_001B095C=-1;
        PlayMobySound(8,0,obj);
        moby_transform_joint_to_world(obj,2,&work[0]);
        moby_transform_joint_to_world(obj,1,&work[1]);
        FastVecAdd(&work[2],&work[0],&work[1]);
        FastVecScale(&work[2],&work[2],0.5f);
        I598(rec,0x78)=0;F598(rec,0x7C)=1.75f;
        part_spawn_spark_burst_2(&work[2],rec);
        projectile_create(obj,&work[0],&work[1],rec);
    }
}
