#include "names.h"
/* func_US2_L00_00349AAC, the level copy of func_US2_002D023C (the v2.00 relative of
 * func_002CF2B8): the same C, where func_US2_0029D368 becomes the level's func_US2_L00_0030E850. */
#include "common.h"

extern void SetupGifPaging(int);
extern void module_l00_call_handler_13_us2(void);
extern char *GetLocalizedString(s32);
extern void text_draw_right_aligned_small(int, int, u64, u8 *, int);
extern void DoGifPaging(void);
extern int g_right_text_alt_x __attribute__((sda));
extern int g_right_text_alt_y;

int func_US2_L00_00349AAC(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_13_us2();
    text_draw_right_aligned_small(g_right_text_alt_x, g_right_text_alt_y, 0x80F0F0F0ULL, (u8 *)GetLocalizedString(0x2BE5), -1);
    DoGifPaging();
    return 0;
}
