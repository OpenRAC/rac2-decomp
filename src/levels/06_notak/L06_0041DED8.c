#include "include_asm.h"
#include "common.h"

extern short *D_L06_001FB3A0[];
extern char *D_L06_001B281C[] __attribute__((sda));
extern float func_35A780(void);
extern void func_458138(char *);

extern int func_00282948(char *);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern void func_002AB8C0(char *, char *);
extern int func_002A7820(int, int);
/* EE argument banks preserve position/count/velocity/color/flags and four floats. */
extern char *func_002BDCE8(char *, float, float, float, int, char *, float, unsigned int, int);

extern char D_L06_002AA500[];

extern void func_32D268(char *);
extern void func_366160(char *, char *, float, int, int);
extern void func_36C158();
extern void func_36C1B0(float);
extern void func_3BFBB8(char *, int);

extern char D_L06_00189EA0[];
extern char D_L06_001B13B0[];
extern char D_L06_001B13F0[];
extern char D_L06_001B1330[];
extern char D_L06_001B1370[];
extern char D_L06_001395CE;
extern char D_L06_001395CF;
extern char D_L06_001395D0;

/* The two flags the re-arm sets, at 0x001395B8. */
typedef struct {
    char pad_000[0x13];
    char flag_013;
    char flag_014;
} L06ArmFlags;

extern L06ArmFlags D_L06_001395B8;

extern int func_333898(void);
extern void func_2E3EF0(char *);
extern int func_360F58(char *, int);
extern void func_35A550(char *, int, int);
extern void func_35B810(int, int);
extern int func_35CBA0(char *, int, int);
extern int func_3A0948(int, int, char *);
extern void func_3661E0(char *, int, float);
extern void func_350388(char *);
extern void func_32D650(char *, char *, float);
/* Throws out a set of small debris particles around the object, one for each bit set in the mask. */
extern void func_L06_00457C00(char *, int, void *, int, float, float, float, float);
extern void func_32D5F8(char *, char *, char *);
extern void func_365030(char *, char *, char *, int);
extern float func_32DC80(float, float);
extern float func_32D740(char *);
extern void func_32D5C8(char *, char *, char *);
extern int func_32E728(float);
extern void func_352000(char *, int, int, int);
extern void func_32D8A8(char *, char *, float);
extern void func_00310C88();
extern int D_L06_001B375C __attribute__((sda));
extern int D_L06_001B3758 __attribute__((sda));
extern void func_L06_003DDCA8();
extern int func_32D238(char *);
extern int func_35A620(int);
extern void func_35A270(char *, int, int, int);
extern void *D_L06_002E1F00[];
extern char *func_31B0D0(char *, int, int, int, float, float, char *, char *, char *,
                         int);
extern char D_L06_001A8F20[];
/* Pushes the moby away and starts its tumbling fall with a burst of effects. */
extern void func_L06_004579C8(char *);

extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(float *, float *, float *);
extern float func_00282DF0(float *);
extern void func_00282F20(float *, float *, float);
extern int func_002A7EA0(char *, char *, char *, int, float, float, float, float);
extern float func_002AA2E8(float *, float, float);
extern void func_002AA548(float *, char *, float, float, float, float);
extern void func_002AAA00(char *, float, float, float, float, char *, int);
extern float func_00283C80(float, float);
extern int func_L02_0032E998(char *, int, float *, char *, int, char *, char *, float,
                             float);


/* Picks the actor's next walking or idle animation after it reaches a goal or finishes a turn. */
void func_L06_0041FAF8(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    if (*(int *)(vars + 0x5A0) == 1) {
        if (*(int *)(vars + 0x23C) == -1) {
            if (func_32D238(vars + 0x25C)) {
                func_35A550(moby, 7, 2);
                if (*(unsigned char *)(moby + 0x43) != 0x13) {
                    func_35A270(moby, 0x13, 0, 20);
                }
                vars[0x48] = func_32E728(20.0f);
                vars[0x4A] = func_32E728(24.0f);
            }
        } else {
            func_35A550(moby, 8, 2);
            if (*(unsigned char *)(moby + 0x43) != 0x12) {
                func_35A270(moby, 0x12, 0, 20);
            }
            vars[0x48] = func_32E728(20.0f);
            vars[0x4A] = func_32E728(24.0f);
        }
    } else if (*(short *)(vars + 0x492) != 0 && func_32D238(vars + 0x25C)) {
        *(short *)(vars + 0x492) = 0;
        func_35A550(moby, 7, 2);
        if (!func_35A620(2)) {
            if (*(unsigned char *)(moby + 0x43) != 0x11) {
                func_35A270(moby, 0x11, 0, 20);
            }
            vars[0x48] = func_32E728(20.0f);
            vars[0x4A] = func_32E728(24.0f);
        } else {
            if (*(unsigned char *)(moby + 0x43) != 0x13) {
                func_35A270(moby, 0x13, 0, 20);
            }
            vars[0x48] = func_32E728(20.0f);
            vars[0x4A] = func_32E728(24.0f);
        }
    } else if (*(short *)(vars + 0x492) == 0 && func_32D238(vars + 0x25C)) {
        func_35A550(moby, 9, 2);
        if (*(unsigned char *)(moby + 0x43) != 0x12) {
            func_35A270(moby, 0x12, 0, 20);
        }
        vars[0x48] = func_32E728(20.0f);
        vars[0x4A] = func_32E728(24.0f);
    }
}

void func_L06_004579C8(char *a0)
{
    char *s2 = *(char **)(a0 + 0x68);
    int v;

    func_32D5C8(a0 + 0x10, a0 + 0x10, s2);
    v = func_32E728((float)D_L06_001B375C * 1.5f);
    func_352000(a0, v, func_32E728((float)D_L06_001B375C * 1.25f), D_L06_001B375C);
    if (D_L06_001B3758 != 0) {
        func_32D8A8(s2, s2, 0.11666667461395264f);
        *(float *)(s2 + 0x8) = *(float *)(s2 + 0x8) + 0.18333333730697632f;
        *(unsigned int *)(a0 + 0x64) = (unsigned int)func_L06_003DDCA8;
        *(float *)(a0 + 0x2C) = *(float *)(a0 + 0x2C) * 0.75f;
        func_352000(a0, 0x10, 0x10, 0x10);
    }
}

/* Turns the head toward the hero, within a limited left-right and up-down range. */
void func_L06_00444068(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float toHero[3];

    func_32D5F8((char *)toHero, D_L06_00189EA0, moby + 0x10);
    func_365030(moby, (char *)toHero, (char *)toHero, 0);
    *(float *)(vars + 0x2C0) = func_32DC80(toHero[0], toHero[1]);
    if (*(float *)(vars + 0x2C0) > 0.78539825f) {
        *(float *)(vars + 0x2C0) = 0.78539825f;
    } else if (*(float *)(vars + 0x2C0) < -0.78539825f) {
        *(float *)(vars + 0x2C0) = -0.78539825f;
    }
    *(float *)(vars + 0x2C8) = -func_32DC80(func_32D740((char *)toHero), toHero[2]);
    if (*(float *)(vars + 0x2C8) > 0.52359885f) {
        *(float *)(vars + 0x2C8) = 0.52359885f;
    } else if (*(float *)(vars + 0x2C8) < -0.52359885f) {
        *(float *)(vars + 0x2C8) = -0.52359885f;
    }
}

/* A breakable object: waits to be hit, then bursts into particles and disappears. */
void func_L06_00457AD0(unsigned char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        *(unsigned short *)(moby + 0x34) |= 0x800;
        func_35A550((char *)moby, 1, -1);
        break;
    case 1:
        if (func_35CBA0((char *)moby, 0x4010000, 0) != 0) {
            if (*(int *)vars == 0) {
                func_35A550((char *)moby, 2, -1);
            }
        }
        moby[0xA8] = 0xFF;
        break;
    case 2: {
        char offset[16];

        func_32D650(offset, (char *)(moby + 0xD0), -0.033333335f);
        SpawnDebrisParticles((char *)moby, 7, offset, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_3A0948(0, 0, (char *)moby);
        func_3661E0((char *)moby, 1, 0.0f);
        func_350388((char *)moby);
        break;
    }
    }
}

/* Same breakable object behaviour as func_L06_00457AD0, used by another object type. */
void func_L06_00457DA0(unsigned char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        *(unsigned short *)(moby + 0x34) |= 0x800;
        func_35A550((char *)moby, 1, -1);
        break;
    case 1:
        if (func_35CBA0((char *)moby, 0x4010000, 0) != 0) {
            if (*(int *)vars == 0) {
                func_35A550((char *)moby, 2, -1);
            }
        }
        moby[0xA8] = 0xFF;
        break;
    case 2: {
        char offset[16];

        func_32D650(offset, (char *)(moby + 0xD0), -0.033333335f);
        SpawnDebrisParticles((char *)moby, 7, offset, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_3A0948(0, 0, (char *)moby);
        func_3661E0((char *)moby, 1, 0.0f);
        func_350388((char *)moby);
        break;
    }
    }
}

/* Switches on the linked object, if this object has one. */
void func_L06_0041FD60(char *moby)
{
    if (*(unsigned char *)(moby + 0x21) != 0xFF)
        func_35B810(*(unsigned char *)(moby + 0x21), 1);
}

/* func_L06_0041DED8 is defined in L06_0041DED8-update.c. */

extern char D_L06_001B0820[];
extern char D_L06_001B9840[];
extern int func_L02_0032E508(void *, int, void *, int);
extern void func_0026FEB8(const char *, ...);
extern float func_002A78D8(float, float);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_002B0ED8(void *, void *, int);
extern void func_L06_0041F798(u8 *);
extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);
extern void func_002A6C58(void *, int, int);
extern void func_002AC728(void *, void *, int, float, float);
extern void func_0029F338(void *);

/* A Notak enemy's update, the same shape as func_L06_00443A38: spawn-time setup, then the
   distance, target and ground checks. The fields are indexed through typed pointers (in-struct
   MEMs), and the setup's store order is the one that gives retail's schedule and registers.
   qzero_nc's bare volatile asm flushes cse, so the later `m[0x43] != 3` test builds a fresh 3
   rather than keeping the setup's 3 in a saved register across the calls, as retail does. */
#define B(o) (v[o])
#define H(o) (((short *)v)[(o) / 2])
#define I(o) (((int *)v)[(o) / 4])
#define F(o) (((float *)v)[(o) / 4])

void func_L06_0041EF08(u8 *moby)
{
    u8 *v = *(u8 **)(moby + 0x68);
    int hitResult;

    if (moby[0x20] == 0) {
        I(0x480) = BuildRouteNodes(moby, I(0x230), v + 0x260, 16);
        STUB_printf(D_L06_001B0820, I(0x480));
        qcopy(v + 0x460, moby + 0x10);
        F(0x46C) = *(float *)(moby + 0xF8);
        B(0x70) = 15;
        I(0xA8) = 3;
        B(0x71) = 12;
        F(0x90) = 0.5f;
        B(0x28) = 1;
        B(0xD4) = 0;
        H(0x26) = 0;
        B(0x72) = 16;
        B(0x76) = 14;
        B(0x77) = 15;
        F(0x7C) = 0.20000002f;
        F(0x80) = 0.125f;
        F(0x84) = 0.00555555569f;
        F(0x88) = 0.00972222257f;
        F(0x8C) = 0.00416666688f;
        F(0x94) = 0.5f;
        F(0x9C) = 0.4f;
        B(0xCC) = 7;
        B(0xCD) = 12;
        B(0xCE) = 3;
        B(0xCF) = 5;
        B(0xD2) = 10;
        B(0xD3) = 17;
        F(0x5AC) = (float)B(0x34);
        B(0x29) = 1;
        F(0x30) = 0.75f;
        F(0x47C) = RandomSignedFloatRange(10.0f, 25.0f) * 0.0174532942f;
        I(0x478) = 0;
        H(0x24C) = RandomIntRange(0, 0x5F);
        I(0x498) = -1;
        I(0x5A0) = H(0x490);
        qzero_nc(v + 0x5B0);
        SetMobyState(moby, 1, 0);
        if (moby[0x43] != 1)
            StartAnimationBlended(moby, 1, 0, 0);
        B(0x48) = FloatToInt(20.0f);
        B(0x4A) = FloatToInt(8.0f);
        if (H(0x492) != 0) {
            if (moby[0x43] != 3)
                StartAnimationBlended(moby, 3, 0, 0);
            B(0x48) = FloatToInt(20.0f);
            B(0x4A) = FloatToInt(24.0f);
        }
    }
    if (moby[0x31] != 0 && fast_vec_dist(moby + 0x10, D_L06_001B9840) < 24.0f) {
        UpdateMobyGroundCheck(moby);
        moby[0x6F] = 0x16;
    }
    hitResult = ApplyDamageToObject(moby, v + 0x60, 0);
    if (hitResult != 0) {
        if (B(0x37) == 10)
            B(0xD7) = 1;
        if (hitResult == 5) {
            I(0xF0) = 0;
            F(0xF4) = 0.837758183f;
        }
        AlertGroupActors(moby);
        moby[0xA8] = 0xFF;
    }
    I(0x228) = SelectAimTarget_002B3BA8(moby, I(0x220), F(0x240), 10.0f, 0, 0);
    I(0x22C) = SelectAimTarget_002B3BA8(moby, I(0x224), F(0x244), 10.0f, 0, 0);
    if (*(float *)(moby + 0x18) < 48.0f) {
        SetDeathBits(moby, 0, 3);
        SpawnExplosionWithSparks(moby, moby + 0x10, -1, 1.0f, 13.0f);
        MarkMobySpawned(moby);
    }
}

#undef B
#undef H
#undef I
#undef F

/* Turns the actor toward its target and keeps the two angles it stores at +0x470 and
   +0x474 of its state; returns 1 when the actor's state changed. */
int func_L06_0041F2A0(char *moby, char *goal, float defaultYaw, float speedScale, float slowDistance, float turnRate)
{
    char *vars = *(char **)(moby + 0x68);
    float toGoal[4];
    float step[4];
    float nextPos[4];
    float d = 0.0f;
    float desiredYaw;
    float distance;
    float accelStep;
    int changed = 0;

    FastVecSub(toGoal, (float *)goal, (float *)(moby + 0x10));
    toGoal[2] = 0.0f;
    distance = FastVecLength(toGoal);
    accelStep = speedScale * 0.0008333333535119891f;
    if (slowDistance < distance) {
        int pathCount = *(int *)(vars + 0x480);

        desiredYaw = 0.0f;
        ComputeRegionRouteHeading(moby + 0x10, (int)goal, &desiredYaw, vars + 0x260, pathCount, vars + 0x488,
                          vars + 0x48C, turnRate, 0.5f);
        ApproachTargetWithDirectionMode(moby + 0xF8, desiredYaw, 0.0037815470714122057f,
                      0.0037815470714122057f, 0.29670602083206177f, vars + 0x474, 0);
        if (FastDiffRots(*(float *)(moby + 0xF8), desiredYaw) < 1.3089970350265503f) {
            StepValueTowardTarget(&d, vars + 0x470, distance, accelStep, accelStep, speedScale * 0.01666666753590107f);
        } else {
            *(float *)(vars + 0x470) = 0.0f;
        }
    } else {
        ApproachTargetWithDirectionMode(moby + 0xF8, defaultYaw, 0.0037815470714122057f,
                      0.0037815470714122057f, 0.29670602083206177f, vars + 0x474, 0);
        ApproachValue((float *)(vars + 0x470), 0.0f, accelStep);
        if (*(float *)(vars + 0x470) == 0.0f) {
            if (FastDiffRots(*(float *)(moby + 0xF8), defaultYaw) < 0.0872664749622345f) {
                *(float *)(vars + 0x474) = 0.0f;
                changed = 1;
            }
        }
    }
    vec_scale_to_length(step, (float *)(moby + 0xC0), *(float *)(vars + 0x470));
    FastVecAdd(nextPos, step, (float *)(moby + 0x10));
    if (MoveOverGround(moby, moby + 0x10, (char *)nextPos, 0, 0.8999999761581421f, 1.0f, 0.5f,
                     0.7853982448577881f) == 0) {
        *(int *)(vars + 0x5A8) = *(int *)(vars + 0x5A8) + 1;
    }
    /* The counter at +0x5A8 wraps at 0x14, and the actor then reports the change. */
    if (*(int *)(vars + 0x5A8) < 0x14) {
        goto done;
    }
    *(int *)(vars + 0x5A8) = 0;
    changed = 1;
done:
    return changed;
}

/* func_L06_0041F558 is defined in L06_0041F558.c. */

extern char D_L06_001B9840[];
extern int func_35A620(int);
extern float func_35A718(float, float);
extern void func_361300(void *, void *, void *, float);
extern char *func_37A018(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_32E728(float);
extern float func_35A6B8(float, float);

/* Throws a burst of colored particles away from the hero's side of the given position. */
void func_L06_0041F818(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    func_32D5F8((char *)direction, (char *)D_L06_001B9840, (char *)pos);
    func_32D8A8((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_35A6B8(0.5f, 2.0f);
        sign = func_35A620(2);
        if (!sign) sign--;
        angle = func_35A6B8(-1.0471977f, 1.0471977f);
        func_361300(velocity, direction, axis, angle);
        func_32D8A8((char *)velocity, (char *)velocity, func_35A6B8(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = func_35A6B8(1.0f, 5.0f) * 0.0166666675f;
        func_32D5C8((char *)origin, (char *)pos, (char *)offset);
        pos[0] += func_35A718(0, 0.15f);
        pos[1] += func_35A718(0, 0.15f);
        pos[2] += func_35A718(0, 0.15f);
        particle = func_37A018(origin, 20, size * 0.1f, size, 0x7F801010, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_32E728(4.0f) + 0x70;
        particle = func_37A018(origin, 20, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_32E728(4.0f) + 0x70;
    }
}



/* func_L06_0041FC58 is matched in its own unit, src/levels/06_notak/L06_0041FC58-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

/* Counts down the actor's timers and puffs out a few dust particles each frame. */
void func_L06_0041FD90(unsigned char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float velocity[4], position[4];
    int count;
    unsigned char *first, *particle;
    UpdateColorFade(moby, vars + 0x50);
    if (moby[0xBC]) {
        moby[0xBC] = 0;
        if (*(int *)(vars + 0x248) < 300)
            *(int *)(vars + 0x248) = RandomIntRange(480, 600);
    }
    if (FastFloatHelperD(vars + 0x24C) && *(int *)(vars + 0x204) != 2)
        FastFloatHelperD(vars + 0x248);
    FastFloatHelperD(vars + 0x240);
    if (*(unsigned short *)(moby + 0x96) < 65534) ++*(unsigned short *)(moby + 0x96);
    if (FastFloatHelperD(vars + 0x250)) *(float *)(vars + 0x290) = *(float *)(vars + 0x298);
    velocity[0] = 0;
    velocity[2] = -0.05f;
    velocity[3] = 1;
    velocity[1] = 0;
    count = RandomIntBelow(16);
    if (RandomIntBelow(2)) count = -count;
    qcopy(position, moby + 0x10);
    position[2] -= 0.2f;
    first = SpawnSpinningSparkParticle((char *)position, .1f, 1, .9f, count, (char *)velocity, 315000, 0xDF204080, 0);
    if (first) {
        unsigned char *state;
        *(short *)(first + 0xA) = 9;
        state = first + 0x20;
        first[9] = FloatToInt(4) + 0x70;
        *(int *)(state + 4) = 2;
        state[0xA] = 0xDF;
        state[0xB] = first[0xA];
    }
    {
        unsigned char *second = SpawnSpinningSparkParticle((char *)position, .1f, 1, .9f, count, (char *)velocity, 315000, 0xDF204080, 0);
        if (second) {
            unsigned char *state = second + 0x20;
            /* Retail reuses the first particle header here. */
            *(short *)(first + 0xA) = 9;
            first[9] = FloatToInt(4) + 0x70;
            *(int *)(state + 4) = 2;
            state[0xA] = 0xDF;
            state[0xB] = first[0xA];
        }
    }
    particle = SpawnSpinningSparkParticle((char *)position, .05f, 1, .97f, 16, (char *)velocity, 157500, 0x8FFFFFFF, 0);
    if (particle) {
        unsigned char *state;
        state = particle + 0x20;
        particle[9] = FloatToInt(4) + 0x70;
        *(short *)(particle + 0xA) = 23;
        particle[8] = RandomIntBelow(255);
        *(int *)(state + 4) = 2;
        state[0xA] = 0x8F;
        state[0xB] = first[0xA];
    }
}

/* func_L06_00420080 is defined in L06_00420080.c. */


/* func_L06_00420548 is defined in L06_00420548-g.c. */

/* func_L06_00420740 is defined in L06_00420740.c. */

/* func_L06_00420AE8 is defined in L06_00420AE8-g8.c. */

/* The object runs through five states. The dispatch reads the level's own jump table (five
   words in the level's data at 0x2E1F00); `cases` only keeps the labels alive. */
/* Opens and closes a mechanism in five steps, playing an animation for each step. */
void func_L06_0042B868(char *moby)
{
    static void *cases[5] = {&&c0, &&c1, &&c2, &&c3, &&c4};
    char *obj = moby;
    char *vars;
    unsigned int step;

    step = *(unsigned char *)(obj + 0x20);
    vars = *(char **)(obj + 0x68);
    if (step < 5)
        goto *D_L06_002E1F00[step];
    goto done;
c0:
    *(unsigned char *)(obj + 0x20) = 1;
    *(int *)vars = 0x5DC;
    goto done;
c1:
    if (*(unsigned char *)(obj + 0xBC) == 0)
        goto done;
    *(unsigned char *)(obj + 0x20) = 2;
    if (*(unsigned char *)(obj + 0x43) != 1)
        func_35A270(obj, 1, 0, 0);
    *(int *)(obj + 0x98) = 0;
    goto done;
c2:
    if ((*(unsigned char *)(obj + 0x60) & 2) == 0)
        goto done;
    *(unsigned char *)(obj + 0x20) = 3;
    if (*(unsigned char *)(obj + 0x43) == 2)
        goto done;
    func_35A270(obj, 2, 0, 0);
    goto done;
c3:
    if (func_32D238(vars) == 0)
        goto done;
    *(unsigned char *)(obj + 0x20) = 4;
    if (*(unsigned char *)(obj + 0x43) == 3)
        goto done;
    func_35A270(obj, 3, 0, 0);
    goto done;
c4:
    if ((*(unsigned char *)(obj + 0x60) & 2) == 0)
        goto done;
    *(unsigned char *)(obj + 0x20) = 1;
    if (*(unsigned char *)(obj + 0x43) == 0)
        goto tail;
    func_35A270(obj, 0, 0, 0);
tail:
    *(int *)(obj + 0x98) = *(int *)(*(int *)(obj + 0x24) + 0x10);
    *(int *)vars = 0x5DC;
    func_35B810(*(unsigned char *)(obj + 0x21), 0);
    goto done;
done:
    return;
}

/* func_L06_00430318 is defined in L06_00430318-g8.c. */


/* func_L06_00443280 is defined in L06_00443280-g8.c. */

/* func_L06_00443A38 is defined in L06_0041DED8-g8.c. */

/* Starts or stops the actor's glow effect. */
void func_L06_00443DE0(char *moby, int unused, int mode)
{
    char *vars = *(char **)(moby + 0x68);

    if (mode == 0) {
        func_36C158();
    } else {
        func_36C1B0(*(float *)(vars + 0x31C));
    }
}

/* Counts down the actor's timers, ages it by one frame and updates its effects. */
void func_L06_00443E18(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    unsigned int age;

    func_32D268(vars + 0x310);
    func_32D268(vars + 0x312);
    age = *(unsigned short *)(moby + 0x96);
    if (age <= 0xFFFE)
        *(unsigned short *)(moby + 0x96) = age + 1;
    func_366160(moby, vars + 0x260, 2.5f, 0, 1);
}


/* func_L06_00444168 and func_L06_00444300 live in L06_0041DED8-g8.c (func_L06_00444300 reaches
 * its constants through $gp; the pair is the level 6 twin of func_L14_00428A08/func_L14_00428BA0). */

/* The same re-arm, with two probe addresses and two flags. */
/* When the hero reaches the object's trigger, switches on both gate flags and moves the object to its next state. */
void func_L06_0044B250(char *moby)
{
    int handle;

    if (*(unsigned char *)(moby + 0x20) != 0)
        return;
    handle = *(int *)(*(int *)(moby + 0x68));
    if (handle == -1)
        return;
    if (func_360F58(D_L06_00189EA0, handle) == 0)
        return;
    func_2E3EF0(D_L06_001B1330);
    func_2E3EF0(D_L06_001B1370);
    D_L06_001395B8.flag_013 = 1;
    D_L06_001395B8.flag_014 = 1;
    func_35A550(moby, 1, -1);
}

/* Re-arms the object when the shared probe accepts its live handle. */
/* When the hero reaches the object's trigger, sets the first gate flag and moves the object to its next state. */
void func_L06_0044B2D8(char *moby)
{
    int handle;

    if (*(unsigned char *)(moby + 0x20) != 0)
        return;
    handle = *(int *)(*(int *)(moby + 0x68));
    if (handle == -1)
        return;
    if (func_360F58(D_L06_00189EA0, handle) == 0)
        return;
    func_2E3EF0(D_L06_001B13B0);
    D_L06_001395CE = 1;
    func_35A550(moby, 1, -1);
}

/* The same re-arm, with the level's second probe address. */
/* When the hero reaches the object's trigger, sets the second gate flag and moves the object to its next state. */
void func_L06_0044B350(char *moby)
{
    int handle;

    if (*(unsigned char *)(moby + 0x20) != 0)
        return;
    handle = *(int *)(*(int *)(moby + 0x68));
    if (handle == -1)
        return;
    if (func_360F58(D_L06_00189EA0, handle) == 0)
        return;
    func_2E3EF0(D_L06_001B13F0);
    D_L06_001395CF = 1;
    func_35A550(moby, 1, -1);
}

/* The same re-arm, gated on the shared live-object probe. */
/* When the hero reaches the object's trigger and the level check passes, sets the third gate flag and moves on. */
void func_L06_004504C8(char *moby)
{
    int handle;

    if (*(unsigned char *)(moby + 0x20) != 0)
        return;
    handle = *(int *)(*(int *)(moby + 0x68));
    if (handle == -1)
        return;
    if (func_360F58(D_L06_00189EA0, handle) == 0)
        return;
    if (func_333898() == 0)
        return;
    D_L06_001395D0 = 1;
    func_35A550(moby, 1, -1);
}

/* func_L06_00455BC0 is in L06_0041DED8-f7-g8.c. */

/* func_L06_00456278 is in L06_00456278.c. */


/* Clears the level's pool of small effect objects. */
void func_L06_00456EE0(void)
{
    func_3BFBB8(D_L06_002AA500, 0x30);
}

/* func_L06_00456F08 is defined in L06_00456F08.c. */

/* func_L06_00457270 is in L06_00457270.c: its zeroed vector is a por. */

/* func_L06_004573E8 is in L06_004573E8-g8.c. */


/* func_L06_004577B0 lives in L06_0041DED8-g8.c: it reads its first angle through $gp. */



extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_00273730(char *, int, int, int, char *, char *,
                           float *, int, float, float);

void func_L06_00457C00(char *object, int mask, void *offset, int color,
                      float speed_min, float speed_max,
                      float vertical_min, float vertical_max)
{
    float velocity[3];
    float angle, speed, life, size;
    char *particle;
    unsigned char shade = color;
    int i;

    for (i = 0; i < 15; i++) {
        if (((mask >> i) ^ 1) & 1)
            continue;
        angle = RandomAngle();
        speed = RandomFloatRange(speed_min, speed_max) * (1.0f / 60.0f);
        velocity[0] = FastSinOrCosA(angle) * speed;
        velocity[1] = FastSinOrCosB(angle) * speed;
        velocity[2] = 0.0f;
        velocity[2] = RandomFloatRange(vertical_min, vertical_max) * (1.0f / 60.0f);
        FastVecAdd(velocity, velocity, offset);
        life = RandomFloatRange(90.0f, 270.0f);
        size = RandomFloatRange(10.0f, 20.0f);
        particle = CreateCameraMoby(object, 2, *(short *)(object + 0xAA), i,
                                object + 0x10, object + 0xF0, velocity, shade,
                                life, size);
        if (particle)
            *(unsigned short *)(particle + 0x34) |= 0x10;
    }
}

/* When hit, wakes up the actors in its linked groups and then removes itself. */
void func_L06_00457ED0(unsigned char *moby)
{
    char *vars;
    char *hitMoby;
    short *idList, *idCursor;
    char *actor;
    char *actorVars;
    if (moby[0x20] == 0) {
        *(unsigned short *)(moby + 0x34) |= 0x800;
        moby[0x20] = 1;
    }
    vars = *(char **)(moby + 0x68);
    hitMoby = (char *)func_35CBA0((char *)moby, 0x10000, 0);
    if (hitMoby && *(short *)(*(char **)(hitMoby + 0x20) + 0xAA) != 0xFE5 /* moby class 4069 */) {
        if (*(int *)vars == 255) { func_458138((char *)moby); return; }
        {
            idList = D_L06_001FB3A0[*(int *)vars];
            if (idList == 0) { func_458138((char *)moby); return; }
            {
                idCursor = idList;
                do {
                    actor = D_L06_001B281C[0] + ((*idCursor & 0x7FFF) << 8);
                    if (*(signed char *)(actor + 0x20) >= 0 && *(short *)(actor + 0xAA) == 0xBBA /* moby class 3002 */) {
                        actorVars = *(char **)(actor + 0x68);
                        if (*(float *)(actorVars + 0x20) > 0.0f) {
                            *(float *)(actorVars + 0x5A4) = func_35A780();
                            qcopy(actorVars + 0x5B0, actorVars + 0x460);
                            *(short *)(actorVars + 0x24C) = 0x10E;
                            actor[0x20] = 4;
                            func_35A270(actor, 6, 0, 10);
                            *(int *)(actorVars + 0x5A0) = 0;
                            *(short *)(actorVars + 0x492) = 0;
                            actor[0x20] = 5;
                            actor[0x95] = 1;
                        }
                    }
                } while (*idCursor++ >= 0);
            }
        }
        if (*(int *)(vars + 4) == 255) goto destroy;
        idList = D_L06_001FB3A0[*(int *)(vars + 4)];
        if (idList == 0) {
 destroy:
            func_458138((char *)moby); return;
        }
        {
            idCursor = idList;
            do {
                actor = D_L06_001B281C[0] + ((*idCursor & 0x7FFF) << 8);
                if (*(signed char *)(actor + 0x20) >= 0 && *(short *)(actor + 0xAA) == 0xBBA /* moby class 3002 */) {
                    actorVars = *(char **)(actor + 0x68);
                    *(float *)(actorVars + 0x5A4) = func_35A780();
                    qcopy(actorVars + 0x5B0, actorVars + 0x460);
                    *(short *)(actorVars + 0x24C) = 0x10E;
                    actor[0x20] = 4;
                    func_35A270(actor, 6, 0, 10);
                    actor[0x20] = 5;
                    actor[0x95] = 1;
                }
            } while (*idCursor++ >= 0);
        }
        func_458138((char *)moby);
    }
    moby[0xA8] = 255;
}
