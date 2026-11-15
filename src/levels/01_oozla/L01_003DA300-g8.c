#include "common.h"

extern u8 *func_0029EFD0(s32);
extern f32 func_002A7940(void);
extern void func_002A7470(u8 *, s32, s32, s32);
extern f32 D_L01_001B0828 __attribute__((sda));

typedef int SpawnQuad __attribute__((mode(TI)));
/* Measured state prefix; total allocation extent is unspecified. */
struct SpawnState {
    SpawnQuad position;
    u8 *handle;
    u8 unknown14[4];
    f32 weight;
};

/* Creates the 0xB24 object, seeds its state block and copies the two vectors in. */
u8 *func_L01_003DA300(u8 *a0, u8 *a1, u8 *a2, f32 f12)
{
    u8 *s1;
    struct SpawnState *state;

    s1 = CreateMoby(0xB24);
    if (s1 != 0) {
        *(u8 *)(s1 + 0x30) = 0xFF;
        *(u16 *)(s1 + 0x32) = 0xFF;
        *(u8 *)(s1 + 0x31) = 1;
        *(u8 *)(s1 + 0x20) = 0;
        state = *(struct SpawnState **)(s1 + 0x68);
        *(f32 *)(s1 + 0xF8) = func_002A7940();
        *(f32 *)(s1 + 0xF4) = func_002A7940();
        *(f32 *)(s1 + 0xF0) = func_002A7940();
        *(f32 *)(s1 + 0x2C) = *(f32 *)(*(u8 **)(s1 + 0x24) + 0x24) * D_L01_001B0828;
        state->handle = a2;
        state->weight = f12;
        qcopy(s1 + 0x10, a0);
        qcopy(&state->position, a1);
        if (*(u8 *)(s1 + 0x43) != 0)
            func_002A7470(s1, 0, 0, 0xA);
    }
    return s1;
}
