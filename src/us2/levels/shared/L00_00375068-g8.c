#include "include_asm.h"
#include "names.h"

typedef struct {
    char pad00[0x28];
    char *object;
    char pad2c[0x54];
    int index;
    int state;
    char pad88[0xBC];
    struct { int price; int value; int third; } cells[0];  
} PurchaseModel;
extern PurchaseModel g_purchase_menu_model;
typedef struct { char pad[0x1C4]; unsigned int pressed; } PurchaseInput;
extern PurchaseInput g_pad_state;
extern int g_player_bolts;
extern unsigned int g_previous_pad_pressed __attribute__((sda));
extern int g_shop_purchase_state __attribute__((sda));
extern int g_shop_flag __attribute__((sda));
extern int g_shop_selected_value __attribute__((sda));
extern int PlayMobySound(int, int, char *);
extern char *GetLocalizedString(int);
extern void shop_set_message_text(void *);
extern void shop_close_sub_menu_us2(void);
extern void PrepareVendorSelectionPreview_us2(void);

/* Handles the selected-item purchase dialog: waits for the answer, then charges bolts and confirms or plays the refusal sound. */
void UpdateSelectedItemPurchaseDialog_us2(int *answer, int *unused) {
    PurchaseModel *model = &g_purchase_menu_model;
    int index = model->index;
    int price = model->cells[index].price;
    int state = g_purchase_menu_model.state;
    if (state == 1) {
        *answer = 0;
        if (g_player_bolts < price) PlayMobySound(2, 17, g_purchase_menu_model.object);
        g_purchase_menu_model.state = 2;
    } else if (state == 2) {
        if ((g_pad_state.pressed & 0x10) && !(g_previous_pad_pressed & 0x10)) {
            *answer = 0;
            g_purchase_menu_model.state = 3;
        } else if ((g_pad_state.pressed & 0x40) && !(g_previous_pad_pressed & 0x40)) {
            *answer = 1;
            g_purchase_menu_model.state = 3;
        }
    } else if (state == 3) {
        if (*answer) {
            if (g_player_bolts >= price && g_shop_purchase_state != 4) {
                g_shop_flag = 1;
                g_shop_selected_value = model->cells[index].value;
                PlayMobySound(7, 17, g_purchase_menu_model.object);
                g_player_bolts -= price;
                shop_set_message_text((void *)GetLocalizedString(0x2C61));
                PlayMobySound(7, 17, g_purchase_menu_model.object);
                shop_close_sub_menu_us2();
            } else if (g_shop_purchase_state == 4) {
                shop_set_message_text((void *)GetLocalizedString(0x2C62));
                PlayMobySound(0, 17, g_purchase_menu_model.object);
            } else {
                shop_set_message_text((void *)GetLocalizedString(0x2C62));
                PlayMobySound(0, 17, g_purchase_menu_model.object);
            }
        } else PlayMobySound(0, 17, g_purchase_menu_model.object);
        g_purchase_menu_model.state = 0;
        PrepareVendorSelectionPreview_us2();
    }
}
