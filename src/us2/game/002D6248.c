#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(long);
extern void DoGifPaging(void);
void SetupGifPaging(long);
void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);
extern void func_0029CB20(void);

/* Draws a second kind of menu page between the start and end of screen drawing. */
int menu_page_draw_second_us2(void) {
    SetupGifPaging(0);
    func_0029CB20();
    DoGifPaging();
    return 0;
}

extern char *g_resident_data_base[] __attribute__((sda));
extern void menu_set_value(char *, int);
extern void list_menu_set_records(char *, char *);
extern char g_list_menu_records_first[];

/* Sets up the text of a menu page when the menu data is loaded. */
int menu_page_text_init_first_us2(void)
{
    if (g_resident_data_base[0] != 0) {
        menu_set_value(g_resident_data_base[0] + 0x3E9C8, 1);
        list_menu_set_records(g_resident_data_base[0] + 0x3E9C8, g_list_menu_records_first);
    }
    return 0;
}

extern int g_pad_state[];
extern char g_pause_menu_state[];
extern int func_0029CA70(int);
extern int list_menu_get_selected_record(unsigned char *);
extern void menu_start_action(int);

/* Reads the buttons on a menu page: cancel goes back, other keys close it, and confirm sends the chosen entry to the menu request handler. */
int menu_page_handle_input_confirm_us2(void)
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
        func_0029CA70(flags);
        if ((state[0x1C4 / 4] & 0x40) && g_resident_data_base[0]) {
            char *entry = (char *)list_menu_get_selected_record((unsigned char *)(g_resident_data_base[0] + 0x3E760));
            struct { short unused; unsigned short id; int value; } request;
            request.id = *(unsigned short *)(entry + 8);
            request.value = *(int *)(entry + 12);
            menu_start_action((int)&request);
        }
    }
    return result;
}

