#include "include_asm.h"
#include "names.h"

/* Layouts measured from the selected-item panel. */
typedef struct { unsigned int word[4]; } PanelColors;
typedef struct { int price; int pad[3]; unsigned char *name; int pad2[2]; } ShopItem;
typedef struct { char prefix[0x144]; ShopItem items[0]; } ShopModel;
extern PanelColors g_menu_panel_colors;
extern int g_menu_call_state_words[] __attribute__((sda));
extern int g_screen_width __attribute__((sda));
extern int g_bolt_count __attribute__((sda));
/* PAL-only mode word and scale of the top counter, 0x120 and 0x124 past D_L00_001B25E0; the shared
   D_L00_001B2700 is another variable in levels 5, 10, 15 and 25. */
extern int ref_PAL_L00_0037A4B0_00 __attribute__((sda));
extern float ref_PAL_L00_0037A4B0_01 __attribute__((sda));
extern void text_draw_right_aligned_small(int, int, unsigned long long, unsigned char *, int);

/* Selected-item prompt and panel; the model has 28-byte trailing records. */
typedef struct {
    char pad00[0x80];
    int index;
    int state;
    char pad88[0xBC];
    struct { int price; int rest[6]; } cells[0]; /* Variable-length trailing table. */
} UpgradeModel;
extern void func_PAL_002802D8(int, int, unsigned long long, unsigned char *, int, int, float);
extern unsigned char g_language __attribute__((sda));
extern void hud_draw_sprite(int, int, int, int, int, int);

extern char g_purchase_menu_model[];
extern float g_menu_slide_scale __attribute__((sda));
extern int g_player_bolts __attribute__((sda));
extern int g_is_pal_video __attribute__((sda));
extern char *GetLocalizedString(int);
extern void text_draw_right_aligned_medium(int, int, unsigned long long, unsigned char *, int);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite_gradient(int, int, int, int, int, unsigned int *);
extern void func_PAL_002FAB40(char *, int);
extern void text_draw_medium(int, int, unsigned long long, unsigned char *, int);
extern unsigned int level_get_native_table_entry(int);
extern int text_draw_centered_medium(int, int, unsigned long long, unsigned char *, int);

void func_PAL_L00_00379EF0(void) {
    unsigned int colors[4];
    char text[256];
    char *model = g_purchase_menu_model;
    int price = *(int *)(model + 0x144 + *(int *)(model + 0x80) * 12);
    int y;
    unsigned long long color;
    if (price > 0) {
        text_draw_right_aligned_medium(140, (int)(g_menu_slide_scale * 290.0f + 0.5f), 0x80F0F0F0ULL,
                      (unsigned char *)GetLocalizedString(0x114E), -1);
        colors[0] = 0x60F0F0B0;
        colors[1] = 0x60F0F0B0;
        colors[2] = 0x60F0F0B0;
        colors[3] = 0x60F0F0B0;
        hud_draw_sprite_gradient(GetIconFrame(0x7567, 0), 156,
                      (int)(g_menu_slide_scale * 290.0f + 0.5f), 16,
                      (int)(g_menu_slide_scale * 16.0f + 0.5f), colors);
        func_PAL_002FAB40(text, price);
        color = 0x80F0F0F0ULL;
        if (price > g_player_bolts) color = 0x802020F0ULL;
        text_draw_medium(176, (int)(g_menu_slide_scale * 290.0f + 0.5f), color, (unsigned char *)text, -1);
        y = (int)(g_menu_slide_scale * 363.0f + 0.5f) + 7;
        if (!g_is_pal_video) y -= 7;
        text_draw_centered_medium(256, y, 0x80F0F0F0ULL,
            (unsigned char *)GetLocalizedString(level_get_native_table_entry(*(int *)(model + 0x148 + *(int *)(model + 0x80) * 12))), -1);
    } else {
        y = (int)(g_menu_slide_scale * 363.0f + 0.5f) + 7;
        if (!g_is_pal_video) y -= 7;
        text_draw_centered_medium(256, y, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0x109C), -1);
    }
}



/* func_PAL_L00_0037A4B0, the PAL copy of func_L00_003778F0: the same C, where the top counter and
   its icon take PAL's vertical adjustments and the label text id becomes 0x10A0. */
void func_PAL_L00_0037A4B0(void) {
    PanelColors colors;
    char text[256];
    char *model = g_purchase_menu_model;
    int index = *(int *)(model + 0x80);
    float v;
    int y;
    int h;
    int icon;
    int mode;
    colors = g_menu_panel_colors;
    g_menu_call_state_words[1] = 0;
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 16, (int)(g_menu_slide_scale * 51.0f + 0.5f),
                  192, (int)(g_menu_slide_scale * 96.0f + 0.5f), colors.word);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 400, (int)(g_menu_slide_scale * 51.0f + 0.5f),
                  -192, (int)(g_menu_slide_scale * 96.0f + 0.5f), colors.word);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 16, (int)(g_menu_slide_scale * 243.0f + 0.5f),
                  192, -(int)(g_menu_slide_scale * 96.0f + 0.5f), colors.word);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 400, (int)(g_menu_slide_scale * 243.0f + 0.5f),
                  -192, -(int)(g_menu_slide_scale * 96.0f + 0.5f), colors.word);
    text_draw_right_aligned_medium(270, (int)(g_menu_slide_scale * 218.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)GetLocalizedString(0x10a0), -1);
    func_PAL_002FAB40(text, ((ShopModel *)model)->items[index].price);
    text_draw_medium(270, (int)(g_menu_slide_scale * 218.0f + 0.5f), 0x80F0F0F0ULL, (unsigned char *)text, -1);
    text_draw_centered_medium(g_screen_width >> 1, (int)(g_menu_slide_scale * 277.0f + 0.5f), 0x80F0F0F0ULL,
                  ((ShopModel *)model)->items[index].name, -1);
    colors.word[3] = 0x60F0F0B0;
    colors.word[2] = 0x60F0F0B0;
    colors.word[1] = 0x60F0F0B0;
    colors.word[0] = 0x60F0F0B0;
    func_PAL_002FAB40(text, g_bolt_count);
    v = ref_PAL_L00_0037A4B0_01 * 17.0f + 0.5f;
    text_draw_right_aligned_small(444, ref_PAL_L00_0037A4B0_00 == 1 ? (int)(v + -4.0f) : (int)v, 0x80FFFFFFULL, (unsigned char *)text, -1);
    icon = GetIconFrame(0xEAA2, 3);
    mode = g_is_pal_video;
    y = (int)(g_menu_slide_scale * 15.0f + 0.5f);
    h = (int)(g_menu_slide_scale * 32.0f + 0.5f);
    hud_draw_sprite_gradient(icon, 458, mode ? y - 3 : y, 32, mode ? h - 2 : h, colors.word);
}




/* func_PAL_L00_0037B1A0, the PAL copy of func_L00_00378578: the same panel, with its prompts drawn
   through func_PAL_002802D8 at scale 0.7 and moved up when D_001A7B90 is set. Retail really tests
   the language byte and carries both arms in full, although they draw the same two strings. */
void func_PAL_L00_0037B1A0(void) {
    UpgradeModel *model = (UpgradeModel *)g_purchase_menu_model;
    int index = model->index;
    int mode;
    int y;
    if (model->state != 0) {
        if (model->cells[index].price <= g_bolt_count) {
            func_PAL_002802D8(444, (int)(g_menu_slide_scale * 190.0f + 0.5f), 0x80F0F0F0ULL,
                              (unsigned char *)GetLocalizedString(0x113B), -1, 82, 0.7f);
            func_PAL_002802D8(444, (int)(g_menu_slide_scale * 214.0f + 0.5f), 0x80F0F0F0ULL,
                              (unsigned char *)GetLocalizedString(0x1138), -1, 82, 0.7f);
        } else {
            int top;
            mode = g_is_pal_video;
            y = (int)(g_menu_slide_scale * 214.0f + 0.5f);
            top = mode ? y - 11 : y;
            func_PAL_002802D8(444, top, 0x80F0F0F0ULL,
                              (unsigned char *)GetLocalizedString(0x1124), -1, 82, 0.7f);
        }
    } else if (g_language == 2) {
        func_PAL_002802D8(444, (int)(g_menu_slide_scale * 190.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)GetLocalizedString(0x1125), -1, 82, 0.7f);
        func_PAL_002802D8(444, (int)(g_menu_slide_scale * 214.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)GetLocalizedString(0xB60), -1, 82, 0.7f);
    } else {
        func_PAL_002802D8(444, (int)(g_menu_slide_scale * 190.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)GetLocalizedString(0x1125), -1, 82, 0.7f);
        func_PAL_002802D8(444, (int)(g_menu_slide_scale * 214.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)GetLocalizedString(0xB60), -1, 82, 0.7f);
    }
    {
        int icon = GetIconFrame(0xEAA8, 1);
        mode = g_is_pal_video;
        y = (int)(g_menu_slide_scale * 64.0f + 0.5f);
        hud_draw_sprite(icon, 402, mode ? y - 3 : y, 89, (int)(g_menu_slide_scale * 115.0f + 0.5f), 64);
    }
    text_draw_centered_medium(445, (int)(g_menu_slide_scale * 130.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)GetLocalizedString(0x13DB), -1);
    text_draw_centered_medium(445, (int)(g_menu_slide_scale * 148.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)GetLocalizedString(0x13DC), -1);
}
