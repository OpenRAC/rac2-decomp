#include "include_asm.h"
#include "common.h"

extern f32 D_L18_001B06AC[] __attribute__((sda));
extern f32 D_L18_001B0778 __attribute__((sda));
extern f32 D_L18_001B077C[] NOT_SDA;
extern s32 D_L18_001B0780 __attribute__((sda));
extern f32 D_L18_001B0784 __attribute__((sda));

extern void func_002820A0(void);
extern f32 func_002AA140(f32, f32, f32);
extern s32 func_00283CF0(f32);
extern void func_002820D0(void *, s32, s32, f32, f32, f32);

/* The func_L18_0043E9B0 pulse driven by a clamped ratio of the state's +0xC0 timer; the
   count and size go to the state's own emitter at +0x90. */
/* Fires a burst of effect particles whose number and size depend on a timer value. */
void func_L18_003FD730(u8 *moby) {
    u8 *state;
    f32 ratio;
    f32 intensity;
    s32 particleCount;

    SetGsRegisterConstant();
    state = *(u8 **)(moby + 0x68);
    ratio = *(f32 *)(state + 0xC0) / D_L18_001B06AC[0];
    if (ratio > 1.0f)
        ratio = 1.0f;
    else if (ratio < 0.0f)
        ratio = 0.0f;
    intensity = LerpFloat_002AA140(D_L18_001B0778, D_L18_001B077C[0], ratio);
    if (ratio < 0.1f) {
        particleCount = FloatToInt((f32)D_L18_001B0780 * ratio * 10.0f);
    } else {
        particleCount = FloatToInt((f32)D_L18_001B0780 * (1.0f - ratio));
    }
    DrawBillboardQuadWithUv(state + 0x90, particleCount, 0, intensity, D_L18_001B0784, 0.08f);
}
