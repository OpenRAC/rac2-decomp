#include "include_asm.h"

#include "common.h"
extern f32 func_2E5318(f32 a, f32 b);
extern f32 func_2E4918(f32 a, f32 b);
extern f32 D_L07_001B0F84 __attribute__((sda));
extern u8 *D_L07_001B22DC __attribute__((sda));
extern u8 *func_2CD050(s32 a);
extern s32 func_312FA8(u8 *a, s32 b, s32 c);
extern f32 func_313008(u8 *a, s32 b);
extern f32 D_L07_001B10B8 __attribute__((sda));
extern f32 D_L07_001B10BC __attribute__((sda));
extern u32 D_L07_001B10C0 __attribute__((sda));
extern f32 D_L07_001B0FD0 __attribute__((sda));
extern f32 D_L07_001B0E98 __attribute__((sda));
extern f32 D_L07_001B0E9C __attribute__((sda));
extern f32 D_L07_001B0EA0 __attribute__((sda));
extern f32 func_002AA2E8(f32 *value, f32 target, f32 step);
extern f32 func_00283B98(f32 a, f32 b);
extern s32 func_L01_003120A8(void *a, void *b, void *c, s32 d, f32 e, f32 f, s32 g, s32 h, s32 i);
extern f32 D_L07_001B173C;
extern u8 D_L07_001B1730 __attribute__((sda));
extern u8 *D_L07_001B2954;
extern u8 *D_L07_001B295C;
extern s32 D_L07_001B1E90;
extern void func_L00_00424A08(s32, f32, f32);
extern void func_L00_00424A50(f32, f32);
extern u8 *func_PAL_L00_002D7850(s32);
typedef struct { f32 x, y; u8 pad08[0x2C]; u32 color; } Effect;
typedef struct { u8 pad[0x450]; Effect *effect; } EffectState;
extern f32 func_2E49C8(f32 a, f32 b);
extern f32 func_2E5360(f32 a, f32 b);
extern f32 D_L07_001B17D4 __attribute__((sda));
extern f32 D_L07_001B17D8 __attribute__((sda));
extern u8 *D_L07_001B9250 __attribute__((nosda));
extern u8 *D_L07_001ADAAC MACRO_ADDR;
extern u8 D_L07_001B31A9;
extern u8 D_00189E20[];
extern u32 D_L07_001B1E08 MACRO_ADDR;
extern f32 func_00282E48(u8 *a, u8 *b);
extern f32 D_L07_001B0FD0 __attribute__((sda));
extern u8 *D_L07_001C36C0[];

void func_PAL_L07_003FCFE0(u8 *a0)
{
    EffectState *s1 = *(EffectState **)(a0 + 0x68);

    func_L00_00424A08(0, D_L07_001B10B8, 0.003f);
    func_L00_00424A50(D_L07_001B10BC, 0.003f);
    if (*(u8 *)(a0 + 0x95) != 0) {
        if (s1->effect == 0)
            s1->effect = (Effect *)func_PAL_L00_002D7850(5);
        {
            f32 x = D_L07_001B10B8;
            f32 y = D_L07_001B10BC;
            u32 z;
            s1->effect->x = x;
            z = D_L07_001B10C0;
            s1->effect->y = y;
            s1->effect->color = z;
        }
    }
}
