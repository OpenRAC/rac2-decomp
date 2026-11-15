#include "include_asm.h"
#include "names.h"
extern int g_pad_state[];
extern char g_pause_menu_state[];
extern int D_001A8CFC __attribute__((sda));
extern int func_0029C920(int);
extern int list_page_get_selected_record(int);
extern void menu_start_action(int);

int func_PAL_002D4238(void)
{
    int result = 0;
    int *state = g_pad_state;
    int flags = state[0x1C4 / 4];
    if (flags & 0x10) {
        char *root = g_pause_menu_state;
        int value = *(int *)(*(char **)(root + 0x14) + 0xE0);
        int status;
        if (value != 0) {
            *(int *)(root + 0x18) = value;
        } else {
            switch (*(int *)(root + 0x134)) {
            case 0:
                status = -1;
                goto finish;
            default:
                break;
            }
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900)
        result = 1;
    else {
        func_0029C920(flags);
        if ((state[0x1C4 / 4] & 0x40) && D_001A8CFC) {
            char *entry = (char *)list_page_get_selected_record(D_001A8CFC + 0x3F4A0);
            struct { short unused; unsigned short id; int value; } request;
            request.id = *(unsigned short *)(entry + 8);
            request.value = *(int *)(entry + 12);
            menu_start_action((int)&request);
        }
    }
    return result;
}
