#include "common.h"
extern u8 *D_L06_001B281C MACRO_ADDR;
extern void func_L00_00429020(int);
extern short D_L06_001B3790[] __attribute__((sda));
extern short D_L06_001B37A0[] __attribute__((sda));
extern char D_L06_0025FFC0[];
extern float func_00283CE0(int);
extern void func_L06_00459020(char *, int, int, int, float, float, float);
extern void func_L06_00459620(char *);


extern float func_00283B98(float, float);
typedef struct NotakChild {
    char pad[0x20];
    unsigned char state;
    char pad21[15];
    unsigned int alpha : 8;
    unsigned int mode : 8;
    unsigned int flags : 16;
} NotakChild;
extern char *func_0029EFD0(int);
extern void func_002A0F48(char *);
extern void func_003514C8(void *, int, void *);

extern void func_002B0A68(char *, int, void *, int, float, float, float, float);
typedef unsigned int NotakQuad __attribute__((mode(TI)));
extern char D_00188660[];
extern char D_00189EA0[];
/* Keep this absolute address as one assembler macro under -G0. */
extern char D_L06_001A8F20[] __attribute__((sda));
extern void func_002A8598(int, int);
extern void func_002E59F8(int);
extern int func_002A7820(int, int);
extern int func_00282948(void *);
extern float func_00282E80(void *, void *);
extern void func_L06_0045C6D0(char *);
extern void *func_0032C700(void *, int, int, int, int, int, int, int,
                            float, float, int, int, int, int);

extern char D_L06_001B9840[];
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern int func_002A77E0(int);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_00283CF0(float);


extern char *D_L06_001B9890[];

extern char *func_00270280(int);

extern float func_002A8A20(char *);

extern int func_00273B70(char *);

extern void func_002A7750(char *, int, int);

extern void func_0029F338(char *);

extern void func_002ABBB8(void *, void *, int, int, int, int, int, int, int, int, int, int,
                          float, float, float, float, float, float, float);

extern void func_002A7A00(float *, float, float);

extern float func_00282C48(float);

extern float func_002A78D8(float, float);

extern float func_002A7878(float, float);

extern char *func_00273730(char *, int, int, int, char *, char *, float *, int, float, float);

extern void func_L06_0045C350(unsigned char *);

extern int func_002A8600(char **, int, int, int);

extern int func_002A86E8(char **, char *, int, int);

extern void func_002A7470(char *, int, int, int);

extern void func_002AA548(char *, char *, float, float, float, float);

extern int func_L04_0033CB08(char *, char *, int, int, float, float);

extern void func_00282D30(char *, char *, float);

extern float func_00282E20(char *);

extern float func_00283C80(float, float);

extern float func_00283180(float);

extern float func_00283198(float);

extern int func_002A9640(char *, int, int);

extern void func_L06_00457C00(char *, int, void *, int, float, float, float, float);

extern void func_002E5CF8(int, int, char *);

extern void func_L00_00326110(char *, int, float);

extern float D_L06_001B234C __attribute__((sda));

extern float D_001B2350 __attribute__((sda));

extern int func_0035CBA0(char *, int, int);

extern void func_L06_0045BE30(char *, int, float, float, float, float);

extern int func_003A0948(int, int, char *);

extern void func_00350388(char *);

extern void func_00283098(void *, void *, void *);
extern double func_001234F0(float);
extern void func_0026FEB8(char *, ...);
extern char D_L06_001B18E0[];
extern void func_L00_003263D0(char *, void *, int, float, int, void *, float, unsigned int, float, float, int);
/* Throws a burst of sparks out from the object, then removes it. */
void func_L06_00458138(char *moby) {
    float pos[4], vel[4];
    int count = 13, i;
    if (D_L06_001B234C < 0.9f && D_001B2350 < 0.9f) count = 40;
    for (i = 0; i < count; i++) {
        pos[0] = RandomFloatRange(-8.045f, 8.045f);
        pos[1] = FloatAbs(pos[0] * 0.1243008077f) * 1.745f;
        pos[2] = RandomFloatRange(0.0f, 3.99f);
        vel[0] = pos[0] * 0.0041433605f;
        vel[1] = -0.13333334f;
        vel[2] = RandomFloatRange(3.0f, 7.0f) * 0.0166666675f;
        matrix_mul_vec3(pos, pos, moby + 0xC0);
        FastVecAdd(pos, pos, moby + 0x10);
        matrix_mul_vec3(vel, vel, moby + 0xC0);
        STUB_printf(D_L06_001B18E0, FloatToDouble(pos[0]), FloatToDouble(pos[1]), FloatToDouble(pos[2]), FloatToDouble(vel[0]), FloatToDouble(vel[1]), FloatToDouble(vel[2]));
        SpawnTintedEffects(moby, pos, 1, 0.0f, 1, vel, 3.0f, 0x50808040, 1.0f, 5.5f, 0);
        func_003A0948(0, 0, moby);
    }
    func_00350388(moby);
}

extern char *func_0029EFD0(int);
extern float func_00283B98(float, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A0F48(char *);

/* Spawns a chained segment from the record at +0x68 and recurses while length remains. */
char *func_L06_004583A8(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *segment = 0;
    char *segmentVars;
    float angle;
    float dirTag;
    float segLength;

    if (*(float *)(vars + 4) > 0.0f) {
        segment = CreateMoby(0xFE2 /* moby class 4066 */);
        if (segment != 0) {
            *(unsigned char *)(segment + 0x31) = 1;
            *(unsigned char *)(segment + 0x30) = 0xFF;
            *(short *)(segment + 0x32) = 0xFF;
            *(unsigned char *)(segment + 0x20) = 1;
            segmentVars = *(char **)(segment + 0x68);
            *(float *)(segment + 0x2C) = *(float *)(moby + 0x2C);
            *(long *)(segment + 0x38) = *(long *)(moby + 0x38);
            *(char **)(segmentVars + 0x10) = moby;
            *(int *)segmentVars = *(int *)vars;
            segLength = *(float *)(vars + 0x1C);
            *(float *)(segmentVars + 0x1C) = segLength;
            *(float *)(segmentVars + 4) = *(float *)(vars + 4) - segLength;
            angle = FastAddRotations(*(float *)(moby + 0xF8), 3.1415927f);
            *(float *)(segmentVars + 8) = angle;
            qcopy(segment + 0xF0, moby + 0xF0);
            *(float *)(segment + 0xF8) = angle;
            dirTag = *(float *)(vars + 0xC);
            if (dirTag == 0.0001f)
                *(float *)(segmentVars + 0xC) = 1.0f;
            else if (dirTag == -0.0001f)
                *(float *)(segmentVars + 0xC) = -1.0f;
            else if (dirTag == 1.0f)
                *(float *)(segmentVars + 0xC) = -0.0001f;
            else if (dirTag == -1.0f)
                *(float *)(segmentVars + 0xC) = 0.0001f;
            TransformMobyJointToWorld(*(char **)(segmentVars + 0x10), 0, segment + 0x10);
            func_002A0F48(segment);
            if (*(float *)(segmentVars + 4) > 0.0f)
                SpawnChainedSegment(segment);
        }
    }
    return segment;
}

/* func_L06_004587E8 is defined in L06_004587E8-axis-g8.c. */


/* Draws every active ribbon trail of the projectile, then its glowing sprite. */
void func_L06_00458F30(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *trail = D_L06_0025FFC0;
    short *alphaTimers = D_L06_001B37A0;
    short *activeTimers = D_L06_001B3790;
    int i;

    for (i = 5; i >= 0; i--) {
        if (*activeTimers != 0) {
            float alphaFloat = IntToFloat(*alphaTimers);
            int alpha = FloatToInt(alphaFloat);

            DrawNotakRibbonWithHalo(trail + *(int *)(vars + 0x48) * 0x180, alpha, alpha, 4, 0.025f, 0.5f, 0.2f);
        }
        trail += 0x40;
        alphaTimers++;
        activeTimers++;
    }
    DrawFacingGlowSprite_L06(moby);
}

/* func_L06_00459020 is defined in L06_00458138-ribbon-g8.c. */

/* func_L06_00459620 is defined in L06_00458138-render-g8.c. */

/* Emits paired particles with opposite spin and randomized velocities. */
void func_L06_00459828(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    FastVecSub(direction, (float *)D_L06_001B9840, pos);
    vec_scale_to_length((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = RandomFloatRange(0.5f, 2.0f);
        sign = RandomIntBelow(2);
        if (!sign) sign--;
        angle = RandomFloatRange(-1.0471977f, 1.0471977f);
        ApplyAxisRotationToQuaternion(velocity, direction, axis, angle);
        vec_scale_to_length((char *)velocity, (char *)velocity, RandomFloatRange(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = RandomFloatRange(1.0f, 5.0f) * 0.0166666675f;
        FastVecAdd(origin, pos, offset);
        pos[0] += RandomSignedFloatRange(0, 0.15f);
        pos[1] += RandomSignedFloatRange(0, 0.15f);
        pos[2] += RandomSignedFloatRange(0, 0.15f);
        particle = SpawnGroundEffectParticle(origin, 60, size * 0.1f, size, 0x7F801010, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
        particle = SpawnGroundEffectParticle(origin, 60, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
    }
}


extern float func_0032D788(void *, void *);

/* Fills in the length of each segment of a closed path of points. */
void func_L06_00459B18(char *path) {
    int count;
    int i;
    float length;

    if (path == 0) {
        return;
    }
    count = *(int *)path;
    i = 0;
    while (i < count) {
        int byteOffset = i * 16;

        length = func_0032D788(path + (byteOffset + 16), path + (((i + 1) % count) * 16 + 0x10));
        *(float *)(path + byteOffset + 0x1C) = length;
        i++;
        count = *(int *)path;
    }
}

/* Works out how much room there is above the object and returns a size class (0, 1 or 2). */
int func_L06_00459BA8(char *moby, char *vars)
{
    float height = GetGroundHeightUnderObject(moby + 0x10);
    float gap;

    *(float *)(vars + 0x120) = height;
    gap = *(float *)(*(char **)(vars + 0x11C)) - height;
    *(float *)(vars + 0x128) = height + gap * 0.5f;
    if (gap < 0.41f) {
        return 2;
    }
    if (0.68f < gap) {
        return 0;
    }
    return 1;
}

/* Starts the animation and state that match the object's size class. */
void func_L06_00459C38(unsigned char *moby)
{
    switch (moby[0xBC]) {
    case 0:
        if (moby[0x43] != 0) {
            StartAnimationBlended((char *)moby, 0, 0, 0xA);
        }
        moby[0x20] = 1;
        break;
    case 1:
        if (moby[0x43] != 3) {
            StartAnimationBlended((char *)moby, 3, 0, 0xA);
        }
        moby[0x20] = 7;
        break;
    case 2:
        if (moby[0x43] != 9) {
            StartAnimationBlended((char *)moby, 9, 0, 0xA);
        }
        moby[0x20] = 0xF;
        break;
    }
}

/* func_L06_00459D08 is defined in L06_00458138-g8.c. */

extern int func_002A8AF0(void *, void *, int);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00277258(void *, int, void *, float);
extern float func_00283248(float, float);

/* Sweeps for a free heading when a sweep is pending, else (or when none is free) faces the
   target. The found block before the sweep is what puts the flag test's fallback on its own
   branch: its store goes into the sweep's branch-likely slot, leaving that branch behind. */
void func_L06_00459EC0(char *obj, char *st)
{
    float dir[3];
    char *p;
    float ang;
    float step;
    float total;

    if (*(int *)(st + 0x124) != 0)
        goto search;
    goto fallback;
found:
    *(float *)(st + 0x12C) = ang;
    return;
search:
    dir[0] = FastSinOrCosA(*(float *)(obj + 0xF8)) * 5.2f;
    dir[1] = FastSinOrCosB(*(float *)(obj + 0xF8)) * 5.2f;
    dir[2] = 0.0f;
    FastVecAdd(dir, dir, obj + 0x10);
    p = *(char **)(st + 0x118);
    if (point_in_path_xy(dir, p + 0x10, *(int *)p) != 0 &&
        CollLine(obj + 0x10, dir, 0x24, obj, 0) == 0 &&
        TestPointAgainstCollision(dir, 0x24, obj, 1.5f) == 0)
        return;
    step = FloatAbs(*(float *)(st + 0x130));
    ang = *(float *)(obj + 0xF8);
    total = 0.0f;
    do {
        ang = FastAddRotations(ang, *(float *)(st + 0x130));
        dir[0] = FastSinOrCosA(ang) * 5.2f;
        dir[1] = FastSinOrCosB(ang) * 5.2f;
        dir[2] = 0.0f;
        FastVecAdd(dir, dir, obj + 0x10);
        p = *(char **)(st + 0x118);
        if (point_in_path_xy(dir, p + 0x10, *(int *)p) == 0 ||
            CollLine(obj + 0x10, dir, 0x24, obj, 0) != 0 ||
            TestPointAgainstCollision(dir, 0x24, obj, 1.5f) != 0) {
            total += step;
            continue;
        }
        goto found;
    } while (total < 6.283186f);
fallback:
    *(float *)(st + 0x12C) = FastMatrixHelperA(*(float *)(st + 0xE0) - *(float *)(obj + 0x10),
                                         *(float *)(st + 0xE4) - *(float *)(obj + 0x14));
}

/* Moves the object using its stored speed, pulls it down when it is high, and slows it after a bump. */
void func_L06_0045A0D0(char *moby, char *vars, float f, float g, float h)
{
    char position[16];
    char *varsAlias = vars;

    if (*(float *)(*(char **)(vars + 0x11C)) - 0.3f < *(float *)(moby + 0x18)) {
        *(float *)(vars + 0xC8) -= 0.163333335f;
    }
    qcopy(position, moby + 0x10);
    StepValueTowardTarget(position + 8, varsAlias + 0xC8, *(float *)(varsAlias + 0x128), f, g, h);
    if (BlendWithScaledCount(moby, varsAlias + 0xC0, 0x400, 0x10, 1.0f, 0.0f) != 0) {
        FastVecScale(varsAlias + 0xC0, varsAlias + 0xC0, 0.5f);
    }
}

/* Speeds up or slows down the object depending on how closely it faces a direction; returns 1 when speeding up. */
int func_L06_0045A1B0(char *moby, char *vars, float p1, float p2, float p3, float p4, float p5,
                      float p6, float p7)
{
    float speed = vec_length_xy(vars + 0xC0);
    float angleDiff = FastDiffRots(*(float *)(moby + 0xF8), p1);
    int speedingUp = 0;

    if (angleDiff < p2) {
        speed += p3;
        speedingUp = 1;
    } else if (p4 < angleDiff) {
        speed -= p5;
    }
    if (p6 < speed) {
        speed = p6;
    } else if (speed < p7) {
        speed = p7;
    }
    *(float *)(vars + 0xC0) = FastSinOrCosA(*(float *)(moby + 0xF8)) * speed;
    *(float *)(vars + 0xC4) = FastSinOrCosB(*(float *)(moby + 0xF8)) * speed;
    return speedingUp;
}

extern float func_0029F530(char *);
extern void func_002A8C00(void *, char *, int, void *, float);
extern int func_00277F48(void *, float, int, char *, void *);
extern void *D_L06_001BFC98;

/* Runs the shared pickup test: when the object is in the given state and the draw is inside the window, aims at the target and, on a hit with the expected tag, hands over to the next state. */
void func_L06_0045A2D8(char *obj, float lo, char *self, float hi, int kind, int sub, float scale, float reach, float range,
                       int anim, int link, int next, void *tag)
{
    float dir[4] __attribute__((aligned(16)));
    char aim[0x30] __attribute__((aligned(16)));
    float probe[4] __attribute__((aligned(16)));
    float roll = GetMobyAnimationValue(obj);
    char *vec;

    if (*(u8 *)(obj + 0x20) == kind && *(u8 *)(obj + 0x42) == sub && lo < roll && roll < hi) {
        vec = self + 0xC0;
        vec_scale_to_length((char *)dir, vec, scale);
        dir[2] = 1.0f;
        make_hit_descriptor(aim, obj, 1, dir, reach);
        func_003514C8(obj, 0, probe);
        if (ProcessCollisionHit(probe, range, 0x21, obj, aim) != 0 && D_L06_001BFC98 == tag) {
            FastVecScale(vec, vec, -1.0f);
            *(float *)(self + 0xC8) = -0.05f;
            if (*(u8 *)(obj + 0x43) != anim)
                StartAnimationBlended(obj, anim, link, 5);
            *(u8 *)(obj + 0x20) = next;
        }
    }
}

extern void func_003514C8(void *, int, void *);

extern int func_0031EBF8(f32, void *, int, void *);

extern void *D_L06_001BFC98;

/* Checks whether a short probe from the object hits the given thing; returns 1 if it does. */
int func_L06_0045A490(void *moby, void *expected, f32 reach) {
    char probe[16];
    int hitResult;

    func_003514C8(moby, 0, probe);
    hitResult = func_0031EBF8(reach, probe, 0x21, moby);
    if (hitResult != 0) {
        if (D_L06_001BFC98 == expected) {
            return 1;
        }
    }
    return 0;
}

/* Returns 1 if another object of the same group is in a state between the two given values. */
int func_L06_0045A500(char *moby, int minState, int maxState)
{
    char *found = 0;

    if (GetFirstMobyInGroup(&found, *(unsigned char *)(moby + 0x21), 0, 0) != 0) {
        return 0;
    }
    while (found != 0) {
        if (found != moby) {
            int otherState = *(unsigned char *)(found + 0x20);

            if (otherState >= minState) {
                if (otherState <= maxState) {
                    return 1;
                }
            }
        }
        if (GetNextMobyInGroup(&found, found, 0, 0) != 0) {
            return 0;
        }
    }
    return 0;
}

/* When hit, bursts into a spray of pieces and removes itself. */
void func_L06_0045BD38(char *moby)
{
    char *hit;
    int count;

    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(unsigned char *)(moby + 0x20) = 1;
        *(unsigned short *)(moby + 0x34) |= 0x800;
    }

    hit = (char *)func_0035CBA0(moby, 0x4010000, 0);
    if (hit != 0 && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5 /* moby class 4069 */) {
        count = 3;
        if (D_L06_001B234C < 0.8999999761581421f && D_001B2350 < 0.8999999761581421f)
            count = 0xE;

        func_L06_0045BE30(moby, count, 0.0f, 3.263000011444092f, 1.9739999771118164f,
                          0.11666667461395264f);
        func_003A0948(0, 0, moby);
        func_00350388(moby);
    } else {
        *(unsigned char *)(moby + 0xA8) = 0xFF;
    }
}

/* Waits until hit, then bursts into fragments and removes itself. */
void func_L06_0045BFC0(unsigned char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        *(unsigned short *)(moby + 0x34) |= 0x800;
        SetMobyState((char *)moby, 1, -1);
        break;
    case 1:
        if (FindOwnedEffectSlot((char *)moby, 0x4010000, 0) != 0) {
            if (*(int *)vars == 0) {
                SetMobyState((char *)moby, 2, -1);
            }
        }
        moby[0xA8] = 0xFF;
        break;
    case 2: {
        char offset[16];

        FastVecScale(offset, (char *)(moby + 0xD0), -0.033333335f);
        SpawnDebrisParticles((char *)moby, 3, offset, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        PlayMobySound(0, 0, (char *)moby);
        SpawnScaledBolts((char *)moby, 1, 0.0f);
        MarkMobySpawned((char *)moby);
        break;
    }
    }
}

/* Looks up the object bound to the given flags; unless the hit object's own field says
   0xFE5, it starts a smoke emitter, spawns one particle with the level's own callback
   and six more in a loop, then clears the object's byte at 0xA8. */
void func_L06_0045C0F0(char *moby)
{
    char *hit;
    char *piece;
    float velocity[3];
    int i;

    hit = (char *)FindOwnedEffectSlot(moby, 0x4010001, 0);
    if (hit != 0 && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5 /* moby class 4069 */) {
        PlayMobySound(0, 0, moby);
        SpawnExplosionEffects(moby, moby + 0x10, 0, 10, 3, 9, -1, 1, 1, -1, 0, 0x810001,
                      0.0f, 0.0f, 4.0f, 2.0f, 9.0f, 0.0f, 15.0f);
        RandomDirectionVector(velocity, 0.0333333350718021392822265625f, 0.066666670143604278564453125f);
        velocity[2] = FloatAbs(velocity[2]);
        piece = CreateCameraMoby(moby, 1, *(short *)(moby + 0xAA), 6, moby + 0x10, moby + 0xF0,
                          velocity, 1, RandomSignedFloatRange(20.0f, 45.0f), 15.0f);
        if (piece != 0) {
            *(void (**)(void))(piece + 0x64) = (void (*)(void))UpdateFlyingFragmentMoby;
        }
        for (i = 0; i < 6; i++) {
            RandomDirectionVector(velocity, 0.10000000894069671630859375f, 0.2000000178813934326171875f);
            velocity[2] = FloatAbs(velocity[2]);
            CreateCameraMoby(moby, 2, *(short *)(moby + 0xAA), i, moby + 0x10, moby + 0xF0,
                          velocity, 0xFF, RandomSignedFloatRange(20.0f, 45.0f),
                          RandomFloatRange(15.0f, 25.0f));
        }
        PlayMobySound(1, 0, moby);
        SpawnScaledBolts(moby, 1, 0.0f);
        MarkMobySpawned(moby);
    }
    *(unsigned char *)(moby + 0xA8) = 0xFF;
}

/* Updates a flying fragment: it flies until it lands, then fades out and disappears. */
void func_L06_0045C350(unsigned char *moby)
{
    switch (moby[0x20]) {
    case 0:
        if (UpdateCameraMoby((char *)moby) != 0) {
            SetMobyState((char *)moby, 1, -1);
            *(unsigned short *)(moby + 0x34) |= 0x2800;
        }
        break;
    case 1:
        UpdateCameraMoby((char *)moby);
        if (moby[0x23] < 2) {
            MarkMobySpawned((char *)moby);
        } else {
            moby[0x23] -= 2;
        }
        break;
    }
}

/* Updates an emitter that rests, then spits particles while the hero is near, and bursts when hit. */
void func_L06_0045C3E8(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *hit;
    float pos[4];
    *(unsigned char *)(moby + 0x23) = 0x80;
    if (!vars) {
        return;
    }
    hit = (char *)func_0035CBA0(moby, 0x4010000, 0);
    if (hit && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5 /* moby class 4069 */) {
        if (*(unsigned char *)(moby + 0x20) == 1) {
            SetByteOnGroupMobys(*(unsigned char *)(moby + 0x21), 0);
        }
        func_003A0948(1, 0, moby);
        *(NotakQuad *)pos = 0;
        pos[2] = 1.0f;
        FastVecAdd(pos, pos, moby + 0x10);
        SpawnExplosion(pos, 1, 25, 20, 20, 20, 45, 1, 1.25f, 20.0f, 1, 1, 0, 0);
        SpawnDebrisForMaskedParts(moby, 0x7F, D_L06_001A8F20, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        SpawnScaledBolts(moby, 1, 0.0f);
        func_00350388(moby);
    }
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned char *)(moby + 0x23) = 0x80;
        *(int *)vars = RandomIntRange(40, 250);
        moby[0x20] = 2;
        *(int *)(vars + 8) = -1;
        break;
    case 1:
        if (vec_distance_xy(moby + 0x10, gHeroPosition) < 32.0f) {
            EmitFacingParticles(moby);
        }
        if (FastFloatHelperD(vars + 4)) {
            *(int *)vars = RandomIntRange(200, 250);
            if (*(int *)(vars + 8) != -1) {
                char *sound = gSoundState + *(int *)(vars + 8) * 0x70;
                if (*(char **)(sound + 0x88) == moby && *(unsigned char *)(sound + 0x74)) {
                    StopSoundVoice(*(int *)(vars + 8));
                }
            }
            *(int *)(vars + 8) = -1;
            moby[0x20] = 2;
            SetByteOnGroupMobys(*(unsigned char *)(moby + 0x21), 0);
        }
        break;
    case 2:
        if (FastFloatHelperD(vars) && *(unsigned char *)(moby + 0xBC) == 0) {
            char *sound;
            *(int *)(vars + 4) = RandomIntRange(200, 250);
            sound = gSoundState + *(int *)(vars + 8) * 0x70;
            if (*(char **)(sound + 0x88) != moby || !*(unsigned char *)(sound + 0x74)) {
                *(int *)(vars + 8) = func_003A0948(0, 4, moby);
            }
            moby[0x20] = 1;
            SetByteOnGroupMobys(*(unsigned char *)(moby + 0x21), 1);
        }
        break;
    }
    *(unsigned char *)(moby + 0xA8) = 0xFF;
}

/* func_L06_004621C8 is defined in L06_00458138-effect-g8.c. */

/* Waits for a linked object to reach state 2, then fires a trigger and follows that object's state. */
void func_L06_00464900(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned char *)(moby + 0x30) = 0xFF;
        *(unsigned char *)(moby + 0x20) = 1;
        break;
    case 1: {
        int i = *(int *)(vars + 4);
        char *base = (char *)D_L06_001B281C;
        char *p = (char *)(base + (i << 8));
        int t = *(unsigned char *)(p + 0x20);
        int j;
        char *q;

        if (t != 2) {
            break;
        }
        j = *(int *)(vars + 8);
        q = (char *)(base + (j << 8));
        if (q == 0) {
            break;
        }
        if (*(unsigned char *)(q + 0x20) == 0xFE) {
            break;
        }
        if (*(unsigned char *)(q + 0x20) == 0xFD) {
            break;
        }
        LockCameraEntry(*(int *)vars);
        *(unsigned char *)(moby + 0x20) = t;
        break;
    }
    case 2: {
        int i = *(int *)(vars + 4);
        char *p = (char *)(D_L06_001B281C + (i << 8));

        if (*(unsigned char *)(p + 0x20) != 2) {
            *(unsigned char *)(moby + 0x20) = 1;
        }
        break;
    }
    }
}

/* func_L06_004649F0 is defined in L06_004649F0-g8.c. */

/* func_L06_00464F40 is defined in L06_00464F40-g8.c. */


/* Stores two values in the settings block of the object of kind 5, finding that object first if needed. */
void func_L06_00478548(float valueA, float valueB)
{
    char *first = D_L06_001B9890[0];
    char *target;
    char *settings;

    if (*(short *)(first + 0x86) != 5) {
        target = FindRecordByHandleId(5);
    } else {
        target = first;
    }
    settings = *(char **)(target + 0x70) + 0xE0;
    *(float *)(settings + 0x44) = valueA;
    *(float *)(settings + 0x48) = valueB;
}

