#include "common.h"

/* func_PAL_L04_002DCE68, the PAL copy of func_L04_002DCE78: the same C, where speeds become x6/5,
   accelerations x36/25 and frame counts x5/6 for 50 Hz. */

extern void func_00282CC0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(float *, float *, float);
extern void func_00283098(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283BE0(float, float);
extern float func_00283C80(float, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern float func_002AA2E8(float *, float, float);
extern void func_L00_002AA0F0(float, float, float);
extern void func_L00_002B39F0(int, float);
extern void func_L00_002B3EF8(int, float, float, float);
extern void func_L00_002B41B8(float, float);
extern void func_L00_002B47A8(void *, void *, int, float, float);
extern void func_L00_002B54F8(float, float);
extern void func_L00_002B6198(float);
extern void func_L00_002D3798(void *, void *, float);
extern float func_L00_002D3A58(void *);
extern void func_L00_002D3B58(void *, void *, float);
extern void func_L00_002D3BD8(void *, void *, float);
extern int D_001A8FF0 MACRO_ADDR;
extern float D_001A7DC0 MACRO_ADDR;
extern unsigned char D_L04_001B9540[];
typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} HopVector;
typedef struct {
    unsigned char pad0[0x20];
    HopVector field20;
    unsigned char pad30[0x68];
    float yaw;
    unsigned char pad9C[0x54];
    HopVector velocity;
    unsigned char pad100[0x60];
    HopVector momentum;
    unsigned char pad170[0x4];
    float flat_speed;
    unsigned char pad178[0x18];
    HopVector move_dir;
    float move_yaw;
    float yaw_rate;
    float yaw_error;
    unsigned char pad1AC[0x4];
    float target_speed;
    float ground_speed;
    int state_timer;
    unsigned char pad1BC[0x164];
    float field320;
    unsigned char pad324[0x24];
    short field348;
    short field34A;
    unsigned char pad34C[0x108];
    float field454;
    unsigned char pad458[0x18];
    HopVector field470;
    HopVector field480;
    unsigned char pad490[0x4];
    float field494;
    unsigned char pad498[0x6];
    unsigned char field49E;
    unsigned char pad49F[0xF];
    short field4AE;
    unsigned char pad4B0[0xC];
    float ledge_jump_speed;
    float high_jump_drift_yaw;
    float takeoff_yaw;
    unsigned char pad4C8[0xC];
    int field4D4;
    float air_target_speed;
    float high_jump_drift_speed;
    unsigned char pad4E0[0x10];
    HopVector field4F0;
    unsigned char pad500[0x20];
    float jump_gravity;
    short field524;
    unsigned char pad526[0x2];
    short field528;
    unsigned char pad52A[0x3];
    unsigned char field52D;
    unsigned char pad52E[0x532];
    HopVector move_impulse;
    unsigned char padA70[0x14];
    float fieldA84;
    unsigned char padA88[0x1B0];
    float anim_frame;
    unsigned char padC3C[0x804];
    HopVector field1440;
    unsigned char pad1450[0x4];
    short field1454;
    unsigned char pad1456[0x2];
    float field1458;
    unsigned char pad145C[0x36];
    unsigned char field1492;
    unsigned char pad1493[0xE01];
    int state;
    unsigned char pad2298[0x4];
    int control_mode;
    unsigned char pad22A0[0x23];
    unsigned char field22C3;
    unsigned char pad22C4[0x1F4];
    float stick_magnitude;
} HopPlayer;
typedef struct {
    unsigned char pad0[0x158];
    float yaw;
    unsigned char pad15C[0x370 - 0x15C];
    HopVector direction;
} HopSavedState;
#define HOP_SAVED (*(HopSavedState *)D_L04_001B9540)
#define HOP_PLAYER (*(HopPlayer *)&D_00189E20)

extern f32 func_002AA898(f32 *position, f32 target, f32 *velocity,
                         f32 acceleration, f32 damping, f32 limit, s32 direction);
extern int D_00189E20;

/* Per-state airborne steering; shares the hop-velocity state cases with
   rac1-decomp's hero_update_hop_velocity. */
void func_PAL_L04_002DCE68(void) {
    float probe_start[4], probe_end[4], yaw, speed, rate;

    if (HOP_PLAYER.state == 10) {
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(HOP_PLAYER.momentum.f, HOP_PLAYER.move_impulse.f);
        HOP_PLAYER.ground_speed = HOP_PLAYER.flat_speed;
    } else if (HOP_PLAYER.state == 16) {
        if (HOP_PLAYER.state_timer >= 46) {
            func_002AA2E8(&HOP_PLAYER.jump_gravity, 0.010000001f, 0.0028000001f);
        }
        if (HOP_PLAYER.state_timer < 46) {
            HOP_PLAYER.target_speed = HOP_PLAYER.field454;
        } else {
            HOP_PLAYER.target_speed = 0.07000001f;
        }
        func_L00_002B41B8(0.0176f, 0.018000001f);
        func_L00_002D3BD8(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, 0.0f);
        func_L00_002D3798(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, HOP_PLAYER.ground_speed);
    } else if (HOP_PLAYER.state == 27) {
        if (HOP_PLAYER.state_timer >= 34) {
            func_L00_002B3EF8(0, 0.057600003f, 0.28800002f, 0.30019668f);
            func_L00_002B6198(0.008f);
        }
        if (HOP_PLAYER.anim_frame >= 13.0f && HOP_PLAYER.anim_frame <= 30.0f) {
            if (HOP_PLAYER.anim_frame > 27.0f) {
                func_002AA2E8(&HOP_PLAYER.ledge_jump_speed, 0.0f, 0.0032000002f);
            } else {
                func_002AA2E8(&HOP_PLAYER.ledge_jump_speed, 0.040000003f, 0.0032000002f);
            }
        }
        probe_start[1] = 0.0f;
        probe_start[0] = HOP_PLAYER.ledge_jump_speed;
        probe_start[2] = func_00282DB0(HOP_PLAYER.velocity.f, HOP_PLAYER.field20.f);
        func_00283098(HOP_PLAYER.velocity.f, probe_start, &HOP_PLAYER);
    } else if (HOP_PLAYER.state == 11) {
        HOP_PLAYER.move_yaw = HOP_PLAYER.takeoff_yaw;
        qcopy(HOP_PLAYER.move_dir.f, HOP_PLAYER.field480.f);
        func_L00_002B3EF8(0, 0.057600003f, 0.28800002f, 0.13962635f);
        if (HOP_PLAYER.field4D4 != 3) {
            HOP_PLAYER.ground_speed = HOP_PLAYER.air_target_speed;
        } else {
            HOP_PLAYER.ground_speed = 0.0f;
        }
        if (HOP_PLAYER.field52D) {
            float drift = HOP_PLAYER.stick_magnitude * 0.10000001f;

            if (drift < 0.040000003f) drift = 0.040000003f;
            func_002AA2E8(&HOP_PLAYER.high_jump_drift_speed, drift, 0.014800001f);
            HOP_PLAYER.ground_speed = HOP_PLAYER.flat_speed;
        } else if (HOP_PLAYER.field49E && HOP_PLAYER.field4AE < 10) {
            func_002AA2E8(&HOP_PLAYER.high_jump_drift_speed, 0.0f, 0.0032000002f);
        } else {
            func_002AA2E8(&HOP_PLAYER.high_jump_drift_speed, 0.084f, 0.0032000002f);
        }
        if (!HOP_PLAYER.field22C3) {
            HOP_PLAYER.velocity.f[0] = func_00283180(HOP_PLAYER.high_jump_drift_yaw) * HOP_PLAYER.high_jump_drift_speed;
            HOP_PLAYER.velocity.f[1] = func_00283198(HOP_PLAYER.high_jump_drift_yaw) * HOP_PLAYER.high_jump_drift_speed;
        } else {
            func_L00_002D3BD8(probe_start, HOP_PLAYER.field470.f, HOP_PLAYER.high_jump_drift_speed);
            func_L00_002D3B58(probe_start, probe_start, 0.0f);
            func_L00_002D3BD8(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, 0.0f);
            func_00282CC0(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, probe_start);
        }
        if (!HOP_PLAYER.field22C3 && !HOP_PLAYER.field52D) {
            float drift = HOP_PLAYER.air_target_speed * func_00283198(func_00283C80(HOP_PLAYER.takeoff_yaw, HOP_PLAYER.high_jump_drift_yaw));

            HOP_PLAYER.velocity.f[0] += func_00283180(HOP_PLAYER.takeoff_yaw) * drift;
            HOP_PLAYER.velocity.f[1] += func_00283198(HOP_PLAYER.takeoff_yaw) * drift;
        }
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(HOP_PLAYER.momentum.f, HOP_PLAYER.move_impulse.f);
    } else if (HOP_PLAYER.state == 17) {
        HOP_PLAYER.move_yaw = HOP_PLAYER.field4F0.f[3];
        qcopy(HOP_PLAYER.move_dir.f, HOP_PLAYER.field4F0.f);
        if (HOP_PLAYER.state_timer >= 8) {
            func_L00_002B3EF8(-1, 0.060480002f, 0.28800002f, 0.23736483f);
        }
        if (HOP_PLAYER.state_timer >= 7) {
            if (!HOP_PLAYER.field348) {
                HOP_PLAYER.velocity.f[0] = func_00283180(HOP_PLAYER.move_yaw) * 0.09800001f;
                HOP_PLAYER.velocity.f[1] = func_00283198(HOP_PLAYER.move_yaw) * 0.09800001f;
            } else {
                func_L00_002D3BD8(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, 0.0f);
                func_00282F20(probe_start, HOP_PLAYER.move_dir.f, 0.09800001f);
                func_00282CC0(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, probe_start);
            }
        }
        HOP_PLAYER.ground_speed = HOP_PLAYER.flat_speed;
    } else if (HOP_PLAYER.state == 0x81 && !D_001A8FF0) {
        func_L00_002B3EF8(0, 0.057600003f, 0.28800002f, HOP_PLAYER.field494);
        HOP_PLAYER.ground_speed = 0.0f;
    } else {
        if (HOP_PLAYER.state == 44) {
            yaw = HOP_PLAYER.yaw;
            HOP_PLAYER.yaw_error = func_002AA898(&yaw, HOP_PLAYER.move_yaw, &HOP_PLAYER.yaw_rate,
                                      0.02592f, 0.28800002f, 0.14660768f, 0);
            {
                float delta = func_00283BE0(yaw, HOP_PLAYER.yaw);

                func_L00_002AA0F0(0.0f, 0.0f, delta);
            }
        } else {
            float saved = HOP_PLAYER.move_yaw;

            qcopy(probe_start, HOP_PLAYER.move_dir.f);
            if (HOP_PLAYER.field1454) {
                HOP_PLAYER.move_yaw = HOP_SAVED.yaw;
                qcopy(HOP_PLAYER.move_dir.f, HOP_SAVED.direction.f);
            }
            func_L00_002B3EF8(0, 0.057600003f, 0.28800002f, HOP_PLAYER.field494);
            if (HOP_PLAYER.field1454) {
                HOP_PLAYER.field1458 = saved;
                qcopy(HOP_PLAYER.field1440.f, probe_start);
                HOP_PLAYER.move_yaw = saved;
                qcopy(HOP_PLAYER.move_dir.f, HOP_PLAYER.field1440.f);
            }
        }
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(HOP_PLAYER.momentum.f, HOP_PLAYER.move_impulse.f);
        rate = 0.008f;
        if (HOP_PLAYER.target_speed < D_001A7DC0 * 0.004f) {
            if (HOP_PLAYER.control_mode == 2) {
                float decel = HOP_PLAYER.fieldA84;

                if (HOP_PLAYER.field1492) decel = 6.8e-05f;
                speed = func_L00_002D3A58(HOP_PLAYER.velocity.f);
                func_002AA2E8(&speed, 0.0f, decel);
                func_L00_002D3BD8(HOP_PLAYER.velocity.f, HOP_PLAYER.velocity.f, speed);
                return;
            }
            if (HOP_PLAYER.field34A) {
                rate = 0.0044f;
            } else if (HOP_PLAYER.field524) {
                rate = 0.00080000004f;
            } else {
                rate = 0.0032000002f;
            }
        }
        if (HOP_PLAYER.field528 && HOP_PLAYER.field1492) {
            rate = 0.00020000001f;
            if (HOP_PLAYER.stick_magnitude > 0.9f) {
                func_L00_002B47A8(probe_start, probe_end, 0, 0.5f, -1.5f);
                probe_start[0] += func_00283180(HOP_PLAYER.move_yaw) * 0.7f;
                probe_start[1] += func_00283198(HOP_PLAYER.move_yaw) * 0.7f;
                probe_end[0] += func_00283180(HOP_PLAYER.move_yaw) * 0.7f;
                probe_end[1] += func_00283198(HOP_PLAYER.move_yaw) * 0.7f;
                if (func_002761F8(probe_start, probe_end, 2, 0, 0) && func_00278E78() != 7) {
                    HOP_PLAYER.target_speed = 0.10000001f;
                    rate = 0.004f;
                }
            }
            if (HOP_PLAYER.state == 15) {
                func_L00_002B39F0(0, 0.050000004f);
                rate = 0.0012f;
            }
            if (HOP_PLAYER.field320 > 0.2617994248867035f) {
                HOP_PLAYER.target_speed = 0.0f;
                rate = HOP_PLAYER.field320 * 0.004583662f;
            }
        }
        func_L00_002B6198(rate);
    }
}
