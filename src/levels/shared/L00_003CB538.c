#include "include_asm.h"
#include "names.h"
typedef struct {
    float v[3];
    float scale;
    void *owner;
    float f14;
    int f18;
    int f1C;
    float f20;
    int f24;
    float f28;
    float f2C;
} Rec_3CB538;

extern Rec_3CB538 *D_L00_001B2AD4 __attribute__((section(".sdata")));
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern void func_00282F20(void *, void *, float);
extern int func_001163B0(void);

/* Starts one new particle in the first free slot, with a random direction, life time and size. */
void func_L00_003CB538(void *owner)
{
    Rec_3CB538 *particle;
    int i;

    for (i = 0; i < 64; i++) {
        particle = &D_L00_001B2AD4[i];
        if (particle->owner == 0) {
            particle->v[0] = RandomFloatRange(-1.0f, 1.0f);
            particle->v[1] = RandomFloatRange(-1.0f, 1.0f);
            particle->v[2] = RandomFloatRange(-1.0f, 1.0f);
            vec_scale_to_length(particle, particle, particle->f14);
            particle->f1C = particle->f18 = RandomIntRange(0x14, 0x32);
            particle->f20 = RandomFloatRange(-1.0f, 1.0f);
            particle->owner = owner;
            particle->f24 = 0;
            particle->f28 = (Rand() & 1) ? -1.0f : 1.0f;
            particle->f2C = 1.0f;
            particle->f14 = RandomFloatRange(0.7f, 0.9f);
            return;
        }
    }
}
