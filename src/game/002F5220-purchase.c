#include "common.h"

typedef struct { int item, kind, c, d, e, special; } PurchaseRow;
typedef struct {
    char pad0[0x28]; void *moby;
    char pad2C[0x3C]; int last;
    char pad6C[0xC]; int handle, unused, index, state;
    char pad88[0xB8]; PurchaseRow rows[64]; int count;
} PurchaseState;
typedef struct { char pad0[0x88]; unsigned short price; char pad8A[4]; unsigned short capacity; char pad90[0x50]; } PurchaseItem;
extern PurchaseState D_0021F240;
extern PurchaseItem D_00239BA0[];
extern unsigned char D_00139568[];
extern int D_00139688[];
extern int D_001A79F8 __attribute__((sda));
extern int D_001B2248 __attribute__((sda));
extern int D_001B223C __attribute__((sda));
extern int D_001B2240 __attribute__((sda));
extern int D_001B2244 __attribute__((sda));
typedef struct { char pad[0x1C4]; int buttons; } PurchaseInput;
extern volatile PurchaseInput D_00138180;
extern int func_002F6510(void);
extern void func_002F6608(int);
extern int func_002E5CF8(int, int, void *);
extern int func_0026F740(int, int);
extern int func_00288FB8(int);
extern void func_002F88D8(int);
extern void func_00288308(int);
extern int func_00288870(void *, int, int);
extern void func_002AD860(int);
extern void func_002887B0(int);
extern void func_0028A130(int);
extern void func_0028B6C8(int, int);
extern void func_0029B6D0(int, int);
extern void func_002FB1A0(void);
#define ITEM (D_00239BA0[D_00139568[D_0021F240.rows[D_0021F240.index].item]])
#define ROW (D_0021F240.rows[D_0021F240.index])
#define BUTTONS (D_00138180.buttons)
/* Runs the buy dialog in the vendor screen: works out how many the player can afford, reads the buttons, and completes or cancels the purchase. */
void func_002F8918(int *cancel, int *confirm)
{
    PurchaseItem upgradeInfo;
    int item, special, boughtCount;
    if (gVendorMenuState.state == 1) {
        {
            PurchaseItem *record = &ITEM;
            if (record->price) D_001B2248 = gPlayerBolts / record->price;
            else D_001B2248 = 0;
        }
        {
            int *ammo = &gItemAmmoCounts[ROW.item];
            PurchaseItem *record = &ITEM;
            int room = record->capacity - *ammo;
            if (D_001B2248 > room) D_001B2248 = room;
        }
        *cancel = 0;
        *confirm = 0;
        if (ROW.kind == 1 && gItemAmmoCounts[ROW.item] >= ITEM.capacity) {
            PlayMobySound(2, 17, gVendorMenuState.moby);
        } else if (ROW.kind == 1) {
            PurchaseItem *record = &ITEM;
            if (gPlayerBolts < record->price) PlayMobySound(2, 17, gVendorMenuState.moby);
            else *confirm = 1;
        } else if (gPlayerBolts < GetSelectedShopItemPrice()) {
            PlayMobySound(2, 0, gVendorMenuState.moby);
        }
        gVendorMenuState.state = 2;
    } else if (gVendorMenuState.state == 2) {
        if (*confirm == 1) {
            if ((BUTTONS & 0x8000) || (D_001B223C >= 16 && !(D_001B223C & 7)) || D_001B223C >= 48) {
                if (D_001B2248 >= 2) {
                    --D_001B2248;
                    if (!(D_001B223C & 3) || D_001B223C < 16)
                        PlayMobySound(1, 17, gVendorMenuState.moby);
                }
            }
            if ((BUTTONS & 0x2000) || (D_001B2240 >= 16 && !(D_001B2240 & 7)) || D_001B2240 >= 48) {
                PurchaseItem *record = &ITEM;
                if (record->price) {
                    int max = gPlayerBolts / record->price;
                    int left = record->capacity - gItemAmmoCounts[ROW.item];
                    if (left < max) max = left;
                    if (D_001B2248 < max) {
                        ++D_001B2248;
                        if (!(D_001B2240 & 3) || D_001B2240 < 16)
                            PlayMobySound(1, 17, gVendorMenuState.moby);
                    }
                }
            }
        }
        if ((BUTTONS & 16) && !(D_001B2244 & 16)) {
            *cancel = 0;
            gVendorMenuState.state = 4;
        } else if ((BUTTONS & 64) && !(D_001B2244 & 64)) {
            *cancel = 1;
            gVendorMenuState.state = 4;
        }
    } else if (gVendorMenuState.state == 4) {
        if (*cancel == 1) {
            int cost;
            PurchaseItem *gate;
            if (ROW.kind == 1) {
                PurchaseItem *record = &ITEM;
                cost = record->price * D_001B2248;
            } else cost = GetSelectedShopItemPrice();
            if (gPlayerBolts < cost && gItemAmmoCounts[ROW.item] >= (gate = &ITEM)->capacity) {
                PlayMobySound(0, 17, gVendorMenuState.moby);
            } else if (ROW.kind == 1) {
                int *ammo = &gItemAmmoCounts[ROW.item];
                PurchaseItem *record = &ITEM;
                int total;
                if (*ammo < record->capacity) {
                    total = record->price * D_001B2248;
                    if (gPlayerBolts >= total) {
                        if (*ammo > record->capacity) *ammo = record->capacity;
                        boughtCount = D_001B2248;
                        boughtCount -= EmptyStubF740(ROW.item, boughtCount);
                        {
                            PurchaseItem *record = &ITEM;
                            total = record->price * boughtCount;
                            gPlayerBolts -= total;
                        }
                        BuildVendorWeaponList(0);
                        SetShopMessageText(GetLocalizedString(0x2DCB));
                        PlayMobySound(7, 17, gVendorMenuState.moby);
                    } else {
                        SetShopMessageText(GetLocalizedString(0x2DCC));
                        PlayMobySound(0, 17, gVendorMenuState.moby);
                    }
                } else PlayMobySound(0, 17, gVendorMenuState.moby);
            } else {
                int price = GetSelectedShopItemPrice();
                if (gPlayerBolts >= price) {
                    item = ROW.item;
                    UnlockHelpEntry(item);
                    if (ROW.special) {
                        special = 0;
                        switch (ROW.item) {
                        case 12: case 14: case 17: case 18: case 53: special = 1; break;
                        }
                        if (special) {
                            PurchaseState *shop = &gVendorMenuState;
                            PurchaseRow *rows = shop->rows;
                            if (CopyHelpRecordAtDepth(&upgradeInfo, rows[shop->index].item, 1) && upgradeInfo.price)
                                gItemAmmoCounts[rows[shop->index].item] = upgradeInfo.capacity;
                        } else {
                            PurchaseState *shop = &gVendorMenuState;
                            PurchaseRow *rows = shop->rows;
                            if (CopyHelpRecordAtDepth(&upgradeInfo, rows[shop->index].item, 2) && upgradeInfo.price)
                                gItemAmmoCounts[rows[shop->index].item] = upgradeInfo.capacity;
                        }
                    }
                    if (item != 31 && item != 61) HandleRequestSlotState(item);
                    gVendorMenuState.last = item;
                    if (ROW.special) StartHelpEntry(ROW.item);
                    QueueHintForEvent(gVendorMenuState.last);
                    gPlayerBolts -= price;
                    BuildVendorWeaponList(0);
                    if (gVendorMenuState.handle != -1) set_animation_parameter(gVendorMenuState.handle, 0);
                    gVendorMenuState.handle = -1;
                    if (ROW.kind == 1) ForwardPairToLevelObject(ROW.item, 0x112A880);
                    else if (gVendorMenuState.index > gVendorMenuState.count - 1) gVendorMenuState.index = gVendorMenuState.count - 1;
                    SetShopMessageText(GetLocalizedString(0x2DCB));
                    PlayMobySound(7, 17, gVendorMenuState.moby);
                } else {
                    SetShopMessageText(GetLocalizedString(0x2DCC));
                    PlayMobySound(0, 17, gVendorMenuState.moby);
                }
            }
        } else PlayMobySound(0, 17, gVendorMenuState.moby);
        gVendorMenuState.state = 0;
        PrepareVendorSelectionPreview();
    }
}
