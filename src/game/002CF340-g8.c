#include "include_asm.h"
#include "names.h"

/* 0xE0-byte class records indexed through D_00139568. */
typedef struct {
    int active;
    char pad04[0x94];
    int requirement[3];
    char pad_a4[0x3C];
} ClassRecord;

typedef struct {
    int text_id;
    int unk04;
    void *data;
    int unk0C;
    int unk10;
} MenuEntry;

typedef struct {
    char header[0x40];
    MenuEntry entries[3];
} Menu;

extern char *D_001A8CFC;
extern int D_001AA430 __attribute__((sda));
extern int D_001AA434 __attribute__((sda));
extern int D_001AA438 __attribute__((sda));
extern unsigned char D_00139568[];
extern unsigned char D_001A7A0A;
extern unsigned char D_001A7AF8[] __attribute__((sda));
extern unsigned char D_001A7A80[] __attribute__((sda));
extern unsigned char D_00239BA0[];
extern Menu D_00261750;
extern char D_002615F8[], D_00261698[];
extern char D_0025C450[], D_0025C5E8[], D_0025CCF8[];
extern void func_00341540(char *, char *, char *, char *);
extern void func_00341610(char *, int);

/* Works out which Extras sections are unlocked from game progress and fills in the three-entry Extras menu. */
int func_002CF340(void)
{
    int i, j;

    if (D_001A8CFC) {
        D_001AA430 = 1;
        D_001AA434 = 1;
        D_001AA438 = 1;
        for (i = 0; i < 56; i++) {
            if (((ClassRecord *)(gItemSlotToRecord[i] * 0xE0 + (int)gWeaponTable_00239BA0))->active && i != 9 && i != 10) {
                if (!gItemOwnedFlags[i]) {
                    D_001AA430 = 0;
                    D_001AA434 = 0;
                    D_001AA438 = 0;
                } else {
                    for (j = 0; j < 3; j++) {
                        int value;
                        ClassRecord *record;
                        switch (j) {
                        case 0:
                            record = (ClassRecord *)(gItemSlotToRecord[i] * 0xE0 + (int)gWeaponTable_00239BA0);
                            value = record->requirement[0];
                            break;
                        case 1:
                            record = (ClassRecord *)(gItemSlotToRecord[i] * 0xE0 + (int)gWeaponTable_00239BA0);
                            value = record->requirement[1];
                            break;
                        case 2:
                            record = (ClassRecord *)(gItemSlotToRecord[i] * 0xE0 + (int)gWeaponTable_00239BA0);
                            value = record->requirement[2];
                            break;
                        default:
                            value = 0;
                            break;
                        }
                        if (value && !((unsigned long)D_001A7A80[i] & ((1U << (j * 2)) & 255UL))) {
                            D_001AA434 = 0;
                            D_001AA438 = 0;
                        }
                    }
                }
            }
        }
        if (!D_001A7A0A) {
            Menu *menu = &D_00261750;
            menu->entries[0].text_id = 0x2DC0;
            menu->entries[0].data = 0;
            menu->entries[1].text_id = 0x2DC0;
            menu->entries[1].data = 0;
            menu->entries[2].text_id = 0x2DC0;
            menu->entries[2].data = 0;
        } else {
            Menu *menu = &D_00261750;
            menu->entries[0].text_id = 0x3202;
            menu->entries[0].data = D_0025C450;
            menu->entries[1].text_id = 0x320C;
            menu->entries[1].data = D_0025C5E8;
            menu->entries[2].text_id = 0x323F;
            menu->entries[2].data = D_0025CCF8;
        }
        SetTabbedMenuTables(D_001A8CFC + 0x3BE08, D_002615F8, D_00261698, (char *)&D_00261750);
        SwitchTabbedMenuTab(D_001A8CFC + 0x3BE08, 2);
    }
    return 0;
}
