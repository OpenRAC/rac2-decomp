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
extern unsigned int D_L00_001B25A4 __attribute__((sda));
extern int D_L00_001AD500 __attribute__((sda));
extern int D_L00_001AD4F8 __attribute__((sda));
extern int D_L00_001AD4FC __attribute__((sda));
extern int PlayMobySound(int, int, char *);
extern int GetLocalizedString(int);
extern void shop_set_message_text(void *);
extern void func_PAL_002FA118(void);
extern void func_PAL_002FC1D0(void);

void func_PAL_L00_00376810(int *answer, int *unused) {
    PurchaseModel *model = &g_purchase_menu_model;
    int index = model->index;
    int price = model->cells[index].price;
    int state = g_purchase_menu_model.state;
    if (state == 1) {
        *answer = 0;
        if (g_player_bolts < price) PlayMobySound(2, 17, g_purchase_menu_model.object);
        g_purchase_menu_model.state = 2;
    } else if (state == 2) {
        if ((g_pad_state.pressed & 0x10) && !(D_L00_001B25A4 & 0x10)) {
            *answer = 0;
            g_purchase_menu_model.state = 3;
        } else if ((g_pad_state.pressed & 0x40) && !(D_L00_001B25A4 & 0x40)) {
            *answer = 1;
            g_purchase_menu_model.state = 3;
        }
    } else if (state == 3) {
        if (*answer) {
            if (g_player_bolts >= price && D_L00_001AD500 != 4) {
                D_L00_001AD4F8 = 1;
                D_L00_001AD4FC = model->cells[index].value;
                PlayMobySound(7, 17, g_purchase_menu_model.object);
                g_player_bolts -= price;
                shop_set_message_text((void *)GetLocalizedString(0xBDC));
                PlayMobySound(7, 17, g_purchase_menu_model.object);
                func_PAL_002FA118();
            } else if (D_L00_001AD500 == 4) {
                shop_set_message_text((void *)GetLocalizedString(0xBDD));
                PlayMobySound(0, 17, g_purchase_menu_model.object);
            } else {
                shop_set_message_text((void *)GetLocalizedString(0xBDD));
                PlayMobySound(0, 17, g_purchase_menu_model.object);
            }
        } else PlayMobySound(0, 17, g_purchase_menu_model.object);
        g_purchase_menu_model.state = 0;
        func_PAL_002FC1D0();
    }
}
