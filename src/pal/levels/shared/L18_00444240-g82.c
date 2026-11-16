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

void banner_pick_table_vectors_pal(u8 *obj) {
    u8 *state;
    u8 *dst;
    u8 *src;
    TI128 scratch;
    s32 i;
    s32 v = g_frame_l18_counter;
    s32 r = v % 50;

    state = *(u8 **)(obj + 0x68);
    if (r) {
        /* the level's frame counter has not reached its turn yet */
    } else {
        *(s32 *)(state + 0x160) = math_random_int_below(6);
        *(s32 *)(state + 0x164) = math_random_int_below(6);
    }
    dst = obj + 0x10;
    src = obj + 0xC0;
    i = *(s32 *)(state + 0x160);
    matrix_mul_vec3(&scratch, g_emitter_offset_vectors + i * 16, src);
    FastVecAdd(&scratch, dst, &scratch);
    *(TI128 *)(state + 0x10) = *(TI128 *)&scratch;
    i = *(s32 *)(state + 0x164);
    matrix_mul_vec3(&scratch, g_emitter_offset_vectors + i * 16, src);
    FastVecAdd(&scratch, dst, &scratch);
    *(TI128 *)(state + 0xB0) = *(TI128 *)&scratch;
    spinning_part_update_angles(obj);
}
