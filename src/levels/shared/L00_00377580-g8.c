#include "common.h"

/* Partial model and class layouts measured from the item fields. */
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
extern unsigned char D_001A7A80[] __attribute__((sda));
extern int D_L00_001A8E40[] __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
typedef struct { char prefix[8]; int name; char tail[0xE0-12]; } UpgradeInfo;
extern UpgradeInfo g_weapon_l00_table[];
extern char D_L00_001AD738[10];
extern char D_L00_001AD748[9];
extern char D_L00_001AD758[9];
extern int D_L00_001AD718 __attribute__((sda));
extern int D_L00_001AD71C;
extern int D_L00_001AD724;
extern int D_L00_001AD728 __attribute__((sda));
extern int D_L00_001AD72C;
extern int D_L00_001AD730 __attribute__((sda));
extern int D_L00_001AD734;
extern float D_L00_001B25E0;
extern char *GetLocalizedString(int);
extern int sprintf(char *, char *, ...);
extern int text_draw_centered_medium(int, int, unsigned long long, unsigned char *, int);
extern void text_format_number_with_separators(char *, int);
extern int GetIconFrame(int, int);
extern int text_measure_width_second_set(unsigned char *, int);
extern void hud_draw_sprite_gradient(int, int, int, int, int, unsigned int *);
extern int save_count_items_above_baseline(void);

/* Draws the upgrade name, its price and the player's current amount, each with a bolt icon, unless the upgrade is already owned. */
void shop_draw_upgrade_price_lines(void) {
    char first[256];
    char second[256];
    unsigned int colors[4];
    char *model = (char *)&g_purchase_menu_model;
    int group = g_purchase_menu_model.groups.rows[*(int *)(model + 0x80)].group;
    int slot = g_purchase_menu_model.slots.rows[*(int *)(model + 0x80)].group;
    int handle;
    int width;
    if (((unsigned long)D_001A7A80[group] & ((1U << (slot * 2)) & 255UL)) != 0) return;
    if (group != 0) {
        sprintf(first, D_L00_001AD738,
            (unsigned char *)GetLocalizedString(D_L00_001A8E40[slot]),
            (unsigned char *)GetLocalizedString(((UpgradeInfo *)((char *)g_weapon_l00_table + g_item_slot_to_record[g_purchase_menu_model.groups.rows[*(int *)(model + 0x80)].group] * 224))->name));
        text_draw_centered_medium(D_L00_001AD728, (int)((float)D_L00_001AD72C * D_L00_001B25E0 + 0.5f),
                      0x80F0F0F0ULL, (unsigned char *)first, -1);
    }
    text_format_number_with_separators(first, g_purchase_menu_model.prices.rows[*(int *)(model + 0x80)].group);
    sprintf(second, D_L00_001AD748, (unsigned char *)GetLocalizedString(0x114E), first,
        (unsigned char *)GetLocalizedString(0x3262));
    text_draw_centered_medium(D_L00_001AD718, (int)((float)D_L00_001AD71C * D_L00_001B25E0 + 0.5f),
                  0x80F0F0F0ULL, (unsigned char *)second, -1);
    colors[0] = 0x60F0F0B0;
    colors[1] = 0x60F0F0B0;
    colors[2] = 0x60F0F0B0;
    colors[3] = 0x60F0F0B0;
    handle = GetIconFrame(0xEAA2, 0);
    width = text_measure_width_second_set((unsigned char *)second, -1);
    hud_draw_sprite_gradient(handle, D_L00_001AD718 + (width >> 1) + 4,
                  (int)((float)D_L00_001AD724 * D_L00_001B25E0 + 0.5f), 16,
                  (int)(D_L00_001B25E0 * 16.0f + 0.5f), colors);
    sprintf(first, D_L00_001AD758, (unsigned char *)GetLocalizedString(0x2F2D),
        save_count_items_above_baseline(), (unsigned char *)GetLocalizedString(0x3262));
    text_draw_centered_medium(D_L00_001AD730, (int)((float)D_L00_001AD734 * D_L00_001B25E0 + 0.5f),
                  0x80F0F0F0ULL, (unsigned char *)first, -1);
    handle = GetIconFrame(0xEAA2, 0);
    width = text_measure_width_second_set((unsigned char *)first, -1);
    hud_draw_sprite_gradient(handle, D_L00_001AD730 + (width >> 1) + 4,
                  (int)((float)D_L00_001AD734 * D_L00_001B25E0 + 0.5f), 16,
                  (int)(D_L00_001B25E0 * 16.0f + 0.5f), colors);
}
