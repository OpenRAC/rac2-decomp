#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern int D_L03_001A8F00;
extern char D_L03_001A8F20[] __attribute__((sda)), D_L03_001BFDE0[], D_00188660[];
extern float D_L03_001B0590 __attribute__((sda)), D_L03_001B0594 __attribute__((sda));
extern void func_0029F338(void *);
extern int func_002AD0E0(void *,void *,void *,void *,void *,void *);
extern void func_00282CF0(void *,void *,void *),func_002AFDD8(void *,void *,void *,int);
extern void func_00282D08(void *,void *,void *,float),func_00282CC0(void *,void *,void *);
extern float func_002AA2E8(void *,float,float);
extern void func_00283098(void *,void *,void *);
extern void func_002A7750(void *,int,int),func_002A8C00(void *,void *,int,void *,float);
extern int func_002761F8(void *,void *,int,void *,void *);
extern float func_002A7940(void),func_002A7878(float,float),func_00283180(float),func_00283198(float);
extern void func_L03_003D0FC8(void *,void *,void *),func_002A7A00(void *,float,float);
extern int func_002A77E0(int),func_002E5CF8(int,int,void *),func_00282948(void *);
extern void func_002E59F8(int),func_L00_002E6CF0(void *,void *),func_L03_003D0AE0(void *);

/* Interpolates the emitter position, keeps it relative to its attachment,
 * emits particles while active, and releases its sound and object after fading. */
void func_L03_003D04E0(char *moby) {
    float offsetStep[4], rayStart[4], rayEnd[4], hit[12], spawnVec[4], spawnVel[4];
    char *vars = P(moby, 0x68), *position, *soundSlot;
    float angle, speed;

    if (D_L03_001A8F00 == 2) {
        MarkMobySpawned(moby);
        return;
    }
    position = moby + 0x10;
    if (P(vars, 0x40)) {
        TransformPointAndRotationByParent(moby, P(vars, 0x40), position, moby + 0xF0, position, moby + 0xF0);
        FastVecSub(position, position, P(vars, 0x40) + 0x10);
        TransformVectorByObjectOrGiven(P(vars, 0x40), position, position, 0);
    }
    lerp_vector(offsetStep, vars, vars + 0x10, F(vars, 0x20));
    FastVecAdd(position, position, offsetStep);
    ApproachValue(vars + 0x20, 1.0f, F(vars, 0x24));
    if (P(vars, 0x40)) {
        matrix_mul_vec3(position, position, P(vars, 0x40) + 0xC0);
        FastVecAdd(position, position, P(vars, 0x40) + 0x10);
    }
    switch ((unsigned char)moby[0x20]) {
    case 0:
        I(vars, 0x3C) = -1;
        if (F(vars, 0x20) > 0.5f)
            SetMobyState(moby, 1, -1);
        break;
    case 1:
        qcopy(rayStart, position);
        qcopy(rayEnd, position);
        rayEnd[2] -= F(vars, 0x20) * 5.0f;
        make_hit_descriptor(hit, moby, 0x10001, D_L03_001A8F20, (float)I(vars, 0x38));
        if (CollLine(rayStart, rayEnd, 0, moby, hit) && !P(vars, 0x40)) {
            angle = RandomAngle();
            speed = RandomFloatRange(0, 0.5f) * (1.0f / 60.0f);
            spawnVec[0] = FastSinOrCosA(angle) * speed;
            spawnVec[1] = FastSinOrCosB(angle) * speed;
            spawnVec[2] = 0;
            spawnVec[2] = RandomFloatRange(1, 2) * (1.0f / 60.0f);
            SpawnEmitterParticlePair(moby, D_L03_001BFDE0, spawnVec);
        }
        if (!P(vars, 0x40) && !RandomIntBelow(2)) {
            qcopy(spawnVec, position);
            spawnVec[2] -= RandomFloatRange(0, 5);
            RandomDirectionVector(spawnVel, 0, 1.0f / 30.0f);
            SpawnEmitterParticlePair(moby, spawnVec, spawnVel);
        }
        soundSlot = (char *)(I(vars, 0x3C) * 0x70);
        soundSlot = (char *)((int)soundSlot + (int)gSoundState);
        if (P(soundSlot, 0x88) != moby || !((unsigned char *)soundSlot)[0x74])
            I(vars, 0x3C) = PlayMobySound(0, 4, moby);
        if (F(vars, 0x34) < 1)
            ApproachValue(vars + 0x34, 1, 1.0f / 15.0f);
        if (FastFloatHelperD(vars + 0x28))
            SetMobyState(moby, 2, -1);
        break;
    case 2:
        ApproachValue(vars + 0x34, 0, 1.0f / 30.0f);
        if (F(vars, 0x34) <= 0) {
            int handle = I(vars, 0x3C);
            if (handle != -1) {
                int offset = handle * 0x70;
                char *slot = gSoundState + offset;
                if (P(slot, 0x88) == moby && ((unsigned char *)slot)[0x74])
                    StopSoundVoice(handle);
            }
            I(vars, 0x3C) = -1;
            MarkMobySpawned(moby);
            return;
        }
        break;
    }
    F(vars, 0x2C) += D_L03_001B0590 * (1.0f / 60.0f);
    if (F(vars, 0x2C) > 1)
        F(vars, 0x2C) -= 1;
    else if (F(vars, 0x2C) < 1)
        F(vars, 0x2C) += 1;
    F(vars, 0x30) += D_L03_001B0594 * (1.0f / 60.0f);
    if (F(vars, 0x30) > 1)
        F(vars, 0x30) -= 1;
    AddDrawCallbackToList1(DrawGlowingBeamEffect, moby);
}
