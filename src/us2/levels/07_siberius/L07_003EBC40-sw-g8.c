#include "include_asm.h"

#include "common.h"
#define FLOAT_AT(p, offset) (*(float *)((char *)(p) + (offset)))
#define INT_AT(p, offset) (*(int *)((char *)(p) + (offset)))
#define PTR_AT(p, offset) (*(char **)((char *)(p) + (offset)))
#define BYTE_AT(p, offset) (*(unsigned char *)((char *)(p) + (offset)))
extern int D_L07_001B1E08[] __attribute__((sda));
extern int D_L07_001C9780 NOT_SDA;
extern float D_L07_001B0BA0 __attribute__((sda)), D_L07_001B0BA4 __attribute__((sda));
typedef struct {
    char pad00[0x80];
    float position[4];
    char pad90[0x40];
    float targetPosition[4];
    char padE0[0x21B0];
    char *targetObject;
} SiberiusPlayerView;
extern SiberiusPlayerView D_00189E20;
extern char *D_L07_001B23CC[] __attribute__((sda));
extern float D_L07_001A8F20[] __attribute__((sda));
extern void func_L07_003EB2C0(void *);
extern void func_L07_003EBAB8(void *);
extern void func_L07_003EB700(void *);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_0029F338(void *);
extern void func_L00_00424A08(int, float, float);
extern void func_L00_00424A50(float, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_002AD330(void *, void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_003280C8(void *, void *, void *, int, int, float);
extern void func_00283098(void *, void *, void *);
extern void func_L02_003329C8(void *, void *, float, float);
extern void func_L07_00323038(void *, float, float, float);
extern int func_L02_00331440(void *, void *, int, float, float, float);
extern int func_L01_00322288(void *, float);
extern int func_L01_00321178(void *, void *);
extern int func_002A7820(int, int);
extern int func_002B1C20(void *, void *);
extern int func_002B3868(void *);
extern int func_US2_002AF9C8(void *, float);
extern int func_002A77E0(int);
extern int func_002A8508(int, int);
extern int func_002ACBC8(void *, int);
extern float func_00282DB0(void *, void *);
extern float func_00283180(float);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_002A78D8(float, float);
extern float func_00283B98(float, float);
extern float func_002A7878(float, float);

/* Update the phase and behavior state, then run the common update pass. */
void func_US2_L07_003EBC40(unsigned char *object)
{
    char *state = PTR_AT(object, 0x68);
    char *targetObject;
    float origin[4] __attribute__((aligned(16)));
    float targetPosition[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float unitDirection[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float angle;
    int hitFlags;

    if (D_L07_001B1E08[0] >= 2 && D_L07_001C9780 != INT_AT(state, 0x320)) return;
    func_L07_003EB2C0(object);
    switch (object[0x95]) {
    case 0:
        if (INT_AT(state, 0x2DC) == 1) func_002A7750(object, 5, 2);
        else if (INT_AT(state, 0x2D0)) {
            func_002A7750(object, 2, 1);
            INT_AT(state, 0x2D0) = 0;
            if (INT_AT(state, 0x2D4) < 300) INT_AT(state, 0x2D4) = func_002A7820(480, 600);
        }
        break;
    case 1:
        if (INT_AT(state, 0x2DC) == 1) func_002A7750(object, 5, 2);
        else if (INT_AT(state, 0x2D4) == 0) func_002A7750(object, 1, 0);
        break;
    case 2:
        func_L00_00424A08(0, D_L07_001B0BA0, 0.003000000026077032f);
        func_L00_00424A50(D_L07_001B0BA4, 0.003000000026077032f);
        if (INT_AT(state, 0x2DC) != 1) {
            func_002A7750(object, 2, 1);
            INT_AT(state, 0x2D4) = func_002A7820(580, 600);
        }
        break;
    case 3:
        hitFlags = func_002B1C20(object, state + 0x140);
        if (hitFlags & 1) {
            func_L07_003EBAB8(object);
            func_0029F338(object);
            return;
        }
        if (hitFlags & 2) {
            if (INT_AT(state, 0x2DC) == 1) func_002A7750(object, 5, 2);
            else {
                func_002A7750(object, 2, 1);
                INT_AT(state, 0x2D4) = func_002A7820(580, 600);
            }
        }
    }
    switch (object[0x20]) {
    case 1:
        if (func_002B3868(object) && object[0x43] != 2) func_002A7470(object, 2, 0, 20);
        break;
    case 2:
        if (func_002B3868(object) && object[0x43] != 5) func_002A7470(object, 5, 0, 20);
        break;
    case 3:
        if (func_002B3868(object) && object[0x43] != 20) func_002A7470(object, 20, 0, 20);
        if (func_US2_002AF9C8(object, 17.0f)) {
            func_0029FCC0(object, 4, origin);
            targetObject = PTR_AT(state, 0x220);
            if (targetObject == D_00189E20.targetObject) {
                qcopy(targetPosition, D_00189E20.targetPosition);
                if (PTR_AT(state, 0x314)) {
                    func_002AD330(object, PTR_AT(state, 0x314), targetPosition, axis);
                    func_00282CC0(targetPosition, targetPosition, axis);
                }
            } else if (targetObject) {
                qcopy(targetPosition, targetObject + 0x10);
                targetPosition[2] += FLOAT_AT(targetObject, 0xC) * 0.0009765625f;
            } else qcopy(targetPosition, state + 0x210);
            func_00282CF0(unitDirection, targetPosition, origin);
            func_00282F20(unitDirection, unitDirection, 1.0f);
            angle = func_00282DB0(object + 0xC0, unitDirection);
            if (angle < func_00283180(0.3490658700466156f)) {
                func_00282CF0(delta, targetPosition, origin);
                qcopy(direction, object + 0xC0);
                func_00282DD8(axis, object + 0xC0, delta);
                func_002ACEC0(direction, direction, axis, -0.3490658700466156f);
            } else func_00282CF0(direction, targetPosition, origin);
            func_00282F20(direction, direction, 0.3333333432674408f);
            func_003280C8(object, direction, origin, 0, INT_AT(state, 0x314), (float)BYTE_AT(state, 0x34));
        } else if (object[0x60] & 2) {
            if (func_002A77E0(2) ||
                func_00283C80(FLOAT_AT(object, 0xF8),
                    func_00283248(D_00189E20.position[0] - FLOAT_AT(object, 0x10),
                                  D_00189E20.position[1] - FLOAT_AT(object, 0x14))) > 0.3490658700466156f)
                func_002A7750(object, 5, -1);
            else func_002A7750(object, 4, -1);
        }
        break;
    case 4:
        if (func_002B3868(object) && object[0x43] != 14) func_002A7470(object, 14, 0, 20);
        if (object[0x60] & 2) func_002A7750(object, 3, -1);
        break;
    case 5:
        if (func_002B3868(object)) {
            if (object[0x43] != 7) func_002A7470(object, 7, 0, 15);
            angle = func_00283248(D_00189E20.position[0] - FLOAT_AT(object, 0x10),
                                  D_00189E20.position[1] - FLOAT_AT(object, 0x14));
            FLOAT_AT(state, 0x324) = func_00283B98(angle, func_002A78D8(45.0f, 100.0f) * 0.01745329424738884f);
        }
        func_L02_00331440(object, D_L07_001A8F20, INT_AT(state, 0x88) | 0x10,
                         FLOAT_AT(state, 0x324), -1.0f, -1.0f);
        func_L01_00322288(object,
            func_00283248(FLOAT_AT(state, 0x210) - FLOAT_AT(object, 0x10),
                          FLOAT_AT(state, 0x214) - FLOAT_AT(object, 0x14)));
        if (INT_AT(state, 0xD0) >= 31 || *(unsigned short *)(object + 0x96) >= 121) func_002A7750(object, 3, -1);
        break;
    case 7:
        if (!func_002A8508(INT_AT(state, 0x2B8), -1) ||
            FLOAT_AT(state, 0x20) < (float)*(short *)(state + 0x24))
            func_002A7750(object, 8, -1);
        break;
    case 8:
        if (func_002B3868(object) && object[0x43] != 1) func_002A7470(object, 1, 0, 2);
        if (object[0x60] & 2) {
            if (INT_AT(state, 0x2C0) == -1 || INT_AT(state, 0x2C4) == -1) func_002A7750(object, 3, 2);
            else func_002A7750(object, 9, -1);
        }
        break;
    case 9:
        if (func_002B3868(object) && object[0x43] != 10) func_002A7470(object, 10, 0, 2);
        func_L00_00424A08(0, D_L07_001B0BA0, 0.003000000026077032f);
        func_L00_00424A50(D_L07_001B0BA4, 0.003000000026077032f);
        func_00282CF0(origin, object + 0x10, D_L07_001B23CC[0] + (INT_AT(state, 0x2C0) << 7) + 0x30);
        func_00283098(origin, origin, D_L07_001B23CC[0] + (INT_AT(state, 0x2C0) << 7) + 0x40);
        origin[0] = 0.5f;
        func_00283098(origin, origin, D_L07_001B23CC[0] + (INT_AT(state, 0x2C0) << 7));
        func_00282CC0(origin, origin, D_L07_001B23CC[0] + (INT_AT(state, 0x2C0) << 7) + 0x30);
        func_L01_00321178(object, origin);
        if (func_002ACBC8(object + 0x10, INT_AT(state, 0x2C0))) {
            func_00282CF0(targetPosition, object + 0x10, D_L07_001B23CC[0] + (INT_AT(state, 0x2C0) << 7) + 0x30);
            func_00283098(targetPosition, targetPosition, D_L07_001B23CC[0] + (INT_AT(state, 0x2C0) << 7) + 0x40);
            targetPosition[0] = func_002A7878(0.0f, 1.0f);
            func_00283098(targetPosition, targetPosition, D_L07_001B23CC[0] + (INT_AT(state, 0x2C4) << 7));
            func_00282CC0(targetPosition, targetPosition, D_L07_001B23CC[0] + (INT_AT(state, 0x2C4) << 7) + 0x30);
            func_L02_003329C8(object, targetPosition, 0.10000000894069672f, 0.0055555556900799274f);
            func_002A7750(object, 10, -1);
        }
        break;
    case 10:
        if (func_002B3868(object) && object[0x43] != 4) func_002A7470(object, 4, 0, 2);
        func_L07_00323038(object, 1.0f, 8.0f, 12.5f);
        func_L00_00424A08(0, D_L07_001B0BA0, 0.003000000026077032f);
        func_L00_00424A50(D_L07_001B0BA4, 0.003000000026077032f);
        FLOAT_AT(state, 0x180) = FLOAT_AT(object, 0x18)-3.0f;
        if (object[0x60] & 2) {
            angle = func_00283C80(FLOAT_AT(object, 0xF8),
                func_00283248(FLOAT_AT(state, 0x210) - FLOAT_AT(object, 0x10),
                              FLOAT_AT(state, 0x214) - FLOAT_AT(object, 0x14)));
            if (angle < 0.1745329350233078f) func_002A7750(object, 3, 2);
            else func_002A7750(object, 5, 2);
        }
        break;
    }
    func_L07_003EB700(object);
}
