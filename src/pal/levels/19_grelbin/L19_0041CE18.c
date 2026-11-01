#include "include_asm.h"

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
extern void func_00281EB8(void *, int, int, float, int, float, float);
extern void func_002C7970(void *, void *, int, int, int, int, int, int, float, float, float);

void func_PAL_L19_0041CE18(char *obj)
{
    float mat[16] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    char *state = *(char **)(obj + 0x68);
    float primaryRadius, secondaryRadius, phase;
    int particleType;

    func_0029FC20(obj, 0, mat);
    qcopy(pos, mat + 12);
    func_00282F20(scaled, mat, 0.25f);
    func_00282CC0(pos, pos, scaled);
    pos[2] += 2.0f;
    primaryRadius = *(float *)(state + 0x228) * 2.0f;
    phase = func_002A7940();
    func_00281EB8(pos, 0x31, 0x60804020, primaryRadius, 1, 0.08f, phase);
    secondaryRadius = *(float *)(state + 0x228);
    secondaryRadius *= 1.5f;
    func_00281EB8(pos, 0x31, 0x80808080, secondaryRadius, 1, 0.08f, func_002A7940());
    *(float *)(state + 0x228) += 0.03f;
    if (*(float *)(state + 0x228) < 1.15f) {
        float *particlePos = point;
        float *particleVel = vel;
        int i;

        for (i = 19; i >= 0; i--) {
            particleType = func_00283CF0(func_002A78D8(2.0f, 5.0f));
            func_002A7988(particlePos, 2.5f, 3.0f);
            func_00282CC0(particlePos, particlePos, pos);
            func_00282CF0(particleVel, pos, particlePos);
            func_00282F20(particleVel, particleVel, 0.060000002f);
            func_002C7970(particlePos, particleVel, 25, 0x804020, particleType, 0, 127, 5,
                          func_002A7878(0.2f, 0.5f) * 210000.0f, 126000.0078125f, 0.0f);
        }
    }
}

