#include "include_asm.h"

#include "common.h"
#define F(p, o) (*(float *)((p) + (o)))
#define I(p, o) (*(int *)((p) + (o)))
#define B(p, o) (*(unsigned char *)((p) + (o)))
extern void func_PAL_L11_0043F9A8(char *);
extern void func_L11_0043A620(char *);
extern void func_PAL_L11_004400D0(char *);
extern void func_PAL_L11_0043FDB8(char *);
extern void func_PAL_L11_0045EBA0(void *, void *, void *, float);
extern void func_L11_0043ACB0(float, void *, void *, float, float);
extern int func_L11_00439D78(float, float, float, float);
extern char *func_L11_004417E8(void *);
extern float func_00282E80(void *, void *);
extern float func_L02_002F21C0(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00283B98(float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002833F0(void *, void *);
extern int func_002B3868(void *);
extern int func_002A77E0(int);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_PAL_002B5BA8(void *, void *, float);
extern void func_PAL_002B5E10(void *);
extern float func_0029F530(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_0029FC20(void *, int, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_002E5DA0(int, int, void *, int);
extern void func_00282948(void *);
extern int func_002B1C20(void *, void *);
extern float D_L11_001B1354 __attribute__((sda));
extern float D_L11_001B134C __attribute__((sda));
extern float D_L11_001B132C __attribute__((sda));
extern float D_L11_001B1328 __attribute__((sda));
extern int D_L11_001B1330 __attribute__((sda));
extern int D_L11_001B1350 __attribute__((sda));
extern char D_L11_001B1360[16] SDATA(D_L11_001B1360) __attribute__((sda));

/* Updates the airborne tumble, approach, firing and reaction states. */
void func_PAL_L11_0043F35C(char *object)
{
    float target[4], before[4], after[4], delta[4], velocity[16];
    char *state = *(char **)(object + 0x68);
    float distance, angle, height, frames, anim;
    int result, fireTimer;
    char *pos;
    char *aim;

    func_PAL_L11_0043F9A8(object);
    qcopy(target, state + 0x50);
    pos = object + 0x10;
    distance = func_00282E80(pos, target);
    angle = func_00283248(target[0] - F(object, 0x10), target[1] - F(object, 0x14));
    func_00283C80(F(object, 0xF8), angle);
    switch (B(object, 0x20)) {
    case 3:
        if (func_002B3868(object)) {
            height = F(object, 0x18);
            height -= D_L11_001B1354;
            F(object, 0xF8) = angle;
            I(object, 0xF0) = 0;
            I(object, 0xF4) = 0;
            frames = func_L11_00439D78(height,
                F(func_L11_004417E8(*(void **)(object + 0xB8)), 8),
                F(state, 0x2A8), F(state, 0x2AC));
            F(state, 0x2B0) = (func_002A77E0(D_L11_001B1350) + 1) * 6.2831855f / frames;
            F(state, 0x2B4) = (func_002A77E0(D_L11_001B1350) + 1) * 6.2831855f / frames;
            F(state, 0x2B8) = (func_002A77E0(D_L11_001B1350) + 1) * 6.2831855f / frames;
        }
        height = F(object, 0x18);
        height -= D_L11_001B1354;
        if (height >= F(func_L11_004417E8(*(void **)(object + 0xB8)), 8)) {
            func_00282CC0(pos, pos, state + 0x2A0);
            F(state, 0x2A8) -= F(state, 0x2AC);
            func_00283098(before, D_L11_001B1360, object + 0xC0);
            F(object, 0xF0) = func_00283B98(F(state, 0x2B0), F(object, 0xF0));
            F(object, 0xF4) = func_00283B98(F(state, 0x2B4), F(object, 0xF4));
            F(object, 0xF8) = func_00283B98(F(state, 0x2B8), F(object, 0xF8));
            func_002833F0(object + 0xC0, object + 0xF0);
            func_00283098(after, D_L11_001B1360, object + 0xC0);
            func_00282CF0(delta, before, after);
            func_00282CC0(pos, pos, delta);
        } else {
            I(object, 0xF0) = 0;
            I(object, 0xF4) = 0;
            func_002A7750(object, 4, -1);
        }
        break;
    case 4:
        result = func_002B3868(object);
        aim = state + 0x2C0;
        if (result) {
            if (B(object, 0x43) != 7)
                func_PAL_002A7E68(object, 7, 0, 2);
            F(object, 0x48) = D_L11_001B134C;
            qcopy(aim, pos);
            func_L11_0043ACB0(D_L11_001B132C, aim, target, 45, 2);
        }
        F(object, 0x18) -= D_L11_001B1354;
        func_PAL_002B5BA8(object, aim, F(state, 0x2D4));
        F(object, 0x18) += D_L11_001B1354;
        if (func_L02_002F21C0(object + 0x10, aim) < 4.84f && B(object, 0x31)) {
            F(object, 0x48) = 1;
            func_002A7750(object, 5, -1);
            return;
        }
        if (func_L02_002F21C0(aim, target) > D_L11_001B1328 * D_L11_001B1328) {
            func_002A7750(object, 4, -1);
            return;
        }
        break;
    case 5:
        if (func_002B3868(object)) {
            B(object, 0xBC) = 0;
            if (B(object, 0x43) != 3)
                func_PAL_002A7E68(object, 3, 0, 2);
            I(state, 0x2D0) = 0;
        } else {
            if (B(object, 0xBC) == 0) {
                if (B(object, 0x60) & 2) {
                    B(object, 0xBC) = 1;
                    if (B(object, 0x43) != 4)
                        func_PAL_002A7E68(object, 4, 0, 6);
                    F(object, 0x48) = I(state, 0x2E4);
                    goto attack;
                }
            }
            if (B(object, 0xBC) == 3 && (B(object, 0x60) & 2))
                func_002A7750(object, 4, -1);
        }
attack:
        if (B(object, 0xBC) == 1) {
            anim = func_0029F530(object);
            func_PAL_L11_0043FDB8(object);
            func_002E5CF8(2, 0, object);
            if (!I(state, 0x2D0) && anim < (fireTimer = D_L11_001B1330) + 1) {
                I(state, 0x2D0) = ((s32)(fireTimer) * 5 + 2) / 6;
                func_0029FCC0(object, 1, before);
                /* This helper writes the complete 64-byte joint matrix. */
                func_0029FC20(object, 1, velocity);
                func_PAL_L11_0045EBA0(before, object, velocity, B(state, 0x34));
                func_002E5DA0(0, 0, object, 0xD4B);
            }
            func_00282948(state + 0x2D0);
            if (distance > D_L11_001B1328) {
                B(object, 0xBC) = 3;
                F(object, 0x48) = 1;
                if (B(object, 0x43) != 5)
                    func_PAL_002A7E68(object, 5, 0, 2);
            }
        }
        F(object, 0x18) -= D_L11_001B1354;
        func_PAL_002B5E10(object);
        F(object, 0x18) += D_L11_001B1354;
        break;
    case 6:
        if (func_002B3868(object))
            func_002E5DA0(2, 0, object, 0xD4B);
        result = func_002B1C20(object, state + 0x170);
        if (result & 2)
            func_002A7750(object, 4, 1);
        if (result & 1) {
            func_002E5CF8(3, 0, object);
            func_PAL_L11_004400D0(object);
        }
        break;
    }
    func_L11_0043A620(object);
}
