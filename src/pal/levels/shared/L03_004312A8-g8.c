#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef float f32;
extern void FastVecAdd(u8 *, u8 *, u8 *);
extern f32 D_L03_001B1FC4 __attribute__((sda));
extern f32 FastAddRotations(f32, f32);
extern void moby_mark_spawned(u8 *);

/* Same body as func_L03_0042B930, with this function's own callees. */
void func_PAL_L03_004312A8(u8 *a0) {
    u8 *q = *(u8 **)(a0 + 0x68);
    u8 *r = *(u8 **)(a0 + 0x24);

    *(f32 *)(a0 + 0x2C) = *(f32 *)(r + 0x24) * D_L03_001B1FC4;
    *(f32 *)(q + 0x8) = *(f32 *)(q + 0x8) - 0.006f;
    FastVecAdd(a0 + 0x10, a0 + 0x10, q);
    FastVecAdd(a0 + 0xF0, a0 + 0xF0, q + 0x10);
    *(f32 *)(a0 + 0xF0) = FastAddRotations(*(f32 *)(a0 + 0xF0), *(f32 *)(q + 0x10));
    *(f32 *)(a0 + 0xF4) = FastAddRotations(*(f32 *)(a0 + 0xF4), *(f32 *)(q + 0x14));
    *(f32 *)(a0 + 0xF8) = FastAddRotations(*(f32 *)(a0 + 0xF8), *(f32 *)(q + 0x18));
    a0[0xBC] = a0[0xBC] - 1;
    if (a0[0xBC] == 0)
        moby_mark_spawned(a0);
}
