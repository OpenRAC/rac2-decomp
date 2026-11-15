#include "common.h"

extern void SetupGifPaging(int);
extern void func_0029C4C0(void);
extern float D_001B23A4[] __attribute__((sda));
extern s32 GetLocalizedString(s32);
extern int text_draw_centered_small(int, int, u64, u8 *, int);
extern void DoGifPaging(void);

/* Draw the centered panel text in scaled screen coordinates. */
int menu_draw_centered_prompt(void)
{
    float unscaledY;
    int screenY;

    SetupGifPaging(0);
    func_0029C4C0();
    unscaledY = 293.0f;
    screenY = (int)(D_001B23A4[0] * unscaledY + 0.5f);
    /* One-pass text draw group after coordinate conversion. */
    do {
        text_draw_centered_small(0x1A5, screenY, 0x80F0F0F0ULL, (u8 *)GetLocalizedString(0x2D4F), -1);
    } while (0);
    DoGifPaging();
    return 0;
}
