#include "include_asm.h"

#include "common.h"
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; } Hero;
extern u8 D_00189E20[];
extern float D_001A7DB0[] MACRO_ADDR;
extern void func_L00_002B39F0(int, float);
#define H ((Hero *)D_00189E20)

void func_PAL_L00_002B3C38(void)
{
    func_L00_002B39F0(0, 1.0f);
    if (0.0f < H->f[0x1B0 / 4]) {
        H->f[0x1B0 / 4] = D_001A7DB0[4] * (H->f[0x24B8 / 4] * 0.020000001f);
    }
    if (H->i[0x2294 / 4] == 0x70) {
        H->f[0x1B0 / 4] = H->f[0x1B0 / 4] * 0.8f;
        if (H->f[0x1B0 / 4] < 0.050000004f) {
            H->f[0x1B0 / 4] = 0.050000004f;
        }
    }
}

