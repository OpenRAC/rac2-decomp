#include "common.h"

/* Small-data unit: the bodies whose state lives at $gp-relative offsets. */

extern void func_00281EB8(void *a0, void *a1, void *a2, float f12, float f13, float f14,
                          int a3);

extern float func_002A7940(void);

extern int func_002A7820(int a0, int a1);

extern float func_002A7878(float a, float b);

extern void func_L11_00458DF0(char *a0, void *a1, void *a2, int a3, int t0, float f12,
                              float f13);

extern void func_00282F20(char *a0, void *a1, float f12);

extern void func_002AB668(void *a0, void *a1, float f12);

extern void func_00282D30(char *a0, void *a1, float f12);

extern void func_002ACDE8(void *a0, void *a1, void *a2);

extern void func_00282CC0(void *a0, void *a1, void *a2);

extern float func_00283BE0(float a, float b);

extern void func_L00_002E6CF0(void *a0, void *a1);

extern void func_L11_00459E48(char *p);

extern void func_L11_00459EA0(char *p);

extern void func_L11_0045A8C0(char *p, float *v);

extern void func_00282D08(float *out, char *a, char *b, float k);

extern float func_00282E80(char *p, float *v);

extern float func_00283248(float a, float b);

extern void func_00283410(float *matrix, float *quat);

extern void func_00280B90(char *pkt, float *matrix, int mode);

extern int func_001163B0(void);

extern int D_L11_001B2014 __attribute__((sda));

extern int D_L11_001B2020 __attribute__((sda));

/* The vector the aim helpers read, at 0x001BA780 in joba. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L11AimVector;

extern L11AimVector D_L11_001BA780;

extern void *D_L11_001B1DB4 __attribute__((sda));

extern void *D_L11_001B1DB8 __attribute__((sda));

extern float D_L11_001B1DBC __attribute__((sda));

extern void *D_L11_001B1FBC __attribute__((sda));

extern void *D_L11_001B1FC0 __attribute__((sda));

extern float D_L11_001B1FC8 __attribute__((sda));

extern float D_L11_001B1FCC __attribute__((sda));

extern float D_L11_001B1FFC __attribute__((sda));

/* The level's script gate, read through $gp. */
extern s32 D_L11_001A8FF4 __attribute__((sda));

/* The shared table of the level's live projectiles. */
extern char D_00188660[];

/* The aiming target the level's spot checks measure against. */
extern char D_L11_001BA8C0[];

extern int func_00283CF0(float);

extern void func_002A7750(void *, int, int);

extern void func_002B60B0(void *, float, float, float, float);

extern void func_002A04B8(void *, void *, void *, void *);

extern void func_002A93B0(void *);

extern float func_002A96A0(void *, void *);

extern void *func_002A9640(void *, unsigned int, int);

extern float func_00282E48(void *, void *);

extern int func_002E59B0(void *, int);

extern void func_002E59F8(int);

extern int func_002E5CF8(int, int, char *);

extern void func_00283698(void *, void *);

extern void func_002AFFD8(void *, void *, int);

extern void func_002AB800(void *, void *);

extern void func_002A7A00(void *, float, float);

extern void func_00282CF0(void *, void *, void *);

extern float func_00282DB0(void *, void *);

extern float func_00282DF0(void *);


extern float func_00283B98(float, float);

extern float func_L00_002EE290(void *);

extern void func_L11_00454B60(char *);

extern void func_L11_00454DD8(char *);

extern u8 *func_L11_004417E8(u8 *);

extern int func_L11_004461C0(u8 *, u8 *);


extern float func_002A78D8(float, float);

extern int func_002A77E0(int);

extern void func_002ACEC0(void *, void *, void *, float);

extern void func_002AF000(void *, float, float, float);

extern char *func_002C2210(void *, int, int, float, float, float, int, int, void *, int);

extern void func_L00_0033E888(void *, void *, int, int, float, float, int, int, int, int, int);

extern float D_L11_001B1FE0 __attribute__((sda));
extern float D_L11_001B1FE4 __attribute__((sda));
extern float D_L11_001B1FE8 __attribute__((sda));
extern float D_L11_001B1FEC __attribute__((sda));
extern float D_L11_001B1FF0 __attribute__((sda));
extern float D_L11_001B1FF4 __attribute__((sda));
extern float D_L11_001B1FF8 __attribute__((sda));
extern int D_L11_001B2000 __attribute__((sda));
extern int D_L11_001B2004 __attribute__((sda));

/* Sprays smoke puffs and a few sparks out of a point, thrown toward the level's aim target. The mode picks the smaller puffs. */
void func_L11_00459640(float *center, int count, int mode)
{
    float vel[4], pos[4], axis[4], up[4], a[4], b[4], out[4];
    int i, j, sign;
    char *effect;
    float size, speed, angle, heading;

    FastVecSub(axis, D_L11_001BA8C0, center);
    axis[2] = 0;
    up[0] = 0;
    up[1] = 0;
    up[2] = 1;
    up[3] = 1;
    for (i = 0; i < count; i++) {
        size = RandomFloatRange(D_L11_001B1FF4, D_L11_001B1FF8);
        sign = RandomIntBelow(2);
        if (!sign)
            --sign;
        angle = RandomFloatRange(-1.0471977f, 1.0471977f);
        ApplyAxisRotationToQuaternion(vel, axis, up, angle);
        speed = RandomFloatRange(D_L11_001B1FE0, D_L11_001B1FE4) * (1.0f / 60.0f);
        vec_scale_to_length((char *)vel, vel, speed);
        vel[2] = RandomFloatRange(D_L11_001B1FE8, D_L11_001B1FEC) * (1.0f / 60.0f);
        qcopy(pos, center);
        pos[0] += RandomSignedFloatRange(0, 0.15f);
        pos[1] += RandomSignedFloatRange(0, 0.15f);
        pos[2] += RandomSignedFloatRange(0, 0.15f);
        if (!mode) {
            if (!(Rand() & 1)) {
                FastVecScale((char *)vel, vel, 1.5f);
                effect = SpawnGroundEffectParticle(pos, 60, D_L11_001B2000, size * 0.35f, size, D_L11_001B1FF0, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = SpawnGroundEffectParticle(pos, 60, D_L11_001B2004, size * 0.245f, size * 0.7f, D_L11_001B1FF0, 1, -sign, vel, 0);
            } else {
                FastVecSub(a, D_L11_001BA8C0, pos);
                vec_scale_to_length((char *)a, a, speed);
                FastVecAdd(vel, vel, a);
                effect = SpawnGroundEffectParticle(pos, 40, D_L11_001B2000, size * 2.05f, size, D_L11_001B1FF0, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = SpawnGroundEffectParticle(pos, 40, D_L11_001B2004, size * 1.4350000619888306f, size * 0.7f, D_L11_001B1FF0, 1, -sign, vel, 0);
            }
        } else {
            if (!(Rand() & 1)) {
                FastVecScale((char *)vel, vel, 1.5f);
                effect = SpawnGroundEffectParticle(pos, 60, D_L11_001B2000, size * 0.3f, size, D_L11_001B1FF0, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = SpawnGroundEffectParticle(pos, 60, D_L11_001B2004, size * (0.3f * 0.7f), size * 0.7f, D_L11_001B1FF0, 1, -sign, vel, 0);
            } else {
                FastVecSub(a, D_L11_001BA8C0, pos);
                vec_scale_to_length((char *)a, a, speed);
                FastVecAdd(vel, vel, a);
                effect = SpawnGroundEffectParticle(pos, 40, D_L11_001B2000, size * 0.25f, size, D_L11_001B1FF0, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = SpawnGroundEffectParticle(pos, 40, D_L11_001B2004, size * 0.175f, size * 0.7f, D_L11_001B1FF0, 1, -sign, vel, 0);
            }
        }
        if (effect)
            effect[9] = FloatToInt(4.0f) + 112;
    }
    for (j = 1; j >= 0; j--) {
        angle = RandomFloatRange(-0.9599312f, -1.3962636f);
        heading = RandomAngle();
        BuildSphericalOffset(a, RandomFloatRange(0, 0.5f) * (1.0f / 60.0f), heading, angle);
        FastVecSub(b, D_L11_001BA8C0, center);
        vec_scale_to_length((char *)b, b, 0.15f);
        FastVecAdd(center, center, b);
        size = RandomFloatRange(30000, 60000);
        out[0] = center[0] + RandomSignedFloatRange(0, 0.15f);
        out[1] = center[1] + RandomSignedFloatRange(0, 0.15f);
        out[2] = center[2] + RandomSignedFloatRange(0, 0.15f);
        if (mode)
            SpawnSpinningParticle_L00(out, a, 0x4F93E5FF, 0x102434EE, size, 0.5f, RandomIntRange(10, 20), 1, -1, -1, 0);
        else
            SpawnSpinningParticle_L00(out, a, 0x4F93E5FF, 0x102434EE, size, 0.5f, RandomIntRange(25, 60), 1, -1, -1, 0);
    }
}

/* Rebuilds the state's offset block from its rotation and installs the next handler. */
void func_L11_00459D48(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float rotation[4];

    vec_scale_to_length((char *)rotation, vars + 0x40, 1.0f);
    BuildAxisAngleQuaternion(rotation, rotation, *(float *)(vars + 0x30));
    FastVecScale(vars + 0x10, vars, *(float *)(vars + 0x60));
    RotateVectorByQuaternion(vars + 0x10, vars + 0x10, rotation);
    *(float *)(vars + 0x20) = -*(float *)(vars + 0x10);
    *(float *)(vars + 0x24) = -*(float *)(vars + 0x14);
    *(float *)(vars + 0x28) = -*(float *)(vars + 0x18);
    FastVecAdd(vars + 0x10, moby + 0x10, vars + 0x10);
    FastVecAdd(vars + 0x20, moby + 0x10, vars + 0x20);
    *(float *)(vars + 0x30) = fast_subtract_rotations(*(float *)(vars + 0x30),
                                         D_L11_001B1FFC * 0.000290888245f);
    AddDrawCallbackToList1(UpdateJobaEffectParticles, moby);
}

/* Aims the object's stage at the level's aim vector and dispatches the resulting packet. */
void func_L11_0045A578(char *moby)
{
    char pkt[144];
    float matrix[16];
    float quat[4];
    float point[4];
    char *vars = *(char **)(moby + 0x68);
    float scale;
    int parity;
    int alphaShift;

    InitSquareDrawPacket(pkt);
    lerp_vector(point, vars + 0x10, vars + 0x20, RandomFloatRange(0.0f, 1.0f));

    point[0] += RandomFloatRange(-0.1f, 0.1f) * *(float *)(vars + 0x60);
    point[1] += RandomFloatRange(-0.1f, 0.1f) * *(float *)(vars + 0x60);
    point[2] += RandomFloatRange(-0.1f, 0.1f) * *(float *)(vars + 0x60);

    *(long long *)(pkt + 120) = GetEffectTextureDescriptor((char *)0xB);
    *(long long *)(pkt + 128) = 0x0000FF9000000260LL;
    *(long long *)(pkt + 112) = 0LL;

    parity = Rand();
    *(long long *)(pkt + 136) = ((long long)((parity % 2) + 1) << 2) | 0x8000000040LL;
    alphaShift = RandomIntRange(0x40, 0x7F) << 24;
    *(int *)(pkt + 76) = (D_L11_001B2014 & 0xFFFFFF) + alphaShift;
    *(int *)(pkt + 72) = (D_L11_001B2014 & 0xFFFFFF) + alphaShift;
    *(int *)(pkt + 68) = (D_L11_001B2014 & 0xFFFFFF) + alphaShift;
    *(int *)(pkt + 64) = (D_L11_001B2014 & 0xFFFFFF) + alphaShift;

    quat[3] = 0.0f;
    quat[2] = FastMatrixHelperA(D_L11_001BA780.x_140 - point[0], D_L11_001BA780.y_144 - point[1]);
    quat[1] = -FastMatrixHelperA(vec_distance_xy((char *)point, &D_L11_001BA780.x_140),
                             D_L11_001BA780.z_148 - point[2]);
    quat[0] = RandomAngle();
    euler_to_matrix(matrix, quat);

    matrix[12] = point[0];
    matrix[13] = point[1];
    matrix[14] = point[2];
    matrix[15] = 1.0f;

    scale = RandomFloatRange(0.05f, 0.15f) * *(float *)(vars + 0x60);
    FastVecScale(pkt, pkt, scale);
    FastVecScale(pkt + 16, pkt + 16, scale);
    FastVecScale(pkt + 32, pkt + 32, scale);
    FastVecScale(pkt + 48, pkt + 48, scale);
    draw_world_quad(pkt, matrix, 0);

    *(int *)(pkt + 76) = (D_L11_001B2020 & 0xFFFFFF) + alphaShift;
    *(int *)(pkt + 72) = (D_L11_001B2020 & 0xFFFFFF) + alphaShift;
    *(int *)(pkt + 68) = (D_L11_001B2020 & 0xFFFFFF) + alphaShift;
    *(int *)(pkt + 64) = (D_L11_001B2020 & 0xFFFFFF) + alphaShift;

    FastVecScale(pkt, pkt, 0.5f);
    FastVecScale(pkt + 16, pkt + 16, 0.5f);
    FastVecScale(pkt + 32, pkt + 32, 0.5f);
    FastVecScale(pkt + 48, pkt + 48, 0.5f);
    draw_world_quad(pkt, matrix, 0);

    SpawnRandomSparkBeam(moby, point);
}

/* The launcher's state handler: re-arms the shot, aims the head at the level's
   target and hands the launch to the level's helpers. */
void func_L11_00454508(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float vec0[4];
    float vec1[4];
    float vec2[4];
    float damage;
    float dot;
    float len;
    int slot;
    char *hit;
    char *entry;
    u8 *other;

    if (*(u8 *)(moby + 0x20) == 0) {
        *(int *)(vars + 0x18) = (int)(vars + 0x60);
        *(float *)(moby + 0x2C) *= 0.75f;
        *(int *)(vars + 0x1DC) = -1;
        *(u8 *)(vars + 0x48) = FloatToInt(15.0f);
        *(u8 *)(vars + 0x4A) = FloatToInt(12.0f);
        *(float *)(vars + 0x1D0) =
            RandomFloatRange(-*(float *)(vars + 0x1D0), *(float *)(vars + 0x1D0)) *
            0.01745329424738884f;
        *(u8 *)(moby + 0x30) = 0x80;
        *(int *)(vars + 0x1D4) = 1;
        *(float *)(vars + 0x1D8) *= 0.01666666753590107f;
        SetControllerSpeedLimits(moby, 0.02777777798473835f, 1.6666667461395264f,
                      0.0011635529808700085f, 0.10471977293491364f);
        *(int *)(vars + 0x98) |= 4;
        *(float *)(vars + 0x60) = 0.75f;
        *(float *)(vars + 0x68) = 0.75f;
        *(int *)(vars + 0x64) = 0;
        *(float *)(vars + 0x6C) = 0.5f;
        *(float *)(vars + 0x70) = 1.134464144706726f;
        *(float *)(vars + 0x90) = 0.523598849773407f;
        *(float *)(vars + 0x8C) = 0.0027777778450399637f;
        get_moby_color(moby, vars + 0x1F0, vars + 0x1F4, vars + 0x1F8);
        *(u8 *)(vars + 0x28) = 3;
        *(int *)(vars + 0x30) = 0;
        *(short *)(vars + 0x1EC) = 0;
        ResetJobaDroneToIdle(moby);
    }
    if (*(short *)(vars + 0x1FC) == 0 && *(u8 *)(moby + 0x20) != 0xE &&
        D_L11_001A8FF4 == 0) {
        *(u16 *)(moby + 0x34) |= 0x400;
        if (*(u8 *)(moby + 0x31) != 0) {
            if (fast_vec_dist(moby + 0x10, D_L11_001BA8C0) < 24.0f) {
                UpdateMobyGroundCheck(moby);
                *(u8 *)(moby + 0x6F) = 0x16;
            }
        }
    } else {
        *(u16 *)(moby + 0x34) &= 0xFBFF;
    }
    if (*(u8 *)(moby + 0x95) >= 2) {
        if (IsVoicePlayingForOwner(moby, *(int *)(vars + 0x1DC)) == 0)
            *(int *)(vars + 0x1DC) = PlayMobySound(1, 4, moby);
    } else {
        if (IsVoicePlayingForOwner(moby, *(int *)(vars + 0x1DC))) {
            slot = *(int *)(vars + 0x1DC);
            if (slot != -1) {
                entry = gSoundState + slot * 0x70;
                if (*(char **)(entry + 0x88) == moby && *(u8 *)(entry + 0x74) != 0)
                    StopSoundVoice(slot);
            }
            *(int *)(vars + 0x1DC) = -1;
        }
    }
    if (*(short *)(vars + 0x1FC) != 0)
        *(int *)(vars + 0x98) &= ~0x10;
    else
        *(int *)(vars + 0x98) |= 0x10;
    hit = (char *)FindOwnedEffectSlot(moby, 0x10000, 0);
    if (hit != 0) {
        other = *(u8 **)(hit + 0x20);
        if (other != 0) {
            if (*(short *)(other + 0xAA) == 0xA03 /* moby class 2563 */)
                *(int *)(hit + 0x2C) = 0;
            else if (*(u8 *)(moby + 0x31) == 0 && *(short *)(other + 0xAA) == 0xB89 /* moby class 2953 */)
                *(int *)(hit + 0x2C) = 0;
        }
    }
    damage = UpdateAimTargetStrength(moby, hit);
    *(u8 *)(moby + 0xA8) = 0xFF;
    *(float *)(vars + 0x20) -= damage;
    if (damage != 0.0f) {
        if (*(u8 *)(moby + 0x20) != 3 && *(u8 *)(moby + 0x20) != 0xE) {
            vec_scale_to_length((char *)vec0, hit + 0x10, 0.8333333730697632f);
            RandomDirectionVector(vec1, -0.1388888955116272f, 0.1388888955116272f);
            FastVecAdd(vec0, vec0, vec1);
            if (*(short *)(vars + 0x1FC) == 0) {
                vec0[2] = RandomFloatRange(0.0f, 0.0f) * 0.00027777778450399637f;
                vec0[3] = 5627.9248046875f;
            } else {
                FastVecSub(vec2, GetArenaCenterPoint(*(u8 **)(moby + 0xB8)),
                              moby + 0x10);
                vec2[2] = 0.0f;
                vec_scale_to_length((char *)vec2, vec2, 1.0f);
                dot = FastVecDot(vec0, vec2);
                if (dot < 0.0f) {
                    vec_scale_to_length((char *)vec2, vec2, dot);
                    len = FastVecLength(vec0);
                    FastVecSub(vec0, vec0, vec2);
                    vec_scale_to_length((char *)vec0, vec0, len);
                }
            }
            FastVecAdd(vars + 0x100, vars + 0x100, vec0);
            RandomDirectionVector(vec1, 0.0017453294713050127f, 0.006981317885220051f);
            *(float *)(vars + 0x1B0) = FastAddRotations(*(float *)(vars + 0x1B0), vec1[0]);
            *(float *)(vars + 0x1B4) = FastAddRotations(*(float *)(vars + 0x1B4), vec1[1]);
            *(float *)(vars + 0x1B8) = FastAddRotations(*(float *)(vars + 0x1B8), vec1[2]);
            StartColorFade(moby, vars + 0x50);
            SetMobyState(moby, 0xD, 4);
        }
    }
    if (*(short *)(vars + 0x1FC) != 0) {
        matrix_from_basis_rows(vars + 0x170, moby + 0xC0);
        ComputeViewDirection(moby + 0x10, vars + 0x1A0, 0);
        if (IsPointInArenaInnerZone(*(u8 **)(moby + 0xB8), (u8 *)(moby + 0x10)) == 0) {
            *(int *)(vars + 0x20) = 0;
            SetMobyState(moby, 0xE, 4);
        }
        if (*(u8 *)(moby + 0x20) != 0xE) {
            len = *(float *)(moby + 0x18);
            other = GetArenaCenterPoint(*(u8 **)(moby + 0xB8));
            FastVecSub(vec0, moby + 0x10, other);
            vec0[2] = 0.0f;
            if (func_L00_002EE290(vec0) > 225.0f) {
                vec_scale_to_length((char *)vec0, vec0, 15.0f);
                other = GetArenaCenterPoint(*(u8 **)(moby + 0xB8));
                FastVecAdd(moby + 0x10, vec0, other);
                *(float *)(moby + 0x18) = len;
            }
        }
    }
    if (*(u8 *)(moby + 0x20) >= 2 && *(u8 *)(vars + 0x2E) == 2)
        ResetJobaDroneToIdle(moby);
    UpdateJobaDroneLockOn(moby);
}

extern unsigned short D_L11_001B1F84 __attribute__((sda));
extern float func_00283248(float a, float b);
extern void func_002A0F48(char *p);

/* Initialises a spawned object: clears its state flags, copies the two start vectors and the
   caller's parameters into the object and its state block, and aims it along the first vector. */
void func_L11_00458A98(char *moby, int owner, int controller, int goalObject, float gravity, float damage, void *startPos,
                       float *velocity, int fadeTime)
{
    char *vars = *(char **)(moby + 0x68);

    int flagsWord;

    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
    flagsWord = *(int *)(*(char **)(moby + 0x24) + 0x10);
    *(unsigned short *)(moby + 0x34) &= 0xEFFF;
    *(int *)(moby + 0x98) = flagsWord;
    *(unsigned char *)(moby + 0x30) = 0xFF;
    *(unsigned short *)(moby + 0x32) = 0xFF;
    moby[0x20] = 2;
    *(int *)(vars + 0x15C) = owner;
    *(int *)(moby + 0xB8) = controller;
    qcopy(moby + 0x10, startPos);
    qcopy(vars + 0xC0, velocity);
    *(unsigned short *)(vars + 0x16C) = D_L11_001B1F84;
    *(int *)(vars + 0x150) = fadeTime;
    *(float *)(vars + 0x4C) = gravity;
    *(unsigned short *)(vars + 0x16E) = 0;
    *(int *)(moby + 0xF0) = 0;
    *(int *)(moby + 0xF4) = 0;
    *(float *)(moby + 0xF8) = FastMatrixHelperA(velocity[0], velocity[1]);
    *(float *)(vars + 0x158) = damage;
    func_002A0F48(moby);
    *(int *)(vars + 0x164) = goalObject;
    *(int *)(moby + 0x78) = 0xFF84E643;
}

extern char *func_0029EFD0(int);
extern void func_L11_00460258(void *, int);
extern float D_L11_001B22C4 __attribute__((sda));
extern int D_L11_001B22CC __attribute__((sda));
extern void func_002E5DA0(int, int, char *, int);
