#include "common.h"
typedef struct {float v[4];} Vec;
typedef struct {Vec basis[3]; Vec pos;} Camera;
typedef struct {float yaw,pitch,dist; int frames_left; float inv_frames; int frames; char pad[8]; Vec fwd,up,rot,pos,saved_rot;} CamBlendOrbit;
extern unsigned char D_001B5490[];
extern char g_hero_state[];
extern Vec g_hero_position[], g_camera_eye_state[], D_001B5570[], D_0018A0E0[];
extern float math_cosine_blend(float,float,float);
extern void FastVecCross(void*,void*,void*);
extern void cam_compute_aim_angles(float*,void*,void*,void*,void*,void*);
extern void vec_scale_to_length(void*,void*,float);
extern float fast_subtract_rotations(float,float), FastAddRotations(float,float);
extern void math_apply_axis_rotation_to_quat(void*,void*,void*,float);
extern void FastVecScale(void*,void*,float), FastVecSub(void*,void*,void*);
extern float FastVecDot(void*,void*), FastVecLength(void*), math_fast_angle_helper(float), math_fabs(float);
extern void math_build_axis_angle_quat(void*,void*,float), vec_rotate_by_quaternion(void*,void*,void*);
extern int math_fast_float_d(void*);
extern void quaternion_to_rotation_basis(void*,void*), mat_transform_via_copy(void*,void*), FastVecAdd(void*,void*,void*);
/* Adapted from RAC1 advance_alternate_camera_transition, GPL-3.0. */
/* Moves the camera around an orbit toward its goal each frame; returns 1 when the move is finished. */
int cam_advance_orbit_transition(Camera *cam, CamBlendOrbit *orbit) {
    Vec ang;
    Vec fwd;
    Vec side;
    Vec up;
    Vec target;
    Vec pos;
    Vec diff;
    Vec proj;
    Vec axes[3];
    Vec r0;
    Vec r1;
    Vec r2;
    Vec temp_rot;
    float step;
    float dyaw;
    float dpitch;
    float yaw;
    float turn;
    float sign;
    float pitch_sign;
    float d;
    char *hero;

    if (orbit->frames_left <= 0) {
        return 1;
    }
    step = 1.0f / math_cosine_blend(1.0f, (float)orbit->frames, (float)orbit->frames_left * orbit->inv_frames);
    if (D_001B5490[2] == 2) {
        qcopy(&target, g_hero_position);
        qcopy(&fwd, &orbit->fwd);
        qcopy(&up, &orbit->up);
        FastVecCross(&side, &fwd, &up);
        cam_compute_aim_angles(ang.v, &cam->pos, &target, &fwd, &side, &up);
    } else {
        qcopy(&target, &cam->pos);
        hero = g_hero_state;
        vec_scale_to_length(&fwd, *(char **)(hero + 0x2290) + 0xC0, 1.0f);
        vec_scale_to_length(&up, *(char **)(hero + 0x2290) + 0xE0, 1.0f);
        ang.v[2] = 0.0f;
        ang.v[1] = 0.0f;
        ang.v[0] = 3.1415927f;
    }
    dyaw = fast_subtract_rotations(ang.v[0], orbit->yaw);
    orbit->yaw = FastAddRotations(orbit->yaw, dyaw * step);
    dpitch = fast_subtract_rotations(ang.v[1], orbit->pitch);
    orbit->pitch = FastAddRotations(orbit->pitch, dpitch * step);
    orbit->dist = orbit->dist + (ang.v[2] - orbit->dist) * step;
    vec_scale_to_length(&pos, &fwd, orbit->dist);
    math_apply_axis_rotation_to_quat(&pos, &pos, &up, orbit->yaw);
    FastVecCross(&side, &pos, &up);
    vec_scale_to_length(&side, &side, 1.0f);
    math_apply_axis_rotation_to_quat(&pos, &pos, &side, orbit->pitch);
    FastVecAdd(&orbit->pos, &target, &pos);
    qcopy(g_camera_eye_state, &orbit->pos);
    quaternion_to_rotation_basis(&orbit->rot, axes);
    d = FastVecDot(&axes[2], cam);
    FastVecScale(&proj, &axes[2], d);
    FastVecSub(&diff, cam, &proj);
    yaw = 1.57079637f - math_fast_angle_helper(FastVecDot(&axes[0], &diff) / FastVecLength(&diff));
    sign = -1.0f;
    if (FastVecDot(&diff, &axes[1]) >= 0.0f) {
        sign = 1.0f;
    }
    yaw = yaw * sign;
    if (math_fabs(dyaw) > 1.5707965f
        && ((dyaw >= 0.0f && sign < 0.0f) || (dyaw < 0.0f && sign >= 0.0f))) {
        if (yaw < 0.0f) {
            yaw += 6.283186f;
        } else {
            yaw -= 6.283186f;
        }
    }
    turn = yaw * step;
    if (math_fabs(turn) < 1e-5f) {
        qcopy(&r0, &axes[0]);
        qcopy(&r1, &axes[1]);
    } else {
        math_build_axis_angle_quat(&r2, &axes[2], turn);
        vec_rotate_by_quaternion(&r0, &axes[0], &r2);
        vec_rotate_by_quaternion(&r1, &axes[1], &r2);
    }
    if (math_fabs(yaw) < 1e-5f) {
        qcopy(&r2, &axes[0]);
    } else {
        math_build_axis_angle_quat(&temp_rot, &axes[2], yaw);
        vec_rotate_by_quaternion(&r2, &axes[0], &temp_rot);
    }
    yaw = 1.57079637f - math_fast_angle_helper(FastVecDot(&r2, cam));
    d = FastVecDot(&r2, &cam->basis[2]);
    pitch_sign = -1.0f;
    if (d >= 0.0f) {
        pitch_sign = 1.0f;
    }
    yaw *= pitch_sign;
    math_apply_axis_rotation_to_quat(&r0, &r0, &r1, yaw * step);
    vec_scale_to_length(&D_001B5570[0], &r0, 1.0f);
    FastVecCross(&D_001B5570[1], &D_001B5570[0], D_0018A0E0);
    vec_scale_to_length(&D_001B5570[1], &D_001B5570[1], -1.0f);
    FastVecCross(&D_001B5570[2], &D_001B5570[1], &D_001B5570[0]);
    mat_transform_via_copy(&orbit->saved_rot, D_001B5570);
    mat_transform_via_copy(&orbit->rot, D_001B5570);
    math_fast_float_d(&orbit->frames_left);
    return 0;
}
