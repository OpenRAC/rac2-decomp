#include "common.h"

extern unsigned char D_00189E20[];
extern char *D_00152C00 NOT_SDA;
extern int D_L05_001B20CC;
extern float D_L05_001B1A4C __attribute__((sda));
extern float D_L05_001B1A50 __attribute__((sda));
extern float D_L05_001B1A54 __attribute__((sda));
extern float D_L05_001B1A58 __attribute__((sda));
extern float D_L05_001B1A5C __attribute__((sda));
extern float D_L05_001B1A64 __attribute__((sda));
extern float D_L05_001B1AC0 __attribute__((sda));
extern float D_L05_001B1F60, D_L05_001B1F64;
/* These views address the same fade words through $gp. */
extern float D_L05_001B1F60_sda SDATA(D_L05_001B1F60);
extern float D_L05_001B1F64_sda SDATA(D_L05_001B1F64);
extern int D_L05_001B1AF8 __attribute__((sda));
extern int D_L05_001B1B20 __attribute__((sda));
extern int D_L05_001B1B24 __attribute__((sda));
extern int D_L05_001B1ADC __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
/* Incomplete sda arrays keep absolute addresses together without claiming
 * the complete extent of the saved transforms. */
extern char D_L05_001B3620[] __attribute__((sda));
extern char D_L05_001B3610[] __attribute__((sda));
extern char D_L05_001B3600[] __attribute__((sda));
extern char D_L05_001B35D0[] __attribute__((sda));
extern char D_L05_001B35E0[] __attribute__((sda));
extern char D_L05_001B35F0[] __attribute__((sda));
extern char D_L05_002B8770[];

extern void func_L00_002D2E68(void);
extern void func_L05_00442A58(void *, void *, void *);
extern void func_L05_004431A0(void *, void *, void *);
extern void func_L05_004432E0(void *);
extern void func_L05_00443740(void *);
extern void func_002833F0(void *, void *);
extern void func_L00_002B30E8(void);
extern void func_L05_004424B8(void *, float);
extern void func_L00_002D6998(void *);
extern void func_L05_00442560(void *);
extern float func_L05_0037AE28(void);
extern int func_L05_00379F58(void);
extern int func_00282948(void *);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define U(p, o) (*(unsigned short *)((char *)(p) + (o)))

/* Dispatches the flight controller and its timed transform transitions. */
/* Runs the player's ship each frame. It steers normally and handles the screen fades and resets between ship states. */
void func_L05_00441F30(char *obj)
{
    int yawRate, pitchRate;
    char *input = P(obj, 0x70) + 0x50;
    float yawParam0 = D_L05_001B1A4C, yawParam1 = D_L05_001B1A50, yawParam2 = D_L05_001B1A54;
    float pitchParam0 = D_L05_001B1A58, pitchParam1 = D_L05_001B1A5C, pitchParam2 = D_L05_001B1A64;

    F(input, 0) = yawParam0;
    F(input, 4) = yawParam1;
    F(input, 8) = yawParam2;
    F(input, 12) = pitchParam0;
    F(input, 16) = pitchParam1;
    F(input, 20) = pitchParam2;
    D_L05_001B20CC = 2;
    if (!gHeroState[0x22B5]) {
        I(P(gHeroState, 0x2290), 0x98) = 0;
        SetHeroObjectsFlagBit();
        gHeroState[0x22B5] = 1;
    }
    if (!D_L05_001B1AF8) {
        U(gHeroMoby_00152C00, 0x34) |= 0x41;
        U(gHeroMoby_00152C00, 0x34) &= 0xEFFF;
        I(gHeroMoby_00152C00, 0x98) = 0;
    }
    D_L05_001B1AC0 = GetClampedStatValue();
    if (GetPlayerStateField18()) return;

    switch (gShipState) {
    case 0:
        UpdateSteeringInput(obj, &yawRate, &pitchRate);
        ApplyShipSteeringRotation(obj, &yawRate, &pitchRate);
        UpdateChaseCameraPosition(obj);
        UpdateDrivenMobyTransform(obj);
        break;
    case 1:
        UpdateSteeringInput(obj, &yawRate, &pitchRate);
        ApplyShipSteeringRotation(obj, &yawRate, &pitchRate);
        UpdateChaseCameraPosition(obj);
        UpdateDrivenMobyTransform(obj);
        D_L05_001B1F60_sda = D_L05_001B1F60 + 0.05f;
        if (D_L05_001B1F60_sda >= 1.0f) {
            D_L05_001B1F60 = 1.0f;
            gShipState = 4;
            qcopy(obj + 0x30, D_L05_001B3620);
            euler_rotation_basis(obj, D_L05_001B3610);
        }
        break;
    case 4:
        D_L05_001B1F60_sda = D_L05_001B1F60 - 0.05f;
        if (D_L05_001B1F60_sda <= 0.0f) {
            D_L05_001B1F60 = 0.0f;
            gShipState = 5;
        }
        break;
    case 5:
        if (FastFloatHelperD(&gShipTransitionTimer)) gShipState = 3;
        break;
    case 3:
        D_L05_001B1F60_sda = D_L05_001B1F60 + 0.05f;
        if (D_L05_001B1F60_sda >= 1.0f) {
            D_L05_001B1F60 = 1.0f;
            gShipState = 2;
            qcopy(obj + 0x30, D_L05_001B3600);
            qcopy(obj, D_L05_001B35D0);
            qcopy(obj + 0x10, D_L05_001B35E0);
            qcopy(obj + 0x20, D_L05_001B35F0);
        }
        break;
    case 2:
        UpdateSteeringInput(obj, &yawRate, &pitchRate);
        ApplyShipSteeringRotation(obj, &yawRate, &pitchRate);
        UpdateChaseCameraPosition(obj);
        UpdateDrivenMobyTransform(obj);
        D_L05_001B1F60_sda = D_L05_001B1F60 - 0.05f;
        if (D_L05_001B1F60_sda <= 0.0f) {
            D_L05_001B1F60_sda = 0.0f;
            gShipState = 0;
        }
        break;
    case 6:
        qcopy(obj + 0x30, D_L05_001B3620);
        euler_rotation_basis(obj, D_L05_001B3610);
        if (FastFloatHelperD(&gShipTransitionTimer)) {
            RecordHeroPlayCounters();
        } else {
            float resetSpeed = 0.13333334f;
            if (gCurrentMapIndex == 20) resetSpeed = 0.26666668f;
            UpdateShipRecordTransform(obj, resetSpeed);
            if (D_L05_001B1ADC - 20 < gShipTransitionTimer) {
                CopyRecordsToFreeSlots(D_L05_002B8770);
            }
        }
        break;
    case 7:
        D_L05_001B1F64_sda = D_L05_001B1F64 + 0.05f;
        if (D_L05_001B1F64_sda >= 1.0f) {
            D_L05_001B1F64 = 1.0f;
            gShipState = 8;
            RespawnShipAtBestSavedSlot(obj);
        }
        break;
    case 8:
        D_L05_001B1F64_sda = D_L05_001B1F64 - 0.05f;
        if (D_L05_001B1F64_sda <= 0.0f) {
            D_L05_001B1F64 = 0.0f;
            gShipState = 0;
        }
        break;
    }
}
