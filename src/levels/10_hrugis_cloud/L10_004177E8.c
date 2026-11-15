#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct HrugisEffectCamera {
    char pad00[0x140];
    float position[4];
} HrugisEffectCamera;

extern HrugisEffectCamera D_L10_001B9540;
extern float func_00283248(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern void func_002AF000(void *, float, float, float);
extern unsigned char *func_002BDCE8(float, float, float, float,
                                    void *, int, void *, int, int);
extern int func_002A7820(int, int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);

/* Throws out one dark puff of smoke from the object, flying away at a random angle. A
   nonzero joint makes it a slower, flatter puff. */
void func_L10_004177E8(char *object, int joint, float radius) {
    float initial[4], point[4], velocity[4];
    float heading, speed, tilt, yaw;
    unsigned char *particle;
    unsigned char *data;
    int one = 1;

    *(TI128 *)initial = *(TI128 *)(object + 0x10);
    heading = FastMatrixHelperA(D_L10_001B9540.position[0] - *(float *)(object + 0x10),
                            D_L10_001B9540.position[1] - *(float *)(object + 0x14));
    point[0] = initial[0] + RandomSignedFloatRange(0, radius);
    point[1] = initial[1] + RandomSignedFloatRange(0, radius);
    point[2] = initial[2] + RandomSignedFloatRange(0, radius);
    if (joint != 0) {
        speed = RandomFloatRange(radius * 0.01666666753590107f, radius * 2 * 0.01666666753590107f);
        tilt = RandomSignedFloatRange(0, 1.396263599395752f);
    } else {
        speed = RandomFloatRange(radius * 2 * 0.01666666753590107f, radius * 0.0666666701436043f);
        tilt = RandomSignedFloatRange(0.6981317996978760f, 0.8726646900177002f);
    }
    yaw = FastAddRotations(heading, RandomSignedFloatRange(0, 1.5707964897155762f));
    BuildSphericalOffset(velocity, speed, yaw, tilt);
    particle = SpawnSpinningSparkParticle(0, 1.0f, 1.01f, radius * 210000.0f,
                             point, -one, velocity, 0x101010, 0);
    if (particle != 0) {
        particle[3] = 0x44;
        *(short *)(particle + 0xA) = RandomIntRange(40, 70);
        particle[9] = FloatToInt(4.0f) + 0x60;
        data = particle + 0x20;
        *(float *)(data + 0x1C) = IntToFloat(RandomIntRange(1, 10));
        *(int *)(data + 4) = 3;
        data[0xA] = 0x7F;
        data[0xB] = particle[0xA];
    }
}
