#include "common.h"

extern void SetupGifPaging(int);
extern void func_0029C4C0(void);
extern float g_hud_scale[] __attribute__((sda));
extern char *GetLocalizedString(s32);
extern int text_draw_centered_small(int, int, u64, u8 *, int);
extern void DoGifPaging(void);

/* Draw the centered panel text in scaled screen coordinates. */
int menu_draw_centered_prompt(void)
{
    float unscaled_y;
    int screen_y;

    SetupGifPaging(0);
    func_0029C4C0();
    unscaled_y = 293.0f;
    screen_y = (int)(g_hud_scale[0] * unscaled_y + 0.5f);
    /* One-pass text draw group after coordinate conversion. */
    do {
        text_draw_centered_small(0x1A5, screen_y, 0x80F0F0F0ULL, (u8 *)GetLocalizedString(0x2D4F), -1);
    } while (0);
    DoGifPaging();
    return 0;
}
