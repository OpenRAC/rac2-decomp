#include "include_asm.h"

#include "common.h"
extern int D_L00_001AA374 __attribute__((sda));
extern int g_frame_l00_counter;
extern int D_L00_001B208C;
extern int ref_L00_0032A258_00 __attribute__((sda));
extern void func_PAL_L00_003281C0(void *,int,float);
extern void moby_get_anim_entry_count(void *,int *,int *);
extern int PlayMobySound(int,int,void *);
extern float math_random_float_range(float,float);
extern float math_random_signed_float_range(float,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void *func_PAL_002735D0(void *,int,int,int,void *,void *,void *,int,float,float);
extern void STUB_printf(void *);
extern char D_L00_001AA380[];

void func_PAL_L00_0032C328(unsigned char *object,float *range,float *scale,float *lifetime,int kinds,int sound,int skip,int flags,int mask,unsigned char alpha,void *callback)
{
    float velocity[4], life, size;
    int first,count,i;
    unsigned char *particle;
    if(D_L00_001AA374 != g_frame_l00_counter) {
        D_L00_001AA374=g_frame_l00_counter;
        D_L00_001B208C=0;
    }
    ref_L00_0032A258_00=D_L00_001B208C+1;
    if(!object) return;
    *(short *)(object+0x7c)=0;
    *(int *)(object+0x98)=0;
    if((flags ^ 1)&1) func_PAL_L00_003281C0(object,1,0.0f);
    if(flags&16) func_PAL_L00_003281C0(object,9,0.0f);
    else if(flags&32) func_PAL_L00_003281C0(object,2,0.0f);
    moby_get_anim_entry_count(object,&first,&count);
    if(sound!=-1) PlayMobySound(sound,0,object);
    for(i=0;i<count;++i) {
        if(skip==i || (((mask>>i)^1)&1)) continue;
        life=math_random_float_range(lifetime[0],lifetime[1]);
        size=math_random_float_range(scale[0],scale[1]);
        if(flags&2) velocity[0]=math_random_signed_float_range(range[0],range[4])*0.020000001f;
        else velocity[0]=math_random_float_range(range[0],range[4])*0.020000001f;
        if(flags&4) velocity[1]=math_random_signed_float_range(range[1],range[5])*0.020000001f;
        else velocity[1]=math_random_float_range(range[1],range[5])*0.020000001f;
        velocity[2]=math_random_float_range(range[2],range[6])*0.020000001f;
        if(!(flags&8)) matrix_mul_vec3(velocity,velocity,object+0xc0);
        if((kinds>>i)&1)
            particle=func_PAL_002735D0(object,2,*(short *)(object+0xaa),i,object+0x10,object+0xf0,velocity,alpha,size,life);
        else particle=func_PAL_002735D0(object,1,*(short *)(object+0xaa),i,object+0x10,object+0xf0,velocity,alpha,size,life);
        if(particle) { if(callback) *(void **)(particle+0x64)=callback; }
        else STUB_printf(D_L00_001AA380);
    }
}
