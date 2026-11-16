#include "include_asm.h"

#include "common.h"
extern char *g_camera_def_table __attribute__((section(".sdata")));
extern char *g_follow_camera_object;
extern char g_hero_position[];
extern float math_fabs(float);
extern float vec_distance_xy(char *, char *);
extern int IsPointInCuboid(char *, int);
extern int coll_point_inside_record_volume(char *, int);
extern int coll_is_point_inside_unit_sphere(char *, int);
typedef struct { char pad[0x30]; char pos[16]; char rest[0x40]; } Entry_b0898;
extern Entry_b0898 *g_aranos_launch_poses __attribute__((section(".sdata")));
typedef struct {
 char pad[0x80]; char position[16]; char pad90[0x174-0x90]; float speed; char pad178[0x2294-0x178]; int mode;
 char pad2298[0x22B4-0x2298]; unsigned char flag;
} Global_b0898;
extern Global_b0898 D_00189E20_b0898;

/* Tests whether the hero is inside any of the trigger's volumes (cuboid, record volume, sphere), after
   checking the camera is free and the hero is slow enough; returns 1 when it is. */
int cam_test_trigger_volumes_pal(char *trigger)
{
    char *owner = g_follow_camera_object;
    char *sub = *(char **)(owner + 0x70);
    char *move = sub + 0x160;
    char *rot = sub + 0x1C0;
    char *params = *(char **)(g_camera_def_table + *(short *)(trigger + 0x84) * 32 + 28);
    unsigned int mode;
    if (*(short *)(owner + 0x86) != 0) return 0;
    mode = D_00189E20_b0898.flag - 1U < 2U;
    if (*(short *)(params + 0x4A) && !mode) return 0;
    if (*(short *)(params + 0x48) && mode) return 0;
    if (*(int *)(params + 0x34)) {
        if (math_fabs(*(float *)(move + 0x34)) > 0.01f) return 0;
        if (math_fabs(*(float *)(rot + 8)) > 0.01f) return 0;
    }
    if ((unsigned int)(D_00189E20_b0898.mode - 0x62) >= 2 && D_00189E20_b0898.speed > 0.020000001f) return 0;
    if (*(int *)(params + 0xC) >= 0) {
        if (D_00189E20_b0898.mode == 0x62 && vec_distance_xy(D_00189E20_b0898.position, g_aranos_launch_poses[*(int *)(params + 0xC)].pos) < 3.0f) return 1;
        if (IsPointInCuboid(g_hero_position, *(int *)(params + 0xC))) return 1;
    }
    if (*(int *)(params + 0x10) >= 0) {
        if (D_00189E20_b0898.mode == 0x62 && vec_distance_xy(D_00189E20_b0898.position, g_aranos_launch_poses[*(int *)(params + 0x10)].pos) < 3.0f) return 1;
        if (coll_point_inside_record_volume(g_hero_position, *(int *)(params + 0x10))) return 1;
    }
    if (*(int *)(params + 8) >= 0) {
        if (D_00189E20_b0898.mode == 0x62 && vec_distance_xy(D_00189E20_b0898.position, g_aranos_launch_poses[*(int *)(params + 8)].pos) < 3.0f) return 1;
        if (coll_is_point_inside_unit_sphere(g_hero_position, *(int *)(params + 8))) return 1;
    }
    *(short *)(params + 0x26) = 1;
    return 0;
}


typedef struct Row_429F68 {
    float position[3];
    char pad[8];
    float pitch;
    float yaw;
    char *params;
} Row_429F68;
typedef struct Hero_429F68 {
    char pad[0x80];
    float position[4];
    char pad90[0x230];
    float axis[4];
} Hero_429F68;
extern Hero_429F68 D_00189E20_6;
extern float mat_fast_helper_a(float, float), FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float), math_fast_sin_or_cos_b(float), math_fast_sin_or_cos_a(float);
extern void FastVecSub(char *, char *, char *);
extern float FastVecDot(char *, char *), FastVecLength(char *);
extern void FastVecScale(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern int cam_claim_request_slot(char *);
extern int cam_release_request_slot(char *);
extern int cam_test_trigger_volumes_pal(char *);
extern int g_pad_pressed_flags;
extern void follow_camera_set_distance(int, float, float);
extern void cam_set_snap_flag(void);
extern void follow_camera_set_height(float, float);
extern void cam_set_aim_offset_target(int, float, float);
extern void cam_set_tuning_value(float);
extern void set_follow_camera_orbit_clamp_mode(int);
extern void cam_set_turn_limits_pal(float, float, float);

/* Initializes and updates the aim - camera volume, including follow - camera offsets. */
void UpdateVolumeAimCamera_pal(char *camera)
{
    float position[4] __attribute__((aligned(16)));
    char to_position[16] __attribute__((aligned(16)));
    char gravity_offset[16] __attribute__((aligned(16)));
    char horizontal[16] __attribute__((aligned(16)));
    char *params = *(char **)(g_camera_def_table + *(short *)(camera + 0x84)*32 + 0x1C);
    char *camera_position, *state, *reset, *tail, *follow, *snap, *rig;
    float yaw, height, tangent, pitch;
    if (cam_test_trigger_volumes_pal(camera)) {
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
        yaw = mat_fast_helper_a(
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
        FastVecAdd(state + 0xB0, (char *)D_00189E20_6.position, gravity_offset);
        FastVecSub(tail, (char *)position, state + 0xB0);
        qcopy(state + 0x170, tail);
        FastVecScale(gravity_offset, (char *)D_00189E20_6.axis,  - *(float *)(follow + 0xB0));
        FastVecAdd(state + 0xA0, (char *)D_00189E20_6.position, gravity_offset);
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
    if (*(int *)(params + 0x20)>167) *(int *)(params + 0x20) = 167;
    if (*(float *)(params + 0x38)!=0.0f) {
        follow_camera_set_distance(0, *(float *)(params + 0x38), 0.003f);
        cam_set_snap_flag();
    }
    if (*(float *)(params + 0x3C)!=0.0f) follow_camera_set_height(*(float *)(params + 0x3C), 0.003f);
    if (*(float *)(params + 0x40)!=0.0f) cam_set_aim_offset_target(0, *(float *)(params + 0x40), 0.005f);
    if (*(float *)(params + 0x28)!=0.0f) cam_set_tuning_value(*(float *)(params + 0x28)*0.01745329424738884f);
    if (*(short *)(params + 0x24)==0) set_follow_camera_orbit_clamp_mode(0);
    if (*(float *)(params + 0x44)!=0.0f) cam_set_turn_limits_pal(*(float *)(params + 0x44), 60.0f, 60.0f);
}


#define SDA_OBJ __attribute__((section(".sdata")))
extern char *g_camera_def_table SDA_OBJ;
extern char g_cam_object_table_a[] SDA_OBJ;
extern char g_cam_object_table_b[] SDA_OBJ;
extern char g_cam_object_table_c[] SDA_OBJ;
extern char g_cam_object_table_d[] SDA_OBJ;
extern int g_game_l00_mode __attribute__((sda));
extern void UpdateVolumeAimCamera_pal(char *);

/* Looks the owner's table entry up (index half-word at +0x84, 0x20 bytes per entry, the
   entry's own pointer at +0x1C) and clears its flag half-word at +0x26 and its word at
   +0x20, but only when the entry is still idle, the global gate allows it and the extra
   check accepts the owner. */
int cam_update_entry_reset_pal(char *trigger)
{
    char *params = *(char **)(g_camera_def_table + *(short *)(trigger + 0x84) * 0x20 + 0x1C);

    if (*(short *)(params + 0x26) != 0) {
        return 0;
    }
    if (g_game_l00_mode != 0) {
        if (cam_test_trigger_volumes_pal(trigger) != 0) {
            *(short *)(params + 0x26) = 0;
            *(int *)(params + 0x20) = 0;
            return 0;
        }
    }
    UpdateVolumeAimCamera_pal(trigger);
    return 0;
}

