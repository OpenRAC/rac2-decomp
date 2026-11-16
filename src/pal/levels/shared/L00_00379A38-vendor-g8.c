#include "include_asm.h"
#include "names.h"

/* func_PAL_L00_00379A38, the PAL copy of func_002FA880: the same C, where text id 0x2DC9
 * becomes 0xBDA and the "not available" prompt is drawn by func_PAL_002803E8 at scale 0.9. */
typedef struct {
    int id;
    int kind;
    char pad[12];
    int owned;
} VendorSlot;
typedef struct {
    char pad[0x80];
    int index;
    char pad2[0xBC];
    VendorSlot slots[1];
} VendorState;
typedef struct {
    char pad[8];
    int text;
    char pad2[0x7C];
    unsigned short price;
    char pad3[4];
    unsigned short max;
    char pad4[0x50];
} VendorItem;
extern VendorState g_vendor_menu_state;
extern unsigned char g_item_slot_to_record[];
extern int g_item_ammo_counts[];
extern char g_weapon_table[];
extern char g_str_vendor_format[];
extern int g_screen_width;
extern int g_player_bolts;
extern float g_pal_aspect_scale;
extern char *GetLocalizedString(int);
extern char *strcpy(char *, char *);
extern int sprintf(char *, char *, ...);
extern int text_draw_centered_medium(int, int, unsigned long, char *, int);
extern void text_draw_centered_medium_scaled(int, int, unsigned long, char *, int, float);
extern void text_draw_right_aligned_medium(int, int, unsigned long, char *, int);
extern void text_draw_medium(int, int, unsigned long, char *, int);
extern void text_format_number_with_separators_pal(char *, int);
extern int help_copy_record_at_depth(void *, int, int);
extern int GetSelectedShopItemPrice(void);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite_gradient(int, int, int, int, int, void *);

/* Draws the selected vendor item, its price and the purchase/maximum-ammo prompt. */
void draw_vendor_purchase_prompt_pal(void)
{
    char text[256];
    char info[224];
    int available = 1;
    VendorState *vendor;
    int color = 0x80F0F0F0;
    vendor = &g_vendor_menu_state;
    if (vendor->slots[vendor->index].kind == available) {
        int id = vendor->slots[vendor->index].id;
        char *name_text;
        char *format = g_str_vendor_format;
        if (g_item_ammo_counts[id] >=
            ((VendorItem *)(g_weapon_table + g_item_slot_to_record[id] * 224))->max)
            available = 0;
        name_text = strcpy(text, GetLocalizedString(((VendorItem *)(g_weapon_table + g_item_slot_to_record[id] * 224))->text));
        sprintf(text, format, name_text, GetLocalizedString(0xbda));
        text_draw_centered_medium(g_screen_width >> 1, (int)(g_pal_aspect_scale * 274.0f + 0.5f), 0x80F0F0F0L, text, -1);
        text_format_number_with_separators_pal(text, ((VendorItem *)(g_weapon_table + g_item_slot_to_record[vendor->slots[vendor->index].id] * 224))->price);
        if (g_player_bolts < ((VendorItem *)(g_weapon_table + g_item_slot_to_record[vendor->slots[vendor->index].id] * 224))->price)
            color = (int)0x802020F0;
    } else {
        if (g_vendor_menu_state.slots[g_vendor_menu_state.index].owned) {
            int special = 0;
            switch (g_vendor_menu_state.slots[g_vendor_menu_state.index].id) {
            case 12:
            case 14:
            case 17:
            case 18:
            case 53:
                special = 1;
            }
            help_copy_record_at_depth(info, g_vendor_menu_state.slots[g_vendor_menu_state.index].id, special ? 1 : 2);
            text_draw_centered_medium(g_screen_width >> 1, (int)(g_pal_aspect_scale * 274.0f + 0.5f), 0x80F0F0F0L, GetLocalizedString(*(int *)(info + 8)), -1);
        } else {
            text_draw_centered_medium(g_screen_width >> 1, (int)(g_pal_aspect_scale * 274.0f + 0.5f), 0x80F0F0F0L, GetLocalizedString(((VendorItem *)(g_weapon_table + g_item_slot_to_record[g_vendor_menu_state.slots[g_vendor_menu_state.index].id] * 224))->text), -1);
        }
        text_format_number_with_separators_pal(text, GetSelectedShopItemPrice());
        if (g_player_bolts < GetSelectedShopItemPrice())
            color = (int)0x802020F0;
    }
    if (available) {
        int icon;
        text_draw_right_aligned_medium(220, (int)(g_pal_aspect_scale * 210.0f + 0.5f), 0x80F0F0F0L, GetLocalizedString(0x114E), -1);
        ((int *)info)[0] = 0x60F0F0B0;
        ((int *)info)[1] = 0x60F0F0B0;
        ((int *)info)[2] = 0x60F0F0B0;
        ((int *)info)[3] = 0x60F0F0B0;
        icon = GetIconFrame(0x7567, 0);
        hud_draw_sprite_gradient(icon, 236, (int)(g_pal_aspect_scale * 210.0f + 0.5f), 16, (int)(g_pal_aspect_scale * 16.0f + 0.5f), info);
        text_draw_medium(256, (int)(g_pal_aspect_scale * 210.0f + 0.5f), color, text, -1);
    } else {
        text_draw_centered_medium_scaled(259, (int)(g_pal_aspect_scale * 210.0f + 0.5f), 0x80F0F0F0L, GetLocalizedString(0x1126), -1, 0.9f);
    }
}
