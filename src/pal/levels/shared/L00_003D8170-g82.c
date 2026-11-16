#include "include_asm.h"
#include "names.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float v[4]; } Vector;
extern float math_random_float_range(float low, float high);
extern void moby_transform_joint_to_world(char *object, int joint, void *out);
extern void *part_spawn_object_relative_particle(char *object, void *position, void *velocity, void *parameters, int mode);
extern char g_drift_particle_desc_a __attribute__((sda));
extern char g_drift_particle_desc_b __attribute__((sda));
extern char g_drift_particle_desc_c __attribute__((sda));

/* While the object is active, spawns three drifting particles that fall slowly from its first joint (PAL). */
void part_emit_drifting_from_moby_pal(char *object)
{
    Vector position, velocity, temporary;
    if (*(unsigned char *)(object + 0x31) != 0) {
        temporary.q = 0;
        temporary.v[2] = -(math_random_float_range(1.0f, 2.0f) * 0.020000001f);
        velocity.q = temporary.q;
        moby_transform_joint_to_world(object, 0, &position);
        part_spawn_object_relative_particle(object, &position, &velocity, &g_drift_particle_desc_a, 1);
        part_spawn_object_relative_particle(object, &position, &velocity, &g_drift_particle_desc_b, 1);
        part_spawn_object_relative_particle(object, &position, &velocity, &g_drift_particle_desc_c, 1);
    }
}
