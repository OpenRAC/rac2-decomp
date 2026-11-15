#include "common.h"
typedef struct {
    f32 samples[16][16];
    f32 pad_400[0x20];
    f32 bottom_edge[16];
    f32 right_edge[16];
    f32 pad_500[0x23];
    f32 corner;
    f32 pad_590[0xC];
} SurfaceHeightLayer;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 pad_C[0x44];
    SurfaceHeightLayer layers[3];
} SurfaceHeightTile;
typedef struct {
    u8 pad_0[8];
    f32 origin_x;
    f32 origin_y;
    f32 cell_width;
    f32 cell_height;
} SurfaceHeightGrid;
extern SurfaceHeightTile * D_001B22D0[] __attribute__((sda));
extern SurfaceHeightGrid ref_L00_002FD828_00 __attribute__((sda));
extern int ref_L00_002FD828_01 __attribute__((sda));
extern float func_00283CE0(int);
extern s32 func_002FCFC8(f32, f32, f32);
extern s32 func_00283CF0(f32) ;
extern void func_00282DD8(f32 *, f32 *, f32 *);
extern void func_00282F20(f32 *, f32 *, f32) ;

/* Adapted from Lombyte's project (GPL-3.0) for PAL by OpenRAC's tools/port.py: src/textbin/fun_00239f58.c, func_002FD828. */
/* Finds the water surface height (and optionally its slope) at a point; returns 0 if no patch is there. */
s32 func_002FD828(f32 *height, f32 *normal, f32 x, f32 y, f32 z) {
    f32 x_tangent[4] __attribute__((aligned(16)));
    f32 y_tangent[4] __attribute__((aligned(16)));
    SurfaceHeightTile *tile;
    s32 tile_index;
    s32 column;
    s32 row;
    f32 fraction_x;
    f32 fraction_y;
    f32 h00;
    f32 h10;
    f32 h01;
    f32 h11;
    f32 first_row_height;
    f32 weight_x;
    f32 weight_y;

    tile_index = FindSurfaceBoxAtPoint(x, y, z);
    if (tile_index < 0) {
        return 0;
    }
    tile = &gSurfaceHeightTiles[0][tile_index];
    fraction_x = tile->x;
    fraction_y = tile->y;
    fraction_x += ref_L00_002FD828_00.origin_x;
    fraction_y += ref_L00_002FD828_00.origin_y;
    fraction_x = x - fraction_x;
    fraction_y = y - fraction_y;
    column = FloatToInt(fraction_x / ref_L00_002FD828_00.cell_width);
    row = FloatToInt(*&fraction_y / ref_L00_002FD828_00.cell_height);
    fraction_x -= IntToFloat(column) * ref_L00_002FD828_00.cell_width; weight_x = fraction_x / ref_L00_002FD828_00.cell_width;
    fraction_y -= IntToFloat(row) * ref_L00_002FD828_00.cell_height;
    /* Divide the signed remainder after rounding the row, before choosing the sample bank. */
    weight_y = fraction_y / ref_L00_002FD828_00.cell_height;
    h00 = tile->layers[ref_L00_002FD828_01].samples[row][column];
    if (column == 15) {
        h10 = tile->layers[ref_L00_002FD828_01].right_edge[row];
    } else {
        h10 = tile->layers[ref_L00_002FD828_01].samples[row][column + 1];
    }
    if (row == 15) {
        h01 = tile->layers[ref_L00_002FD828_01].bottom_edge[column];
    } else {
        h01 = tile->layers[ref_L00_002FD828_01].samples[row + 1][column];
    }
    if (column == 15) {
        if (row == 15) {
            h11 = tile->layers[ref_L00_002FD828_01].corner;
        } else {
            h11 = tile->layers[ref_L00_002FD828_01].right_edge[row + 1];
        }
    } else if (row == 15) {
        h11 = tile->layers[ref_L00_002FD828_01].bottom_edge[column + 1];
    } else {
        h11 = tile->layers[ref_L00_002FD828_01].samples[row + 1][column + 1];
    }
    if (height != 0) {
        first_row_height = h00 + (h10 - h00) * weight_x;
        *height = first_row_height +
                  ((h01 + (h11 - h01) * weight_x) - first_row_height) * weight_y + tile->z;
    }
    if (normal != 0) {
        x_tangent[0] = ref_L00_002FD828_00.cell_width;
        x_tangent[1] = 0.0f;
        x_tangent[2] = h10 - h00;
        x_tangent[3] = 1.0f;
        y_tangent[0] = 0.0f;
        y_tangent[1] = ref_L00_002FD828_00.cell_height;
        y_tangent[2] = h01 - h00;
        y_tangent[3] = 1.0f;
        FastVecCross(normal, x_tangent, y_tangent);
        vec_scale_to_length(normal, normal, 1.0f);
    }
    return 1;
}
