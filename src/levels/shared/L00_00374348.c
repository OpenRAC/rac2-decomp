#include "names.h"
/* Measured purchase panel: 28-byte rows up to the selection limit at +0x740. */
typedef struct { int cost, value4, value8, item, remainder[3]; } PurchaseRow;
typedef struct {
    char pad00[0x28];
    int owner;
    char pad2C[0x20];
    int item_id;
    char pad50[0x30];
    int selected;
    int state;
    char pad88[0xBC];
    PurchaseRow rows[54];
    char pad72C[0x14];
    int limit;
} PurchaseState;
extern PurchaseState g_purchase_menu_model;
typedef struct { int words[10]; } ResetRow;
extern ResetRow g_menu_reset_rows[15];

/* The persistent save block. Retail reads the balance as an offset from this base: a load of
 * symbol+offset counts as two words, so it stays out of the delay slot of the branch before it. */
typedef struct {
    int word0;
    int balance;
    char pad08[0xF0];
    int last_item;
} PlayerProgress;
extern PlayerProgress g_player_bolts __attribute__((sda));
extern int g_pad_state[];
extern int g_previous_pad_pressed __attribute__((sda));
extern int PlayMobySound(int, int, int);
extern void shop_build_vendor_list_by_flags(void);
extern void PrepareVendorSelectionPreview(void);

/* The purchase confirmation's state machine: warn about the price, wait for a button, then buy. */
void UpdatePurchaseConfirmationDialog(int *result, int *unused)
{
    PurchaseState *model = &g_purchase_menu_model;
    int index = model->selected;
    int cost = model->rows[index].cost;
    if (model->state == 1) {
        *result = 0;
        if (g_player_bolts.balance < cost) PlayMobySound(2, 17, model->owner);
        model->state = 2;
    } else if (model->state == 2) {
        if ((g_pad_state[0x1C4 / 4] & 16) && !(g_previous_pad_pressed & 16)) {
            *result = 0;
            g_purchase_menu_model.state = 3;
        } else if ((g_pad_state[0x1C4 / 4] & 64) && !(g_previous_pad_pressed & 64)) {
            *result = 1;
            g_purchase_menu_model.state = 3;
        }
    } else if (model->state == 3) {
        if (*result) {
            if (g_player_bolts.balance >= cost) {
                g_player_bolts.balance -= cost;
                g_player_bolts.last_item = model->item_id;
                g_menu_reset_rows[g_purchase_menu_model.rows[index].item].words[6] = 1;
                shop_build_vendor_list_by_flags();
                if (model->limit < model->selected) model->selected = model->limit;
                PlayMobySound(7, 17, model->owner);
            } else PlayMobySound(0, 17, model->owner);
        } else PlayMobySound(0, 17, model->owner);
        g_purchase_menu_model.state = 0;
        PrepareVendorSelectionPreview();
    }
}
