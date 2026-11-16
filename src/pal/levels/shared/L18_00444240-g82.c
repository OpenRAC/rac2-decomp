#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef signed int s32;
typedef int TI128 __attribute__((mode(TI)));
extern s32 g_frame_l18_counter;
extern u8 g_emitter_offset_vectors[];
extern s32 math_random_int_below(s32);
extern void matrix_mul_vec3(void *, const void *, const void *);
extern void FastVecAdd(void *, void *, void *);
extern void spinning_part_update_angles(u8 *);

/* Every 50 frames picks two new table vectors for the banner, then places both ends relative to the object (PAL: 50 frame period). */
void banner_pick_table_vectors_pal(u8 *moby) {
    u8 *vars;
    u8 *dst;
    u8 *src;
    TI128 scratch;
    s32 i;
    s32 frame = g_frame_l18_counter;
    s32 frame_mod = frame % 50;

    vars = *(u8 **)(moby + 0x68);
    if (frame_mod) {
        /* the level's frame counter has not reached its turn yet */
    } else {
        *(s32 *)(vars + 0x160) = math_random_int_below(6);
        *(s32 *)(vars + 0x164) = math_random_int_below(6);
    }
    dst = moby + 0x10;
    src = moby + 0xC0;
    i = *(s32 *)(vars + 0x160);
    matrix_mul_vec3(&scratch, g_emitter_offset_vectors + i * 16, src);
    FastVecAdd(&scratch, dst, &scratch);
    *(TI128 *)(vars + 0x10) = *(TI128 *)&scratch;
    i = *(s32 *)(vars + 0x164);
    matrix_mul_vec3(&scratch, g_emitter_offset_vectors + i * 16, src);
    FastVecAdd(&scratch, dst, &scratch);
    *(TI128 *)(vars + 0xB0) = *(TI128 *)&scratch;
    spinning_part_update_angles(moby);
}
