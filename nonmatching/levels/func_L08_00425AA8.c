/* func_L08_00425AA8: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections -ffast-math.
   Full initializer reconstructed. The retail min.s source/profile reduced 1064 to 1040 bytes. Constant setup and stores still schedule differently.
   No linked match is claimed.
*/

#include "common.h"
#define W(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
extern s32 func_00283CF0(f32), func_L08_003D3D80(void *);
extern void func_L08_00425398(void *), func_L01_003377C8(void *);
extern f32 func_L08_0032EF80(void *, s32, s32, s32, s32);
extern f32 func_L08_00425328(void *, f32, f32, f32);
extern void func_0026FEB8(void *, s32, s32, s32), func_002A7750(void *, s32, s32);
extern void func_002A7470(void *, s32, s32, s32);
extern u8 *D_L08_001FE7C0[];
extern u8 D_L08_001B1BD0[];

void func_L08_00425AA8(u8 *object)
{
    f32 point[4], height;
    s32 priority;
    u8 *state = *(u8 **)(object + 0x68);
    state[0x48] = func_00283CF0(40.0f);
    state[0x4A] = func_00283CF0(64.0f);
    state[0x29] = 1;
    qcopy(state + 0x170, object + 0x10);
    F(state, 0x208) = F(object, 0xF8);
    func_L08_00425398(object);
    if (object[0x21] != 0xFF && W(*(u8 **)(state + 0x200), 0) != 0x4CB2F) {
        W(*(u8 **)(state + 0x1FC), 0) = 0;
        W(*(u8 **)(state + 0x1F8), 0) = 0;
        W(*(u8 **)(state + 0x200), 0) = 0x4CB2F;
    }
    state[0x20E] = object[0x30];
    qcopy(point, object + 0x10);
    height = func_L08_0032EF80(point, W(state, 0x1D0), -1, W(state, 0x1D4), -1);
    if (height > 0.0f) object[0x30] = func_00283CF0(height + 2.0f);
    state[0x20E] = object[0x30];
    state[0x20F] = object[0x30];
    qcopy(point, object + 0x10);
    height = func_L08_0032EF80(point, W(state, 0x1D8), W(state, 0x1E0), W(state, 0x1DC), -1);
    if (height > 0.0f) state[0x20E] = func_00283CF0(height + 2.0f);
    if (W(state, 0x1E4) != -1) func_L01_003377C8(D_L08_001FE7C0[W(state, 0x1E4)]);
    state[0x60] = 5; state[0x61] = 8; state[0x62] = 8;
    state[0x66] = 10; state[0x67] = 11;
    F(state, 0x6C) = 0.38333336f;
    F(state, 0x70) = 0.23333335f;
    F(state, 0x74) = 1.0f / 240.0f;
    F(state, 0x78) = 1.0f / 120.0f;
    F(state, 0x7C) = 1.0f / 360.0f;
    F(state, 0x80) = 2.75f; F(state, 0x84) = 0.0f; F(state, 0x8C) = 0.4f;
    W(state, 0x98) = -1;
    state[0xBC] = 7; state[0xBD] = 24; state[0xBE] = 6; state[0xBF] = 13;
    state[0xC2] = 7; state[0xC3] = 14; state[0xC4] = 0; state[0xC5] = 0;
    state[0xC6] = 1; state[0xC7] = 1;
    W(state, 0xCC) = W(state, 0x1E4);
    state[0x2E] = 3; state[0x28] = 1; F(state, 0x30) = 0.0f; F(state, 0x1F0) = 1.0f;
    qzero(state + 0x190);
    qcopy(state + 0x180, object + 0x10);
    qzero(state + 0x1A0);
    if (F(state, 0x1C4) == 0.0f) {
        height = func_L08_00425328(object + 0x10, F(object, 0x18) + 20.0f, F(state, 0x90), F(state, 0x90));
        F(state, 0x1C4) = height;
        F(state, 0x1C8) = height < F(state, 0x178) ? height : F(state, 0x178);
    }
    if (F(state, 0x1C4) > 0.0f) F(object, 0x18) = F(state, 0x1C4) - 0.5f;
    W(state, 0x22C) = func_L08_003D3D80(object);
    *(u16 *)(state + 0x1BE) = 0;
    if (state[0x20C] == 1 || state[0x20C] == 4) {
        func_0026FEB8(D_L08_001B1BD0, *(s16 *)(object + 0xB2), state[0x20C], state[0x20C] + 1);
        state[0x20C]++;
    }
    qcopy(state + 0x170, object + 0x10);
    *(u16 *)(object + 0x34) &= 0xEFFF;
    func_002A7750(object, 1, -1);
    if (object[0x43]) func_002A7470(object, 0, 0, 2);
    W(object, 0x98) = 0;
    object[0x31] = 0;
    *(u16 *)(object + 0x34) |= 1;
    priority = *(s16 *)(object + 0x32);
    if (priority < state[0x20E]) priority = state[0x20E];
    state[0x20E] = priority;
    if (object[0x21] != 0xFF) {
        if ((s32)state[0x20D] < W(*(u8 **)(state + 0x1FC), 0)) state[0x20D] = **(u8 **)(state + 0x1FC);
        W(*(u8 **)(state + 0x1FC), 0)++;
    }
}
