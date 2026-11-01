#include "include_asm.h"

#include "common.h"
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282F20(void *, void *, float);
typedef int DriveVector __attribute__((mode(TI)));
typedef struct PlayerDriveView {
    unsigned char pad0[0x20]; float basis[16];
    unsigned char pad60[0x98 - 0x60]; float rotation;
    unsigned char pad9C[0xF0 - 0x9C]; DriveVector velocity;
    unsigned char pad100[0x160 - 0x100]; DriveVector pendingResult;
    float distance, planarDistance;
    unsigned char pad178[0x190 - 0x178]; DriveVector direction; float heading;
    float yawRate, yawError;
    unsigned char pad1AC[4]; float speed, targetSpeed; int frame;
    unsigned char pad1BC[0x348 - 0x1BC]; short request, contact;
    unsigned char pad34C[0x454 - 0x34C]; float recoverySpeed;
    unsigned char pad458[0x470 - 0x458]; DriveVector localDirection, targetDirection;
    float pad490, acceleration;
    unsigned char pad498[6]; unsigned char allowAction;
    unsigned char pad49F[0x4AE - 0x49F]; short actionFrame;
    unsigned char pad4B0[12]; float lateralSpeed, inputHeading, targetHeading;
    unsigned char pad4C8[12]; int transition; float inputSpeed, strafeSpeed;
    unsigned char pad4E0[16]; DriveVector jumpDirection;
    unsigned char pad500[0x20]; float recoveryRate; short special;
    unsigned char pad526[7]; unsigned char useCurrentSpeed;
    unsigned char pad52E[0xA60 - 0x52E]; DriveVector pending;
    unsigned char padA70[0x14]; float pendingDamping;
    unsigned char padA88[0xC38 - 0xA88]; float plane;
    unsigned char padC3C[0x1440 - 0xC3C]; DriveVector savedDirection;
    unsigned char pad1450[4]; short overrideDirection;
    unsigned char pad1456[2]; float savedHeading;
    unsigned char pad145C[0x2294 - 0x145C]; int state;
    unsigned char pad2298[4]; int mode;
    unsigned char pad22A0[0x22C3 - 0x22A0]; unsigned char axisMode;
    unsigned char pad22C4[0x24B8 - 0x22C4]; float animationSpeed;
} PlayerDriveView;
extern PlayerDriveView D_00189E20;
typedef struct DriveVelocityView {
    DriveVector velocity;
    unsigned char pad10[0xC4 - 0x10]; float targetSpeed;
} DriveVelocityView;
extern DriveVelocityView D_00189F10;
extern int D_L07_001A8FF0 MACRO_ADDR;
extern float D_L07_001A7DC0 MACRO_ADDR;
typedef struct DriveSettings {
    unsigned char pad0[0x158]; float heading;
    unsigned char pad15C[0x370 - 0x15C]; DriveVector direction;
} DriveSettings;
extern DriveSettings D_L07_001B90C0;
extern void func_L00_002B54F8(float, float);
extern void func_L00_002B41B8(float, float);
extern void func_L00_002B3EF8(int, float, float, float);
extern void func_PAL_L01_002B6870(float);
extern void func_L00_002D3798(DriveVector *, DriveVector *, float);
extern void func_L00_002D3B58(DriveVector *, DriveVector *, float);
extern void func_L00_002D3BD8(void *, const void *, float);
extern float func_L00_002D3A58(char *);
extern float func_002AA2E8(float *, float, float);
extern float func_002AA898(float *, float *, int, float, float, float, float);
extern float func_00283BE0(float, float);
extern void func_L00_002AA0F0(float, float, float);
extern float func_00282DB0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283C80(float, float);
extern void func_00282CC0(void *, void *, void *);

/* Update directional movement, including the state-44 yaw spring.
 * Shares the resident views and locomotion arms with func_L01_002B7360. */
void func_PAL_L07_002B5728(void)
{
    union { DriveVector q; float f[3]; } local;
    float smoothed;
    float oldHeading;
    int state = D_00189E20.state;

    if (state == 10) {
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(&D_00189E20.pendingResult, &D_00189E20.pending);
        D_00189E20.targetSpeed = D_00189E20.planarDistance;
    } else if (state == 16) {
        float speed;
        PlayerDriveView *hero = &D_00189E20;
        if (D_00189E20.frame > 45) {
            func_002AA2E8((float *)(&D_00189E20.recoveryRate), 0.010000001f, 0.0028000001f);
        }
        if (D_00189E20.frame <= 45) speed = D_00189E20.recoverySpeed;
        else speed = 0.07000001f;
        hero->speed = speed;
        func_L00_002B41B8(0.0176f, 0.018000001f);
        func_L00_002D3BD8(&D_00189F10.velocity, &D_00189F10.velocity, 0.0f);
        func_L00_002D3798((DriveVector *)(&D_00189F10.velocity), (DriveVector *)(&D_00189F10.velocity), D_00189F10.targetSpeed);
    } else if (state == 27) {
        if (D_00189E20.frame > 33) {
            func_L00_002B3EF8(0, 0.057600003f, 0.28800002f, 0.30019668f);
            func_PAL_L01_002B6870(0.008f);
        }
        if (13.0f <= D_00189E20.plane && D_00189E20.plane <= 3e+01f) {
            if (27.0f < D_00189E20.plane)
                func_002AA2E8((float *)(&D_00189E20.lateralSpeed), 0.0f, 0.0032000002f);
            else func_002AA2E8((float *)(&D_00189E20.lateralSpeed), 0.040000003f, 0.0032000002f);
        }
        local.f[0] = D_00189E20.lateralSpeed;
        local.f[1] = 0.0f;
        local.f[2] = func_00282DB0(&D_00189E20.velocity, &D_00189E20.basis);
        func_00283098(&D_00189E20.velocity, &local, &D_00189E20);
    } else if (state == 11) {
        D_00189E20.heading = D_00189E20.targetHeading;
        qcopy(&D_00189E20.direction, &D_00189E20.targetDirection);
        func_L00_002B3EF8(0, 0.057600003f, 0.28800002f, 0.13962635f);
        if (D_00189E20.transition != 3) D_00189E20.targetSpeed = D_00189E20.inputSpeed;
        else D_00189E20.targetSpeed = 0.0f;
        if (D_00189E20.useCurrentSpeed != 0) {
            float rate = D_00189E20.animationSpeed * 0.10000001f;
            if (rate < 0.040000003f) rate = 0.040000003f;
            func_002AA2E8((float *)(&D_00189E20.strafeSpeed), rate, 0.014800001f);
            D_00189E20.targetSpeed = D_00189E20.planarDistance;
        } else {
            if (D_00189E20.allowAction != 0 && D_00189E20.actionFrame <= 9)
                func_002AA2E8((float *)(&D_00189E20.strafeSpeed), 0.0f, 0.0032000002f);
            else func_002AA2E8((float *)(&D_00189E20.strafeSpeed), 0.084f, 0.0032000002f);
        }
        if (D_00189E20.axisMode == 0) {
            ((float *)&D_00189E20.velocity)[0] = func_00283180(D_00189E20.inputHeading);
            ((float *)&D_00189E20.velocity)[0] *= D_00189E20.strafeSpeed;
            ((float *)&D_00189E20.velocity)[1] = func_00283198(D_00189E20.inputHeading);
            ((float *)&D_00189E20.velocity)[1] *= D_00189E20.strafeSpeed;
        } else {
            func_L00_002D3BD8(&local, &D_00189E20.localDirection, D_00189E20.strafeSpeed);
            func_L00_002D3B58(&local.q, &local.q, 0.0f);
            func_L00_002D3BD8(&D_00189E20.velocity, &D_00189E20.velocity, 0.0f);
            func_00282CC0(&D_00189E20.velocity, &D_00189E20.velocity, &local);
        }
        if (D_00189E20.axisMode == 0 && D_00189E20.useCurrentSpeed == 0) {
            float angle = func_00283C80(D_00189E20.targetHeading, D_00189E20.inputHeading);
            float cosine = func_00283198(angle);
            float amount = D_00189E20.inputSpeed * cosine;
            float component = func_00283180(D_00189E20.targetHeading);
            ((float *)&D_00189E20.velocity)[0] += component * amount;
            component = func_00283198(D_00189E20.targetHeading);
            ((float *)&D_00189E20.velocity)[1] += component * amount;
        }
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(&D_00189E20.pendingResult, &D_00189E20.pending);
    } else if (state == 17) {
        D_00189E20.heading = ((float *)&D_00189E20.jumpDirection)[3];
        qcopy(&D_00189E20.direction, &D_00189E20.jumpDirection);
        if (D_00189E20.frame > 7) func_L00_002B3EF8(-1, 0.060480002f, 0.28800002f, 0.23736483f);
        if (D_00189E20.frame > 6) {
            if (D_00189E20.request == 0) {
                ((float *)&D_00189E20.velocity)[0] = func_00283180(D_00189E20.heading);
                ((float *)&D_00189E20.velocity)[0] *= 0.09800001f;
                ((float *)&D_00189E20.velocity)[1] = func_00283198(D_00189E20.heading);
                ((float *)&D_00189E20.velocity)[1] *= 0.09800001f;
            } else {
                func_L00_002D3BD8(&D_00189E20.velocity, &D_00189E20.velocity, 0.0f);
                func_00282F20(&local, &D_00189E20.direction, 0.09800001f);
                func_00282CC0(&D_00189E20.velocity, &D_00189E20.velocity, &local);
            }
        }
        D_00189E20.targetSpeed = D_00189E20.planarDistance;
    } else if (state == 129 && D_L07_001A8FF0 == 0) {
        func_L00_002B3EF8(0, 0.057600003f, 0.28800002f, D_00189E20.acceleration);
        D_00189E20.targetSpeed = 0.0f;
    } else {
        if (D_00189E20.state == 44) {
            float angle = D_00189E20.rotation;
            float delta;
            D_00189E20.yawError = func_002AA898(&angle, &D_00189E20.yawRate, 0,
                D_00189E20.heading, 0.02592f, 0.28800002f, 0.14660768f);
            delta = func_00283BE0(angle, D_00189E20.rotation);
            func_L00_002AA0F0(0.0f, 0.0f, delta);
        } else {
            oldHeading = D_00189E20.heading;
            qcopy(&local, &D_00189E20.direction);
            if (D_00189E20.overrideDirection != 0) {
                D_00189E20.heading = D_L07_001B90C0.heading;
                qcopy(&D_00189E20.direction, &D_L07_001B90C0.direction);
            }
            func_L00_002B3EF8(0, 0.057600003f, 0.28800002f, D_00189E20.acceleration);
            if (D_00189E20.overrideDirection != 0) {
                D_00189E20.savedHeading = oldHeading;
                qcopy(&D_00189E20.savedDirection, &local);
                D_00189E20.heading = oldHeading;
                qcopy(&D_00189E20.direction, &D_00189E20.savedDirection);
            }
        }
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(&D_00189E20.pendingResult, &D_00189E20.pending);
        {
            float damping = 0.008f;
            if (D_00189E20.speed < D_L07_001A7DC0 * 0.004f) {
                if (D_00189E20.mode == 2) {
                    float rate = D_00189E20.pendingDamping;
                    smoothed = func_L00_002D3A58((char *)&D_00189E20.velocity);
                    func_002AA2E8(&smoothed, 0.0f, rate);
                    func_L00_002D3BD8(&D_00189E20.velocity, &D_00189E20.velocity, smoothed);
                    return;
                }
                if (D_00189E20.contact != 0) damping = 0.0044f;
                else if (D_00189E20.special != 0) damping = 0.00080000004f;
                else damping = 0.0032000002f;
            }
            func_PAL_L01_002B6870(damping);
        }
    }
}

