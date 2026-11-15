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

extern PagePreview D_0025A6E0;
extern u8 D_0025E680[];
extern u8 D_0025A190[];
extern u8 D_001A7BC8[] MACRO_ADDR;  /* page available, one byte per page */
extern int D_00139768[];            /* flag bits: bit (n & 31) of word n >> 2 */
extern int D_0025A620[];
extern int D_001A7478;
extern int g_current_map_index __attribute__((sda));
extern int D_001A72D4 __attribute__((sda));
extern char D_001BAD40[];

extern int map_find_table_index(int);
extern void map_set_current_and_refresh(int);
extern int snd_play_from_global_bank(int, int, void *);
extern void menu_update_entry_states(void);
extern int func_US2_0029E960(int *, int *, int *, int);
extern void menu_restore_saved_screen_image(int);
extern int req_push_queue(char *, int);
extern int req_launch_queued(char *);

int func_US2_002D8320(PageMenu *menu)
{
    int previous, count, old, next, mapped;
    PageMap *map;

    previous = ((PageMap *)g_map_overlay_state)->page;
    if (*(PageMenu **)(((PageRoot *)g_pause_menu_state)->owner + 0xE8) != menu) {
        if (((PageMap *)g_map_overlay_state)->page < 28)
            menu->selection[((PageMap *)g_map_overlay_state)->page] = -1;
        return 0;
    }
    if ((((PagePad *)g_pad_state)->buttons & 0xD00) && !((PageRoot *)g_pause_menu_state)->lock && ((PageRoot *)g_pause_menu_state)->owner != D_0025E680)
        return 1;

    /* Next and previous available page. */
    if (((PagePad *)g_pad_state)->buttons & 8) {
        for (next = ((PageMap *)g_map_overlay_state)->page + 1; next < 28; next++) {
            if (D_001A7BC8[next] || g_current_map_index == next) {
                if (map_find_table_index(next) < 0)
                    return 0;
                map_set_current_and_refresh(next);
                break;
            }
        }
    }
    if (((PagePad *)g_pad_state)->buttons & 4) {
        for (next = ((PageMap *)g_map_overlay_state)->page - 1; next >= 0; next--) {
            if (D_001A7BC8[next] || g_current_map_index == next) {
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
    count = func_US2_0029E960((int *)0x70000000, 0, (int *)0x70000100, 1);
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
            D_0025A6E0.timer = -576;
            entry = &selections[((PageMap *)g_map_overlay_state)->page];
            D_0025A6E0.item = ((int *)0x70000000)[*entry];
            *D_0025A620 = ((int *)0x70000100)[*entry];
        }
    } else {
        D_0025A6E0.item = 0;
        *D_0025A620 = -1;
    }

    /* Back. */
    if ((((PagePad *)g_pad_state)->buttons & 0x10) && ((PageRoot *)g_pause_menu_state)->owner != D_0025E680) {
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
            if (D_00139768[word] & bit) {
                PageRoot *root = ((PageRoot *)g_pause_menu_state);
                if (root->owner != D_0025E680 && root->owner != D_0025A190)
                    return 0;
                D_001A72D4 = root->saved;
                menu_restore_saved_screen_image(0);
                root->savedMode = D_001A7478;
                root->savedOwner = root->owner;
                root->page = map->page;
                root->savedCurrent = root->field8;
                D_001A7478 = 2;
                req_push_queue(D_001BAD40, mapped);
                req_launch_queued(D_001BAD40);
                return 1;
            }
        }
    }
    return 0;
}
