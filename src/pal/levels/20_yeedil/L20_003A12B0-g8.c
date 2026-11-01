#include "include_asm.h"

#include "common.h"
extern void func_L20_00330A68(void *, int);
extern void func_002A7750(void *, int, int);
extern s32 func_002B3BA8(void *, s32, s32, float, float, s32);
extern int func_002A9640(void *, int, int);
extern float func_PAL_002AA108(void *, int);
extern const float D_L20_001AED00 __attribute__((sda));
extern int g_pHeroMoby[];

/* A countdown object: set up once, then it drains its timer by the animation's step
   and changes state at the end of the count or on a long step. */
void func_PAL_L20_003A1538(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    float zero;
    float step;
    float left;

    if (*(u8 *)(obj + 0x20) == 0) {
        if (*(f32 *)(state + 0x20) == 0.0f) {
            *(u16 *)(state + 0x24) = 0x1E;
            *(f32 *)(state + 0x20) = 30.0f;
        }
        func_L20_00330A68(obj, 0xCBC);
        *(u16 *)(obj + 0x32) = 0xFF;
        *(u16 *)(obj + 0x34) &= 0xFFFB;
        *(f32 *)(obj + 0x2C) = *(f32 *)(*(char **)(obj + 0x24) + 0x24) * D_L20_001AED00;
        *(int *)(state + 0x190) = 1;
        *(int *)(obj + 0x98) = 0;
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) | 0x41) & 0xEFFF;
        func_002A7750(obj, 1, -1);
    }
    zero = 0.0f;
    func_002B3BA8(obj, *(int *)(state + 0x80), 0, zero, zero, 0);
    if (*(int *)(state + 0x60) == 0)
        *(int *)(state + 0x60) = g_pHeroMoby[0];
    step = func_PAL_002AA108(obj, func_002A9640(obj, 0x10000, 0));
    left = *(f32 *)(state + 0x20) - step;
    *(f32 *)(state + 0x20) = left;
    if (left <= zero)
        func_002A7750(obj, 5, -1);
    if (5.0f <= step)
        func_002A7750(obj, 4, -1);
    *(u8 *)(obj + 0xA8) = 0xFF;
}
