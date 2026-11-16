#include "names.h"
/* func_US2_002D8320, the USA v2.00 copy of func_002D7698: the same C, where opening a page's
   special screen also requires the active menu to be D_0025E680 or D_0025A190. */
#include "include_asm.h"
#include "common.h"

extern char g_pause_menu_state[];
typedef struct {
    u8 pad0[8];
    int field8;             /* 0x08 */
    u8 padC[8];
    u8 *owner;              /* 0x14: active menu screen */
    int current;            /* 0x18 */
    u8 pad1C[0xC];
    int saved;              /* 0x28 */
    u8 pad2C[0xAF];
    u8 active;              /* 0xDB */
    u8 padDC[0x18];
    int page;               /* 0xF4 */
    u8 padF8[8];
    u8 *savedOwner;         /* 0x100 */
    int savedCurrent;       /* 0x104 */
    u8 pad108[0x2C];
    int lock;               /* 0x134 */
    u8 pad138[8];
    int savedMode;          /* 0x140 */
} PageRoot;

typedef struct {
    u8 pad[0x230];
    int page;               /* 0x230: current page, 0..27 */
} PageMap;

typedef struct {
    u8 pad[0x1C4];
    u32 buttons;            /* 0x1C4 */
} PagePad;

typedef struct {
    u8 pad[0x30];
    int selection[28];      /* 0x30: selected row per page */
    int count;              /* 0xA0: rows on the current page */
} PageMenu;

typedef struct {
    char pad[0x34];
    int item;               /* 0x34 */
    int pad38;
    int timer;              /* 0x3C */
} PagePreview;

extern char g_map_overlay_state[];
extern char g_pad_state[];

extern PagePreview g_page_preview;
extern u8 g_level_page_root[];
extern u8 g_pause_page_b[];
extern u8 g_map_visited_flags[] MACRO_ADDR;  /* page available, one byte per page */
extern int g_request_flag_table[];            /* flag bits: bit (n & 31) of word n >> 2 */
extern int g_level_page_entry_value[];
extern int g_loader_state_word;
extern int g_current_map_index __attribute__((sda));
extern int g_vram_frame_base __attribute__((sda));
extern char g_loader_movie[];

extern int map_find_table_index(int);
extern void map_set_current_and_refresh(int);
extern int snd_play_from_global_bank(int, int, void *);
extern int menu_update_entry_states(void);
extern int menu_list_active_entries_us2(int *, int *, int *, int);
extern void menu_restore_saved_screen_image(int);
extern int req_push_queue(char *, int);
extern int req_launch_queued(char *);

/* Handles buttons on the page list: moves between pages and rows, goes back, or opens the page's own screen. */
int level_page_menu_update_input_us2(PageMenu *menu)
{
    int previous_page, row_count, old_selection, next_page, mapped;
    PageMap *map;

    previous_page = ((PageMap *)g_map_overlay_state)->page;
    if (*(PageMenu **)(((PageRoot *)g_pause_menu_state)->owner + 0xE8) != menu) {
        if (((PageMap *)g_map_overlay_state)->page < 28)
            menu->selection[((PageMap *)g_map_overlay_state)->page] = -1;
        return 0;
    }
    if ((((PagePad *)g_pad_state)->buttons & 0xD00) && !((PageRoot *)g_pause_menu_state)->lock && ((PageRoot *)g_pause_menu_state)->owner != g_level_page_root)
        return 1;

    /* Next and previous_page available page. */
    if (((PagePad *)g_pad_state)->buttons & 8) {
        for (next_page = ((PageMap *)g_map_overlay_state)->page + 1; next_page < 28; next_page++) {
            if (g_map_visited_flags[next_page] || g_current_map_index == next_page) {
                if (map_find_table_index(next_page) < 0)
                    return 0;
                map_set_current_and_refresh(next_page);
                break;
            }
        }
    }
    if (((PagePad *)g_pad_state)->buttons & 4) {
        for (next_page = ((PageMap *)g_map_overlay_state)->page - 1; next_page >= 0; next_page--) {
            if (g_map_visited_flags[next_page] || g_current_map_index == next_page) {
                if (map_find_table_index(next_page) < 0)
                    return 0;
                map_set_current_and_refresh(next_page);
                break;
            }
        }
    }
    if (((PageMap *)g_map_overlay_state)->page != previous_page) {
        snd_play_from_global_bank(3, 0, 0);
        menu_update_entry_states();
    }

    /* Rows of the page, written to the scratchpad. */
    row_count = menu_list_active_entries_us2((int *)0x70000000, 0, (int *)0x70000100, 1);
    menu->count = row_count;
    if (row_count) {
        u32 buttons = ((PagePad *)g_pad_state)->buttons;
        int *selections = menu->selection;
        {
            int *entry = &selections[((PageMap *)g_map_overlay_state)->page];
            old_selection = *entry;
            if (buttons & 0x1000)
                *entry = (old_selection + row_count - 1) % row_count;
        }
        if (buttons & 0x4000) {
            int *entry = &selections[((PageMap *)g_map_overlay_state)->page];
            *entry = (*entry + 1) % menu->count;
        }
        {
            int *entry = &selections[((PageMap *)g_map_overlay_state)->page];
            if (*entry != old_selection)
                snd_play_from_global_bank(3, 0, 0);
        }
        if ((buttons & 0x5000) || ((PageMap *)g_map_overlay_state)->page != previous_page) {
            int *entry;
            g_page_preview.timer = -576;
            entry = &selections[((PageMap *)g_map_overlay_state)->page];
            g_page_preview.item = ((int *)0x70000000)[*entry];
            *g_level_page_entry_value = ((int *)0x70000100)[*entry];
        }
    } else {
        g_page_preview.item = 0;
        *g_level_page_entry_value = -1;
    }

    /* Back. */
    if ((((PagePad *)g_pad_state)->buttons & 0x10) && ((PageRoot *)g_pause_menu_state)->owner != g_level_page_root) {
        int back = *(int *)(((PageRoot *)g_pause_menu_state)->owner + 0xE0);
        int status;
        if (back)
            ((PageRoot *)g_pause_menu_state)->current = back;
        else if (!((PageRoot *)g_pause_menu_state)->lock) {
            status = -1;
            goto done;
        }
        status = 0;
done:
        return status;
    }

    /* Open the page's special screen. */
    if ((((PagePad *)g_pad_state)->buttons & 0x20) && ((PageMap *)g_map_overlay_state)->page >= 0) {
        if (((PageRoot *)g_pause_menu_state)->active)
            return 0;
        if (((PageMap *)g_map_overlay_state)->page == 0)
            mapped = 21;
        else if (((PageMap *)g_map_overlay_state)->page == 24)
            mapped = 0;
        else
            mapped = ((PageMap *)g_map_overlay_state)->page;
        map = ((PageMap *)g_map_overlay_state);
        if (map->page >= 0) {
            unsigned int word = (unsigned)mapped >> 2;
            int bit = 1 << (mapped & 0x1F);
            if (g_request_flag_table[word] & bit) {
                PageRoot *root = ((PageRoot *)g_pause_menu_state);
                if (root->owner != g_level_page_root && root->owner != g_pause_page_b)
                    return 0;
                g_vram_frame_base = root->saved;
                menu_restore_saved_screen_image(0);
                root->savedMode = g_loader_state_word;
                root->savedOwner = root->owner;
                root->page = map->page;
                root->savedCurrent = root->field8;
                g_loader_state_word = 2;
                req_push_queue(g_loader_movie, mapped);
                req_launch_queued(g_loader_movie);
                return 1;
            }
        }
    }
    return 0;
}
