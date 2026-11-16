#include "include_asm.h"

#include "common.h"
extern int g_menu_input_flags;
extern int func_PAL_0029CB00(int);
extern unsigned int stub_empty_26(void);
extern unsigned int stub_empty_26(void);
extern unsigned int stub_empty_26(void);
extern unsigned int stub_empty_28(void);
extern unsigned int stub_empty_28(void);
extern unsigned int stub_empty_29(void);
extern int menu_handle_step_simple(int);
extern int menu_handle_mode_action(int);
extern int menu_run_action_by_index(int);
extern int func_PAL_002CC7B8(int);
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern unsigned int stub_empty_24(void);
extern unsigned int stub_empty_25(void);
extern unsigned int stub_empty_27(void);

int menu_handle_button_input_pal(void)
{
    unsigned int flags = g_menu_input_flags;
    int res = 0;

    if (flags & 0x910) {
        res = 1;
    } else if (flags & 0x40) {
        res = func_PAL_0029CB00(flags);
        if (stub_empty_24() && stub_empty_25()) {
            res = func_PAL_002CC7B8(res);
        } else if (stub_empty_27()) {
            res = menu_handle_mode_action(res);
        } else if (stub_empty_26()) {
            res = func_PAL_002CC8C8(res);
        } else if (stub_empty_29() == 0x31) {
            res = menu_handle_step_simple(res);
        } else if (stub_empty_28()) {
            res = menu_handle_step_simple(res);
        } else if (stub_empty_29() == 0x1C) {
            res = menu_handle_step_simple(res);
        } else {
            res = menu_run_action_by_index(res);
        }
    } else {
        func_PAL_0029CB00(flags);
    }

    if (res) {
        snd_play_from_global_bank(0x12, 0, 0);
    }
    return res;
}


extern void SetupGifPaging(long);
extern void func_0029C138(void);
extern void DoGifPaging(void);
void SetupGifPaging(long);
void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void SetupGifPaging(long param_1);

int menu_run_setup_calls_pal(void)
{
  SetupGifPaging(0);
  func_0029C138();
  DoGifPaging();
  return 0;
}

