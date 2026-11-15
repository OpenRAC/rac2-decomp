#include "common.h"

extern s32 D_001A79F0;
extern float D_L05_001B1B1C __attribute__((sda));

extern unsigned long func_0027C878(s32);
extern float func_00283B98(float, float);
extern void func_L05_00444FD0(float, float, float, float, float, s32, s32, long, s32, s32, s32, s32, s32);

/* Draws the four quarter-turn copies of a sprite ring around the point, the same size each time. */
void func_L05_00444DF8(u8 a, u8 b, u8 c, u8 d, float x, float y, float scale, float angle)
{
    unsigned long sprite;
    float size;

    if (D_001A79F0 == 0x14)
        sprite = GetEffectTextureDescriptor(0x41);
    else
        sprite = GetEffectTextureDescriptor(0x3F);
    size = D_L05_001B1B1C * scale;
    func_L05_00444FD0(x, y, size, size, angle, 0x3F, 0x3F, sprite, 0xFFFFF3, a, b, c, d);
    angle = FastAddRotations(angle, 1.5707964f);
    func_L05_00444FD0(x, y, size, size, angle, 0x3F, 0x3F, sprite, 0xFFFFF3, a, b, c, d);
    angle = FastAddRotations(angle, 1.5707964f);
    func_L05_00444FD0(x, y, size, size, angle, 0x3F, 0x3F, sprite, 0xFFFFF3, a, b, c, d);
    func_L05_00444FD0(x, y, size, size, FastAddRotations(angle, 1.5707964f), 0x3F, 0x3F, sprite, 0xFFFFF3, a, b, c, d);
}
