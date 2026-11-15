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

extern int D_001AD1C0 __attribute__((sda));
extern int D_001AD1B8 __attribute__((sda));
extern Func002F71B8Table D_001AD268;
extern unsigned char D_001395B8[];
extern Func002F71B8List g_vendor_menu_state;
extern int flag_is_byte_set(void);

void shop_rebuild_unlocked_slot_list(void)
{
    Func002F71B8Table values = D_001AD268;
    int i;

    g_vendor_menu_state.count = 0;
    D_001AD1B8 = 0;
    for (i = D_001AD1C0 != 0 ? D_001AD1C0 + 1 : 1; i < 5; i++) {
        if ((unsigned int)i >= 8 ||
            ((D_001395B8[0x8D] >> i) & 1) == 0) {
            if (flag_is_byte_set() == 0)
                continue;
        }
        g_vendor_menu_state.entry[g_vendor_menu_state.count].slot = i;
        g_vendor_menu_state.entry[g_vendor_menu_state.count].value = values.value[i];
        g_vendor_menu_state.entry[g_vendor_menu_state.count].id = i + 0xEA92;
        g_vendor_menu_state.count = g_vendor_menu_state.count + 1;
    }
}
