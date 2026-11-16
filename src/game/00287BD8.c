#include "include_asm.h"
#include "names.h"

/* Family 8c659bbcffcd2ad3 -- 324 bytes, 27 level placements. */

#ifndef RAC2_T_BLOCK48_F8C659BBC
#define RAC2_T_BLOCK48_F8C659BBC
typedef struct { char pad[48]; } Block48_F8c659bbc;
#endif

#ifndef RAC2_T_BLOCK16_F8C659BBC
#define RAC2_T_BLOCK16_F8C659BBC
typedef struct { char pad[16]; } Block16_F8c659bbc;
#endif

extern char g_camera_offset_vector[] __attribute__((sda));

extern char g_camera_l00_position[];

extern char g_cam_follow_matrix[];

extern char g_camera_euler_angles __attribute__((sda));

extern void FastVecSub(char *a, char *b, char *c);

extern void vec_scale_to_length(char *a, char *b, float f);

extern void euler_rotation_basis(char *a, char *b);

extern void multiply_matrix3x3(char *a, char *b, char *c);

extern void FastVecCross(char *a, char *b, char *c);

extern float FastVecLength(char *a);

extern void vec_set_direction_with_complement(char *a, char *b, float f);

extern void math_approach_target_with_braking(char *a, float f1, float f2, float f3, float f4);

extern void quaternion_to_rotation_basis(char *a, char *b);

/* Turns the camera to follow the player: builds a rotation from the current view and eases it, then folds it into the camera matrix. */
void cam_update_follow_rotation(char *easeState, int useFixedAngle)
{
    Block48_F8c659bbc finalRotation;
    Block48_F8c659bbc combined;
    Block48_F8c659bbc lookMatrix;
    Block16_F8c659bbc axis;
    Block16_F8c659bbc direction;
    float halfAngle;

    FastVecSub((char *)&direction, g_camera_l00_position, g_camera_offset_vector);
    vec_scale_to_length((char *)&direction, (char *)&direction, 1.0f);
    euler_rotation_basis((char *)&lookMatrix, (char *)&g_camera_euler_angles);
    multiply_matrix3x3((char *)&combined, g_camera_l00_position + 560, (char *)&lookMatrix);
    FastVecCross((char *)&axis, (char *)&combined, (char *)&direction);
    halfAngle = FastVecLength((char *)&axis) * 0.5f;
    if (useFixedAngle != 0) {
        vec_set_direction_with_complement((char *)&axis, (char *)&axis, -halfAngle);
    } else {
        math_approach_target_with_braking(easeState, halfAngle, 5.8177649043500423431396e-04f,
                5.8177649043500423431396e-04f,
                5.2359886467456817626953e-02f);
        vec_set_direction_with_complement((char *)&axis, (char *)&axis, -*(float *)easeState);
    }
    quaternion_to_rotation_basis((char *)&axis, (char *)&finalRotation);
    multiply_matrix3x3(g_cam_follow_matrix, (char *)&finalRotation, g_cam_follow_matrix);
}

extern float g_camera_roll_scale __attribute__((sda));
/* Rolls the camera by an amount taken from the stick roll value. */
void cam_apply_roll(float *roll) { char rotation[0x40]; float angle = *roll * 0.0002908882452175021f * g_camera_roll_scale; vec_set_direction_with_complement(rotation, g_cam_follow_matrix, angle); quaternion_to_rotation_basis(rotation, rotation + 0x10); multiply_matrix3x3(g_cam_follow_matrix, rotation + 0x10, g_cam_follow_matrix); }

extern void FastVecAdd(char *a, char *b, char *c);

extern int g_camera_offset_length __attribute__((sda));

/* Moves the camera direction by the given offset and re-normalizes it. */
void cam_offset_direction(char *offset)
{
    FastVecSub(g_camera_l00_position, g_camera_l00_position, g_camera_offset_vector);
    FastVecAdd(g_camera_l00_position, g_camera_l00_position, offset);
    vec_scale_to_length(g_camera_l00_position, g_camera_l00_position, (float)g_camera_offset_length);
    FastVecAdd(g_camera_l00_position, g_camera_l00_position, g_camera_offset_vector);
}
