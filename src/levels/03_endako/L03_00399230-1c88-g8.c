#include "include_asm.h"

#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));

extern float func_002A7940(void);
extern float func_002A78D8(float, float);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern float func_L02_002F21C0(void *, void *);
extern void func_002A7750(char *, int, int);
extern void func_002833F0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_002A9640(char *, int, int);
extern void func_002AAA00(void *, void *, int, float, float, float, float);
extern void func_0029F390(char *);
extern int func_002B3868(char *);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_00282F20(void *, void *, float);
extern void func_L01_002E1680(void *, void *, int, int, int, float, float, float);
extern int func_002E5CF8(int, int, char *);
extern char *func_L00_00326620(char *, int, int);
extern void func_L00_0032A258(char *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_0029F338(char *);
extern void func_L00_00324F18(char *, void *, float, float, float);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float,
                          float, float, int, float, int, int, int, int, int);

extern char D_00189EA0[];
/* Paired absolute views of the same small-data floats. */
extern float D_L03_001B0AE0_1[] MACRO_ADDR;
extern float D_L03_001B0AE8_1[] MACRO_ADDR;
extern float D_L03_001B0B30_1[] MACRO_ADDR;
extern float D_L03_001B0AE0 __attribute__((sda));
extern float D_L03_001B0AE8 __attribute__((sda));
extern float D_L03_001B0AF0 __attribute__((sda));
extern float D_L03_001B0AF4 __attribute__((sda));
extern float D_L03_001B0AF8 __attribute__((sda));
extern float D_L03_001B0B30 __attribute__((sda));
extern char D_L03_001B0B10_GP[] SDATA(D_L03_001B0B10);
extern char D_L03_001B0B08_GP[] SDATA(D_L03_001B0B08);
extern char D_L03_001B0B00_GP[] SDATA(D_L03_001B0B00);
extern char D_L03_001A8F20[] __attribute__((sda));
extern int D_L03_001B0B40 __attribute__((sda));

/* Updates a floating object that sways in the air, drifts toward something that touches it, then flies off, plays an effect and disappears. */
void func_L03_003E1C88(char *obj)
{
    float tmpVec[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    char matrix[0x30] __attribute__((aligned(16)));
    char *vars = *(char **)(obj + 0x68);
    float angle;
    int stateId;

    stateId = *(u8 *)(obj + 0x20);
    switch (stateId) {
    case 0:
        qcopy(vars, obj + 0x10);
        *(int *)(obj + 0x48) = 0;
        obj[0x42] = 0;
        *(int *)(obj + 0x44) = 0;
        obj[0x43] = 1;
        *(float *)(vars + 0x10) = RandomAngle();
        *(float *)(vars + 0x14) = RandomAngle();
        *(float *)(vars + 0x18) =
            RandomSignedFloatRange(D_L03_001B0AE0, D_L03_001B0AE0_1[1]) * 0.0002908882452175021f;
        *(float *)(vars + 0x1C) =
            RandomSignedFloatRange(D_L03_001B0AE8, D_L03_001B0AE8_1[1]) * 0.0002908882452175021f;
        *(float *)(vars + 0x3C) = 0.10471977f;
        *(float *)(vars + 0x38) = 0.0017453294713050127f;
        SetMobyState(obj, 1, -1);
        break;

    case 1:
        if (!*(u8 *)(obj + 0x31))
            break;
        *(float *)(vars + 0x10) = FastAddRotations(*(float *)(vars + 0x10), *(float *)(vars + 0x18));
        *(float *)(vars + 0x14) = FastAddRotations(*(float *)(vars + 0x14), *(float *)(vars + 0x1C));
        *(float *)(obj + 0xF0) = D_L03_001B0AF0 * FastSinOrCosB(*(float *)(vars + 0x10));
        *(float *)(obj + 0xF4) = D_L03_001B0AF4 * FastSinOrCosB(*(float *)(vars + 0x14));
        *(Quad *)angles = 0;
        angles[0] = *(float *)(vars + 0x10);
        angles[2] = *(float *)(vars + 0x14);
        *(Quad *)tmpVec = *(Quad *)angles;
        euler_rotation_basis(matrix, tmpVec);
        FastVecScale(obj + 0x10, matrix + 0x10, D_L03_001B0AF8);
        FastVecAdd(obj + 0x10, obj + 0x10, vars);
        if (!*(int *)(vars + 0x30)) {
            char *hit = FindOwnedEffectSlot(obj, 0x4010000, 0);
            if (hit) {
                qcopy(vars + 0x20, hit + 0x10);
                SetMobyState(obj, 2, -1);
            }
        }
        if (DistanceSquaredXY(obj + 0x10, gHeroPosition) < 200.0f) {
            char *hero = gHeroPosition - 0x80;
            angle = FastAddRotations(FastMatrixHelperA(*(float *)(hero + 0x80) - *(float *)(obj + 0x10),
                                            *(float *)(hero + 0x84) - *(float *)(obj + 0x14)),
                              1.5707964f);
            ApproachTargetWithDirectionMode(obj + 0xF8, vars + 0x34, 0, angle, *(float *)(vars + 0x38),
                          *(float *)(vars + 0x38), *(float *)(vars + 0x3C));
            angle = FastMatrixHelperA(vec_distance_xy(gHeroPosition, obj + 0x10),
                              *(float *)(obj + 0x18) - *(float *)(hero + 0x88)) * 0.63661975f;
            if (angle > 1.0f)
                angle = 1.0f;
            else if (angle < 0.0f)
                angle = 0.0f;
            *(float *)(obj + 0x44) = 1.0f - angle;
            update_moby_animation_state(obj);
        }
        break;

    case 2:
        if (SetFirstPendingFlag(obj)) {
            *(unsigned short *)(obj + 0x96) = RandomIntRange(20, 30);
            *(float *)(obj + 0xF0) *= 4.0f;
            *(float *)(obj + 0xF4) *= 4.0f;
            vec_scale_to_length(vars + 0x20, vars + 0x20, 1.0f / 6.0f);
        }
        *(Quad *)tmpVec = 0;
        tmpVec[2] = 1.0f / 15.0f;
        if (!RandomIntBelow(2))
            SpawnSparkBurst_L01(obj + 0x10, tmpVec, 1, 0x40202020, 1, 0.0066666672937572f, 0.9f, 1.02f);
        *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(obj + 0xF8), 0.20943954586982727f);
        FastVecAdd(obj + 0x10, obj + 0x10, vars + 0x20);
        {
            int timer = *(unsigned short *)(obj + 0x96);

            stateId = timer - 1;
            *(unsigned short *)(obj + 0x96) = stateId;
            if (!timer)
                SetMobyState(obj, 3, -1);
        }
        break;

    case 3: {
        char *effect;

        PlayMobySound(0, 0, obj);
        effect = SpawnChildMoby_L00(obj, 0x113D, *(u8 *)(obj + 0x30));
        if (effect) {
            ExplodeObjectIntoPieces(effect, D_L03_001B0B10_GP, D_L03_001B0B08_GP, D_L03_001B0B00_GP, 65535, 1,
                              D_L03_001B0B40, 6, 65535, 255, 0);
            MarkMobySpawned(effect);
        }
        LocalOffsetToWorld(obj, tmpVec, D_L03_001B0B30, D_L03_001B0B30_1[1], D_L03_001B0B30_1[2]);
        SpawnExplosionEffects(obj, D_L03_001A8F20, tmpVec, 0.0f, 0.0f, 10, 5, 15, 0.0f, 0.0f, 9.0f,
                      *(float *)(obj + 0x2C) * 30.0f, -1, 0.0f, 0, 0, -1, 0, 0x810001);
        MarkMobySpawned(obj);
        break;
    }
    }
}
