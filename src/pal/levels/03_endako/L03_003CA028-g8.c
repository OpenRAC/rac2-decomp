#include "include_asm.h"

#include "common.h"
extern f32 D_L03_001B0050 __attribute__((sda));
extern f32 D_L03_001B0054 __attribute__((sda));
extern f32 D_L03_001B0058[2] __attribute__((sda));
extern char D_L03_00188660[];
typedef struct { f32 scale; f32 spin; f32 wobble[2]; f32 roll; f32 fade; s32 slot; } SpinState;
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern f32  func_00283B98(f32 a0, f32 a1);
extern void func_L00_002E6CF0(void *a0, void *a1);
extern void func_L03_003C6208(void);
extern s32  func_002B38B8(char *a0);
extern f32  func_002AA2E8(f32 *a0, f32 a1, f32 a2);
extern void func_002E59F8(s32 a0);
extern s32  func_002E5CF8(s32 a0, s32 a1, char *a2);

void func_PAL_L03_003CA028(char *a0)
{
    char *s1 = a0;
    SpinState *s2 = *(SpinState **)(s1 + 0x68);

    switch (*(u8 *)(s1 + 0x20)) {
    case 0:
        *(f32 *)(s1 + 0x2C) = *(f32 *)(*(s32 *)(s1 + 0x24) + 0x24) * s2->scale;
        func_002A7750(s1, 1, -1);
        *(u16 *)(s1 + 0x34) |= 1;
        *(u8 *)(s1 + 0x31) = 0;
        s2->fade = 1.0f;
        break;
    case 1: {
        f32 k = 0.0003490659f;
        f32 *c = D_L03_001B0058;
        f32 *p = s2->wobble;
        s32 i;

        s2->spin = func_00283B98(s2->spin, D_L03_001B0050 * k);
        s2->roll = func_00283B98(s2->roll, D_L03_001B0054 * k);
        for (i = 1; i >= 0; i--) {
            *p = func_00283B98(*p, *c * 0.0003490659f);
            p++;
            c++;
        }
        func_L00_002E6CF0(func_L03_003C6208, s1);
        if (func_002B38B8(s1) != 0) {
            func_002AA2E8(&s2->fade, 0.0f, 0.040000003f);
            if (s2->fade <= 0.0f) {
                func_002A7750(s1, 2, -1);
                *(s32 *)(s1 + 0x98) = 0;
            }
        }
        break;
    }
    }
    if (*(u8 *)(s1 + 0x20) == 1) {
        char *p = D_L03_00188660 + s2->slot * 0x70;

        if (*(char **)(p + 0x88) != s1 || *(u8 *)(p + 0x74) == 0)
            s2->slot = func_002E5CF8(0, 4, s1);
    } else {
        s32 v = s2->slot;

        if (v != -1) {
            char *p = D_L03_00188660 + v * 0x70;

            if (*(char **)(p + 0x88) == s1 && *(u8 *)(p + 0x74) != 0)
                func_002E59F8(v);
        }
        s2->slot = -1;
    }
}
