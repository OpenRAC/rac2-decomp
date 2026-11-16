#include "include_asm.h"

#include "common.h"
extern void *ref_L06_00457920_00(void *, s32, s16, s32, void *, void *, void *, s32, f32, f32);
extern void ref_L06_00457920_01(s32, s32, f32);
extern s32 ref_L06_00457920_02;
extern s8 ref_L06_00457920_03[];

/* Breaks the object into fifteen flying pieces, each with its own update callback. */
void part_spawn_debris_pieces_pal(void *moby) {
    void *piece;
    s32 piece_vars;
    s32 i;

    i = 0;
    do {
        piece = ref_L06_00457920_00(moby, 2, (*(s16 *)((s8 *)(moby) + (0xAA))), i, (s8 *)moby + 0x10, (s8 *)moby + 0xF0, &ref_L06_00457920_02, 0xFF, 0.0f, 10.0f);
        i += 1;
        if (piece != 0) {
            piece_vars = (*(s32 *)((s8 *)(piece) + (0x68)));
            ref_L06_00457920_01(piece_vars, piece_vars + 0x20, 0.0024f);
            (*(s32 *)((s8 *)(piece) + (0x64))) = (s32)ref_L06_00457920_03;
        }
    } while (i < 0xF);
}
