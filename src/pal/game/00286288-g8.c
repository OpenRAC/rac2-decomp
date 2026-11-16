#include "include_asm.h"
#include "names.h"

extern char g_cam_follow_matrix[];
extern void multiply_matrix3x3(char *a, char *b, char *c);
extern void vec_set_direction_with_complement(char *a, char *b, float f);
extern void quaternion_to_rotation_basis(char *a, char *b);
extern float g_camera_roll_scale __attribute__((sda));

/* Rolls the camera by an amount taken from the stick roll value (PAL: scaled for 50 Hz). */
void func_PAL_00288638(float *roll) { char rotation[0x40]; float angle = *roll * 0.0003490659f * g_camera_roll_scale; vec_set_direction_with_complement(rotation, g_cam_follow_matrix, angle); quaternion_to_rotation_basis(rotation, rotation + 0x10); multiply_matrix3x3(g_cam_follow_matrix, rotation + 0x10, g_cam_follow_matrix); }

typedef struct { char pad[48]; } Block48_F8c659bbc;
typedef struct { char pad[16]; } Block16_F8c659bbc;
extern char g_camera_offset_vector[] __attribute__((sda));
extern char g_camera_l00_position[];
extern char g_camera_euler_angles __attribute__((sda));
extern void FastVecSub(char *a, char *b, char *c);
extern void vec_scale_to_length(char *a, char *b, float f);
extern void euler_rotation_basis(char *a, char *b);
extern void FastVecCross(char *a, char *b, char *c);
extern float FastVecLength(char *a);
extern void math_approach_target_with_braking(char *a, float f1, float f2, float f3, float f4);

/* Turns the camera to follow the player: builds a rotation from the current view and eases it, then folds it into the camera matrix (PAL: 50 Hz easing constants). */
void cam_update_follow_rotation_pal(char *ease_state, int use_fixed_angle)
{
    Block48_F8c659bbc new_rotation;
    Block48_F8c659bbc relative_basis;
    Block48_F8c659bbc euler_basis;
    Block16_F8c659bbc axis;
    Block16_F8c659bbc view_dir;
    float axis_length;

    FastVecSub((char *)&view_dir, g_camera_l00_position, g_camera_offset_vector);
    vec_scale_to_length((char *)&view_dir, (char *)&view_dir, 1.0f);
    euler_rotation_basis((char *)&euler_basis, (char *)&g_camera_euler_angles);
    multiply_matrix3x3((char *)&relative_basis, g_camera_l00_position + 560, (char *)&euler_basis);
    FastVecCross((char *)&axis, (char *)&relative_basis, (char *)&view_dir);
    axis_length = FastVecLength((char *)&axis) * 0.5f;
    if (use_fixed_angle != 0) {
        vec_set_direction_with_complement((char *)&axis, (char *)&axis, -axis_length);
    } else {
        math_approach_target_with_braking(ease_state, axis_length, 0.0008377582f,
                0.0008377582f,
                0.062831864f);
        vec_set_direction_with_complement((char *)&axis, (char *)&axis, -*(float *)ease_state);
    }
    quaternion_to_rotation_basis((char *)&axis, (char *)&new_rotation);
    multiply_matrix3x3(g_cam_follow_matrix, (char *)&new_rotation, g_cam_follow_matrix);
}
