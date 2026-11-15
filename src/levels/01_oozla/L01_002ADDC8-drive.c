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
    int state = gHeroState.state;

    if (state == 10) {
        BuildHeroMoveImpulse(0.7f, 0.0f);
        qcopy(&gHeroState.pendingResult, &gHeroState.pending);
        gHeroState.targetSpeed = gHeroState.planarDistance;
    } else if (state == 16) {
        float speed;
        PlayerDriveView *hero = &gHeroState;
        if (gHeroState.frame > 54) {
            ApproachValue((float *)(&gHeroState.recoveryRate), 0.0069444445f, 0.0019444445f);
        }
        if (gHeroState.frame <= 54) speed = gHeroState.recoverySpeed;
        else speed = 0.058333337f;
        hero->speed = speed;
        ApproachHeroSpeed(0.012222223f, 0.0125f);
        SetViewSpaceVectorLength(&D_00189F10.velocity, &D_00189F10.velocity, 0.0f);
        OffsetPointBySideDirection((DriveVector *)(&D_00189F10.velocity), (DriveVector *)(&D_00189F10.velocity), D_00189F10.targetSpeed);
    } else if (state == 27) {
        if (gHeroState.frame > 40) {
            SteerHeroHeading(0, 0.04f, 0.2f, 0.250163913f);
            ApproachHeroVelocity_L01(0.0055555557f);
        }
        if (13.0f <= gHeroState.plane && gHeroState.plane <= 30.0f) {
            if (27.0f < gHeroState.plane)
                ApproachValue((float *)(&gHeroState.lateralSpeed), 0.0f, 0.0022222223f);
            else ApproachValue((float *)(&gHeroState.lateralSpeed), 0.033333335f, 0.0022222223f);
        }
        local.f[0] = gHeroState.lateralSpeed;
        local.f[1] = 0.0f;
        local.f[2] = FastVecDot(&gHeroState.velocity, &gHeroState.basis);
        matrix_mul_vec3(&gHeroState.velocity, &local, &gHeroState);
    } else if (state == 11) {
        gHeroState.heading = gHeroState.targetHeading;
        qcopy(&gHeroState.direction, &gHeroState.targetDirection);
        SteerHeroHeading(0, 0.04f, 0.2f, 0.11635530f);
        if (gHeroState.transition != 3) gHeroState.targetSpeed = gHeroState.inputSpeed;
        else gHeroState.targetSpeed = 0.0f;
        if (gHeroState.useCurrentSpeed != 0) {
            float rate = gHeroState.animationSpeed * 0.083333336f;
            if (rate < 0.033333335f) rate = 0.033333335f;
            ApproachValue((float *)(&gHeroState.strafeSpeed), rate, 0.010277778f);
            gHeroState.targetSpeed = gHeroState.planarDistance;
        } else {
            if (gHeroState.allowAction != 0 && gHeroState.actionFrame <= 11)
                ApproachValue((float *)(&gHeroState.strafeSpeed), 0.0f, 0.0022222223f);
            else ApproachValue((float *)(&gHeroState.strafeSpeed), 0.07f, 0.0022222223f);
        }
        if (gHeroState.axisMode == 0) {
            ((float *)&gHeroState.velocity)[0] = FastSinOrCosA(gHeroState.inputHeading);
            ((float *)&gHeroState.velocity)[0] *= gHeroState.strafeSpeed;
            ((float *)&gHeroState.velocity)[1] = FastSinOrCosB(gHeroState.inputHeading);
            ((float *)&gHeroState.velocity)[1] *= gHeroState.strafeSpeed;
        } else {
            SetViewSpaceVectorLength(&local, &gHeroState.localDirection, gHeroState.strafeSpeed);
            SetViewSpaceHeight(&local.q, &local.q, 0.0f);
            SetViewSpaceVectorLength(&gHeroState.velocity, &gHeroState.velocity, 0.0f);
            FastVecAdd(&gHeroState.velocity, &gHeroState.velocity, &local);
        }
        if (gHeroState.axisMode == 0 && gHeroState.useCurrentSpeed == 0) {
            float angle = FastDiffRots(gHeroState.targetHeading, gHeroState.inputHeading);
            float cosine = FastSinOrCosB(angle);
            float amount = gHeroState.inputSpeed * cosine;
            float component = FastSinOrCosA(gHeroState.targetHeading);
            ((float *)&gHeroState.velocity)[0] += component * amount;
            component = FastSinOrCosB(gHeroState.targetHeading);
            ((float *)&gHeroState.velocity)[1] += component * amount;
        }
        BuildHeroMoveImpulse(0.7f, 0.0f);
        qcopy(&gHeroState.pendingResult, &gHeroState.pending);
    } else if (state == 17) {
        gHeroState.heading = ((float *)&gHeroState.jumpDirection)[3];
        qcopy(&gHeroState.direction, &gHeroState.jumpDirection);
        if (gHeroState.frame > 9) SteerHeroHeading(-1, 0.042f, 0.2f, 0.19780402f);
        if (gHeroState.frame > 8) {
            if (gHeroState.request == 0) {
                ((float *)&gHeroState.velocity)[0] = FastSinOrCosA(gHeroState.heading);
                ((float *)&gHeroState.velocity)[0] *= 0.08166667f;
                ((float *)&gHeroState.velocity)[1] = FastSinOrCosB(gHeroState.heading);
                ((float *)&gHeroState.velocity)[1] *= 0.08166667f;
            } else {
                SetViewSpaceVectorLength(&gHeroState.velocity, &gHeroState.velocity, 0.0f);
                vec_scale_to_length(&local, &gHeroState.direction, 0.08166667f);
                FastVecAdd(&gHeroState.velocity, &gHeroState.velocity, &local);
            }
        }
        gHeroState.targetSpeed = gHeroState.planarDistance;
    } else if (state == 129 && D_L01_001A9030 == 0) {
        SteerHeroHeading(0, 0.04f, 0.2f, gHeroState.acceleration);
        gHeroState.targetSpeed = 0.0f;
    } else {
        oldHeading = gHeroState.heading;
        qcopy(&local, &gHeroState.direction);
        if (gHeroState.overrideDirection != 0) {
            gHeroState.heading = D_L01_001B9380.heading;
            qcopy(&gHeroState.direction, &D_L01_001B9380.direction);
        }
        SteerHeroHeading(0, 0.04f, 0.2f, gHeroState.acceleration);
        if (gHeroState.overrideDirection != 0) {
            gHeroState.savedHeading = oldHeading;
            qcopy(&gHeroState.savedDirection, &local);
            gHeroState.heading = oldHeading;
            qcopy(&gHeroState.direction, &gHeroState.savedDirection);
        }
        BuildHeroMoveImpulse(0.7f, 0.0f);
        qcopy(&gHeroState.pendingResult, &gHeroState.pending);
        {
            float damping = 0.0055555557f;
            if (gHeroState.speed < D_L01_001A7DC0 * 0.00333333365f) {
                if (gHeroState.mode == 2) {
                    float rate = gHeroState.pendingDamping;
                    smoothed = GetViewSpaceVectorLength((char *)&gHeroState.velocity);
                    ApproachValue(&smoothed, 0.0f, rate);
                    SetViewSpaceVectorLength(&gHeroState.velocity, &gHeroState.velocity, smoothed);
                    return;
                }
                if (gHeroState.contact != 0) damping = 0.00305555575f;
                else if (gHeroState.special != 0) damping = 0.00055555557f;
                else damping = 0.0022222223f;
            }
            ApproachHeroVelocity_L01(damping);
        }
    }
}
