#include "include_asm.h"
#include "names.h"

extern int g_pad_state[];
extern char g_pause_menu_state[];
extern int g_resident_data_base __attribute__((sda));
extern int func_0029C920(int);
extern int list_page_get_selected_record(int);
extern void menu_start_action(int);

int menu_page_update_with_preview_us2(void)
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
        if ((state[0x1C4 / 4] & 0x40) && g_resident_data_base) {
            char *entry = (char *)list_page_get_selected_record(g_resident_data_base + 0x3F3F0);
            struct { short unused; unsigned short id; int value; } request;
            request.id = *(unsigned short *)(entry + 8);
            request.value = *(int *)(entry + 12);
            menu_start_action((int)&request);
        }
    }
    return result;
}

extern void SetupGifPaging(long);
extern void DoGifPaging(void);
void SetupGifPaging(long);
void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);
extern void func_0029C960(void);

/* Candidate function: FUN_002d3390 */
unsigned long long menu_page_draw_9_us2(void)
{
    SetupGifPaging(0);
    func_0029C960();
    DoGifPaging();
    return 0;
}

extern void func_0029C5A0(void);

int menu_page_draw_10_us2(void) {
    SetupGifPaging(0);
    func_0029C5A0();
    DoGifPaging();
    return 0;
}

