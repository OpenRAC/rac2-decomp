#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base;
extern int ref_L00_002D5570_00 __attribute__((sda));
extern int ref_L00_002D5570_01 __attribute__((sda));
extern void popup_init_texts_hidden_pal(char *);
extern void popup_init_texts_shown_pal(char *);

/* Sets up the popup texts as hidden or shown, depending on which page asked (PAL). */
int menu_start_key_action_pal(char *page)
{
    if (g_resident_data_base != 0) {
        if (page == (char *)&ref_L00_002D5570_00)
            popup_init_texts_hidden_pal(g_resident_data_base + 0x3CF50);
        else if (page == (char *)&ref_L00_002D5570_01)
            popup_init_texts_shown_pal(g_resident_data_base + 0x3CF50);
    }
    return 0;
}

extern int g_save_menu_flags;
extern int g_save_menu_screen;
extern int g_pad_state[];
extern char g_pause_menu_state[];
extern char *ref_L00_002D55E0_00 __attribute__((sda));
extern int resident_list_menu_set_selection(int);
extern int func_PAL_00343EC0(char *);
extern void menu_start_action_pal(int);

/* Handles input for the save menu page: confirms or closes, passes buttons on, and starts the selected entry action on X (PAL). */
int menu_page_handle_input_close_pal(void)
{
    int result = 0;
    int *state = g_pad_state;
    int flags;
    g_save_menu_flags = (g_save_menu_flags | 2) & ~4;
    flags = state[0x1c4 / 4];
    if (flags & 0x10) {
        char *root = g_pause_menu_state;
        int value = *(int *)(*(char **)(root + 0x14) + 0xe0);
        int status;
        if (value != 0) {
            *(int *)(root + 0x18) = value;
        } else {
            switch (*(int *)(root + 0x134)) {
            case 0: status = -1; goto finish;
            default: break;
            }
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900) result = 1;
    else {
        resident_list_menu_set_selection(flags);
        if ((state[0x1c4 / 4] & 0x40) && ref_L00_002D55E0_00) {
            char *entry = (char *)func_PAL_00343EC0(ref_L00_002D55E0_00 + 0x3EA78);
            struct { short unused; short id; int value; } request;
            request.id = *(unsigned short *)(entry + 8);
            request.value = *(int *)(entry + 12);
            if ((g_save_menu_screen == 6 || g_save_menu_screen == 13) && request.id == 5) {
                g_save_menu_screen = 12;
                g_save_menu_flags &= ~2;
            }
            menu_start_action_pal((int)&request);
        }
    }
    return result;
}

/* func_PAL_002D5FF0, the PAL copy of func_002D53F0: a centred text draw at y = 329 less a word
   reached through $gp (-G8), with text id 0xB60 where USA draws 0x2D4F at a scaled y. */
extern int g_ui_y_offset __attribute__((sda));
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern void menu_draw_tab_menu_2_pal(void);
extern char *GetLocalizedString(int);
extern void text_draw_right_aligned_small(int, int, unsigned long long, unsigned char *, int);

int menu_draw_centered_text_pal(void)
{
    int y;

    SetupGifPaging(0);
    menu_draw_tab_menu_2_pal();
    y = 329 - g_ui_y_offset;
    text_draw_right_aligned_small(0x1C7, y, 0x80F0F0F0ULL, (unsigned char *)GetLocalizedString(0xB60), -1);
    DoGifPaging();
    return 0;
}
