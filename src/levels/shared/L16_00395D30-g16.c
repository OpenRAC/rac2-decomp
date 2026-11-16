#include "include_asm.h"
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 rotation[3], inverse[4], axes[3], point, angles; } AimWorkspace;
extern char *g_moby_instance_table[] __attribute__((sda));
extern char g_scene_origin_transform[];
extern Vector128 g_cam_blend_start_rotation[] __attribute__((sda));
extern Vector128 g_cam_blend_end_rotation[] __attribute__((sda));
extern Vector128 g_cam_blend_start_offset[] __attribute__((sda));
extern Vector128 g_cam_blend_end_offset[] __attribute__((sda));
extern Vector128 g_camera_blend_vector __attribute__((sda));
extern void SetCamera5Pose(void *,void *,int,int,int);
extern void euler_rotation_basis(void *,void *);
extern void matrix_from_basis_rows(void *,void *);
extern void mat_build_rotation_from_angles(void *,float *);
extern void FastVecSub(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecCross(void *,void *,void *);
extern void mat_get_euler_angles(float *,float *);
/* Sets up the camera move toward the object's chosen target, recording where the camera starts and where it should end. */
void cam_start_blend_to_target(char *object)
{
    AimWorkspace local;
    char *state=*(char **)(object+0x68);
    char *camera;
    char *cameraPosition;
    char *target;
    if (*(int *)(state+4)==-1) return;
    camera=g_scene_origin_transform;
    cameraPosition=camera+0x10;
    target=g_moby_instance_table[0]+*(int *)(state+4)*0x100;
    SetCamera5Pose(camera,cameraPosition,1,0,0);
    *(int *)(state+0x4c)=0; *(int *)(state+0x50)=0;
    euler_rotation_basis(local.rotation,state+0x20);
    matrix_from_basis_rows(local.inverse,local.rotation);
    mat_build_rotation_from_angles(g_cam_blend_start_rotation,(float *)cameraPosition);
    FastVecSub(g_cam_blend_start_offset,camera,state+0x10);
    matrix_mul_vec3(g_cam_blend_start_offset,g_cam_blend_start_offset,local.inverse);
    vec_scale_to_length(&local.point,target+0xe0,3.0f);
    FastVecAdd(&local.point,&local.point,target+0x10);
    FastVecSub(&local.axes[0],&local.point,object+0x10);
    vec_scale_to_length(&local.axes[0],&local.axes[0],1.0f);
    qcopy(&local.axes[2],&local.rotation[2]);
    FastVecCross(&local.axes[1],&local.axes[0],&local.axes[2]);
    matrix_mul_vec3(g_cam_blend_end_offset,&g_camera_blend_vector,local.axes);
    matrix_mul_vec3(g_cam_blend_end_offset,g_cam_blend_end_offset,local.inverse);
    mat_get_euler_angles((float *)local.axes,(float *)&local.angles);
    mat_build_rotation_from_angles(g_cam_blend_end_rotation,(float *)&local.angles);
}
