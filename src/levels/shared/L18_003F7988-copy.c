#include "names.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef float f32;
typedef int Quad __attribute__((mode(TI)));
extern void func_002833F0(char *, char *);
extern void func_002A7750(u8 *, u8, s32);

/* Restores the saved spawn transform and starts the object in its idle state. */
void func_L18_003F7988(u8 *self) {
    u8 *state = *(u8 **)(self + 0x68);
    state[0x2E] = 1;
    *(f32 *)(state + 0x20) = *(s16 *)(state + 0x24);
    self[0x7F] = 0;
    *(Quad *)(self + 0x10) = *(Quad *)(state + 0x210);
    *(Quad *)(self + 0xF0) = *(Quad *)(state + 0x220);
    euler_rotation_basis((char *)self + 0xC0, (char *)self + 0xF0);
    SetMobyState(self, 0, -1);
}

/* Restores the second object's saved transform and collision settings. */
void func_L18_003FC9B8(u8 *self) {
    u8 *state = *(u8 **)(self + 0x68);
    u8 *model = *(u8 **)(self + 0x24);
    *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) & 0xFFBE) | 0x1000;
    *(s32 *)(self + 0x98) = *(s32 *)(model + 0x10);
    *(s32 *)(self + 0x98) = *(s32 *)(model + 0x10);
    *(Quad *)(self + 0x10) = *(Quad *)(state + 0x60);
    *(Quad *)(self + 0xF0) = *(Quad *)(state + 0x70);
    euler_rotation_basis((char *)self + 0xC0, (char *)self + 0xF0);
    SetMobyState(self, 0, -1);
}
