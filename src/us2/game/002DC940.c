#include "include_asm.h"

#include "common.h"
typedef struct { short s[12]; } PromptTextBox;
typedef struct { int words[4]; } PromptCornerColors;
typedef struct { int left, top, right, bottom; } PromptBounds;
typedef struct {
    char reserved00[0x18];
    int left, top, width, height;
} PromptMenuPrefix;
extern int g_prompt_box_kind;
extern unsigned char g_prompt_box_text[];
extern int g_prompt_box_initialized SDATA(D_001B1E10) __attribute__((sda));
extern int g_menu_panel_fill_color SDATA(D_001AA43C) __attribute__((sda));
extern PromptCornerColors g_prompt_corner_colors[] SDATA(D_001B1E00) __attribute__((sda));
extern PromptBounds g_prompt_bounds_table[] MACRO_ADDR;
extern PromptBounds D_001ABB80_gp[] SDATA(D_001ABB80) __attribute__((sda));
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void SetupGifPaging(int);
extern char *GetLocalizedString(int);
extern void text_draw_window_medium(unsigned short *, unsigned long, unsigned char *, int);
extern void gfx_draw_screen_rectangle(int, int, int, int, int, void *);
extern void DoGifPaging(void);

/* Draws the prompt box over the menu area: the text with a shadow, a border, and a bright copy on top. */
int menu_prompt_box_draw_us2(PromptMenuPrefix *menu)
{
    unsigned char *text;
    int kind;
    VU1_addGSregister(0x42, 0x44ULL);
    VU1_addGSregister(0x47, 0x2004BULL);
    SetupGifPaging(0);
    text = g_prompt_box_text;
    kind = g_prompt_box_kind;
    switch (kind) {
    case 0:
    case 1:
    case 2:
        text = (unsigned char *)GetLocalizedString(0x2C8F);
        break;
    case 3:
        text = (unsigned char *)GetLocalizedString(0x2C92);
        break;
    }
    {
        PromptTextBox box = {{menu->top, menu->top + menu->height + 1,
                              menu->left, menu->left + menu->width + 1,
                              (menu->left + menu->width) >> 1, menu->top + 5,
                              menu->width - 5, menu->height - 5, 16, 5}};
        if (!g_prompt_box_initialized) {
            g_prompt_box_initialized = 1;
            g_prompt_corner_colors[0] = (PromptCornerColors){{g_menu_panel_fill_color, g_menu_panel_fill_color, g_menu_panel_fill_color, g_menu_panel_fill_color}};
        }
        text_draw_window_medium((unsigned short *)&box, 0x80000000UL, text, -1);
        box.s[5] = (menu->height - box.s[7]) >> 1;
        box.s[9] ^= 4;
        text_draw_window_medium((unsigned short *)&box, 0x80000000UL, text, -1);
        {
            int top = g_prompt_bounds_table[0].top;
            int bottom = g_prompt_bounds_table[0].bottom;
            int right = g_prompt_bounds_table[0].right;
            gfx_draw_screen_rectangle(D_001ABB80_gp[0].left, top, right, bottom, 0, &g_prompt_corner_colors[0]);
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

