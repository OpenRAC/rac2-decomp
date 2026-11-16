#include "include_asm.h"

#include "common.h"
extern s8 g_ring_pieces[];
extern void gfx_draw_lightning_bolt_variant_pal(s32 a, s32 b);
extern void gfx_draw_billboard_quad(void *o, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14);
extern f32 math_random_float_range(f32 a, f32 b);

/* Draws the lightning bolt and three flashes for each ring piece owned by owner (PAL: same as USA v1.01). */
void part_draw_ring_piece_flashes_pal(s32 owner) {
    s32 i;
    s32 piece_start;
    s8 *piece;
    s8 *pieces;

    pieces = g_ring_pieces;
    piece = pieces + 0x30;
    piece_start = (s32) pieces;
    for (i = 0; i < 12; i++) {
        if ((*(s32 *)((s8 *)(piece) + (0x6C))) == owner) {
            gfx_draw_lightning_bolt_variant_pal(owner, piece_start);
            if ((*(s32 *)((s8 *)(piece) + (0x70))) == 0) {
                gfx_draw_billboard_quad(piece, 0x31, 0x3F7F0000, 1, math_random_float_range(0.125f, 0.25f) * 5.0f, 1.25f, 0.0f);
                gfx_draw_billboard_quad(piece, 0x31, 0x5F7F7F7F, 1, math_random_float_range(0.0625f, 0.125f) * 5.0f, 1.24f, 0.0f);
                gfx_draw_billboard_quad(piece, 0xB, 0x103F0000, 1, math_random_float_range(0.15f, 0.35f) * 5.0f, 1.23f, 0.0f);
            }
        }
        piece += 0xB0;
        piece_start += 0xB0;
    }
}
