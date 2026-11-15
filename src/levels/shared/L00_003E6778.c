#include "common.h"
extern char *D_L00_001B2B54 __attribute__((sda));
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern void func_002ACEC0(char *, char *, char *, float);
extern void func_00282F20(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);

/* Allocate an owner-tagged effect record and initialize its mode-specific fields. */
char *func_L00_003E6778(char *rec, int mode, float amount, char *pos)
{
    char offsetA[16] __attribute__((aligned(16)));
    char offsetB[16] __attribute__((aligned(16)));
    char *piece;
    char *base = D_L00_001B2B54;
    int i;
    int zeroInt = 0;
    float zero = (float)zeroInt;
    for (i = 0; i < 320; i++) {
        if (*(int *)(base + i * 128 + 124) != 0) continue;
        switch (mode) {
        case 0:
            if (++*(int *)(rec + 64) == 150) {
                --*(int *)(rec + 64);
                return 0;
            }
            break;
        case 1:
            if (++*(int *)(rec + 68) == 150) {
                --*(int *)(rec + 68);
                return 0;
            }
            break;
        }
        piece = D_L00_001B2B54 + i * 128;
        *(char **)(piece + 124) = rec;
        ++*(int *)(rec + 56);
        {
            int color = RandomIntRange(95, 127);
            *(int *)(piece + 120) = mode;
            *(int *)(piece + 96) = color;
            *(int *)(piece + 92) = color;
        }
        if (mode == 0) {
            int color;
            ApplyAxisRotationToQuaternion(piece + 16, rec + 16, rec, RandomAngle());
            *(float *)(piece + 60) = *(float *)(piece + 56) = *(float *)(rec + 60) * RandomFloatRange(zero, 1.25f);
            *(float *)(piece + 64) = zero;
            color = RandomIntRange(0, 13);
            *(int *)(piece + 108) = (color << 16) + (color << 8) + color;
            *(float *)(piece + 72) = *(float *)(piece + 68) = RandomFloatRange(0.25f, 0.35f);
            *(float *)(piece + 76) = RandomFloatRange(0.75f, 1.0f);
            *(float *)(piece + 36) = zero;
            *(int *)(piece + 88) = *(int *)(piece + 84) = RandomIntRange(100, 120);
            qcopy(piece, *(char **)(piece + 124) + 32);
            vec_scale_to_length(offsetA, piece + 16, RandomFloatRange(0.15f, 0.75f));
            FastVecAdd(piece, offsetA, piece);
            *(int *)(piece + 112) = 2;
            goto zero_angle;
        } else if (mode == 1) {
            int color;
            ApplyAxisRotationToQuaternion(piece + 16, rec + 16, rec, RandomAngle());
            *(float *)(piece + 56) = zero;
            *(float *)(piece + 60) = zero;
            *(float *)(piece + 64) = zero;
            color = RandomIntRange(0, 13);
            *(int *)(piece + 108) = (color << 16) + (color << 8) + color;
            *(float *)(piece + 72) = *(float *)(piece + 68) = RandomFloatRange(0.25f, 0.5f);
            *(float *)(piece + 76) = RandomFloatRange(1.0f, 1.5f);
            *(float *)(piece + 36) = RandomFloatRange(0.06666667f, 0.083333336f);
            *(int *)(piece + 88) = *(int *)(piece + 84) = RandomIntRange(100, 120);
            qcopy(piece, pos);
            *(int *)(piece + 112) = 2;
zero_angle:
            *(float *)(piece + 48) = zero;
        } else if (mode == 2) {
            int color;
            ApplyAxisRotationToQuaternion(piece + 16, rec + 16, rec, amount);
            *(float *)(piece + 56) = zero;
            *(float *)(piece + 60) = zero;
            *(float *)(piece + 64) = zero;
            color = RandomIntRange(1, 10);
            *(int *)(piece + 108) = (color << 16) + (color << 8) + color;
            *(float *)(piece + 72) = *(float *)(piece + 68) = RandomFloatRange(0.15f, 0.25f) * 0.5f;
            *(float *)(piece + 76) = RandomFloatRange(0.5f, 0.8f) * 1.15f;
            *(float *)(piece + 36) = 0.058333337f;
            *(int *)(piece + 88) = *(int *)(piece + 84) = 90;
            vec_scale_to_length(offsetA, *(char **)(piece + 124), 0.2f);
            FastVecAdd(piece, *(char **)(piece + 124) + 32, offsetA);
            vec_scale_to_length(offsetB, piece + 16, 0.75f);
            FastVecAdd(piece, offsetB, piece);
            *(float *)(piece + 48) = RandomSignedFloatRange(0.052359886f, 0.10471977f);
            *(int *)(piece + 112) = mode;
        }
        *(float *)(piece + 32) = 0.00055555557f;
        *(int *)(piece + 104) = *(int *)(piece + 100) = 0x103080;
        *(float *)(piece + 44) = *(float *)(piece + 40) = RandomSignedFloatRange(0.3141593f, 0.35633811354637146f);
        *(float *)(piece + 52) = RandomAngle();
        *(int *)(piece + 116) = 0;
        return piece;
    }
    return 0;
}
