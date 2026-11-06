/* func_PAL_L10_0041C7A0, the PAL copy of func_L10_00417A38: the same C, where rename-macro func_002BDCE8 becomes func_PAL_002BE9A8; scale (func_00335200(1, 10)); scale func_00335200(40, 70); rename func_003091E8 becomes func_00283248; rename func_003352B8 becomes func_002A78D8; rename func_00335258 becomes func_002A7878; rename func_00309B38 becomes func_00283B98; rename func_0033D090 becomes func_002AF000; rename func_00348DA0 becomes func_PAL_002BE9A8; rename func_00335200 becomes func_002A7820; rename func_00309C90 becomes func_00283CF0; rename func_00309C80 becomes func_00283CE0. */
typedef int TI128 __attribute__((mode(TI)));

typedef struct HrugisEffectCamera {
    char pad00[0x140];
    float position[4];
} HrugisEffectCamera;

extern HrugisEffectCamera D_L10_001B9540;
extern unsigned char *D_L10_001FF36C;
extern float func_00283248(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern void func_002AF000(void *, float, float, float);
extern unsigned char *func_PAL_002BE9A8(float, float, float, float,
                                    void *, int, void *, int, int);
extern int func_002A7820(int, int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);

void func_PAL_L10_0041C7A0(char *object, int joint, float radius) {
    float initial[4], point[4], velocity[4];
    float heading, speed, tilt, yaw;
    unsigned char *particle;
    unsigned char *data;

    *(TI128 *)initial = *(TI128 *)(object + 0x10);
    heading = func_00283248(D_L10_001B9540.position[0] - *(float *)(object + 0x10),
                            D_L10_001B9540.position[1] - *(float *)(object + 0x14));
    point[0] = initial[0] + func_002A78D8(0, radius);
    point[1] = initial[1] + func_002A78D8(0, radius);
    point[2] = initial[2] + func_002A78D8(0, radius);
    speed = func_002A7878(radius * 0.010000001f,
                          radius * 0.020000001f);
    tilt = func_002A78D8(0, 1.396263599395752f);
    yaw = func_00283B98(heading, func_002A78D8(0, 1.5707964897155762f));
    func_002AF000(velocity, speed, yaw, tilt);
    particle = func_PAL_002BE9A8(0, 1.0f, 1.01f, radius * 210000.0f,
                             point, -1, velocity, 0x307F7F7F, 0);
    if (particle != 0) {
        particle[3] = 0x48;
        *(short *)(particle + 0xA) = (((int)(func_002A7820(40, 70)) * 5 + 2) / 6);
        particle[9] = func_00283CF0(4.0f) + 0x60;
        data = particle + 0x20;
        *(float *)(data + 0x1C) = func_00283CE0(((int)((func_002A7820(1, 10))) * 5 + 2) / 6);
        *(int *)(data + 4) = 3;
        data[0xA] = 0x7F;
        data[0xB] = particle[0xA];
        particle[2] = D_L10_001FF36C[1];
    }
}
