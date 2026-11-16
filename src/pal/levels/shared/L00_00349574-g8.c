#include "common.h"

extern void SetupGifPaging(int);
extern void DoGifPaging(void);
extern char *GetLocalizedString(s32);
extern void module_l00_call_handler_12_pal(void);
extern int g_text_right_x_e __attribute__((sda));
extern int g_text_right_y_e[] __attribute__((sda));

extern void text_draw_right_aligned_small(int, int, u64, char *, int);

/* func_PAL_L00_00349574, the PAL copy of func_002CDA20: the same shape, where the
 * text position comes from two PAL words in place of 0x1A5 and the scaled 293,
 * the string id becomes 0xB60, the second call is the PAL level's own
 * func_PAL_L00_0030F3E8 and the draw call is func_0027F980. As in
 * func_PAL_002CE388, retail reads the first word through $gp and the second
 * through lui, hence the two declaration forms and the -G8 unit. */
int func_PAL_L00_00349574(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_12_pal();
    text_draw_right_aligned_small(g_text_right_x_e, g_text_right_y_e[0], 0x80F0F0F0ULL, (char *)GetLocalizedString(0xB60), -1);
    DoGifPaging();
    return 0;
}
