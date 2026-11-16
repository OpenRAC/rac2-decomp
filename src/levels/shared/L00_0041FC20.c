#include "common.h"

typedef struct { float x,y,z,w; } ImpactVector;
extern float g_camera_l00_position[];
extern float g_default_vector[] MACRO_ADDR;
extern float math_random_float_range(float, float), math_random_angle(void), math_random_signed_float_range(float, float);
extern int math_random_int_range(int, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void *part_spawn_spinning_particle(float, float, void *, void *, int, int, int, int, int, int, int);
extern void *part_spawn_pulled_particle(float, void *, float, int, int, int, int, float *, int, int, short, int);

/* Both effect constructors replace the copied position W before consumption;
 * 0033E888 likewise replaces velocity W with its rotation value. */
/* Spawns a burst of blue sparks and flashes where a shot hits something. */
void part_l00_spawn_impact_spark_burst_2(float *position, void *unused, int shortLife)
{
    ImpactVector velocity, offset, point;
    int i = 1;
    float pitch, yaw, life;
    do {
        pitch = math_random_float_range(-0.9599312f, -1.3962636f);
        yaw = math_random_angle();
        vec_build_spherical_offset(&velocity, math_random_float_range(0.0f, 0.5f) * 0.016666668f, yaw, pitch);
        FastVecSub(&offset, g_camera_l00_position, position);
        vec_scale_to_length(&offset, &offset, 0.15f);
        FastVecAdd(position, position, &offset);
        life = math_random_float_range(30000.0f, 60000.0f);
        point.x = position[0] + math_random_signed_float_range(0.0f, 0.15f);
        point.y = position[1] + math_random_signed_float_range(0.0f, 0.15f);
        point.z = position[2] + math_random_signed_float_range(0.0f, 0.15f);
        if (shortLife)
            part_spawn_spinning_particle(life, 0.5f, &point, &velocity, 0x4F93E5FF, 0x102434EE,
                              math_random_int_range(10, 20), 1, -1, -1, 1);
        else
            part_spawn_spinning_particle(life, 0.5f, &point, &velocity, 0x4F93E5FF, 0x102434EE,
                              math_random_int_range(25, 60), 1, -1, -1, 1);
    } while (--i >= 0);
    part_spawn_pulled_particle(0.1f, position, 1.05f, 40, 0x64FFFFFF, 2, 4, g_default_vector, 0, 1, 6, 1);
    part_spawn_pulled_particle(0.4f, position, 2.05f, 30, 0x3C388EF7, 2, 0, g_default_vector, 0, 0, 6, 1);
    part_spawn_pulled_particle(0.15f, position, 1.65f, 40, 0x32388EF7, 0, 2, g_default_vector, 0, 4, 6, 1);
    part_spawn_pulled_particle(0.5f, position, 2.35f, 27, 0x3C0063F7, 2, 0, g_default_vector, 3, 0, 6, 1);
    part_spawn_pulled_particle(0.3f, position, 1.75f, 27, 0x1E0063F7, 1, -2, g_default_vector, 3, 4, 6, 1);
    part_spawn_pulled_particle(1.25f, position, 1.7f, 70, 0x2D002DFF, 0, 0, g_default_vector, 4, 3, 6, 1);
    part_spawn_pulled_particle(0.9f, position, 0.7f, 10, 0x3C787878, 2, 2, g_default_vector, 0, 2, 6, 1);
    part_spawn_pulled_particle(1.7f, position, 0.7f, 10, 0x3C787878, 2, -1, g_default_vector, 1, 2, 6, 1);
    part_spawn_pulled_particle(2.0f, position, 1.5f, 10, 0x23787878, 2, 1, g_default_vector, 1, 2, 6, 1);
}
