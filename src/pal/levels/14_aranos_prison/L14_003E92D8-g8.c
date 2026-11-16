#include "names.h"
/* func_PAL_L14_003E92D8, the PAL copy of func_L14_003E4EA0: the same C, where both ends of the
   span are key positions scaled to 50 Hz and the current position stays unscaled. A unit of its
   own: it reads four float constants through $gp (hence -g8), and it is built with -g, whose line
   label in front of the `mul.s` before the second division makes the assembler pad that `div.s`
   with retail's `nop` (the division-floor class of docs/build/compiler-notes.md, as in
   func_L23_004160B0). func_00282C48 is `fabs`. The state block is read as a halfword key table at
   +0x00, with the current position at +0x14 and the current key index at +0x16: the span runs
   from the key to the previous one (index != 0), or to one of three words (index == 0). `raw`
   serves two blocks, as the far object's state pointer and as the unscaled key: retail allocates
   it as one multi-block variable. Computing both results before the two stores gives retail's
   store order. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef int s32;

extern float g_keyframe_blend_bias_a __attribute__((sda));
extern float g_keyframe_blend_bias_b __attribute__((sda));
extern float g_keyframe_blend_scale_a __attribute__((sda));
extern float g_keyframe_blend_scale_b __attribute__((sda));
extern float math_fabs(float);

/* Blends the keyframe span of a group moby: works out how far the current position is between two keys and stores two blend values in the linked moby (PAL: keys scaled to 50 Hz). */
void moby_update_keyframe_span_blend_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *linked = *(char **)(vars + 0x30);
    char *linked_vars;
    int span_end;
    int key_word;
    int span_start;
    int raw_key;
    u16 position;
    u16 index;
    float start_f;
    float span_f;
    float dist_a;
    float dist_b;
    float blend_a;
    float result_a;
    float result_b;

    if (linked == 0)
        return;
    linked_vars = *(char **)(linked + 0x68);
    index = *(u16 *)(vars + 0x16);
    if (*(s16 *)(vars + 0x16) == 0) {
        key_word = *(int *)(vars + 0x34);
        if (key_word > 0) {
            span_end = (key_word * 5 + 2) / 6;
            position = *(u16 *)(vars + 0x14);
        } else if (*(int *)(vars + 0x38) >= 0) {
            raw_key = *(int *)(*(char **)(vars + 0x3C) + 0x68);
            position = *(u16 *)(vars + 0x14);
            span_end = (*(int *)(raw_key + 0x34) * 5 + 2) / 6;
        } else {
            span_end = (*(s16 *)(vars + 0x14) * 5 + 2) / 6;
            position = *(u16 *)(vars + 0x14);
        }
    } else {
        span_end = (*(s16 *)(vars + *(s16 *)(vars + 0x16) * 2 - 2) * 5 + 2) / 6;
        position = *(u16 *)(vars + 0x14);
    }
    raw_key = *(s16 *)(vars + (s16)index * 2);
    span_start = (raw_key * 5 + 2) / 6;
    start_f = (float)span_start;
    span_f = (float)(span_end - span_start);
    dist_a = math_fabs((g_keyframe_blend_bias_a - 1.0f) - (g_keyframe_blend_bias_a + g_keyframe_blend_bias_a - 2.0f) * ((float)(s16)position - start_f) / span_f);
    blend_a = g_keyframe_blend_bias_a - dist_a;
    dist_b = math_fabs((g_keyframe_blend_bias_b - 1.0f) - (g_keyframe_blend_bias_b + g_keyframe_blend_bias_b - 2.0f) * ((float)*(s16 *)(vars + 0x14) - start_f) / span_f);
    result_a = blend_a * g_keyframe_blend_scale_a;
    result_b = (g_keyframe_blend_bias_b - dist_b) * g_keyframe_blend_scale_b;
    *(float *)(linked_vars + 0x40) = result_a;
    *(float *)(linked_vars + 0x44) = result_b;
}
