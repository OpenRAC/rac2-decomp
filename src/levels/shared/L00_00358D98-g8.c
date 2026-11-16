#include "include_asm.h"
#include "names.h"

/* -G8 unit: the two registry words this body passes by address are small data (the retail reaches
 * them with `addiu $a0,$gp,0x35A0`), so the function lives here; see config/cflags.txt. */

extern int g_purchase_menu_model[];

extern int g_purchase_dialog_selection __attribute__((sda));

extern int g_purchase_dialog_result __attribute__((sda));

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
        VendorPurchaseDialogUpdate(&g_purchase_dialog_selection, &g_purchase_dialog_result);
    else if (mode == 1)
        UpdateItemPurchaseConfirmation(&g_purchase_dialog_selection, &g_purchase_dialog_result);
    else if (mode == 2)
        UpdatePurchaseConfirmationDialog(&g_purchase_dialog_selection, &g_purchase_dialog_result);
    else if (mode == 3)
        UpdateSelectedItemPurchaseDialog(&g_purchase_dialog_selection, &g_purchase_dialog_result);
}

extern int g_table_entries_base __attribute__((sda));
extern void ref_L00_0036ADB0_00(void *, float);
/* Resets all 64 entries of a table to the same starting value. */
void table_reset_entries(void)
{
    int i = 0;
    do {
        ref_L00_0036ADB0_00((void *)(g_table_entries_base + i * 64), 1.0f);
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

extern ResetState g_menu_reset_state;
extern ResetRow g_menu_reset_rows[15];
extern ResetBlock g_menu_reset_blocks[128];
extern int g_menu_state_word_a __attribute__((sda));
extern int g_menu_state_word_b __attribute__((sda));

/* Sets the saved menu state back to its start values and clears the 128 menu slots. */
void menu_reset_state(void) {
    int i;

    g_menu_reset_state.words[7] = 2;
    g_menu_reset_state.words[6] = 3;
    g_menu_reset_state.words[8] = 4;
    g_menu_reset_state.words[0] = -1;
    g_menu_reset_state.words[10] = 100;
    g_menu_reset_state.words[14] = -1;
    g_menu_reset_state.words[31] = 7;
    g_menu_reset_state.words[1] = 0;
    g_menu_reset_state.words[4] = 0;
    g_menu_reset_state.words[2] = 0;
    g_menu_reset_state.words[5] = 0;
    g_menu_reset_state.words[3] = 0;
    g_menu_reset_state.words[30] = 0;
    g_menu_reset_state.words[9] = 0;
    g_menu_reset_state.words[11] = 0;
    g_menu_reset_state.words[13] = 0;
    g_menu_reset_state.words[15] = 0;
    g_menu_reset_state.words[18] = 0;
    g_menu_reset_state.words[19] = 0;
    g_menu_reset_state.words[20] = 0;
    g_menu_reset_state.words[21] = 0;
    g_menu_reset_state.words[28] = 0;
    g_menu_reset_state.words[23] = 0;
    g_menu_reset_state.words[25] = 0;
    g_menu_reset_state.words[24] = 0;
    g_menu_reset_state.words[26] = 0;
    g_menu_reset_state.words[22] = 0;
    g_menu_reset_state.words[27] = 0;
    g_menu_reset_state.words[32] = 0;
    g_menu_reset_state.words[33] = 0;
    g_menu_state_word_a = 0;
    g_menu_state_word_b = 0;
    for (i = 0; i < 15; i++)
        g_menu_reset_rows[i].words[5] = g_menu_reset_rows[i].words[3];
    g_menu_reset_rows[7].words[5] = g_menu_reset_rows[7].words[3];
    g_menu_reset_rows[13].words[5] = g_menu_reset_rows[13].words[3];
    for (i = 127; i >= 0; i--)
        g_menu_reset_blocks[i].active = 0;
}
