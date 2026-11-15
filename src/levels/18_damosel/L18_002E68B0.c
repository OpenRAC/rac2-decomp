#include "include_asm.h"
#include "common.h"

extern s32 func_00282978(s16 *timer);
extern s32 func_00288E18(s32 key, s32 selection);
extern s32 func_002ACBC8(void *point, s32 index);
extern s32 func_002E5E58(s32 index, s32 value, void *object);
extern void func_002B0A18(s32 first, s32 second);

extern u16 D_0018CF40;
extern u8 D_001A7AFD[] __attribute__((sda));
extern u8 D_001A7A60[] MACRO_ADDR;
extern u8 D_00189EA0[];
extern u8 D_00189E20[];
extern u32 D_L18_001A903C[] __attribute__((sda));

typedef int u128 __attribute__((mode(TI)));

extern char *func_002A9640(char *, int, int);
extern void func_002B0ED8(char *, char *, int);
extern void func_002A6C58(char *, int, int);
extern void func_0029F338(char *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A8C28(char *, void *, float, float, float, int, int, int, int);
extern void func_L00_002E6EF8(void *, char *);
extern char D_L18_003F9018[];

extern void func_3F7CD8(s32);
extern void func_3F7EF8(s32);
extern void func_3F80A0(s32);
extern void func_3F8A98(s32);
extern void func_3F8C08(s32);

extern float func_309900(float, float);
extern float func_308EE8(float);
extern float func_308F00(float);
extern float func_3099E8(float, float);
extern float func_308860(float);
extern void func_34B1D0(s32);

extern char *func_002B9030(s32);
extern s32 func_001163B0(void);
extern s32 func_00283CF0(float);
extern float func_00283180(float);
extern float func_00283198(float);
extern u8 *D_L18_001FF4D4;

/* func_L18_002E68B0 is in the sibling file L18_002E68B0-decider.c (its own profile). */

/* func_L18_003170F8 is in the sibling file L18_002E68B0-movables.c (its own profile). */


/* Fills the record with the requested fields and derived coordinates. */
/* Creates a short-lived effect that circles a point, at a set distance and angle from it. */
char *func_L18_0035B6B8(char *center, float radius, float angle, float angleStep, float scaleA, float scaleB, s16 frameStep,
                         char *owner, s32 typeIndex, char *flag)
{
    char *record = AllocParticle(0x65);
    char *orbit = record + 0x20;

    if (record != 0) {
        *(u8 *)(record + 3) = (flag != 0) ? 0x48 : 0x44;
        *(u8 *)(record + 1) = 0;
        *(u8 *)(record + 2) = D_L18_001FF4D4[typeIndex];
        *(u8 *)(record + 8) = Rand();
        *(u8 *)(record + 9) = FloatToInt(1.0f) + 0x40;
        *(u32 *)(record + 4) = owner;
        *(float *)(record + 0xC) = scaleA * 210000.0f;
        *(u32 *)(orbit + 0) = center;
        *(float *)(orbit + 4) = radius;
        *(float *)(orbit + 8) = angle;
        *(float *)(orbit + 0xC) = angleStep;
        *(u16 *)(orbit + 0x14) = frameStep;
        *(float *)(orbit + 0x10) = scaleB * 210000.0f;
        *(float *)(record + 0x10) = *(float *)(*(char **)(orbit + 0)) +
                                *(float *)(orbit + 4) * FastSinOrCosA(angle);
        *(float *)(record + 0x18) = *(float *)(*(char **)(orbit + 0) + 8) +
                                *(float *)(orbit + 4) * FastSinOrCosB(*(float *)(orbit + 8));
        *(float *)(record + 0x14) = *(float *)(*(char **)(orbit + 0) + 4);
    }
    return record;
}

/* Turns the circling effect a little each frame, moves it, and removes it when it has turned far enough. */
void func_L18_0035B838(char *effect)
{
    char *record = effect;
    char *orbit = record + 0x20;
    float angleDiff;

    *(u8 *)(record + 8) = *(u8 *)(record + 8) + *(u8 *)(orbit + 0x14);
    *(float *)(orbit + 8) = func_309900(*(float *)(orbit + 8), *(float *)(orbit + 0xC));
    *(float *)(record + 0xC) = *(float *)(record + 0xC) + *(float *)(orbit + 0x10);
    *(float *)(record + 0x10) = *(float *)(*(char **)(record + 0x20)) +
                            *(float *)(orbit + 4) * func_308EE8(*(float *)(orbit + 8));
    *(float *)(record + 0x18) = *(float *)(*(char **)(record + 0x20) + 8) +
                            *(float *)(orbit + 4) * func_308F00(*(float *)(orbit + 8));
    angleDiff = func_3099E8(*(float *)(orbit + 8), *(float *)(*(char **)(record + 0x20) + 0x10));
    if (angleDiff < func_308860(*(float *)(orbit + 0xC) + *(float *)(orbit + 0xC)))
        func_34B1D0(record);
}

/* Watches the hero in two steps, first for one action and then for another, and then triggers an event with a sound. */
void func_L18_003A0C28(u8 *moby) {
    u8 *vars;
    u32 step;
    u8 stateByte;

    vars = *(u8 **)(moby + 0x68);
    if (moby[0x20] == 0) {
        moby[0x30] = 0xFF;
        *(u16 *)(vars + 0xE) = 0x28;
        *(u16 *)(vars + 0xC) = 0;
        moby[0x20] = 1;
    }
    if (D_0018CF40 != 0)
        goto after;
    if (D_001A7AFD[0] != 0) {
        if (FastDecTimer((s16 *)(vars + 0xE)) != 0)
            RequestSubtitleVoiceLine(0xA27, 0x7E);
    }
after:
    stateByte = moby[0x20];
    if (stateByte != 1)
        goto end;
    step = *(u32 *)(vars + 0x8);
    switch (step) {
    case 0: {
        u8 *hero = gHeroPosition;
        if (IsPointInCuboid(hero, *(u32 *)(vars + 0)) != 0) {
            if (*(u32 *)(hero + 0x221C) == 15)
                *(u32 *)(vars + 8) = stateByte;
        }
        break;
    }
    case 1: {
        u8 *hero = gHeroState;
        if (*(u32 *)(hero + 0x2294) == 0x3E) {
            *(u32 *)(vars + 8) = 0;
        } else if (IsPointInCuboid(hero + 0x80, *(u32 *)(vars + 4)) != 0) {
            if (D_001A7A60[7] == 0) {
                D_001A7A60[7] = step;
                PlaySoundFromGlobalBank(1, 0, 0);
                SetEntryValueByIndex(0x1233, -1);
                D_L18_001A903C[0] = step;
            }
        }
        break;
    }
    }
end:
    return;
}


/* Per-frame update of a small flying robot enemy: sets it up on the first frame, then runs its movement, attack and hit checks. */
void func_L18_003F7C70(s32 moby)
{
    u8 stateByte = *(u8 *)(moby + 0x20);

    if (stateByte == 0) {
        func_3F7CD8(moby);
        return;
    }
    if (stateByte == 1)
        return;
    func_3F7EF8(moby);
    func_3F80A0(moby);
    func_3F8A98(moby);
    func_3F8C08(moby);
}

extern void func_002B60B0(u8 *, float, float, float, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_L02_0032E508(u8 *, int, u8 *, int);
extern void func_L18_003F8FA8(u8 *);
extern void func_002A7750(u8 *, int, int);

/* Sets up the robot enemy: its speeds, turning and bounce values, a random spin direction and its starting behaviour. */
void func_L18_003F7CD8(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    float turnDegrees, turnSpeed;

    vars[0x70] = 9;
    *(int *)(vars + 0xA8) = 4;
    *(float *)(vars + 0x90) = 0.8f;
    *(float *)(vars + 0x94) = 0.9f;
    *(float *)(vars + 0x9C) = 0.4f;
    if (*(short *)(vars + 0x24) == 0) {
        *(short *)(vars + 0x24) = 16;
        *(float *)(vars + 0x20) = 16;
    }
    vars[0x28] = 3;
    *(float *)(vars + 0x144) = 0.25f;
    *(float *)(vars + 0x110) = 0.8f;
    *(float *)(vars + 0x13C) = 0.0055555556900799274f;
    *(float *)(vars + 0x114) = 0.5f;
    *(float *)(vars + 0x118) = 0.5f;
    *(float *)(vars + 0x11C) = 2.0f;
    *(float *)(vars + 0x120) = 1.5707964897155762f;
    SetControllerSpeedLimits(object, 0.0033333334140479565f, 0.10000000894069672f,
                  0.0034906589426100254f, 0.20943954586982727f);
    *(u8 **)(vars + 0x158) = vars + 0x680;
    *(u8 **)(vars + 0x15C) = vars + 0x600;
    turnDegrees = RandomFloatRange(5.0f, 20.0f);
    if (RandomIntBelow(2) != 0)
        turnSpeed = turnDegrees * -0.01745329424738884f;
    else
        turnSpeed = turnDegrees * 0.01745329424738884f;
    *(float *)(vars + 0x720) = turnSpeed;
    *(int *)(vars + 0x14C) = *(int *)(vars + 0x718);
    if (*(int *)(vars + 0x71C) != -1)
        *(int *)(vars + 0x730) = BuildRouteNodes(object,
            *(int *)(vars + 0x71C), vars + 0x200, 0x20);
    *(short *)(vars + 0x76C) = RandomIntBelow(2);
    *(float *)(vars + 0x72C) = RandomFloatRange(5.0f, 7.0f);
    *(u16 *)(object + 0x7C) |= 1 << RandomIntBelow(6);
    switch (*(short *)(vars + 0x764)) {
    case 1:
        ResetToStartAnimation(object);
        break;
    case 2:
        SetMobyState(object, 2, 1);
        break;
    }
}

/* Handles hits on the robot enemy: damages or ignores the thing it touched, destroys it if it falls too low, and draws its shadow. */
void func_L18_003F7EF8(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *hitInfo = FindOwnedEffectSlot(moby, 0x10000, 1);
    int oldAnim;
    float worldPos[4] __attribute__((aligned(16)));
    float offsetTemp[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    if (hitInfo && *(char **)(hitInfo + 0x20)) {
        int hitClass = *(short *)(*(char **)(hitInfo + 0x20) + 0xAA);
        if (hitClass == 0xB69 /* Protopet */) {
            if (*(unsigned char *)(moby + 0x31)) *(float *)(hitInfo + 0x2C) = 4.0f;
            else *(float *)(hitInfo + 0x2C) = 0;
        } else if (hitClass == 0xF0A /* Extermibot Legs */ || hitClass == 0xF9E /* moby class 3998 */) *(float *)(hitInfo + 0x2C) = 0;
    }
    oldAnim = *(unsigned char *)(moby + 0x94);
    ApplyDamageToObject(moby, vars + 0x60, 0);
    if (*(unsigned char *)(moby + 0x20) == 9 &&
        (*(unsigned char *)(moby + 0x94) == 9 || *(unsigned char *)(moby + 0x94) == 4 || *(unsigned char *)(moby + 0x94) == 3))
        *(unsigned char *)(moby + 0x94) = oldAnim;
    if (*(float *)(moby + 0x18) < 90.0f) {
        SetDeathBits(moby, 0, 3);
        MarkMobySpawned(moby);
        return;
    }
    *(u128 *)offset = 0;
    offset[2] = *(float *)(vars + 0x114) + *(float *)(vars + 0x110);
    *(u128 *)offsetTemp = *(u128 *)offset;
    FastVecAdd(worldPos, moby + 0x10, offsetTemp);
    SweepCollisionFromObject(moby, worldPos, *(float *)(vars + 0x110) + 0.2f, 10.0f, 1.0f, 0x4000000, 0, 1, 0);
    if (*(unsigned char *)(moby + 0x20) >= 2) AddDrawCallbackToList3(D_L18_003F9018, moby);
}
