#include "include_asm.h"
#include "names.h"

extern int g_menu_input_flags;
typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackStateL001FEC40;
extern CallbackStateL001FEC40 g_pause_input_state;
extern int level_l00_call_module_handler_with_arg_4(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
int pad_l00_update_input_callback_4_us2(void)
{
    int result = 0;
    int flags = g_menu_input_flags;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_input_state.source + 0xE0);
        if (value != 0)
            g_pause_input_state.value = value;
        else if (g_pause_input_state.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        level_l00_call_module_handler_with_arg_4(flags);
    return result;
}

extern void SetupGifPaging(int a);
extern void DoGifPaging(void);
extern void level_l00_call_module_handler_5(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
int level_l00_run_setup_return_zero_6_us2(void)
{
    SetupGifPaging(0);
    level_l00_call_module_handler_5();
    DoGifPaging();
    return 0;
}

