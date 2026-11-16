#include "common.h"

/* func_L17_003C7C70 has a unit of its own: it needs -G8 for its $gp tuning values and -g,
   which gives the nop pairs retail has before each division, and its jump table is this
   unit's only .rodata. */

/* The tuning value the first rate divides by is read-only here: as const its load carries no
   anti-dependences on the flag stores, so sched1 issues it after the 360.0f numerator, which
   lengthens that constant's life and leaves $f20 to the scale constant, as in retail. */
extern const float g_tilt_platform_period __attribute__((sda));
extern float g_tilt_platform_amplitude __attribute__((sda));
extern float g_tilt_platform_sway_amp __attribute__((sda));
extern float g_tilt_platform_sway_period __attribute__((sda));
extern float g_tilt_platform_tilt_period __attribute__((sda));
extern float g_tilt_platform_hold_seconds __attribute__((sda));
extern float g_tilt_platform_tilt_seconds __attribute__((sda));
extern float g_tilt_platform_return_seconds __attribute__((sda));
extern float g_tilt_platform_scale_a __attribute__((sda));
extern float g_tilt_platform_drop_height __attribute__((sda));
extern void math_update_wrapped_angle_offset(void *,void *,void *,float,float,float),moby_scale_owner_words_by_angles(void *,void *,void *,float,float,float);
extern int hero_is_current_selected_id(void *),flag_set_first_pending(void *),math_fast_float_d(void *),FloatToInt(float);
extern void moby_set_state(void *,int,int);
extern int PlayMobySound(int,int,void *);
extern float IntToFloat(int),math_wrap_angle_to_pi(float),math_fast_sin_or_cos_b(float),math_fast_sin_or_cos_a(float),FastAddRotations(float,float),math_fast_float_g(float);
extern void FastVecSub(void *,void *,void *),mat_combine_and_store(void *,void *,void *,void *);
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } UpdateVector;
typedef struct {
    u8 pad00[0x3e];
    u16 flags3e;
    u8 pad40[0x4c];
    int flags8c;
    UpdateVector origin;
    float a0, a4, a8, ac;
    int b0, b4, b8;
} UpdateState;
typedef struct {
    u8 pad00[0x10];
    UpdateVector position;
    u8 mode;
    u8 pad21[0x13];
    u16 flags34;
    u8 pad36[0x32];
    UpdateState *state;
    u8 pad6c[0x84];
    UpdateVector rotation;
} UpdateObject;
/* Moves a tilting platform: it waits for a trigger, wobbles, tips over along an arc, then
   swings back up to where it started (moby class 2359). */
void tilting_platform_update(UpdateObject *moby)
{
    float oldpos[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float oldrot[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    UpdateState *vars;
    float first_rate;
    float rate_scale = 0.000290888245f;
    first_rate=360.0f/g_tilt_platform_period;
    *(Quad *)oldpos=moby->position.q;
    *(Quad *)oldrot=moby->rotation.q;
    vars=moby->state;
    vars->flags8c|=1;
    vars->flags3e|=8;
    moby->flags34|=0x20;
    math_update_wrapped_angle_offset(moby,&vars->a0,&vars->a4,g_tilt_platform_amplitude,first_rate*rate_scale,-1.0f);
    moby_scale_owner_words_by_angles(moby,&vars->a8,&vars->ac,g_tilt_platform_sway_amp,(360.0f/g_tilt_platform_sway_period)*rate_scale,(360.0f/g_tilt_platform_tilt_period)*rate_scale);
    switch(moby->mode) {
    case 0:
        vars->origin.q=*(Quad *)oldpos;
        moby->mode=1;
        break;
    case 1:
        if(hero_is_current_selected_id(moby)) {
            moby_set_state(moby,2,-1);
            vars->b0=FloatToInt(g_tilt_platform_hold_seconds*60.0f);
        }
        break;
    case 2: {
        float progress;
        if(flag_set_first_pending(moby))PlayMobySound(0,0,moby);
        if(vars->b0==60)PlayMobySound(0,0,moby);
        if(math_fast_float_d(&vars->b0)) {
            vars->b4=FloatToInt(g_tilt_platform_tilt_seconds*60.0f);
            moby->mode=3;
        } else {
            rot[0]=math_fast_sin_or_cos_b(math_wrap_angle_to_pi(IntToFloat(vars->b0)*0.75f))*0.017453294f;
            rot[1]=math_fast_sin_or_cos_a(math_wrap_angle_to_pi(IntToFloat(vars->b0)*0.89f))*0.017453294f;
            if((float)vars->b4>g_tilt_platform_hold_seconds*60.0f-30.0f) {
                progress=IntToFloat(vars->b0)/(g_tilt_platform_hold_seconds*60.0f-30.0f);
                moby->rotation.f[0]=moby->rotation.f[0]*progress+rot[0]*(1.0f-progress);
                moby->rotation.f[1]=moby->rotation.f[1]*progress+rot[1]*(1.0f-progress);
            } else {
                moby->rotation.f[1]=rot[1];
                moby->rotation.f[0]=rot[0];
            }
        }
        break;
    }
    case 3: {
        float progress,f,b,ax,ay;
        progress=IntToFloat(vars->b4)/(g_tilt_platform_tilt_seconds*60.0f);
        f=(1.0f-progress)*g_tilt_platform_scale_a;
        moby->rotation.f[1]=0;
        moby->rotation.f[0]=(1.0f-progress)*1.57079649f;
        ax=math_fast_sin_or_cos_a(FastAddRotations(1.57079649f,moby->rotation.f[2]));
        b=math_fast_sin_or_cos_b(moby->rotation.f[0]);
        ax*=f*b;
        moby->position.f[0]=ax;
        ay=math_fast_sin_or_cos_b(FastAddRotations(1.57079649f,moby->rotation.f[2]));
        b=math_fast_sin_or_cos_b(moby->rotation.f[0]);
        ay*=f*b;
        moby->position.f[1]=ay;
        moby->position.f[2]=0;
        moby->position.f[0]+=vars->origin.f[0];
        ay+=vars->origin.f[1];
        moby->position.f[1]=ay;
        f*=math_fast_sin_or_cos_a(moby->rotation.f[0]);
        moby->position.f[2]=vars->origin.f[2]-f;
        moby->position.f[2]-=math_fast_sin_or_cos_a(progress*1.57079649f)*g_tilt_platform_drop_height;
        vars->flags8c&=~1;
        vars->flags3e&=~8;
        moby->flags34&=~0x20;
        if(math_fast_float_d(&vars->b4)) {
            moby->mode=4;
            vars->b8=FloatToInt(g_tilt_platform_return_seconds*60.0f);
        }
        break;
    }
    case 4: {
        float progress,f,b,c,ax,ay;
        progress=IntToFloat(vars->b8)/(g_tilt_platform_return_seconds*60.0f);
        *(Quad *)rot=moby->rotation.q;
        c=1.0f-progress;
        f=(1.0f-c)*g_tilt_platform_scale_a;
        moby->rotation.f[0]=math_fast_float_g((rot[0]*c+c*4.71238947f)+1.57079649f);
        moby->rotation.f[1]=rot[1]*c;
        ax=math_fast_sin_or_cos_a(FastAddRotations(1.57079649f,moby->rotation.f[2]));
        b=math_fast_sin_or_cos_b(moby->rotation.f[0]);
        ax*=f*b;
        moby->position.f[0]=ax;
        ay=math_fast_sin_or_cos_b(FastAddRotations(1.57079649f,moby->rotation.f[2]));
        b=math_fast_sin_or_cos_b(moby->rotation.f[0]);
        ay*=f*b;
        moby->position.f[1]=ay;
        moby->position.f[2]=0;
        moby->position.f[0]+=vars->origin.f[0];
        ay+=vars->origin.f[1];
        moby->position.f[1]=ay;
        f*=math_fast_sin_or_cos_a(moby->rotation.f[0]);
        moby->position.f[2]=vars->origin.f[2]-f;
        moby->position.f[2]-=math_fast_sin_or_cos_a(c*1.57079649f)*g_tilt_platform_drop_height;
        vars->flags8c&=~1;
        vars->flags3e&=~8;
        moby->flags34&=~0x20;
        if(math_fast_float_d(&vars->b8)) {
            moby->mode=1;
            {
                Quad home = vars->origin.q;
                moby->rotation.q=*(Quad *)rot;
                moby->position.q=home;
            }
        }
        break;
    }
    }
    if(moby->mode<3) {
        FastVecSub(pos,&moby->position,oldpos);
        mat_combine_and_store((u8 *)vars+0x50,pos,oldrot,&moby->rotation);
    }
}
