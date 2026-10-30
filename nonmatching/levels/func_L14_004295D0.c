/* Retained reconstruction,30 October2026; not linked and no matching credit.
 * Profile: -O2 -G8 -ffunction-sections.
 * 796/796 bytes; us 0/1, us2 0/1, pal absent.
 * Reviewed qcopy preserves the complete position transfer without the old copy-profile
 * requirement. The initial angular-velocity/constants schedule still differs at+0x90,
 * as in the previous candidate. Reopen with genuine initialization-group or
 * field-lifetime evidence.
 */
#include "common.h"
typedef int PrisonInitQuad __attribute__((mode(TI)));
extern int func_00283CF0(float), func_002A77E0(int);
extern void func_00325B70(void *, void *, int, int);
extern float func_002B0178(void *, void *, void *);
extern void func_002A7750(void *, int, int), func_002A7470(void *, int, int, int);
extern void func_L14_003DF650(void *), func_002A93B0(void *);
extern float func_00282E48(void *, void *);
extern int func_002B0ED8(void *, void *, int);
extern void func_L14_00429A18(void *), func_00325D30(void *, void *);
extern int func_002B3BA8(void *, int, void *, int, float, float);
extern char D_L14_001B9500[];
extern char *D_L14_001B259C __attribute__((sda));
extern float D_L14_001B1948 __attribute__((sda));
extern unsigned short D_L14_001B1950 __attribute__((sda));
extern unsigned short D_L14_001B1954;
#define F(offset) (*(float *)(state + (offset)))
#define I(offset) (*(int *)(state + (offset)))
#define H(offset) (*(unsigned short *)(state + (offset)))

int func_L14_004295D0(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    float velocity;
    if (object[0x20] == 0) {
        state[0x48] = func_00283CF0(15.0f);
        state[0x4a] = func_00283CF0(9.6f);
        state[0x150] = 6;
        F(0x17c) = 0.15f;
        I(0x188) = 2;
        F(0x174) = F(0x170) = 1.0f;
        velocity = D_L14_001B1948;
        velocity *= 0.01745329424738884f;
        F(0x180) = *(float *)(object + 0x18) - 3.0f;
        F(0x54) = 0.3f;
        F(0x50) = 1.0f;
        F(0x78) = 0.10000000894069672f;
        F(0x74) = F(0x70) = 0.005f;
        F(0x68) = F(0x64) = 0.0034906589426100254f;
        F(0x60) = 3.1415927f;
        if (func_002A77E0(2)) velocity = -velocity;
        F(0x12c) = velocity;
        H(0x132) = D_L14_001B1950;
        H(0x134) = D_L14_001B1954;
        state[0x2e] = 1;
        qcopy(state + 0x2e0, object + 0x10);
        I(0x31c) = 1;
        F(0x2b4) = 4.0f;
        func_00325B70(object, state + 0x300, 0, 2);
        F(0x20) = 3.0f;
        H(0x24) = 3;
        *(float *)(object + 0x18) += 0.5f;
        func_002B0178(object + 0x10, object, object + 0x10);
        if (I(0x2bc) != -1) {
            func_002A7750(object, 7, 3);
            if (object[0x43]) func_002A7470(object, 0, 0, 0);
        } else {
            func_002A7750(object, 1, 0);
            if (object[0x43] != 2) func_002A7470(object, 2, 0, 0);
        }
        if (I(0x2b8) != -1) func_L14_003DF650(D_L14_001B259C + I(0x2b8) * 256);
    }
    if (object[0x31] && func_00282E48(object + 0x10, D_L14_001B9500) < 24.0f) {
        func_002A93B0(object);
        object[0x6f] = 22;
    }
    if (func_002B0ED8(object, state + 0x140, 0) && F(0x20) <= 0.0f) {
        func_L14_00429A18(object);
        return 1;
    }
    if ((unsigned char)state[0x2e] == 2) {
        if (state + 0x300) func_00325D30(object, state + 0x300);
        return 1;
    }
    I(0x2f0) = func_002B3BA8(object, I(0x2b0), 0, 0, F(0x2b4), 1.5f);
    return 0;
}
#undef F
#undef I
#undef H
