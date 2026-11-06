/* func_PAL_L03_00422624, the PAL copy of func_L03_0041D258: the same C at 50 Hz, with the random timers
   scaled, the 20-frame blends at 17, the 60-frame test at 50, the rates and speeds rescaled, and case 5
   of the second switch clearing the s16 fields state+0x356 and state+0x354 as in USA v2.00. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
extern void func_002AA2E8(void *, float, float);
extern void func_PAL_L03_00422F18(void *), func_PAL_L03_00423128(void *), func_PAL_L03_004233F0(void *);
extern int func_002B3890(void *), func_002B3868(void *);
extern int func_002A7820(int, int), func_00282978(void *);
extern void func_002A7750(void *, int, int), func_PAL_002A7E68(void *, int, int, int);
extern float func_00282E80(void *, void *), func_00283248(float, float), func_002A7878(float, float), func_002A78D8(float, float);
extern int func_002B1C20(void *, void *), func_PAL_002AF6C0(void *, float);
extern void func_00283098(void *, void *, void *), func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, float);
extern void func_PAL_002AD288(void *, void *, int, float, float);
extern void func_L03_003268C0(void *, int, int, int, int, int, int, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int), func_PAL_002A7650(void *, int, int), func_0029F338(void *);
/* Integer and FP arguments retain their independent EE register-bank order. */
extern void func_002AAA00(void *, float, void *, float, float, float, int);
extern void func_0029FCC0(void *, int, void *), func_L01_0031A278(void *, void *, float, float, float);
extern void func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern void func_PAL_L03_003D5A98(void *, void *, void *, int);
extern u8 D_00189EA0[], D_L03_00188660[];
extern u8 D_L03_001A8F20[] __attribute__((sda));
extern float D_L03_001B1BCC __attribute__((sda));
extern float D_L03_001B1BD0 __attribute__((sda));
extern float D_L03_001B1BD4 __attribute__((sda));
/* The transform reads one complete vector; the file uses -G16 for its address. */
extern u8 D_L03_001B1BE0[16] __attribute__((sda));

/* Advance the path actor's behaviour, movement, animation and attack effects. */
void func_PAL_L03_00422624(u8 *entity)
{
    u8 *state = *(u8 **)(entity + 0x68);
    float spawnPosition[4] __attribute__((aligned(16)));
    float targetPosition[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float effectPosition[4] __attribute__((aligned(16)));
    int flags, hit;

    func_PAL_L03_00422F18(entity);

    switch (entity[0x95]) {
    case 0:
        if (func_002B3890(entity))
            *(s16 *)(state + 0x332) = ((s32)(func_002A7820(20, 60)) * 5 + 2) / 6;
        if ((*(int *)(state + 0x204) == 1 || *(s16 *)(state + 0x336) != 0) && func_00282978(state + 0x332)) {
            func_002A7750(entity, 3, 2);
            if (entity[0x43] != 1)
                func_PAL_002A7E68(entity, 1, 0, 17);
            *(s16 *)(state + 0x336) = 0;
        }
        break;
    case 1:
        if (func_002B3890(entity))
            *(s16 *)(state + 0x330) = ((s32)(func_002A7820(120, 150)) * 5 + 2) / 6;
        if (*(int *)(state + 0x204) == 1 || *(s16 *)(state + 0x336)) {
            func_002A7750(entity, 5, 2);
            if (entity[0x43] != 4)
                func_PAL_002A7E68(entity, 4, 0, 17);
            *(s16 *)(state + 0x336) = 0;
        } else if (!*(s16 *)(state + 0x330)) {
            if (func_00282E80(entity + 0x10, D_00189EA0) > 24.0f) {
                func_002A7750(entity, 1, 0);
                if (entity[0x43] != 0)
                    func_PAL_002A7E68(entity, 0, 0, 17);
            } else {
                func_002A7750(entity, 4, 2);
                if (entity[0x43] != 3)
                    func_PAL_002A7E68(entity, 3, 0, 17);
            }
        }
        break;
    case 2:
        if (func_002B3890(entity))
            *(int *)(state + 0x34C) = ((s32)(func_002A7820(400, 500)) * 5 + 2) / 6;
        if (*(int *)(state + 0x204) != 1 && entity[0x20] == 5 && !*(int *)(state + 0x34C)) {
            func_002A7750(entity, 2, 1);
            if (entity[0x43] != 2)
                func_PAL_002A7E68(entity, 2, 0, 17);
        }
        break;
    case 3:
        flags = func_002B1C20(entity, state + 0x50);
        if ((flags & 1) || (entity[0x43] == 8 && func_PAL_002AF6C0(entity, 8.0f))) {
            func_00283098(spawnPosition, D_L03_001B1BE0, entity + 0xC0);
            func_00282CC0(spawnPosition, spawnPosition, entity + 0x10);
            func_PAL_002AD288(entity, spawnPosition, -1, 0.5f, 13.0f);
            func_00282CF0(targetPosition, entity + 0x10, D_00189EA0);
            targetPosition[2] = 0;
            func_00282F20(targetPosition, targetPosition, 0.120000005f);
            func_L03_003268C0(entity, 0xA0D, 5, 0, 0, 0, 0, D_L03_001A8F20);
            func_002E5CF8(6, 0, entity);
            if (*(int *)(state + 0x350) != -1) {
                u8 *sound = D_L03_00188660 + *(int *)(state + 0x350) * 0x70;
                if (*(u8 **)(sound + 0x88) == entity && sound[0x74])
                    func_002E59F8(*(int *)(state + 0x350));
            }
            *(int *)(state + 0x350) = -1;
            func_PAL_002A7650(entity, 0, 3);
            func_0029F338(entity);
            return;
        }
        if (flags & 2) {
            func_002A7750(entity, 5, 2);
            if (entity[0x43] != 4)
                func_PAL_002A7E68(entity, 4, 0, 17);
        }
        break;
    }

    switch (entity[0x20]) {
    case 1:
    case 2:
        break;
    case 3:
        {
            u8 *rotation = entity + 0xF8;
            float angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(entity + 0x10),
                                        *(float *)(state + 0x1F4) - *(float *)(entity + 0x14));

            func_002AAA00(rotation, angle, state + 0x1B4,
                          0.005026549f, 0.005026549f, 0.25132746f, 0);
        }
        func_002A7750(entity, 4, -1);
        if (entity[0x43] != 3)
            func_PAL_002A7E68(entity, 3, 0, 17);
        break;
    case 4:
        {
            u8 *rotation = entity + 0xF8;
            float angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(entity + 0x10),
                                        *(float *)(state + 0x1F4) - *(float *)(entity + 0x14));

            func_002AAA00(rotation, angle, state + 0x1B4,
                          0.005026549f, 0.005026549f, 0.25132746f, 0);
        }
        func_PAL_L03_00423128(entity);
        if (*(u16 *)(entity + 0x96) > 50) {
            func_002A7750(entity, 5, -1);
            if (entity[0x43] != 4)
                func_PAL_002A7E68(entity, 4, 0, 17);
        }
        break;
    case 5:
        if (func_002B3868(entity)) {
            *(float *)(state + 0x33C) = 4.0f;
            *(float *)(state + 0x348) = func_002A7878(3.5f, 4.5f) * 0.020000001f;
            *(s16 *)(state + 0x356) = 0;
            *(s16 *)(state + 0x354) = 0;
        }
        {
            u8 *rotation = entity + 0xF8;
            float angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(entity + 0x10),
                                        *(float *)(state + 0x1F4) - *(float *)(entity + 0x14));

            func_002AAA00(rotation, angle, state + 0x1B4,
                          0.005026549f, 0.005026549f, 0.25132746f, 0);
        }
        func_PAL_L03_00423128(entity);
        {
            float first = func_00283248(*(float *)(state + 0x33C), D_L03_001B1BCC);
            float second = D_L03_001B1BD0;
            float value;

            *(float *)(state + 0x280) = first;
            value = func_00283248(*(float *)(state + 0x33C), second);
            *(float *)(state + 0x308) = value;
            *(float *)(state + 0x288) = -value;
            *(float *)(state + 0x300) = -*(float *)(state + 0x280);
        }
        func_002AA2E8(state + 0x33C, 16.0f, *(float *)(state + 0x348));
        hit = 0;
        if (func_PAL_002AF6C0(entity, 1.0f)) {
            hit = 1;
            func_0029FCC0(entity, 2, spawnPosition);
        } else if (func_PAL_002AF6C0(entity, 11.0f)) {
            hit = 1;
            func_0029FCC0(entity, 3, spawnPosition);
        }
        if (hit) {
            float *target = targetPosition;
            float spread = func_002A78D8(0, 0.5f);

            func_L01_0031A278(entity, target, *(float *)(state + 0x33C), spread, 0);
            func_00282CF0(direction, targetPosition, spawnPosition);
            func_00282F20(direction, direction, D_L03_001B1BD4 * 0.020000001f);
            func_002A8C28(entity, spawnPosition, 1, 0, 1, 0, 0.6660000085830688f, (float)state[0x34], 1.0f);
            func_PAL_L03_003D5A98(entity, spawnPosition, direction, state[0x34]);
            *(Quad *)effectPosition = 0;
            effectPosition[0] = 2.5f;
            effectPosition[2] = 0.5f;
            func_00283098(effectPosition, effectPosition, entity + 0xC0);
            func_00282CC0(effectPosition, effectPosition, entity + 0x10);
            func_002A8C28(entity, effectPosition, 1, 0, 1, 0, 1.5f, (float)state[0x34], 3.0f);
        }
        if (entity[0x60] & 2) {
            *(s16 *)(state + 0x356) = 0;
            *(s16 *)(state + 0x354) = 0;
        }
        if (*(float *)(state + 0x33C) >= 12.0f) {
            func_002A7750(entity, 6, -1);
            if (entity[0x43] != 5)
                func_PAL_002A7E68(entity, 5, 0, 17);
        }
        break;
    case 6:
        {
            u8 *rotation = entity + 0xF8;
            float angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(entity + 0x10),
                                        *(float *)(state + 0x1F4) - *(float *)(entity + 0x14));

            func_002AAA00(rotation, angle, state + 0x1B4,
                          0.005026549f, 0.005026549f, 0.25132746f, 0);
        }
        func_PAL_L03_00423128(entity);
        if (entity[0x60] & 2) {
            func_002A7750(entity, 5, -1);
            if (entity[0x43] != 4)
                func_PAL_002A7E68(entity, 4, 0, 17);
        }
        break;
    }
    func_PAL_L03_004233F0(entity);
}
