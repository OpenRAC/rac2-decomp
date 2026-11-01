#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern void func_002AFFD8(void *, void *, int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_002AF000(void *, float, float, float);
extern void func_00282F20(void *, void *, float);
extern void *func_PAL_L00_00340CA0(float, void *, void *, int, int, int, int, float, int, int, int);
extern void *func_L00_0033C0D0(void *, void *, void *, void *, int);
extern char D_L00_001B1418 __attribute__((sda));
extern char D_L00_001B13F8 __attribute__((sda));
extern char D_L00_001B1408 __attribute__((sda));
extern char D_L00_001B1428 __attribute__((sda));

/* Emits three effect particles at the object, then four spawns along its velocity at rising heights. */
void func_PAL_L00_0041C528(char *object)
{
    Vec up, velocity, pos, pos2, pos3, pos4;
    char *state = *(char **)(object + 0x68);
    int i;
    float angle, random, life, speed, spread, frame;

    func_002AFFD8(object + 0x10, &up, 1);
    if (*(int *)(state + 4) != 0)
        return;
    frame = 0.020000001f;
    for (i = 0; i < 3; i++) {
        angle = func_002A7878(-0.9599311948f, -1.3962635994f);
        random = func_002A7940();
        speed = func_002A7878(0.0f, 0.5f);
        spread = 0.3f;
        frame = 0.020000001f;
        speed *= frame;
        func_002AF000(&velocity, speed, random, angle);
        life = func_002A7878(0.65f, 0.85f) * 210000.0f;
        pos.f[0] = *(float *)(object + 0x10) + func_002A78D8(0.0f, spread);
        pos.f[1] = *(float *)(object + 0x14) + func_002A78D8(0.0f, spread);
        pos.f[2] = *(float *)(object + 0x18) + func_002A78D8(0.0f, spread);
        func_PAL_L00_00340CA0(life, &pos, &velocity, 0x4F808080, 0x08101010, func_002A7820(29, 42), 1, 0.5f, 1, -1, 1);
    }
    func_002AFFD8(object + 0x10, &velocity, 1);
    func_00282F20(&velocity, &velocity, 0.2f);
    qcopy_nc(&pos, object + 0x10);
    pos.f[2] += func_002A7878(0.1f, 0.4f);
    func_L00_0033C0D0(object, &pos, &velocity, &D_L00_001B1418, func_002A77E0(2));
    qcopy_nc(&pos2, object + 0x10);
    pos2.f[2] += func_002A7878(0.9f, 1.2f);
    func_L00_0033C0D0(object, &pos2, &velocity, &D_L00_001B13F8, func_002A77E0(2));
    qcopy_nc(&pos3, object + 0x10);
    pos3.f[2] += func_002A7878(0.8f, 1.5f);
    func_L00_0033C0D0(object, &pos3, &velocity, &D_L00_001B1408, func_002A77E0(2));
    qcopy_nc(&pos4, object + 0x10);
    func_L00_0033C0D0(object, &pos4, &velocity, &D_L00_001B1428, func_002A77E0(2));
}
