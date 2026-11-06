/* func_PAL_L15_0043ABF0, the PAL copy of func_L15_00434F90: the same C with 50 Hz speeds and lifetimes. */
#include "include_asm.h"
#include "common.h"

typedef struct HrugisEffectCamera {
    char pad00[0x140];
    float position[4];
} HrugisEffectCamera;

extern HrugisEffectCamera D_L15_001B9680;
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

void func_PAL_L15_0043ABF0(char *object, int a1, int joint, float radius) {
    float initial[4], point[4], velocity[4];
    float heading, speed, tilt, yaw;
    unsigned char *particle;
    unsigned char *data;
    int one = 1;

    func_0029FCC0(object, a1, initial);
    heading = func_00283248(D_L15_001B9680.position[0] - *(float *)(object + 0x10),
                            D_L15_001B9680.position[1] - *(float *)(object + 0x14));
    point[0] = initial[0] + func_002A78D8(0, radius);
    point[1] = initial[1] + func_002A78D8(0, radius);
    point[2] = initial[2] + func_002A78D8(0, radius);
    if (joint != 0) {
        speed = func_002A7878(radius * 0.020000001f, radius * 2 * 0.020000001f);
        tilt = func_002A78D8(0, 1.396263599395752f);
    } else {
        speed = func_002A7878(radius * 2 * 0.020000001f, radius * 0.080000006f);
        tilt = func_002A78D8(0.6981317996978760f, 0.8726646900177002f);
    }
    yaw = func_00283B98(heading, func_002A78D8(0, 1.5707964897155762f));
    func_002AF000(velocity, speed, yaw, tilt);
    particle = func_002BDCE8(0, 1.0f, 1.01f, radius * 210000.0f,
                             point, -one, velocity, 0x101010, 0);
    if (particle != 0) {
        particle[3] = 0x44;
        *(short *)(particle + 0xA) = ((s32)(func_002A7820(40, 70)) * 5 + 2) / 6;
        particle[9] = func_00283CF0(4.0f) + 0x60;
        data = particle + 0x20;
        *(float *)(data + 0x1C) = func_00283CE0(((s32)(func_002A7820(1, 10)) * 5 + 2) / 6);
        *(int *)(data + 4) = 3;
        data[0xA] = 0x7F;
        data[0xB] = particle[0xA];
    }
}
