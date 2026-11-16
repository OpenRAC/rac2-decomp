#include "include_asm.h"
#include "names.h"

/*
 * Disassembled at 0x002cd220
 * Signature: int FUN_002cd220(void)
 * Behavior:
 *   - Saves RA on stack
 *   - Calls func_0027C540(0)
 *   - Calls func_0029C138()
 *   - Calls func_0027C660()
 *   - Restores RA from stack
 *   - Returns 0
 */
extern void SetupGifPaging(long);

extern void DoGifPaging(void);

void SetupGifPaging(long);

void DoGifPaging(void);

/* 
 * Function: func_002D2EE0
 * 
 * Disassembly summary:
 * - Saves return address on stack
 * - Calls func_0027C540(0) (with zero argument)
 * - Calls func_0029C7A0()
 * - Calls func_0027C660()
 * - Restores return address
 * - Returns 0
 *
 * Notes:
 * - The function follows standard MIPS ABI prologue/epilogue.
 * - Delay slots are filled with NOP or argument setup as seen in disassembly.
 * - No local variables used.
 * - All external function addresses come from the assigned externals list.
 */

extern void SetupGifPaging(long arg0);

/* External functions declared with exact aliases from task.externals */
extern void SetupGifPaging(long param_1);

extern void func_0029CED8(void);

/* Draws a menu page between the start and end of screen drawing. */
long long menu_page_draw_gif(void)
{
    SetupGifPaging(0);
    func_0029CED8();
    DoGifPaging();
    return 0;
}

/* func_002D5570 is matched in 002D5540-g8.c (-G8 small data). */

/* Does nothing and returns zero. */
int menu_page_noop_first(void) {
    return 0;
}

/* func_002D55E0 uses small data in 002D5540-g8.c. */

extern void func_0029CB20(void);

/* Draws a second kind of menu page between the start and end of screen drawing. */
int menu_page_draw_second(void) {
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
int menu_page_text_init_first(void)
{
    if (g_resident_data_base[0] != 0) {
        menu_set_value(g_resident_data_base[0] + 0x3E430, 1);
        list_menu_set_records(g_resident_data_base[0] + 0x3E430, g_list_menu_records_first);
    }
    return 0;
}

extern int g_pad_state[];
extern char g_pause_menu_state[];
extern int func_0029CA70(int);
extern int list_menu_get_selected_record(unsigned char *);
extern void menu_start_action(int);

/* Reads the buttons on a menu page: cancel goes back, other keys close it, and confirm sends the chosen entry to the menu request handler. */
int menu_page_handle_input_confirm(void)
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
            char *entry = (char *)list_menu_get_selected_record((unsigned char *)(g_resident_data_base[0] + 0x3E1D8));
            struct { short unused; unsigned short id; int value; } request;
            request.id = *(unsigned short *)(entry + 8);
            request.value = *(int *)(entry + 12);
            menu_start_action((int)&request);
        }
    }
    return result;
}


extern void func_0029CAB0(void);

/* Draws a third kind of menu page between the start and end of screen drawing. */
int menu_page_draw_third(void) {
    SetupGifPaging(0);
    func_0029CAB0();
    DoGifPaging();
    return 0;
}

extern void list_menu_set_enabled(char *, int);
extern void list_menu_set_record_table(char *, char *);
extern char g_list_menu_record_table_second[];

/* Sets up the text of another menu page when the menu data is loaded. */
int menu_page_text_init_second(void)
{
    if (g_resident_data_base[0] != 0) {
        list_menu_set_enabled(g_resident_data_base[0] + 0x3E1D8, 1);
        list_menu_set_record_table(g_resident_data_base[0] + 0x3E1D8, g_list_menu_record_table_second);
    }
    return 0;
}

extern int g_menu_input_flags;
extern int func_0029C3A0(int);

/* Draws a menu page using the current button state. */
int menu_page_draw_with_pad_state(void) {
    func_0029C3A0(g_menu_input_flags);
    return 0;
}

extern void func_0029C370(void);

/* Draws a fourth kind of menu page between the start and end of screen drawing. */
int menu_page_draw_fourth(void) {
    SetupGifPaging(0);
    func_0029C370();
    DoGifPaging();
    return 0;
}

extern int g_menu_choice;

/* Clears the saved menu choice to "none". */
int menu_clear_choice(void) {
    g_menu_choice = -1;
    return 0;
}

/* Does nothing and returns zero. */
int menu_page_noop_second(void) {
    return 0;
}

extern int g_current_map_index __attribute__((sda));
extern volatile unsigned char g_mission_active_flag __attribute__((sda));
extern int g_selected_map_index;
extern int g_map_overlay_state[];
extern void FadeToBlack(int);
extern void menu_set_pause_scale_inverse(float);
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern int stub_empty_23(void);
extern int stub_empty_24(void);
extern void data_set_small_value_and_refresh(int, int);
extern int request_begin_slot(int, int, int, int, int);
extern int func_0029C410(int);

/* Reads the buttons on the page-select menu: cancel closes, confirm picks the highlighted page and plays a sound or starts the change. */
int menu_page_select_handle_input(void)
{
    int result = 0;
    int flags = g_menu_input_flags;
    if (flags & 0x10) {
        char *root;
        int value;
        FadeToBlack(4);
        menu_set_pause_scale_inverse(4.0f);
        root = g_pause_menu_state;
        value = *(int *)(*(char **)(root + 0x14) + 0xE0);
        if (value != 0) {
            *(int *)(root + 0x18) = value;
        } else {
            switch (*(int *)(root + 0x134)) {
            case 0:
                result = -1;
                goto finish;
            default:
                break;
            }
        }
        result = 0;
    } else if (flags & 0xD00) {
        result = 1;
        g_selected_map_index = g_current_map_index;
    } else if (flags & 0x40) {
        int *base = g_map_overlay_state;
        if (g_current_map_index != base[0x230 / 4]) {
            result = 1;
            snd_play_from_global_bank(4, 0, 0);
            if (base[0x230 / 4] != 0 && g_mission_active_flag == 0 && base[0x230 / 4] == 2) {
                request_begin_slot(6, 2, 1, 0x19, 0);
            } else if (stub_empty_23() && stub_empty_24()) {
                data_set_small_value_and_refresh(g_map_overlay_state[0x230 / 4], 1);
            } else {
                request_begin_slot(6, 2, 1, g_map_overlay_state[0x230 / 4], 0);
            }
        } else {
            result = 1;
            snd_play_from_global_bank(4, 0, 0);
            FadeToBlack(4);
        }
    } else {
        func_0029C410(flags);
    }
finish:
    return result;
}

extern void func_0029C3E0(void);

/* Draws a fifth kind of menu page between the start and end of screen drawing. */
int menu_page_draw_fifth(void) {
    SetupGifPaging(0);
    func_0029C3E0();
    DoGifPaging();
    return 0;
}

extern int menu_process_request(int, int, int *);

/* Sends a menu request and ignores the result. */
int menu_send_request(int first, int second) {
    int result[4];
    result[0] = 0;
    return menu_process_request(first, second, result);
}

typedef struct {
    char pad0[8];
    int f08;
    char pad1[8];
    int f14;
    int f18;
    int f1C;
    char pad2[0xF4 - 0x20];
    int fF4;
    int fF8;
    int fFC;
    int f100;
    int f104;
} Func002D5B58Root;
extern int g_save_menu_flags __attribute__((sda));
extern char g_language __attribute__((sda));
extern int g_map_targets[];
extern int g_message_panel_flags;
extern void *D_0026CD60[];
extern void menu_clear_confirm_pending(void);
extern void settings_store_four(int, int, int, int);
extern void menu_set_size_limits(int, int);
extern void snd_play_menu_sound_if_enabled(int, int);

/* Handles a request by type (0 and 1 do nothing): the others set a state code and its parameters in
   the block at D_001F2840, change the flags of D_001A7424 or call the helpers. Types 6 to 11 store 0
   through `result` and return 1 (type 7 falls through into type 8). The dispatch reads the table
   retail already has at D_0026CD60 (fourteen code addresses, one per type; types 0 and 1 go to the
   common return); `cases` only keeps the labels alive. */
int menu_process_request(int type, int value, int *result)
{
    static void *cases[12] = {&&L3, &&L4, &&L5, &&L6, &&L7, &&L8, &&L10, &&L11, &&L9, &&L2, &&L12, &&L13};
    int ret = 0;

    if ((unsigned)type >= 14)
        goto done;
    goto *D_0026CD60[type];
L3:
    ((Func002D5B58Root *)g_pause_menu_state)->f18 = value;
    goto done;
L4:
    snd_play_from_global_bank(4, 0, 0);
    menu_clear_confirm_pending();
    g_save_menu_flags = (g_save_menu_flags | 2) & ~4;
    g_message_panel_flags = 0;
    request_begin_slot(4, 1, 1, value, 0);
    goto done;
L5:
    snd_play_from_global_bank(4, 0, 0);
    g_save_menu_flags = (g_save_menu_flags | 4) & ~2;
    request_begin_slot(4, 1, 1, value, 0);
    g_message_panel_flags = 1;
    goto done;
L6: {
    Func002D5B58Root *root;
    int index = value >> 16;
    if (index != 0) {
        Func002D5B58Root *first = (Func002D5B58Root *)g_pause_menu_state;
        first->fFC = g_map_targets[index];
    }
    root = (Func002D5B58Root *)g_pause_menu_state;
    root->f100 = root->f14;
    root->f104 = root->f08;
    root->f1C = 5;
    root->fF4 = value & 0xFFFF;
    ret = 1;
    snd_play_menu_sound_if_enabled(0, 0x11);
    *result = 0;
    goto done;
}
L7: {
    Func002D5B58Root *root = (Func002D5B58Root *)g_pause_menu_state;
    root->fF4 = value;
    root->f100 = root->f14;
    root->f1C = 3;
    root->f104 = root->f08;
    snd_play_menu_sound_if_enabled(0, 0x11);
    *result = 0;
}
L8: {
    Func002D5B58Root *root = (Func002D5B58Root *)g_pause_menu_state;
    root->f100 = root->f14;
    root->f104 = root->f08;
    root->f1C = 4;
    root->fF4 = value;
    ret = 1;
    snd_play_menu_sound_if_enabled(0, 0x11);
    *result = 0;
    goto done;
}
L10: {
    Func002D5B58Root *root = (Func002D5B58Root *)g_pause_menu_state;
    root->f100 = root->f14;
    root->f104 = root->f08;
    root->f1C = 6;
    root->fF4 = value;
    ret = 1;
    snd_play_menu_sound_if_enabled(0, 0x11);
    *result = 0;
    goto done;
}
L11: {
    Func002D5B58Root *root = (Func002D5B58Root *)g_pause_menu_state;
    root->f100 = root->f14;
    root->f104 = root->f08;
    root->f1C = 7;
    ret = 1;
    snd_play_menu_sound_if_enabled(0, 0x11);
    *result = 0;
    goto done;
}
L9:
    g_language = value;
    ret = 1;
    *result = 0;
    goto done;
L2:
    snd_play_menu_sound_if_enabled(2, 0x11);
    goto done;
L12:
    snd_play_from_global_bank(4, 0, 0);
    settings_store_four(0, 0, 0, 0);
    menu_set_size_limits(0, 0);
    request_begin_slot(4, 1, 9, ((Func002D5B58Root *)g_pause_menu_state)->f14, 0);
    goto done;
L13:
    request_begin_slot(4, 1, 11, ((Func002D5B58Root *)g_pause_menu_state)->f14, 0);
done:
    return ret;
}

/* Runs the request for the currently highlighted row of a menu. */
int menu_process_selected_row_request(char *object, int arg, int *result)
{
    typedef struct { int first, value, third; } Func002D5E38Row;
    Func002D5E38Row *rows = *(Func002D5E38Row **)(object + 0x34);
    int index = *(int *)(object + 0x40);
    return menu_process_request(arg, rows[index].value, result);
}

/* Runs the request stored in one menu entry. */
int menu_process_entry_request(char *object, int *result) {
    return menu_process_request(*(short *)(object + 2), *(int *)(object + 4), result);
}
