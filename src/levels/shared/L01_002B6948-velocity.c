#include "common.h"

typedef int VelocityQuad __attribute__((mode(TI)));

typedef struct {
    unsigned char pad0[240];
    float xf0;
    float xf4;
    float xf8;
    unsigned char padfc[120];
    float x174;
    float x178;
    unsigned char pad17c[36];
    float x1a0;
    unsigned char pad1a4[12];
    float x1b0;
    float x1b4;
    unsigned char pad1b8[207];
    unsigned char x287;
    unsigned char pad288[194];
    short x34a;
    unsigned char pad34c[472];
    short x524;
    unsigned char pad526[3886];
    short x1454;
    unsigned char pad1456[3646];
    int x2294;
    unsigned char pad2298[4];
    int x229c;
    unsigned char pad22a0[35];
    unsigned char x22c3;
} PlayerVelocityState;
extern PlayerVelocityState g_hero_state;
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float vec_length_xy(void *);
extern float cam_get_view_space_vector_length(void *);
extern float FastVecDot(void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void vec_fast_normalize_helper(void *,void *,float);
extern void vec_scale_to_length(void *,void *,float);
extern void cam_set_view_space_height(void *,void *,float);
extern void cam_set_view_space_vector_length(void *,void *,float);
extern float hero_get_speed_along_forward(void *);

/* Approach the requested velocity, increasing acceleration when reversing direction. */
void hero_approach_velocity(float rate) {
    float targetVelocity[4] __attribute__((aligned(16)));
    float sourceVec[4] __attribute__((aligned(16)));
    float currentDir[4] __attribute__((aligned(16)));
    float angle,speed,alignment,targetLength,currentLength;
    switch(g_hero_state.x22c3) {
    case 0:
        angle=g_hero_state.x1a0;speed=g_hero_state.x1b0;
        if(g_hero_state.x229c==4 && g_hero_state.x524 && g_hero_state.x287) speed=0.0833333358f;
        if(g_hero_state.x34a && g_hero_state.x2294==14 && speed>0.0166666675f) speed=0.0166666675f;
        targetVelocity[0]=math_fast_sin_or_cos_a(angle)*speed;
        targetVelocity[1]=math_fast_sin_or_cos_b(angle)*speed;
        targetVelocity[2]=g_hero_state.xf8;
        alignment=-(g_hero_state.xf0*targetVelocity[0]+g_hero_state.xf4*targetVelocity[1]);
        targetLength=vec_length_xy(targetVelocity);currentLength=vec_length_xy((char *)&g_hero_state+0xf0);
        if(targetLength==0.0f || currentLength==0.0f) alignment=0.0f;
        else {
            alignment/=targetLength;
            alignment/=currentLength;
        }
        alignment+=1.0f;
        alignment*=1.5f;
        if(alignment>3.0f) alignment=3.0f;
        if(alignment<1.0f) alignment=1.0f;
        rate*=alignment;
        FastVecSub(targetVelocity,targetVelocity,(char *)&g_hero_state+0xf0);
        if(vec_length_xy(targetVelocity)>rate) vec_fast_normalize_helper(targetVelocity,targetVelocity,rate);
        FastVecAdd((char *)&g_hero_state+0xf0,(char *)&g_hero_state+0xf0,targetVelocity);
        *(VelocityQuad *)sourceVec=*(VelocityQuad *)((char *)&g_hero_state+0xa60);
        g_hero_state.x1b4=g_hero_state.x178-hero_get_speed_along_forward(sourceVec);
        if(g_hero_state.x1454) g_hero_state.x1b4=g_hero_state.x174;
        break;
    case 1:case 2:
        *(VelocityQuad *)sourceVec=*(VelocityQuad *)((char *)&g_hero_state+0x190);speed=g_hero_state.x1b0;
        cam_set_view_space_height(targetVelocity,sourceVec,0.0f);
        vec_scale_to_length(targetVelocity,targetVelocity,speed);
        cam_set_view_space_height(currentDir,(char *)&g_hero_state+0xf0,0.0f);
        alignment=-FastVecDot(currentDir,targetVelocity);
        targetLength=cam_get_view_space_vector_length(targetVelocity);currentLength=cam_get_view_space_vector_length((char *)&g_hero_state+0xf0);
        if(targetLength==0.0f || currentLength==0.0f) alignment=0.0f;
        else {
            alignment/=targetLength;
            alignment/=currentLength;
        }
        alignment+=1.0f;
        alignment*=1.5f;
        if(alignment>3.0f) alignment=3.0f;
        if(alignment<1.0f) alignment=1.0f;
        rate*=alignment;
        FastVecSub(targetVelocity,targetVelocity,(char *)&g_hero_state+0xf0);
        cam_set_view_space_height(targetVelocity,targetVelocity,0.0f);
        if(cam_get_view_space_vector_length(targetVelocity)>rate) cam_set_view_space_vector_length(targetVelocity,targetVelocity,rate);
        FastVecAdd((char *)&g_hero_state+0xf0,(char *)&g_hero_state+0xf0,targetVelocity);
        g_hero_state.x1b4=g_hero_state.x178;
        if(g_hero_state.x1454) g_hero_state.x1b4=g_hero_state.x174;
        break;
    }
}
