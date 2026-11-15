#include "common.h"
typedef struct {
    unsigned char pad0[0x30];
    float pointX;
    float pointY;
    unsigned char pad1[0x48];
} Rec_42550;

extern float D_L20_001B2124 __attribute__((sda));

extern float D_L20_001B2134 __attribute__((sda));

extern char D_00189E20[];

extern Rec_42550 *D_L20_001B308C;

extern float func_002AA2E8(float *, float, float);

extern void func_002AA800(char *, int, float, float);

extern float func_00282E80(char *, char *);

extern float func_002A89A8(void *, int, float);

extern float func_00283248(float, float);

extern int func_L01_00322288(char *, float);

extern int func_002E5CF8(int, int, char *);

/* Makes the enemy fall and bounce on the ground while it turns toward the hero or its target. Returns 1 when the bouncing has stopped. */
int func_L20_00442550(char *moby) {
    char *self = moby;
    char *vars = *(char **)(moby + 0x68);
    char *hero;
    char *heroPos;
    float value;
    int pathIndex;
    Rec_42550 *pathPoint;

    ApproachValue((float *)(self + 0x48), 1.0f, 0.033333335f);

    if (*(u8 *)(self + 0x94) == 2) {
        StepAngleTowardTarget(vars + 0x1804, 1, 0.0f, D_L20_001B2124 * 0.00014544412f);
    }
    value = *(float *)(vars + 0xF8);
    hero = gHeroState;
    *(float *)(self + 0x18) += value;

    *(float *)(vars + 0xF8) -= *(float *)(vars + 0x7C);

    if (*(int *)(hero + 0x2294) == 0x8C) {
        float value;
        heroPos = hero + 0x80;
        value = vec_distance_xy(heroPos, self + 0x10);
        if (value <= 4.0f) {
            value = *(float *)(hero + 0x88);
            value += 5.0f;
            *(float *)(hero + 0x88) = value;
            value = ProbeGroundHeightBelow(heroPos, 0, 0.5f);
            *(float *)(hero + 0x88) = value;
            *(unsigned short *)(hero + 0x1E0) = 5;
            *(unsigned short *)(hero + 0x1F0) = 5;
        }
        pathIndex = *(int *)(vars + 0x230);
        pathPoint = (Rec_42550 *)((pathIndex << 7) + (unsigned int)D_L20_001B308C);
        value = FastMatrixHelperA(pathPoint->pointX - *(float *)(self + 0x10), pathPoint->pointY - *(float *)(self + 0x14));
        StartMobyEffectFromEntry(self, value);

    } else {
        StartMobyEffectFromEntry(self, FastMatrixHelperA(
            *(float *)(hero + 0x80) - *(float *)(self + 0x10),
            *(float *)(hero + 0x84) - *(float *)(self + 0x14)));
    }

    if (*(float *)(self + 0x18) <= *(float *)(vars + 0xE0)) {
        float velocity;
        *(float *)(self + 0x18) = *(float *)(vars + 0xE0);
        PlayMobySound(0, 0, self);
        velocity = *(float *)(vars + 0xF8) * -D_L20_001B2134;
        *(float *)(vars + 0xF8) = velocity;
        if (velocity < 0.016666668f) {
            *(int *)(vars + 0xF8) = 0;
            return 1;
        }
    }
    return 0;
}
