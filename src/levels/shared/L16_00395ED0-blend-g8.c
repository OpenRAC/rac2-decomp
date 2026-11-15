#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 rotation[3], source[3], quaternion, angles; float position[4] __attribute__((aligned(16))); } BlendWorkspace;
/* Integer and FP arguments retain their order within the EE ABI register banks. */
extern float math_step_value_toward_target(float *,float,float *,float,float,float);
extern void euler_rotation_basis(void *,void *);
extern float mat_fast_helper_a(float,float);
extern float vec_length_xy(void *);
extern float math_move_angle_toward_target(float,float,float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void vec_fast_normalize3(void *,void *,void *,float);
extern void quaternion_to_rotation_basis(void *,void *);
extern void mat_get_euler_angles(float *,float *);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern float D_L16_001B3490[4] MACRO_ADDR;
extern float D_L16_001B34A0[4] MACRO_ADDR;
extern float D_L16_001B34B0[4] MACRO_ADDR;
extern float D_L16_001B34C0[4] MACRO_ADDR;
/* Blends the camera smoothly from its start view to the target view over time and applies the result. */
void BlendCameraPose(char *object)
{
    BlendWorkspace local;
    char *state=*(char **)(object+0x68);
    float startAngle,endAngle,startLength,endLength,startHeight,endHeight,angle,length;
    float *position;
    if (*(int *)(state+4)==-1) return;
    if (*(float *)(state+0x4c)<1.0f) math_step_value_toward_target((float *)(state+0x4c),1.0f,(float *)(state+0x50),0.0001850000117f,0.0001850000117f,0.01110000070f);
    euler_rotation_basis(local.source,state+0x20);
    if (*(float *)(state+0x4c)<1.0f) {
        startAngle=mat_fast_helper_a(D_L16_001B34B0[0],D_L16_001B34B0[1]);
        endAngle=mat_fast_helper_a(D_L16_001B34C0[0],D_L16_001B34C0[1]);
        startLength=vec_length_xy(D_L16_001B34B0);
        endLength=vec_length_xy(D_L16_001B34C0);
        startHeight=D_L16_001B34B0[2]; endHeight=D_L16_001B34C0[2];
        angle=math_move_angle_toward_target(startAngle,endAngle,*(float *)(state+0x4c));
        length=(endLength-startLength)*(*(float *)(state+0x4c))+startLength;
        local.position[0]=math_fast_sin_or_cos_a(angle)*length;
        local.position[1]=math_fast_sin_or_cos_b(angle)*length;
        local.position[2]=0.0f;
        local.position[2]=(endHeight-startHeight)*(*(float *)(state+0x4c))+startHeight;
    } else { qcopy(local.position,D_L16_001B34C0); }
    position=local.position;
    matrix_mul_vec3(position,position,local.source);
    FastVecAdd(position,position,state+0x10);
    vec_fast_normalize3(&local.quaternion,D_L16_001B3490,D_L16_001B34A0,*(float *)(state+0x4c));
    quaternion_to_rotation_basis(&local.quaternion,local.rotation);
    mat_get_euler_angles((float *)local.rotation,(float *)&local.angles);
    object_copy_vector_to_selected(position);
    cam_set_state_rotation(&local.angles);
}
