#include "common.h"

extern void func_002A7750(u8 *arg0, s32 arg1, s32 arg2);

extern u8 *func_002A9640(s32 arg0, s32 arg1, s32 arg2);

extern void func_002A7470(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

extern void func_002A05A8(u8 *arg0);

extern s32 func_002E59B0(u8 *arg0, s32 arg1);

extern s32 func_002E5CF8(s32 arg0, s32 arg1, u8 *arg2);

extern void func_002E59F8(s32 arg0);

extern s32 func_00283CF0(f32 arg0);

extern void func_002A04B8(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);

extern void func_002A93B0(u8 *arg0);

extern f32 func_00282E48(u8 *arg0, u8 *arg1);

extern void func_L11_003F1D18();

extern void func_L11_003F1DB0(u8 *arg0);

extern void func_L11_003F1F48(u8 *arg0);

extern void func_L11_003F2A30(u8 *arg0);

extern void func_L11_003F2C28(u8 *arg0);

extern s32 func_L11_003F2E00(u8 *arg0);

extern void func_L11_003F3098(u8 *arg0);

extern void func_L11_003F31C0(u8 *arg0);

extern u8 D_L11_00188660[];

extern u8 D_L11_001BA8C0[];

extern s32 D_L11_001A8FF0 __attribute__((sda));

extern s32 D_L11_001A8FF4 __attribute__((sda));

typedef int TI128 __attribute__((mode(TI)));

extern f32 func_002B04E0(u8 *a0, f32 *a1, s32 a2);

extern f32 func_00282E80(u8 *a0, u8 *a1);

extern void func_00282CF0(f32 *a0, const f32 *a1, const f32 *a2);

extern u8 D_L11_00189EA0[];

extern void func_L11_003F3CB8(u8 *arg0);

/* The entity table's base and the current level, read as retail's tied absolute loads. */
extern u8 *D_L11_001B359C[] __attribute__((sda));

extern s32 D_001A79F0[] __attribute__((sda));

/* Per-level flag bytes, sixteen per level. */
extern u8 D_0019B2E8[][16];

extern void func_00282F20(void *, void *, f32);

extern void func_00282CC0(void *, void *, void *);

extern s32 func_002B38B8(u8 *);

extern f32 func_00283BE0(f32, f32);

extern f32 func_002AA548(void *, void *, f32, f32, f32, f32);

/* Defined in L11_003D6270-path.c. */


/* func_L11_003DCEB0 lives in L11_003DCEB0-g8.c. */

/* Defined in L11_003DD068-g8.c. */

/* Per-frame update for the Joba enemy. On the first frame it sets itself up; after that it
   runs damage, its state machine, its movement and its effects. */
void func_L11_003F1C68(u8 *mobyArg) {
    u8 *moby = mobyArg;
    if (*(u8 *)(moby + 0x20) == 0) {
        InitJobaEnemy();
    } else {
        if (IsJobaEnemyActive(moby) != 0)
            return;
        if (*(u8 *)(moby + 0x31) != 0
            && fast_vec_dist(moby + 0x10, D_L11_001BA8C0) < 48.0f) {
            UpdateMobyGroundCheck(moby);
            *(u8 *)(moby + 0x6F) = 0x2D;
        }
        ApplyJobaEnemyDamage(moby);
        UpdateJobaEnemyStateMachine(moby);
        UpdateJobaEnemyOrbit(moby);
        UpdateJobaEnemyEffects(moby);
    }
}
/* Sets up a new Joba enemy: fills in its starting values and puts it in its idle state. */
void func_L11_003F1D18(u8 *mobyArg) {
    u8 *moby = mobyArg;
    u8 *vars = *(u8 **)(moby + 0x68);
    *(u8 *)(vars + 0x48) = FloatToInt(15.0f);
    *(u8 *)(vars + 0x4A) = FloatToInt(16.0f);
    get_moby_color(moby, vars + 0x280, vars + 0x284, vars + 0x288);
    *(u8 *)(vars + 0x28) = 3;
    *(f32 *)(vars + 0x30) = 1.5f;
    *(u8 *)(vars + 0x29) = 1;
    *(u16 *)(moby + 0x34) |= 0x100;
    ResetJobaEnemy(moby);
    *(s32 *)(vars + 0x290) = -1;
}

/* func_L11_003F1DB0 is defined in L11_003D6270-g8.c (this unit has no $gp access for it). */

/* func_L11_003F1F48 is defined in L11_003D6270-state-g8.c. */

/* Defined in L11_003F2A30-g8.c. */

/* func_L11_003F2C28 is defined in L11_003D6270-g8.c (this unit has no $gp access for it). */


/* True when the engine's two global gates are both clear and the stage byte is not nine. */
s32 func_L11_003F2E00(u8 *moby) {
    s32 result = 0;

    if (D_L11_001A8FF0 == 0 || D_L11_001A8FF4 == 0)
        result = *(u8 *)(moby + 0x20) != 9;
    return result;
}

/* Puts the enemy back into state 4. */
void func_L11_003F2D18(u8 *moby) {
    SetMobyState(moby, 4, -1);
}

/* Remembers the enemy's current state, then switches it to its hit reaction state. */
void func_L11_003F2DC8(u8 *mobyArg) {
    u8 *moby = mobyArg;
    s32 vars = *(s32 *)(moby + 0x68);
    u8 oldState = *(u8 *)(moby + 0x20);
    u8 savedValue = *(u8 *)(moby + 0x95);
    *(u8 *)(moby + 0x94) = oldState;
    *(u16 *)(vars + 0x294) = savedValue;
    SetMobyState(mobyArg, 3, -1);
}

/* Reports the signed area of the triangle (arg0, arg1, arg2). */
f32 func_L11_003F2F00(f32 *pointA, f32 *pointB, f32 *pointC) {
    return (pointA[0] - pointC[0]) * (pointB[1] - pointC[1])
         - (pointA[1] - pointC[1]) * (pointB[0] - pointC[0]);
}


/* Resets the enemy to its idle look and clears its counters. */
void func_L11_003F3098(u8 *moby) {
    ClearJobaEnemyCounters(moby);
    StartAnimationBlended(moby, 0, 0, 3);
    func_002A05A8(moby);
    SetMobyState(moby, 1, 0);
    *(u8 *)(moby + 0x31) = 0;
    *(s32 *)(moby + 0x98) = 0;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 1) & 0xEFFF;
}

/* Clears one pair of the enemy's counters and sets the other pair to 1. */
void func_L11_003F3108(u8 *moby) {
    s32 i = 1;
    u16 *counters = (u16 *)(*(u8 **)(moby + 0x68) + 0x278);
    do {
        counters[-2] = 0;
        counters[0] = 1;
        i--;
        counters++;
    } while (i >= 0);
}

/* Clears one pair of the enemy's counters, sets the other pair to 2 and starts its sound
   effect if it has none. */
void func_L11_003F3140(u8 *mobyArg) {
    s32 i = 1;
    u8 *moby = mobyArg;
    u8 *vars = *(u8 **)(moby + 0x68);
    u16 *counters = (u16 *)(vars + 0x278);
    do {
        counters[-2] = 0;
        counters[0] = 2;
        i--;
        counters++;
    } while (i >= 0);
    if (IsVoicePlayingForOwner(moby, *(s32 *)(vars + 0x290)) == 0) {
        *(s32 *)(vars + 0x290) = PlayMobySound(2, 4, moby);
    }
}

/* Clears the enemy's counters and stops its sound effect. */
void func_L11_003F31C0(u8 *mobyArg) {
    s32 i = 1;
    u8 *moby = mobyArg;
    u8 *vars = *(u8 **)(moby + 0x68);
    u16 *counters = (u16 *)(vars + 0x278);
    s32 soundIndex;
    do {
        counters[-2] = 0;
        counters[0] = 0;
        i--;
        counters++;
    } while (i >= 0);
    soundIndex = *(s32 *)(vars + 0x290);
    if (soundIndex != -1) {
        u8 *sound = D_L11_00188660 + soundIndex * 0x70;
        if (*(u8 **)(sound + 0x88) == moby && *(u8 *)(sound + 0x74) != 0) {
            StopSoundVoice(soundIndex);
        }
    }
    *(s32 *)(vars + 0x290) = -1;
}

/* func_L11_003F3258 is defined in L11_003F3258-g8.c. */

/* func_L11_003F33E0 is defined in L11_003F33E0-g8.c. */

/* func_L11_003F3CB8 is in L11_003F3CB8-g8.c. */

/* Defined in L11_003F4060-g8.c. */

/* Defined in L11_003F4490-g8.c. */


/* Defined in L11_003F4F30-g8.c. */

/* func_L11_003F7B70 is in L11_003F7B70-g8.c. */

/* Defined in L11_003F7F58.c. */

/* Defined in L11_003F8150.c. */

/* Defined in L11_003F8510-g8.c. */

/* Defined in L11_00411D40-g8.c. */

/* Defined in L11_00412B20-g8.c. */

/* Defined in L11_00415E70.c. */


/* Steps a seven-state swing, easing the angle at 0xF0 between -90 and -75/-85 degrees, then
   places the linked table entity at this one's position, offset along two of its axes. */
/* Swings a part of the object between a few angles and keeps a linked object attached in
   front of it. */
void func_L11_004169E0(u8 *mobyArg) {
    f32 frontOffset[4], sideOffset[4];
    u8 *moby = mobyArg;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *linked = gMobyTable_L11[0] + *(s32 *)vars * 256;
    u8 *pos;

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (IsThirdPendingFlagSet(linked)) {
            PlayMobySound(0, 0, moby);
            SetMobyState(moby, 2, -1);
        }
        if (D_0019B2E8[gCurrentMapIndex[0]][*(u8 *)(moby + 0xB0)] & 0x80) {
            *(f32 *)(moby + 0xF0) = fast_subtract_rotations(*(f32 *)(moby + 0xF0), 1.5707964897155762f);
            SetMobyState(moby, 6, -1);
        }
        break;
    case 2:
        StepValueTowardTarget(moby + 0xF0, vars + 4, -1.5707964897155762f, 0.0005332950968295336f,
                      174.53294372558594f, 290.8882751464844f);
        if (*(f32 *)(moby + 0xF0) <= -1.5707964897155762f) {
            *(s32 *)(vars + 4) = 0;
            SetMobyState(moby, 3, -1);
            PlayMobySound(1, 0, moby);
        }
        break;
    case 3:
        StepValueTowardTarget(moby + 0xF0, vars + 4, -1.3089970350265503f, 0.01745329424738884f,
                      0.0004363323678262532f, 0.872664749622345f);
        if (*(f32 *)(moby + 0xF0) >= -1.3089970350265503f) {
            *(s32 *)(vars + 4) = 0;
            SetMobyState(moby, 4, -1);
        }
        break;
    case 4:
        StepValueTowardTarget(moby + 0xF0, vars + 4, -1.5707964897155762f, 0.0004363323678262532f,
                      0.174532949924469f, 2.9088826179504395f);
        if (*(f32 *)(moby + 0xF0) <= -1.5707964897155762f) {
            *(s32 *)(vars + 4) = 0;
            SetMobyState(moby, 5, -1);
            PlayMobySound(1, 0, moby);
        }
        break;
    case 5:
        StepValueTowardTarget(moby + 0xF0, vars + 4, -1.483530044555664f, 0.01745329424738884f,
                      0.0004363323678262532f, 0.872664749622345f);
        if (*(f32 *)(moby + 0xF0) >= -1.483530044555664f) {
            *(s32 *)(vars + 4) = 0;
            SetMobyState(moby, 6, -1);
        }
        break;
    case 6:
        StepValueTowardTarget(moby + 0xF0, vars + 4, -1.5707964897155762f, 0.0004363323678262532f,
                      0.174532949924469f, 2.9088826179504395f);
        if (*(f32 *)(moby + 0xF0) <= -1.5707964897155762f) {
            *(s32 *)(vars + 4) = 0;
            SetMobyState(moby, 7, -1);
            PlayMobySound(1, 0, moby);
        }
        break;
    }
    pos = linked + 0x10;
    qcopy(pos, moby + 0x10);
    vec_scale_to_length(frontOffset, moby + 0xE0, 5.7f);
    FastVecAdd(pos, pos, frontOffset);
    vec_scale_to_length(sideOffset, moby + 0xD0, 0.35f);
    FastVecAdd(pos, pos, sideOffset);
}


/* func_L11_00417340 is defined in L11_003D6270-g8.c (this unit has no $gp access for it). */

/* Reports whether the helper found the measured resource and updates its timer. */
/* Checks whether the enemy's damage source still exists and takes its damage off the
   enemy's health. */
s32 func_L11_00420C38(u8 *mobyArg) {
    u8 *vars = *(u8 **)(mobyArg + 0x68);
    u8 *source = FindOwnedEffectSlot(*(s32 *)(vars + 0x280), 0x10000, 0);
    if (source != 0) {
        *(f32 *)(vars + 0x20) = *(f32 *)(vars + 0x20) - *(f32 *)(source + 0x2C);
        return 1;
    }
    return 0;
}
