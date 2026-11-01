#include "common.h"
extern float D_L18_001B1270 __attribute__((sda));
extern u16 D_L18_001B1240 __attribute__((sda)), D_L18_001B1244 __attribute__((sda));
extern u16 D_L18_001B1268 __attribute__((sda));
extern u8 D_L18_001B1248 __attribute__((sda));
extern int D_L18_001B124C __attribute__((sda)), D_L18_001B1250 __attribute__((sda));
extern u32 D_00138320[];
extern char D_L18_001B1360[];
extern float func_00282E80(void *, void *), func_00283248(float, float);
extern void func_002B5258(void *), func_002B5278(void *, float);
extern int func_L01_00321178(void *, void *), func_L18_00428338(void *);
extern int func_00282978(short *), func_002829A8(u8 *);
extern void func_002A6C58(void *, int, int), func_002A7750(void *, int, int);
extern void func_L18_00426F28(void *, int, int, float), func_L18_00426F78(void *);
extern u8 *func_L18_00428428(void *, int);
extern int func_002A7820(int, int), func_001163B0(void);
extern void func_0026FEB8(const char *, ...);

/* Advance the shared enemy's ranged attack and its two muzzle timers. */
int func_L18_00428738(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    int changed = 0;
    switch (*(short *)(object + 0xAA)) {
    case 0xEC0:
        if (object[0xBC] != 1) {
            if (func_00282E80(object + 0x10, state + 0x220) < D_L18_001B1270)
                func_002B5258(object);
            else func_L01_00321178(object, state + 0x220);
        } else {
            if (D_00138320[1] & 0x80) *(u16 *)(state + 0x392) = D_L18_001B1240;
            func_00282978((short *)(state + 0x392));
        }
        if (*(float *)(object + 0x18) < *(float *)(state + 0x90)) {
            func_002A6C58(object, 0, 3);
            changed = 1;
            func_002A7750(object, 12, -1);
        }
        func_L18_00428338(object);
        if (*(short *)(state + 0x392) == 0) {
            if (object[0xBC] != 1) {
                func_L18_00426F78(object);
                changed = 1;
                *(u16 *)(state + 0x396) = D_L18_001B1244;
                func_L18_00426F28(object, 2, 0, 10.0f);
                func_002A7750(object, 4, 6);
            } else changed = 1;
        }
        break;
    case 0xED4:
    case 0xEE1:
        if (object[0xBC] != 1) {
            u8 *target = *(u8 **)(state + 0x230);
            func_002B5278(object, func_00283248(*(float *)(target + 0x10) - *(float *)(object + 0x10),
                                             *(float *)(target + 0x14) - *(float *)(object + 0x14)));
        }
        switch (object[0x42]) {
        case 10:
            if (object[0x60] & 2) {
                func_L18_00426F28(object, 11, 0, 10.0f);
                *(float *)(object + 0x48) = 3.0f;
                {
                    u8 bursts = D_L18_001B1248;
                    *(short *)(state + 0x394) = 0;
                    state[0x39D] = bursts;
                }
            }
            break;
        case 11:
            if (*(short *)(object + 0xAA) == 0xEE1) {
                if (*(short *)(state + 0x394) % 6 == 0) {
                    func_L18_00428428(object, 0);
                    func_002829A8(state + 0x39D);
                }
                if ((*(short *)(state + 0x394) + 3) % 6 == 0) func_L18_00428428(object, 1);
            } else if (*(short *)(object + 0xAA) == 0xED4 && *(short *)(state + 0x394) % 6 != 0) {
                func_L18_00428428(object, 0);
                func_002829A8(state + 0x39D);
            }
            {
                int controlled = object[0xBC];
                if (controlled == 1) {
                    changed = (D_00138320[0] & 0x80) ? changed : controlled;
                } else if (state[0x39D] == 0) func_L18_00426F28(object, 12, 0, 10.0f);
            }
            break;
        case 12:
            if (object[0x60] & 2) {
                changed = 1;
                {
                    int delay = func_002A7820(D_L18_001B124C, D_L18_001B1250);
                    u16 cooldown = D_L18_001B1268;
                    *(short *)(state + 0x396) = delay;
                    *(u16 *)(state + 0x392) = cooldown;
                }
                func_L18_00426F28(object, (func_001163B0() & 1) | 4, 0, 10.0f);
                func_002A7750(object, 2, 6);
            }
            break;
        }
        break;
    default:
        func_0026FEB8(D_L18_001B1360);
        break;
    }
    return changed;
}
