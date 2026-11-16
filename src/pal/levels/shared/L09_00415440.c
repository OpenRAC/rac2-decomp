#include "include_asm.h"




#include "common.h"
extern s32 math_random_int_below(s32);
extern u8 *part_spawn_spinning_spark_pal(void *, f32, f32, f32, s32, void *, f32, u32, s32);
extern s32 FloatToInt(f32);

/* Spawn two colored particles and one white particle below the object. */
void part_spawn_below_object_pal(u8 *moby)
{
    f32 vel[4] __attribute__((aligned(16)));
    f32 pos[4] __attribute__((aligned(16)));
    s32 count;
    u8 *first;
    vel[0] = 0.0f;
    vel[2] = -0.5f;
    vel[3] = 1.0f;
    vel[1] = 0.0f;
    count = math_random_int_below(16);
    if (math_random_int_below(2)) count = -count;
    qcopy(pos, moby + 0x10);
    pos[2] -= 0.25f;
    first = part_spawn_spinning_spark_pal(pos, 0.1f, 1.0f, 0.9f, count, vel, 420000.0f, 0xdf204080, 0);
    if (first) {
        u8 *data = first + 0x20;
        *(s16 *)(first + 0xa) = 8;
        first[9] = FloatToInt(4.0f) + 112;
        *(s32 *)(data + 4) = 2;
        data[0xa] = 0xdf;
        data[0xb] = first[0xa];
    }
    {
        u8 *particle = part_spawn_spinning_spark_pal(pos, 0.1f, 1.0f, 0.9f, count, vel, 420000.0f, 0xdf204080, 0);
        if (particle) {
            u8 *data = particle + 0x20;
            /* Retail updates the first particle here as well. */
            *(s16 *)(first + 0xa) = 8;
            first[9] = FloatToInt(4.0f) + 112;
            *(s32 *)(data + 4) = 2;
            data[0xa] = 0xdf;
            data[0xb] = first[0xa];
        }
    }
    {
        u8 *particle = part_spawn_spinning_spark_pal(pos, 0.05f, 1.0f, 0.97f, 16, vel, 210000.0f, 0xdfffffff, 0);
        if (particle) {
            u8 *data = particle + 0x20;
            particle[9] = FloatToInt(4.0f) + 112;
            *(s16 *)(particle + 0xa) = 4;
            particle[8] = math_random_int_below(255);
            *(s32 *)(data + 4) = 2;
            data[0xa] = 0xdf;
            data[0xb] = first[0xa];
        }
    }
}
