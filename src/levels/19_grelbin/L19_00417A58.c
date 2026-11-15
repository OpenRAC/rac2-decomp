#include "common.h"

extern float func_002A7878(float, float);
extern void func_0029FC20(void *, int, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_002A7940(void);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern void func_002A7988(void *, float, float);
/* The integer and floating argument banks retain their respective orders. */
extern void func_00281EB8(void *, int, int, float, int, float, float);
extern void func_002C7970(void *, void *, int, int, int, int, int, int, float, float, float);

/* Draws the Leviathan's charge-up flash in front of it and shoots sparks outward while the flash grows. */
void func_L19_00417A58(char *moby)
{
    float bodyMatrix[16] __attribute__((aligned(16)));
    float muzzlePos[4] __attribute__((aligned(16)));
    float muzzleOffset[4] __attribute__((aligned(16)));
    float sparkVelBuf[4] __attribute__((aligned(16)));
    float sparkPosBuf[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    float primaryRadius, secondaryRadius, phase;
    int particleType;

    TransformMobyJointPoint(moby, 0, bodyMatrix);
    qcopy(muzzlePos, bodyMatrix + 12);
    vec_scale_to_length(muzzleOffset, bodyMatrix, 0.25f);
    FastVecAdd(muzzlePos, muzzlePos, muzzleOffset);
    muzzlePos[2] += 2.0f;
    primaryRadius = *(float *)(vars + 0x228) * 2.0f;
    phase = RandomAngle();
    DrawBillboardQuad_00281EB8(muzzlePos, 0x31, 0x60804020, primaryRadius, 1, 0.08f, phase);
    secondaryRadius = *(float *)(vars + 0x228);
    secondaryRadius *= 1.5f;
    DrawBillboardQuad_00281EB8(muzzlePos, 0x31, 0x80808080, secondaryRadius, 1, 0.08f, RandomAngle());
    *(float *)(vars + 0x228) += 0.03f;
    if (*(float *)(vars + 0x228) < 1.15f) {
        float *particlePos = sparkPosBuf;
        float *particleVel = sparkVelBuf;
        int i;

        for (i = 19; i >= 0; i--) {
            particleType = FloatToInt(RandomSignedFloatRange(2.0f, 5.0f));
            SpawnRandomDirectionEffect(particlePos, 2.5f, 3.0f);
            FastVecAdd(particlePos, particlePos, muzzlePos);
            FastVecSub(particleVel, muzzlePos, particlePos);
            vec_scale_to_length(particleVel, particleVel, 0.050000004f);
            SpawnFadingDriftParticle(particlePos, particleVel, 30, 0x804020, particleType, 0, 127, 5,
                          RandomFloatRange(0.2f, 0.5f) * 210000.0f, 126000.0078125f, 0.0f);
        }
    }
}
