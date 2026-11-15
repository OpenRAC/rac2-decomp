#include "include_asm.h"
#include "names.h"

typedef struct {
    int id;
    int kind;
    char pad[12];
    int owned;
} VendorSlot;
typedef struct {
    char pad[0x80];
    int index;
    char pad2[0xBC];
    VendorSlot slots[1];
} VendorState;
typedef struct {
    char pad[8];
    int text;
    char pad2[0x7C];
    unsigned short price;
    char pad3[4];
    unsigned short max;
    char pad4[0x50];
} VendorItem;
extern VendorState D_0021F240;
extern unsigned char D_00139568[];
extern int D_00139688[];
extern char D_00239BA0[];
extern char D_001AD3D0[];
extern int D_001A7340;
extern int D_001A79F8;
extern float D_001B2280;
extern char *func_00288FB8(int);
extern char *func_00115690(char *, char *);
extern int func_00115DA8(char *, char *, ...);
extern int func_0027FB40(int, int, unsigned long, char *, int);
extern void func_0027FA10(int, int, unsigned long, char *, int);
extern void func_0027F5B8(int, int, unsigned long, char *, int);
extern void func_002F9BC0(char *, int);
extern void func_00288870(void *, int, int);
extern int func_002F6510(void);
extern int func_0028E588(int, int);
extern int func_0028EA58(int, int, int, int, int, void *);

/* Draws the selected vendor item, its price and the purchase/maximum-ammo prompt. */
void func_002FA880(void)
{
    char text[256];
    char info[224];
    int available = 1;
    VendorState *v;
    int color = 0x80F0F0F0;
    v = &gVendorMenuState;
    if (v->slots[v->index].kind == available) {
        int id = v->slots[v->index].id;
        char *copied;
        char *fmt = D_001AD3D0;
        if (gItemAmmoCounts[id] >=
            ((VendorItem *)(gWeaponTable_00239BA0 + gItemSlotToRecord[id] * 224))->max)
            available = 0;
        copied = strcpy(text, GetLocalizedString(((VendorItem *)(gWeaponTable_00239BA0 + gItemSlotToRecord[id] * 224))->text));
        Sprintf(text, fmt, copied, GetLocalizedString(0x2DC9));
        DrawTextCenteredMediumFont(gScreenWidth >> 1, (int)(D_001B2280 * 274.0f + 0.5f), 0x80F0F0F0L, text, -1);
        FormatNumberWithSeparators_002F9BC0(text, ((VendorItem *)(gWeaponTable_00239BA0 + gItemSlotToRecord[v->slots[v->index].id] * 224))->price);
        if (gPlayerBolts < ((VendorItem *)(gWeaponTable_00239BA0 + gItemSlotToRecord[v->slots[v->index].id] * 224))->price)
            color = (int)0x802020F0;
    } else {
        if (gVendorMenuState.slots[gVendorMenuState.index].owned) {
            int special = 0;
            switch (gVendorMenuState.slots[gVendorMenuState.index].id) {
            case 12:
            case 14:
            case 17:
            case 18:
            case 53:
                special = 1;
            }
            CopyHelpRecordAtDepth(info, gVendorMenuState.slots[gVendorMenuState.index].id, special ? 1 : 2);
            DrawTextCenteredMediumFont(gScreenWidth >> 1, (int)(D_001B2280 * 274.0f + 0.5f), 0x80F0F0F0L, GetLocalizedString(*(int *)(info + 8)), -1);
        } else {
            DrawTextCenteredMediumFont(gScreenWidth >> 1, (int)(D_001B2280 * 274.0f + 0.5f), 0x80F0F0F0L, GetLocalizedString(((VendorItem *)(gWeaponTable_00239BA0 + gItemSlotToRecord[gVendorMenuState.slots[gVendorMenuState.index].id] * 224))->text), -1);
        }
        FormatNumberWithSeparators_002F9BC0(text, GetSelectedShopItemPrice());
        if (gPlayerBolts < GetSelectedShopItemPrice())
            color = (int)0x802020F0;
    }
    if (available) {
        int tex;
        DrawTextRightAlignedMediumFont(220, (int)(D_001B2280 * 210.0f + 0.5f), 0x80F0F0F0L, GetLocalizedString(0x114E), -1);
        ((int *)info)[0] = 0x60F0F0B0;
        ((int *)info)[1] = 0x60F0F0B0;
        ((int *)info)[2] = 0x60F0F0B0;
        ((int *)info)[3] = 0x60F0F0B0;
        tex = GetIconFrame(0x7567, 0);
        DrawHudSpriteGradient(tex, 236, (int)(D_001B2280 * 210.0f + 0.5f), 16, (int)(D_001B2280 * 16.0f + 0.5f), info);
        DrawTextMediumFont(256, (int)(D_001B2280 * 210.0f + 0.5f), color, text, -1);
    } else {
        DrawTextCenteredMediumFont(259, (int)(D_001B2280 * 210.0f + 0.5f), 0x80F0F0F0L, GetLocalizedString(0x1126), -1);
    }
}
