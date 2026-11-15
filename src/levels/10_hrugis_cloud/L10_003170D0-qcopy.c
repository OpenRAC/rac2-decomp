#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct HrugisEffectCamera {
    char pad00[0x140];
    float position[4];
} HrugisEffectCamera;

extern HrugisEffectCamera D_L10_001B9540;
extern unsigned char *D_L10_001FF36C;
extern float func_003091E8(float, float);
extern float func_003352B8(float, float);
extern float func_00335258(float, float);
extern float func_00309B38(float, float);
extern void func_0033D090(void *, float, float, float);
extern unsigned char *func_00348DA0(float, float, float, float,
                                    void *, int, void *, int, int);
extern int func_00335200(int, int);
extern int func_00309C90(float);
extern float func_00309C80(int);

/* Throws out one dark puff of smoke from the object, flying away at a random angle. The
   radius sets how far and how fast it goes. */
void func_L10_00417A38(char *object, int joint, float radius) {
    float initial[4], point[4], velocity[4];
    float heading, speed, tilt, yaw;
    unsigned char *particle;
    unsigned char *data;

    *(TI128 *)initial = *(TI128 *)(object + 0x10);
    heading = func_003091E8(D_L10_001B9540.position[0] - *(float *)(object + 0x10),
                            D_L10_001B9540.position[1] - *(float *)(object + 0x14));
    point[0] = initial[0] + func_003352B8(0, radius);
    point[1] = initial[1] + func_003352B8(0, radius);
    point[2] = initial[2] + func_003352B8(0, radius);
    speed = func_00335258(radius * 0.008333333767950535f,
                          radius * 0.01666666753590107f);
    tilt = func_003352B8(0, 1.396263599395752f);
    yaw = func_00309B38(heading, func_003352B8(0, 1.5707964897155762f));
    func_0033D090(velocity, speed, yaw, tilt);
    particle = func_00348DA0(0, 1.0f, 1.01f, radius * 210000.0f,
                             point, -1, velocity, 0x307F7F7F, 0);
    if (particle != 0) {
        particle[3] = 0x48;
        *(short *)(particle + 0xA) = func_00335200(40, 70);
        particle[9] = func_00309C90(4.0f) + 0x60;
        data = particle + 0x20;
        *(float *)(data + 0x1C) = func_00309C80(func_00335200(1, 10));
        *(int *)(data + 4) = 3;
        data[0xA] = 0x7F;
        data[0xB] = particle[0xA];
        particle[2] = D_L10_001FF36C[1];
    }
}
