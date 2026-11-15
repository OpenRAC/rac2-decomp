#include "names.h"
/* A cleared velocity vector is adjusted and copied before the three emissions. */
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float v[4]; } Vector;
extern float math_random_float_range(float low, float high);
extern void moby_transform_joint_to_world(char *object, int joint, void *out);
extern void part_spawn_object_relative_particle(char *object, void *position, void *velocity, void *parameters, int mode);
extern char D_L00_001B02E8 __attribute__((sda));
extern char D_L00_001B02F8 __attribute__((sda));
extern char D_L00_001B0308 __attribute__((sda));
/* When active, throws three small particle puffs from the moby with a gentle downward drift. */
void part_emit_drifting_from_moby(char *object)
{
    Vector position, velocity, temporary;
    if (*(unsigned char *)(object + 0x31) != 0) {
        temporary.q = 0;
        temporary.v[2] = -(math_random_float_range(1.0f, 2.0f) * 0.016666668f);
        velocity.q = temporary.q;
        moby_transform_joint_to_world(object, 0, &position);
        part_spawn_object_relative_particle(object, &position, &velocity, &D_L00_001B02E8, 1);
        part_spawn_object_relative_particle(object, &position, &velocity, &D_L00_001B02F8, 1);
        part_spawn_object_relative_particle(object, &position, &velocity, &D_L00_001B0308, 1);
    }
}
