#include "common.h"

extern void SetupGifPaging(int);
extern void func_0029C530(void);
extern float D_001B23A4[] __attribute__((sda));
extern s32 GetLocalizedString(s32);
extern int text_draw_centered_small(int, int, u64, u8 *, int);
extern void DoGifPaging(void);

/* Draw centered text in scaled screen coordinates. */
int menu_draw_centered_prompt_low(void)
{
    float unscaled_y;
    int screen_y;

    SetupGifPaging(0);
    func_0029C530();
    unscaled_y = 256.0f;
    screen_y = (int)(D_001B23A4[0] * unscaled_y + 0.5f);
    do {
        text_draw_centered_small(0x1A5, screen_y, 0x80F0F0F0ULL, (u8 *)GetLocalizedString(0x2D4F), -1);
    } while (0);
    DoGifPaging();
    return 0;
}
