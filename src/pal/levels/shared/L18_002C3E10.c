#include "include_asm.h"

#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;
extern u8 D_00189E20[];
extern u32 D_00138320;
extern s32 D_L18_001AFBB0 MACRO_ADDR;
extern void func_PAL_L00_002D2668(s32, s32, float);
extern void func_PAL_L18_0042D088(u8 *, s32);
#define H ((Hero *)D_00189E20)

void func_PAL_L18_002C3E10(void)
{
    u8 *object;
    object = H->ptr[0x2290 / 4];
    if (*(s16 *)(object + 0xAA) != 0xEC0) {
        if ((D_00138320 & 0x80) && D_L18_001AFBB0 == 0 && H->h[0x1E0 / 2] == 0 && H->i[0x2294 / 4] != 0x6F) {
            H->b[0x22B8] = 1;
            H->b[0x22BA] = 1;
            if (object[0x43] != 11) {
                func_PAL_L00_002D2668(11, 1, 4.0f);
                H->f[0xC20 / 4] = 3.0f;
            }
        } else if (H->i[0xC28 / 4] & 2) {
            H->b[0x22B8] = 0;
            H->b[0x22BA] = 0;
            if (H->i[0x2294 / 4] == 0x8E) func_PAL_L00_002D2668(14, 0, 7.0f);
            else func_PAL_L00_002D2668(13, 0, 7.0f);
        }
    }
    object = H->ptr[0x2290 / 4];
    if (object[0x42] == 11 || (*(u64 *)(object + 0x40) & 0xFFFF0000ULL) == 0x0BFF0000ULL) {
        H->f[0xC20 / 4] = 3.0f;
        if (*(s16 *)(object + 0xAA) == 0xEE1) {
            if (H->i[0x1D8 / 4] > 2) {
                if (H->i[0x1D8 / 4] % 5 == 0) func_PAL_L18_0042D088(object, 0);
                if ((H->i[0x1D8 / 4] + 2) % 5 == 0) func_PAL_L18_0042D088(H->ptr[0x2290 / 4], 1);
            }
        } else if (*(s16 *)(object + 0xAA) == 0xED4 && H->i[0x1D8 / 4] % 5 != 0) {
            func_PAL_L18_0042D088(object, 0);
        }
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L18_002C4000);
