#include "include_asm.h"
#include "names.h"

/* Purchase confirmation state and input fields measured from retail accesses. */
typedef struct {
    char pad00[0x28];
    char *object;
    char pad2c[0x54];
    int index;
    int state;
    char pad88[0xBC];
    struct { int price; int value; int third; } cells[0]; /* Variable-length trailing table. */
} PurchaseModel;
extern PurchaseModel D_L00_0022F7C0;
typedef struct { char pad[0x1C4]; unsigned int pressed; } PurchaseInput;
extern PurchaseInput D_00138180;
extern int D_001A79F8;
extern unsigned int D_L00_001B25A4 __attribute__((sda));
extern int D_L00_001AD500 __attribute__((sda));
extern int D_L00_001AD4F8 __attribute__((sda));
extern int D_L00_001AD4FC __attribute__((sda));
extern int func_002E5CF8(int, int, char *);
extern int func_00288FB8(int);
extern void func_002F88D8(void *);
extern void func_002F9198(void);
extern void func_002FB1A0(void);

/* Asks the player to confirm buying the selected item, then takes the bolts and gives the item. */
void func_L00_00373D40(int *answer, int *unused) {
    PurchaseModel *model = &gPurchaseMenuModel;
    int index = model->index;
    int price = model->cells[index].price;
    int state = gPurchaseMenuModel.state;
    if (state == 1) {
        *answer = 0;
        if (gPlayerBolts < price) PlayMobySound(2, 17, gPurchaseMenuModel.object);
        gPurchaseMenuModel.state = 2;
    } else if (state == 2) {
        if ((gPadState.pressed & 0x10) && !(D_L00_001B25A4 & 0x10)) {
            *answer = 0;
            gPurchaseMenuModel.state = 3;
        } else if ((gPadState.pressed & 0x40) && !(D_L00_001B25A4 & 0x40)) {
            *answer = 1;
            gPurchaseMenuModel.state = 3;
        }
    } else if (state == 3) {
        if (*answer) {
            if (gPlayerBolts >= price && D_L00_001AD500 != 4) {
                D_L00_001AD4F8 = 1;
                D_L00_001AD4FC = model->cells[index].value;
                PlayMobySound(7, 17, gPurchaseMenuModel.object);
                gPlayerBolts -= price;
                SetShopMessageText((void *)GetLocalizedString(0x2DCB));
                PlayMobySound(7, 17, gPurchaseMenuModel.object);
                CloseShopSubMenu();
            } else if (D_L00_001AD500 == 4) {
                SetShopMessageText((void *)GetLocalizedString(0x2DCC));
                PlayMobySound(0, 17, gPurchaseMenuModel.object);
            } else {
                SetShopMessageText((void *)GetLocalizedString(0x2DCC));
                PlayMobySound(0, 17, gPurchaseMenuModel.object);
            }
        } else PlayMobySound(0, 17, gPurchaseMenuModel.object);
        gPurchaseMenuModel.state = 0;
        PrepareVendorSelectionPreview();
    }
}
