#include "include_asm.h"

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
extern ParticleSettings D_L18_001B05B0 __attribute__((sda));
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern void vec_add_random_offset(void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void *enemy_spawn_record(void *, void *, void *, int, int);

/* Spawns a random number of particles (one more than a draw bounded by D_L18_001B05D4)
   around the object's position (+0x10): each from the position jittered by
   D_L18_001B05C8 and a direction from the vector at +0xC0, scaled by minus a random
   value between D_L18_001B05CC and D_L18_001B05D0 divided by 60, with two more draws. */
void func_PAL_L18_003FF768(u8 *object)
{
    float position[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    int count;
    int i;

    count = math_random_int_below(D_L18_001B05D4) + 1;
    for (i = 0; i < count; i++) {
        qcopy(position, object + 0x10);
        vec_add_random_offset(position, D_L18_001B05C8);
        vec_scale_to_length(direction, object + 0xC0,
                      -(math_random_float_range(D_L18_001B05CC, D_L18_001B05D0) * 0.020000001f));
        enemy_spawn_record(position, direction, &D_L18_001B05B0, math_random_int_below(2),
                          math_random_int_range(-2, 2));
    }
}
