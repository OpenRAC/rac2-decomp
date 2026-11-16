#include "names.h"
/* func_US2_002D023C, the v2.00 relative of func_002CF2B8: the same C, built with -G8, where the
 * x and y become v2.00 data (0x1C7 and 0x100), the callee func_0027F980 and the text id 0x2BE5. */
#include "common.h"

extern void SetupGifPaging(int);
extern void tab_menu_draw_2_call_us2(void);
extern char *GetLocalizedString(s32);
extern void text_draw_right_aligned_small(int, int, u64, u8 *, int);
extern void DoGifPaging(void);
extern int g_right_text_alt_x __attribute__((sda));
extern int g_right_text_alt_y;

int menu_draw_centered_prompt_low_us2(void)
{
    SetupGifPaging(0);
    tab_menu_draw_2_call_us2();
    text_draw_right_aligned_small(g_right_text_alt_x, g_right_text_alt_y, 0x80F0F0F0ULL, (u8 *)GetLocalizedString(0x2BE5), -1);
    DoGifPaging();
    return 0;
}
