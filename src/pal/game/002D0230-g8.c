#include "common.h"

extern void SetupGifPaging(int);
extern void DoGifPaging(void);
extern char *GetLocalizedString(s32);
extern void func_PAL_0029CEC8(void);
extern void text_draw_right_aligned_small(int v, int p7, unsigned long long k, char *r, int m1);
extern int g_text_right_x_d __attribute__((sda));
extern int g_text_right_y_d[] __attribute__((sda));

/* func_PAL_002D022C, the PAL copy of func_002CF2B8: the same C, where the text
 * position comes from two PAL words in place of 0x1A5 and the scaled 256, and
 * the string id becomes 0xB60. */
int func_PAL_002D022C(void)
{
    SetupGifPaging(0);
    func_PAL_0029CEC8();
    text_draw_right_aligned_small(g_text_right_x_d, g_text_right_y_d[0], 0x80F0F0F0ULL, (char *)GetLocalizedString(0xb60), -1);
    DoGifPaging();
    return 0;
}
