#include "common.h"

extern float g_hud_scale[] __attribute__((sda));
extern void SetupGifPaging(int);
extern void func_0029C530(void);
extern char *GetLocalizedString(s32);
extern int text_draw_centered_small(int, int, u64, u8 *, int);
extern void DoGifPaging(void);

/* Draw centered text in scaled screen coordinates. */
int menu_draw_centered_text(void)
{
    float position;
    int y;

    SetupGifPaging(0);
    func_0029C530();
    position = 329.0f;
    y = (int)(g_hud_scale[0] * position + 0.5f);
    /* One-pass text draw group after coordinate conversion. */
    do {
        text_draw_centered_small(0x1A6, y, 0x80F0F0F0ULL, (u8 *)GetLocalizedString(0x2D4F), -1);
    } while (0);
    DoGifPaging();
    return 0;
}
