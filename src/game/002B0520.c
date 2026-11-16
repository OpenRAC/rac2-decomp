#include "include_asm.h"
#include "common.h"

typedef int TI __attribute__((mode(TI)));

extern u8 *g_heightmap_data MACRO_ADDR;
extern f32 g_heightmap_origin[] __attribute__((sda));
extern f32 g_heightmap_cell_width MACRO_ADDR;
extern f32 g_heightmap_cell_depth MACRO_ADDR;
extern f32 g_heightmap_height_scale MACRO_ADDR;
extern s32 g_heightmap_cache_key MACRO_ADDR;
extern s32 g_map_mode;

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
    if (g_heightmap_data == 0) {
        return 0.0f;
    }
    FastVecSub(rel, world_pos, g_heightmap_origin);
    rel[0] = rel[0] / g_heightmap_cell_width;
    rel[1] = rel[1] / g_heightmap_cell_depth;
    if (rel[0] < 0.0f || 256.0f < rel[0] || rel[1] < 0.0f || 256.0f < rel[1] || g_heightmap_cache_key != g_map_mode) {
        return 1023.0f;
    }
    cell_index = FloatToInt(rel[1]) << 8;
    cell_index += FloatToInt(rel[0]);
    height_byte = g_heightmap_data[cell_index];
    if (height_byte == 0xFF) {
        return 1023.0f;
    }
    return IntToFloat(height_byte) * g_heightmap_height_scale + g_heightmap_origin[2];
}
