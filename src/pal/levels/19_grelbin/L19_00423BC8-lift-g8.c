#include "common.h"
extern float D_L19_001B1D5C __attribute__((sda));
extern float D_L19_001B1D60 __attribute__((sda));
extern float D_L19_001B1D64 __attribute__((sda));
extern float D_L19_001B1D68 __attribute__((sda));
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00282E80(void *, void *);
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern void func_002E5CF8(int, int, void *);
typedef struct { u8 *other; float angle, height, time; } LiftState;
/* func_PAL_L19_00423BC8, the PAL copy of func_L19_0041E5B0: the same C, where each timer's rate
   is scaled for 50 Hz. Lowers and rotates the lift, waits for the linked object to leave, then resets it. */
void func_PAL_L19_00423BC8(u8 *obj)
{
    LiftState *s = *(LiftState **)(obj + 0x68);
    switch (obj[0x20]) {
    case 0: {
        float angle, height;
        s->other = 0;
        s->angle = *(float *)(obj + 0xF8);
        s->height = *(float *)(obj + 0x18);
        angle = func_00283B98(*(float *)(obj + 0xF8), 3.1415927f);
        height = *(float *)(obj + 0x18) - D_L19_001B1D5C;
        *(float *)(obj + 0xF8) = angle;
        *(float *)(obj + 0x18) = height;
        func_002A7750(obj, 1, -1);
        break;
    }
    case 1:
        if (s->other && s->other[0x20] != 0xFE && s->other[0x20] != 0xFD) {
            s->time = 0;
            func_002A7750(obj, 2, -1);
        }
        break;
    case 2:
        if (func_002B3868(obj)) func_002E5CF8(0, 0, obj);
        s->time += 1.0f / ((D_L19_001B1D60 * 5.0f + 2.0f) * 0.16666667f);
        if (s->time > 1.0f) {
            s->time = 0;
            *(float *)(obj + 0x18) = s->height;
            obj[0xBC] = 1;
            func_002A7750(obj, 3, -1);
        } else {
            float f = (func_00283180(s->time * 3.1415927f) + 1.0f) * 0.5f;
            if (f > 1.0f) f = 1.0f;
            else if (f < 0.0f) f = 0.0f;
            *(float *)(obj + 0x18) = s->height - f * D_L19_001B1D5C;
        }
        break;
    case 3:
        s->time += 1.0f / ((D_L19_001B1D64 * 5.0f + 2.0f) * 0.16666667f);
        if (s->time > 1.0f) {
            s->time = 0;
            *(float *)(obj + 0xF8) = s->angle;
            obj[0xBC] = 2;
            func_002A7750(obj, 4, -1);
        } else {
            float f = (func_00283180(s->time * 3.1415927f) + 1.0f) * 0.5f;
            *(float *)(obj + 0xF8) = func_00283B98(s->angle, f * 3.1415927f);
        }
        break;
    case 4:
        if (!s->other || s->other[0x20] == 0xFE || s->other[0x20] == 0xFD ||
            func_00282E80(obj + 0x10, s->other + 0x10) > D_L19_001B1D68) {
            obj[0xBC] = 3;
            s->other = 0;
            s->time = 1.0f;
            func_002A7750(obj, 5, -1);
        }
        break;
    case 5:
        if (func_002B3868(obj)) func_002E5CF8(1, 0, obj);
        s->time -= 1.0f / ((D_L19_001B1D64 * 5.0f + 2.0f) * 0.16666667f);
        if (s->time <= 0.0f) {
            s->time = 1.0f;
            *(float *)(obj + 0xF8) = func_00283B98(s->angle, 3.1415927f);
            func_002A7750(obj, 6, -1);
        } else {
            float f = (func_00283180(s->time * 3.1415927f) + 1.0f) * 0.5f;
            *(float *)(obj + 0xF8) = func_00283B98(s->angle, f * 3.1415927f);
        }
        break;
    case 6:
        s->time -= 1.0f / ((D_L19_001B1D60 * 5.0f + 2.0f) * 0.16666667f);
        if (s->time <= 0.0f) {
            float height = s->height - D_L19_001B1D5C;
            s->time = 0;
            obj[0xBC] = 0;
            *(float *)(obj + 0x18) = height;
            func_002A7750(obj, 1, -1);
        } else {
            float f = (func_00283180(s->time * 3.1415927f) + 1.0f) * 0.5f;
            if (f > 1.0f) f = 1.0f;
            else if (f < 0.0f) f = 0.0f;
            *(float *)(obj + 0x18) = s->height - f * D_L19_001B1D5C;
        }
        break;
    }
}
