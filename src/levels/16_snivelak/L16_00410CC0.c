#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

/* Partial table view: retail visits up to eight four-short rows. GP access
 * is independently evidenced; this is not a complete global extent claim. */
typedef struct { s16 row[8][4]; } RowTablePrefix;
extern RowTablePrefix g_snivelak_path_neighbor_table __attribute__((sda));

extern u32 g_path_l16_table[];

extern float math_closest_point_on_segment(void *, void *, void *, void *);

extern float vec_distance_xy(void *, void *);

/* Walks the level's table of short rows, keeping the closest match of the handle's
   measured pair in the handle and the winning row in the handle's second half. */
void snivelak_find_closest_path_point(u8 *moby, u8 *point)
{
    TI128 best_point;
    TI128 work;
    u32 *vars;
    u8 *path;
    s32 next;
    u8 *best_out;
    f32 best;
    f32 along;
    f32 dist;
    s32 row;
    s32 count;
    s16 neighbor;
    s16 *row_ptr;

    vars = *(u32 **)(moby + 0x68);
    best = 2001.0f;
    path = *(u8 **)(g_path_l16_table + vars[92]);
    qcopy(&best_point, point);
    best_out = (u8 *)vars + 0x200;
    for (row = 0; row < 8; row = next) {
        count = 0;
        neighbor = g_snivelak_path_neighbor_table.row[row][0];
        next = row + 1;
        if (neighbor == -1)
            continue;
        row_ptr = g_snivelak_path_neighbor_table.row[row];
        do {
            if (neighbor >= row) {
                along = math_closest_point_on_segment(&work, path + (row * 16 + 0x10), path + (neighbor * 16 + 0x10), point);
                dist = vec_distance_xy(point, &work);
                if (dist < best) {
                    best = dist;
                    vars[0x7E] = neighbor;
                    *(f32 *)((u8 *)vars + 0x1FC) = along;
                    vars[0x7D] = row;
                    qcopy(&best_point, &work);
                }
            }
            count++;
            row_ptr++;
            if (count >= 4)
                break;
            neighbor = *row_ptr;
        } while (neighbor != -1);
    }
    qcopy(best_out, &best_point);
}

/* Picks which two path points the boss should walk between next when it has moved onto a different part of the path. */
void snivelak_pick_next_path_segment(u8 *moby)
{
    s32 *vars;
    s32 mask;
    s32 acc;
    s32 i;
    s32 j;
    s32 neighbor;

    vars = *(s32 **)(moby + 0x68);
    if (vars[0x7D] == vars[0x88] || vars[0x7D] == vars[0x89]) {
        vars[0x8A] = vars[0x7D];
        vars[0x8B] = vars[0x7E];
        return;
    }
    if (vars[0x7E] == vars[0x88] || vars[0x7E] == vars[0x89]) {
        vars[0x8A] = vars[0x7E];
        vars[0x8B] = vars[0x7D];
        return;
    }
    mask = (1 << vars[0x7D]) | (1 << vars[0x7E]);
    acc = 0;
    for (;;) {
        for (i = 0; i < 8; i++) {
            if ((mask >> i) & 1) {
                for (j = 0; j < 4 && (neighbor = g_snivelak_path_neighbor_table.row[i][j]) != -1; j++) {
                    acc |= 1 << neighbor;
                    if (neighbor == vars[0x88]) {
                        vars[0x8A] = neighbor;
                        vars[0x8B] = i;
                        return;
                    }
                    if (neighbor == vars[0x89]) {
                        vars[0x8A] = neighbor;
                        vars[0x8B] = i;
                        return;
                    }
                }
            }
        }
        mask |= acc;
    }
}
