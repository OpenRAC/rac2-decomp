#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern float D_L17_001AF320 __attribute__((sda)), D_L17_001AF324 __attribute__((sda));
extern char D_00188660[];
extern int func_00282948(void *);
extern float func_002A7878(float, float);
extern void func_00283410(void *, void *);
extern void func_00282C88(void *);
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CD8(void *, void *, void *);
extern int func_002A77E0(int);
extern void func_002C02F0(void *, void *, int, void *, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002E59F8(int);
/* Updates the moby that sprays a burst of randomly scattered particles: it waits, sprays for a
   while, then stops its sound and starts over. */
void func_L17_003A14A0(unsigned char *obj)
{
    float matrix[16];
    Vec position, velocity, step, jitter, random;
    char *state = *(char **)(obj + 0x68);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(int *)(state + 0xC) = *(int *)(state + 0x14);
        obj[0x30] = 255;
        obj[0x20] = 1;
        *(float *)(obj + 0x18) -= 3.0f;
        break;
    case 1:
        *(int *)(state + 0x10) = -1;
        if (FastFloatHelperD(state + 0xC)) {
            *(int *)(state + 0xC) = *(int *)(state + 4);
            obj[0x20] = 2;
        }
        break;
    case 2:
        random.q = 0;
        random.f[0] = RandomFloatRange(-1.0f, 1.0f);
        random.f[1] = RandomFloatRange(-1.0f, 1.0f);
        random.f[2] = RandomFloatRange(-1.0f, 1.0f);
        jitter.q = random.q;
        qcopy(&position, obj + 0x10);
        euler_to_matrix(matrix, obj + 0xF0);
        ClearVector128(&velocity);
        velocity.f[0] = *(float *)state * (D_L17_001AF320 * 3.0f) * 0.016666668f;
        FastVecScale(&jitter, &jitter, velocity.f[0] * D_L17_001AF324);
        transform_vector(&velocity, &velocity, matrix);
        add_vectors(&random, &velocity, &jitter);
        if (*(int *)(state + 0xC) >= 10 || RandomIntBelow(10 - *(int *)(state + 0xC)) == 0) {
            FastVecScale(&step, &velocity, 0.33f);
            SpawnScaledSmokeParticle(&position, &velocity, 0x40, obj, 0x80, 0x1FF);
        }
        if (*(int *)(state + 0xC) >= 10 || RandomIntBelow(10 - *(int *)(state + 0xC)) == 0) {
            FastVecAdd(&position, &position, &step);
            SpawnScaledSmokeParticle(&position, &velocity, 0x40, obj, 0x80, 0x1FF);
        }
        if (FastFloatHelperD(state + 0xC)) {
            int index;
            *(int *)(state + 0xC) = *(int *)(state + 8);
            obj[0x20] = 1;
            index = *(int *)(state + 0x10);
            if (index != -1) {
                char *slot = gSoundState + index * 0x70;
                if (*(char **)(slot + 0x88) == obj && *(unsigned char *)(slot + 0x74))
                    StopSoundVoice(index);
            }
            *(int *)(state + 0x10) = -1;
        }
        break;
    }
}
