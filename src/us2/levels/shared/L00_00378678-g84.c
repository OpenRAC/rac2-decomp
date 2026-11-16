#include "include_asm.h"

#include "common.h"
typedef struct { int group; int pad[3]; } UpgradeGroup;
typedef union {
    struct { char prefix[0x144]; UpgradeGroup rows[0];
} groups;
    struct { char prefix[0x140]; UpgradeGroup rows[0];
} slots;
    struct { char prefix[0x148]; UpgradeGroup rows[0];
} prices;
} UpgradeModel;
extern UpgradeModel g_purchase_menu_model;
extern unsigned char g_movie_seen_flags[] __attribute__((sda));
extern int g_shop_upgrade_string_ids[] __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
typedef struct { char prefix[8]; int name; char tail[0xE0-12]; } UpgradeInfo;
extern UpgradeInfo g_weapon_l00_table[];
extern char g_str_shop_price_format[10];
extern char g_str_shop_price_line_format[9];
extern char g_str_shop_upgrade_format[9];
extern int g_shop_price_line_x __attribute__((sda));
extern int g_shop_price_line_y;
extern int g_shop_price_line_extra_y;
extern int g_shop_price_second_x __attribute__((sda));
extern int g_shop_price_second_y;
extern int g_shop_price_third_x __attribute__((sda));
extern int g_shop_price_third_y;
extern float g_menu_slide_scale;
extern char *GetLocalizedString(int);
extern int sprintf(char *, char *, ...);
extern int text_draw_centered_medium(int, int, unsigned long long, unsigned char *, int);
extern void text_format_number_with_separators(char *, int);
extern int GetIconFrame(int, int);
extern int text_measure_width_second_set(unsigned char *, int);
extern void hud_draw_sprite_gradient(int, int, int, int, int, unsigned int *);
extern int save_count_items_above_baseline(void);

void func_US2_L00_003788C8(void) {
    char first[256];
    char second[256];
    unsigned int colors[4];
    char *model = (char *)&g_purchase_menu_model;
    int group = g_purchase_menu_model.groups.rows[*(int *)(model + 0x80)].group;
    int slot = g_purchase_menu_model.slots.rows[*(int *)(model + 0x80)].group;
    int handle;
    int width;
    if (((unsigned long)g_movie_seen_flags[group] & ((1U << (slot * 2)) & 255UL)) != 0) return;
    if (group != 0) {
        sprintf(first, g_str_shop_price_format,
            (unsigned char *)GetLocalizedString(g_shop_upgrade_string_ids[slot]),
            (unsigned char *)GetLocalizedString(((UpgradeInfo *)((char *)g_weapon_l00_table + g_item_slot_to_record[g_purchase_menu_model.groups.rows[*(int *)(model + 0x80)].group] * 224))->name));
        text_draw_centered_medium(g_shop_price_second_x, (int)((float)g_shop_price_second_y * g_menu_slide_scale + 0.5f),
                      0x80F0F0F0ULL, (unsigned char *)first, -1);
    }
    text_format_number_with_separators(first, g_purchase_menu_model.prices.rows[*(int *)(model + 0x80)].group);
    sprintf(second, g_str_shop_price_line_format, (unsigned char *)GetLocalizedString(0x31DA), first,
        (unsigned char *)GetLocalizedString(0x30F8));
    text_draw_centered_medium(g_shop_price_line_x, (int)((float)g_shop_price_line_y * g_menu_slide_scale + 0.5f),
                  0x80F0F0F0ULL, (unsigned char *)second, -1);
    colors[0] = 0x60F0F0B0;
    colors[1] = 0x60F0F0B0;
    colors[2] = 0x60F0F0B0;
    colors[3] = 0x60F0F0B0;
    handle = GetIconFrame(0xEAA2, 0);
    width = text_measure_width_second_set((unsigned char *)second, -1);
    hud_draw_sprite_gradient(handle, g_shop_price_line_x + (width >> 1) + 4,
                  (int)((float)g_shop_price_line_extra_y * g_menu_slide_scale + 0.5f), 16,
                  (int)(g_menu_slide_scale * 16.0f + 0.5f), colors);
    sprintf(first, g_str_shop_upgrade_format, (unsigned char *)GetLocalizedString(0x2DC3),
        save_count_items_above_baseline(), (unsigned char *)GetLocalizedString(0x30F8));
    text_draw_centered_medium(g_shop_price_third_x, (int)((float)g_shop_price_third_y * g_menu_slide_scale + 0.5f),
                  0x80F0F0F0ULL, (unsigned char *)first, -1);
    handle = GetIconFrame(0xEAA2, 0);
    width = text_measure_width_second_set((unsigned char *)first, -1);
    hud_draw_sprite_gradient(handle, g_shop_price_third_x + (width >> 1) + 4,
                  (int)((float)g_shop_price_third_y * g_menu_slide_scale + 0.5f), 16,
                  (int)(g_menu_slide_scale * 16.0f + 0.5f), colors);
}
