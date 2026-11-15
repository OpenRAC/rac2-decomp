/* func_L16_00418E38: own -G8 unit (default game profile by name). */
#include "common.h"

/* Per-segment tuning tables (three entries each), read $gp-relative through explicit SDATA
   views: the blend limits in degrees and the blend gains per second, then the weight above
   which the next segment starts blending. */
extern f32 D_L16_001B1C40_gp[] SDATA(D_L16_001B1C40);
extern f32 D_L16_001B1C50_gp[] SDATA(D_L16_001B1C50);
extern f32 D_L16_001B1C5C __attribute__((sda));
extern char D_L16_001B9B00[];
extern void func_002AA548(char *, char *, f32, f32, f32, f32);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282D30(char *, char *, f32);
extern void func_00282CC0(char *, char *, char *);
extern void func_L16_00419140(char *);
extern s32 func_002A9640(char *, u32, s32);
extern void func_0032C700(char *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
extern void func_0029F338(char *);
extern s32 func_00277258(char *, s32, char *, f32);
extern void func_002A7750(char *, s32, s32);
extern void func_00282F20(char *, char *, f32);
extern void func_0032DA58(char *, char *, char *, f32);
extern s32 func_002A8C28(char *, char *, f32, u32, s32, s32, s32, f32, f32);

/* Blends three motion segments and finishes with the object's destruction effect. */
void func_L16_00418E38(char *self) {
    char delta[16] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);
    char *current;
    char *next;
    f32 *weight, *rate;
    f32 *w;
    s32 i;
    switch (*(u8 *)(self + 0x20)) {
    case 0:
        qcopy(self + 16, vars);
        i = 0;
        current = vars;
        next = vars + 16;
        weight = (f32 *)(vars + 0x40);
        rate = (f32 *)(vars + 0x50);
        w = weight;
        for (; i < 3; current += 16, weight++, next += 16, rate++, w++, i++) {
            if (i == 0 || weight[-1] > D_L16_001B1C5C)
                StepValueTowardTarget((char *)w, (char *)rate, 1.0f,
                              D_L16_001B1C40_gp[i] * 0.00027777778450399637f,
                              D_L16_001B1C40_gp[i] * 0.00027777778450399637f,
                              D_L16_001B1C50_gp[i] * 0.01666666753590107f);
            FastVecSub(delta, next, current);
            FastVecScale(delta, delta, *weight);
            FastVecAdd(self + 16, self + 16, delta);
        }
        EmitSnivelakFallingParticles(self);
        if (FindOwnedEffectSlot(self, 0x10000, 0)) {
            SpawnExplosion(self + 16, 0, 0, 0, 0, 20, 45, 1, 1, 0, 0, 0, 1.0f, 20.0f);
            MarkMobySpawned(self);
        } else if (*(f32 *)(vars + 0x48) >= 1.0f || (*(f32 *)(vars + 0x44) >= 0.5f && TestPointAgainstCollision(self + 16, 0, self, 0.5f)))
            SetMobyState(self, 1, -1);
        break;
    case 1:
    {
        char *endPosition = self + 16;
        FastVecSub(delta, D_L16_001B9B00, endPosition);
        vec_scale_to_length(delta, delta, 1.0f);
        SpawnBlastEffectMoby(self, endPosition, delta, 0.0f);
        /* radius 2.0f is the first FP argument: each register bank keeps its order */
        SweepCollisionFromObject(self, endPosition, 2.0f, 0x10001, 0, 1, 0, 5.0f, 1.0f);
        MarkMobySpawned(self);
        break;
    }
    }
}
