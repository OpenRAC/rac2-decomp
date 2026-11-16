#include "common.h"

typedef struct { float f[4]; } __attribute__((aligned(16))) V;
typedef struct { float a, va, b, vb, ang, z, vz; } S_9f38;
typedef struct { u8 p0[0x15C]; float f15C; u8 p1[0x348-0x160]; short s348; u8 p2[0x2290-0x34A]; u8 *p2290; u8 p3[0x22A0-0x2294]; int i22A0; u8 p4[0x22B5-0x22A4]; u8 b22B5; } HeroInput;
typedef struct { u8 p0[0x100]; float f100,f104,f108,f10C; u8 p1[0x1A0-0x110]; int i1A0; } Controller;
extern HeroInput g_hero_state;
extern Controller g_pad_state;
typedef struct { u8 pad[0x290]; short phase; } CamGlobal;
extern CamGlobal D_L00_001B8C80_1;
extern char *g_camera_def_table;
extern int g_effects_volume[] __attribute__((sda));
extern int g_hero_height_zone_active __attribute__((sda));
extern float g_cam_aligned_speed_min __attribute__((sda));
extern float g_zoom_fov_value_a __attribute__((sda));
extern float g_zoom_fov_value_b __attribute__((sda));
extern float g_zoom_fov_value_c __attribute__((sda));
extern float g_zoom_fov_value_d __attribute__((sda));
void cam_build_aim_from_hero(void *);
void vec_scale_to_length(void *,void *,float);
void FastVecCross(void *,void *,void *);
void FastVecAdd(void *,void *,void *);
float IntToFloat(int);
float math_fabs(float);
float math_step_spring_damper_clamped(float,float,float,float,float,float *);
void math_apply_axis_rotation_to_quat(void *,void *,void *,float);
float FastAddRotations(float,float);
float fast_subtract_rotations(float,float);
int coll_test_point(void *,int,void *,float);

/* Adapted from RAC1 update_hero_aligned_camera_from_input, camera_modes_and_scripts.c. */
/* Turns the aligned camera left, right, up and down from the control stick and keeps it from tilting too far. */
void cam_aligned_update_from_input(u8 *camera) {
    V up;
    V side;
    V d;
    S_9f38 *state;
    float stick, turn, speed;
    char *params = *(char **)(g_camera_def_table + *(short *)(camera + 0x84) * 0x20 + 0x1C);
    state = *(S_9f38 **)(camera + 0x70);
    cam_build_aim_from_hero(camera);
    vec_scale_to_length(&up, g_hero_state.p2290 + 0xE0, 1.0f);
    if (D_L00_001B8C80_1.phase == 0 && g_hero_state.b22B5 == 0) g_hero_state.b22B5 = 1;
    stick = -g_pad_state.f108;
    if (stick == 0.0f) stick = -g_pad_state.f100;
    if (stick == 0.0f) stick = IntToFloat((g_pad_state.i1A0 >> 15) & 1);
    if (stick == 0.0f) stick = -IntToFloat((g_pad_state.i1A0 >> 13) & 1);
    if (*(short *)(params + 0x26)) stick = 0.0f;
    turn = math_fabs(state->a);
    speed = g_cam_aligned_speed_min + (g_zoom_fov_value_a - g_cam_aligned_speed_min) * turn;
    state->a = turn = math_step_spring_damper_clamped(state->a, stick, g_zoom_fov_value_b, g_zoom_fov_value_c, g_zoom_fov_value_d, &state->va);
    if (turn != 0.0f) math_apply_axis_rotation_to_quat(camera, camera, &up, speed * turn);
    if (g_hero_state.f15C != 0.0f && g_hero_state.s348 == 0 && g_hero_height_zone_active == 0)
        math_apply_axis_rotation_to_quat(camera, camera, &up, g_hero_state.f15C);
    stick = -g_pad_state.f10C;
    if (stick == 0.0f) stick = -g_pad_state.f104;
    if (stick == 0.0f) stick = IntToFloat((g_pad_state.i1A0 >> 12) & 1);
    if (stick == 0.0f) stick = -IntToFloat((g_pad_state.i1A0 >> 14) & 1);
    if (D_L00_001B8C80_1.phase != 0 && g_hero_state.i22A0 == 2) stick = 0.0f;
    if (*(short *)(params + 0x26)) stick = 0.0f;
    if (g_effects_volume[1] == 0) stick = -stick;
    turn = math_fabs(state->b);
    speed = g_cam_aligned_speed_min + (g_zoom_fov_value_a - g_cam_aligned_speed_min) * turn;
    state->b = math_step_spring_damper_clamped(state->b, stick, g_zoom_fov_value_b, g_zoom_fov_value_c, g_zoom_fov_value_d, &state->vb);
    if (state->b != 0.0f) {
        float step, tilt, zero;
        FastVecCross(&side, camera, &up);
        step = speed * state->b;
        tilt = math_fabs(FastAddRotations(state->ang, step));
        if (1.1170108318328857f < tilt && math_fabs(state->ang) < tilt)
            step += -step * (fast_subtract_rotations(tilt, 1.1170108318328857f) * 2.86478853225708f);
        if (tilt >= 1.1152654886245728f && state->ang > 0.0f)
            state->z = math_step_spring_damper_clamped(state->z, 0.5f, 0.005f, 0.2f, 0.0f, &state->vz);
        else
            state->z = math_step_spring_damper_clamped(state->z, 0.0f, 0.005f, 0.2f, 0.0f, &state->vz);
        zero = 0.0f;
        d.f[0] = *(float *)(camera + 0);
        d.f[1] = *(float *)(camera + 4);
        d.f[3] = zero;
        d.f[2] = zero;
        vec_scale_to_length(&d, &d, state->z);
        FastVecAdd(camera + 0x30, camera + 0x30, &d);
        if (coll_test_point(camera + 0x30, 0x12, g_hero_state.p2290, 0.3f))
            state->z = math_step_spring_damper_clamped(state->z, zero, 0.005f, 0.2f, zero, &state->vz);
        tilt = FastAddRotations(state->ang, step);
        if (math_fabs(tilt) > 1.4660767316818237f)
            { float limit = 1.4660767316818237f; if (!(zero < tilt)) limit = -1.4660767316818237f; step = fast_subtract_rotations(limit, state->ang); }
        math_apply_axis_rotation_to_quat(camera, camera, &side, step);
        state->ang = FastAddRotations(state->ang, step);
    }
    vec_scale_to_length(camera, camera, 1.0f);
    FastVecCross(camera + 0x10, camera, &up);
    vec_scale_to_length(camera + 0x10, camera + 0x10, 1.0f);
    FastVecCross(camera + 0x20, camera + 0x10, camera);
    *(short *)(params + 0x26) = 0;
}
