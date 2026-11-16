#include "names.h"
/* func_002CF5B0 in its own unit: retail reaches D_001AB9EC through $gp, so the file is compiled
   at -G32 (config/cflags.txt), like 002D01D0-g32.c. Menu input handler over the 12-entry table
   D_001ABCD0 (entries with cost 100 are skipped). One pointer variable holds the table base for the
   cost test and later the D_001A7A40 slot; that reuse makes the base live in two blocks, so global
   allocation puts it in $a0 as retail does. */
#include "common.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
typedef struct { unsigned char f0; unsigned char f1; unsigned char item; unsigned char cost; } ShopEntry;

extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern int g_unlockable_options_cursor __attribute__((sda));
extern ShopEntry g_unlockable_shop_table[] MACRO_ADDR;
extern unsigned char g_item_enabled_flags[] MACRO_ADDR;
extern unsigned char g_unlocked_item_flags[] MACRO_ADDR;
typedef struct { char pad0[0x20]; short level; char pad22[0x1E]; } Settings_002F9198;
extern Settings_002F9198 g_player_bolts MACRO_ADDR;
extern int save_count_nonzero_flags(void);
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern void tex_load_level_pack(void *);

static __inline__ ShopEntry *shop_entry(int index)
{
    return &g_unlockable_shop_table[index];
}

static __inline__ int shop_cost(int index)
{
    return shop_entry(index)->cost;
}

static __inline__ int shop_item(int index)
{
    return shop_entry(index)->item;
}

/* Handles input on the unlockable options menu: moves the cursor and toggles an option if the player has enough skill points. */
int menu_handle_unlockable_options_input(void)
{
    int result = 0;
    int entry_cost;
    unsigned char *slot;
    int available = save_count_nonzero_flags();
    int flags = g_pad_state.flags;

    if (flags & 0x10) {
        int value, return_code;
        g_unlockable_options_cursor = 0;
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            return_code = -1;
            goto finish;
        }
        return_code = 0;
finish:
        return return_code;
    }
    if (flags & 0x900) {
        g_unlockable_options_cursor = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            snd_play_from_global_bank(3, 0, 0);
            do {
                ShopEntry *table;
                if (--g_unlockable_options_cursor < 0)
                    g_unlockable_options_cursor = 11;
                table = g_unlockable_shop_table;
                if (table[g_unlockable_options_cursor].cost != 100)
                    break;
            } while (1);
        } else if (flags & 0x4000) {
            int next_index;
            ShopEntry *table;
            snd_play_from_global_bank(3, 0, 0);
            next_index = g_unlockable_options_cursor;
            table = g_unlockable_shop_table;
            do {
                if (++next_index >= 12)
                    next_index = 0;
            } while (table[next_index].cost == 100);
            g_unlockable_options_cursor = next_index;
        }
        if (g_pad_state.flags & 0x40) {
            slot = (unsigned char *)g_unlockable_shop_table;
            entry_cost = ((ShopEntry *)slot)[g_unlockable_options_cursor].cost;
            if ((entry_cost != 0x5A && entry_cost <= available)
                || (shop_cost(g_unlockable_options_cursor) == 0x5A && g_item_enabled_flags[0] != 0)) {
                snd_play_from_global_bank(4, 0, 0);
                slot = &g_unlocked_item_flags[shop_entry(g_unlockable_options_cursor)->item];
                if (*slot)
                    *slot = 0;
                else
                    *slot = 1;
                {
                    flags = shop_item(g_unlockable_options_cursor);
                    if (flags == 9 || flags == 10 || (unsigned char)flags == 2 || (unsigned char)flags == 11)
                        tex_load_level_pack((void *)(s32)g_player_bolts.level);
                }
            } else
                snd_play_from_global_bank(5, 0, 0);
        }
    }
    return result;
}
