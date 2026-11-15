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
extern int D_001B2248 __attribute__((sda));
extern int D_001B223C __attribute__((sda));
extern int D_001B2240 __attribute__((sda));
extern int D_001B2244 __attribute__((sda));
typedef struct { char pad[0x1C4]; int buttons; } PurchaseInput;
extern volatile PurchaseInput g_pad_state;
extern int GetSelectedShopItemPrice(void);
extern void shop_build_vendor_weapon_list(int);
extern int PlayMobySound(int, int, void *);
extern int stub_empty_7(int, int);
extern int GetLocalizedString(int);
extern void shop_set_message_text(int);
extern void help_unlock_entry(int);
extern int help_copy_record_at_depth(void *, int, int);
extern void moby_handle_request_slot_state(int);
extern void help_start_entry(int);
extern void script_queue_hint_for_event(int);
extern void set_animation_parameter(int, int);
extern void level_forward_pair(int, int);
extern void PrepareVendorSelectionPreview(void);
#define ITEM (D_00239BA0[D_00139568[D_0021F240.rows[D_0021F240.index].item]])
#define ROW (D_0021F240.rows[D_0021F240.index])
#define BUTTONS (D_00138180.buttons)
/* Runs the buy dialog in the vendor screen: works out how many the player can afford, reads the buttons, and completes or cancels the purchase. */
void VendorPurchaseDialogUpdate(int *cancel, int *confirm)
{
    PurchaseItem upgradeInfo;
    int item, special, boughtCount;
    if (g_vendor_menu_state.state == 1) {
        {
            PurchaseItem *record = &ITEM;
            if (record->price) D_001B2248 = g_player_bolts / record->price;
            else D_001B2248 = 0;
        }
        {
            int *ammo = &g_item_ammo_counts[ROW.item];
            PurchaseItem *record = &ITEM;
            int room = record->capacity - *ammo;
            if (D_001B2248 > room) D_001B2248 = room;
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
            if ((BUTTONS & 0x8000) || (D_001B223C >= 16 && !(D_001B223C & 7)) || D_001B223C >= 48) {
                if (D_001B2248 >= 2) {
                    --D_001B2248;
                    if (!(D_001B223C & 3) || D_001B223C < 16)
                        PlayMobySound(1, 17, g_vendor_menu_state.moby);
                }
            }
            if ((BUTTONS & 0x2000) || (D_001B2240 >= 16 && !(D_001B2240 & 7)) || D_001B2240 >= 48) {
                PurchaseItem *record = &ITEM;
                if (record->price) {
                    int max = g_player_bolts / record->price;
                    int left = record->capacity - g_item_ammo_counts[ROW.item];
                    if (left < max) max = left;
                    if (D_001B2248 < max) {
                        ++D_001B2248;
                        if (!(D_001B2240 & 3) || D_001B2240 < 16)
                            PlayMobySound(1, 17, g_vendor_menu_state.moby);
                    }
                }
            }
        }
        if ((BUTTONS & 16) && !(D_001B2244 & 16)) {
            *cancel = 0;
            g_vendor_menu_state.state = 4;
        } else if ((BUTTONS & 64) && !(D_001B2244 & 64)) {
            *cancel = 1;
            g_vendor_menu_state.state = 4;
        }
    } else if (g_vendor_menu_state.state == 4) {
        if (*cancel == 1) {
            int cost;
            PurchaseItem *gate;
            if (ROW.kind == 1) {
                PurchaseItem *record = &ITEM;
                cost = record->price * D_001B2248;
            } else cost = GetSelectedShopItemPrice();
            if (g_player_bolts < cost && g_item_ammo_counts[ROW.item] >= (gate = &ITEM)->capacity) {
                PlayMobySound(0, 17, g_vendor_menu_state.moby);
            } else if (ROW.kind == 1) {
                int *ammo = &g_item_ammo_counts[ROW.item];
                PurchaseItem *record = &ITEM;
                int total;
                if (*ammo < record->capacity) {
                    total = record->price * D_001B2248;
                    if (g_player_bolts >= total) {
                        if (*ammo > record->capacity) *ammo = record->capacity;
                        boughtCount = D_001B2248;
                        boughtCount -= stub_empty_7(ROW.item, boughtCount);
                        {
                            PurchaseItem *record = &ITEM;
                            total = record->price * boughtCount;
                            g_player_bolts -= total;
                        }
                        shop_build_vendor_weapon_list(0);
                        shop_set_message_text(GetLocalizedString(0x2DCB));
                        PlayMobySound(7, 17, g_vendor_menu_state.moby);
                    } else {
                        shop_set_message_text(GetLocalizedString(0x2DCC));
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
                            if (help_copy_record_at_depth(&upgradeInfo, rows[shop->index].item, 1) && upgradeInfo.price)
                                g_item_ammo_counts[rows[shop->index].item] = upgradeInfo.capacity;
                        } else {
                            PurchaseState *shop = &g_vendor_menu_state;
                            PurchaseRow *rows = shop->rows;
                            if (help_copy_record_at_depth(&upgradeInfo, rows[shop->index].item, 2) && upgradeInfo.price)
                                g_item_ammo_counts[rows[shop->index].item] = upgradeInfo.capacity;
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
                    shop_set_message_text(GetLocalizedString(0x2DCB));
                    PlayMobySound(7, 17, g_vendor_menu_state.moby);
                } else {
                    shop_set_message_text(GetLocalizedString(0x2DCC));
                    PlayMobySound(0, 17, g_vendor_menu_state.moby);
                }
            }
        } else PlayMobySound(0, 17, g_vendor_menu_state.moby);
        g_vendor_menu_state.state = 0;
        PrepareVendorSelectionPreview();
    }
}
