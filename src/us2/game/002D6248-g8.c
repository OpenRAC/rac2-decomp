#include "include_asm.h"
#include "names.h"
extern int g_save_menu_flags;
extern int g_save_menu_screen;
extern int g_pad_state[];
extern char g_pause_menu_state[];
extern char *ref_L00_002D55E0_00 __attribute__((sda));
extern int func_0029CAE0(int);
extern int func_00341E58(char *);
extern void menu_start_action(int);

/* Reads the buttons on a menu page: cancel goes back, other keys close it, and confirm sends the chosen entry to the menu request handler. (USA v2.00) */
int menu_page_handle_input_close_us2(void)
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
        func_0029CAE0(flags);
        if ((state[0x1c4 / 4] & 0x40) && ref_L00_002D55E0_00) {
            char *entry = (char *)func_00341E58(ref_L00_002D55E0_00 + 0x3E9C8);
            struct { short unused; short id; int value; } request;
            request.id = *(unsigned short *)(entry + 8);
            request.value = *(int *)(entry + 12);
            if ((g_save_menu_screen == 6 || g_save_menu_screen == 13) && request.id == 5) {
                g_save_menu_screen = 12;
                g_save_menu_flags &= ~2;
            }
            menu_start_action((int)&request);
        }
    }
    return result;
}
