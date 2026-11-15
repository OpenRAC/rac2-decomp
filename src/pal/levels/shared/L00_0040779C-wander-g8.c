#include "names.h"
/* func_PAL_L00_0040779C, the PAL copy of func_L00_00402E50: the same C, where
 * the timers take the 50 Hz scale, the per-frame rates are rescaled and the
 * animation calls blend over 8 frames instead of 10. It has its own unit for
 * its jump table and -frac2-hazard-labels, without which it does not match.
 *
 * func_002A7CA0 is void (see src/game/0032EB28-ai-g8.c). With a float
 * declaration the call sets F0, which ends the F12 copy's dependence on the
 * later calls, and sched2 issues that copy after F14/F15, A0 and A1.
 * The arguments interleave by bank; each bank keeps its order. */
#include "common.h"

extern struct { char pad[0x80]; float pos[4]; char gap[0x2200]; int surface; } g_hero_state;
extern struct { char pad[0x18]; int surface; int gap; float point[4]; } g_collision_result;
extern int D_L00_001ADB2C;
extern int D_L00_001A8FF0, D_L00_001A8FF4;
extern void copy_matrix_rotation(void *,void *);
extern void mat_get_euler_angles(void *,void *);
extern void moby_transform_point_and_rotation_by_parent(void *,int,void *,void *,void *,void *);
extern void euler_rotation_basis(void *,void *);
extern int part_find_owned_effect_slot(void *,int,int);
extern void func_PAL_00333CD8(void *);
extern float mat_fast_helper_a(float,float);
extern void part_queue_ground_shadow(void *,float);
extern void moby_set_state(void *,int,int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern float math_random_float_range(float,float);
extern float vec_distance_xy(void *,void *);
extern int math_fast_float_d(void *);
extern int math_random_int_below(int);
extern int math_random_int_range(int,int);
extern float FastAddRotations(float,float);
extern void MobySpringTurn(float,void *,void *,float,float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int moby_move_over_ground(void *,void *,void *,float,float,float,float,int);
extern int coll_test_point(void *,int,void *,float);
extern void moby_forward_position_call(void *,void *,int);
extern int CollLine(void *,void *,int,void *,int);
extern int GetCollHitMaterial(void);
extern float coll_probe_ground_height_below(void *,int,float);

#define AI_F(p,n) (*(float *)((char *)(p)+(n)))
#define AI_I(p,n) (*(int *)((char *)(p)+(n)))
#define AI_B(p,n) (*(unsigned char *)((char *)(p)+(n)))

void func_PAL_L00_0040779C(char *object)
{
    float dest[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    union { float matrix[16]; struct { float vector[4]; float far[4]; float near[4]; } v; } work __attribute__((aligned(16)));
    char *state = *(char **)(object+0x68);
    float r;
    float angle;
    char *position;
    float *saved;
    int hit;

    if (AI_B(object,0x20) && D_L00_001ADB2C) {
        copy_matrix_rotation(work.matrix,object+0xc0);
        mat_get_euler_angles(work.matrix,dest);
        moby_transform_point_and_rotation_by_parent(object,D_L00_001ADB2C,object+0x10,dest,object+0x10,temp);
        euler_rotation_basis(object+0xc0,temp);
        qcopy(object+0xf0,temp);
    }
    if (part_find_owned_effect_slot(object,0x4010000,0)) func_PAL_00333CD8(object);
    mat_fast_helper_a(AI_F(object,0x10)-g_hero_state.pos[0],AI_F(object,0x14)-g_hero_state.pos[1]);
    part_queue_ground_shadow(object,0.5f);
    switch (AI_B(object,0x20)) {
    case 0:
        moby_set_state(object,1,-1);
        break;
    case 1:
        if (AI_B(object,0x60)&2) {
            r=math_random_float_range(0,100);
            if (r>=0 && r<20) func_PAL_002A7E68(object,0,0,8);
            if (r>=20 && r<50) func_PAL_002A7E68(object,4,0,8);
            if (r>=50 && r<100) func_PAL_002A7E68(object,1,0,8);
        }
        if (vec_distance_xy(object+0x10,g_hero_state.pos)<2 && !D_L00_001A8FF4 && !D_L00_001A8FF0) {
            moby_set_state(object,2,-1);
            func_PAL_002A7E68(object,2,0,8);
            AI_F(object,0x48)=0.75f;
        }
        if (math_fast_float_d(state+0x70)) {
            if (D_L00_001A8FF4) return;
            if (!D_L00_001A8FF0) {
                if (math_random_int_below(2)) {
                    moby_set_state(object,5,-1);
                    AI_I(state,0x70)=(((int)(math_random_int_range(400,600)) * 5 + 2) / 6);
                    func_PAL_002A7E68(object,2,0,8);
                    AI_F(object,0x48)=0.75f;
                } else {
                    moby_set_state(object,6,-1);
                    AI_I(state,0x70)=(((int)(math_random_int_range(180,360)) * 5 + 2) / 6);
                    func_PAL_002A7E68(object,3,0,8);
                }
            }
        }
        break;
    case 6:
        if (AI_B(object,0x60)&2) func_PAL_002A7E68(object,3,0,8);
        if (math_fast_float_d(state+0x70)) {
            moby_set_state(object,1,-1);
            AI_I(state,0x70)=(((int)(math_random_int_range(120,600)) * 5 + 2) / 6);
            func_PAL_002A7E68(object,math_random_int_below(2),0,8);
        }
        break;
    case 5:
        if (AI_B(object,0x60)&2) {
            func_PAL_002A7E68(object,2,0,8);
            AI_F(object,0x48)=0.75f;
        }
        position=object+0x10;
        if (vec_distance_xy(position,g_hero_state.pos)<2) {
            moby_set_state(object,2,-1);
            AI_F(object,0x48)=0.1f;
            func_PAL_002A7E68(object,2,0,8);
        }
        if (math_fast_float_d(state+0x70)) {
            moby_set_state(object,1,-1);
            AI_I(state,0x70)=(((int)(math_random_int_range(400,600)) * 5 + 2) / 6);
        }
        angle=FastAddRotations(AI_F(object,0xf8),math_random_float_range(-30,30)*0.017453294f);
        MobySpringTurn(angle,object,state+0x58,0.00020943955f,0.00062831864f,0.015707966f);
        vec_scale_to_length(temp,object+0xc0,0.0050000004f);
        FastVecAdd(dest,position,temp);
        saved=work.matrix;
        qcopy_nc(saved,position);
        if (moby_move_over_ground(object,position,dest,0.1f,0.7f,0.25f,0.52359885f,2)) {
            if (coll_test_point(position,1,object,0.5f) && g_collision_result.surface) qcopy(position,saved);
        } else {
            angle=FastAddRotations(AI_F(object,0xf8),math_random_float_range(20,135)*0.017453294f);
            MobySpringTurn(angle,object,state+0x58,6.9813184e-05f,0.00062831864f,0.015707966f);
        }
        break;
    case 2:
        position=object+0x10;
        if (vec_distance_xy(position,g_hero_state.pos)<2) {
            angle=FastAddRotations(AI_F(object,0xf8),math_random_float_range(-30,30)*0.017453294f);
            MobySpringTurn(angle,object,state+0x58,0.00020943955f,0.00062831864f,0.015707966f);
            vec_scale_to_length(temp,object+0xc0,0.0050000004f);
            FastVecAdd(dest,position,temp);
            saved=work.matrix;
            qcopy_nc(saved,position);
            if (moby_move_over_ground(object,position,dest,0.5f,0.7f,0.25f,0.52359885f,2)) {
                if (coll_test_point(position,1,object,0.5f) && g_collision_result.surface) qcopy(position,saved);
            } else {
                angle=FastAddRotations(AI_F(object,0xf8),math_random_float_range(-90,-10)*0.017453294f);
                MobySpringTurn(angle,object,state+0x58,8.377582e-05f,0.00062831864f,0.015707966f);
            }
        } else {
            AI_F(object,0x48)=1;
            moby_set_state(object,1,-1);
        }
        break;
    case 4:
        moby_forward_position_call(object,work.matrix,0);
        vec_scale_to_length(work.matrix,work.matrix,4);
        FastVecAdd(work.v.far,object+0x10,work.matrix);
        vec_scale_to_length(work.matrix,work.matrix,-1);
        FastVecAdd(work.v.near,object+0x10,work.matrix);
        if (CollLine(work.v.near,work.v.far,0,object,0)) {
            if (g_collision_result.surface!=g_hero_state.surface) qcopy(object+0x10,g_collision_result.point);
        }
        hit=GetCollHitMaterial();
        if (hit>0 && hit!=10 && !D_L00_001A8FF4) {func_PAL_00333CD8(object);return;}
        moby_set_state(object,0,-1);
        break;
    case 3:
        break;
    }
    if (!D_L00_001A8FF4 && !D_L00_001A8FF0) {
        qcopy(work.matrix,object+0x10);
        work.matrix[2]+=0.5f;
        AI_F(object,0x18)=coll_probe_ground_height_below(work.matrix,0,0.5f);
    }
}
