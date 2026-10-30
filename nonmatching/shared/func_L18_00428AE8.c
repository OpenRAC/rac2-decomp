/* Complete nonmatching reconstruction; 1064/1052 bytes.
 * -O2 -G8 -ffunction-sections; keep-block-order control ties.
 * Local US/US2 each 0/3; PAL has no catalogue row. Two hypotheses.
 * Remaining: linked-controller pointer lifetimes and branch/load schedules.
 * Reopen with independent original object/state lifetime evidence.
 */
#include "common.h"
typedef struct { float v[4]; } EnemyVector __attribute__((aligned(16)));
typedef u8 EnemySlot[0x100];
extern EnemySlot *D_L18_001B281C;
extern u16 D_L18_001B1240 __attribute__((sda)), D_L18_001B1264 __attribute__((sda));
extern void func_00282F20(void *, const void *, float), func_00282CD8(void *, const void *, const void *);
extern int func_L01_00321178(void *, void *), func_L09_003F7A88(void *, int);
extern int func_L18_004271C0(void *), func_L18_00428138(void *), func_001163B0(void);
extern int func_L18_00427130(void *, int, int);
extern void func_L18_00426F28(void *, int, int, float);
extern void func_002A7750(void *, int, int), func_L01_00318638(void *, void *, void *);
extern int func_002B4FF0(void *, void *, float);
extern void func_002A6C58(void *, int, int);
extern float func_00282E80(void *, void *);

/* Follow the assigned path while temporarily releasing the linked controller. */
void func_L18_00428AE8(u8 *object)
{
    EnemyVector offset, scratch;
    u8 *state = *(u8 **)(object + 0x68);
    EnemySlot *slots;
    int index = *(int *)(state + 0x3B4);
    if (index != -1 && *(short *)((slots = D_L18_001B281C)[index] + 0xAA) == 0x114D &&
        slots[index][0x20] != 0xFE && slots[index][0x20] != 0xFD)
        *(int *)(slots[index] + 0x98) = 0;
    if (object[0x95] == 13) {
        float oldAngle, oldSpeed;
        func_00282F20(&offset, D_L18_001B281C[*(int *)(state + 0x3B4)] + 0xC0, 5.0f);
        func_00282CD8(&scratch, &offset, D_L18_001B281C[*(int *)(state + 0x3B4)] + 0x10);
        offset.v[2] = *(float *)(object + 0x18);
        *(float *)(state + 0x128) *= 10.0f;
        *(float *)(state + 0x120) *= 10.0f;
        oldAngle = *(float *)(state + 0x110);
        oldSpeed = *(float *)(state + 0x10C);
        *(float *)(state + 0x110) = 3.1415927f;
        *(float *)(state + 0x10C) = 0.5f;
        func_L01_00321178(object, &offset);
        *(float *)(state + 0x128) *= 0.1f;
        *(float *)(state + 0x120) *= 0.1f;
        *(float *)(state + 0x110) = oldAngle;
        *(float *)(state + 0x10C) = oldSpeed;
    } else {
        {
            if (*(int *)(state + 0x38C) != -1 && func_L09_003F7A88(object, *(int *)(state + 0x38C))) {
                switch (object[0x95]) {
                case 5:
                    if (state[0x399] & 2) state[0x399] = 0;
                    func_L18_00427130(object, *(int *)(state + 0x374), -1);
                    *(u16 *)(state + 0x392) = D_L18_001B1240;
                    func_L18_00426F28(object, 2, 0, 10.0f);
                    func_002A7750(object, 4, 6);
                    break;
                case 6:
                    if (func_L18_004271C0(object)) {
                        *(u16 *)(state + 0x392) = D_L18_001B1240;
                        func_L18_00426F28(object, 2, 0, 10.0f);
                        func_002A7750(object, 4, 6);
                    }
                    if (*(short *)(object + 0xAA) != 0xEC0) func_L18_00428138(object);
                    break;
                case 2:
                    func_L18_004271C0(object);
                    if (object[0x60] & 2) {
                        func_L18_00426F28(object, func_001163B0() & 1, 0, 10.0f);
                        func_002A7750(object, 2, -1);
                    }
                    break;
                }
                if (*(short *)(object + 0xAA) == 0xEC0 && (unsigned)(object[0x95] - 5) < 2 &&
                    func_00282E80(object + 0x10, *(u8 **)(state + 0x230) + 0x10) < *(float *)(state + 0x3A0)) {
                    *(int *)(state + 0x38C) = -1;
                    func_002A7750(object, 4, 6);
                }
            } else if (object[0x95] == 6) {
                if (object[0x20] == 6) func_L01_00321178(object, state + 0x220);
                else {
                    func_002B4FF0(object, state + 0x220, 0.0f);
                    func_L18_00428138(object);
                }
            } else {
                func_L01_00318638(object, state + 0x1F0, state + 0x100);
                if (*(short *)(state + 0x392) == 0) {
                    *(u16 *)(state + 0x392) = D_L18_001B1264;
                    func_L18_00426F28(object, func_001163B0() & 1, 0, 10.0f);
                    func_002A7750(object, 2, -1);
                }
            }
        }
        if (*(float *)(object + 0x18) < *(float *)(state + 0x90)) {
            func_002A6C58(object, 0, 3);
            func_002A7750(object, 12, 10);
        }
        index = *(int *)(state + 0x3B4);
        slots = D_L18_001B281C;
        if (index != -1 && *(short *)((slots = D_L18_001B281C)[index] + 0xAA) == 0x114D &&
            slots[index][0x20] != 0xFE && slots[index][0x20] != 0xFD)
            *(int *)(slots[index] + 0x98) = *(int *)(*(u8 **)(slots[index] + 0x24) + 0x10);
    }
}
