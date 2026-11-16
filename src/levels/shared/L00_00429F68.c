#include "common.h"

/* Partial layouts measured from the descriptor and hero accesses below. */
typedef struct Row_429F68 {
    float position[3];
    char pad[8];
    float pitch;
    float yaw;
    char *params;
} Row_429F68;

extern char *g_camera_def_table __attribute__((section(".sdata")));
extern char *g_follow_camera_object;
typedef struct Hero_429F68 {
    char pad[0x80];
    float position[4];
    char pad90[0x230];
    float axis[4];
} Hero_429F68;
extern Hero_429F68 D_00189E20_6;
extern float func_00283248_1(float, float), FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float), math_fast_sin_or_cos_b(float), math_fast_sin_or_cos_a(float);
extern void FastVecSub(char *, char *, char *);
extern float FastVecDot(char *, char *), FastVecLength(char *);
extern void FastVecScale(char *, char *, float);
extern void func_00282CC0_4(char *, char *, char *);
extern int cam_claim_request_slot(char *);
extern int cam_release_request_slot(char *);
extern int cam_test_trigger_volumes(char *);
extern int g_pad_pressed_flags;
extern float math_fabs(float);
extern void follow_camera_set_distance(int, float, float);
extern void cam_set_snap_flag(void);
extern void follow_camera_set_height(float, float);
extern void cam_set_aim_offset_target(int, float, float);
extern void cam_set_tuning_value(float);
extern void set_follow_camera_orbit_clamp_mode(int);
extern void cam_set_turn_limits(float, float, float);

/* Initializes and updates the aim - camera volume, including follow - camera offsets. */
void UpdateVolumeAimCamera(char *camera)
{
    float position[4] __attribute__((aligned(16)));
    char to_position[16] __attribute__((aligned(16)));
    char gravity_offset[16] __attribute__((aligned(16)));
    char horizontal[16] __attribute__((aligned(16)));
    char *params = *(char **)(g_camera_def_table + *(short *)(camera + 0x84)*32 + 0x1C);
    char *camera_position, *state, *reset, *tail, *follow, *snap, *rig;
    float yaw, height, tangent, pitch;
    if (cam_test_trigger_volumes(camera)) {
        if (cam_claim_request_slot(camera)<=0) {
            if (*(int *)(params + 0x20)) *(short *)(params + 0x26) = 1;
            *(int *)(params + 0x20) = 0;
            return;
        }
        if (!(g_pad_pressed_flags&4)) goto run;
    }
    if (*(int *)(params + 0x20)) *(short *)(params + 0x26) = 1;
    *(int *)(params + 0x20) = 0;
    cam_release_request_slot(camera);
    return;
run:
    if (*(int *)(params + 0x20)<2) {
        if (*(float *)(params + 0x2C)==0.0f && *(float *)(params + 0x30)==0.0f) {
            char *table = g_camera_def_table;
            *(float *)(params + 0x2C) = *(float *)(table + *(short *)(camera + 0x84)*32 + 0x14);
            *(float *)(params + 0x30) = *(float *)(table + *(short *)(camera + 0x84)*32 + 0x18);
        }
        yaw = func_00283248_1(
            D_00189E20_6.position[0] - ((Row_429F68 *)g_camera_def_table)[*(short *)(camera + 0x84)].position[0],
            D_00189E20_6.position[1] - ((Row_429F68 *)g_camera_def_table)[*(short *)(camera + 0x84)].position[1]);
        if (FastDiffRots(*(float *)(params + 0x30), yaw)>0.03490658849477768f)
            *(float *)(params + 0x44) = fast_subtract_rotations(*(float *)(params + 0x30), yaw);
        position[0] = ((Row_429F68 *)g_camera_def_table)[*(short *)(camera + 0x84)].position[0];
        position[1] = ((Row_429F68 *)g_camera_def_table)[*(short *)(camera + 0x84)].position[1];
        position[2] = ((Row_429F68 *)g_camera_def_table)[*(short *)(camera + 0x84)].position[2];
        position[3] = 0.0f;
        FastVecSub(to_position, (char *)position, (char *)D_00189E20_6.position);
        height = FastVecDot(to_position, (char *)D_00189E20_6.axis);
        FastVecScale(gravity_offset, (char *)D_00189E20_6.axis, height);
        FastVecSub(horizontal, to_position, gravity_offset);
        *(float *)(params + 0x38) = FastVecLength(horizontal);
        *(float *)(params + 0x3C) =  - height;
        pitch = *(float *)(params + 0x2C);
        if (math_fabs(pitch)==1.5707964897155762f) *(float *)(params + 0x40) = 0.0f;
        else {
            tangent = math_fast_sin_or_cos_b(pitch);
            tangent/=math_fast_sin_or_cos_a(pitch);
            *(float *)(params + 0x40) = *(float *)(params + 0x3C) - *(float *)(params + 0x38)*tangent;
        }
        camera_position = g_follow_camera_object;
        rig = *(char **)(camera_position + 0x70);
        camera_position+=0x30;
        follow = rig + 0x60;
        tail = rig + 0x160;
        snap = rig + 0x1F0;
        state = rig;
        reset = state + 0x20;
        qcopy(camera_position, position);
        *(float *)(tail + 0x2C) = *(float *)(params + 0x38);
        *(float *)(tail + 0x30) = *(float *)(params + 0x3C);
        *(float *)(reset + 0x28) = *(float *)(params + 0x44);
        *(float *)(follow + 0xB0) = *(float *)(params + 0x40);
        FastVecScale(gravity_offset, (char *)D_00189E20_6.axis,  - *(float *)(tail + 0x30));
        func_00282CC0_4(state + 0xB0, (char *)D_00189E20_6.position, gravity_offset);
        FastVecSub(tail, (char *)position, state + 0xB0);
        qcopy(state + 0x170, tail);
        FastVecScale(gravity_offset, (char *)D_00189E20_6.axis,  - *(float *)(follow + 0xB0));
        func_00282CC0_4(state + 0xA0, (char *)D_00189E20_6.position, gravity_offset);
        qcopy(state + 0xF0, state + 0xA0);
        qcopy(follow, (char *)D_00189E20_6.position);
        qcopy(state + 0xC0, follow);
        qcopy(state, camera_position);
        qcopy(state + 0x210, camera_position);
        *(int *)(snap + 0x30) = 0;
        *(int *)(reset + 0x14) = 0;
        *(float *)(reset + 4) = *(float *)(follow + 0xB0);
        {
            float zero = *(float *)(reset + 0x14);
            float distance = *(float *)(tail + 0x30);
            *(float *)(reset + 8) = distance;
            *(short *)(reset + 2) = 0;
            *(float *)(reset + 0x18) = zero;
            *(float *)(reset + 0x10) = zero;
            *(float *)(reset + 0xC) = zero;
        }
    }
    ++*(int *)(params + 0x20);
    if (*(int *)(params + 0x20)>200) *(int *)(params + 0x20) = 200;
    if (*(float *)(params + 0x38)!=0.0f) {
        follow_camera_set_distance(0, *(float *)(params + 0x38), 0.003f);
        cam_set_snap_flag();
    }
    if (*(float *)(params + 0x3C)!=0.0f) follow_camera_set_height(*(float *)(params + 0x3C), 0.003f);
    if (*(float *)(params + 0x40)!=0.0f) cam_set_aim_offset_target(0, *(float *)(params + 0x40), 0.005f);
    if (*(float *)(params + 0x28)!=0.0f) cam_set_tuning_value(*(float *)(params + 0x28)*0.01745329424738884f);
    if (*(short *)(params + 0x24)==0) set_follow_camera_orbit_clamp_mode(0);
    if (*(float *)(params + 0x44)!=0.0f) cam_set_turn_limits(*(float *)(params + 0x44), 60.0f, 60.0f);
}
