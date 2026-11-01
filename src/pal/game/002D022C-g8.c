#include "include_asm.h"

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
extern void func_PAL_003435C0(char *, char *, char *, char *);
extern void func_PAL_00343690(char *, int);

int func_PAL_002D0290(void)
{
    int i, j;

    if (D_001A8CFC) {
        D_001AA430 = 1;
        D_001AA434 = 1;
        D_001AA438 = 1;
        for (i = 0; i < 56; i++) {
            if (((ClassRecord *)(D_00139568[i] * 0xE0 + (int)D_00239BA0))->active && i != 9 && i != 10) {
                if (!D_001A7AF8[i]) {
                    D_001AA430 = 0;
                    D_001AA434 = 0;
                    D_001AA438 = 0;
                } else {
                    for (j = 0; j < 3; j++) {
                        int value;
                        ClassRecord *record;
                        switch (j) {
                        case 0:
                            record = (ClassRecord *)(D_00139568[i] * 0xE0 + (int)D_00239BA0);
                            value = record->requirement[0];
                            break;
                        case 1:
                            record = (ClassRecord *)(D_00139568[i] * 0xE0 + (int)D_00239BA0);
                            value = record->requirement[1];
                            break;
                        case 2:
                            record = (ClassRecord *)(D_00139568[i] * 0xE0 + (int)D_00239BA0);
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
            menu->entries[0].text_id = 0xBD1;
            menu->entries[0].data = 0;
            menu->entries[1].text_id = 0xBD1;
            menu->entries[1].data = 0;
            menu->entries[2].text_id = 0xBD1;
            menu->entries[2].data = 0;
        } else {
            Menu *menu = &D_00261750;
            menu->entries[0].text_id = 0x1114;
            menu->entries[0].data = D_0025C450;
            menu->entries[1].text_id = 0x111E;
            menu->entries[1].data = D_0025C5E8;
            menu->entries[2].text_id = 0x1408;
            menu->entries[2].data = D_0025CCF8;
        }
        func_PAL_003435C0(D_001A8CFC + 0x3C210, D_002615F8, D_00261698, (char *)&D_00261750);
        func_PAL_00343690(D_001A8CFC + 0x3C210, 2);
    }
    return 0;
}
