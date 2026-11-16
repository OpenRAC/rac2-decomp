#include "include_asm.h"

#include "common.h"
extern int g_menu_input_flags;
extern int menu_update_choice_list_pal(int);
extern unsigned int stub_empty_26(void);
extern unsigned int stub_empty_26(void);
extern unsigned int stub_empty_26(void);
extern unsigned int stub_empty_28(void);
extern unsigned int stub_empty_28(void);
extern unsigned int stub_empty_29(void);
extern int menu_handle_step_simple(int);
extern int menu_handle_mode_action(int);
extern int menu_run_action_by_index(int);
extern int menu_handle_command_pal(int);
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern unsigned int stub_empty_24(void);
extern unsigned int stub_empty_25(void);
extern unsigned int stub_empty_27(void);

/* Reads the menu input flags and runs the handler for the current menu kind, playing a click when the input was handled (PAL). */
int menu_handle_button_input_pal(void)
{
    unsigned int flags = g_menu_input_flags;
    int result = 0;

    if (flags & 0x910) {
        result = 1;
    } else if (flags & 0x40) {
        result = menu_update_choice_list_pal(flags);
        if (stub_empty_24() && stub_empty_25()) {
            result = menu_handle_command_pal(result);
        } else if (stub_empty_27()) {
            result = menu_handle_mode_action(result);
        } else if (stub_empty_26()) {
            result = menu_handle_step_with_reset_pal(result);
        } else if (stub_empty_29() == 0x31) {
            result = menu_handle_step_simple(result);
        } else if (stub_empty_28()) {
            result = menu_handle_step_simple(result);
        } else if (stub_empty_29() == 0x1C) {
            result = menu_handle_step_simple(result);
        } else {
            result = menu_run_action_by_index(result);
        }
    } else {
        menu_update_choice_list_pal(flags);
    }

    if (result) {
        snd_play_from_global_bank(0x12, 0, 0);
    }
    return result;
}


extern void SetupGifPaging(long);
extern void func_0029C138(void);
extern void DoGifPaging(void);
void SetupGifPaging(long);
void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);

/* Runs the menu setup calls between SetupGifPaging and DoGifPaging (PAL). */
int menu_run_setup_calls_pal(void)
{
  SetupGifPaging(0);
  func_0029C138();
  DoGifPaging();
  return 0;
}

