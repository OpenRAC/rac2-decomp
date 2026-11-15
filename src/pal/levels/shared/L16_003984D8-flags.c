#include "include_asm.h"

#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 difference, local, previous, velocity, lateral; } MotionWorkspace;
extern char g_hero_state[];
extern float D_L16_001AF43C __attribute__((sda));
extern void hero_resolve_stick_direction(int,float);
extern void FastVecSub(void *,void *,void *);
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void vec_transform_by_object_or_given(char *,char *,char *,char *);
extern void vec_fast_normalize_helper(void *,void *,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern float FastVecDot(void *,void *);
extern float ApproachValue(float *,float,float);
extern void FastVecAdd(void *,void *,void *);
extern void mem_fast_helper_b(void *,int);
extern void vec_clamp_length(float *,float);

void func_PAL_L16_00398C40(char *object)
{
    MotionWorkspace local;
    char *state=*(char **)(object+0x68);
    float alignment;
    hero_resolve_stick_direction(0,1.0f);
    qcopy(&local.previous,(g_hero_state+0x190));
    FastVecSub(&local.difference,g_hero_state+0x80,object+0x10);
    FastVecCross((g_hero_state+0x190),&local.difference,object+0xe0);
    vec_scale_to_length((g_hero_state+0x190),(g_hero_state+0x190),1.0f);
    vec_transform_by_object_or_given(object,(char *)&local.local,(char *)&local.difference,0);
    vec_fast_normalize_helper(&local.velocity,&local.local,D_L16_001AF43C);
    matrix_mul_vec3(&local.velocity,&local.velocity,object+0xc0);
    alignment=FastVecDot(&local.previous,(g_hero_state+0x190));
    if (*(float *)(g_hero_state+0x24b8)>0.5f && alignment>0.5f)
        ApproachValue((float *)(state+0x30),alignment*0.10000001f,0.002f);
    else ApproachValue((float *)(state+0x30),0.0f,0.002f);
    if (*(float *)(state+0x30)!=0.0f) {
        vec_scale_to_length(&local.lateral,(g_hero_state+0x190),*(float *)(state+0x30));
        FastVecAdd(&local.velocity,&local.velocity,&local.lateral);
        *(float *)(state+0x34)+=*(float *)(state+0x30)/(*(float *)(state+8)*6.28318548f);
        if (*(float *)(state+0x34)>1.0f) *(float *)(state+0x34)=1.0f;
    }
    FastVecAdd(&local.velocity,&local.velocity,object+0x10);
    mem_fast_helper_b(g_hero_state+0xf0,0xa0);
    FastVecSub(g_hero_state+0xf0,&local.velocity,g_hero_state+0x80);
    vec_clamp_length((float *)(g_hero_state+0xf0),0.120000005f);
}
