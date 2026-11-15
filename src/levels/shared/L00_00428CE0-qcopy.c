#include "include_asm.h"
#include "common.h"

extern char g_hero_position[];
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern float math_step_spring_damper_stored(char *, float, float, float, float, float);
extern void FastVecCross(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char ref_L00_00428CE0_00[];

/* Turns the camera smoothly to look at the hero's position, then rebuilds the camera's other two direction vectors. */
void cam_aim_at_hero(char *camera) {
    char *vars = *(char **)(camera + 0x70);
    char *a30 = vars + 0x30;
    char *a40 = vars + 0x40;
    float aim_point[4] __attribute__((aligned(16)));
    float aim_dir[4] __attribute__((aligned(16)));
    float turn_axis[4] __attribute__((aligned(16)));
    float scale, aim_angle;

    qcopy(aim_point, g_hero_position);
    aim_point[2] += *(float *)(a40 + 0x4C);
    FastVecSub(aim_dir, aim_point, camera + 0x30);
    vec_scale_to_length(aim_dir, aim_dir, 1.0f);
    aim_angle = 1.5707964f - math_fast_angle_helper(FastVecDot(aim_dir, camera));
    if (*(int *)(g_hero_position + 0x2214) == 0x24) {
        *(float *)a30 = *(float *)a30 + 0.017f;
        if (1.0f < *(float *)a30)
            *(float *)a30 = 1.0f;
        scale = aim_angle * *(float *)a30;
    } else {
        scale = math_step_spring_damper_stored(a30, 0.0f, aim_angle, 0.02f, 0.175f, 0.0f);
    }
    FastVecCross(turn_axis, aim_dir, camera + 0x40);
    math_apply_axis_rotation_to_quat(camera, camera + 0x40, turn_axis, scale);
    vec_scale_to_length(camera + 0x40, camera, 1.0f);
    qcopy(camera, camera + 0x40);
    FastVecCross(camera + 0x10, camera, ref_L00_00428CE0_00);
    vec_scale_to_length(camera + 0x10, camera + 0x10, 1.0f);
    FastVecCross(camera + 0x20, camera + 0x10, camera);
}
