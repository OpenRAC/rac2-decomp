#include "include_asm.h"
#include "names.h"

extern char g_pause_menu_state[];
extern int g_menu_input_flags;
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
extern int info_panel_update_call_us2(int);
extern int stub_empty_24(void);

extern int ref_US2_002D65D8_00(void);
extern int ref_US2_002D65D8_01(void);

/* Reads the buttons on the page-select menu: cancel closes, confirm picks the highlighted page and plays a sound or starts the change. */
int menu_page_select_handle_input_us2(void)
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
            } else if (ref_US2_002D65D8_00() && ref_US2_002D65D8_01()) {
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
        info_panel_update_call_us2(flags);
    }
finish:
    return result;
}



