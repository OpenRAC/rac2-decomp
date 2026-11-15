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
extern char D_001AD3D0[];
extern int g_screen_width;
extern int g_player_bolts;
extern float D_001B2280;
extern char *GetLocalizedString(int);
extern char *strcpy(char *, char *);
extern int sprintf(char *, char *, ...);
extern int text_draw_centered_medium(int, int, unsigned long, char *, int);
extern void func_PAL_002803E8(int, int, unsigned long, char *, int, float);
extern void text_draw_right_aligned_medium(int, int, unsigned long, char *, int);
extern void text_draw_medium(int, int, unsigned long, char *, int);
extern void func_PAL_002FAB40(char *, int);
extern int help_copy_record_at_depth(void *, int, int);
extern int GetSelectedShopItemPrice(void);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite_gradient(int, int, int, int, int, void *);

/* Draws the selected vendor item, its price and the purchase/maximum-ammo prompt. */
void func_PAL_L00_00379A38(void)
{
    char text[256];
    char info[224];
    int available = 1;
    VendorState *v;
    int color = 0x80F0F0F0;
    v = &g_vendor_menu_state;
    if (v->slots[v->index].kind == available) {
        int id = v->slots[v->index].id;
        char *copied;
        char *fmt = D_001AD3D0;
        if (g_item_ammo_counts[id] >=
            ((VendorItem *)(g_weapon_table + g_item_slot_to_record[id] * 224))->max)
            available = 0;
        copied = strcpy(text, GetLocalizedString(((VendorItem *)(g_weapon_table + g_item_slot_to_record[id] * 224))->text));
        sprintf(text, fmt, copied, GetLocalizedString(0xbda));
        text_draw_centered_medium(g_screen_width >> 1, (int)(D_001B2280 * 274.0f + 0.5f), 0x80F0F0F0L, text, -1);
        func_PAL_002FAB40(text, ((VendorItem *)(g_weapon_table + g_item_slot_to_record[v->slots[v->index].id] * 224))->price);
        if (g_player_bolts < ((VendorItem *)(g_weapon_table + g_item_slot_to_record[v->slots[v->index].id] * 224))->price)
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
            text_draw_centered_medium(g_screen_width >> 1, (int)(D_001B2280 * 274.0f + 0.5f), 0x80F0F0F0L, GetLocalizedString(*(int *)(info + 8)), -1);
        } else {
            text_draw_centered_medium(g_screen_width >> 1, (int)(D_001B2280 * 274.0f + 0.5f), 0x80F0F0F0L, GetLocalizedString(((VendorItem *)(g_weapon_table + g_item_slot_to_record[g_vendor_menu_state.slots[g_vendor_menu_state.index].id] * 224))->text), -1);
        }
        func_PAL_002FAB40(text, GetSelectedShopItemPrice());
        if (g_player_bolts < GetSelectedShopItemPrice())
            color = (int)0x802020F0;
    }
    if (available) {
        int tex;
        text_draw_right_aligned_medium(220, (int)(D_001B2280 * 210.0f + 0.5f), 0x80F0F0F0L, GetLocalizedString(0x114E), -1);
        ((int *)info)[0] = 0x60F0F0B0;
        ((int *)info)[1] = 0x60F0F0B0;
        ((int *)info)[2] = 0x60F0F0B0;
        ((int *)info)[3] = 0x60F0F0B0;
        tex = GetIconFrame(0x7567, 0);
        hud_draw_sprite_gradient(tex, 236, (int)(D_001B2280 * 210.0f + 0.5f), 16, (int)(D_001B2280 * 16.0f + 0.5f), info);
        text_draw_medium(256, (int)(D_001B2280 * 210.0f + 0.5f), color, text, -1);
    } else {
        func_PAL_002803E8(259, (int)(D_001B2280 * 210.0f + 0.5f), 0x80F0F0F0L, GetLocalizedString(0x1126), -1, 0.9f);
    }
}
