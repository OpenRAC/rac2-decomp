#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

extern void func_002A7750(void *, s32, s32);

extern void func_002833F0(void *, void *);

extern void func_00283738(void *, void *, void *);

extern void func_002830C0(void *, void *, void *);

extern s32 D_L16_001B18F0 __attribute__((sda));

extern s32 D_L16_001B18E0 __attribute__((sda));

extern s32 D_L16_001B1704 __attribute__((sda));

extern char D_L16_00189E20[] __attribute__((nosda));

extern float D_L16_001B1708 __attribute__((sda));

extern float D_L16_00189EF8 __attribute__((nosda));

extern void func_002A7470(void *, s32, s32, void *);

extern u32 D_001A79F0[1];

extern float D_L16_001B1444 __attribute__((sda));

extern float D_L16_001B1448 __attribute__((sda));

extern char D_L16_001B9B00[];

extern void func_002B60B0(void *, float, float, float, float);

extern s32 func_00283CF0(float);

extern float func_00282E48(void *, void *);

extern void func_002A93B0(void *);

extern void func_002AEE70(void *, void *, void *, float, float, float);

extern void func_002AB8C0(void *, void *);

extern s32 func_002A9640(void *, s32, s32);

extern s32 func_00282978(void *);

extern float func_002A96A0(void *, void *);

extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);

extern void func_0029F338(void *);

extern void func_002A6C58(void *, s32, s32);

extern void *func_0029EFD0(s32);

extern float func_L07_003F90E8(s32, s32, float, float);

extern void func_L00_00310748(void *, s32, void *, float, float);

extern void func_002B37E8(void *, void *);

extern void func_002AAC80(void *, float, float, float, float);

extern void func_0032C700(void *, s32, s32, s32, s32, s32, s32, s32, float, float,
                          s32, s32, s32, s32);

extern char D_L16_001A63A8[] __attribute__((nosda));

extern char D_L16_001B1850[] __attribute__((nosda));

extern char D_L16_001B1870[] __attribute__((nosda));

extern void func_0026FEB8(void *);

extern void func_002B6D28(void);

extern void func_00282948(void *);

extern void func_L16_00412C58(void *, s32, s32);

extern s32 func_002A7820(s32, s32);

extern float func_002A7940(void);

extern void func_L16_00414038(void *, s32, s32, s32, float, float, float, s32, void *);

/* Raises the handle's measured flag, rebuilds the motion record from the level's
   pair of measured vectors and submits both halves of the sub-object. */
/* Sets up a child object so it starts on the parent's position and direction. */
void func_L16_00413690(u8 *child, u8 *parent)
{
    u8 basis[0x30];

    SetMobyState(child, 1, -1);
    *(u16 *)(child + 0x34) |= 0x100;
    euler_rotation_basis(basis, &D_L16_001B18F0);
    multiply_matrix3x3(child + 0xC0, parent, basis);
    transform_vector(child + 0x10, &D_L16_001B18E0, parent);
}

/* Raises the level's one-shot flag while the counter is low, then hands the sub-object
   its tail record. */
/* Plays voice lines and a sound when the hero reaches certain moments of the fight. */
void func_L16_00412AF0(u8 *moby)
{
    u8 *vars;
    u8 *hero;
    u8 *voice;

    vars = *(u8 **)(moby + 0x68);
    hero = D_L16_00189E20;
    if (*(s32 *)(hero + 0x2294) == 0x39) {
        if (*(s32 *)(hero + 0x1B8) == 0) {
            STUB_printf(D_L16_001B1850);
            PlayUnplayedVoiceLine(moby, 0x1C, 0x20);
            D_L16_001B1704++;
        }
    }
    voice = D_L16_001A63A8;
    if (*(s16 *)(voice + 0x72) == 3 && *(s16 *)(voice + 0x6C) < 0x1770) {
        STUB_printf(D_L16_001B1870);
        ResumeMusicStream();
    }
    FastFloatHelperD(vars + 0x350);
}

/* func_L16_00413EC8 is defined in L16_00403900.c (this unit has no $gp access for it). */

/* Two timed transitions of the same handle: the first drops the swung state once the
   measured clock passes the level's threshold, the second raises it below the other. */
/* Switches the boss between a flying state and a hovering state depending on how high the hero is. */
void func_L16_00410B88(u8 *moby)
{
    u8 *vars;
    u8 *hero;

    vars = *(u8 **)(moby + 0x68);
    if (*(s32 *)(vars + 0x26C) != 0) {
        if (*(float *)(vars + 0x264) + D_L16_001B1708 > D_L16_00189EF8) {
            *(s32 *)(vars + 0x26C) = 0;
            *(s32 *)(vars + 0x270) = *(u8 *)(moby + 0x20);
            *(s32 *)(vars + 0x274) = *(u8 *)(moby + 0x95);
            SetMobyState(moby, 0x10, 4);
        }
    } else {
        hero = D_L16_00189E20;
        if (*(s32 *)(hero + 0x2294) != 0x81
            && *(float *)(vars + 0x264) + D_L16_001B1708 < *(float *)(hero + 0xD8)) {
            *(s32 *)(vars + 0x268) = 0;
            *(s32 *)(vars + 0x26C) = 1;
            if (*(u8 *)(moby + 0x43) != 0x16)
                StartAnimationBlended(moby, 0x16, 0, 0x1E);
            if (*(u8 *)(*(u8 **)(vars + 0x1F0) + 0x43) == 0xA)
                StartAnimationBlended(*(u8 **)(vars + 0x1F0), 0, 0, 0x1E);
        }
    }
}

/* func_L16_0040DAE0 is defined in L16_00403900.c (this unit has no $gp access for it). */

/* Arms the object the level has just spawned: the entry latch, the two measured speed
   ratios, the object's own timer, then the two children and the hero sensor. */
/* Updates the Snivelak boss each frame: setup, hearing the hero, taking damage; returns 1 when it dies. */
s32 func_L16_00404A60(u8 *moby)
{
    u8 *vars;
    u8 *hit;
    float speedA;
    float speedB;
    float zero;
    float damage;

    vars = *(u8 **)(moby + 0x68);
    if (*(u8 *)(moby + 0x20) == 0) {
        if (gCurrentMapIndex[0] == 0x10
            && (*(s16 *)(moby + 0xB2) == 0x27 || *(s16 *)(moby + 0xB2) == 0x114))
            *(s32 *)(vars + 0x2AC) = 1;
        if (*(s32 *)(vars + 0x2AC) != 0)
            *(float *)(vars + 0x28C) = *(float *)(moby + 0x18) + 300.0f;
        *(u8 *)(vars + 0x150) = 8;
        *(s32 *)(vars + 0x188) = 3;
        *(float *)(vars + 0x17C) = 0.15000001f;
        *(s32 *)(vars + 0x2A4) = 0;
        *(float *)(vars + 0x170) = 0.5f;
        *(float *)(vars + 0x174) = 0.5f;
        if (*(s16 *)(vars + 0x24) == 0) {
            *(s16 *)(vars + 0x24) = 5;
            *(float *)(vars + 0x20) = 5.0f;
        }
        speedB = *(float *)(vars + 0x2A0);
        speedA = (speedB + speedB) * 0.00027777778f;
        speedB = speedB * 0.016666668f;
        *(s32 *)(vars + 0x50) = 0;
        *(s32 *)(vars + 0x88) = *(s32 *)(vars + 0x88) | 0x17;
        *(u8 *)(vars + 0x2E) = 1;
        *(float *)(vars + 0x84) = 0.5f;
        *(float *)(vars + 0x54) = 1.0f;
        *(float *)(vars + 0x58) = 0.40000001f;
        *(float *)(vars + 0x5C) = 0.40000001f;
        *(float *)(vars + 0x60) = 1.5707965f;
        *(float *)(vars + 0x80) = 1.5533432f;
        SetControllerSpeedLimits(moby, speedA, speedB, 0.0017453295f, 0.20943955f);
        SetMobyState(moby, 1, 0);
        if (*(u8 *)(moby + 0x43) != 0)
            StartAnimationBlended(moby, 0, 0, 0);
        *(u8 *)(vars + 0x48) = FloatToInt(17.0f);
        *(u8 *)(vars + 0x4A) = FloatToInt(32.0f);
    }
    if (*(u8 *)(moby + 0x31) != 0) {
        if (fast_vec_dist(moby + 0x10, D_L16_001B9B00) < 24.0f) {
            UpdateMobyGroundCheck(moby);
            *(u8 *)(moby + 0x6F) = 0x16;
        }
    }
    UpdateWrappedAngleOffset(moby, vars + 0x284, vars + 0x278, D_L16_001B1444,
                  D_L16_001B1448 * 0.00029088825f, -1.0f);
    UpdateColorFade(moby, vars + 0x140);
    hit = FindOwnedEffectSlot(moby, 0x10000, 0);
    if (FastDecTimer(vars + 0x26) == 0)
        hit = 0;
    if (hit != 0) {
        float v = *(float *)(hit + 0x2C);

        if (*(float *)(vars + 0x1E8) != 0.0f
            && *(u8 **)(hit + 0x20) != 0
            && *(s16 *)(moby + 0xAA) == *(s16 *)(*(u8 **)(hit + 0x20) + 0xAA))
            *(float *)(hit + 0x2C) = v * *(float *)(vars + 0x1E8);
        *(u8 *)(moby + 0xA8) = 0xFF;
    }
    damage = UpdateAimTargetStrength(moby, hit);
    *(u8 *)(moby + 0xA8) = 0xFF;
    *(float *)(vars + 0x20) = *(float *)(vars + 0x20) - damage;
    if ((float)*(s16 *)(vars + 0x24) * 0.33000001f <= damage || *(float *)(vars + 0x20) <= 0.0f) {
        if (*(u8 *)(moby + 0x43) != 4)
            StartAnimationBlended(moby, 4, 0, 3);
        SetMobyState(moby, 9, 3);
    }
    if (*(u8 *)(vars + 0x2E) == 2) {
        MarkMobySpawned(*(u8 **)(vars + 0x274));
        SetDeathBits(moby, 0, 3);
        return 1;
    }
    zero = 0.0f;
    *(s32 *)(vars + 0x260) = SelectAimTarget_002B3BA8(moby, *(s32 *)(vars + 0x250), *(float *)(vars + 0x254), zero, 0, 0);
    *(s32 *)(vars + 0x2B4) = SelectAimTarget_002B3BA8(moby, *(s32 *)(vars + 0x2B0), zero, zero, 0, 0);
    return 0;
}

extern void func_L16_00411368(void *);
extern float D_L16_00189EA8 __attribute__((nosda));
extern u8 *D_L16_001B9B50 __attribute__((nosda));
extern float D_L16_001B16FC __attribute__((sda));
extern float D_L16_001B1700 __attribute__((sda));
extern void func_L00_00424A08(s32, float, float);
extern void func_L00_00424A50(float, float);
extern float func_00283CE0(s32);
extern void func_L01_002F14E8(s32, s32, float);
extern s32 D_L16_001B2648[] __attribute__((sda));
extern void func_L16_004130B0(void *, s32);
extern s32 func_L02_003272D8(void *);
extern void func_002AEC18(void *, s32);
extern void func_002B0990(void *, void *, s32, s32, float);
extern void func_0029FC20(void *, s32, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_L13_0040DC20(void *, void *, void *, s32, float);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float D_L16_001B16E0 __attribute__((sda));
extern u8 D_L16_00189EF0[] __attribute__((nosda));
extern void func_00282D30(void *, void *, float);
extern void func_0029FCC0(void *, s32, void *);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00283B98(float, float);
extern void func_002AEC48(void *, void *, s32, float, float);
extern u8 D_L16_00189F30[] __attribute__((nosda));
extern float D_L16_001B1640 __attribute__((sda));
extern float D_L16_001B1644 __attribute__((sda));

/* Updates a boss part each frame: follows the parent, makes sounds and moves the children. */
void func_L16_00411480(u8 *moby)
{
    u8 *state;
    s32 value;
    float rate;
    state = *(u8 **)(moby + 0x68);
    if (*(s32 *)(state + 0x26C) != 0)
        BobAlongSineWave(moby);
    if (moby[0x95] != 0) {
        if (D_L16_00189EA8 > 118.0f && *(s16 *)(D_L16_001B9B50 + 0x86) == 0) {
            rate = 0.003f;
            follow_camera_set_distance(0, D_L16_001B16FC, rate);
            follow_camera_set_height(D_L16_001B1700, rate);
        }
        StartHudOverlay(11, 0, *(float *)(state + 0x20) / IntToFloat(*(s16 *)(state + 0x24)));
        if ((D_L16_001B2648[0] & 31) == (((s32)moby >> 8) & 31))
            SpawnBossRockProjectile(moby, 0);
        UpdateMobyGroundCheck(moby);
    }
    UpdateColorFade(moby, state + 0x50);
    value = PackObjectHandle(moby);
    if (*(void **)(state + 0x1F0)) SetMobyLightColor(*(void **)(state + 0x1F0), value);
    if (*(void **)(state + 0x238)) SetMobyLightColor(*(void **)(state + 0x238), value);
    if (*(void **)(state + 0x23C)) SetMobyLightColor(*(void **)(state + 0x23C), value);
    if (*(u16 *)(moby + 0x96) < 0xFFFF) ++*(u16 *)(moby + 0x96);
    SetValueAndStartSmoothChange(*(void **)(state + 0x1F0), state + 0x390, 2, 1, 4.0f);
}



/* Aims the turret part at the hero and swivels it, limited to a safe angle. */
void func_L16_0040CF98(u8 *moby)
{
    float partPos[4];
    float target[4];
    u8 *state;
    u8 *aimPoint;
    float value;
    float scale;
    state = *(u8 **)(moby + 0x68);
    FastFloatHelperD(state + 0x238);
    FastDecTimer(state + 0x23C);
    if (*(u16 *)(moby + 0x96) < 0xFFFF) ++*(u16 *)(moby + 0x96);
    TransformMobyJointToWorld(moby, 0, partPos);
    if (moby[0x20] != 4) {
        aimPoint = state + 0x1F0;
        value = fast_vec_dist(partPos, aimPoint) - 1.0f;
        FastVecScale(target, D_L16_00189F30, value + value);
        target[2] = 0.0f;
        FastVecAdd(target, target, aimPoint);
        FastVecSub(partPos, target, partPos);
        *(float *)(state + 0x2B8) = fast_subtract_rotations(FastMatrixHelperA(partPos[0], partPos[1]), *(float *)(moby + 0xF8));
        TransformMobyJointToWorld(moby, 1, partPos);
        FastVecSub(partPos, target, partPos);
        value = fast_subtract_rotations(-FastMatrixHelperA(vec_length_xy(partPos), partPos[2]), *(float *)(moby + 0xF4));
        if (value > 0.523598849773407f) value = 0.523598849773407f;
        else if (value < -0.523598849773407f) value = -0.523598849773407f;
        *(float *)(state + 0x334) = value;
        scale = 0.5f;
    } else {
        scale = 0.085f;
        *(float *)(state + 0x2B8) = FastAddRotations(*(float *)(state + 0x298), 0.523598849773407f);
    }
    UpdateEasedNode(moby, state + 0x250, 0, D_L16_001B1640 * scale, D_L16_001B1644 * scale);
    UpdateEasedNode(moby, state + 0x2D0, 1, D_L16_001B1640 * scale, D_L16_001B1644 * scale);
}
