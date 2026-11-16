#include "include_asm.h"

#include "common.h"
typedef struct { int item, kind, c, d, e, special; } PurchaseRow;
typedef struct {
    char pad0[0x28]; void *moby;
    char pad2C[0x3C]; int last;
    char pad6C[0xC]; int handle, unused, index, state;
    char pad88[0xB8]; PurchaseRow rows[64]; int count;
} PurchaseState;
typedef struct { char pad0[0x88]; unsigned short price; char pad8A[4]; unsigned short capacity; char pad90[0x50]; } PurchaseItem;
extern PurchaseState g_vendor_menu_state;
extern PurchaseItem g_weapon_table[];
extern unsigned char g_item_slot_to_record[];
extern int g_item_ammo_counts[];
extern int g_player_bolts __attribute__((sda));
extern int g_shop_max_purchase_count __attribute__((sda));
extern int g_shop_left_hold_timer __attribute__((sda));
extern int g_shop_right_hold_timer __attribute__((sda));
extern int g_shop_prev_buttons __attribute__((sda));
typedef struct { char pad[0x1C4]; int buttons; } PurchaseInput;
extern volatile PurchaseInput g_pad_state;
extern int GetSelectedShopItemPrice(void);
extern void shop_build_vendor_weapon_list(int);
extern int PlayMobySound(int, int, void *);
extern int stub_empty_8(int, int);
extern char *GetLocalizedString(int);
extern void shop_set_message_text(int);
extern void help_unlock_entry(int);
extern int help_copy_record_at_depth(void *, int, int);
extern int moby_handle_request_slot_state(int);
extern int help_start_entry(int);
extern void script_queue_hint_for_event(int);
extern void set_animation_parameter(int, int);
extern void level_forward_pair(int, int);
extern void func_US2_002FC008(void);
#define ITEM (D_00239BA0[D_00139568[D_0021F240.rows[D_0021F240.index].item]])
#define ROW (D_0021F240.rows[D_0021F240.index])
#define BUTTONS (D_00138180.buttons)
extern int ref_US2_002F97A8_00(int, int);

void VendorPurchaseDialogUpdate_us2(int *cancel, int *confirm)
{
    PurchaseItem result;
    int item, special, used;
    if (g_vendor_menu_state.state == 1) {
        {
            PurchaseItem *record = &ITEM;
            if (record->price) g_shop_max_purchase_count = g_player_bolts / record->price;
            else g_shop_max_purchase_count = 0;
        }
        {
            int *ammo = &g_item_ammo_counts[ROW.item];
            PurchaseItem *record = &ITEM;
            int room = record->capacity - *ammo;
            if (g_shop_max_purchase_count > room) g_shop_max_purchase_count = room;
        }
        *cancel = 0;
        *confirm = 0;
        if (ROW.kind == 1 && g_item_ammo_counts[ROW.item] >= ITEM.capacity) {
            PlayMobySound(2, 17, g_vendor_menu_state.moby);
        } else if (ROW.kind == 1) {
            PurchaseItem *record = &ITEM;
            if (g_player_bolts < record->price) PlayMobySound(2, 17, g_vendor_menu_state.moby);
            else *confirm = 1;
        } else if (g_player_bolts < GetSelectedShopItemPrice()) {
            PlayMobySound(2, 0, g_vendor_menu_state.moby);
        }
        g_vendor_menu_state.state = 2;
    } else if (g_vendor_menu_state.state == 2) {
        if (*confirm == 1) {
            if ((BUTTONS & 0x8000) || (g_shop_left_hold_timer >= 16 && !(g_shop_left_hold_timer & 7)) || g_shop_left_hold_timer >= 48) {
                if (g_shop_max_purchase_count >= 2) {
                    --g_shop_max_purchase_count;
                    if (!(g_shop_left_hold_timer & 3) || g_shop_left_hold_timer < 16)
                        PlayMobySound(1, 17, g_vendor_menu_state.moby);
                }
            }
            if ((BUTTONS & 0x2000) || (g_shop_right_hold_timer >= 16 && !(g_shop_right_hold_timer & 7)) || g_shop_right_hold_timer >= 48) {
                PurchaseItem *record = &ITEM;
                if (record->price) {
                    int max = g_player_bolts / record->price;
                    int left = record->capacity - g_item_ammo_counts[ROW.item];
                    if (left < max) max = left;
                    if (g_shop_max_purchase_count < max) {
                        ++g_shop_max_purchase_count;
                        if (!(g_shop_right_hold_timer & 3) || g_shop_right_hold_timer < 16)
                            PlayMobySound(1, 17, g_vendor_menu_state.moby);
                    }
                }
            }
        }
        if ((BUTTONS & 16) && !(g_shop_prev_buttons & 16)) {
            *cancel = 0;
            g_vendor_menu_state.state = 4;
        } else if ((BUTTONS & 64) && !(g_shop_prev_buttons & 64)) {
            *cancel = 1;
            g_vendor_menu_state.state = 4;
        }
    } else if (g_vendor_menu_state.state == 4) {
        if (*cancel == 1) {
            int cost;
            PurchaseItem *gate;
            if (ROW.kind == 1) {
                PurchaseItem *record = &ITEM;
                cost = record->price * g_shop_max_purchase_count;
            } else cost = GetSelectedShopItemPrice();
            if (g_player_bolts < cost && g_item_ammo_counts[ROW.item] >= (gate = &ITEM)->capacity) {
                PlayMobySound(0, 17, g_vendor_menu_state.moby);
            } else if (ROW.kind == 1) {
                int *ammo = &g_item_ammo_counts[ROW.item];
                PurchaseItem *record = &ITEM;
                int total;
                if (*ammo < record->capacity) {
                    total = record->price * g_shop_max_purchase_count;
                    if (g_player_bolts >= total) {
                        if (*ammo > record->capacity) *ammo = record->capacity;
                        used = g_shop_max_purchase_count;
                        used -= ref_US2_002F97A8_00(ROW.item, used);
                        {
                            PurchaseItem *record = &ITEM;
                            total = record->price * used;
                            g_player_bolts -= total;
                        }
                        shop_build_vendor_weapon_list(0);
                        shop_set_message_text(GetLocalizedString(0x2C61));
                        PlayMobySound(7, 17, g_vendor_menu_state.moby);
                    } else {
                        shop_set_message_text(GetLocalizedString(0x2C62));
                        PlayMobySound(0, 17, g_vendor_menu_state.moby);
                    }
                } else PlayMobySound(0, 17, g_vendor_menu_state.moby);
            } else {
                int price = GetSelectedShopItemPrice();
                if (g_player_bolts >= price) {
                    item = ROW.item;
                    help_unlock_entry(item);
                    if (ROW.special) {
                        special = 0;
                        switch (ROW.item) {
                        case 12: case 14: case 17: case 18: case 53: special = 1; break;
                        }
                        if (special) {
                            PurchaseState *shop = &g_vendor_menu_state;
                            PurchaseRow *rows = shop->rows;
                            if (help_copy_record_at_depth(&result, rows[shop->index].item, 1) && result.price)
                                g_item_ammo_counts[rows[shop->index].item] = result.capacity;
                        } else {
                            PurchaseState *shop = &g_vendor_menu_state;
                            PurchaseRow *rows = shop->rows;
                            if (help_copy_record_at_depth(&result, rows[shop->index].item, 2) && result.price)
                                g_item_ammo_counts[rows[shop->index].item] = result.capacity;
                        }
                    }
                    if (item != 31 && item != 61) moby_handle_request_slot_state(item);
                    g_vendor_menu_state.last = item;
                    if (ROW.special) help_start_entry(ROW.item);
                    script_queue_hint_for_event(g_vendor_menu_state.last);
                    g_player_bolts -= price;
                    shop_build_vendor_weapon_list(0);
                    if (g_vendor_menu_state.handle != -1) set_animation_parameter(g_vendor_menu_state.handle, 0);
                    g_vendor_menu_state.handle = -1;
                    if (ROW.kind == 1) level_forward_pair(ROW.item, 0x112A880);
                    else if (g_vendor_menu_state.index > g_vendor_menu_state.count - 1) g_vendor_menu_state.index = g_vendor_menu_state.count - 1;
                    shop_set_message_text(GetLocalizedString(0x2C61));
                    PlayMobySound(7, 17, g_vendor_menu_state.moby);
                } else {
                    shop_set_message_text(GetLocalizedString(0x2C62));
                    PlayMobySound(0, 17, g_vendor_menu_state.moby);
                }
            }
        } else PlayMobySound(0, 17, g_vendor_menu_state.moby);
        g_vendor_menu_state.state = 0;
        func_US2_002FC008();
    }
}
