#include "common.h"

extern int D_L18_001B05D4 __attribute__((sda));
extern float D_L18_001B05C8 __attribute__((sda));
extern float D_L18_001B05CC __attribute__((sda));
extern float D_L18_001B05D0 __attribute__((sda));
typedef struct ParticleSettings {
    s32 *colorRange;
    s16 *sizeRange;
    s16 *frameRange;
    u32 unknown0C;
    s32 frameCount;
    f32 speed;
} ParticleSettings;
/* The shared particle constructor reads this complete 24-byte settings record. */
extern ParticleSettings D_L18_001B05B0 __attribute__((sda));
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern void func_002ACB48(void *, float);
extern void func_00282F20(void *, void *, float);
extern void *func_L02_003449D8(void *, void *, void *, int, int);

/* Spawns a random number of particles (one more than a draw bounded by D_L18_001B05D4)
   around the object's position (+0x10): each from the position jittered by
   D_L18_001B05C8 and a direction from the vector at +0xC0, scaled by minus a random
   value between D_L18_001B05CC and D_L18_001B05D0 divided by 60, with two more draws. */
void func_L18_003FB620(u8 *object)
{
    float position[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    int count;
    int i;

    count = RandomIntBelow(D_L18_001B05D4) + 1;
    for (i = 0; i < count; i++) {
        qcopy(position, object + 0x10);
        AddRandomOffsetToVector(position, D_L18_001B05C8);
        vec_scale_to_length(direction, object + 0xC0,
                      -(RandomFloatRange(D_L18_001B05CC, D_L18_001B05D0) * 0.016666668f));
        SpawnEnemyRecord(position, direction, &D_L18_001B05B0, RandomIntBelow(2),
                          RandomIntRange(-2, 2));
    }
}
