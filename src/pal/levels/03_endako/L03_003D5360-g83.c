#include "include_asm.h"

#include "common.h"
extern char *CreateMoby(s32);
extern void moby_init_child_from_parent(char *, char *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 vec_length_xy(f32 *);
extern f32 D_L03_001B0648 __attribute__((sda));

char *func_PAL_L03_003D5A98(char *a0, char *a1, f32 *a2, s32 a3)
{
    char *s1 = CreateMoby(0xA02);
    char *s0;

    if (s1 != 0) {
        s0 = *(char **)(s1 + 0x68);
        moby_init_child_from_parent(s1, a0);
        qcopy(s1 + 0x10, a1);
        qcopy(s0, a2);
        *(f32 *)(s1 + 0xF8) = mat_fast_helper_a(a2[0], a2[1]);
        {
            f32 t = vec_length_xy(a2);
            f32 angle = -mat_fast_helper_a(t, a2[2]);
            f32 scale = D_L03_001B0648;

            *(f32 *)(s1 + 0xF4) = angle;
            *(s32 *)(s0 + 0x30) = 0x64;
            *(s32 *)(s0 + 0x38) = a3;
            *(f32 *)(s1 + 0x2C) = *(f32 *)(*(u32 *)(s1 + 0x24) + 0x24)
                * scale;
        }
    }
    return s1;
}
