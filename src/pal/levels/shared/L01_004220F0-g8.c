#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef float f32;
extern void FastVecAdd(u8 *, u8 *, u8 *);
extern f32 g_moby_hit_radius_scale __attribute__((sda));
extern f32 FastAddRotations(f32, f32);
extern void moby_mark_spawned(u8 *);

/* Same body as func_L03_0042B930, with this function's own callees. */
void entity_l01_age_and_blend_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *owner = *(u8 **)(moby + 0x24);

    *(f32 *)(moby + 0x2C) = *(f32 *)(owner + 0x24) * g_moby_hit_radius_scale;
    *(f32 *)(vars + 0x8) = *(f32 *)(vars + 0x8) - 0.006f;
    FastVecAdd(moby + 0x10, moby + 0x10, vars);
    FastVecAdd(moby + 0xF0, moby + 0xF0, vars + 0x10);
    *(f32 *)(moby + 0xF0) = FastAddRotations(*(f32 *)(moby + 0xF0), *(f32 *)(vars + 0x10));
    *(f32 *)(moby + 0xF4) = FastAddRotations(*(f32 *)(moby + 0xF4), *(f32 *)(vars + 0x14));
    *(f32 *)(moby + 0xF8) = FastAddRotations(*(f32 *)(moby + 0xF8), *(f32 *)(vars + 0x18));
    moby[0xBC] = moby[0xBC] - 1;
    if (moby[0xBC] == 0)
        moby_mark_spawned(moby);
}
