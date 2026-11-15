#include "common.h"

typedef struct HrugisEffectCamera {
    char pad00[0x140];
    float position[4];
} HrugisEffectCamera;

extern HrugisEffectCamera D_L22_001B9B40;
extern int D_L22_001AF374 __attribute__((sda));
extern int D_L22_001AF378 __attribute__((sda));
extern void func_0029FCC0(void *, int, void *);
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

/* Spawns one particle near the object (or one of its sockets) with a random spread and speed, flying off at a random angle. */
void func_L22_003A6640(char *object, int socketIndex, int override, float radius) {
    float initial[4], point[4], velocity[4];
    float heading, speed, tilt, yaw;
    unsigned char *particle;
    unsigned char *data;

    if (socketIndex != -1) {
        TransformMobyJointToWorld(object, socketIndex, initial);
    } else {
        if (override != 0)
            qcopy(initial, &override);
        else
            qcopy(initial, object + 0x10);
    }
    heading = FastMatrixHelperA(D_L22_001B9B40.position[0] - *(float *)(object + 0x10),
                            D_L22_001B9B40.position[1] - *(float *)(object + 0x14));
    point[0] = initial[0] + RandomSignedFloatRange(0, radius);
    point[1] = initial[1] + RandomSignedFloatRange(0, radius);
    point[2] = initial[2] + RandomSignedFloatRange(0, radius);
    speed = RandomFloatRange(radius * 0.01666666753590107f, radius * 2 * 0.01666666753590107f);
    tilt = RandomSignedFloatRange(0, 1.396263599395752f);
    yaw = FastAddRotations(heading, RandomSignedFloatRange(0, 1.5707964897155762f));
    BuildSphericalOffset(velocity, speed, yaw, tilt);
    particle = SpawnSpinningSparkParticle(0, 1.0f, 1.01f, radius * 210000.0f,
                             point, -1, velocity, 0x101010, 0);
    if (particle != 0) {
        particle[3] = 0x44;
        *(short *)(particle + 0xA) = RandomIntRange(D_L22_001AF374, D_L22_001AF378);
        particle[9] = FloatToInt(4.0f) + 0x60;
        data = particle + 0x20;
        *(float *)(data + 0x1C) = IntToFloat(RandomIntRange(1, 10));
        *(int *)(data + 4) = 3;
        data[0xA] = 0x7F;
        data[0xB] = particle[0xA];
    }
}
