/* func_PAL_L13_00420460, the PAL copy of func_L13_0041B670: the same C with 50 Hz rates, where mode 0 also resets
 * D_PAL_001B16F8 from D_001A7904, and the locked sound can come from D_PAL_001A7988 (as v2.00's func_US2_L30_0040D208).
 * Each sound keeps its own call: jump2 cross-jumps them. */
#include "common.h"

typedef struct { float acceleration, deceleration, speed; } MotionSettings_L13;
typedef struct {
    int primary, secondary, flagA, flagB;   /* 0x00 */
    char pad10[0x10];
    float f20, f24;                         /* 0x20 */
    int i28, i2C;                           /* 0x28 */
    char pad30[4];
    float timer;                            /* 0x34 */
    int enabled, busy, locked;              /* 0x38 */
} RingState_L13;
typedef struct {
    char pad0[0x10];
    float position[4];                      /* 0x10 */
    u8 mode;                                /* 0x20 */
    char pad21[0x68 - 0x21];
    RingState_L13 *state;                   /* 0x68 */
    char pad6C[0xF0 - 0x6C];
    char fF0[8];                            /* 0xF0 */
    float fF8;                              /* 0xF8 */
    char padFC[4];
} Ring_L13;
typedef struct {
    char pad0[0x33C];
    Ring_L13 *target;                       /* 0x33C */
    char pad340[0x34E - 0x340];
    short busy;                             /* 0x34E */
} Hero_L13_0041B670;
extern Hero_L13_0041B670 D_00189E20;
extern int D_001A79F0;
extern unsigned char D_0019B2E8[];
extern unsigned int D_00138324[];
extern int D_L13_001A8FB4;
extern Ring_L13 *D_L13_001B291C;
extern unsigned char D_0018C0D5[];
extern MotionSettings_L13 D_L13_001B16D8 __attribute__((sda));
extern int D_001A7904;
extern int D_PAL_001A7988 __attribute__((sda));
extern int D_PAL_001B16F8 __attribute__((sda));
extern void func_PAL_L13_00420888(Ring_L13 *);
extern int func_002E5CF8(int, int, Ring_L13 *);
extern void func_L00_002D40A0(float *, int, float);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern int func_L00_002D40F0(void);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_00288CB0(int, int);
extern void func_L13_0041BAE0(void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern float func_002AA2E8(float *, float, float);
extern float func_002AA548(float *, float *, float, float, float, float);

void func_PAL_L13_00420460(Ring_L13 *object)
{
    float position[4] __attribute__((aligned(16)));
    RingState_L13 *state = object->state;
    Ring_L13 *destination;
    RingState_L13 *target_state;
    int code;

    if (state->enabled == 0)
        return;
    switch (object->mode) {
    case 0:
        object->mode = 1;
        D_PAL_001B16F8 = 0;
        if (D_001A7904 == 1) {
            D_PAL_001B16F8 = 1;
            D_001A7904 = 0;
        }
        return;
    case 1:
        if (state->flagA >= 0 && !(D_0019B2E8[state->flagA + D_001A79F0 * 16] & 0x80))
            return;
        if (state->primary == -1 && state->locked == 0 && state->busy == 0)
            return;
        if (D_00189E20.target != object || D_00189E20.busy != 0)
            return;
        func_PAL_L13_00420888(object);
        if (!(D_00138324[0] & 0x10))
            return;
        if (D_L13_001A8FB4 == 11) {
            func_002E5CF8(0, 0, object);
            object->mode = 2;
            state->i28 = 0;
            state->i2C = 0;
            func_L00_002D40A0(object->position, 0, object->fF8);
            func_002A8C28(object, object->position, 0x10000, 0, 1, 0, 1.5f, 20.0f, 1.0f);
        }
        return;
    case 2:
        code = func_L00_002D40F0();
        if (code == 2) {
            state->timer = 1.95f;
            object->mode = 3;
        } else if (code == 0) {
            object->mode = 4;
        }
        return;
    case 3:
        if (state->timer == 0.0f) {
            if (state->busy == 0 && state->locked == 0) {
                destination = &D_L13_001B291C[state->primary];
                if (state->secondary != -1 && (D_0019B2E8[state->flagB + D_001A79F0 * 16] & 0x80))
                    destination = &D_L13_001B291C[state->secondary];
                target_state = destination->state;
                qcopy(position, destination->position);
                position[2] += 0.2f;
                func_L00_002B9D60(position, destination->fF0, 0, 1);
                D_0018C0D5[0] = 1;
                destination->mode = 4;
                target_state->timer = 0.0f;
                target_state->i28 = 0;
                target_state->i2C = 0;
                target_state->f20 = 1.0f;
                target_state->f24 = 1.0f;
                func_002E5CF8(1, 0, destination);
                object->mode = 1;
                state->timer = 1.95f;
                state->f24 = 0;
                state->i28 = 0;
                state->i2C = 0;
                state->f20 = 0;
            } else {
                if (state->locked) {
                    if (D_PAL_001B16F8)
                        func_00288CB0(D_PAL_001A7988, 1);
                    else
                        func_00288CB0(13, 1);
                } else {
                    func_00288CB0(21, 1);
                }
            }
            return;
        }
        func_L00_002E6CF0(func_L13_0041BAE0, object);
        func_002AA2E8(&state->timer, 0.0f, 0.080000006f);
        return;
    case 4:
        if (state->timer < 1.95f) {
            func_L00_002E6CF0(func_L13_0041BAE0, object);
            func_002AA2E8(&state->timer, 1.95f, 0.080000006f);
            return;
        }
        if (state->f24 > 0.0f) {
            func_002AA548(&state->f24, (float *)&state->i28, 0.0f,
                D_L13_001B16D8.acceleration * 0.00040000002f,
                D_L13_001B16D8.deceleration * 0.00040000002f,
                D_L13_001B16D8.speed * 0.020000001f);
            return;
        }
        if (state->f20 > 0.0f) {
            func_002AA548(&state->f20, (float *)&state->i2C, 0.0f,
                D_L13_001B16D8.acceleration * 0.00040000002f,
                D_L13_001B16D8.deceleration * 0.00040000002f,
                D_L13_001B16D8.speed * 0.020000001f);
            return;
        }
        object->mode = 1;
    }
}
