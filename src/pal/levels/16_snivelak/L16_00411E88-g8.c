#include "common.h"

/* func_PAL_L16_00411E88, the PAL copy of func_L16_0040CF98: the same C, where the lead doubling
   becomes 2 * 5/6 and the turn rates take a 6/5 squared correction at 50 Hz. */

extern void func_00282948(void *);
extern s32 func_00282978(void *);
extern void func_0029FCC0(void *, s32, void *);
extern float func_00282E48(void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00283B98(float, float);
extern void func_002AEC48(void *, void *, s32, float, float);
extern u8 D_L16_00189F30[] __attribute__((nosda));
extern float D_L16_001B1640 __attribute__((sda));
extern float D_L16_001B1644 __attribute__((sda));

void func_PAL_L16_00411E88(u8 *arg)
{
    float temp[4];
    float target[4];
    u8 *state;
    u8 *origin;
    float value;
    float scale;
    float rate;
    state = *(u8 **)(arg + 0x68);
    func_00282948(state + 0x238);
    func_00282978(state + 0x23C);
    if (*(u16 *)(arg + 0x96) < 0xFFFF) ++*(u16 *)(arg + 0x96);
    func_0029FCC0(arg, 0, temp);
    if (arg[0x20] != 4) {
        origin = state + 0x1F0;
        value = func_00282E48(temp, origin) - 1.0f;
        func_00282D30(target, D_L16_00189F30, value * 1.6666666f);
        target[2] = 0.0f;
        func_00282CC0(target, target, origin);
        func_00282CF0(temp, target, temp);
        *(float *)(state + 0x2B8) = func_00283BE0(func_00283248(temp[0], temp[1]), *(float *)(arg + 0xF8));
        func_0029FCC0(arg, 1, temp);
        func_00282CF0(temp, target, temp);
        value = func_00283BE0(-func_00283248(func_00282E20(temp), temp[2]), *(float *)(arg + 0xF4));
        if (value > 0.523598849773407f) value = 0.523598849773407f;
        else if (value < -0.523598849773407f) value = -0.523598849773407f;
        *(float *)(state + 0x334) = value;
        scale = 0.5f;
    } else {
        *(float *)(state + 0x2B8) = func_00283B98(*(float *)(state + 0x298), 0.523598849773407f);
        scale = 0.085f;
    }
    rate = scale * 1.44f;
    func_002AEC48(arg, state + 0x250, 0, D_L16_001B1640 * rate, D_L16_001B1644 * rate);
    func_002AEC48(arg, state + 0x2D0, 1, D_L16_001B1640 * rate, D_L16_001B1644 * rate);
}
