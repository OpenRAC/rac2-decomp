#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(int);
extern void module_l00_call_handler_12_us2(void);
extern char *GetLocalizedString(int);
extern void text_draw_right_aligned_small(int, int, unsigned long long, unsigned char *, int);
extern void DoGifPaging(void);
extern int g_right_text_extra_x __attribute__((sda));
extern int g_right_text_extra_y;

/* func_US2_L00_00348244, the USA v2.00 relative of func_002CDA20: the same draw sequence,
   with the text id 0x2BE5, the position read from a level pair (not the boot unit's D_001ABA90 pair) and func_0027F980 drawing it. */
int menu_draw_centered_prompt_l00_us2(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_12_us2();
    text_draw_right_aligned_small(g_right_text_extra_x, g_right_text_extra_y, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0x2BE5), -1);
    DoGifPaging();
    return 0;
}
