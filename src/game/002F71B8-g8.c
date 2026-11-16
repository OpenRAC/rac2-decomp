#include "include_asm.h"
#include "names.h"

/* Rebuilds the list of the slots after the current one that are unlocked (the bit in
   the save byte, or the fallback check), each with its id and table value. */

typedef struct {
    int value[5];
} Func002F71B8Table;

typedef struct {
    int id;
    int value;
    int slot;
} Func002F71B8Entry;

typedef struct {
    char pad[0x140];
    Func002F71B8Entry entry[0x80];
    int count;
} Func002F71B8List;

extern int g_shop_saved_bolts_level __attribute__((sda));
extern int g_shop_bolts_level_override __attribute__((sda));
extern Func002F71B8Table g_shop_slot_value_table;
extern unsigned char g_game_flag_table[];
extern Func002F71B8List g_vendor_menu_state;
extern int flag_is_byte_set(void);

void shop_rebuild_unlocked_slot_list(void)
{
    Func002F71B8Table values = g_shop_slot_value_table;
    int i;

    g_vendor_menu_state.count = 0;
    g_shop_bolts_level_override = 0;
    for (i = g_shop_saved_bolts_level != 0 ? g_shop_saved_bolts_level + 1 : 1; i < 5; i++) {
        if ((unsigned int)i >= 8 ||
            ((g_game_flag_table[0x8D] >> i) & 1) == 0) {
            if (flag_is_byte_set() == 0)
                continue;
        }
        g_vendor_menu_state.entry[g_vendor_menu_state.count].slot = i;
        g_vendor_menu_state.entry[g_vendor_menu_state.count].value = values.value[i];
        g_vendor_menu_state.entry[g_vendor_menu_state.count].id = i + 0xEA92;
        g_vendor_menu_state.count = g_vendor_menu_state.count + 1;
    }
}
