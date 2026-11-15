#include "common.h"
extern float func_002A7878(float, float);
extern s32 func_002A77E0(s32);
extern s32 func_00283CF0(float);
extern float func_00282E48(char *, void *);
extern void func_002A93B0(char *);
extern float func_00283B98(float, float);
extern void func_00325B70(char *, char *, s32, s32);
extern void func_00325C50(char *, char *, s32, void *, float);
extern void func_00325DA0(char *, char *);
extern char *func_002A9640(char *, s32, s32);
extern s32 func_002B0ED8(char *, char *, s32);
extern void func_00283698(char *, char *);
extern void func_002AFFD8(char *, char *, s32);
extern s32 func_L11_004461C0(s32, char *);
extern void func_002A7750(char *, s32, s32);
extern char D_L11_001BA8C0[];
extern char D_L11_001A8F20[] __attribute__((sda));
extern s32 D_001A8FF4;
extern void func_L11_0044C4F0(char *);
extern void func_L11_0044C268(char *);

/* Initializes the object and its child rig, then updates aim, damage and activation. */
void func_L11_0044BD68(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *hit, *other;
    float speed, angle;
    if (*(u8 *)(object + 0x20) == 0) {
        *(char **)(state + 0x18) = state + 0x100;
        speed = RandomFloatRange(15.0f, 40.0f) * 0.01745329424738884f;
        if (RandomIntBelow(2)) speed = -speed;
        *(float *)(state + 0x494) = speed;
        if (RandomIntBelow(2) == 1) *(u16 *)(object + 0x34) |= 0x8000;
        *(u8 *)(state + 0x48) = FloatToInt(15.0f);
        *(u8 *)(state + 0x4A) = FloatToInt(12.0f);
        *(float *)(state + 0x80) = 0.8f;
        *(float *)(state + 0x8C) = 0.4f;
        *(s8 *)(state + 0xBC) = -1;
        *(s8 *)(state + 0xBD) = -1;
        *(s8 *)(state + 0xBE) = -1;
        *(s8 *)(state + 0xBF) = -1;
        *(s8 *)(state + 0xC2) = -1;
        *(float *)(state + 0x108) = 0.4f;
        *(float *)(state + 0x4AC) = 8.0f;
        *(u8 *)(state + 0x60) = 10;
        *(int *)(state + 0x98) = 5;
        *(float *)(state + 0x84) = 0.8f;
        *(s8 *)(state + 0xC3) = -1;
        *(float *)(state + 0x100) = 0.6f;
        *(float *)(state + 0x104) = 0.2f;
        *(float *)(state + 0x10C) = 0.4f;
        *(float *)(state + 0x110) = 1.5707964897155762f;
        *(float *)(state + 0x130) = 0.523598849773407f;
        *(float *)(state + 0x12C) = 0.0055555556900799274f;
        *(u8 *)(state + 0x28) = 3;
        *(int *)(state + 0x49C) = 0;
        SpawnEnemyChildParts(object, state + 0x4A0, 0, 1);
        *(short *)(state + 0x4CA) = 0;
        DeactivateSmasherRobot(object);
    }
    if (*(short *)(state + 0x4D2) == 0 && *(u8 *)(object + 0x20) != 11 && !D_001A8FF4) {
        *(u16 *)(object + 0x34) |= 0x400;
        if (*(u8 *)(object + 0x31) && fast_vec_dist(object + 0x10, D_L11_001BA8C0) < 24.0f) {
            UpdateMobyGroundCheck(object);
            *(u8 *)(object + 0x6F) = 22;
        }
    } else *(u16 *)(object + 0x34) &= 0xFBFF;
    angle = FastAddRotations(*(float *)(state + 0x49C), *(float *)(state + 0x4AC) * 0.01745329424738884f);
    *(float *)(state + 0x49C) = angle;
    AttachAndTurnChildParts(object, state + 0x4A0, 1, D_L11_001A8F20, angle);
    SyncGroupCounter(object, state + 0x4BC);
    if (*(u8 *)(object + 0x20) >= 3) {
        hit = FindOwnedEffectSlot(object, 0x10000, 1);
        if (hit && (other = *(char **)(hit + 0x20)) && !*(u8 *)(object + 0x31)) {
            if (*(short *)(other + 0xAA) == 0xA03 /* moby class 2563 */ || *(short *)(other + 0xAA) == 0xB89 /* moby class 2953 */)
                *(int *)(hit + 0x2C) = 0;
        }
        if (ApplyDamageToObject(object, state + 0x50, 0) == 5) {
            *(int *)(state + 0xE0) = 0;
            *(float *)(state + 0xE4) = 0.8377581834793091f;
        }
        UpdateSmasherRobotPairing(object);
        if (*(short *)(state + 0x4D2)) {
            matrix_from_basis_rows(state + 0x230, object + 0xC0);
            ComputeViewDirection(object + 0x10, state + 0x260, 0);
            if (!IsPointInArenaInnerZone(*(int *)(object + 0xB8), object + 0x10)) {
                *(int *)(state + 0x20) = 0;
                SetMobyState(object, 11, 5);
            }
        }
    }
    if (*(u8 *)(object + 0x20) >= 2 && *(u8 *)(state + 0x2E) == 2)
        DeactivateSmasherRobot(object);
}
