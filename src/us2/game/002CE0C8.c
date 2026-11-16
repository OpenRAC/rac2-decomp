#include "include_asm.h"

#include "common.h"
extern int g_menu_input_flags;
extern int resident_menu_update_us2(int);
extern unsigned int stub_empty_29(void);
extern unsigned int stub_empty_29(void);
extern unsigned int stub_empty_29(void);
extern unsigned int stub_empty_30(void);
extern unsigned int stub_empty_29(void);
extern unsigned int stub_empty_30(void);
extern int menu_handle_step_simple(int);
extern int menu_handle_mode_action(int);
extern int menu_run_action_by_index(int);
extern int menu_handle_command_us2(int);
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern unsigned int stub_empty_24(void);
extern unsigned int stub_empty_25(void);
extern unsigned int stub_empty_28(void);
extern unsigned int stub_empty_27(void);

/* Handles menu button input and picks the right handler for the current screen. Plays a sound if input was used. */
int menu_handle_button_input_us2(void)
{
    unsigned int flags = g_menu_input_flags;
    int result = 0;

    if (flags & 0x910) {
        result = 1;
    } else if (flags & 0x40) {
        result = resident_menu_update_us2(flags);
        if (stub_empty_24() && stub_empty_25()) {
            result = menu_handle_command_us2(result);
        } else if (stub_empty_28()) {
            result = menu_handle_mode_action(result);
        } else if (stub_empty_27()) {
            result = menu_handle_step_with_reset(result);
        } else if (stub_empty_30() == 0x31) {
            result = menu_handle_step_simple(result);
        } else if (stub_empty_29()) {
            result = menu_handle_step_simple(result);
        } else if (stub_empty_30() == 0x1C) {
            result = menu_handle_step_simple(result);
        } else {
            result = menu_run_action_by_index(result);
        }
    } else {
        resident_menu_update_us2(flags);
    }

    if (result) {
        snd_play_from_global_bank(0x12, 0, 0);
    }
    return result;
}

