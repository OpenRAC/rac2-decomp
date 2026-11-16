#include "include_asm.h"
#include "names.h"
extern int g_purchase_menu_model[];
extern int g_purchase_dialog_selection __attribute__((sda));
extern int g_purchase_dialog_result __attribute__((sda));
extern void VendorPurchaseDialogUpdate(int *a, int *b);
extern void UpdateItemPurchaseConfirmation(int *a, int *b);
extern void UpdatePurchaseConfirmationDialog(int *a, int *b);
extern void UpdateSelectedItemPurchaseDialog(int *a, int *b);

/* Dispatch on a mode word held in the level's own data, once the module's registry word is set. */
void shop_dispatch_purchase_confirm_us2(void)
{
    int *model = g_purchase_menu_model;
    int mode;

    if (model[0x84 / 4] == 0)
        return;
    mode = model[0x50 / 4];
    if (mode == 0)
        VendorPurchaseDialogUpdate(&g_purchase_dialog_selection, &g_purchase_dialog_result);
    else if (mode == 1)
        UpdateItemPurchaseConfirmation(&g_purchase_dialog_selection, &g_purchase_dialog_result);
    else if (mode == 2)
        UpdatePurchaseConfirmationDialog(&g_purchase_dialog_selection, &g_purchase_dialog_result);
    else if (mode == 3)
        UpdateSelectedItemPurchaseDialog(&g_purchase_dialog_selection, &g_purchase_dialog_result);
}
