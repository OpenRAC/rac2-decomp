#include "include_asm.h"

#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float v[4]; } Vector;
typedef struct {Vector position,angles;} PartialCameraPose;
extern PartialCameraPose g_camera_l00_position;
typedef struct {unsigned char reserved[0x1A0];unsigned int held,pressed;} PartialInput;
extern PartialInput g_pad_state;
typedef struct {unsigned char reserved[0x1FB0];float pitch,yaw;unsigned char middle[0x24B8-0x1FB8];float delta;} PartialRoot;
extern PartialRoot g_hero_state;
typedef struct { short vector[4]; int active; } PartialCameraLock;
extern PartialCameraLock D_L00_001B1BE0 __attribute__((sda));
extern int D_L00_001A8FF0;
extern Vector D_L00_001B1B10 MACRO_ADDR;
extern float D_L00_001AFA30 __attribute__((sda));
extern void moby_set_state(unsigned char *,int,int),cam_set_mode_state(int);
extern void func_PAL_L00_002C4480(int,int),func_PAL_L00_002F5D28(void),ForceClaimNotice(int,int,int);
extern void euler_rotation_basis(float *,float *),vec_scale_to_length(void *,void *,float),FastVecAdd(void *,void *,void *);
extern float ApproachValue(float *,float,float),fast_vec_dist(void *,void *),FastVecDot(void *,void *),math_fabs(float),mat_fast_helper_a(float,float);
extern void cam_compute_view_direction(void *,void *,int),FastVecCross(void *,void *,void *),vec_set_direction_with_complement(void *,void *,float);
extern void quaternion_to_rotation_basis(void *,void *),multiply_matrix3x3(void *,void *,void *);
extern void object_copy_vector_to_selected(void *),mat_get_euler_angles(float *,float *),cam_set_state_rotation(void *);

void func_PAL_L00_003B9360(unsigned char *object)
{
    Vector position,angles;
    float matrix[12] __attribute__((aligned(16)));
    Vector movement,turn,cross,forward;
    float rotation[12] __attribute__((aligned(16)));
    float *state=*(float **)(object+0x68);
    float step,pitch,distance,projection;
    switch(object[0x20]) {
    case 0:
        moby_set_state(object,1,-1);
        break;
    case 1:
        break;
    case 2:
        if(g_pad_state.pressed&0x200) {cam_set_mode_state(0);func_PAL_L00_002C4480(0,1);moby_set_state(object,1,-1);}
        func_PAL_L00_002F5D28();
        object[0x31]=0;*(unsigned short *)(object+0x34)|=1;
        D_L00_001B1BE0.active=1;
        ForceClaimNotice(6,0,1);
        qcopy(&position,&g_camera_l00_position.position);
        qcopy(&angles,&g_camera_l00_position.angles);
        euler_rotation_basis(matrix,angles.v);
        if(g_pad_state.held&0x10)ApproachValue(state,-0.8000001f,0.0028000001f);
        else if(g_pad_state.held&0x40)ApproachValue(state,0.8000001f,0.0028000001f);
        vec_scale_to_length(&movement,matrix,state[0]);
        FastVecAdd(&position,&position,&movement);
        step=D_L00_001AFA30*6.981318e-06f;
        if(g_hero_state.delta>0.1f)step*=g_hero_state.delta;
        ApproachValue(state+1,-g_hero_state.pitch*0.062831864f,step);
        ApproachValue(state+2,-g_hero_state.yaw*0.062831864f,step);
        cam_compute_view_direction(&position,&forward,1);
        FastVecCross(&cross,matrix,&forward);
        pitch=state[2];
        if(D_L00_001A8FF0) {
            distance=fast_vec_dist(&position,&D_L00_001B1B10);
            projection=math_fabs(FastVecDot(&forward,&movement));
            pitch=state[2]+mat_fast_helper_a(distance,state[0]-projection);
        }
        vec_set_direction_with_complement(&turn,&forward,state[1]*0.5f);
        vec_set_direction_with_complement(&cross,&cross,pitch*0.5f);
        quaternion_to_rotation_basis(&turn,rotation);
        multiply_matrix3x3(matrix,rotation,matrix);
        quaternion_to_rotation_basis(&cross,rotation);
        multiply_matrix3x3(matrix,rotation,matrix);
        object_copy_vector_to_selected(&position);
        mat_get_euler_angles(matrix,angles.v);
        cam_set_state_rotation(&angles);
        break;
    }
}
