#include "common.h"

extern int D_001A79F0;
typedef struct { char pad[0x68]; char *state; char rest[0x94]; } EffectOwner;
extern EffectOwner *D_L05_001B251C;
extern int D_L05_001B1024 __attribute__((sda));
/* The resident level index is also read through its GP address view. */
extern int current_level_gp SDATA(D_001A79F0);
extern float D_L05_001A8F20[4] __attribute__((sda));
extern int func_002ACCA8(void *, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern void func_00281EB8(void *, int, int, int, float, float, float);
extern char *func_002BDCE8(void *, float, float, int, void *, int, float, float, int);
extern int func_002A7820(int, int);
extern int func_00283CF0(float);

/* Spawns and moves the glowing particles that trail behind the object, on some levels only. */
void func_L05_00419370(char *object)
{
    float step[4];
    char *state = *(char **)(object + 0x68);
    char *otherVars;
    char *axis;
    float randomValue, spriteSize;
    char *effect, *detail;
    int kind;

    if (gCurrentMapIndex == 5 || gCurrentMapIndex == 25) {
        otherVars = ((EffectOwner *)((char *)D_L05_001B251C + (*(int *)(state + 0xA4) << 8)))->state;
        if (gCurrentMapIndex == 25 ||
            (!IsPointInsideUnitSphereOfRecord(object + 0x10, *(int *)(otherVars + 4)) &&
             !IsPointInsideUnitSphereOfRecord(object + 0x10, *(int *)(otherVars + 8)) &&
             !IsPointInsideUnitSphereOfRecord(object + 0x10, *(int *)(otherVars + 12)) &&
             !IsPointInsideUnitSphereOfRecord(object + 0x10, *(int *)(otherVars + 16)))) {
            char *particle;
            float *life;
            int i;

            axis = object + 0xC0;
            particle = state + 0xB0;
            life = (float *)(state + 0x1B0);
            for (i = 15; i >= 0; i--) {
                if (*life <= 0.0f) {
                    qcopy(particle, axis);
                    *(float *)(particle) += RandomFloatRange(-0.2f, 0.2f);
                    *(float *)(particle + 4) += RandomFloatRange(-0.2f, 0.2f);
                    *(float *)(particle + 8) += RandomFloatRange(-0.2f, 0.2f);
                    vec_scale_to_length(particle, particle, RandomFloatRange(24.0f, 30.0f));
                    FastVecAdd(particle, particle, object + 0x10);
                    *life = RandomFloatRange(11.0f, 14.0f);
                }
                qcopy(step, axis);
                randomValue = RandomFloatRange(0.15f, 0.25f);
                vec_scale_to_length(step, step, -randomValue);
                *life -= randomValue;
                FastVecAdd(particle, particle, step);
                spriteSize = RandomFloatRange(0.07f, 0.12f);
                randomValue = RandomFloatRange(0.0f, 1.0f);
                DrawBillboardQuad_00281EB8(particle, 0x47, 0x7F7F6464, 0, spriteSize, 0.0f, randomValue);
                life++;
                particle += 16;
            }
        }
    }
    if (D_L05_001B1024 && current_level_gp == 15) {
        float *life = (float *)(state + 0x1B0);
        int i;

        axis = object + 0xC0;
        kind = 0x44;
        state += 0xB0;
        for (i = 3; i >= 0; i--) {
            if (*life <= 0.0f) {
                qcopy(state, axis);
                *(float *)state += RandomFloatRange(-0.2f, 0.2f);
                *(float *)(state + 4) += RandomFloatRange(-0.2f, 0.2f);
                *(float *)(state + 8) += RandomFloatRange(-0.2f, 0.2f);
                vec_scale_to_length(state, state, RandomFloatRange(15.0f, 30.0f));
                FastVecAdd(state, state, object + 0x10);
                *life = RandomFloatRange(10.0f, 30.0f);
            }
            qcopy(step, axis);
            randomValue = RandomFloatRange(0.15f, 0.25f);
            vec_scale_to_length(step, step, -randomValue);
            *life -= randomValue;
            FastVecAdd(state, state, step);
            effect = SpawnSpinningSparkParticle(state, 2.0f, 1.03f, 1, D_L05_001A8F20, 0x0A786E64, 1.045f, 210000.0f, 0);
            if (effect) {
                effect[3] = kind;
                *(short *)(effect + 10) = RandomIntRange(40, 70);
            }
            effect = SpawnSpinningSparkParticle(state, 1.8f, 1.03f, 1, D_L05_001A8F20, 0x0AADA196, 1.045f, 210000.0f, 0);
            if (effect) {
                effect[3] = kind;
                detail = effect + 0x20;
                *(short *)(effect + 10) = RandomIntRange(40, 70);
                effect[9] = FloatToInt(4.0f) + 0x40;
                *(float *)(detail + 0x1C) = 20.0f;
                *(int *)(detail + 4) = 3;
                detail[10] = 0x7F;
                detail[11] = effect[10];
            }
            state += 16;
            life++;
        }
    }
}
