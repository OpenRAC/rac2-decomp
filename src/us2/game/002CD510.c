#include "include_asm.h"

#include "common.h"
typedef struct {
    s32 v[8];
} IdTable_1AB938;
typedef struct {
    s32 v[7];
} StringTable_1AB958;
typedef struct {
    int value;
    int id;
    int a;
    int b;
    int c;
} CheatEntry_25FC90;
extern IdTable_1AB938 g_cheat_id_table;
extern StringTable_1AB958 g_cheat_string_table;
extern char g_unlocked_item_flags[] __attribute__((sda));
extern unsigned char g_cheat_unlocked_flags[] __attribute__((sda));
extern CheatEntry_25FC90 g_cheat_list[];

/* Builds the list of cheats the player has unlocked from two small lookup tables, and ends the list with a blank entry. */
int menu_build_unlocked_cheat_list_us2(void)
{
    IdTable_1AB938 ids = g_cheat_id_table;
    StringTable_1AB958 strings = g_cheat_string_table;
    int count = 0;
    int i;

    for (i = 0; i < 12; i++) {
        if (ids.v[i] == -1)
            break;
        if (g_cheat_unlocked_flags[ids.v[i]] != 0) {
            g_cheat_list[count].value = strings.v[i];
            g_cheat_list[count].id = (int)(g_unlocked_item_flags + ids.v[i]);
            g_cheat_list[count].a = 0x2C5C;
            g_cheat_list[count].b = 0x2C5D;
            g_cheat_list[count].c = 0;
            count++;
        }
    }
    g_cheat_list[count].value = 0;
    return 0;
}

