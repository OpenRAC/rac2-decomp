#include "common.h"

extern void SetupGifPaging(int);
extern void module_l00_call_handler_13_pal(void);
extern char *GetLocalizedString(s32);
extern void text_draw_right_aligned_small(int, int, u64, u8 *, int);
extern void DoGifPaging(void);
extern int ref_PAL_L00_0034ADE4_00 __attribute__((sda));
extern int ref_PAL_L00_0034ADE4_01[] __attribute__((sda));

/* func_PAL_L00_0034ADE4, the PAL copy of func_002CF2B8: the same C, where the
 * text position comes from two PAL words in place of 0x1A5 and the scaled 256,
 * the string id becomes 0xB60, and the draw call is func_0027F980. Retail reads
 * the first word through $gp and the second through lui, hence the two
 * declaration forms, as in func_PAL_002CE388. */
int level_l00_draw_text_right_2_pal(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_13_pal();
    text_draw_right_aligned_small(ref_PAL_L00_0034ADE4_00, ref_PAL_L00_0034ADE4_01[0], 0x80F0F0F0ULL,
                  (u8 *)GetLocalizedString(0xB60), -1);
    DoGifPaging();
    return 0;
}
