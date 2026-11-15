#include "include_asm.h"
#include "names.h"

/* -G8 unit: the two registry words this body passes by address are small data (the retail reaches
 * them with `addiu $a0,$gp,0x35A0`), so the function lives here; see config/cflags.txt. */

extern int g_purchase_menu_model[];

extern int D_001B2590 __attribute__((sda));

extern int D_001B2594 __attribute__((sda));

extern void VendorPurchaseDialogUpdate(int *a, int *b);

extern void UpdateItemPurchaseConfirmation(int *a, int *b);

extern void UpdatePurchaseConfirmationDialog(int *a, int *b);

extern void UpdateSelectedItemPurchaseDialog(int *a, int *b);

/* Dispatch on a mode word held in the level's own data, once the module's registry word is set. */
/* Runs the purchase confirmation step that matches the current menu mode. */
void shop_dispatch_purchase_confirm(void)
{
    int *menu = g_purchase_menu_model;
    int mode;

    if (menu[0x84 / 4] == 0)
        return;
    mode = menu[0x50 / 4];
    if (mode == 0)
        VendorPurchaseDialogUpdate(&D_001B2590, &D_001B2594);
    else if (mode == 1)
        UpdateItemPurchaseConfirmation(&D_001B2590, &D_001B2594);
    else if (mode == 2)
        UpdatePurchaseConfirmationDialog(&D_001B2590, &D_001B2594);
    else if (mode == 3)
        UpdateSelectedItemPurchaseDialog(&D_001B2590, &D_001B2594);
}

extern int D_L00_001AD410 __attribute__((sda));
extern void ref_L00_0036ADB0_00(void *, float);
/* Resets all 64 entries of a table to the same starting value. */
void table_reset_entries(void)
{
    int i = 0;
    do {
        ref_L00_0036ADB0_00((void *)(D_L00_001AD410 + i * 64), 1.0f);
        i++;
    } while (i < 64);
}


typedef struct { int words[34]; } ResetState;
typedef struct { int words[10]; } ResetRow;
typedef struct {
    char reserved00[0x50];
    int active;
    char reserved54[0x2C];
} ResetBlock;

extern ResetState D_L00_00221410;
extern ResetRow D_L00_0028B380[15];
extern ResetBlock D_L00_002214D0[128];
extern int D_L00_001AC598 __attribute__((sda));
extern int D_L00_001AC59C __attribute__((sda));

/* Sets the saved menu state back to its start values and clears the 128 menu slots. */
void menu_reset_state(void) {
    int i;

    D_L00_00221410.words[7] = 2;
    D_L00_00221410.words[6] = 3;
    D_L00_00221410.words[8] = 4;
    D_L00_00221410.words[0] = -1;
    D_L00_00221410.words[10] = 100;
    D_L00_00221410.words[14] = -1;
    D_L00_00221410.words[31] = 7;
    D_L00_00221410.words[1] = 0;
    D_L00_00221410.words[4] = 0;
    D_L00_00221410.words[2] = 0;
    D_L00_00221410.words[5] = 0;
    D_L00_00221410.words[3] = 0;
    D_L00_00221410.words[30] = 0;
    D_L00_00221410.words[9] = 0;
    D_L00_00221410.words[11] = 0;
    D_L00_00221410.words[13] = 0;
    D_L00_00221410.words[15] = 0;
    D_L00_00221410.words[18] = 0;
    D_L00_00221410.words[19] = 0;
    D_L00_00221410.words[20] = 0;
    D_L00_00221410.words[21] = 0;
    D_L00_00221410.words[28] = 0;
    D_L00_00221410.words[23] = 0;
    D_L00_00221410.words[25] = 0;
    D_L00_00221410.words[24] = 0;
    D_L00_00221410.words[26] = 0;
    D_L00_00221410.words[22] = 0;
    D_L00_00221410.words[27] = 0;
    D_L00_00221410.words[32] = 0;
    D_L00_00221410.words[33] = 0;
    D_L00_001AC598 = 0;
    D_L00_001AC59C = 0;
    for (i = 0; i < 15; i++)
        D_L00_0028B380[i].words[5] = D_L00_0028B380[i].words[3];
    D_L00_0028B380[7].words[5] = D_L00_0028B380[7].words[3];
    D_L00_0028B380[13].words[5] = D_L00_0028B380[13].words[3];
    for (i = 127; i >= 0; i--)
        D_L00_002214D0[i].active = 0;
}
