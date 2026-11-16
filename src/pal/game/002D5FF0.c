#include "include_asm.h"
#include "names.h"

/* func_PAL_002D6058, the PAL copy of func_002D5480: the same C, where the object offset 0x3BE08
   becomes 0x3C210 and the callees are PAL's own. */
extern char *g_resident_data_base[] __attribute__((sda));
extern void menu_clear_counter(void);
extern void tab_menu_set_tables_pal(char *, char *, char *, char *);
extern void func_PAL_00343690(char *, int);
extern char g_extras_tab_table_a[], g_extras_tab_table_b[], g_extras_tab_table_c[];

int func_PAL_002D6058(void)
{
    menu_clear_counter();
    if (g_resident_data_base[0] != 0) {
        tab_menu_set_tables_pal(g_resident_data_base[0] + 0x3C210, g_extras_tab_table_a, g_extras_tab_table_b, g_extras_tab_table_c);
        func_PAL_00343690(g_resident_data_base[0] + 0x3C210, 1);
    }
    return 0;
}

/* func_PAL_002D60C8, the PAL copy of func_L00_0034E950: the same C, calling PAL's func_PAL_0029D8A0. */
extern int g_menu_input_flags;
extern int func_PAL_0029D8A0(int);

int func_PAL_002D60C8(void)
{
    func_PAL_0029D8A0(g_menu_input_flags);
    return 0;
}

extern int g_menu_input_flags;
extern int func_0029CF08(int);
extern int g_menu_input_flags;
extern int func_0029CF08(int);

int menu_handle_buttons_pal(void) {
    func_0029CF08(g_menu_input_flags);
    return 0;
}

#include "common.h"
extern void func_PAL_0029D870(void);

int func_PAL_002D6118(void)
{
  SetupGifPaging(0);
  func_PAL_0029D870();
  DoGifPaging();
  return 0;
}





extern void func_PAL_0029D4B8(void);

int func_PAL_002D62F0(void)
{
  SetupGifPaging(0);
  func_PAL_0029D4B8();
  DoGifPaging();
  return 0;
}


extern char *g_resident_data_base[] __attribute__((sda));
extern void menu_set_value(char *, int);
extern void list_menu_set_records_pal(char *, char *);
extern char g_list_menu_records_first[];

int func_PAL_002D6320(void)
{
    if (g_resident_data_base[0] != 0) {
        menu_set_value(g_resident_data_base[0] + 0x3EA78, 1);
        list_menu_set_records_pal(g_resident_data_base[0] + 0x3EA78, g_list_menu_records_first);
    }
    return 0;
}



extern void func_PAL_0029D448(void);

int func_PAL_002D6448(void)
{
  SetupGifPaging(0);
  func_PAL_0029D448();
  DoGifPaging();
  return 0;
}


extern void list_menu_set_enabled(char *, int);
extern void list_menu_set_record_table_pal(char *, char *);

extern char g_ui_object_data[];

int func_PAL_002D6478(void)
{
    if (g_resident_data_base[0] != 0) {
        list_menu_set_enabled(g_resident_data_base[0] + 0x3E810, 1);
        list_menu_set_record_table_pal(g_resident_data_base[0] + 0x3E810, g_ui_object_data);
    }
    return 0;
}





extern void SetupGifPaging(long);
extern void DoGifPaging(void);
void SetupGifPaging(long);
void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);
extern void func_0029CED8(void);

long long menu_page_draw_gif_pal(void)
{
    SetupGifPaging(0);
    func_0029CED8();
    DoGifPaging();
    return 0;
}

extern int g_menu_choice;

int func_PAL_002D6528(void) {
    g_menu_choice = -1;
    return 0;
}



extern char g_pause_menu_state[];
extern int g_current_map_index __attribute__((sda));
extern volatile unsigned char g_mission_active_flag __attribute__((sda));
extern int g_selected_map_index;
extern int g_map_overlay_state[];
extern void FadeToBlack(int);
extern void menu_set_pause_scale_inverse(float);
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern int stub_empty_25(void);
extern int stub_empty_25(void);
extern void data_set_small_value_and_refresh(int, int);
extern int request_begin_slot(int, int, int, int, int);
extern int func_PAL_0029CDA8(int);
extern int stub_empty_24(void);

int func_PAL_002D6548(void)
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
            } else if (stub_empty_24() && stub_empty_25()) {
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
        func_PAL_0029CDA8(flags);
    }
finish:
    return result;
}


extern void func_0029CB20(void);

int menu_page_draw_second_pal(void) {
    SetupGifPaging(0);
    func_0029CB20();
    DoGifPaging();
    return 0;
}

extern int func_PAL_002D6730(int, int, int *);

int func_PAL_002D6710(int first, int second) {
    int result[4];
    result[0] = 0;
    return func_PAL_002D6730(first, second, result);
}


extern int menu_process_request(int, int, int *);
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
int func_PAL_002D6730(int type, int value, int *result)
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


int func_PAL_002D6A10(char *object, int arg, int *result)
{
    typedef struct { int first, value, third; } Func002D5E38Row;
    Func002D5E38Row *rows = *(Func002D5E38Row **)(object + 0x34);
    int index = *(int *)(object + 0x40);
    return func_PAL_002D6730(arg, rows[index].value, result);
}


void func_PAL_002D6A48(char *object, int *result) {
    func_PAL_002D6730(*(short *)(object + 2), *(int *)(object + 4), result);
}










