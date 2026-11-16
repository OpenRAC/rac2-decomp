#include "include_asm.h"
#include "names.h"

/* Selected-item prompt and panel; the model has 28-byte trailing records. */
typedef struct {
    char pad00[0x80];
    int index;
    int state;
    char pad88[0xBC];
    struct { int price; int rest[6]; } cells[0]; /* Variable-length trailing table. */
} UpgradeModel;
extern UpgradeModel g_purchase_menu_model;
extern float g_menu_slide_scale __attribute__((sda));
extern int g_bolt_count __attribute__((sda));
extern char g_str_menu_text_format[7];
extern char g_str_menu_text_short[5];
extern char *GetLocalizedString(int);
extern int text_draw_centered_medium(int, int, unsigned long long, unsigned char *, int);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite(int, int, int, int, int, int);

/* Draws the buy and back labels and the item picture and two text lines on the right of the panel. */
void DrawSelectedItemPurchasePanel(void) {
    UpgradeModel *model = &g_purchase_menu_model;
    int index = model->index;
    if (model->state != 0) {
        if (model->cells[index].price <= g_bolt_count) {
            text_draw_centered_medium(438, (int)(g_menu_slide_scale * 190.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)GetLocalizedString(0x113B), -1);
            text_draw_centered_medium(438, (int)(g_menu_slide_scale * 214.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)GetLocalizedString(0x1138), -1);
        } else {
            text_draw_centered_medium(438, (int)(g_menu_slide_scale * 214.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)GetLocalizedString(0x1124), -1);
        }
    } else {
        text_draw_centered_medium(438, (int)(g_menu_slide_scale * 190.0f + 0.5f), 0x80F0F0F0ULL,
                      (unsigned char *)GetLocalizedString(0x1125), -1);
        text_draw_centered_medium(438, (int)(g_menu_slide_scale * 214.0f + 0.5f), 0x80F0F0F0ULL,
                      (unsigned char *)GetLocalizedString(0x2D4F), -1);
    }
    hud_draw_sprite(GetIconFrame(0xEAA8, 1), 402, (int)(g_menu_slide_scale * 64.0f + 0.5f), 89,
                  (int)(g_menu_slide_scale * 115.0f + 0.5f), 64);
    text_draw_centered_medium(445, (int)(g_menu_slide_scale * 130.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)g_str_menu_text_format, -1);
    text_draw_centered_medium(445, (int)(g_menu_slide_scale * 148.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)g_str_menu_text_short, -1);
}
