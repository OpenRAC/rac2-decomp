#include "common.h"
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vector;
typedef Vector Row[4];
typedef struct {
    int index;
    char pad4[0xe];
    short lifetime;
    int pad14;
    u8 selected[8];
    Vector positions[32], velocities[32];
    Vector branches[4][4], branchVelocities[4][4];
    int duration;
    char pad624[0x2c];
    float rotation[3];
} Beam;
typedef struct {
    char pad0[0x10];
    Vector position;
    char pad20[0x48];
    Beam *vars;
} BeamMoby;
extern int D_001A79F0;
extern int D_L16_001AF884 __attribute__((sda)), D_L16_001AF888 __attribute__((sda));
extern float D_L16_001AF908 __attribute__((sda)), D_L16_001AF90C __attribute__((sda)), D_L16_001AF920 __attribute__((sda));
extern int D_L16_001AF914 __attribute__((sda)), D_L16_001AF918 __attribute__((sda));
extern int D_L16_001AF928 __attribute__((sda)), D_L16_001AF92C __attribute__((sda));
extern char *D_L16_001B2C0C __attribute__((sda));
extern float D_L16_001B9B00[4];
extern int func_002A7820(int,int);
extern float func_002A7878(float,float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_002A7A00(void *,float,float);
extern void func_00282C88(void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern float func_00282E80(void *,void *);
extern float func_002A7940(void);
extern void func_00283410(void *,void *);
extern void func_002830C0(void *,void *,void *);
extern int func_002A77E0(int);
extern void *func_002BAA28(void *,void *,void *,int,int,int,int,int,int);

/* The second particle loop draws this coin and never reads it. The test still has to be there at
   gcse: it splits the block, so the call's &jitter takes the reaching register as in the first loop. */
static inline void flipCoin(int *heads)
{
    if (func_002A77E0(2))
        *heads = 1;
    else
        *heads = 0;
}

void func_L16_003AA3F0(BeamMoby *object)
{
    Beam *beam = object->vars;
    Vector positions[32], velocities[32], scratch, jitter;
    Vector transform[4];
    const float frameTime = 0.01666666753590107f;
    float half;
    float timeStep;
    float unit;
    float spread;
    int i, smoothIndex, branchIndex, particleIndex, j, k;
    int selected;
    object->position.w = 1.0f;
    beam->lifetime = func_002A7820(D_L16_001AF884, D_L16_001AF888);
    beam->duration = beam->lifetime;
    if (D_001A79F0 == 0xd5 || D_001A79F0 == 16)
        spread = func_002A7878(40.0f, 45.0f);
    else spread = func_002A7878(4.0f, 8.0f);
    half = 0.5f;
    timeStep = frameTime;
    unit = 1.0f;
    for (i = 0; i < 32; i++) {
        float height = func_00283CE0(i);
        float last = func_00283CE0(31);
        height = height / last;
        height = (half - height) * spread;
        if ((unsigned)(i - 3) >= 26) {
            func_00282C88(&positions[i]);
            func_00282C88(&velocities[i]);
        } else {
            func_002A7A00(&positions[i], 0.0f, D_L16_001AF908);
            if (D_001A79F0 == 16 || D_001A79F0 == 0xd5)
                func_002A7A00(&velocities[i], 0.0f, 0.20000001788139343f);
            else func_002A7A00(&velocities[i], 0.0f, D_L16_001AF90C * timeStep);
        }
        {
            float y = positions[i].y;
            positions[i].w = unit;
            positions[i].y = y + height;
        }
    }
    for (smoothIndex = 0; smoothIndex < 32; smoothIndex++) {
        if (smoothIndex == 0 || smoothIndex == 31) {
            qcopy(&beam->positions[smoothIndex], &positions[smoothIndex]);
            qcopy(&beam->velocities[smoothIndex], &velocities[smoothIndex]);
        } else {
            func_00282CC0(&scratch, &positions[smoothIndex-1], &positions[smoothIndex]);
            func_00282CC0(&scratch, &scratch, &positions[smoothIndex+1]);
            func_00282D30(&beam->positions[smoothIndex], &scratch, 0.333f);
            func_00282CC0(&scratch, &velocities[smoothIndex-1], &velocities[smoothIndex]);
            func_00282CC0(&scratch, &scratch, &velocities[smoothIndex+1]);
            func_00282D30(&beam->velocities[smoothIndex], &scratch, 0.333f);
        }
    }
    for (branchIndex = 0; branchIndex < 4; branchIndex++) {
        if (D_001A79F0 == 0xd5 || D_001A79F0 == 16)
            func_002A7A00(&scratch, 1.0f, 1.0f);
        else func_002A7A00(&scratch, D_L16_001AF908, D_L16_001AF908);
        selected = func_00283CF0(func_002A7878((float)branchIndex * 6.0f, (float)(branchIndex + 1) * 6.0f)) + 4;
        beam->selected[branchIndex] = selected;
        qcopy(&beam->branches[0][branchIndex], &beam->positions[selected]);
        qcopy(&beam->branchVelocities[0][branchIndex], &beam->velocities[selected]);
        {
            int velOffset = (int)&((Beam *)0)->branchVelocities[0][branchIndex];
            int curOffset = (int)&((Beam *)0)->branches[0][branchIndex];
            for (j = 1; j < 4; j++) {
                Beam *column = (Beam *)(branchIndex * 16);
                column = (Beam *)((int)column + (int)beam);
                func_002A7A00(&jitter, 0.1f, 0.1f);
                if (D_001A79F0 == 0xd5 || D_001A79F0 == 16)
                    func_002A7A00(((Row *)((char *)beam + velOffset))[j], 0.0f, 0.20000001788139343f);
                else func_002A7A00(((Row *)((char *)beam + velOffset))[j], 0.0f, D_L16_001AF90C * frameTime);
                func_00282CC0(((Row *)((char *)beam + curOffset))[j], column->branches[j-1], &scratch);
                func_00282CC0(((Row *)((char *)beam + curOffset))[j], ((Row *)((char *)beam + curOffset))[j], &jitter);
            }
        }
    }
    if (func_00282E80(&object->position, D_L16_001B9B00) >= 4.0f) {
        char *definition = (char *)(beam->index * 128 + (int)D_L16_001B2C0C);
        beam->rotation[2] = *(float *)(definition + 0x78);
        beam->rotation[1] = *(float *)(definition + 0x74);
        beam->rotation[0] = func_002A7940();
        func_00283410(transform, beam->rotation);
        qcopy(&transform[3], &object->position);
        for (particleIndex = 0; particleIndex < 32; particleIndex += 8) {
            int color, duration;
            func_002830C0(&scratch, &beam->positions[particleIndex], transform);
            qcopy(&jitter, &beam->velocities[particleIndex]);
            jitter.w = D_L16_001AF920;
            color = func_002A77E0(2) ? D_L16_001AF928 : D_L16_001AF92C;
            duration = func_002A77E0(10);
            func_002BAA28(&scratch, &jitter, &jitter, D_L16_001AF914, D_L16_001AF918, particleIndex >> 1, 15, duration + 20, color);
        }
        for (k = 0; k < 2; k++) {
            int duration, heads;
            func_002830C0(&scratch, &beam->branches[3][k], transform);
            qcopy(&jitter, &beam->branchVelocities[3][k]);
            jitter.w = D_L16_001AF920;
            flipCoin(&heads);
            duration = func_002A77E0(10);
            func_002BAA28(&scratch, &jitter, &jitter, D_L16_001AF914, D_L16_001AF918, beam->selected[k] >> 1, 15, duration + 20, D_L16_001AF92C);
        }
    }
}
