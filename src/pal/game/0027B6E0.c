#include "include_asm.h"
#include "common.h"

/* func_PAL_0027B6E0, the PAL copy of func_0027B2F8: the same C, without the stores of 32.0f to fA0
   and 1048576.0f to fA4. */

extern float func_00283CE0(int);
/* Partial view of the shared screen/render state. */
typedef struct {
    char pad[0xA0];
    float fA0, fA4;
    char gap[8];
    float fB0;
    char gapB4[0x14C];
    float f200, f204, f208, f20C;
    char gap210[8];
    float f218, f21C;
    char gap220[8];
    float f228, f22C;
    int color[3];
} ScreenState;
extern ScreenState D_001B9040;
extern void func_0027AB40(void);

typedef struct {
    int width, height, half_width, half_height;
    int left, top, right, bottom;
} ScreenExtent;
extern ScreenExtent D_001A7340 __attribute__((sda));

void func_PAL_0027B6E0(int width, int height, float scale, float a, float b, float c, float d)
{
    ScreenState *context = &D_001B9040;
    int halfW = width >> 1;
    int halfH = height >> 1;
    float halfHeight;
    D_001A7340.width = width;
    D_001A7340.height = height;
    D_001A7340.half_width = halfW;
    D_001A7340.half_height = halfH;
    D_001A7340.left = (2048 - halfW) << 4;
    D_001A7340.top = (2048 - halfH) << 4;
    D_001A7340.right = (halfW + 2048) << 4;
    D_001A7340.bottom = (halfH + 2048) << 4;
    context->fB0 = scale;
    context->f200 = func_00283CE0(width) * 0.5f;
    halfHeight = func_00283CE0(height) * 0.5f;
    context->f204 = halfHeight;
    context->f208 = context->f200 * 4.0f;
    context->f20C = halfHeight * 4.0f;
    context->f218 = a;
    context->f21C = b;
    context->f228 = c;
    context->f22C = d;
    func_0027AB40();
}

INCLUDE_ASM("asm/pal/game", func_PAL_0027B810);
