#include "common.h"

extern void SetupGifPaging(int);
extern void menu_draw_tab_menu_pal(void);
extern char *GetLocalizedString(s32);
extern void text_draw_right_aligned_small(int, int, u64, u8 *, int);
extern void DoGifPaging(void);
/* PAL's stored panel text position (455, 293). */
extern int g_text_right_x_b __attribute__((sda));
extern int g_text_right_y_b[] __attribute__((sda));

/* func_PAL_002CE9BC, the PAL copy of func_002CDA20: the same centered panel text
   draw, where the fixed x and scaled y become PAL's stored position and text
   0x2D4F becomes 0xB60. */
int menu_draw_centered_prompt_pal(void)
{
    SetupGifPaging(0);
    menu_draw_tab_menu_pal();
    text_draw_right_aligned_small(g_text_right_x_b, g_text_right_y_b[0], 0x80F0F0F0ULL, (u8 *)GetLocalizedString(0xB60), -1);
    DoGifPaging();
    return 0;
}
