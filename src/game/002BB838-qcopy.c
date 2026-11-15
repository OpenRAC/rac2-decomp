#include "include_asm.h"
#include "names.h"

/* func_002BB838 (236 bytes, 28 places).
 *
 * The old draft was retail's body but for the 4.0f of func_00283CF0: the
 * reload hoisted the constant above the 16-byte copy.  The qcopy barrier
 * keeps the copy first, in retail's order.  Matches 28/28 in USA v1.01,
 * PAL and USA v2.00.
 */
extern void *part_alloc(int kind);
extern int FloatToInt(float f);
extern float IntToFloat(int n);
extern unsigned char *D_001F2560;

typedef int TI128_002BB838 __attribute__((mode(TI)));

void part_spawn_color_blend(void *position, void *velocity, int color, int endColor, int life, float f)
{
    void *particle;
    char *motion;
    int alphaRand;
    float sizeStep;

    if (life == 0)
        return;
    particle = part_alloc(8);
    if (particle == 0)
        return;
    *(TI128_002BB838 *)((char *)particle + 0x10) = *(TI128_002BB838 *)position;
    *(int *)((char *)particle + 4) = color;
    alphaRand = FloatToInt(4.0f);
    motion = (char *)particle + 0x20;
    *(unsigned char *)((char *)particle + 9) = (unsigned char)(alphaRand - 0x60);
    *(unsigned char *)((char *)particle + 3) = 0x48;
    *(unsigned char *)((char *)particle + 1) = 0;
    *(int *)((char *)particle + 0xC) = 0;
    *(unsigned char *)((char *)particle + 8) = 0;
    *(unsigned char *)((char *)particle + 2) = *D_001F2560;
    *(TI128_002BB838 *)motion = *(TI128_002BB838 *)velocity;
    *(short *)((char *)particle + 0xA) = life;
    *(int *)(motion + 0x18) = life;
    sizeStep = f / IntToFloat(life);
    *(int *)(motion + 0x14) = endColor;
    *(int *)(motion + 0x10) = color;
    *(float *)(motion + 0x1C) = sizeStep;
}
