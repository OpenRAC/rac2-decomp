#include "include_asm.h"

typedef struct { char pad0[0x80]; char position[0x2BC]; char *active; int enabled; char pad1[0x244]; char *other; char pad2[0x1D10]; int mode; } Globals;
extern Globals D_00189E20;
extern char *D_L08_001B29DC;
extern float D_L08_001B01E0 __attribute__((sda)), D_L08_001B01E4 __attribute__((sda)), D_L08_001B01E8 __attribute__((sda));
extern float D_L08_001B01EC __attribute__((sda)), D_L08_001B01F0 __attribute__((sda)), D_L08_001B01F4 __attribute__((sda)), D_L08_001B01F8 __attribute__((sda));
extern int func_L08_003D0098(int);
extern float func_00283180(float);
extern float func_00282E80(void *, void *);
extern float func_00283B98(float, float);
extern float func_00282C48(float);
extern void func_002E5CF8(int, int, void *);
extern void func_L08_003D0040(void *);

void func_PAL_L08_003D4078(char *object) {
    char *state = *(char **)(object + 0x68);
    float delta, previous, magnitude;
    float damping;
    int result;
    switch ((unsigned char)object[0x20]) {
    case 0:
        *(float *)(state + 8) = 0;
        if (*(int *)(state + 0x14) != -1) {
            char *part = (char *)((*(unsigned int *)(state + 0x14) << 8) + (unsigned int)D_L08_001B29DC);
            int status = (unsigned char)part[0x20];
            if (status == 0xFE) goto first_done;
            if (status == 0xFD) goto first_done;
            *(char **)state = part;
        }
    first_done:
        if (*(int *)(state + 0x18) != -1) {
            char *part = (char *)((*(unsigned int *)(state + 0x18) << 8) + (unsigned int)D_L08_001B29DC);
            int status = (unsigned char)part[0x20];
            if (status == 0xFE) goto second_done;
            if (status == 0xFD) goto second_done;
            *(char **)(state + 4) = part;
        }
    second_done:
        *(int *)(state + 0x10) = func_L08_003D0098(*(int *)(state + 0xC));
        object[0x20] = 1;
        break;
    case 1:
        delta = 0;
        if (D_00189E20.enabled) {
            if (D_00189E20.active == *(char **)state) {
                float angular = func_00283180(*(float *)(object + 0xF4));
                float distance = func_00282E80(D_00189E20.position, object + 0x10);
                float coefficient = D_L08_001B01E0;
                angular *= 6.981318e-06f;
                delta = coefficient * angular * distance / D_L08_001B01F0;
            }
            if (D_00189E20.active == *(char **)(state + 4)) {
                magnitude = func_00283180(*(float *)(object + 0xF4));
                delta = -(D_L08_001B01E0 * 6.981318e-06f) * magnitude * func_00282E80(D_00189E20.position, object + 0x10) / D_L08_001B01F0;
            }
        }
        if (D_00189E20.mode == 3) {
            if (D_00189E20.other == *(char **)state) {
                float angular = func_00283180(*(float *)(object + 0xF4));
                float distance = func_00282E80(D_00189E20.position, object + 0x10);
                float coefficient = D_L08_001B01E0;
                angular *= 6.981318e-06f;
                delta = coefficient * angular * distance / D_L08_001B01F0;
            }
            if (D_00189E20.other == *(char **)(state + 4)) {
                magnitude = func_00283180(*(float *)(object + 0xF4));
                delta = -(D_L08_001B01E0 * 6.981318e-06f) * magnitude * func_00282E80(D_00189E20.position, object + 0x10) / D_L08_001B01F0;
            }
        }
        if (*(float *)(object + 0xF4) > D_L08_001B01E4 * 0.01745329424738884f)
            {
            float offset = *(float *)(object + 0xF4) - D_L08_001B01E4 * 0.01745329424738884f;
            float range = D_L08_001B01E8 * 0.01745329424738884f;
            offset /= range;
            delta -= D_L08_001B01EC * (offset * 6.981318e-06f);
        }
        else if (*(float *)(object + 0xF4) < -D_L08_001B01E4 * 0.01745329424738884f)
            {
            float offset = D_L08_001B01E4 * 0.01745329424738884f + *(float *)(object + 0xF4);
            float range = D_L08_001B01E8 * 0.01745329424738884f;
            offset /= range;
            delta -= D_L08_001B01EC * (offset * 6.981318e-06f);
        }
        previous = *(float *)(state + 8);
        *(float *)(state + 8) += delta;
        *(float *)(object + 0xF4) = func_00283B98(*(float *)(object + 0xF4), *(float *)(state + 8));
        if ((func_00282C48(previous) < 0.0003490659f && func_00282C48(*(float *)(state + 8)) > 0.0003490659f) ||
            (func_00282C48(previous) < 0.0017453296f && func_00282C48(*(float *)(state + 8)) > 0.0017453296f) ||
            (func_00282C48(previous) < 0.0034906592f && func_00282C48(*(float *)(state + 8)) > 0.0034906592f))
            func_002E5CF8(0, 0, object);
        result = func_L08_003D0098(*(int *)(state + 0xC));
        if (func_00282C48(*(float *)(object + 0xF4)) > D_L08_001B01F4 * 0.01745329424738884f && result) {
            *(float *)(state + 8) = 0;
            object[0x20] = 2;
        }
        damping = D_L08_001B01F8;
        *(int *)(state + 0x10) = result;
        *(float *)(state + 8) *= damping;
        func_L08_003D0040(object);
        break;
    case 2:
        if (!func_L08_003D0098(*(int *)(state + 0xC))) object[0x20] = 1;
        break;
    }
}
