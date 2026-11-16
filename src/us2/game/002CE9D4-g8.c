#include "common.h"

/* func_US2_002CE9D4, the USA v2.00 copy of func_002CDA20: the same draw sequence, where the text
 * (string 0x2BE5) goes through func_0027F980 at a stored position instead of a computed one. */

extern void SetupGifPaging(int);
extern void func_US2_0029D2F8(void);
extern int g_right_text_x __attribute__((sda));
extern int g_right_text_y;
extern char *GetLocalizedString(s32);
extern void text_draw_right_aligned_small(int, int, u64, u8 *, int);
extern void DoGifPaging(void);

int func_US2_002CE9D4(void)
{
    SetupGifPaging(0);
    func_US2_0029D2F8();
    text_draw_right_aligned_small(g_right_text_x, g_right_text_y, 0x80F0F0F0ULL, (u8 *)GetLocalizedString(0x2BE5), -1);
    DoGifPaging();
    return 0;
}
