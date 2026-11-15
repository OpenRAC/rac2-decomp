#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct HrugisEffectCamera {
    char pad00[0x140];
    float position[4];
} HrugisEffectCamera;

extern HrugisEffectCamera D_L10_001B9540;
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

/* Throws out one dark puff of smoke from the object, flying away at a random angle. A
   nonzero joint makes it a slower, flatter puff. */
void part_spawn_smoke_puff(char *object, int joint, float radius) {
    float initial[4], point[4], velocity[4];
    float heading, speed, tilt, yaw;
    unsigned char *particle;
    unsigned char *data;
    int one = 1;

    *(TI128 *)initial = *(TI128 *)(object + 0x10);
    heading = mat_fast_helper_a(D_L10_001B9540.position[0] - *(float *)(object + 0x10),
                            D_L10_001B9540.position[1] - *(float *)(object + 0x14));
    point[0] = initial[0] + math_random_signed_float_range(0, radius);
    point[1] = initial[1] + math_random_signed_float_range(0, radius);
    point[2] = initial[2] + math_random_signed_float_range(0, radius);
    if (joint != 0) {
        speed = math_random_float_range(radius * 0.01666666753590107f, radius * 2 * 0.01666666753590107f);
        tilt = math_random_signed_float_range(0, 1.396263599395752f);
    } else {
        speed = math_random_float_range(radius * 2 * 0.01666666753590107f, radius * 0.0666666701436043f);
        tilt = math_random_signed_float_range(0.6981317996978760f, 0.8726646900177002f);
    }
    yaw = FastAddRotations(heading, math_random_signed_float_range(0, 1.5707964897155762f));
    vec_build_spherical_offset(velocity, speed, yaw, tilt);
    particle = SpawnSpinningSparkParticle(0, 1.0f, 1.01f, radius * 210000.0f,
                             point, -one, velocity, 0x101010, 0);
    if (particle != 0) {
        particle[3] = 0x44;
        *(short *)(particle + 0xA) = math_random_int_range(40, 70);
        particle[9] = FloatToInt(4.0f) + 0x60;
        data = particle + 0x20;
        *(float *)(data + 0x1C) = IntToFloat(math_random_int_range(1, 10));
        *(int *)(data + 4) = 3;
        data[0xA] = 0x7F;
        data[0xB] = particle[0xA];
    }
}
