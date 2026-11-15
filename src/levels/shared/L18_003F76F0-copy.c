#include "names.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef unsigned int u32;
typedef float f32;
typedef int Quad __attribute__((mode(TI)));
extern s32 func_L18_0032B768(u8 *, s32, s32);
extern void func_002A7750(u8 *, u8, s32);

/* Activates the waiting object at its supplied position and saves its impulse. */
void func_L18_003F76F0(u8 *self, void *position, void *impulse) {
    u8 *state;
    if ((u32)(self[0x20] - 1) >= 2) return;
    state = *(u8 **)(self + 0x68);
    state[0x2E] = 1;
    *(f32 *)(state + 0x20) = *(s16 *)(state + 0x24);
    self[0x7F] = 0;
    *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) & 0xFFBE) | 0x1000;
    *(s32 *)(self + 0x98) = *(s32 *)(*(u8 **)(self + 0x24) + 0x10);
    self[0x31] = 0;
    *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) & ~2) | 1;
    SetTableEntryByte(self, 0, 3);
    SetMobyState(self, 3, 0);
    *(s32 *)(self + 0x98) = *(s32 *)(*(u8 **)(self + 0x24) + 0x10);
    *(u16 *)(self + 0x34) |= 0x1000;
    *(Quad *)(self + 0x10) = *(Quad *)position;
    *(Quad *)(state + 0x1A0) = *(Quad *)impulse;
    *(f32 *)(state + 0x104) = 0.009999999776482582f;
    *(f32 *)(state + 0x100) = 0.49000000953674316f;
    *(f32 *)(state + 0x108) = 2.0f;
    *(f32 *)(state + 0x10C) = 5.0f;
    *(s32 *)(state + 0x180) = 0;
}
