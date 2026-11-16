#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 angles, matrix[3], position, target; } CameraFollowWorkspace;
extern float FastAddRotations(float,float);
extern void euler_rotation_basis(void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern Vector128 g_turret_cam_position_offset __attribute__((sda));
extern Vector128 g_turret_cam_target_offset __attribute__((sda));
extern float g_turret_cam_yaw_step __attribute__((sda));
extern float g_turret_cam_height_offset __attribute__((sda));
/* Moves the camera to sit behind the turret, following the way the turret faces. */
void cam_update_turret_follow(char *object)
{
    CameraFollowWorkspace local;
    char *state=*(char **)(object+0x68);
    float height;
    *(Vector128 *)&local.angles=*(Vector128 *)(object+0xf0);
    ((float *)&local.angles)[1]=FastAddRotations(((float *)&local.angles)[1],g_turret_cam_yaw_step);
    ((float *)&local.angles)[1]=FastAddRotations(((float *)&local.angles)[1],*(float *)(state+0x90));
    euler_rotation_basis(local.matrix,&local.angles);
    matrix_mul_vec3(&local.position,&g_turret_cam_position_offset,local.matrix);
    matrix_mul_vec3(&local.target,&g_turret_cam_target_offset,object+0xc0);
    FastVecAdd(&local.target,&local.target,object+0x10);
    FastVecAdd(&local.position,&local.position,&local.target);
    height=*(float *)(object+0x18)+g_turret_cam_height_offset;
    if (((float *)&local.position)[2]<height) ((float *)&local.position)[2]=height;
    object_copy_vector_to_selected(&local.position);
    cam_set_state_rotation(&local.angles);
}
