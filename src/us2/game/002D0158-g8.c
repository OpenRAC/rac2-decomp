#include "include_asm.h"
#include "names.h"
typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
extern char *g_resident_data_base;
extern SelectionCallback g_pause_menu_state;
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern CallbackMenuState g_pad_state;
extern int func_0029C560(int);
extern char *tab_menu_get_selected_entry(void *);
extern void menu_start_action(int);

int menu_handle_input_send_selection_or_refuse_us2(void)
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
        if ((state->flags & 0x40) && g_resident_data_base != 0) {
            char *data = tab_menu_get_selected_entry(g_resident_data_base + 0x3C160);
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
extern int g_extras_unlock_flag_a __attribute__((sda));
extern int g_extras_unlock_flag_b __attribute__((sda));
extern int g_special_items_unlock_flag __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_extras_unlocked_flag;
extern unsigned char g_item_owned_flags[] __attribute__((sda));
extern unsigned char g_movie_seen_flags[] __attribute__((sda));
extern unsigned char g_weapon_table[];
extern Menu g_extras_tab_table_c;
extern char g_extras_tab_table_a[], g_extras_tab_table_b[];
extern char g_extras_unlock_entry_a[], g_extras_unlock_entry_b[], g_extras_unlock_entry_c[];
extern void tab_menu_set_tables_us2(char *, char *, char *, char *);
extern void tab_menu_switch_tab_us2(char *, int);

int func_US2_002D02A0(void)
{
    int i, j;

    if (g_resident_data_base) {
        g_extras_unlock_flag_a = 1;
        g_extras_unlock_flag_b = 1;
        g_special_items_unlock_flag = 1;
        for (i = 0; i < 56; i++) {
            if (((ClassRecord *)(g_item_slot_to_record[i] * 0xE0 + (int)g_weapon_table))->active && i != 9 && i != 10) {
                if (!g_item_owned_flags[i]) {
                    g_extras_unlock_flag_a = 0;
                    g_extras_unlock_flag_b = 0;
                    g_special_items_unlock_flag = 0;
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
                        if (value && !((unsigned long)g_movie_seen_flags[i] & ((1U << (j * 2)) & 255UL))) {
                            g_extras_unlock_flag_b = 0;
                            g_special_items_unlock_flag = 0;
                        }
                    }
                }
            }
        }
        if (!g_extras_unlocked_flag) {
            Menu *menu = &g_extras_tab_table_c;
            menu->entries[0].text_id = 0x2C56;
            menu->entries[0].data = 0;
            menu->entries[1].text_id = 0x2C56;
            menu->entries[1].data = 0;
            menu->entries[2].text_id = 0x2C56;
            menu->entries[2].data = 0;
        } else {
            Menu *menu = &g_extras_tab_table_c;
            menu->entries[0].text_id = 0x3098;
            menu->entries[0].data = g_extras_unlock_entry_a;
            menu->entries[1].text_id = 0x30A2;
            menu->entries[1].data = g_extras_unlock_entry_b;
            menu->entries[2].text_id = 0x30D5;
            menu->entries[2].data = g_extras_unlock_entry_c;
        }
        tab_menu_set_tables_us2(g_resident_data_base + 0x3C160, g_extras_tab_table_a, g_extras_tab_table_b, (char *)&g_extras_tab_table_c);
        tab_menu_switch_tab_us2(g_resident_data_base + 0x3C160, 2);
    }
    return 0;
}
