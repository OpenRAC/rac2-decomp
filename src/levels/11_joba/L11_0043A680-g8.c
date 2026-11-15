#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern void func_002A7750(void *, int, int);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
/* Measured object flags are a 16-bit field at +0x34. */
struct InitObjectFlags { char pad[0x34]; unsigned short flags; };
extern float D_L11_001B133C __attribute__((sda));
extern float D_L11_001B1340 __attribute__((sda));
extern float D_L11_001B1344 __attribute__((sda));
extern float D_L11_001B1348 __attribute__((sda));


void func_L11_0043A680(void *obj, void *arg1, float f12, float f13)
{
    char *p = obj;
    char *state;
    float f;
    float g;
    float angle;
    float limit;
    float duration;

    *(unsigned char *)(p + 0x30) = 255;
    *(short *)(p + 0x32) = 255;
    *(unsigned char *)(p + 0x31) = 1;
    state = *(char **)(p + 0x68);
    func_002A7750(p, 3, 0);
    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(unsigned char *)(p + 0xA8) = 255;
    *(unsigned char *)(state + 0x2E) = 1;
    *(TI128 *)(state + 0x2A0) = *(TI128 *)arg1;
    f = 0.0f;
    g = 3.14159274f;
    *(float *)(state + 0x2AC) = f12;
    *(short *)(state + 0x2EC) = 0;
    *(float *)(p + 0xF0) = func_002A7878(f, g);
    *(float *)(p + 0xF4) = func_002A7878(f, g);
    *(float *)(p + 0xF8) = func_002A7878(f, g);
    angle = func_002A7878(20.0f, 40.0f);
    angle = angle * 0.017453294f;
    if (func_002A77E0(2) != 0)
        angle = -angle;
    *(float *)(state + 0x2D4) = angle;
    *(unsigned char *)(p + 0xA8) = 255;
    ((struct InitObjectFlags *)p)->flags &= 0xFEFF;
    limit = D_L11_001B133C + (D_L11_001B1340 - D_L11_001B133C) * f13;
    duration = D_L11_001B1344 + (D_L11_001B1348 - D_L11_001B1344) * f13;
    *(float *)(state + 0x2E0) = limit;
    *(int *)(state + 0x2E4) = FloatToInt(duration);
}
