#include "names.h"
/* func_PAL_002D82D8, the PAL copy of func_002D7698: the same C. */
#include "common.h"
extern char g_pause_menu_state[];

/* One save-slot summary row of the save context at D_001393E0 (28 bytes). */
typedef struct {
    int state;              /* -1: empty slot */
    int score;
    int extra;
    int ticks;              /* play time, 60 per second */
    unsigned char pad[4];
    unsigned char date[4];
    int unknown;
} SaveRow;

extern SaveRow g_save_slot_rows[];

/* GP-relative layout coefficients of the save-slot panel. */
 /* line height */
 /* slot gap */
extern int g_save_slot_icon_y_table[] MACRO_ADDR;
extern int g_save_slot_icon_size_table[] MACRO_ADDR;
/* Format strings. */
extern char g_str_save_slot_time_fmt[] NOT_SDA;
extern char g_str_save_slot_score_fmt[] NOT_SDA;
extern char g_str_save_slot_thousands_fmt[] NOT_SDA;
extern char g_str_save_slot_score_millions_fmt[] NOT_SDA;
extern char g_str_save_slot_date_fmt[] NOT_SDA;

/* The game state at D_001F2840, as far as the page menu uses it. */
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
    u8 *saved_owner;         /* 0x100 */
    int saved_current;       /* 0x104 */
    u8 pad108[0x2C];
    int lock;               /* 0x134 */
    u8 pad138[8];
    int saved_mode;          /* 0x140 */
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
extern int menu_list_active_entries(int *, int *, int *, int);
extern void menu_restore_saved_screen_image(int);
extern int req_push_queue(char *, int);
extern int req_launch_queued(char *);

/* Level page menu input: changes the shown page, moves the row selection, goes back and opens the page's special screen. */
int level_page_menu_update_input_pal(PageMenu *menu)
{
    int previous, count, old, next, mapped;

    previous = ((PageMap *)g_map_overlay_state)->page;
    if (*(PageMenu **)(((PageRoot *)g_pause_menu_state)->owner + 0xE8) != menu) {
        if (((PageMap *)g_map_overlay_state)->page < 28)
            menu->selection[((PageMap *)g_map_overlay_state)->page] = -1;
        return 0;
    }
    if ((((PagePad *)g_pad_state)->buttons & 0xD00) && !((PageRoot *)g_pause_menu_state)->lock && ((PageRoot *)g_pause_menu_state)->owner != g_level_page_root)
        return 1;

    /* Next and previous available page. */
    if (((PagePad *)g_pad_state)->buttons & 8) {
        for (next = ((PageMap *)g_map_overlay_state)->page + 1; next < 28; next++) {
            if (g_map_visited_flags[next] || g_current_map_index == next) {
                if (map_find_table_index(next) < 0)
                    return 0;
                map_set_current_and_refresh(next);
                break;
            }
        }
    }
    if (((PagePad *)g_pad_state)->buttons & 4) {
        for (next = ((PageMap *)g_map_overlay_state)->page - 1; next >= 0; next--) {
            if (g_map_visited_flags[next] || g_current_map_index == next) {
                if (map_find_table_index(next) < 0)
                    return 0;
                map_set_current_and_refresh(next);
                break;
            }
        }
    }
    if (((PageMap *)g_map_overlay_state)->page != previous) {
        snd_play_from_global_bank(3, 0, 0);
        menu_update_entry_states();
    }

    /* Rows of the page, written to the scratchpad. */
    count = menu_list_active_entries((int *)0x70000000, 0, (int *)0x70000100, 1);
    menu->count = count;
    if (count) {
        u32 buttons = ((PagePad *)g_pad_state)->buttons;
        int *selections = menu->selection;
        {
            int *entry = &selections[((PageMap *)g_map_overlay_state)->page];
            old = *entry;
            if (buttons & 0x1000)
                *entry = (old + count - 1) % count;
        }
        if (buttons & 0x4000) {
            int *entry = &selections[((PageMap *)g_map_overlay_state)->page];
            *entry = (*entry + 1) % menu->count;
        }
        {
            int *entry = &selections[((PageMap *)g_map_overlay_state)->page];
            if (*entry != old)
                snd_play_from_global_bank(3, 0, 0);
        }
        if ((buttons & 0x5000) || ((PageMap *)g_map_overlay_state)->page != previous) {
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
        if (((PageMap *)g_map_overlay_state)->page >= 0) {
            unsigned int word = (unsigned)mapped >> 2;
            int bit = 1 << (mapped & 0x1F);
            if (g_request_flag_table[word] & bit) {
                g_vram_frame_base = ((PageRoot *)g_pause_menu_state)->saved;
                menu_restore_saved_screen_image(0);
                ((PageRoot *)g_pause_menu_state)->saved_mode = g_loader_state_word;
                ((PageRoot *)g_pause_menu_state)->saved_owner = ((PageRoot *)g_pause_menu_state)->owner;
                ((PageRoot *)g_pause_menu_state)->page = ((PageMap *)g_map_overlay_state)->page;
                ((PageRoot *)g_pause_menu_state)->saved_current = ((PageRoot *)g_pause_menu_state)->field8;
                g_loader_state_word = 2;
                req_push_queue(g_loader_movie, mapped);
                req_launch_queued(g_loader_movie);
                return 1;
            }
        }
    }
    return 0;
}
