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

void func_L22_003A6640(char *object, int a1, int a2, float radius) {
    float initial[4], point[4], velocity[4];
    float heading, speed, tilt, yaw;
    unsigned char *particle;
    unsigned char *data;

    if (a1 != -1) {
        func_0029FCC0(object, a1, initial);
    } else {
        if (a2 != 0)
            qcopy(initial, &a2);
        else
            qcopy(initial, object + 0x10);
    }
    heading = func_00283248(D_L22_001B9B40.position[0] - *(float *)(object + 0x10),
                            D_L22_001B9B40.position[1] - *(float *)(object + 0x14));
    point[0] = initial[0] + func_002A78D8(0, radius);
    point[1] = initial[1] + func_002A78D8(0, radius);
    point[2] = initial[2] + func_002A78D8(0, radius);
    speed = func_002A7878(radius * 0.01666666753590107f, radius * 2 * 0.01666666753590107f);
    tilt = func_002A78D8(0, 1.396263599395752f);
    yaw = FastAddRotations(heading, func_002A78D8(0, 1.5707964897155762f));
    func_002AF000(velocity, speed, yaw, tilt);
    particle = SpawnSpinningSparkParticle(0, 1.0f, 1.01f, radius * 210000.0f,
                             point, -1, velocity, 0x101010, 0);
    if (particle != 0) {
        particle[3] = 0x44;
        *(short *)(particle + 0xA) = func_002A7820(D_L22_001AF374, D_L22_001AF378);
        particle[9] = FloatToInt(4.0f) + 0x60;
        data = particle + 0x20;
        *(float *)(data + 0x1C) = IntToFloat(func_002A7820(1, 10));
        *(int *)(data + 4) = 3;
        data[0xA] = 0x7F;
        data[0xB] = particle[0xA];
    }
}
