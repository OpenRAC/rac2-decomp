#include "names.h"
/* func_L00_00407E38 has its own unit for -frac2-hazard-labels; it is the level
 * copy of func_00332658 (src/game/0032EB28-ai-g8.c). func_002A7CA0 is void here
 * as it is there; the evidence for that is in that file's header. */
#include "common.h"

extern struct { char pad[0x80]; float pos[4]; char gap[0x2200]; int surface; } g_hero_state;
extern int D_L00_001ADB2C;
extern int D_L00_001A8FF0, D_L00_001A8FF4;
extern struct { char pad[0x18]; int surface; int gap; float point[4]; } g_collision_result;
extern void copy_matrix_rotation(void *, void *);
extern void mat_get_euler_angles(void *, void *);
extern int moby_transform_point_and_rotation_by_parent(void *, int, void *, void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void moby_explode_and_hurt_nearby(void *);
extern float mat_fast_helper_a(float, float);
extern void part_queue_ground_shadow(void *, float);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern float math_random_float_range(float, float);
extern void *FindBestTargetByReach(void *, float, float, float, float);
extern float vec_distance_xy(void *, void *);
extern int math_fast_float_d(void *);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern void MobySpringTurn(float, void *, void *, float, float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int moby_move_over_ground(void *, void *, void *, float, float, float, float, int);
extern float FastAddRotations(float, float);
extern float FastDiffRots(float, float);
extern void moby_forward_position_call(void *, void *, int);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);
extern float coll_probe_ground_height_below(void *, int, float);

typedef int AI_Quad __attribute__((mode(TI)));

#define AI_F(p,n) (*(float *)((char *)(p)+(n)))
#define AI_I(p,n) (*(int *)((char *)(p)+(n)))
#define AI_P(p,n) (*(char **)((char *)(p)+(n)))
#define AI_B(p,n) (*(unsigned char *)((char *)(p)+(n)))

/* Updates a Dark Sheep (moby class 3760): it wanders, chases nearby targets, and is removed if it cannot move. */
void dark_sheep_update(char *object)
{
    float end[4], offset[4], scratch[4], front[4], back[4], matrix[4];
    char *state = AI_P(object, 0x68);
    char *target;
    char *position;
    float angle, choice;
    int hit;
    if (AI_B(object,0x20) && D_L00_001ADB2C) {
        copy_matrix_rotation(scratch,object+0xC0);
        mat_get_euler_angles(scratch,end);
        moby_transform_point_and_rotation_by_parent(object,D_L00_001ADB2C,object+0x10,end,object+0x10,offset);
        euler_rotation_basis(object+0xC0,offset);
        qcopy(object+0xF0,offset);
    }
    if (part_find_owned_effect_slot(object,0x4010000,0)) moby_explode_and_hurt_nearby(object);
    AI_I(state,0x78)++;
    angle=mat_fast_helper_a(AI_F(object,0x10)-g_hero_state.pos[0],AI_F(object,0x14)-g_hero_state.pos[1]);
    part_queue_ground_shadow(object,0.5f);
    switch (AI_B(object,0x20)) {
    case 0:
        moby_set_state(object,1,-1);
        break;
    case 1:
        if (AI_B(object,0x60)&2) {
            choice=math_random_float_range(0.0f,100.0f);
            if (choice>=0.0f && choice<25.0f) anim_start_blended(object,0,0,10);
            if (choice>=25.0f && choice<50.0f) anim_start_blended(object,4,0,10);
            if (choice>=50.0f && choice<75.0f) anim_start_blended(object,1,0,10);
            if (choice>=75.0f && choice<100.0f && !D_L00_001A8FF4 && !D_L00_001A8FF0) {
                *(AI_Quad *)scratch=*(AI_Quad *)(object+0x10);
                AI_P(state,0x7C)=FindBestTargetByReach(scratch,1.5707964897155762f,999.0f,-1.0f,-1.0f);
                if (AI_P(state,0x7C)) {
                    moby_set_state(object,8,-1);
                    anim_start_blended(object,5,0,1);
                    AI_F(object,0x48)=1.7f;
                }
            }
        }
        if (vec_distance_xy(object+0x10,g_hero_state.pos)<2.0f && !D_L00_001A8FF4 && !D_L00_001A8FF0) {
            moby_set_state(object,2,-1);
            anim_start_blended(object,5,0,1);
            AI_F(object,0x48)=1.7f;
        }
        if (math_fast_float_d(state+0x70)) {
            if (D_L00_001A8FF4) return;
            if (!D_L00_001A8FF0) {
                if (math_random_int_below(2)) {
                    moby_set_state(object,5,-1);
                    AI_I(state,0x70)=math_random_int_range(400,600);
                    anim_start_blended(object,2,0,10);
                } else {
                    moby_set_state(object,6,-1);
                    AI_I(state,0x70)=math_random_int_range(180,360);
                    anim_start_blended(object,3,0,10);
                }
            }
        }
        break;
    case 8:
        target=AI_P(state,0x7C);
        choice=mat_fast_helper_a(AI_F(target,0x10)-AI_F(object,0x10),AI_F(target,0x14)-AI_F(object,0x14));
        MobySpringTurn(choice,object,state+0x58,0.00021816618391312659f,0.00043633236782625318f,0.017453296110033989f);
        vec_scale_to_length(offset,object+0xC0,1.0f/24.0f);
        FastVecAdd(end,object+0x10,offset);
        if (!moby_move_over_ground(object,object+0x10,end,0.5f,0.6f,0.25f,0.52359885f,0)) moby_explode_and_hurt_nearby(object);
        break;
    case 6:
        if (AI_B(object,0x60)&2) anim_start_blended(object,3,0,10);
        if (math_fast_float_d(state+0x70)) {
            moby_set_state(object,1,-1);
            AI_I(state,0x70)=math_random_int_range(120,600);
            anim_start_blended(object,math_random_int_below(2),0,10);
        }
        break;
    case 5:
        if (AI_B(object,0x60)&2) anim_start_blended(object,2,0,2);
        if (vec_distance_xy(object+0x10,g_hero_state.pos)<2.0f) {
            moby_set_state(object,2,-1);
            anim_start_blended(object,5,0,1);
        }
        if (math_fast_float_d(state+0x70)) {
            moby_set_state(object,1,-1);
            AI_I(state,0x70)=math_random_int_range(400,600);
        }
        MobySpringTurn(FastAddRotations(AI_F(object,0xF8),math_random_float_range(-30.0f,30.0f)*0.01745329424738884f),object,state+0x58,0.00014544412260875106f,0.00043633236782625318f,0.013089972f);
        vec_scale_to_length(offset,object+0xC0,1.0f/240.0f);
        FastVecAdd(end,object+0x10,offset);
        if (!moby_move_over_ground(object,object+0x10,end,0.1f,0.5f,0.25f,0.52359885f,0)) {
            MobySpringTurn(FastAddRotations(AI_F(object,0xF8),math_random_float_range(20.0f,135.0f)*0.01745329424738884f),object,state+0x58,0.000048481375415576622f,0.00043633236782625318f,0.013089972f);
        }
        break;
    case 2:
        position=object+0x10;
        *(AI_Quad *)scratch=*(AI_Quad *)(object+0x10);
        AI_P(state,0x7C)=FindBestTargetByReach(scratch,1.5707964897155762f,999.0f,-1.0f,-1.0f);
        target=AI_P(state,0x7C);
        if (target) {
            choice=mat_fast_helper_a(AI_F(target,0x10)-AI_F(object,0x10),AI_F(target,0x14)-AI_F(object,0x14));
            MobySpringTurn(choice,object,state+0x58,0.00021816618391312659f,0.00043633236782625318f,0.017453296110033989f);
            vec_scale_to_length(offset,object+0xC0,1.0f/24.0f);
            FastVecAdd(end,position,offset);
        }
        if (!moby_move_over_ground(object,position,end,0.5f,0.6f,0.25f,0.52359885f,0)) {
            moby_explode_and_hurt_nearby(object);
        } else if (FastDiffRots(angle,AI_F(object,0xF8))>0.52359885f) {
            MobySpringTurn(angle,object,state+0x58,0.00038785100332461298f,0.00043633236782625318f,0.013089972f);
        }
        break;
    case 4:
        moby_forward_position_call(object,scratch,0);
        vec_scale_to_length(scratch,scratch,4.0f);
        FastVecAdd(front,object+0x10,scratch);
        vec_scale_to_length(scratch,scratch,-1.0f);
        FastVecAdd(back,object+0x10,scratch);
        if (CollLine(back,front,0,object,0)) {
            if (g_collision_result.surface!=g_hero_state.surface) qcopy(object+0x10,g_collision_result.point);
        }
        hit=GetCollHitMaterial();
        if (hit>0 && hit!=10 && !D_L00_001A8FF4) {moby_explode_and_hurt_nearby(object);return;}
        moby_set_state(object,1,-1);
        break;
    }
    if (!D_L00_001A8FF4 && !D_L00_001A8FF0) {
        qcopy(scratch,object+0x10);
        scratch[2]+=0.5f;
        AI_F(object,0x18)=coll_probe_ground_height_below(scratch,0,0.5f);
    }
}
