#include "common.h"
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern float func_002A7878(float, float);
extern unsigned int func_00283D38(int, float, int);
extern float func_002A7940(void);
extern void func_00281EB8(void *, int, unsigned int, int, float, float, float);
extern int D_L04_001B13C0 __attribute__((sda));
extern int D_L04_001B13C4[] NOT_SDA;
extern int D_L04_001B13C8[] NOT_SDA;
extern int D_L04_001B13CC[] NOT_SDA;
extern int D_L04_001B13D0[] NOT_SDA;
extern int D_L04_001B13D4[] NOT_SDA;
extern int D_L04_001B13D8[] NOT_SDA;
extern int D_L04_001B13DC[] NOT_SDA;

void func_L04_0043BEE8(char *object)
{
    float a[4], b[4], position[4];
    char *state = *(char **)(object + 0x68);
    float factor = func_00283198(*(float *)(state + 0x4c) * 3.1415927f);
    unsigned int color;
    float angle, fraction;
    func_00282CC0(a, state, state + 0x10);
    func_00282D08(a, state, a, factor);
    func_00282CC0(b, state + 0x20, state + 0x30);
    func_00282D08(b, state + 0x20, b, factor);
    func_00282D08(position, a, b, *(float *)(state + 0x4c));
    fraction = func_002A7878(0.0f, 1.0f);
    color = func_00283D38(D_L04_001B13C0, fraction, D_L04_001B13C4[0]);
    angle = func_002A7940();
    func_00281EB8(position, 0x31, color, 1, 1.0f, 0.0f, angle);
    fraction = func_002A7878(0.0f, 1.0f);
    color = func_00283D38(D_L04_001B13C8[0], fraction, D_L04_001B13CC[0]);
    angle = func_002A7940();
    func_00281EB8(position, 0x31, color, 1, 0.6f, 0.0f, angle);
    fraction = func_002A7878(0.0f, 1.0f);
    color = func_00283D38(D_L04_001B13D0[0], fraction, D_L04_001B13D4[0]);
    angle = func_002A7940();
    func_00281EB8(position, 0xb, color, 1, 1.4f, 0.0f, angle);
    fraction = func_002A7878(0.0f, 1.0f);
    color = func_00283D38(D_L04_001B13D8[0], fraction, D_L04_001B13DC[0]);
    angle = func_002A7940();
    func_00281EB8(position, 0xb, color, 1, 0.9f, 0.0f, angle);
}
