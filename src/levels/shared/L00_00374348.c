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
extern PurchaseState D_L00_0022F7C0;
typedef struct { int words[10]; } ResetRow;
extern ResetRow D_L00_0028B380[15];

/* The persistent save block. Retail reads the balance as an offset from this base: a load of
 * symbol+offset counts as two words, so it stays out of the delay slot of the branch before it. */
typedef struct {
    int word0;
    int balance;
    char pad08[0xF0];
    int last_item;
} PlayerProgress;
extern PlayerProgress D_001A79F8 __attribute__((sda));
extern int D_00138180[];
extern int D_L00_001B25A4 __attribute__((sda));
extern void func_002E5CF8(int, int, int);
extern void func_002F7738(void);
extern void func_002FB1A0(void);

/* The purchase confirmation's state machine: warn about the price, wait for a button, then buy. */
void func_L00_00374348(int *result, int *unused)
{
    PurchaseState *model = &gPurchaseMenuModel;
    int index = model->selected;
    int cost = model->rows[index].cost;
    if (model->state == 1) {
        *result = 0;
        if (gPlayerBolts.balance < cost) PlayMobySound(2, 17, model->owner);
        model->state = 2;
    } else if (model->state == 2) {
        if ((gPadState[0x1C4 / 4] & 16) && !(D_L00_001B25A4 & 16)) {
            *result = 0;
            gPurchaseMenuModel.state = 3;
        } else if ((gPadState[0x1C4 / 4] & 64) && !(D_L00_001B25A4 & 64)) {
            *result = 1;
            gPurchaseMenuModel.state = 3;
        }
    } else if (model->state == 3) {
        if (*result) {
            if (gPlayerBolts.balance >= cost) {
                gPlayerBolts.balance -= cost;
                gPlayerBolts.last_item = model->item_id;
                D_L00_0028B380[gPurchaseMenuModel.rows[index].item].words[6] = 1;
                BuildFlagGatedVendorList();
                if (model->limit < model->selected) model->selected = model->limit;
                PlayMobySound(7, 17, model->owner);
            } else PlayMobySound(0, 17, model->owner);
        } else PlayMobySound(0, 17, model->owner);
        gPurchaseMenuModel.state = 0;
        PrepareVendorSelectionPreview();
    }
}
