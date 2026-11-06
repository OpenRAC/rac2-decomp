/* func_PAL_002ABCB8, the PAL copy of func_002AB250: 0.03f and 0.015f become 0.036f and 0.018f (x6/5), the
   first delay is scaled to 50 Hz, and the loop is the plain count-up index loop, whose array base is set
   after the hoisted constants. */
#include "include_asm.h"

typedef int s32;

extern void func_00282CC0(float *, float *, void *);
extern int func_002A99A0(void *, int, void *, void *, float);
extern float func_002A7940(void);
extern int func_002A7820(int, int);
extern void func_002AF000(float *, float, float, float);
extern void func_002BAE50(void *, void *, unsigned int, int, int, int, int, int);

void func_PAL_002ABCB8(void *owner, char *offset, void *filter)
{
    float vectors[20][4];
    float position[4];
    int i;
    int result;
    int first;
    float angle;
    result = func_002A99A0(owner, 20, vectors, filter, 14.0f);
    if (result == 0)
        return;
    for (i = 0; i < result; i++) {
        angle = func_002A7940();
        func_002AF000(position, 0.036000002f, angle, func_002A7940());
        func_00282CC0(position, position, offset);
        position[2] += 0.018000001f;
        first = ((s32)func_002A7820(20, 35) * 5 + 2) / 6;
        func_002BAE50(vectors[i], position, 0x7000A0FFu, 255, first, 30, func_002A7820(40, 60), 1);
    }
}
