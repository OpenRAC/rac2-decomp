#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef float f32;
typedef int V4 __attribute__((mode(TI)));

typedef struct {
    u8 pad0[0x98];
    f32 yaw;
    u8 pad1[0x1B4 - 0x9C];
    f32 speed;
    u8 pad2[0x324 - 0x1B8];
    f32 f324;
    u8 pad3[0x22C3 - 0x328];
    u8 flag;
} Owner_002B4208;

typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vec4;
extern Owner_002B4208 g_hero_state;
extern V4 g_drive_velocity_view;
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void transform_vector(void *, void *, void *);
extern void vec_build_spherical_offset(void *, float, float, float);
/* Works out the direction the hero is pushed in from an angle and the hero speed, and saves it. */
void hero_compute_push_direction(float angle)
{
    Vec4 result;
    float direction[4];
    float useAngle;
    float length;
    float zero;
    Owner_002B4208 *hero = &g_hero_state;
    useAngle = hero->yaw;
    if (angle <= 3.1415927f)
        useAngle = angle;
    length = hero->speed;
    if (hero->flag != 0) {
        zero = 0.0f;
        direction[0] = math_fast_sin_or_cos_a(zero) * length;
        direction[1] = math_fast_sin_or_cos_b(zero) * length;
        direction[2] = zero;
        transform_vector(direction, direction, hero);
        *(V4 *)&result = *(V4 *)direction;
    } else {
        vec_build_spherical_offset(&result, length, useAngle, hero->f324);
    }
    g_drive_velocity_view = *(V4 *)&result;
}
