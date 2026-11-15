/* Adapted from RAC1 draw_prompt_box, src/game/pause.c at 8bbc6b38
 * (GPL-3.0), retaining its Lombyte-derived menu/font source provenance.
 * RAC2 adds inset bounds, the corner-color cache and the backdrop draw. */
#include "common.h"

typedef struct { short s[12]; } PromptTextBox;
typedef struct { int words[4]; } PromptCornerColors;
typedef struct { int left, top, right, bottom; } PromptBounds;
typedef struct {
    char reserved00[0x18];
    int left, top, width, height;
} PromptMenuPrefix;
extern int D_001F2924;
extern unsigned char D_001ABB78[];
extern int D_001B1E10 SDATA(D_001B1E10) __attribute__((sda));
extern int D_001AA43C SDATA(D_001AA43C) __attribute__((sda));
extern PromptCornerColors D_001B1E00[] SDATA(D_001B1E00) __attribute__((sda));
/* Measured 16-byte record view of externally owned bounds storage. Its
 * complete allocation is unknown, so both views remain incompletely bounded.
 * Retail reads left through GP and the other three fields absolutely. */
extern PromptBounds D_001ABB80[] MACRO_ADDR;
extern PromptBounds D_001ABB80_gp[] SDATA(D_001ABB80) __attribute__((sda));
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void SetupGifPaging(int);
extern char *GetLocalizedString(int);
extern void text_draw_window_medium(unsigned short *, unsigned long, unsigned char *, int);
extern void gfx_draw_screen_rectangle(int, int, int, int, int, void *);
extern void DoGifPaging(void);

/* Draws the prompt box over the menu area: the text with a shadow, a border, and a bright copy on top. */
int menu_prompt_box_draw(PromptMenuPrefix *menu)
{
    unsigned char *text;
    int kind;
    VU1_addGSregister(0x42, 0x44ULL);
    VU1_addGSregister(0x47, 0x2004BULL);
    SetupGifPaging(0);
    text = D_001ABB78;
    kind = D_001F2924;
    switch (kind) {
    case 0:
    case 1:
    case 2:
        text = (unsigned char *)GetLocalizedString(0x2DF9);
        break;
    case 3:
        text = (unsigned char *)GetLocalizedString(0x2DFC);
        break;
    }
    {
        PromptTextBox box = {{menu->top, menu->top + menu->height + 1,
                              menu->left, menu->left + menu->width + 1,
                              (menu->left + menu->width) >> 1, menu->top + 5,
                              menu->width - 5, menu->height - 5, 16, 5}};
        if (!D_001B1E10) {
            D_001B1E10 = 1;
            D_001B1E00[0] = (PromptCornerColors){{D_001AA43C, D_001AA43C, D_001AA43C, D_001AA43C}};
        }
        text_draw_window_medium((unsigned short *)&box, 0x80000000UL, text, -1);
        box.s[5] = (menu->height - box.s[7]) >> 1;
        box.s[9] ^= 4;
        text_draw_window_medium((unsigned short *)&box, 0x80000000UL, text, -1);
        {
            int top = D_001ABB80[0].top;
            int bottom = D_001ABB80[0].bottom;
            int right = D_001ABB80[0].right;
            gfx_draw_screen_rectangle(D_001ABB80_gp[0].left, top, right, bottom, 0, &D_001B1E00[0]);
        }
        box.s[0]--;
        box.s[1]--;
        box.s[2]--;
        box.s[3]--;
        box.s[4]--;
        box.s[5]--;
        text_draw_window_medium((unsigned short *)&box, 0x80F0F0F0UL, text, -1);
    }
    DoGifPaging();
    return 2;
}
