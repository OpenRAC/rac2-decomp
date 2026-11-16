#include "common.h"

/* func_PAL_L17_003CBDF4, the PAL copy of func_L17_003C7C70: the same C at 50 Hz. It has a unit of its own: it needs -G8 for its $gp tuning values and -g,
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
    float angle_a, angle_b, sway_angle_a, sway_angle_b;
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
/* Tilting platform (PAL: 50 Hz timings): bobs and sways, and once the player stands on it,
   shakes, then tilts over and drops away, and finally swings back to its place. */
void tilting_platform_update_pal(UpdateObject *obj)
{
    float oldpos[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float oldrot[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    UpdateState *state;
    float first_rate;
    float rate_scale = 0.0003490659f;
    first_rate=360.0f/g_tilt_platform_period;
    *(Quad *)oldpos=obj->position.q;
    *(Quad *)oldrot=obj->rotation.q;
    state=obj->state;
    state->flags8c|=1;
    state->flags3e|=8;
    obj->flags34|=0x20;
    math_update_wrapped_angle_offset(obj,&state->angle_a,&state->angle_b,g_tilt_platform_amplitude,first_rate*rate_scale,-1.0f);
    moby_scale_owner_words_by_angles(obj,&state->sway_angle_a,&state->sway_angle_b,g_tilt_platform_sway_amp,(360.0f/g_tilt_platform_sway_period)*rate_scale,(360.0f/g_tilt_platform_tilt_period)*rate_scale);
    switch(obj->mode) {
    case 0:
        state->origin.q=*(Quad *)oldpos;
        obj->mode=1;
        break;
    case 1:
        if(hero_is_current_selected_id(obj)) {
            moby_set_state(obj,2,-1);
            state->b0=FloatToInt((g_tilt_platform_hold_seconds*300.0f+2.0f)*0.16666667f);
        }
        break;
    case 2: {
        float t;
        if(flag_set_first_pending(obj))PlayMobySound(0,0,obj);
        if(state->b0==50)PlayMobySound(0,0,obj);
        if(math_fast_float_d(&state->b0)) {
            state->b4=FloatToInt((g_tilt_platform_tilt_seconds*300.0f+2.0f)*0.16666667f);
            obj->mode=3;
        } else {
            rot[0]=math_fast_sin_or_cos_b(math_wrap_angle_to_pi(IntToFloat(state->b0)*0.75f))*0.017453294f;
            rot[1]=math_fast_sin_or_cos_a(math_wrap_angle_to_pi(IntToFloat(state->b0)*0.89f))*0.017453294f;
            if((float)state->b4>(g_tilt_platform_hold_seconds*300.0f+2.0f)*0.16666667f-25.0f) {
                t=IntToFloat(state->b0)/((g_tilt_platform_hold_seconds*300.0f+2.0f)*0.16666667f-25.333334f);
                obj->rotation.f[0]=obj->rotation.f[0]*t+rot[0]*(1.0f-t);
                obj->rotation.f[1]=obj->rotation.f[1]*t+rot[1]*(1.0f-t);
            } else {
                obj->rotation.f[1]=rot[1];
                obj->rotation.f[0]=rot[0];
            }
        }
        break;
    }
    case 3: {
        float t,f,b,ax,ay;
        t=IntToFloat(state->b4)/((g_tilt_platform_tilt_seconds*300.0f+2.0f)*0.16666667f);
        f=(1.0f-t)*g_tilt_platform_scale_a;
        obj->rotation.f[1]=0;
        obj->rotation.f[0]=(1.0f-t)*1.57079649f;
        ax=math_fast_sin_or_cos_a(FastAddRotations(1.57079649f,obj->rotation.f[2]));
        b=math_fast_sin_or_cos_b(obj->rotation.f[0]);
        ax*=f*b;
        obj->position.f[0]=ax;
        ay=math_fast_sin_or_cos_b(FastAddRotations(1.57079649f,obj->rotation.f[2]));
        b=math_fast_sin_or_cos_b(obj->rotation.f[0]);
        ay*=f*b;
        obj->position.f[1]=ay;
        obj->position.f[2]=0;
        obj->position.f[0]+=state->origin.f[0];
        ay+=state->origin.f[1];
        obj->position.f[1]=ay;
        f*=math_fast_sin_or_cos_a(obj->rotation.f[0]);
        obj->position.f[2]=state->origin.f[2]-f;
        obj->position.f[2]-=math_fast_sin_or_cos_a(t*1.57079649f)*g_tilt_platform_drop_height;
        state->flags8c&=~1;
        state->flags3e&=~8;
        obj->flags34&=~0x20;
        if(math_fast_float_d(&state->b4)) {
            obj->mode=4;
            state->b8=FloatToInt((g_tilt_platform_return_seconds*300.0f+2.0f)*0.16666667f);
        }
        break;
    }
    case 4: {
        float t,f,b,c,ax,ay;
        t=IntToFloat(state->b8)/((g_tilt_platform_return_seconds*300.0f+2.0f)*0.16666667f);
        *(Quad *)rot=obj->rotation.q;
        c=1.0f-t;
        f=(1.0f-c)*g_tilt_platform_scale_a;
        obj->rotation.f[0]=math_fast_float_g((rot[0]*c+c*4.71238947f)+1.57079649f);
        obj->rotation.f[1]=rot[1]*c;
        ax=math_fast_sin_or_cos_a(FastAddRotations(1.57079649f,obj->rotation.f[2]));
        b=math_fast_sin_or_cos_b(obj->rotation.f[0]);
        ax*=f*b;
        obj->position.f[0]=ax;
        ay=math_fast_sin_or_cos_b(FastAddRotations(1.57079649f,obj->rotation.f[2]));
        b=math_fast_sin_or_cos_b(obj->rotation.f[0]);
        ay*=f*b;
        obj->position.f[1]=ay;
        obj->position.f[2]=0;
        obj->position.f[0]+=state->origin.f[0];
        ay+=state->origin.f[1];
        obj->position.f[1]=ay;
        f*=math_fast_sin_or_cos_a(obj->rotation.f[0]);
        obj->position.f[2]=state->origin.f[2]-f;
        obj->position.f[2]-=math_fast_sin_or_cos_a(c*1.57079649f)*g_tilt_platform_drop_height;
        state->flags8c&=~1;
        state->flags3e&=~8;
        obj->flags34&=~0x20;
        if(math_fast_float_d(&state->b8)) {
            obj->mode=1;
            {
                Quad home = state->origin.q;
                obj->rotation.q=*(Quad *)rot;
                obj->position.q=home;
            }
        }
        break;
    }
    }
    if(obj->mode<3) {
        FastVecSub(pos,&obj->position,oldpos);
        mat_combine_and_store((u8 *)state+0x50,pos,oldrot,&obj->rotation);
    }
}
