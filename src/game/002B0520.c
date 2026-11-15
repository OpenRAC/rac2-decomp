#include "include_asm.h"
#include "common.h"

typedef int TI __attribute__((mode(TI)));

extern u8 *D_001B1A20 MACRO_ADDR;
extern f32 D_001B19E0[] __attribute__((sda));
extern f32 D_001B1A10 MACRO_ADDR;
extern f32 D_001B1A14 MACRO_ADDR;
extern f32 D_001B1A18 MACRO_ADDR;
extern s32 D_001A91C0 MACRO_ADDR;
extern s32 D_001C4F40;

extern void FastVecSub(void *, void *, void *);
extern float IntToFloat(int);
extern int FloatToInt(float);

/* Looks up the terrain height under a position from a height map, giving a large default when the position is off the map. */
float coll_get_heightmap_height(TI *position) {
    float world_pos[4] __attribute__((aligned(16)));
    float rel[4] __attribute__((aligned(16)));
    s32 cell_index;
    u8 height_byte;

    *(TI *)world_pos = *position;
    if (D_001B1A20 == 0) {
        return 0.0f;
    }
    FastVecSub(rel, world_pos, D_001B19E0);
    rel[0] = rel[0] / D_001B1A10;
    rel[1] = rel[1] / D_001B1A14;
    if (rel[0] < 0.0f || 256.0f < rel[0] || rel[1] < 0.0f || 256.0f < rel[1] || D_001A91C0 != D_001C4F40) {
        return 1023.0f;
    }
    cell_index = FloatToInt(rel[1]) << 8;
    cell_index += FloatToInt(rel[0]);
    height_byte = D_001B1A20[cell_index];
    if (height_byte == 0xFF) {
        return 1023.0f;
    }
    return IntToFloat(height_byte) * D_001B1A18 + D_001B19E0[2];
}
