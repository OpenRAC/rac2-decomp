#include "include_asm.h"
#include "names.h"



typedef struct { short field[12]; } TextLayout;
typedef struct { int id; int kind; int rest[4]; } ShopEntry;
typedef struct {
    char prefix[0x80];
    int index;
    int active;
    char padding[0xB8];
    ShopEntry entries[0];
} PurchaseModel;
typedef struct { char prefix[0x88]; unsigned short price; char rest[0x56]; } ShopClass;
extern unsigned char g_item_slot_to_record[];
extern char g_weapon_l00_table[];
extern int D_L00_001B25A8 __attribute__((sda));
extern int g_player_bolts __attribute__((sda));
extern char D_L00_001AD798[7];
extern char D_L00_001AD6C8[3];
extern void *memset(void *, int, unsigned int);
extern void text_draw_window_medium(TextLayout *, unsigned long long, unsigned char *, int);
extern int sprintf(char *, char *, ...);
extern int GetSelectedShopItemPrice(void);
typedef struct { int price; int pad[3]; unsigned char *name; int pad2[2]; } ShopItem;
typedef struct { char prefix[0x144]; ShopItem items[0]; } ShopModel;
extern ShopModel g_purchase_menu_model;
extern float D_L00_001B25E0 __attribute__((sda));
extern int GetIconFrame(int, int);
extern int hud_draw_sprite_gradient(int, int, int, int, int, unsigned int *);
extern int GetLocalizedString(int);
extern void text_draw_right_aligned_medium(int, int, unsigned long long, unsigned char *, int);

/* Layouts measured from the selected-item panel. */
typedef struct { unsigned int word[4]; } PanelColors;
extern PanelColors D_L00_001AD768;
extern int D_L00_001B1BB8[] __attribute__((sda));
extern int g_screen_width __attribute__((sda));
extern int D_001A79FC __attribute__((sda));
/* The top counter's mode word and scale: the shared D_L00_001B2700 is another variable in some levels. */
extern int ref_US2_L00_00378C38_00 __attribute__((sda));
extern float ref_US2_L00_00378C38_01 __attribute__((sda));
extern int g_is_pal_video __attribute__((sda));
extern void text_format_number_with_separators(char *, int);
extern void text_draw_medium(int, int, unsigned long long, unsigned char *, int);
extern int text_draw_centered_medium(int, int, unsigned long long, unsigned char *, int);
extern void text_draw_right_aligned_small(int, int, unsigned long long, unsigned char *, int);

/* Measured from func_002FAE68: the state it steps and the status block it tests. */
typedef struct { char pad[0x38]; int st; } CardPrompt;
typedef struct {
    char p0[0x8]; int f8;
    char p1[0x8]; int f14;
    char p2[0x4]; int f1C;
    char p3[0x88]; int fA8;
    char p4[0x8]; int fB4;
    char p5[0x4]; int fBC;
    char p6[0x9C]; int f15C;
    char p7[0x4]; int f164;
    int f168;
} CardStatus;
extern void *D_0026DBE0[];
extern CardPrompt g_vendor_menu_state;
extern CardStatus g_memcard_state;
extern int D_001A7A20 __attribute__((sda));
extern void shop_set_message_text(char *);
extern void shop_mark_bought_special_items_owned(void);

/* func_US2_L00_00378C38, the v2.00 copy of func_L00_003778F0: the same panel, where the top
 * counter's y depends on ref_US2_L00_00378C38_00 and its icon's y and height on D_001A7B90. */
void func_US2_L00_00378C38(void) {
    PanelColors colors;
    char text[256];
    char *model = (char *)&g_purchase_menu_model;
    int index = *(int *)(model + 0x80);
    float y;
    int icon;
    colors = D_L00_001AD768;
    D_L00_001B1BB8[1] = 0;
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 16, (int)(D_L00_001B25E0 * 51.0f + 0.5f),
                  192, (int)(D_L00_001B25E0 * 96.0f + 0.5f), colors.word);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 400, (int)(D_L00_001B25E0 * 51.0f + 0.5f),
                  -192, (int)(D_L00_001B25E0 * 96.0f + 0.5f), colors.word);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 16, (int)(D_L00_001B25E0 * 243.0f + 0.5f),
                  192, -(int)(D_L00_001B25E0 * 96.0f + 0.5f), colors.word);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 400, (int)(D_L00_001B25E0 * 243.0f + 0.5f),
                  -192, -(int)(D_L00_001B25E0 * 96.0f + 0.5f), colors.word);
    text_draw_right_aligned_medium(270, (int)(D_L00_001B25E0 * 218.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)GetLocalizedString(0x3022), -1);
    text_format_number_with_separators(text, g_purchase_menu_model.items[index].price);
    text_draw_medium(270, (int)(D_L00_001B25E0 * 218.0f + 0.5f), 0x80F0F0F0ULL, (unsigned char *)text, -1);
    text_draw_centered_medium(g_screen_width >> 1, (int)(D_L00_001B25E0 * 277.0f + 0.5f), 0x80F0F0F0ULL,
                  g_purchase_menu_model.items[index].name, -1);
    colors.word[3] = 0x60F0F0B0;
    colors.word[2] = 0x60F0F0B0;
    colors.word[1] = 0x60F0F0B0;
    colors.word[0] = 0x60F0F0B0;
    text_format_number_with_separators(text, D_001A79FC);
    y = ref_US2_L00_00378C38_01 * 17.0f + 0.5f;
    text_draw_right_aligned_small(444, ref_US2_L00_00378C38_00 == 1 ? (int)(y + -4.0f) : (int)y, 0x80FFFFFFULL,
                  (unsigned char *)text, -1);
    icon = GetIconFrame(0xEAA2, 3);
    hud_draw_sprite_gradient(icon, 458,
                  g_is_pal_video ? (int)(D_L00_001B25E0 * 15.0f + 0.5f) - 3 : (int)(D_L00_001B25E0 * 15.0f + 0.5f),
                  32,
                  g_is_pal_video ? (int)(D_L00_001B25E0 * 32.0f + 0.5f) - 2 : (int)(D_L00_001B25E0 * 32.0f + 0.5f),
                  colors.word);
}




/* Selected-item prompt and panel; the model has 28-byte trailing records. */
typedef struct {
    char pad00[0x80];
    int index;
    int state;
    char pad88[0xBC];
    struct { int price; int rest[6]; } cells[0]; /* Variable-length trailing table. */
} UpgradeModel;
extern int func_US2_00280440(int, int, unsigned long long, unsigned char *, int, int, float);
extern void hud_draw_sprite(int, int, int, int, int, int);

/* func_US2_L00_00379928, the v2.00 copy of func_L00_00378578: the same panel, with its prompts drawn
 * through func_US2_00280440 at scale 0.7 and moved up when D_001A7B90 is set. */
void func_US2_L00_00379928(void) {
    UpgradeModel *model = (UpgradeModel *)&g_purchase_menu_model;
    int index = model->index;
    int mode;
    int y;
    if (model->state != 0) {
        if (model->cells[index].price <= D_001A79FC) {
            func_US2_00280440(444, (int)(D_L00_001B25E0 * 190.0f + 0.5f), 0x80F0F0F0ULL,
                              (unsigned char *)GetLocalizedString(0x31C7), -1, 82, 0.7f);
            func_US2_00280440(444, (int)(D_L00_001B25E0 * 214.0f + 0.5f), 0x80F0F0F0ULL,
                              (unsigned char *)GetLocalizedString(0x31C4), -1, 82, 0.7f);
        } else {
            int top;
            mode = g_is_pal_video;
            y = (int)(D_L00_001B25E0 * 214.0f + 0.5f);
            top = mode ? y - 11 : y;
            func_US2_00280440(444, top, 0x80F0F0F0ULL,
                              (unsigned char *)GetLocalizedString(0x31B0), -1, 82, 0.7f);
        }
    } else {
        func_US2_00280440(444, (int)(D_L00_001B25E0 * 190.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)GetLocalizedString(0x31B1), -1, 82, 0.7f);
        func_US2_00280440(444, (int)(D_L00_001B25E0 * 214.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)GetLocalizedString(0x2BE5), -1, 82, 0.7f);
    }
    {
        int icon = GetIconFrame(0xEAA8, 1);
        mode = g_is_pal_video;
        y = (int)(D_L00_001B25E0 * 64.0f + 0.5f);
        hud_draw_sprite(icon, 402, mode ? y - 3 : y, 89, (int)(D_L00_001B25E0 * 115.0f + 0.5f), 64);
    }
    text_draw_centered_medium(445, (int)(D_L00_001B25E0 * 130.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)GetLocalizedString(0x30A8), -1);
    text_draw_centered_medium(445, (int)(D_L00_001B25E0 * 148.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)GetLocalizedString(0x30A9), -1);
}

/* func_L00_00377C50 is defined in L00_00377C50-g8.c. */

/* func_L00_003781B0 is defined in L00_003781B0.c. */


/* func_L00_00378578 is defined in L00_00378578.c. */

/* Draws the selected purchase prompt, quantity, total price and bolt icon. */
void func_US2_L00_00379C50(void) {
    TextLayout copy;
    /* This 24-byte workspace becomes the four-color array after drawing text. */
    union { TextLayout layout; unsigned int colors[4]; } seed;
    char text[256];
    PurchaseModel *model = (PurchaseModel *)&g_purchase_menu_model;
    int index;
    int message;
    unsigned short unit_price;
    if (model->active == 0) return;
    memset(&seed.layout, 0, 24);
    seed.layout.field[0] = 120;
    seed.layout.field[1] = (short)(D_L00_001B25E0 * 200.0f + 0.5f);
    seed.layout.field[2] = 160;
    seed.layout.field[3] = 352;
    seed.layout.field[4] = 256;
    seed.layout.field[5] = (short)(D_L00_001B25E0 * 160.0f + 0.5f);
    seed.layout.field[6] = 184;
    seed.layout.field[7] = (short)(D_L00_001B25E0 * 72.0f + 0.5f);
    seed.layout.field[8] = 16;
    seed.layout.field[9] = 3;
    copy = seed.layout;
    index = model->index;
    if (model->entries[index].kind == 1) {
        int selected_id = model->entries[index].id;
        unit_price = ((ShopClass *)g_weapon_l00_table)[g_item_slot_to_record[selected_id]].price;
        if ((int)unit_price <= g_player_bolts) {
            copy.field[9] = 1;
            copy.field[5] = (short)((float)(copy.field[0] + 12) * D_L00_001B25E0 + 0.5f);
            text_draw_window_medium(&copy, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0x31B3), -1);
            sprintf(text, D_L00_001AD798, D_L00_001B25A8);
            copy.field[5] = (short)((float)(copy.field[0] + 40) * D_L00_001B25E0 + 0.5f);
            text_draw_window_medium(&copy, 0x80F0F0F0ULL, (unsigned char *)text, -1);
            sprintf(text, D_L00_001AD6C8, (unsigned int)D_L00_001B25A8 *
                ((ShopClass *)g_weapon_l00_table)[g_item_slot_to_record[model->entries[model->index].id]].price);
            text_draw_right_aligned_medium(256, (int)(D_L00_001B25E0 * 180.0f + 0.5f), 0x80F0F0F0ULL, (unsigned char *)text, -1);
            seed.colors[0] = 0x60F0F0B0;
            seed.colors[1] = 0x60F0F0B0;
            seed.colors[2] = 0x60F0F0B0;
            seed.colors[3] = 0x60F0F0B0;
            hud_draw_sprite_gradient(GetIconFrame(0x7567, 0), 260, (int)(D_L00_001B25E0 * 180.0f + 0.5f),
                          16, (int)(D_L00_001B25E0 * 16.0f + 0.5f), seed.colors);
            return;
        }
        message = 0x31B4;
    } else {
        if (g_player_bolts >= GetSelectedShopItemPrice()) {
            copy.field[9] = 1;
            copy.field[5] = (short)((float)(copy.field[0] + 6) * D_L00_001B25E0 + 0.5f);
            message = 0x31B5;
        } else goto no_money;
    }
    text_draw_window_medium(&copy, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(message), -1);
    return;
no_money:
    text_draw_window_medium(&copy, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0x31B4), -1);
}


typedef struct { int price; int rest[2]; } ConfirmRow;
typedef struct {
    char prefix[0x80];
    int index;
    int active;
    char padding[0xBC];
    ConfirmRow rows[0];
} ConfirmModel;
extern void *memset(void *, int, unsigned int);

/* Draws the confirmation prompt, with another message and layout when the price is affordable. */
void func_US2_L00_0037A050(void) {
    TextLayout copy;
    TextLayout layout;
    ConfirmModel *model = (ConfirmModel *)&g_purchase_menu_model;
    int top;
    float scale;
    if (model->active == 0) return;
    memset(&layout, 0, sizeof(layout));
    top = 314;
    scale = D_L00_001B25E0;
    layout.field[0] = (short)(scale * 120.0f + 0.5f);
    layout.field[1] = (short)(scale * top + 0.5f);
    layout.field[2] = top;
    layout.field[3] = 486;
    layout.field[4] = 400;
    layout.field[5] = (short)(scale * 217.0f + 0.5f);
    layout.field[6] = 164;
    layout.field[7] = (short)(scale * 186.0f + 0.5f);
    layout.field[8] = 16;
    layout.field[9] = 3;
    copy = layout;
    if (g_player_bolts >= model->rows[model->index].price) {
        copy.field[9] = 1;
        copy.field[5] = (short)((float)(copy.field[0] + 40) * scale + 0.5f);
        text_draw_window_medium(&copy, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0x31B5), -1);
    } else {
        text_draw_window_medium(&copy, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0x31B4), -1);
    }
}




/* func_US2_L00_0037A5D0, the v2.00 copy of func_002FAE68: the same state machine, where the
 * prompts are looked up in the text table. */
void func_US2_L00_0037A5D0(void) {
    {
    static void *rc2_labels[] = {&&rc2_case_0, &&rc2_case_1, &&rc2_case_2, &&rc2_case_3, &&rc2_case_4, &&rc2_case_5, &&rc2_case_6};
    unsigned int rc2_selector = (unsigned int)(g_vendor_menu_state.st);
    if (rc2_selector > 6U) goto rc2_default;
goto *D_0026DBE0[rc2_selector];

    rc2_case_0:
    rc2_case_2:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0 && g_memcard_state.f8 == 2) {
            if (g_memcard_state.f14 != 0) {
                g_memcard_state.f164 = 0x18;
                g_vendor_menu_state.st = 3;
                g_memcard_state.f168 = 0;
                goto rc2_switch_end;
            }
        }
        if (g_vendor_menu_state.st != 0) {
            g_vendor_menu_state.st = 4;
        } else {
            g_vendor_menu_state.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_1:
    rc2_case_3:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0) {
            if (D_001A7A20 & 0x80) {
                if (g_memcard_state.f1C == 1) {
                    shop_set_message_text((char *)GetLocalizedString(0x313A));
                } else if (g_memcard_state.f1C >= 3) {
                    shop_set_message_text((char *)GetLocalizedString(0x3138));
                } else {
                    shop_set_message_text((char *)GetLocalizedString(0x3139));
                }
            } else {
                shop_set_message_text((char *)GetLocalizedString(0x3137));
            }
            shop_mark_bought_special_items_owned();
            if (g_vendor_menu_state.st != 0) {
                g_vendor_menu_state.st = 4;
            } else {
                g_vendor_menu_state.st = 6;
            }
        }
        goto rc2_switch_end;
    rc2_case_4:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0 && g_memcard_state.fA8 == 2 && g_memcard_state.fB4 != 0) {
            g_memcard_state.f164 = 0x18;
            g_memcard_state.f168 = 1;
            g_vendor_menu_state.st = 5;
            goto rc2_switch_end;
        }
        g_vendor_menu_state.st = 6;
        goto rc2_switch_end;
    rc2_case_5:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0) {
            if (D_001A7A20 & 0x80) {
                if (g_memcard_state.fBC == 1) {
                    shop_set_message_text((char *)GetLocalizedString(0x313A));
                } else if (g_memcard_state.fBC >= 3) {
                    shop_set_message_text((char *)GetLocalizedString(0x3138));
                } else {
                    shop_set_message_text((char *)GetLocalizedString(0x3139));
                }
            } else {
                shop_set_message_text((char *)GetLocalizedString(0x3137));
            }
            shop_mark_bought_special_items_owned();
            g_vendor_menu_state.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_6:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0) {
            if (g_memcard_state.f1C == 0) {
                int a = g_memcard_state.f8;
                if (a == 2 && g_memcard_state.f14 != 0) {
                    g_vendor_menu_state.st = a;
                    goto rc2_switch_end;
                }
            }
            if (g_memcard_state.fBC == 0 && g_memcard_state.fA8 == 2 && g_memcard_state.fB4 != 0) {
                g_vendor_menu_state.st = 4;
            }
        }
        goto rc2_switch_end;
    rc2_default:
        goto rc2_switch_end;

rc2_switch_end: ;
}
}
