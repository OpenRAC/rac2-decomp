/* func_L02_003FE768: the boss health bar (shared by Maktar and Joba).
 * Own -G8 unit. Each screen edge is rounded into t and converted in a one-pass group
 * (docs/COMPILER-NOTES.md, source methods shared with RAC1): the group's loop notes keep
 * the D_001A7B90 mode load after the conversions, as retail schedules it. Without the
 * groups the load is hoisted across them (0 of 2 places).
 */
#include "common.h"
extern void func_002FC560(unsigned int, unsigned long long);
extern int func_00283CF0(float);
extern int func_L00_0031C998(int, int, float);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern int D_L02_001B1330 __attribute__((sda));
extern int D_L02_001B1338[] __attribute__((sda));
extern int D_L02_001B1334[] __attribute__((sda));
extern int D_L02_001B133C[] __attribute__((sda));
extern int D_L02_001B1340 __attribute__((sda));
extern int D_L02_001B1348 __attribute__((sda));
extern int D_L02_001B134C[] __attribute__((sda));
extern int D_L02_001B1350[] __attribute__((sda));
extern float D_L02_001B3E04[] __attribute__((sda));
extern int D_001A7B90[] __attribute__((sda));

void func_L02_003FE768(float fraction)
{
    int width;
    int color;
    int top;
    int bottom;
    int left;
    int right;
    float t;
    func_002FC560(0x42, 0x8000000044ULL);
    if (fraction < 0.0f)
        fraction = 0.0f;
    width = func_00283CF0((float)(D_L02_001B1338[0] - D_L02_001B1330) * fraction);
    if (fraction > 0.5f)
        color = func_L00_0031C998(D_L02_001B134C[0], D_L02_001B1348, fraction + fraction - 1.0f);
    else
        color = func_L00_0031C998(D_L02_001B1350[0], D_L02_001B134C[0], fraction + fraction);
    t = (float)D_L02_001B1334[0] * D_L02_001B3E04[0] + 0.5f;
    do {
        top = t;
    } while (0);
    if (D_001A7B90[0])
        top -= D_L02_001B1340;
    left = D_L02_001B1330;
    right = left + width;
    t = (float)D_L02_001B133C[0] * D_L02_001B3E04[0] + 0.5f;
    do {
        bottom = t;
    } while (0);
    if (D_001A7B90[0])
        bottom -= D_L02_001B1340;
    func_0028FC48(left, top, right, bottom, color, 0);
}
