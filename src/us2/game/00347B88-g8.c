#include "common.h"

/* func_US2_00347B88, the USA v2.00 copy of func_00346C60: the same C, where the menu fields
   move (origin to +0x438, detail to +0x440, name, column and row down 0x38), the last two
   widgets sit at +0x268 and +0x2C0, and the ammo labels are text ids 0x2C5F and 0x2C4F. */
/* A 4 x 6 item grid menu: the pad moves the cursor (sound 3, wrapping at the edges), the
   widgets are placed from the menu's origin, and an owned entry under the cursor gets its
   name and ammo text (current from D_00139688, maximum from its class record, as in
   00288308.c and 00287E98.c). Cross on an owned entry plays sound 4, records it in
   D_001F2880 and returns the cursor index; on any other entry it plays sound 5. Returns -1
   otherwise. */
typedef struct {
    char pad0[4];
    unsigned char byte04;       /* +0x04: set, the entry counts as owned */
    char pad5;
    short material;             /* +0x06 */
    int name;                   /* +0x08: text id */
    char pad0C[0x7C];
    unsigned short usesAmmo;    /* +0x88 */
    char pad8A[4];
    unsigned short maxAmmo;     /* +0x8E */
    char tail[0x50];
} ItemRecord;

typedef struct {
    char pad0[0x438];
    float *origin;              /* +0x438: position the widgets are placed from */
    char pad43C[4];
    char detail[0x40];          /* +0x440 */
    char name[0x44];            /* +0x480 */
    int column;                 /* +0x4C4 */
    int row;                    /* +0x4C8 */
} ItemMenu;

extern int snd_play_from_global_bank(int, int, void *);
extern void *memset(void *, int, unsigned int);
extern int math_ping_pong_blend_values(int, int, int, int, int);
extern int *object_get_fourth_field(void *);
extern void object_set_first_float4(void *, float, float, float, float);
extern char *GetLocalizedString(int);
extern int sprintf(char *, char *, ...);
extern char g_shop_cursor_pos[], g_shop_item_pos_a[], g_shop_item_pos_b[], g_shop_item_pos_c[];
extern char g_str_shop_label_format[], g_str_shop_ammo_format[], g_str_shop_ammo_split_format[], g_str_count_format[], g_str_shop_max_ammo_format[];
extern char ref_00346C60_00[];
extern short g_menu_item_table_first[][5];
extern ItemRecord g_weapon_table[];
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_item_owned_flags[] MACRO_ADDR;
extern unsigned char g_help_unlocked_flags[] MACRO_ADDR;
extern int g_item_ammo_counts[];
extern int g_selected_item_material __attribute__((sda));
extern int g_selection_grid_cursor[];

int func_US2_00347B88(ItemMenu *menu, int buttons)
{
    float pos0[2] __attribute__((aligned(16)));
    float pos4C[2] __attribute__((aligned(16)));
    float pos130[2] __attribute__((aligned(16)));
    float pos98[2] __attribute__((aligned(16)));
    float cursor[2] __attribute__((aligned(16)));
    float pos17C[2] __attribute__((aligned(16)));
    float pos210[2] __attribute__((aligned(16)));
    float pos258[2] __attribute__((aligned(16)));
    float pos2A0[2] __attribute__((aligned(16)));
    int result = -1;
    int old = menu->column + menu->row * 4;
    int selection, n;
    int *color;
    int entry, item, ammo, maxAmmo;
    ItemRecord *record, *initialRecord;
    char *text;

    if (buttons & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        n = menu->row - 1;
        menu->row = n < 0 ? 5 : n;
    } else if (buttons & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        n = menu->row + 1;
        menu->row = n <= 5 ? n : 0;
    } else if (buttons & 0x8000) {
        snd_play_from_global_bank(3, 0, 0);
        n = menu->column - 1;
        menu->column = n < 0 ? 3 : n;
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3, 0, 0);
        n = menu->column + 1;
        menu->column = n <= 3 ? n : 0;
    }
    selection = menu->column + menu->row * 4;

    memset(pos0, 0, 8);
    memset(pos4C, 0, 8);
    memset(pos130, 0, 8);
    memset(pos98, 0, 8);
    __builtin_memcpy(cursor, g_shop_cursor_pos, 8);
    memset(pos17C, 0, 8);
    __builtin_memcpy(pos210, g_shop_item_pos_a, 8);
    __builtin_memcpy(pos258, g_shop_item_pos_b, 8);
    __builtin_memcpy(pos2A0, g_shop_item_pos_c, 8);
    if (old != selection)
        math_ping_pong_blend_values(0, 0, 1, 0, 1);
    color = object_get_fourth_field((char *)menu + 0xE4);
    *color = math_ping_pong_blend_values(0x60442D00, 0x70FFFEED, 20, 0, 0);

    object_set_first_float4((char *)menu + 0x0, pos0[0] + menu->origin[0], pos0[1] + menu->origin[1], 0.0f, 0.0f);
    object_set_first_float4((char *)menu + 0x4C, pos4C[0] + menu->origin[0], pos4C[1] + menu->origin[1], 0.0f, 0.0f);
    object_set_first_float4((char *)menu + 0x130, pos130[0] + menu->origin[0], pos130[1] + menu->origin[1], 0.0f, 0.0f);
    object_set_first_float4((char *)menu + 0x98, pos98[0] + menu->origin[0], pos98[1] + menu->origin[1], 0.0f, 0.0f);
    object_set_first_float4((char *)menu + 0xE4,
                  cursor[0] + menu->origin[0] + (float)menu->column * 53.5f,
                  cursor[1] + menu->origin[1] + (float)menu->row * 47.0f, 0.0f, 0.0f);
    object_set_first_float4((char *)menu + 0x17C, pos17C[0] + menu->origin[0], pos17C[1] + menu->origin[1], 0.0f, 0.0f);
    object_set_first_float4((char *)menu + 0x210, pos210[0] + menu->origin[0], pos210[1] + menu->origin[1], 0.0f, 0.0f);

    g_selected_item_material = -1;
    if (selection >= 0) {
        entry = g_menu_item_table_first[selection][3];
        item = g_item_slot_to_record[entry];
        initialRecord = &g_weapon_table[item];
        if (initialRecord->byte04) {
            g_item_owned_flags[entry] = 1;
            g_help_unlocked_flags[entry] = 1;
        }
        if (g_item_owned_flags[entry]) {
            text = menu->detail;
            g_selected_item_material = g_weapon_table[g_item_slot_to_record[entry]].material;
            sprintf(menu->name, GetLocalizedString(g_weapon_table[g_item_slot_to_record[entry]].name));
            record = &g_weapon_table[g_item_slot_to_record[entry]];
            ammo = g_item_ammo_counts[entry];
            maxAmmo = record->maxAmmo;
            if (record->usesAmmo) {
                text += sprintf(text, g_str_shop_label_format, GetLocalizedString(0x2C5F));
                if (ammo < 1000)
                    text += sprintf(text, g_str_shop_ammo_format, ammo);
                else
                    text += sprintf(text, g_str_shop_ammo_split_format, ammo / 1000, ammo % 1000);
                if (maxAmmo < 1000)
                    sprintf(text, g_str_count_format, maxAmmo);
                else
                    sprintf(text, g_str_shop_max_ammo_format, maxAmmo / 1000, maxAmmo % 1000);
            } else {
                sprintf(text, ref_00346C60_00, GetLocalizedString(0x2C4F));
            }
            if (buttons & 0x40) {
                result = selection;
                snd_play_from_global_bank(4, 0, 0);
                g_selection_grid_cursor[0] = entry;
            }
        } else {
            menu->detail[0] = 0;
            menu->name[0] = 0;
            if (buttons & 0x40)
                snd_play_from_global_bank(5, 0, 0);
        }
    }

    object_set_first_float4((char *)menu + 0x268, pos258[0] + menu->origin[0], pos258[1] + menu->origin[1], 0.0f, 0.0f);
    object_set_first_float4((char *)menu + 0x2C0, pos2A0[0] + menu->origin[0], pos2A0[1] + menu->origin[1], 0.0f, 0.0f);
    return result;
}
