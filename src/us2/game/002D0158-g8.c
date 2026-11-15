#include "include_asm.h"
#include "names.h"
typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
extern char *D_001A8CFC;
extern SelectionCallback g_pause_menu_state;
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern CallbackMenuState g_pad_state;
extern int func_0029C560(int);
extern char *tab_menu_get_selected_entry(void *);
extern void menu_start_action(int);

int func_US2_002D0158(void)
{
    struct { short reserved; unsigned short key; int value; } message;
    CallbackMenuState *state = &g_pad_state;
    int flags = state->flags;
    int result = 0;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        int status;
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
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
            char *data = tab_menu_get_selected_entry(D_001A8CFC + 0x3C160);
            message.key = *(unsigned short *)(data + 8);
            message.value = *(int *)(data + 0xC);
            if (message.value == 0)
                snd_play_from_global_bank(5, 0, 0);
            menu_start_action((int)&message);
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
extern unsigned char g_item_slot_to_record[];
extern unsigned char D_001A7A0A;
extern unsigned char g_item_owned_flags[] __attribute__((sda));
extern unsigned char D_001A7A80[] __attribute__((sda));
extern unsigned char g_weapon_table[];
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
            if (((ClassRecord *)(g_item_slot_to_record[i] * 0xE0 + (int)g_weapon_table))->active && i != 9 && i != 10) {
                if (!g_item_owned_flags[i]) {
                    D_001AA430 = 0;
                    D_001AA434 = 0;
                    D_001AA438 = 0;
                } else {
                    for (j = 0; j < 3; j++) {
                        int value;
                        ClassRecord *record;
                        switch (j) {
                        case 0:
                            record = (ClassRecord *)(g_item_slot_to_record[i] * 0xE0 + (int)g_weapon_table);
                            value = record->requirement[0];
                            break;
                        case 1:
                            record = (ClassRecord *)(g_item_slot_to_record[i] * 0xE0 + (int)g_weapon_table);
                            value = record->requirement[1];
                            break;
                        case 2:
                            record = (ClassRecord *)(g_item_slot_to_record[i] * 0xE0 + (int)g_weapon_table);
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
