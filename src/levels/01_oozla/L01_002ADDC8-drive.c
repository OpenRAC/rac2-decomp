#include "common.h"

typedef int DriveVector __attribute__((mode(TI)));
typedef struct PlayerDriveView {
    unsigned char pad0[0x20]; float basis[16];
    unsigned char pad60[0xF0 - 0x60]; DriveVector velocity;
    unsigned char pad100[0x160 - 0x100]; DriveVector pendingResult;
    float distance, planarDistance;
    unsigned char pad178[0x190 - 0x178]; DriveVector direction; float heading;
    unsigned char pad1A4[0x1B0 - 0x1A4]; float speed, targetSpeed; int frame;
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
/* Resident subview at the velocity vector; targetSpeed is 0xC4 bytes later. */
typedef struct DriveVelocityView {
    DriveVector velocity;
    unsigned char pad10[0xC4 - 0x10]; float targetSpeed;
} DriveVelocityView;
extern DriveVelocityView D_00189F10;
extern int D_L01_001A9030 MACRO_ADDR;
extern float D_L01_001A7DC0 MACRO_ADDR;
/* The settings prefix ends at the observed direction vector. */
typedef struct DriveSettings {
    unsigned char pad0[0x158]; float heading;
    unsigned char pad15C[0x370 - 0x15C]; DriveVector direction;
} DriveSettings;
extern DriveSettings D_L01_001B9380;
extern void func_L00_002B54F8(float, float);
extern void func_L00_002B41B8(float, float);
extern void func_L00_002B3EF8(int, float, float, float);
extern void func_L01_002B6948(float);
extern void func_L00_002D3798(DriveVector *, DriveVector *, float);
extern void func_L00_002D3B58(DriveVector *, DriveVector *, float);
extern void func_L00_002D3BD8(void *, const void *, float);
extern float func_L00_002D3A58(char *);
extern float func_002AA2E8(float *, float, float);
extern float func_00282DB0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283C80(float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

/* Update directional movement for the active player locomotion state. */
void func_L01_002B7360(void)
{
    union { DriveVector q; float f[4]; } local;
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
        if (D_00189E20.frame > 54) {
            ApproachValue((float *)(&D_00189E20.recoveryRate), 0.0069444445f, 0.0019444445f);
        }
        if (D_00189E20.frame <= 54) speed = D_00189E20.recoverySpeed;
        else speed = 0.058333337f;
        hero->speed = speed;
        func_L00_002B41B8(0.012222223f, 0.0125f);
        func_L00_002D3BD8(&D_00189F10.velocity, &D_00189F10.velocity, 0.0f);
        func_L00_002D3798((DriveVector *)(&D_00189F10.velocity), (DriveVector *)(&D_00189F10.velocity), D_00189F10.targetSpeed);
    } else if (state == 27) {
        if (D_00189E20.frame > 40) {
            func_L00_002B3EF8(0, 0.04f, 0.2f, 0.250163913f);
            func_L01_002B6948(0.0055555557f);
        }
        if (13.0f <= D_00189E20.plane && D_00189E20.plane <= 30.0f) {
            if (27.0f < D_00189E20.plane)
                ApproachValue((float *)(&D_00189E20.lateralSpeed), 0.0f, 0.0022222223f);
            else ApproachValue((float *)(&D_00189E20.lateralSpeed), 0.033333335f, 0.0022222223f);
        }
        local.f[0] = D_00189E20.lateralSpeed;
        local.f[1] = 0.0f;
        local.f[2] = FastVecDot(&D_00189E20.velocity, &D_00189E20.basis);
        matrix_mul_vec3(&D_00189E20.velocity, &local, &D_00189E20);
    } else if (state == 11) {
        D_00189E20.heading = D_00189E20.targetHeading;
        qcopy(&D_00189E20.direction, &D_00189E20.targetDirection);
        func_L00_002B3EF8(0, 0.04f, 0.2f, 0.11635530f);
        if (D_00189E20.transition != 3) D_00189E20.targetSpeed = D_00189E20.inputSpeed;
        else D_00189E20.targetSpeed = 0.0f;
        if (D_00189E20.useCurrentSpeed != 0) {
            float rate = D_00189E20.animationSpeed * 0.083333336f;
            if (rate < 0.033333335f) rate = 0.033333335f;
            ApproachValue((float *)(&D_00189E20.strafeSpeed), rate, 0.010277778f);
            D_00189E20.targetSpeed = D_00189E20.planarDistance;
        } else {
            if (D_00189E20.allowAction != 0 && D_00189E20.actionFrame <= 11)
                ApproachValue((float *)(&D_00189E20.strafeSpeed), 0.0f, 0.0022222223f);
            else ApproachValue((float *)(&D_00189E20.strafeSpeed), 0.07f, 0.0022222223f);
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
            FastVecAdd(&D_00189E20.velocity, &D_00189E20.velocity, &local);
        }
        if (D_00189E20.axisMode == 0 && D_00189E20.useCurrentSpeed == 0) {
            float angle = FastDiffRots(D_00189E20.targetHeading, D_00189E20.inputHeading);
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
        if (D_00189E20.frame > 9) func_L00_002B3EF8(-1, 0.042f, 0.2f, 0.19780402f);
        if (D_00189E20.frame > 8) {
            if (D_00189E20.request == 0) {
                ((float *)&D_00189E20.velocity)[0] = func_00283180(D_00189E20.heading);
                ((float *)&D_00189E20.velocity)[0] *= 0.08166667f;
                ((float *)&D_00189E20.velocity)[1] = func_00283198(D_00189E20.heading);
                ((float *)&D_00189E20.velocity)[1] *= 0.08166667f;
            } else {
                func_L00_002D3BD8(&D_00189E20.velocity, &D_00189E20.velocity, 0.0f);
                vec_scale_to_length(&local, &D_00189E20.direction, 0.08166667f);
                FastVecAdd(&D_00189E20.velocity, &D_00189E20.velocity, &local);
            }
        }
        D_00189E20.targetSpeed = D_00189E20.planarDistance;
    } else if (state == 129 && D_L01_001A9030 == 0) {
        func_L00_002B3EF8(0, 0.04f, 0.2f, D_00189E20.acceleration);
        D_00189E20.targetSpeed = 0.0f;
    } else {
        oldHeading = D_00189E20.heading;
        qcopy(&local, &D_00189E20.direction);
        if (D_00189E20.overrideDirection != 0) {
            D_00189E20.heading = D_L01_001B9380.heading;
            qcopy(&D_00189E20.direction, &D_L01_001B9380.direction);
        }
        func_L00_002B3EF8(0, 0.04f, 0.2f, D_00189E20.acceleration);
        if (D_00189E20.overrideDirection != 0) {
            D_00189E20.savedHeading = oldHeading;
            qcopy(&D_00189E20.savedDirection, &local);
            D_00189E20.heading = oldHeading;
            qcopy(&D_00189E20.direction, &D_00189E20.savedDirection);
        }
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy(&D_00189E20.pendingResult, &D_00189E20.pending);
        {
            float damping = 0.0055555557f;
            if (D_00189E20.speed < D_L01_001A7DC0 * 0.00333333365f) {
                if (D_00189E20.mode == 2) {
                    float rate = D_00189E20.pendingDamping;
                    smoothed = func_L00_002D3A58((char *)&D_00189E20.velocity);
                    ApproachValue(&smoothed, 0.0f, rate);
                    func_L00_002D3BD8(&D_00189E20.velocity, &D_00189E20.velocity, smoothed);
                    return;
                }
                if (D_00189E20.contact != 0) damping = 0.00305555575f;
                else if (D_00189E20.special != 0) damping = 0.00055555557f;
                else damping = 0.0022222223f;
            }
            func_L01_002B6948(damping);
        }
    }
}
