#include "include_asm.h"

#include "common.h"
extern void func_PAL_L07_003E9908(void *);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern float func_PAL_L07_003E9B60(void *,void *,float,float);
extern float math_random_signed_float_range(float,float);
extern int coll_sweep_from_object(void *,void *,float,float,float,int,int,int,int);
extern float FastVecLength(void *);
extern void vec_clamp_length(void *,float);
extern void func_PAL_L07_003EA1F8(void *);
extern float math_step_value_toward_target(void *,float,void *,float,float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void entity_tick_timers(void *);
extern float D_L07_001B0A88 __attribute__((sda));
extern float D_L07_001B0A8C __attribute__((sda));
extern float D_L07_001B0A90 __attribute__((sda));
extern float D_L07_001B0A94 __attribute__((sda));
extern float D_L07_001B0A98[] __attribute__((sda));
struct PlayerState1310 { char pad[0x229C]; int state; char pad2[0x1FC]; void *target; };
extern struct PlayerState1310 g_hero_state;

/* Advance the entity state machine, movement and recovery scaling. */
void func_PAL_L07_003E93E8(unsigned char *o)
{
    float v[4] __attribute__((aligned(16)));
    float len[2];
    char *p=*(char **)(o+0x68);
    int i;
    func_PAL_L07_003E9908(o);
    switch(o[0x95]) {
    case 0:
        if (*(int *)(p+0x114)==1) moby_set_state(o,5,2);
        break;
    case 2:
        if (*(int *)(p+0x114)!=1) moby_set_state(o,1,0);
        break;
    }
    switch(o[0x20]) {
    case 1:
        if (flag_set_first_pending(o) && o[0x43]) func_PAL_002A7E68(o,0,0,17);
        if (*(char **)(p+0x260)) {
            matrix_mul_vec3(v,p+0x220,*(char **)(p+0x260)+0xC0);
            FastVecAdd(v,v,*(char **)(p+0x260)+0x10);
        } else qcopy(v,p+0x220);
        func_PAL_L07_003E9B60(o,v,0,1);
        break;
    case 3:
        if(flag_set_first_pending(o)) *(float *)(p+0x250)=math_random_signed_float_range(D_L07_001B0A98[0],D_L07_001B0A98[1])*0.01745329424738884f;
        if(func_PAL_L07_003E9B60(o,p+0x100,*(float *)(p+0x250),1)<2) moby_set_state(o,4,-1);
        break;
    case 4:
        if(flag_set_first_pending(o) && o[0x43]!=2) func_PAL_002A7E68(o,2,0,5);
        func_PAL_L07_003E9B60(o,p+0x100,*(float *)(p+0x250),1);
        if(o[0x60]&2) moby_set_state(o,5,-1);
        break;
    case 5:
        if(flag_set_first_pending(o) && o[0x43]!=3) func_PAL_002A7E68(o,3,0,2);
        func_PAL_L07_003E9B60(o,p+0x100,*(float *)(p+0x250),1);
        if(*(unsigned short *)(o+0x96)>8)
            coll_sweep_from_object(o,o+0x10,D_L07_001B0A94,(float)*(unsigned char *)(p+0x34),1,0x4000001,0,1,0);
        if(*(unsigned short *)(o+0x96)>25 &&
            (g_hero_state.state==7 || g_hero_state.state==20) &&
            g_hero_state.target==o) moby_set_state(o,6,-1);
        break;
    case 6:
        if(flag_set_first_pending(o) && o[0x43]!=4) func_PAL_002A7E68(o,4,0,1);
        if(o[0x60]&2) moby_set_state(o,5,-1);
        break;
    case 9: {
        float tolerance=0.10000001f;
        FastVecSub(v,p+0x230,o+0x10);
        if(FastVecLength(v)>tolerance) vec_clamp_length(v,tolerance);
        else moby_set_state(o,10,-1);
        FastVecAdd(o+0x10,o+0x10,v);
        func_PAL_L07_003EA1F8(o);
        break;
    }
    case 10:
        if(flag_set_first_pending(o)) *(int *)(o+0x98)=*(int *)(*(char **)(o+0x24)+0x10);
        len[1]=FastVecLength(o+0xC0);
        len[0]=FastVecLength(o+0xE0);
        {
            float a=D_L07_001B0A88*0.00040000002f;
            float b=D_L07_001B0A8C*0.020000001f;
            math_step_value_toward_target(&len[0],1,p+0x254,a,a,b);
            if(len[0]>D_L07_001B0A90) math_step_value_toward_target(&len[1],1,p+0x258,a,a,b);
        }
        for(i=0;i<2;i++) vec_scale_to_length(o+0xC0+i*16,o+0xC0+i*16,len[1]);
        vec_scale_to_length(o+0xE0,o+0xE0,len[0]);
        if(len[1]>=1) {
            for(i=0;i<3;i++) vec_scale_to_length(o+0xC0+i*16,o+0xC0+i*16,1);
            moby_set_state(o,3,2);
        }
        func_PAL_L07_003EA1F8(o);
        break;
    }
    entity_tick_timers(o);
}
