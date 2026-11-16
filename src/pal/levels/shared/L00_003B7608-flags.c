#include "include_asm.h"

#include "common.h"
typedef int Quadword_L00_003B3E78 __attribute__((mode(TI)));
typedef union {
    Quadword_L00_003B3E78 bits;
    float f[4];
} Vec4_L00_003B3E78;
typedef struct {
    unsigned char pad0[4];
    int w4;
    unsigned char pad8[2];
    unsigned char ba;
    unsigned char bb;
} Sub_L00_003B3E78;
extern float g_spark_ring_axis_z __attribute__((sda));
extern int g_spark_ring_spark_count __attribute__((sda));
extern unsigned short g_spark_ring_effect_id __attribute__((sda));
extern float g_spark_ring_speed __attribute__((sda));
extern float g_spark_ring_size __attribute__((sda));
extern int g_spark_ring_spin_param __attribute__((sda));
extern unsigned char g_spark_ring_alpha __attribute__((sda));
extern float g_spark_ring_scale __attribute__((sda));
extern float g_camera_l00_position[];
extern void FastVecSub(void *, void *, void *);
extern float IntToFloat(int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern int math_random_int_below(int);
extern u8 *part_spawn_spinning_spark_pal(u8 *p, float fa, float fb, float fc, float fd, int v, void *local, int a3, int t0);

/* Spawns a ring of sparks around the object, spread evenly around the line to the camera. (PAL: 50
 * Hz timings) */
void part_l00_spawn_spark_ring_pal(u8 *obj)
{
    Vec4_L00_003B3E78 axis;
    Vec4_L00_003B3E78 to_camera;
    Vec4_L00_003B3E78 direction;
    Vec4_L00_003B3E78 velocity;
    float step;
    int i;

    axis.bits = 0;
    axis.f[2] = g_spark_ring_axis_z;
    FastVecSub(&to_camera, g_camera_l00_position, obj + 0x10);
    step = 6.2831855f / IntToFloat(g_spark_ring_spark_count);
    for (i = 0; i < g_spark_ring_spark_count; i++) {
        u8 *effect;
        int spin;
        math_apply_axis_rotation_to_quat(&direction, &axis, &to_camera, (float)i * step);
        vec_scale_to_length(&velocity, &direction, g_spark_ring_speed * 0.020000001f);
        spin = math_random_int_below(16);
        if (math_random_int_below(2) != 0) {
            spin = -spin;
        }
        effect = part_spawn_spinning_spark_pal(obj + 0x10, 0.5f, 1.0f, g_spark_ring_scale, g_spark_ring_size * 210000.0f, spin, &velocity, g_spark_ring_spin_param, 0);
        if (effect != 0) {
            Sub_L00_003B3E78 *sub = (Sub_L00_003B3E78 *)(effect + 0x20);
            *(unsigned short *)(effect + 0xA) = g_spark_ring_effect_id;
            sub->w4 = 2;
            sub->ba = g_spark_ring_alpha;
            sub->bb = effect[0xA];
        }
    }
}
