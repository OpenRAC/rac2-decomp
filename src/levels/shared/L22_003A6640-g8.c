#include "common.h"

typedef struct HrugisEffectCamera {
    char pad00[0x140];
    float position[4];
} HrugisEffectCamera;

extern HrugisEffectCamera g_hero_l22_state_block;
extern int g_scatter_particle_value_min __attribute__((sda));
extern int g_scatter_particle_value_max __attribute__((sda));
extern void moby_transform_joint_to_world(void *, int, void *);
extern float mat_fast_helper_a(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern unsigned char *SpawnSpinningSparkParticle(float, float, float, float,
                                    void *, int, void *, int, int);
extern int math_random_int_range(int, int);
extern int FloatToInt(float);
extern float IntToFloat(int);

/* Spawns one particle near the object (or one of its sockets) with a random spread and speed, flying off at a random angle. */
void part_spawn_scatter(char *object, int socket_index, int override, float radius) {
    float initial[4], point[4], velocity[4];
    float heading, speed, tilt, yaw;
    unsigned char *particle;
    unsigned char *data;

    if (socket_index != -1) {
        moby_transform_joint_to_world(object, socket_index, initial);
    } else {
        if (override != 0)
            qcopy(initial, &override);
        else
            qcopy(initial, object + 0x10);
    }
    heading = mat_fast_helper_a(g_hero_l22_state_block.position[0] - *(float *)(object + 0x10),
                            g_hero_l22_state_block.position[1] - *(float *)(object + 0x14));
    point[0] = initial[0] + math_random_signed_float_range(0, radius);
    point[1] = initial[1] + math_random_signed_float_range(0, radius);
    point[2] = initial[2] + math_random_signed_float_range(0, radius);
    speed = math_random_float_range(radius * 0.01666666753590107f, radius * 2 * 0.01666666753590107f);
    tilt = math_random_signed_float_range(0, 1.396263599395752f);
    yaw = FastAddRotations(heading, math_random_signed_float_range(0, 1.5707964897155762f));
    vec_build_spherical_offset(velocity, speed, yaw, tilt);
    particle = SpawnSpinningSparkParticle(0, 1.0f, 1.01f, radius * 210000.0f,
                             point, -1, velocity, 0x101010, 0);
    if (particle != 0) {
        particle[3] = 0x44;
        *(short *)(particle + 0xA) = math_random_int_range(g_scatter_particle_value_min, g_scatter_particle_value_max);
        particle[9] = FloatToInt(4.0f) + 0x60;
        data = particle + 0x20;
        *(float *)(data + 0x1C) = IntToFloat(math_random_int_range(1, 10));
        *(int *)(data + 4) = 3;
        data[0xA] = 0x7F;
        data[0xB] = particle[0xA];
    }
}
