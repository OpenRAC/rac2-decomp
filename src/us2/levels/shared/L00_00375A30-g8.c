#include "include_asm.h"
#include "names.h"
extern int g_purchase_menu_model[];
extern int D_001B2590 __attribute__((sda));
extern int D_001B2594 __attribute__((sda));
extern void VendorPurchaseDialogUpdate(int *a, int *b);
extern void UpdateItemPurchaseConfirmation(int *a, int *b);
extern void UpdatePurchaseConfirmationDialog(int *a, int *b);
extern void UpdateSelectedItemPurchaseDialog(int *a, int *b);

/* Dispatch on a mode word held in the level's own data, once the module's registry word is set. */
void func_US2_L00_00375A30(void)
{
    int *d = g_purchase_menu_model;
    int v;

    if (d[0x84 / 4] == 0)
        return;
    v = d[0x50 / 4];
    if (v == 0)
        VendorPurchaseDialogUpdate(&D_001B2590, &D_001B2594);
    else if (v == 1)
        UpdateItemPurchaseConfirmation(&D_001B2590, &D_001B2594);
    else if (v == 2)
        UpdatePurchaseConfirmationDialog(&D_001B2590, &D_001B2594);
    else if (v == 3)
        UpdateSelectedItemPurchaseDialog(&D_001B2590, &D_001B2594);
}
