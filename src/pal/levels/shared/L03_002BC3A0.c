#include "include_asm.h"

#include "common.h"
typedef union { int quad __attribute__((mode(TI))); struct { float x, y, z, w; } f; } HopVector;
typedef struct {
    HopVector field_0;
    unsigned char pad_10[0x10];
    HopVector field_20;
    unsigned char pad_30[0x68];
    float rot_z;
    unsigned char pad_9C[0x54];
    float vel_x;
    float vel_y;
    unsigned char pad_F8[0x68];
    HopVector field_160;
    unsigned char pad_170[0x4];
    float field_174;
    unsigned char pad_178[0x18];
    HopVector field_190;
    float facing_angle;
    float field_1A4;
    float field_1A8;
    unsigned char pad_1AC[0x4];
    float field_1B0;
    float field_1B4;
    int state_time;
    unsigned char pad_1BC[0x18c];
    short field_348;
    short field_34A;
    unsigned char pad_34C[0x108];
    float field_454;
    unsigned char pad_458[0x18];
    HopVector field_470;
    HopVector field_480;
    unsigned char pad_490[0x4];
    float field_494;
    unsigned char pad_498[0x6];
    unsigned char field_49E;
    unsigned char pad_49F[0xf];
    short field_4AE;
    unsigned char pad_4B0[0xc];
    float field_4BC;
    float field_4C0;
    float field_4C4;
    unsigned char pad_4C8[0xc];
    int field_4D4;
    float field_4D8;
    float field_4DC;
    unsigned char pad_4E0[0x10];
    HopVector field_4F0;
    unsigned char pad_500[0x20];
    float field_520;
    short field_524;
    unsigned char pad_526[0x7];
    unsigned char field_52D;
    unsigned char pad_52E[0x532];
    HopVector field_A60;
    unsigned char pad_A70[0x14];
    float field_A84;
    unsigned char pad_A88[0x1b0];
    float anim_time;
    unsigned char pad_C3C[0x804];
    HopVector field_1440;
    unsigned char pad_1450[0x4];
    short field_1454;
    unsigned char pad_1456[0x2];
    float field_1458;
    unsigned char pad_145C[0xe38];
    int state;
    unsigned char pad_2298[0x4];
    int field_229C;
    unsigned char pad_22A0[0x23];
    unsigned char field_22C3;
    unsigned char pad_22C4[0x1f4];
    float field_24B8;
} HopPlayer;
#define HOP_PLAYER (*(HopPlayer *)D_L03_00189E20)
extern int g_hero_l03_block_flag[] __attribute__((sda));
extern float g_hero_camera_speed_params[] __attribute__((sda));
typedef struct {
    unsigned char pad_0[0x158];
    float angle;
    unsigned char pad_15C[0x214];
    HopVector basis;
} HopSavedState;
extern unsigned char g_hero_l03_state_alias[];
#define HOP_SAVED (*(HopSavedState *)D_L03_001B9840)
extern void hero_build_move_impulse(float, float);
extern void hero_approach_speed(float, float);
extern void cam_set_view_space_vector_length(float, void *, void *);
extern void cam_offset_point_by_side_direction(void *, void *, float);
extern void hero_steer_heading(float, float, float, int);
extern void func_PAL_L01_002B6870(float);
extern float FastVecDot(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void cam_set_view_space_height(float, void *, void *);
extern float FastDiffRots(float, float);
extern float math_approach_with_velocity(float *, float *, int, float, float, float, float);
extern float fast_subtract_rotations(float, float);
extern void hero_start_pose_offset(float, float, float);
extern float cam_get_view_space_vector_length(void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern unsigned char g_hero_l03_state_block[];
extern float ApproachValue(float *, float, float);
extern void FastVecAdd(void *, void *, void *);

/* Per-state airborne steering of the player: velocity, facing and speed targets. */
void func_PAL_L03_002BC3A0(void) {
    HopVector temp;
    float step, scale;

    if (HOP_PLAYER.state == 10) {
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(&HOP_PLAYER.field_160, &HOP_PLAYER.field_A60);
        HOP_PLAYER.field_1B4 = HOP_PLAYER.field_174;
        return;
    }

    if (HOP_PLAYER.state == 0x10) {
        if (HOP_PLAYER.state_time > 0x2D)
            ApproachValue(&HOP_PLAYER.field_520, 0.010000001f, 0.0028000001f);
        if (HOP_PLAYER.state_time <= 0x2D)
            HOP_PLAYER.field_1B0 = HOP_PLAYER.field_454;
        else
            HOP_PLAYER.field_1B0 = 0.07000001f;
        hero_approach_speed(0.0176f, 0.018000001f);
        cam_set_view_space_vector_length(0.0f, &HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x);
        cam_offset_point_by_side_direction(&HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x, HOP_PLAYER.field_1B4);
        return;
    }

    if (HOP_PLAYER.state == 0x1B) {
        if (HOP_PLAYER.state_time > 0x21) {
            hero_steer_heading(0.057600003f, 0.28800002f, 0.30019668f, 0);
            func_PAL_L01_002B6870(0.008f);
        }
        if (HOP_PLAYER.anim_time >= 13.0f && HOP_PLAYER.anim_time <= 30.0f) {
            if (HOP_PLAYER.anim_time > 27.0f)
                ApproachValue(&HOP_PLAYER.field_4BC, 0.0f, 0.0032000002f);
            else
                ApproachValue(&HOP_PLAYER.field_4BC, 0.040000003f, 0.0032000002f);
        }
        temp.f.x = HOP_PLAYER.field_4BC;
        temp.f.y = 0.0f;
        temp.f.z = FastVecDot(&HOP_PLAYER.vel_x, &HOP_PLAYER.field_20);
        matrix_mul_vec3(&HOP_PLAYER.vel_x, &temp, &HOP_PLAYER);
        return;
    }

    if (HOP_PLAYER.state == 0x48) {
        if (HOP_PLAYER.anim_time >= 5.0f && HOP_PLAYER.anim_time <= 18.0f) {
            if (HOP_PLAYER.anim_time > 15.0f)
                ApproachValue(&HOP_PLAYER.field_4BC, 0.0f, 0.0032000002f);
            else
                ApproachValue(&HOP_PLAYER.field_4BC, 0.025000002f, 0.0032000002f);
        }
        temp.f.x = HOP_PLAYER.field_4BC;
        temp.f.y = 0.0f;
        temp.f.z = FastVecDot(&HOP_PLAYER.vel_x, &HOP_PLAYER.field_20);
        matrix_mul_vec3(&HOP_PLAYER.vel_x, &temp, &HOP_PLAYER);
        return;
    }

    if (HOP_PLAYER.state == 0xB) {
        HOP_PLAYER.facing_angle = HOP_PLAYER.field_4C4;
        qcopy(&HOP_PLAYER.field_190, &HOP_PLAYER.field_480);
        hero_steer_heading(0.057600003f, 0.28800002f, 0.13962635f, 0);
        if (HOP_PLAYER.field_4D4 != 3)
            HOP_PLAYER.field_1B4 = HOP_PLAYER.field_4D8;
        else
            HOP_PLAYER.field_1B4 = 0.0f;
        if (HOP_PLAYER.field_52D) {
            step = HOP_PLAYER.field_24B8 * 0.10000001f;
            if (step < 0.040000003f)
                step = 0.040000003f;
            ApproachValue(&HOP_PLAYER.field_4DC, step, 0.014800001f);
            HOP_PLAYER.field_1B4 = HOP_PLAYER.field_174;
        } else {
            if (HOP_PLAYER.field_49E && HOP_PLAYER.field_4AE <= 9)
                ApproachValue(&HOP_PLAYER.field_4DC, 0.0f, 0.0032000002f);
            else
                ApproachValue(&HOP_PLAYER.field_4DC, 0.084f, 0.0032000002f);
        }
        if (!HOP_PLAYER.field_22C3) {
            HOP_PLAYER.vel_x = math_fast_sin_or_cos_a(HOP_PLAYER.field_4C0);
            HOP_PLAYER.vel_x *= HOP_PLAYER.field_4DC;
            HOP_PLAYER.vel_y = math_fast_sin_or_cos_b(HOP_PLAYER.field_4C0);
            HOP_PLAYER.vel_y *= HOP_PLAYER.field_4DC;
        } else {
            cam_set_view_space_vector_length(HOP_PLAYER.field_4DC, &temp, &HOP_PLAYER.field_470);
            cam_set_view_space_height(0.0f, &temp, &temp);
            cam_set_view_space_vector_length(0.0f, &HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x);
            FastVecAdd(&HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x, &temp);
        }
        if (!HOP_PLAYER.field_22C3 && !HOP_PLAYER.field_52D) {
            scale = HOP_PLAYER.field_4D8 * math_fast_sin_or_cos_b(FastDiffRots(HOP_PLAYER.field_4C4, HOP_PLAYER.field_4C0));
            HOP_PLAYER.vel_x += math_fast_sin_or_cos_a(HOP_PLAYER.field_4C4) * scale;
            HOP_PLAYER.vel_y += math_fast_sin_or_cos_b(HOP_PLAYER.field_4C4) * scale;
        }
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(&HOP_PLAYER.field_160, &HOP_PLAYER.field_A60);
        return;
    }

    if (HOP_PLAYER.state == 0x11) {
        HOP_PLAYER.facing_angle = HOP_PLAYER.field_4F0.f.w;
        qcopy(&HOP_PLAYER.field_190, &HOP_PLAYER.field_4F0);
        if (HOP_PLAYER.state_time > 7)
            hero_steer_heading(0.060480002f, 0.28800002f, 0.23736483f, -1);
        if (HOP_PLAYER.state_time > 6) {
            if (!HOP_PLAYER.field_348) {
                HOP_PLAYER.vel_x = math_fast_sin_or_cos_a(HOP_PLAYER.facing_angle) * 0.09800001f;
                HOP_PLAYER.vel_y = math_fast_sin_or_cos_b(HOP_PLAYER.facing_angle) * 0.09800001f;
            } else {
                cam_set_view_space_vector_length(0.0f, &HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x);
                vec_scale_to_length(&temp, &HOP_PLAYER.field_190, 0.09800001f);
                FastVecAdd(&HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x, &temp);
            }
        }
        HOP_PLAYER.field_1B4 = HOP_PLAYER.field_174;
        return;
    }

    if (HOP_PLAYER.state == 0x81 && !g_hero_l03_block_flag[0]) {
        hero_steer_heading(0.057600003f, 0.28800002f, HOP_PLAYER.field_494, 0);
        HOP_PLAYER.field_1B4 = 0.0f;
        return;
    }

    if (HOP_PLAYER.state == 0x2C) {
        float angle = HOP_PLAYER.rot_z;
        float delta;

        HOP_PLAYER.field_1A8 = math_approach_with_velocity(&angle, &HOP_PLAYER.field_1A4, 0, HOP_PLAYER.facing_angle,
                                             0.02592f, 0.28800002f, 0.14660768f);
        delta = fast_subtract_rotations(angle, HOP_PLAYER.rot_z);
        hero_start_pose_offset(0.0f, 0.0f, delta);
    } else {
        float oldAngle = HOP_PLAYER.facing_angle;

        qcopy(&temp, &HOP_PLAYER.field_190);
        if (HOP_PLAYER.field_1454) {
            HOP_PLAYER.facing_angle = HOP_SAVED.angle;
            qcopy(&HOP_PLAYER.field_190, &HOP_SAVED.basis);
        }
        hero_steer_heading(0.057600003f, 0.28800002f, HOP_PLAYER.field_494, 0);
        if (HOP_PLAYER.field_1454) {
            HOP_PLAYER.field_1458 = oldAngle;
            qcopy(&HOP_PLAYER.field_1440, &temp);
            HOP_PLAYER.facing_angle = oldAngle;
            qcopy(&HOP_PLAYER.field_190, &HOP_PLAYER.field_1440);
        }
    }

    hero_build_move_impulse(0.7f, 0.0f);
    qcopy(&HOP_PLAYER.field_160, &HOP_PLAYER.field_A60);

    step = 0.008f;
    if (HOP_PLAYER.field_1B0 < g_hero_camera_speed_params[0] * 0.004f) {
        if (HOP_PLAYER.field_229C == 2) {
            float brake = HOP_PLAYER.field_A84;
            float angle = cam_get_view_space_vector_length(&HOP_PLAYER.vel_x);

            ApproachValue(&angle, 0.0f, brake);
            cam_set_view_space_vector_length(angle, &HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x);
            return;
        }
        if (HOP_PLAYER.field_34A)
            step = 0.0044f;
        else
            step = HOP_PLAYER.field_524 ? 0.00080000004f : 0.0032000002f;
    }

    func_PAL_L01_002B6870(step);
}

