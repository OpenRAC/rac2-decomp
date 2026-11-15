#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
typedef float f32;
extern void FastVecAdd(u8 *, u8 *, u8 *);
extern f32 D_L03_001B1FC4 __attribute__((sda));
extern f32 FastAddRotations(f32, f32);
extern void moby_mark_spawned(u8 *);

/* Same body as func_L03_0042B930, with this function's own callees. */
/* Moves and turns a falling piece of debris (moby class 1086), makes it fall faster each frame, and removes it when its time runs out. */
void falling_l00_debris_update(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    u8 *config = *(u8 **)(object + 0x24);

    *(f32 *)(object + 0x2C) = *(f32 *)(config + 0x24) * D_L03_001B1FC4;
    *(f32 *)(vars + 0x8) = *(f32 *)(vars + 0x8) - 0.0041666669f;
    FastVecAdd(object + 0x10, object + 0x10, vars);
    FastVecAdd(object + 0xF0, object + 0xF0, vars + 0x10);
    *(f32 *)(object + 0xF0) = FastAddRotations(*(f32 *)(object + 0xF0), *(f32 *)(vars + 0x10));
    *(f32 *)(object + 0xF4) = FastAddRotations(*(f32 *)(object + 0xF4), *(f32 *)(vars + 0x14));
    *(f32 *)(object + 0xF8) = FastAddRotations(*(f32 *)(object + 0xF8), *(f32 *)(vars + 0x18));
    object[0xBC] = object[0xBC] - 1;
    if (object[0xBC] == 0)
        moby_mark_spawned(object);
}
