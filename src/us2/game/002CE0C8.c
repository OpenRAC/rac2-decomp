#include "include_asm.h"

#include "common.h"
extern int g_menu_input_flags;
extern int func_US2_0029CFA0(int);
extern unsigned int stub_empty_29(void);
extern unsigned int stub_empty_29(void);
extern unsigned int stub_empty_29(void);
extern unsigned int stub_empty_30(void);
extern unsigned int stub_empty_29(void);
extern unsigned int stub_empty_30(void);
extern int menu_handle_step_simple(int);
extern int menu_handle_mode_action(int);
extern int menu_run_action_by_index(int);
extern int func_US2_002CC908(int);
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern unsigned int stub_empty_24(void);
extern unsigned int stub_empty_25(void);
extern unsigned int stub_empty_28(void);
extern unsigned int stub_empty_27(void);

int menu_handle_button_input_us2(void)
{
    unsigned int flags = g_menu_input_flags;
    int res = 0;

    if (flags & 0x910) {
        res = 1;
    } else if (flags & 0x40) {
        res = func_US2_0029CFA0(flags);
        if (stub_empty_24() && stub_empty_25()) {
            res = func_US2_002CC908(res);
        } else if (stub_empty_28()) {
            res = menu_handle_mode_action(res);
        } else if (stub_empty_27()) {
            res = menu_handle_step_with_reset(res);
        } else if (stub_empty_30() == 0x31) {
            res = menu_handle_step_simple(res);
        } else if (stub_empty_29()) {
            res = menu_handle_step_simple(res);
        } else if (stub_empty_30() == 0x1C) {
            res = menu_handle_step_simple(res);
        } else {
            res = menu_run_action_by_index(res);
        }
    } else {
        func_US2_0029CFA0(flags);
    }

    if (res) {
        snd_play_from_global_bank(0x12, 0, 0);
    }
    return res;
}

