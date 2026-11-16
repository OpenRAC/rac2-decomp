#include "include_asm.h"

#include "common.h"
typedef int QuadEDA __attribute__((mode(TI)));
typedef union VecEDA { QuadEDA q; float f[4]; } VecEDA;
extern unsigned char *g_camera_state_ptr;
extern char *moby_get_motion_data(unsigned char *);
extern int follower_get_state(unsigned char *);
extern void follower_clamp_range_spawn_sparks_pal(unsigned char *);
extern void follower_check_hazard_contact_pal(unsigned char *);
extern void follower_move_toward_target(unsigned char *);
extern void follower_limit_speed(unsigned char *);
extern void UpdateBankedOrientation(unsigned char *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void follower_set_push_vector(unsigned char *,void *);
extern int follower_has_reached_target(unsigned char *);
extern s64 follower_try_place_at_saved_spot(unsigned char *);
extern void follower_set_state(unsigned char *,int);
extern int func_001163B0(void);
extern float math_random_float_range(float,float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float FastAddRotations(float,float);
extern int math_fast_helper_a(void *,float);
extern int math_random_int_range(int,int);
extern void moby_release_motion_slot(unsigned char *);
extern void follower_start_random_push_pal(unsigned char *);
extern void follower_start_push_from_target_pal(unsigned char *);
#define IEDA(p,o) (*(int *)((p)+(o)))
#define FEDA(p,o) (*(float *)((p)+(o)))
#define PEDA(p,o) (*(unsigned char **)((p)+(o)))

/* Per-frame follower movement: applies velocity, clamps, then steers toward its target by state
   (PAL: 50 Hz timings). */
void follower_l05_update_pal(unsigned char *owner)
{
    VecEDA v, extra, frame[3], zero, up, basis[3], test, rotated;
    unsigned char *vars = (unsigned char *)moby_get_motion_data(owner);
    unsigned char *cam;
    unsigned char *target;
    float sign;
    if (!vars) return;
    zero.q = 0;
    up.q = 0;
    zero.f[2] = 1.0f;
    up.f[0] = 1.0f;
    qcopy(vars+0xB0,owner+0x10);
    if (follower_get_state(owner) != 8)
        FastVecAdd(owner+0x10,vars+0x90,owner+0x10);
    follower_clamp_range_spawn_sparks_pal(owner);
    follower_check_hazard_contact_pal(owner);
    follower_move_toward_target(owner);
    follower_limit_speed(owner);
    UpdateBankedOrientation(owner);
    cam = g_camera_state_ptr;
    switch(follower_get_state(owner)) {
    case 7:
        vec_scale_to_length(&v,PEDA(vars,0x120)+0xC0,-50.0f);
        FastVecAdd(&v,PEDA(vars,0x120)+0x10,&v);
        follower_set_push_vector(owner,&v);
        if(follower_has_reached_target(owner)) {
            follower_set_state(owner,8);
            IEDA(vars,0x130)=750;
            sign = (func_001163B0()&1) ? -1.0f : 1.0f;
            FEDA(vars,0x140)=sign;
            FEDA(vars,0x134)=sign < 0.0f ? 1.5707964f : -1.5707964f;
            FEDA(vars,0x144)=math_random_float_range(5.0f,15.0f);
        }
        break;
    case 8:
        v.f[2]=0.0f;
        v.f[0]=math_fast_sin_or_cos_b(FEDA(vars,0x134))*FEDA(vars,0x144);
        v.f[1]=-math_fast_sin_or_cos_a(FEDA(vars,0x134))*FEDA(vars,0x144);
        v.f[3]=0.0f;
        FEDA(vars,0x134)=FastAddRotations(FEDA(vars,0x134),FEDA(vars,0x140)*0.015707966f);
        qcopy(&basis[2],cam+0x20);
        FastVecCross(&basis[1],&up,&basis[2]);
        vec_scale_to_length(&basis[1],&basis[1],1.0f);
        FastVecCross(&basis[0],&basis[2],&basis[1]);
        matrix_mul_vec3(&v,&v,&basis[0]);
        FastVecAdd(owner+0x10,PEDA(vars,0x120)+0x10,&v);
        follower_set_push_vector(owner,&v);
        if(follower_try_place_at_saved_spot(owner)) follower_set_state(owner,9);
        if(!follower_has_reached_target(owner)) break;
        qcopy(&test,owner+0x10);
        test.f[3]=5.0f;
        if(math_fast_helper_a(&test,256.0f)==-1) {
            moby_release_motion_slot(owner);
            follower_set_state(owner,1);
        }
        break;
    case 9:
        qcopy(&test,owner+0x10);
        test.f[3]=5.0f;
        if(math_fast_helper_a(&test,256.0f)==-1) {
            moby_release_motion_slot(owner);
            follower_set_state(owner,1);
        }
        break;
    case 4:
        if (!PEDA(vars,0x120)) { moby_release_motion_slot(owner); follower_set_state(owner,1); break; }
        vec_scale_to_length(&v,PEDA(vars,0x120)+0xC0,25.0f);
        if (IEDA(vars,0xFC)) {
            matrix_mul_vec3(&rotated,vars+0x70,PEDA(vars,0x120)+0xC0);
            FastVecAdd(&v,&rotated,&v);
        }
        FastVecAdd(&v,PEDA(vars,0x120)+0x10,&v);
        follower_set_push_vector(owner,&v);
        if (follower_has_reached_target(owner)) {
            follower_set_state(owner,5);
            IEDA(vars,0x130)=((s32)(math_random_int_range(300,600)) * 5 + 2) / 6;
        }
        break;
    case 5:
        if (!PEDA(vars,0x120)) { moby_release_motion_slot(owner); follower_set_state(owner,1); break; }
        vec_scale_to_length(&v,PEDA(vars,0x120)+0xC0,5.0f);
        if (IEDA(vars,0xFC)) {
            matrix_mul_vec3(&rotated,vars+0x70,PEDA(vars,0x120)+0xC0);
            FastVecAdd(&v,&rotated,&v);
        }
        FastVecAdd(&v,PEDA(vars,0x120)+0x10,&v);
        follower_set_push_vector(owner,&v);
        if(follower_has_reached_target(owner)) { moby_release_motion_slot(owner); follower_set_state(owner,1); }
        break;
    case 6:
        if (!PEDA(vars,0x120)) { moby_release_motion_slot(owner); follower_set_state(owner,1); break; }
        vec_scale_to_length(&v,PEDA(vars,0x120)+0xC0,10.0f);
        vec_scale_to_length(&extra,PEDA(vars,0x120)+0xE0,0.05f);
        if (IEDA(vars,0xFC)) {
            matrix_mul_vec3(&rotated,vars+0x70,PEDA(vars,0x120)+0xC0);
            FastVecAdd(&v,&rotated,&v);
        }
        FastVecAdd(&v,&extra,&v);
        FastVecAdd(&v,PEDA(vars,0x120)+0x10,&v);
        follower_set_push_vector(owner,&v);
        if(follower_has_reached_target(owner)) { moby_release_motion_slot(owner); follower_set_state(owner,1); }
        break;
    case 3:
        target=PEDA(vars,0x10);
        qcopy(&frame[0],target+0xC0);
        FastVecCross(&frame[1],&frame[0],&zero);
        vec_scale_to_length(&frame[1],&frame[1],1.0f);
        FastVecCross(&frame[2],&frame[1],&frame[0]);
        matrix_mul_vec3(&v,vars,&frame[0]);
        FastVecAdd(&v,target+0x10,&v);
        follower_set_push_vector(owner,&v);
        break;
    case 1:
        if(follower_has_reached_target(owner)) follower_start_random_push_pal(owner);
        break;
    case 13:
        if(follower_has_reached_target(owner)) follower_start_push_from_target_pal(owner);
        break;
    }
}
