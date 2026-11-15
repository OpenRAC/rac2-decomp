#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef float f32;
extern float D_L22_001AF3EC __attribute__((sda));
extern float D_L22_001AF5C8 __attribute__((sda));
extern s16 D_0018A16E[];
extern f32 math_fabs(f32 f);

s32 func_PAL_L22_003A9540(u8 *a0) {
    u8 *s = *(u8 **)(a0 + 0x68);
    f32 t;
    if (*(f32 *)(s + 0x3DC) < D_L22_001AF3EC) return 1;
    t = math_fabs(*(f32 *)(s + 0x414) - *(f32 *)(s + 0x410));
    if (D_0018A16E[0] < 0x9) return 0;
    if (*(f32 *)(s + 0x3E0) < D_L22_001AF3EC) {
        if (t < D_L22_001AF5C8) return 1;
    }
    return 0;
}
