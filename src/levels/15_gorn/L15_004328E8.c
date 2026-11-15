#include "include_asm.h"
#include "common.h"

extern void func_0029F978(unsigned char *, int, unsigned char *);
extern void func_L15_003804B8(int, void *);
#define GF(offset) (((GornState *)state)->f[(offset) / 4])
#define GI(offset) (((GornState *)state)->i[(offset) / 4])

/* Measured prefixes with integer/float views of the same game records. */
typedef union { float f[0x660 / 4]; int i[0x660 / 4]; } GornState;
typedef union { float f[0x80 / 4]; unsigned short h[0x80 / 2]; unsigned char b[0x80]; } GornOwnerFields;

typedef int GornQuad __attribute__((mode(TI)));
extern float func_00283198(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

extern void func_00283098(void *, void *, void *);
extern void func_0029FC20(void *, int, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_00282DF0(void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002831B0(float);
extern float func_00283180(float);
extern char D_L15_001B97C0[];

extern void func_L06_00382608(char *, int, int, int, float, int);
extern int func_002EEB00(char *);
extern void func_002EE920(char *, char *);
extern void func_002EE678(char *, int);
extern void func_L05_0037C160(char *);
extern void func_L05_0037B538(char *, int, int, int);
typedef struct GornPathPoint {
    float position[3];
    float action;
} GornPathPoint;

typedef struct GornPath {
    int count;
    int pad[3];
    GornPathPoint points[1];
} GornPath;
extern char *D_L15_001FE480[];
extern void func_L15_00436BA8(char *);
extern void func_L15_00436C68(void);

/* ---- shared declarations ---- */

extern int func_002ED688(unsigned char *owner);
extern void func_L05_0037AEC0(char *object, int flag);
extern void func_L05_00379C68(int arg0, int value);
extern void func_L00_002E6DB8(void *, void *);
extern void func_L00_002E6CF0(void *a0, void *a1);
extern void func_L00_002E6EF8(void *, int);
extern void func_L15_00438238(void);
extern void func_L15_00438260(void);
extern void func_L15_00438518(void);

extern void func_002FC560(int, int);
extern void func_0027DE50(int, int, int, int, long);
extern int func_00282948(void *);
extern void func_L15_00432A60(void *, int, int, float, float, float, int, int, int);
extern short D_001A6480[];
extern char D_L15_00269FE0[];

/* Sets the level's four effect blocks up: the screen context first, then, when
   the level's own record says the object is idle, the four blocks of the
   effect data, each with its own size and colour. */
void func_L15_004328E8(void *moby) {
    char *vars = *(char **)(moby + 0x68);

    VU1_addGSregister(0x42, 0x48);
    DrawColoredRectangle(0, gScreenAdjustOffsets[0xA9], 0, gScreenAdjustOffsets[0xA8], 0x40404040);
    if (FastFloatHelperD(vars + 0x50) == 0) {
        char *ribbonData = D_L15_00269FE0;

        DrawGornRibbon(ribbonData, 0x46, 0x46, 3.2f, 6.35f, 0.2f, 0x0A, 0x007F7F7F, 0x00FF1010);
        DrawGornRibbon(ribbonData + 0xA0, 0x20, 0x20, 3.1f, 6.19f, 0.2f, 0x0A, 0x007F7F7F, 0x00FF1040);
        DrawGornRibbon(ribbonData + 0x140, 0x20, 0x20, 3.1f, 6.19f, 0.2f, 0x0A, 0x007F7F7F, 0x00FF1040);
        DrawGornRibbon(ribbonData + 0x1E0, 0x20, 0x20, 3.1f, 6.19f, 0.2f, 0x0A, 0x007F7F7F, 0x00FF1040);
    }
}

/* func_L15_00432A60 is in L15_00432A60-ribbon.c. */

extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern int func_L00_00367720(void);
extern void func_L05_00379E60(void *, void *, int, int);
extern void func_L05_0037AE40(void *);
extern void func_L15_004353E8(char *);
extern void func_L15_00434610(void *, int);
extern void func_L15_00435E80(void);
extern void func_L15_00434D28(void *);
extern void func_L05_00424990(void *, int, int, int, int, int, int, int, float, int, int, int);
extern int func_002A77E0(int);
extern void func_0029F338(void *);
extern void func_002833F0(void *, void *);
/* Per-frame update of the Gorn enemy ship moby (class 4625): arms it, runs its route, fades it in and out, and drops it when it falls out of the level. */
void func_L15_00434100(unsigned char *moby) {
    float point[4] __attribute__((aligned(16)));
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float ratio;
    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        if (!GetStoredPointerValue()) return;
        InitGornShip((char *)moby);
        if (*(int *)(vars + 0x264))
            AppendLevelObject(moby, ResetGroupToPathStart, 0, 0);
        qcopy(vars + 0x430, moby + 0x10);
        break;
    case 1:
        UpdateGornShipFlight(moby, 0);
        break;
    case 2:
        UpdateGornShipFlight(moby, 1);
        if (FastFloatHelperD(vars + 0x274)) {
            moby[0x20] = 3;
            *(int *)(vars + 0x274) = 180;
        }
        break;
    case 3:
        UpdateGornShipFlight(moby, 1);
        ratio = IntToFloat(*(int *)(vars + 0x274)) / IntToFloat(180);
        moby[0x23] = FloatToInt((1.0f - ratio) * 95.0f) + 32;
        if (FastFloatHelperD(vars + 0x274)) {
            *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
            moby[0x20] = 4;
            *(int *)(vars + 0x274) = 600;
            moby[0x23] = 128;
            *(unsigned short *)(moby + 0x34) &= 0xFFF7;
        }
        break;
    case 4:
        UpdateGornShipFlight(moby, 0);
        if (FastFloatHelperD(vars + 0x274)) {
            *(int *)(moby + 0x98) = 0;
            moby[0x20] = 5;
            *(int *)(vars + 0x274) = 180;
            *(unsigned short *)(moby + 0x34) |= 8;
        }
        break;
    case 5:
        UpdateGornShipFlight(moby, 1);
        ratio = IntToFloat(*(int *)(vars + 0x274)) / IntToFloat(180);
        moby[0x23] = FloatToInt(ratio * 95.0f) + 32;
        if (FastFloatHelperD(vars + 0x274)) {
            *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
            moby[0x20] = 2;
            *(int *)(vars + 0x274) = 480;
            moby[0x23] = 32;
        }
        break;
    case 6:
        point[0] = *(float *)(moby + 0x10) + RandomFloatRange(-3.0f, 3.0f);
        point[1] = *(float *)(moby + 0x14) + RandomFloatRange(-3.0f, 3.0f);
        point[2] = *(float *)(moby + 0x18) + RandomFloatRange(-3.0f, 3.0f);
        if (*(int *)(vars + 0x278) == 0) {
            SpawnShockwaveBurst(point, 1, 24, 24, 24, 24, 24, 0, 3.0f, 1, 1, 1);
            *(int *)(vars + 0x278) = 1;
        }
        if (RandomIntBelow(12) == 0 && *(float *)(moby + 0x18) > 350.0f)
            SpawnShockwaveBurst(point, 0, 4, 4, 4, 4, 4, 0, 1.5f, 0, 0, 0);
        *(float *)(moby + 0x18) -= *(float *)(vars + 0x27C);
        *(float *)(vars + 0x27C) += 0.0005555555690079927f;
        *(float *)(vars + 0x404) = FastAddRotations(*(float *)(vars + 0x404), 0.0014544413425028324f);
        euler_rotation_basis(moby + 0xC0, vars + 0x400);
        SpawnGornShipDamageEffects(moby);
        if (*(float *)(moby + 0x10) < 2.0f || *(float *)(moby + 0x10) > 1021.0f ||
            *(float *)(moby + 0x14) < 2.0f || *(float *)(moby + 0x14) > 1021.0f ||
            *(float *)(moby + 0x18) < 2.0f || *(float *)(moby + 0x18) > 1021.0f)
            ResetObjectActionState(moby);
        break;
    case 7:
        FastVecAdd(moby + 0x10, vars + 0x410, moby + 0x10);
        *(float *)(vars + 0x418) -= 0.003055555745959282f;
        *(float *)(vars + 0x404) = FastAddRotations(*(float *)(vars + 0x404), 0.02617994323372841f);
        euler_rotation_basis(moby + 0xC0, vars + 0x400);
        if (*(float *)(moby + 0x10) < 2.0f || *(float *)(moby + 0x10) > 1021.0f ||
            *(float *)(moby + 0x14) < 2.0f || *(float *)(moby + 0x14) > 1021.0f ||
            *(float *)(moby + 0x18) < 2.0f || *(float *)(moby + 0x18) > 1021.0f) {
            MarkMobySpawned(moby);
            return;
        }
        break;
    }
    FastFloatHelperD(vars + 0x450);
}

extern s32 D_L15_001AEE20[] __attribute__((sda));
extern s32 D_L15_001B1780[] SDATA(D_L15_001B1780);
extern s32 D_L15_001B17B0[] SDATA(D_L15_001B17B0);
extern u8 D_L15_00188660[];
extern s32 func_002E5CF8(s32 a, s32 b, void *c);
extern s32 func_002A77E0(s32 a);
extern f32 func_002A7878(f32 a, f32 b);
extern void func_0029FCC0(void *obj, s32 a, void *out);
extern void func_L10_0039D5E0(void *a, void *b, s32 c, s32 d, f32 e, f32 f, f32 g, f32 h, s32 i, s32 j, s32 k, s32 l);
extern s32 func_00283CF0(f32 a);
extern void func_L15_00434F90(char *object, int a1, int joint, float radius);
/* The particle helper has a different catalogue body in PAL. */
extern void ref_L15_00434D28_00(char *object, int joint, int unused, float radius);

/* Adds damage effects to the Gorn ship: crackling sparks and puffs of smoke that grow as it loses parts. */
void func_L15_00434D28(void *object)
{
    u8 *obj = (u8 *)object;
    u8 *vars = *(u8 **)(obj + 0x68);
    u8 *soundSlot = D_L15_00188660 + *(s32 *)(vars + 0x458) * 0x70;
    f32 fromPoint[4] __attribute__((aligned(16)));
    f32 toPoint[4] __attribute__((aligned(16)));
    s32 burstCount;
    s32 remaining;
    s32 *jointList;

    if (*(u8 **)(soundSlot + 0x88) != obj || soundSlot[0x74] == 0) {
        *(s32 *)(vars + 0x458) = PlayMobySound(3, 4, obj);
    }
    if (RandomIntBelow(0xF) == 0 && D_L15_001AEE20[0] < 4) {
        TransformMobyJointToWorld(obj, D_L15_001B1780[RandomIntBelow(0xB)], fromPoint);
        TransformMobyJointToWorld(obj, D_L15_001B1780[RandomIntBelow(0xB)], toPoint);
        D_L15_001AEE20[0] = D_L15_001AEE20[0] + 1;
        CreateEnergyStrip(fromPoint, toPoint, 0x19, 0, 0.5f, 0.2f, 0.4020000100135803f, 1.122249960899353f, 0x7F7F7F, 0xFF1010, 0x46, 0x46);
    }
    if (*(s32 *)(vars + 0x26C) < 7) {
        burstCount = FloatToInt(8.0f - (f32)*(s32 *)(vars + 0x26C));
        if (burstCount > 0) {
            remaining = burstCount;
            jointList = D_L15_001B17B0;
            while (1) {
                if (RandomIntBelow(2) != 0) {
                    SpawnGornPuffParticle((char *)obj, *jointList, 0, RandomFloatRange(2.0f, 3.0f));
                    ref_L15_00434D28_00((char *)obj, *jointList, 0, RandomFloatRange(0.5f, 1.5f));
                }
                remaining--;
                jointList++;
                if (remaining == 0) break;
            }
        }
    }
    if (RandomIntBelow(2) != 0 && *(s32 *)(vars + 0x26C) < 2) {
        SpawnGornPuffParticle((char *)obj, 0x14, 1, 7.0f);
        ref_L15_00434D28_00((char *)obj, 0x14, 0, RandomFloatRange(3.0f, 4.5f));
    }
}



typedef struct GornEffectCamera {
    char pad00[0x140];
    float position[4];
} GornEffectCamera;
extern GornEffectCamera D_L15_001B9680;
extern unsigned char *D_L15_001FF4AC;
extern void func_0029FCC0(void *, int, void *);
extern float func_00283248(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern void func_002AF000(void *, float, float, float);
extern unsigned char *func_002BDCE8(float, float, float, float,
                                   void *, int, void *, int, int);
extern int func_002A7820(int, int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);



/* Spawns one drifting smoke particle near a joint of the object. */
void func_L15_004351E0(char *object, int joint, int unused, float radius) {
    float initial[4], point[4], velocity[4];
    float heading, speed, tilt, yaw;
    unsigned char *particle;
    unsigned char *data;

    TransformMobyJointToWorld(object, joint, initial);
    heading = FastMatrixHelperA(D_L15_001B9680.position[0] - *(float *)(object + 0x10),
                            D_L15_001B9680.position[1] - *(float *)(object + 0x14));
    point[0] = initial[0] + RandomSignedFloatRange(0, radius);
    point[1] = initial[1] + RandomSignedFloatRange(0, radius);
    point[2] = initial[2] + RandomSignedFloatRange(0, radius);
    speed = RandomFloatRange(radius * 0.008333333767950535f,
                          radius * 0.01666666753590107f);
    tilt = RandomSignedFloatRange(0, 1.396263599395752f);
    yaw = FastAddRotations(heading, RandomSignedFloatRange(0, 1.5707964897155762f));
    BuildSphericalOffset(velocity, speed, yaw, tilt);
    particle = SpawnSpinningSparkParticle(0, 1.0f, 1.01f, radius * 210000.0f,
                            point, -1, velocity, 0x307F7F7F, 0);
    if (particle != 0) {
        particle[3] = 0x48;
        *(short *)(particle + 0xA) = RandomIntRange(40, 70);
        particle[9] = FloatToInt(4.0f) + 0x60;
        data = particle + 0x20;
        *(float *)(data + 0x1C) = IntToFloat(RandomIntRange(1, 10));
        *(int *)(data + 4) = 3;
        data[0xA] = 0x7F;
        data[0xB] = particle[0xA];
        particle[2] = *D_L15_001FF4AC;
    }
}

/* Sets up the Gorn ship the first time: its health, joint positions and the table of part positions. */
void func_L15_004353E8(char *object)
{
    GornOwnerFields *fields = (GornOwnerFields *)object;
    char *state = *(char **)(object + 0x68);
    char *record;
    char *a = state + 0x2B0;
    char *b = state + 0x2F0;
    char *c = state + 0x330;
    char *d = state + 0x370;
    char *e = state + 0x3B0;
    char *f = state + 0x3F0;
    char *position = object + 0x10;
    record = (char *)GetMobyMotionData((unsigned char *)object);
    *(int *)(record + 0x148) = FloatToInt(150.0f);
    InitSpawnedSubObject(object, 1);
    GF(0x180) = 150.0f;
    object[0x20] = 1;
    *(unsigned char *)(object + 0x30) = 255;
    *(unsigned short *)(object + 0x32) = 0x1FF;
    *(float *)(object + 0x2C) = 0.675f;
    *(unsigned short *)(object + 0x34) |= 0x100;
    *(unsigned short *)(object + 0x7C) = 63;
    GI(0x458) = -1;
    GI(0x268) = 1;
    GI(0x270) = 0;
    GI(0x27C) = 0;
    GI(0x45C) = 0;
    GI(0x278) = 0;
    TransformMobyJointPoint(object, 14, state + 0x280);
    TransformMobyJointPoint(object, 16, state + 0x2C0);
    TransformMobyJointPoint(object, 18, state + 0x300);
    TransformMobyJointPoint(object, 15, state + 0x340);
    TransformMobyJointPoint(object, 17, state + 0x380);
    TransformMobyJointPoint(object, 19, state + 0x3C0);
    FastVecSub(a, a, position);
    FastVecSub(d, d, position);
    FastVecSub(d, d, a);
    FastVecScale(a, a, 1.0f / fields->f[0x2C / 4]);
    FastVecScale(d, d, 1.0f / fields->f[0x2C / 4]);
    FastVecSub(b, b, position);
    FastVecSub(e, e, position);
    FastVecSub(e, e, b);
    FastVecScale(b, b, 1.0f / fields->f[0x2C / 4]);
    FastVecScale(e, e, 1.0f / fields->f[0x2C / 4]);
    FastVecSub(c, c, position);
    FastVecSub(f, f, position);
    FastVecSub(f, f, c);
    FastVecScale(c, c, 1.0f / fields->f[0x2C / 4]);
    FastVecScale(f, f, 1.0f / fields->f[0x2C / 4]);
    AttachManipulator((unsigned char *)object, 12, (unsigned char *)(state + 0x460));
    AttachManipulator((unsigned char *)object, 13, (unsigned char *)(state + 0x4A0));
    AttachManipulator((unsigned char *)object, 14, (unsigned char *)(state + 0x4E0));
    AttachManipulator((unsigned char *)object, 15, (unsigned char *)(state + 0x520));
    AttachManipulator((unsigned char *)object, 16, (unsigned char *)(state + 0x560));
    AttachManipulator((unsigned char *)object, 17, (unsigned char *)(state + 0x5A0));
    AttachManipulator((unsigned char *)object, 18, (unsigned char *)(state + 0x5E0));
    AttachManipulator((unsigned char *)object, 19, (unsigned char *)(state + 0x620));
    GF(0x510) = GF(0x2B0) * 1024.0f;
    GF(0x514) = GF(0x2B4) * 1024.0f;
    GF(0x518) = GF(0x2B8) * 1024.0f;
    GF(0x550) = GF(0x370) * 1024.0f;
    GF(0x554) = GF(0x374) * 1024.0f;
    GF(0x558) = GF(0x378) * 1024.0f;
    GF(0x590) = GF(0x2F0) * 1024.0f;
    GF(0x594) = GF(0x2F4) * 1024.0f;
    GF(0x598) = GF(0x2F8) * 1024.0f;
    GF(0x5D0) = GF(0x3B0) * 1024.0f;
    GF(0x5D4) = GF(0x3B4) * 1024.0f;
    *(unsigned char *)(state + 0x4E3) = 1;
    *(unsigned char *)(state + 0x523) = 1;
    *(unsigned char *)(state + 0x563) = 1;
    *(unsigned char *)(state + 0x5A3) = 1;
    GF(0x4EC) = 1.0f;
    GF(0x51C) = 1.0f;
    GF(0x52C) = 1.0f;
    GF(0x55C) = 1.0f;
    GF(0x56C) = 1.0f;
    GF(0x59C) = 1.0f;
    GF(0x5AC) = 1.0f;
    GF(0x5D8) = GF(0x3B8) * 1024.0f;
    GF(0x5DC) = 1.0f;
    *(unsigned char *)(state + 0x5E3) = 1;
    GF(0x610) = GF(0x330) * 1024.0f;
    GF(0x614) = GF(0x334) * 1024.0f;
    GF(0x618) = GF(0x338) * 1024.0f;
    GF(0x650) = GF(0x3F0) * 1024.0f;
    GF(0x654) = GF(0x3F4) * 1024.0f;
    GF(0x658) = GF(0x3F8) * 1024.0f;
    *(unsigned char *)(state + 0x623) = 1;
    GF(0x5EC) = 1.0f;
    GF(0x61C) = 1.0f;
    GF(0x62C) = 1.0f;
    GF(0x65C) = 1.0f;
    GI(0x444) = 300;
    GI(0x440) = 0;
    SetObjectStateField150((int)object, 0xFFFF);
    SetRecordCallbackPointer((int)object, (void *)1);
}

/* Turns the ship's eight parts toward the camera by building a rotation for each joint pair. */
void func_L15_00435838(char *object) {
    float forward[4], up[4], side[4], axis1[4], axis2[4];
    float matrix1[16], matrix2[16], delta[4], temp[4];
    float angle, dot;
    char *state = *(char **)(object + 0x68);
    char *owner = (char *)GetMobyMotionData((unsigned char *)object);
    *(GornQuad *)forward = 0; *(GornQuad *)up = 0; *(GornQuad *)side = 0;
    *(GornQuad *)axis1 = 0; *(GornQuad *)axis2 = 0;
    forward[0] = 1.0f; up[2] = 1.0f; side[1] = 1.0f;
    axis1[2] = 1.0f; axis2[1] = 1.0f;
    if (*(int *)(owner + 0x120) == 0) return;
    matrix_mul_vec3(forward, forward, object + 0xC0);
    matrix_mul_vec3(up, up, object + 0xC0);
    matrix_mul_vec3(side, side, object + 0xC0);
    TransformMobyJointPoint(object, 14, matrix1);
    TransformMobyJointPoint(object, 15, matrix2);
    FastVecSub(delta, D_L15_001B97C0, matrix1 + 12);
    dot = FastVecDot(delta, up);
    FastVecScale(temp, up, dot);
    FastVecSub(delta, delta, temp);
    vec_scale_to_length(delta, delta, 1.0f);
    angle = (1.5707963705062866f - FastAngleHelper(FastVecDot(forward, delta))) * 0.5f;
    if (FastVecDot(delta, side) > 0.0f) angle = -angle;
    FastVecScale(state + 0x4F0, axis1, FastSinOrCosB(angle));
    *(float *)(state + 0x4FC) = FastSinOrCosA(angle);
    FastVecSub(delta, D_L15_001B97C0, matrix2 + 12);
    FastVecScale(temp, up, FastVecDot(delta, up));
    FastVecSub(delta, delta, temp);
    vec_scale_to_length(delta, forward, FastVecLength(delta));
    FastVecAdd(delta, temp, delta);
    vec_scale_to_length(delta, delta, 1.0f);
    dot = FastVecDot(delta, up);
    if (dot <= 0.3142099976539612f) dot = 0.3142099976539612f;
    angle = (1.5707963705062866f - FastAngleHelper(dot)) * 0.5f;
    FastVecScale(state + 0x530, axis2, -FastSinOrCosB(angle));
    *(float *)(state + 0x53C) = FastSinOrCosA(angle);
    TransformMobyJointPoint(object, 16, matrix1);
    TransformMobyJointPoint(object, 17, matrix2);
    FastVecSub(delta, D_L15_001B97C0, matrix1 + 12);
    FastVecScale(temp, side, FastVecDot(delta, side));
    FastVecSub(delta, delta, temp);
    vec_scale_to_length(delta, delta, 1.0f);
    angle = (1.5707963705062866f - FastAngleHelper(FastVecDot(forward, delta))) * 0.5f;
    if (FastVecDot(delta, up) > 0.0f) angle = -angle;
    FastVecScale(state + 0x570, axis2, -FastSinOrCosB(angle));
    *(float *)(state + 0x57C) = FastSinOrCosA(angle);
    FastVecSub(delta, D_L15_001B97C0, matrix2 + 12);
    FastVecScale(temp, side, FastVecDot(delta, side));
    FastVecSub(delta, delta, temp);
    vec_scale_to_length(delta, forward, FastVecLength(delta));
    FastVecAdd(delta, temp, delta);
    vec_scale_to_length(delta, delta, 1.0f);
    dot = FastVecDot(delta, side);
    if (dot <= 0.3142099976539612f) dot = 0.3142099976539612f;
    angle = (1.5707963705062866f - FastAngleHelper(dot)) * 0.5f;
    FastVecScale(state + 0x5B0, axis1, FastSinOrCosB(angle));
    *(float *)(state + 0x5BC) = FastSinOrCosA(angle);
    TransformMobyJointPoint(object, 18, matrix1);
    TransformMobyJointPoint(object, 19, matrix2);
    FastVecScale(side, side, -1.0f);
    FastVecSub(delta, D_L15_001B97C0, matrix1 + 12);
    FastVecScale(temp, side, FastVecDot(delta, side));
    FastVecSub(delta, delta, temp);
    vec_scale_to_length(delta, delta, 1.0f);
    angle = (1.5707963705062866f - FastAngleHelper(FastVecDot(forward, delta))) * 0.5f;
    if (FastVecDot(delta, up) > 0.0f) angle = -angle;
    FastVecScale(state + 0x5F0, axis2, -FastSinOrCosB(angle));
    *(float *)(state + 0x5FC) = FastSinOrCosA(angle);
    FastVecSub(delta, D_L15_001B97C0, matrix2 + 12);
    FastVecScale(temp, side, FastVecDot(delta, side));
    FastVecSub(delta, delta, temp);
    vec_scale_to_length(delta, forward, FastVecLength(delta));
    FastVecAdd(delta, temp, delta);
    vec_scale_to_length(delta, delta, 1.0f);
    dot = FastVecDot(delta, side);
    if (dot <= 0.3142099976539612f) dot = 0.3142099976539612f;
    angle = (1.5707963705062866f - FastAngleHelper(dot)) * 0.5f;
    FastVecScale(state + 0x630, axis1, -FastSinOrCosB(angle));
    *(float *)(state + 0x63C) = FastSinOrCosA(angle);
}


/* func_L15_00435E80 is in L15_00435E80.c. */

/* Puts the object into its falling state with a long timer and full health value. */
void func_L15_00436090(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    *(int *)(vars + 0x270) = 1;
    *(int *)(vars + 0x274) = 0x1E0;
    *(char *)(moby + 0x23) = 0x20;
    *(char *)(moby + 0x20) = 2;
    *(unsigned short *)(moby + 0x34) |= 8;
    *(float *)(vars + 0x180) = 450.0f;
    *(int *)(moby + 0x98) = 0;
}

/* func_L15_004360D8 is in L15_004360D8.c. */

extern int func_002E5CF8(int, int, void *);
extern void func_L05_00379FA0(void *, int, int, float, int, float, float, float,
                              int, int, int);

/* The mover's own state decides whether the shot happens: the level's record
   must exist and be ready, and the mover's own counter must be idle.  The two
   shots take the slots after the counter, and the counter wraps at three. */
void func_L15_00436298(char *moby) {
    char *mover = moby;
    char *vars;
    char *owner;
    int shotIndex;

    vars = *(char **)(mover + 0x68);
    owner = (char *)GetMobyMotionData(moby);
    if (owner == 0) {
        return;
    }
    if (*(int *)(owner + 0x120) == 0) {
        return;
    }
    if (*(int *)(vars + 0x450) != 0) {
        return;
    }
    PlayMobySound(2, 0, mover);
    SpawnSpaceProjectile(mover, 0x600000CF, 1, 1.0f, 0, 2.0f, 1.5f, 1.5f, 0x1E,
                     *(int *)(vars + 0x454) * 2 + 4, 0);
    SpawnSpaceProjectile(mover, 0x600000CF, 1, 1.0f, 0, 2.0f, 1.5f, 1.5f, 0x1E,
                     *(int *)(vars + 0x454) * 2 + 5, 0);
    *(int *)(vars + 0x450) = RandomIntRange(0x14, 0x3C);
    shotIndex = *(int *)(vars + 0x454) + 1;
    *(int *)(vars + 0x454) = shotIndex;
    if (shotIndex >= 3) {
        *(int *)(vars + 0x454) = 0;
    }
}

/* func_L15_004363C8 is in L15_004363C8-g8.c. */

/* Advance through the path points, pausing when an odd encoded action supplies
   a duration in seconds. The path has a 16-byte header and 16-byte points. */
void func_L15_00436990(char *object) {
    char *mover = object;
    char *state = *(char **)(mover + 0x68);

    switch (*(unsigned char *)(mover + 0x20)) {
    case 0:
        *(unsigned char *)(mover + 0x30) = 0xFF;
        if (GetStoredPointerValue() == 0) {
            return;
        }
        InitGornPathMover(mover);
        if (*(int *)(state + 0x264) != 0) {
            AppendLevelObject(mover, (void *)StartPathFollowing, 0, 0);
        }
        DrawPath(mover, *(int *)(state + 0x268), 0x8000FF00, 0x81, 0.75f, 1);
        break;
    case 1: {
        GornPath *path;
        char *owner;
        int index;

        DrawPath(mover, *(int *)(state + 0x268), 0x8000FF00, 0x81, 0.75f, 1);
        owner = (char *)GetMobyMotionData(mover);
        path = (GornPath *)D_L15_001FE480[*(int *)(state + 0x268)];
        if (HasFollowerReachedTarget(mover) != 0) {
            index = *(int *)(state + 0x26C);
            *(int *)(state + 0x26C) = index + 1;
            if (index + 1 == path->count - 1) {
                *(unsigned char *)(mover + 0x20) = 3;
            } else {
                float action = path->points[index].action;

                if (action != -1.0f) {
                    if ((FloatToInt(action) & 1) != 0) {
                        *(int *)(state + 0x274) = (FloatToInt(action) >> 1) * 0x3C;
                        *(unsigned char *)(mover + 0x20) = 2;
                    }
                }
                SetFollowerPushVector(mover, (char *)&path->points[*(int *)(state + 0x26C)]);
                *(int *)(owner + 0x130) = 0x1E8480;
            }
        }
        SetFollowerState(mover, 0xC);
        UpdateObjectMovementState(mover);
        ProcessObjectCollisionHit(mover, 0, 1, 1);
        break;
    }
    case 2:
        if (FastFloatHelperD((int *)(state + 0x274)) != 0) {
            *(unsigned char *)(mover + 0x20) = 1;
        }
        break;
    }
}


/* Sets up the Gorn path mover the first time: health, size and starting path counters. */
void func_L15_00436BA8(char *moby) {
    char *mover = moby;
    char *vars = *(char **)(mover + 0x68);
    char *owner = (char *)GetMobyMotionData((unsigned char *)moby);

    *(int *)(owner + 0x148) = 100;
    InitSpawnedSubObject(mover, 1);
    *(float *)(vars + 0x180) = 100.0f;
    *(unsigned char *)(mover + 0x20) = 1;
    *(unsigned char *)(mover + 0x30) = 0xFF;
    *(unsigned short *)(mover + 0x32) = 0x1FF;
    *(unsigned short *)(mover + 0x34) |= 0x100;
    *(float *)(mover + 0x2C) = 0.20000000298023224f;
    *(float *)(vars + 0x278) = 10.0f;
    *(int *)(vars + 0x26C) = 0;
    *(int *)(vars + 0x270) = 0;
    *(int *)(vars + 0x274) = 0;
    *(int *)(owner + 0x154) = (int)(vars + 0x278);
    SetObjectStateField150((int)mover, 0xFFFF);
}


/* Registers the three scrolling grid draw callbacks for the object. */
void func_L15_00437B18(void *moby) {
    AddDrawCallbackToList2((void *)DrawScrollingGridIfEnabled, moby);
    AddDrawCallbackToList1((void *)UpdateBackdropEffects, moby);
    AddDrawCallbackToList3((void *)DrawBackdropFadeLayers, moby);
}

/* func_L15_00437B68 is in L15_00437B68-g8.c. */

/* func_L15_00438260 is in L15_00438260-g8.c. */

/* func_L15_00438518 is in L15_00438518-g8.c. */

extern int D_L15_001A8FF0[] __attribute__((sda));
extern char D_00189ED0[];
extern int func_002A77E0(int);
extern int func_001163B0(void);
extern void func_002ACEC0(void *, void *, void *, float);
extern unsigned char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
/* Spawns a burst of spinning spark particles at a position. */
void func_L15_00438B00(char *pos, int count, int mode) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    FastVecSub(direction, D_L15_001B97C0, (float *)pos);
    if (D_L15_001A8FF0[0] == 0) {
        direction[2] = 0.0f;
        axis[0] = 0.0f; axis[1] = 0.0f; axis[2] = 1.0f; axis[3] = 1.0f;
    } else {
        FastVecSub(extra, pos, D_00189ED0);
        vec_scale_to_length(axis, extra, 1.0f);
        FastVecScale(extra, axis, FastVecDot(axis, direction));
        FastVecSub(direction, direction, extra);
    }
    for (i = 0; i < count; i++) {
        size = RandomFloatRange(0.75f, 2.0f);
        sign = RandomIntBelow(2);
        if (sign == 0)
            sign--;
        angle = RandomFloatRange(-1.0471977f, 1.0471977f);
        ApplyAxisRotationToQuaternion(velocity, direction, axis, angle);
        speed = RandomFloatRange(0.05f, 3.0f) * (1.0f / 60.0f);
        vec_scale_to_length((char *)velocity, (char *)velocity, speed);
        velocity[2] = RandomFloatRange(1.0f, 5.0f) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += RandomSignedFloatRange(0.0f, 0.15f);
        point[1] += RandomSignedFloatRange(0.0f, 0.15f);
        point[2] += RandomSignedFloatRange(0.0f, 0.15f);
        if (mode == 0) {
            if (!(Rand() & 1)) {
                FastVecScale(velocity, velocity, 1.5f);
                particle = SpawnGroundEffectParticle(point, 60, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = SpawnGroundEffectParticle(point, 60, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
            } else {
                FastVecSub(extra, D_L15_001B97C0, point);
                vec_scale_to_length((char *)extra, (char *)extra, speed);
                FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
                particle = SpawnGroundEffectParticle(point, 40, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = SpawnGroundEffectParticle(point, 40, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
            }
        } else {
            if (!(Rand() & 1)) {
                FastVecScale(velocity, velocity, 1.5f);
                particle = SpawnGroundEffectParticle(point, 60, size * 0.3f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = SpawnGroundEffectParticle(point, 60, size * 0.21000000834465027f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
            } else {
                FastVecSub(extra, D_L15_001B97C0, point);
                vec_scale_to_length((char *)extra, (char *)extra, speed);
                FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
                particle = SpawnGroundEffectParticle(point, 40, size * 0.25f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = SpawnGroundEffectParticle(point, 40, size * 0.175f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
            }
        }
        if (particle)
            particle[9] = FloatToInt(4.0f) + 0x70;
    }
}


/* The level's id lists: the number of groups, the table of the groups' lists (a pointer, read
   through $gp in a branch delay slot and as a bare lui/lw elsewhere: `sda` arrays of unknown size
   give that), the base of the 64-byte records of the first walk, the base of the 32-byte records
   of the second, and the table that maps a record's byte at +0x1D to a class. */
extern int D_L15_001A9018[] __attribute__((sda));
extern unsigned short **D_L15_001A9014[] __attribute__((sda));
extern unsigned char *D_L15_001B2C9C[] __attribute__((sda));
extern unsigned char *D_L15_001B2C94[] __attribute__((sda));
extern short D_L15_00227500[];

extern float func_00282E80(void *, void *);
extern float func_002A7940(void);
extern float func_00283198(float);
extern void func_002AEE70(void *, void *, void *, float, float, float);
extern void func_L00_00323448(void *, void *, int, int, int, int, int, int);
extern void func_L00_00323E48(void *, int, int, void *);
extern void func_L00_00323958(void *, void *);
extern void func_0029F338(void *);
extern void func_002833F0(void *, void *);

/* State 0 looks for the group of the level's id lists that holds the 64-byte record closest to
   the object (first walk, distances below 9999.0; the group index goes to the state's first word
   and the function ends when there is none), sets the object's aim from two random values
   (func_002A7878, func_002A7940) and the record list at state + 0x40, removes the object when the
   state's byte at +0x8A is zero, and otherwise walks the chosen group's 32-byte records
   (second walk): records of class 0xD34 and 0xD33 get their id written into the record list with
   the payload at state + 0x680 and state + 0x6A0 (func_L00_00323E48).  It then picks two random
   angular speeds (the second gets the sign opposite to the first) and goes to state 1, which
   keeps aiming and turns the two angles at +0x688 and +0x6A8.  Both walks keep the second
   `p != 0` guard before the `p[-1]` read and the second walk has a pointer variable of its own
   (one shared variable swaps two callee-saved registers).  Measured: a0 + 0xC0 and a0 + 0xF0
   formed in locals ahead of the second walk make loop.c hoist the two class constants out of it
   (two more saved registers); written at their use after the walk, as below, they stay in the
   loop.  The sign test is a store followed by a conditional store, which gives retail's
   `bc1f` with the first store in its slot and lets the constant 1 be shared by both stores. */
/* Per-frame update of a Gorn moby (class 4729): finds the nearest group, aims at it and spins its parts. */
void func_L15_004390A0(unsigned char *moby)
{
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    unsigned short *p;
    unsigned short *q;
    unsigned char *record;
    int i;
    int bestGroup;
    short cls;
    float bestDistance;
    float distance;
    float turnB;

    switch (moby[0x20]) {
    case 0:
        bestGroup = -1;
        bestDistance = 9999.0f;
        for (i = 0; i < D_L15_001A9018[0]; i++) {
            for (p = D_L15_001A9014[0][i];
                 p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == D_L15_001A9014[0][i]);
                 p++) {
                record = D_L15_001B2C9C[0] + ((*p & 0x7FFF) << 6);
                if (record == 0)
                    break;
                distance = vec_distance_xy(record + 0x30, moby + 0x10);
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestGroup = i;
                }
            }
        }
        *(int *)vars = bestGroup;
        if (bestGroup == -1)
            return;
        *(float *)(vars + 0x28) = 12.0f;
        *(float *)(vars + 0x2C) = RandomFloatRange(30.0f, 37.0f);
        *(float *)(vars + 0x1C) = RandomAngle();
        *(float *)(vars + 0xC) = FastSinOrCosB(*(float *)(vars + 0x1C)) * *(float *)(vars + 0x28);
        UpdateWrappedAngleOffset(moby, vars + 0x1C, vars + 0xC, *(float *)(vars + 0x28),
                      *(float *)(vars + 0x2C) * 0.000290888245f, -1.0f);
        moby[0x30] = 0xFF;
        BuildObjectAttachmentTransforms(moby, vars + 0x40, 20, *(int *)(vars + 4), *(int *)vars,
                          *(int *)(vars + 8), 7, 0);
        if (vars[0x8A] == 0) {
            MarkMobySpawned(moby);
            return;
        }
        for (q = D_L15_001A9014[0][*(int *)vars];
             q != 0 && ((q != 0 && (short)q[-1] >= 0) || q == D_L15_001A9014[0][*(int *)vars]);
             q++) {
            record = D_L15_001B2C94[0] + ((*q & 0x7FFF) << 5);
            if (record == 0)
                break;
            cls = D_L15_00227500[record[0x1D]];
            if (cls == 0xD34 /* moby class 3380 */)
                SetRecordPayloadBySelectorKey(vars + 0x40, 1, (short)*q, vars + 0x680);
            if (cls == 0xD33 /* moby class 3379 */)
                SetRecordPayloadBySelectorKey(vars + 0x40, 1, (short)*q, vars + 0x6A0);
        }
        vars[0x8D] = 1;
        *(unsigned short *)(moby + 0x34) |= 0x104;
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        *(float *)(vars + 0x38) = RandomSignedFloatRange(27.0f, 52.0f) * 0.000290888245f;
        turnB = RandomSignedFloatRange(25.0f, 37.0f) * 0.000290888245f;
        *(float *)(vars + 0x3C) = turnB;
        if (0.0f <= *(float *)(vars + 0x38) * turnB)
            *(float *)(vars + 0x3C) = -turnB;
        moby[0x20] = 1;
        break;
    case 1:
        UpdateWrappedAngleOffset(moby, vars + 0x1C, vars + 0xC, *(float *)(vars + 0x28),
                      *(float *)(vars + 0x2C) * 0.000290888245f, -1.0f);
        *(float *)(vars + 0x688) = FastAddRotations(*(float *)(vars + 0x688), *(float *)(vars + 0x38));
        *(float *)(vars + 0x6A8) = FastAddRotations(*(float *)(vars + 0x6A8), *(float *)(vars + 0x3C));
        UpdateAttachedObjectTransforms(moby, vars + 0x40);
        break;
    }
}
