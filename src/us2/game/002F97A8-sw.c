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
extern int stub_empty_7(int, int);
extern char *GetLocalizedString(int);
extern void shop_set_message_text(int);
extern void help_unlock_entry(int);
extern int help_copy_record_at_depth(void *, int, int);
extern int moby_handle_request_slot_state(int);
extern int help_start_entry(int);
extern void script_queue_hint_for_event(int);
extern void set_animation_parameter(int, int);
extern void level_forward_pair(int, int);
extern void PrepareVendorSelectionPreview_us2(void);
#define ITEM (D_00239BA0[D_00139568[D_0021F240.rows[D_0021F240.index].item]])
#define ROW (D_0021F240.rows[D_0021F240.index])
#define BUTTONS (D_00138180.buttons)


