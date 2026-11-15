#include "common.h"

/* Partial model and class layouts measured from the item fields. */
typedef struct { int group; int pad[3]; } UpgradeGroup;
typedef union {
    struct { char prefix[0x144]; UpgradeGroup rows[0];
} groups;
    struct { char prefix[0x140]; UpgradeGroup rows[0];
} slots;
    struct { char prefix[0x148]; UpgradeGroup rows[0];
} prices;
} UpgradeModel;
extern UpgradeModel D_L00_0022F7C0;
extern unsigned char D_001A7A80[] __attribute__((sda));
extern int D_L00_001A8E40[] __attribute__((sda));
extern unsigned char D_00139568[];
typedef struct { char prefix[8]; int name; char tail[0xE0-12]; } UpgradeInfo;
extern UpgradeInfo D_L00_00262570[];
extern char D_L00_001AD738[10];
extern char D_L00_001AD748[9];
extern char D_L00_001AD758[9];
extern int D_L00_001AD718 __attribute__((sda));
extern int D_L00_001AD71C;
extern int D_L00_001AD724;
extern int D_L00_001AD728 __attribute__((sda));
extern int D_L00_001AD72C;
extern int D_L00_001AD730 __attribute__((sda));
extern int D_L00_001AD734;
extern float D_L00_001B25E0;
extern int func_00288FB8(int);
extern int func_00115DA8(char *, char *, ...);
extern int func_0027FB40(int, int, unsigned long long, unsigned char *, int);
extern void func_002F9BC0(char *, int);
extern int func_0028E588(int, int);
extern int func_L00_002E9120(unsigned char *, int);
extern int func_0028EA58(int, int, int, int, int, unsigned int *);
extern int func_002B0D70(void);

/* Draws the upgrade name, its price and the player's current amount, each with a bolt icon, unless the upgrade is already owned. */
void func_L00_00377580(void) {
    char first[256];
    char second[256];
    unsigned int colors[4];
    char *model = (char *)&gPurchaseMenuModel;
    int group = gPurchaseMenuModel.groups.rows[*(int *)(model + 0x80)].group;
    int slot = gPurchaseMenuModel.slots.rows[*(int *)(model + 0x80)].group;
    int handle;
    int width;
    if (((unsigned long)D_001A7A80[group] & ((1U << (slot * 2)) & 255UL)) != 0) return;
    if (group != 0) {
        Sprintf(first, D_L00_001AD738,
            (unsigned char *)GetLocalizedString(D_L00_001A8E40[slot]),
            (unsigned char *)GetLocalizedString(((UpgradeInfo *)((char *)gWeaponTable_L00 + gItemSlotToRecord[gPurchaseMenuModel.groups.rows[*(int *)(model + 0x80)].group] * 224))->name));
        DrawTextCenteredMediumFont(D_L00_001AD728, (int)((float)D_L00_001AD72C * D_L00_001B25E0 + 0.5f),
                      0x80F0F0F0ULL, (unsigned char *)first, -1);
    }
    FormatNumberWithSeparators_002F9BC0(first, gPurchaseMenuModel.prices.rows[*(int *)(model + 0x80)].group);
    Sprintf(second, D_L00_001AD748, (unsigned char *)GetLocalizedString(0x114E), first,
        (unsigned char *)GetLocalizedString(0x3262));
    DrawTextCenteredMediumFont(D_L00_001AD718, (int)((float)D_L00_001AD71C * D_L00_001B25E0 + 0.5f),
                  0x80F0F0F0ULL, (unsigned char *)second, -1);
    colors[0] = 0x60F0F0B0;
    colors[1] = 0x60F0F0B0;
    colors[2] = 0x60F0F0B0;
    colors[3] = 0x60F0F0B0;
    handle = GetIconFrame(0xEAA2, 0);
    width = MeasureTextWidthSet2((unsigned char *)second, -1);
    DrawHudSpriteGradient(handle, D_L00_001AD718 + (width >> 1) + 4,
                  (int)((float)D_L00_001AD724 * D_L00_001B25E0 + 0.5f), 16,
                  (int)(D_L00_001B25E0 * 16.0f + 0.5f), colors);
    Sprintf(first, D_L00_001AD758, (unsigned char *)GetLocalizedString(0x2F2D),
        CountItemsAboveBaseline(), (unsigned char *)GetLocalizedString(0x3262));
    DrawTextCenteredMediumFont(D_L00_001AD730, (int)((float)D_L00_001AD734 * D_L00_001B25E0 + 0.5f),
                  0x80F0F0F0ULL, (unsigned char *)first, -1);
    handle = GetIconFrame(0xEAA2, 0);
    width = MeasureTextWidthSet2((unsigned char *)first, -1);
    DrawHudSpriteGradient(handle, D_L00_001AD730 + (width >> 1) + 4,
                  (int)((float)D_L00_001AD734 * D_L00_001B25E0 + 0.5f), 16,
                  (int)(D_L00_001B25E0 * 16.0f + 0.5f), colors);
}
