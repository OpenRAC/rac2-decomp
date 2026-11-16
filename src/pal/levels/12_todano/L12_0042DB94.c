#include "include_asm.h"


#include "common.h"
extern s32 *g_path_zone_table[];
extern s32 *g_path_zone_table[];
extern s32 CollLine(void *from, void *to, s32 mode, void *self, s32 flags);
extern s32 *g_path_zone_table[];
extern f32 math_fabs(f32);
extern f32 vec_distance_xy(void *, void *);
extern s32 math_random_int_range(s32, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern s32 g_spark_timer_min __attribute__((sda));
extern u8 g_zone_event_flag;
extern s32 math_random_int_below(s32);
extern s32 FloatToInt(f32);
extern void math_random_planar_offset(f32 *, f32);
extern u8 *part_spawn_spinning_spark_pal(void *, f32, f32, f32, s32, void *, f32, u32, s32);

/* Retail tests the first allocation again after its second and third calls;
 * preserve that behavior instead of changing the test to the newer pointer. */
/* Sprays three small spark particles upward from the object (PAL: 50 Hz timings). */
void part_spawn_three_sparks_pal(u8 *self)
{
    u8 *vars = *(u8 **)(self + 0x68);
    f32 pos[4];
    f32 velocity[4];
    u8 *first_spark;
    u8 *next_spark;

    qcopy(pos, self + 0x10);
    pos[2] = *(f32 *)(vars + 0x7C);
    math_random_planar_offset(velocity, 0.6f);
    velocity[2] = 0.10000001f;
    first_spark = part_spawn_spinning_spark_pal(pos, 0.1f, 1.0f, 0.9f, math_random_int_below(16), velocity, 420000.0f, 0xDF202020, 0);
    if (first_spark) {
        u8 *data = first_spark + 0x20;
        *(u16 *)(first_spark + 10) = 8;
        first_spark[9] = FloatToInt(4.0f) + 0x70;
        *(s32 *)(data + 4) = 2;
        data[10] = 0xDF;
        data[11] = first_spark[10];
        first_spark[3] = 0x44;
    }
    math_random_planar_offset(velocity, 0.6f);
    velocity[2] = 0.10000001f;
    next_spark = part_spawn_spinning_spark_pal(pos, 0.1f, 1.0f, 0.9f, math_random_int_below(16), velocity, 420000.0f, 0xDF208080, 0);
    if (first_spark) {
        u8 *data = next_spark + 0x20;
        *(u16 *)(next_spark + 10) = 8;
        next_spark[9] = FloatToInt(4.0f) + 0x70;
        *(s32 *)(data + 4) = 2;
        data[10] = 0xDF;
        data[11] = next_spark[10];
        next_spark[3] = 0x48;
    }
    math_random_planar_offset(velocity, 0.40000004f);
    velocity[2] = 0.10000001f;
    next_spark = part_spawn_spinning_spark_pal(pos, 0.1f, 1.0f, 0.9f, math_random_int_below(16), velocity, 420000.0f, 0xDF808080, 0);
    if (first_spark) {
        u8 *data = next_spark + 0x20;
        *(u16 *)(next_spark + 10) = 8;
        next_spark[9] = FloatToInt(4.0f) + 0x70;
        *(s32 *)(data + 4) = 2;
        data[10] = 0xDF;
        data[11] = next_spark[10];
        next_spark[3] = 0x44;
    }
}



