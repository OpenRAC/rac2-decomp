#include "include_asm.h"
#include "common.h"

typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Quad __attribute__((aligned(16)));

extern u8 D_L22_001B9C80[];
extern s32 D_L22_001B2040;
extern f32 D_L22_001B0A0C __attribute__((sda));
extern f32 D_L22_001B0A10 __attribute__((sda));
extern f32 func_00282E48(void *a0, void *a1);
extern f32 func_00283CE0(s32 a0);
extern f32 func_002A78D8(f32 a0, f32 a1);
extern f32 func_002A7940(void);
extern void func_00283098(void *a0, void *a1, void *a2);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern void func_L16_003C3A10(void *a0, void *a1, void *a2);

void func_L22_003F52D8(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    f32 f23 = 60.0f / func_00282E48(D_L22_001B9C80, a0 + 0x10);
    f32 f22;
    f32 f25;
    f32 lim;
    f32 k;
    s32 i;
    Quad v0, v10, v20;

    if (f23 > 2.2f)
        f23 = 2.7f;
    k = *(f32 *)(state + 0xA0);
    f22 = f23 * f23 * k * D_L22_001B0A0C;
    lim = (f32)D_L22_001B2040 * D_L22_001B0A10;
    f25 = k / f22;
    if (f22 > lim)
        f22 = lim;
    for (i = 0; (f32)i < f22; i++) {
        f32 f21 = func_00283CE0(i) * f25;
        f32 f20 = f23 + f21 * 0.1f;

        v10.q = 0;
        v10.f[0] = func_002A78D8(0.0f, f20);
        v10.f[1] = func_002A78D8(0.0f, f20);
        v10.f[2] = f21;
        v0.q = v10.q;
        func_00283098(&v0, &v0, a0 + 0xC0);
        func_00282CC0(&v0, &v0, a0 + 0x10);
        v20.q = 0;
        v20.f[0] = func_002A7940();
        v20.f[1] = func_002A7940();
        v20.f[2] = func_002A7940();
        v10.q = v20.q;
        func_L16_003C3A10(a0, &v0, &v10);
    }
}
