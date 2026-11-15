#include "include_asm.h"

#include "common.h"
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern int table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern int text_draw_centered_small(int, int, u64, char *, int);
extern int text_draw_centered_medium(int, int, u64, char *, int);
extern int func_001157AC(char *);
extern char *D_001A8CFC;
extern int g_screen_width;
extern float D_001B23A8;
extern void gfx_disable_screen_flag(void);
extern void gfx_enable_screen_flag(void);
extern int save_count_nonzero_flags(void);
extern int sprintf(char *, char *, ...);
extern void text_draw_medium(int, int, u64, char *, int);
extern int D_001AB9EC __attribute__((sda));
extern int D_001AB9F0 __attribute__((sda));
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern unsigned char D_001A7A40[] MACRO_ADDR;
extern char D_001AB9F8[];
extern char D_001AB9D8[];
typedef struct {
    short text;
    unsigned char index;
    unsigned char limit;
} MenuOption;
extern MenuOption D_001ABCD0[] MACRO_ADDR;

int func_PAL_002D0740(void)
{
    char buf[64];
    int r, i, y, color, limit, available;
    u64 style;
    float z;

    available = save_count_nonzero_flags();
    z = 0.84f;
    SetupGifPaging(0);
    r = table_find_by_id(D_001A8CFC + 0x8710, 0x8B);
    gfx_draw_scaled_object_two_axes((char *)r, 0x60442D00, (float)(g_screen_width / 2), (float)D_001AB9F0, 1.0f, D_001B23A8, z);
    r = table_find_by_id(D_001A8CFC + 0x8710, 0x8C);
    gfx_draw_scaled_object_two_axes((char *)r, 0x55F0C070, (float)(g_screen_width / 2), (float)D_001AB9F0, 1.0f, D_001B23A8, z);
    r = table_find_by_id(D_001A8CFC + 0x8710, 0x8D);
    gfx_draw_scaled_object_two_axes((char *)r, 0x55F0C070, (float)(g_screen_width / 2), (float)D_001AB9F0, 1.0f, D_001B23A8, z);
    text_draw_centered_small(g_screen_width / 2, 0x41, 0x80F0F0F0ULL, GetLocalizedString(0xC22), -1);
    text_draw_centered_small(g_screen_width / 2, 0x141, 0x80F0F0F0ULL, GetLocalizedString(0xB5F), -1);
    text_draw_centered_small(g_screen_width / 2, 0x15A, 0x80F0F0F0ULL, GetLocalizedString(0xB60), -1);
    for (i = 0, y = 0x70; i < 12; i++) {
        limit = D_001ABCD0[i].limit;
        if (limit == 100) continue;
        if (limit != 90) {
            if (available < limit) goto locked;
            goto enabled;
        }
        if (D_001A7A60[0]) goto enabled;
locked:
        {
            color = 0x80808080;
            if (i == D_001AB9EC) color = 0x7029A1FF;
            text_draw_medium(0x2B, y, color, GetLocalizedString(0xBD1), -1);
            if (limit == 90)
                sprintf(buf, D_001AB9F8, GetLocalizedString(0xC38));
            else
                sprintf(buf, D_001AB9D8, limit, GetLocalizedString(0xC20));
            style = color;
            gfx_disable_screen_flag();
            r = func_001157AC(buf);
            text_draw_centered_medium(0x195, y, style, buf, r);
            gfx_enable_screen_flag();
        }
        goto next;
enabled:
        {
            color = 0x80F0F0F0;
            if (i == D_001AB9EC) color = 0x7029A1FF;
            text_draw_medium(0x2B, y, color, GetLocalizedString(D_001ABCD0[i].text), -1);
            text_draw_centered_medium(0x195, y, color, GetLocalizedString(D_001A7A40[D_001ABCD0[i].index] ? 0xBD7 : 0xBD8), -1);
        }
next:
        y += 19;
    }
    DoGifPaging();
    return 0;
}
