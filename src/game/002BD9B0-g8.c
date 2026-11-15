#include "include_asm.h"
#include "common.h"

typedef int TI __attribute__((mode(TI)));

extern int func_00282978(short *p);
extern void func_002B9180(void *p);
extern float func_00283CE0(int n);
extern int func_002A9568(int a, int b, float f);
extern void func_00282CC0(void *out, void *a, void *b);
extern float func_002A7878(float lo, float hi);
extern int func_002A7820(int lo, int hi);
extern float func_00282DF0(void *v);
extern void func_00282F20(void *dst, void *src, float len);
extern void func_00282D30(void *dst, void *src, float scale);
extern void *func_002BD8B0(void *a0, void *a1, int a2, int a3, int a4, int a5, float f);
extern int D_001B1688 __attribute__((sda));

/* Moves a spark particle and fades its size and colour over its life. It also drops smaller sparks behind it and disappears when its time is up. */
void func_002BD9B0(char *particle)
{
    char *motion = particle + 0x20;
    float invLife;
    float speed;
    float savedPos[4] __attribute__((aligned(16)));
    float sparkVel[4] __attribute__((aligned(16)));
    float randomVec[4] __attribute__((aligned(16)));

    if (FastDecTimer((short *)(particle + 0xA))) {
        KillParticle(particle);
        return;
    }
    invLife = 1.0f / IntToFloat(*(short *)(motion + 0x18));
    *(float *)(particle + 0xC) = IntToFloat(*(short *)(particle + 0xA)) * *(float *)(motion + 0x1C) * invLife;
    *(int *)(particle + 4) = ForwardTwoValuesAndAmount(*(int *)(motion + 0x14), *(int *)(motion + 0x10), IntToFloat(*(short *)(particle + 0xA)) * invLife);
    FastVecAdd((particle + 0x10), (particle + 0x10), motion);
    *(float *)(motion + 8) -= 0.001f;
    qcopy(savedPos, particle + 0x10);
    if (*(short *)(motion + 0x1A) != 0 && (gGameTime & 1)) {
        *(TI *)randomVec = 0;
        randomVec[0] = RandomFloatRange(-1.0f, 1.0f);
        randomVec[1] = RandomFloatRange(-1.0f, 1.0f);
        randomVec[2] = RandomFloatRange(-1.0f, 1.0f);
        *(TI *)sparkVel = *(TI *)randomVec;
        speed = FastVecLength(motion);
        vec_scale_to_length(sparkVel, sparkVel, speed * RandomFloatRange(0.21f, 0.25f));
        FastVecAdd(sparkVel, sparkVel, motion);
        FastVecScale(sparkVel, sparkVel, RandomFloatRange(0.75f, 0.95f));
        SpawnTrailingSparkParticle((particle + 0x10), sparkVel, *(int *)(particle + 4), *(int *)(motion + 0x14), RandomIntRange(15, 20), 0, *(float *)(particle + 0xC));
    } else {
        FastVecScale(motion, motion, 0.96f);
    }
}
