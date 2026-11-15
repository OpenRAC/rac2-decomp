#include "common.h"

typedef int Q __attribute__((mode(TI)));
typedef union {
    Q q;
    float f[4];
} Vector;
extern int D_L20_001A8F00, D_L20_001B2AC8;
extern int D_L20_001BDCF0[];
typedef struct {
    char pad[0x80];
    float pos[4];
} Hero;
extern Hero D_00189E20;
extern char D_00189EA0[];
extern float D_L20_001B1FE0 __attribute__((sda));
extern float D_L20_001B1FE4 __attribute__((sda));
extern float D_L20_001B1FE8 __attribute__((sda));
extern float D_L20_001B1FF0 __attribute__((sda));
extern float D_L20_001B1FF8 __attribute__((sda));
extern float D_L20_001B1FFC __attribute__((sda));
extern float D_L20_001B2000 __attribute__((sda));
extern float D_L20_001B2004 __attribute__((sda));
extern float D_L20_001B1FF4;
extern Vector D_L20_001B2010 SDATA(D_L20_001B2010);
extern void func_L20_0043FC70(char *), func_0029F338(char *);
extern int func_002B3890(char *), func_002A77E0(int), func_002B1C20(char *, void *);
extern void func_002A6C58(char *, int, int), func_L01_003E9CF8(char *, int, void (*)(char *));
extern void func_L20_00440460(char *), func_002A7750(char *, int, int);
extern int func_002B3868(char *);
extern void func_002A7470(char *, int, int, int);
extern float func_00282E80(void *, void *);
extern void func_002B4FF0(char *, void *, float);
extern int func_L20_0043FFF0(char *);
extern float func_0029F530(char *);
extern void func_L01_00321178(char *, void *);
extern float func_00283248(float, float);
extern void func_L01_00322288(char *, float);
extern int func_002AEB60(char *, float);
extern void func_00283098(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_002A8C28(void *, void *, int, int, float, float, float, int, int);
extern void func_00273B70(char *), func_002833F0(void *, void *);
extern float func_00282E20(void *);
extern void func_002AA2E8(void *, float, float), func_00282F70(void *, void *, float);
extern float func_002A89A8(void *, int, float);
extern void func_L20_00440150(char *);

/* Runs the small Yeedil enemy each frame (moby class 4510). It circles the hero, chases, shoots when lined up, and falls over when it is hurt. */
void func_L20_0043F570(char *obj) {
    Vector v;
    Q matrix[3];
    float length;
    char *st = *(char **)(obj + 0x68);
    int hit;

    InitEnemyAndHandleDamage4510(obj);
    if (D_L20_001A8F00 == 2) {
        if (D_L20_001BDCF0[0] >= 5) MarkMobySpawned(obj);
        return;
    }
    switch (*(u8 *)(obj + 0x95)) {
    case 0:
        break;
    case 1:
        if (SetSecondPendingFlag(obj)) *(int *)(st + 0x284) = RandomIntBelow(2);
        break;
    case 2:
        hit = DispatchActionByKind(obj, st + 0x140);
        if (hit & 1) {
            *(int *)(st + 0x280) = 0;
            SetDeathBits(obj, 0, 3);
            QueueMobyForGlowEffect(obj, 0, EnterMobyStateSix);
        } else if (hit & 2) SetMobyState(obj, 3, 1);
        break;
    }
    switch (*(u8 *)(obj + 0x20)) {
    case 2: {
        float distance;
        if (SetFirstPendingFlag(obj)) {
            if (*(u8 *)(obj + 0x43) != 2) StartAnimationBlended(obj, 2, 0, 20);
            *(float *)(st + 0x78) = D_L20_001B1FE0 * 0.0166666675f;
            *(float *)(st + 0x288) = 1.0471977f;
        }
        distance = vec_distance_xy(obj + 0x10, gHeroPosition);
        if (distance < D_L20_001B1FF0) *(float *)(st + 0x288) = 2.0943954f;
        else if (D_L20_001B1FF4 < distance) *(float *)(st + 0x288) = 1.0471977f;
        if (*(int *)(st + 0xD0) == 60) {
            *(int *)(st + 0xD0) = 0;
            *(int *)(st + 0x284) = (*(int *)(st + 0x284) + 1) & 1;
        }
        TurnTowardTargetAndStepMovement(obj, gHeroPosition, *(int *)(st + 0x284) ? *(float *)(st + 0x288) : - *(float *)(st + 0x288));
        if ((D_L20_001B2AC8 & 15) == (((int)obj >> 8) & 15) && CanEnemyStartAttack(obj)) {
            *(int *)(st + 0x280) = 1;
            SetMobyState(obj, 3, -1);
        }
        break;
    }
    case 3:
        if (SetFirstPendingFlag(obj)) {
            if (*(u8 *)(obj + 0x43) != 2) StartAnimationBlended(obj, 2, 0, 10);
            *(float *)(st + 0x78) = D_L20_001B1FE4 * 0.0166666675f;
        }
        TurnTowardTargetAndStepMovement(obj, gHeroPosition, 0.0f);
        if (*(float *)(st + 0x11C) < D_L20_001B1FF8) SetMobyState(obj, 4, -1);
        break;
    case 4: {
        float distance;
        if (SetFirstPendingFlag(obj)) {
            if (*(u8 *)(obj + 0x43) != 4) StartAnimationBlended(obj, 4, (int)D_L20_001B1FFC, 10);
        }
        distance = GetMobyAnimationValue(obj);
        if (*(u8 *)(obj + 0x42) == *(u8 *)(obj + 0x43) && distance >= 9.0f && distance <= 17.0f) {
            float accel = D_L20_001B2004 * 0.00027777778f;
            float speed = D_L20_001B2000 * 0.0166666675f;
            *(float *)(st + 0x74) = accel;
            *(float *)(st + 0x78) = speed;
            *(float *)(st + 0x70) = accel;
            TurnMobyTowardTarget(obj, gHeroPosition);
        } else {
            StartMobyEffectFromEntry(obj, FastMatrixHelperA(
                gHeroState.pos[0] - *(float *)(obj + 0x10),
                gHeroState.pos[1] - *(float *)(obj + 0x14)));
        }
        {
            float accel = D_L20_001B1FE8 * 0.00027777778f;
            float speed = D_L20_001B1FE4 * 0.0166666675f;
            *(float *)(st + 0x74) = accel;
            *(float *)(st + 0x78) = speed;
            *(float *)(st + 0x70) = accel;
        }
        if (*(u8 *)(obj + 0x42) == *(u8 *)(obj + 0x43) && IsValueWithinStepOfThreshold(obj, 14.0f)) {
            matrix_mul_vec3(&v, &D_L20_001B2010, obj + 0xC0);
            FastVecAdd(&v, &v, obj + 0x10);
            SweepCollisionFromObject(obj, &v, 0x04000001, 0, 0.333f, 2.0f, 1.0f, 1, 0);
        }
        if ((*(u8 *)(obj + 0x60) & 2) && vec_distance_xy(obj + 0x10, gHeroPosition) > D_L20_001B1FF8) SetMobyState(obj, 3, -1);
        break;
    }
    case 7:
        *(char **)(obj + 0x68) = st + 0x210;
        UpdateCameraMoby(obj);
        *(char **)(obj + 0x68) = st;
        SweepCollisionFromObject(obj, obj + 0x10, 0x04000000, 0, 0.5f, 5.0f, 1.0f, 1, 0);
        qzero_nc(&v);
        v.f[2] = *(float *)(st + 0x288) * 0.0166666675f;
        euler_rotation_basis(matrix, &v);
        matrix_mul_vec3(st + 0x210, st + 0x210, matrix);
        length = vec_length_xy(st + 0x210);
        if (length < 0.0500000045f) {
            ApproachValue(&length, 0.0f, 0.0027777778f);
            if (length <= 0.0f) SetMobyState(obj, 1, 1);
            else FastVectorNormalizeHelper(st + 0x210, st + 0x210, length);
        }
        if (*(float *)(obj + 0x18) < *(float *)(st + 0x180)) {
            *(int *)(obj + 0x98) = 0;
            *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) | 0x41) & 0xEFFF;
            SetMobyState(obj, 6, -1);
        }
        break;
    case 1:
        if (SetFirstPendingFlag(obj)) {
            char *data = *(char **)(obj + 0x24);
            int flags = *(int *)(data + 0x10);
            *(int *)(obj + 0x9C) = 2;
            *(int *)(obj + 0x98) = flags;
            *(u16 *)(obj + 0x34) = *(u16 *)(data + 0x44) | 0x1000;
            matrix_mul_vec3(&v, st + 0x230, obj + 0xC0);
            FastVecAdd(obj + 0x10, &v, obj + 0x10);
            *(float *)(obj + 0x18) = ProbeGroundHeightBelow(obj + 0x10, 0, 0.5f);
            qzero(obj + 0xF0);
            *(float *)(obj + 0xF8) = FastMatrixHelperA(
                gHeroState.pos[0] - *(float *)(obj + 0x10),
                gHeroState.pos[1] - *(float *)(obj + 0x14));
            if (*(u8 *)(obj + 0x43) != 3) StartAnimationBlended(obj, 3, 0, 5);
        }
        if (*(u8 *)(obj + 0x60) & 2) SetMobyState(obj, 2, 1);
        break;
    case 5:
    case 6:
        break;
    }
    AdvanceMobyFrameCounter(obj);
}

extern float D_L20_001B2BE8;
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern char *func_002A9640(char *, int, int);
extern float func_002A96A0(char *, char *);
extern void func_00282CF0(void *, void *, void *);
extern int func_002B0ED8(char *, char *, int);
extern int func_002B3BA8(char *, int, void *, int, float, float);

/* Sets up the small enemy when it first appears. Each frame it also handles being hit, dying, and remembering the hero position. */
void func_L20_0043FC70(char *obj) {
    char *st = *(char **)(obj + 0x68);
    Vector a;
    Vector b;

    if (*(unsigned char *)(obj + 0x20) == 0) {
        *(float *)(st + 0x170) = 0.5f;
        *(unsigned char *)(st + 0x150) = 5;
        *(int *)(st + 0x188) = 2;
        *(float *)(st + 0x174) = 0.6f;
        *(float *)(st + 0x17C) = 0.15f;
        *(float *)(st + 0x84) = 0.05f;
        *(float *)(st + 0x54) = 0.3f;
        *(float *)(st + 0x50) = 0.5f;
        *(float *)(st + 0x58) = 0.4f;
        *(float *)(st + 0x5C) = 2.0f;
        *(float *)(st + 0x60) = 1.57079649f;
        *(float *)(st + 0x80) = 0.785398245f;
        {
            float angle = RandomSignedFloatRange(18.0f, 22.0f) * 0.0174532942f;
            float speed = D_L20_001B1FE4 * 0.0166666675f;
            float accel = D_L20_001B1FE8 * 0.00027777778f;

            *(short *)(st + 0x132) = 0x78;
            *(short *)(st + 0x134) = 0xB4;
            *(float *)(st + 0x12C) = angle;
            *(float *)(st + 0x78) = speed;
            *(float *)(st + 0x70) = accel;
            *(float *)(st + 0x74) = accel;
        }
        *(int *)(st + 0x88) |= 0x200;
        *(unsigned char *)(st + 0x48) = FloatToInt(8.0f);
        *(unsigned char *)(st + 0x4A) = FloatToInt(12.0f);
        *(unsigned char *)(st + 0x29) = 1;
        if (*(short *)(st + 0x24) == 0) {
            *(short *)(st + 0x24) = 3;
            *(float *)(st + 0x20) = 3.0f;
        }
        *(int *)(obj + 0x98) = 0;
        *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) | 0x41) & 0xEFFF;
        SetMobyState(obj, 6, 3);
        if (*(unsigned char *)(obj + 0x43) != 0) {
            StartAnimationBlended(obj, 0, 0, 0);
        }
    }

    *(float *)(st + 0x180) = D_L20_001B2BE8;
    if (*(unsigned char *)(obj + 0x20) == 6) {
        return;
    }
    if (*(unsigned char *)(st + 0x2E) == 2) {
        *(int *)(obj + 0x98) = 0;
        *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) | 0x41) & 0xEFFF;
        SetMobyState(obj, 6, 3);
    }
    *(unsigned char *)(st + 0x2E) = 1;

    if (*(unsigned char *)(obj + 0x20) == 7 && *(float *)(st + 0x20) > 0.0f) {
        char *hit = FindOwnedEffectSlot(obj, 0x10000, 0);
        float damage = UpdateAimTargetStrength(obj, hit);

        ApproachValue(st + 0x20, 0.0f, damage);
        *(unsigned char *)(obj + 0xA8) = 0xFF;
        if (*(float *)(st + 0x20) <= 0.0f) {
            *(float *)(obj + 0xF4) = 0.0f;
            *(float *)(obj + 0xF0) = 0.0f;
            matrix_mul_vec3(&a, st + 0x230, obj + 0xC0);
            euler_rotation_basis(obj + 0xC0, obj + 0xF0);
            matrix_mul_vec3(&b, st + 0x230, obj + 0xC0);
            FastVecSub(&b, &b, &a);
            FastVecSub(obj + 0x10, obj + 0x10, &b);
        }
    } else {
        ApplyDamageToObject(obj, st + 0x140, 0);
    }
    SelectAimTarget_002B3BA8(obj, *(int *)(st + 0x270), 0, 0, 64.0f, 0.0f);

    if (*(int *)(st + 0x204) == 0) {
        char *g = (char *)&gHeroState;

        *(char **)(st + 0x200) = *(char **)(g + 0x2290);
        qcopy(st + 0x1F0, *(char **)(g + 0x2290) + 0x10);
        *(int *)(st + 0x204) = 1;
    }
}

extern int D_L20_001B2020 __attribute__((sda));
extern int D_L20_001B2FB8 __attribute__((sda));
extern unsigned short *D_L20_001FBB20[];
extern char *D_L20_001B2F9C;

/* Returns 0 when D_L20_001B2020 or more other objects of this object's group (the
   0x7FFF-masked id list at D_L20_001FBB20[obj[0x21]]) are busy (state +0x280) or are
   closer to D_00189EA0 than it; 1 otherwise.  The loop is the group-iteration form used
   by func_00325DA0. */
/* Decides whether this enemy may start attacking. It says no if too many others in its group are already attacking or are closer to the hero. */
int func_L20_0043FFF0(char *obj) {
    float dist;
    int closer = 0;
    int busy = 0;
    unsigned short *p;
    char *e;

    dist = vec_distance_xy(obj + 0x10, gHeroPosition);
    for (p = D_L20_001FBB20[*(u8 *)(obj + 0x21)];
         *(u8 *)(obj + 0x21) != 0xFF && *(u8 *)(obj + 0x21) <= D_L20_001B2FB8 && p != 0 &&
         ((p != 0 && (short)p[-1] >= 0) || p == D_L20_001FBB20[*(u8 *)(obj + 0x21)]);
         p++) {
        e = D_L20_001B2F9C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e != obj && *(u8 *)(e + 0x20) != 6) {
            if (*(int *)(*(char **)(e + 0x68) + 0x280) != 0)
                busy++;
            if (busy >= D_L20_001B2020)
                return 0;
            if (dist > vec_distance_xy(e + 0x10, gHeroPosition))
                closer++;
            if (closer >= D_L20_001B2020)
                return 0;
        }
    }
    return 1;
}
