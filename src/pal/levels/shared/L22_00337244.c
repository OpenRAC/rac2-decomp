#include "include_asm.h"

#include "common.h"
extern void part_kill(char *);
extern s32 math_fast_float_d(void *);
extern void vec_transform_or_copy(char *, char *);

/* Frees the particle record when it is finished, otherwise moves it and fades it (PAL: fade over 5 frames). */
void part_update_fade_record_pal(u8 *object)
{
    u8 *rec = object;
    u8 *extra = object + 0x20;

    if (math_fast_float_d((char *)extra) != 0) {
        part_kill((char *)rec);
        return;
    }
    {
        u8 *vec_ptr = rec + 0x10;

        vec_transform_or_copy((char *)vec_ptr, (char *)vec_ptr);
    }
    *(f32 *)(rec + 0xC) = *(f32 *)(rec + 0xC) + *(f32 *)(extra + 4);
    if (*(s32 *)(extra) < 5) {
        *(unsigned int *)(rec + 4) = (*(unsigned int *)(rec + 4) & 0xFFFFFF)
            | ((unsigned int)(*(s32 *)(extra) * 127 / 5) << 24);
    }
}


