#include "names.h"

/* A cleared velocity vector is adjusted and copied before the three emissions. */
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float v[4]; } Vector;
extern float math_random_float_range(float low, float high);
extern void moby_transform_joint_to_world(char *object, int joint, void *out);
extern void *part_spawn_object_relative_particle(char *object, void *position, void *velocity, void *parameters, int mode);
extern char g_drift_particle_desc_a __attribute__((sda));
extern char g_drift_particle_desc_b __attribute__((sda));
extern char g_drift_particle_desc_c __attribute__((sda));
/* Same body as func_L00_003D4958, with this function's own callees. */
extern char ref_L00_003EC078_00 __attribute__((sda));
extern char ref_L00_003EC078_01 __attribute__((sda));
extern char ref_L00_003EC078_02 __attribute__((sda));
/* Shoots out three small downward puffs from the object when it is visible. */
void synthenoid_emit_exhaust(char *object)
{
    Vector position, velocity, temporary;
    if (*(unsigned char *)(object + 0x31) != 0) {
        temporary.q = 0;
        temporary.v[2] = -(math_random_float_range(1.0f, 2.0f) * 0.016666668f);
        velocity.q = temporary.q;
        moby_transform_joint_to_world(object, 0, &position);
        part_spawn_object_relative_particle(object, &position, &velocity, &ref_L00_003EC078_00, 1);
        part_spawn_object_relative_particle(object, &position, &velocity, &ref_L00_003EC078_01, 1);
        part_spawn_object_relative_particle(object, &position, &velocity, &ref_L00_003EC078_02, 1);
    }
}
