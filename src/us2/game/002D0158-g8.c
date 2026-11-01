#include "include_asm.h"
typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
extern char *D_001A8CFC;
extern SelectionCallback D_001F2840;
extern int func_002E5E58(int, unsigned int, void *);
extern CallbackMenuState D_00138180;
extern int func_0029C560(int);
extern char *func_003415B8(void *);
extern void func_002D5E98(int);

int func_US2_002D0158(void)
{
    struct { short reserved; unsigned short key; int value; } message;
    CallbackMenuState *state = &D_00138180;
    int flags = state->flags;
    int result = 0;
    if (flags & 0x10) {
        int value = *(int *)(D_001F2840.source + 0xE0);
        int status;
        if (value != 0)
            D_001F2840.value = value;
        else if (D_001F2840.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900)
        result = 1;
    else {
        func_0029C560(flags);
        if ((state->flags & 0x40) && D_001A8CFC != 0) {
            char *data = func_003415B8(D_001A8CFC + 0x3C160);
            message.key = *(unsigned short *)(data + 8);
            message.value = *(int *)(data + 0xC);
            if (message.value == 0)
                func_002E5E58(5, 0, 0);
            func_002D5E98((int)&message);
        }
    }
    return result;
}

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
extern void func_US2_00342450(char *, char *, char *, char *);
extern void func_US2_00342520(char *, int);

int func_US2_002D02A0(void)
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
            menu->entries[0].text_id = 0x2C56;
            menu->entries[0].data = 0;
            menu->entries[1].text_id = 0x2C56;
            menu->entries[1].data = 0;
            menu->entries[2].text_id = 0x2C56;
            menu->entries[2].data = 0;
        } else {
            Menu *menu = &D_00261750;
            menu->entries[0].text_id = 0x3098;
            menu->entries[0].data = D_0025C450;
            menu->entries[1].text_id = 0x30A2;
            menu->entries[1].data = D_0025C5E8;
            menu->entries[2].text_id = 0x30D5;
            menu->entries[2].data = D_0025CCF8;
        }
        func_US2_00342450(D_001A8CFC + 0x3C160, D_002615F8, D_00261698, (char *)&D_00261750);
        func_US2_00342520(D_001A8CFC + 0x3C160, 2);
    }
    return 0;
}
