#include "include_asm.h"
#include "names.h"

void func_0027C540_3(long);
void func_0027C660_3(void);
void module_l00_call_handler_17(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
unsigned long long level_l00_run_setup_return_zero_long_3_us2(void)
{
    func_0027C540_3(0);
    module_l00_call_handler_17();
    func_0027C660_3();
    return 0;
}

extern int g_menu_input_flags;
typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackStateL001FEC40;
extern CallbackStateL001FEC40 g_pause_input_state;
extern int module_l00_call_handler_with_arg_18(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
int pad_l00_update_input_callback_2_us2(void)
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
        module_l00_call_handler_with_arg_18(flags);
    return result;
}

extern void func_0027C540_4(long arg0);
extern void module_l00_call_handler_18(void);
extern void func_0027C660_4(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
unsigned long long level_l00_run_setup_return_zero_long_4_us2(void)
{
    func_0027C540_4(0);
    module_l00_call_handler_18();
    func_0027C660_4();
    return 0;
}

extern int module_l00_call_handler_with_arg_19(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
int pad_l00_update_input_callback_3_us2(void)
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
        module_l00_call_handler_with_arg_19(flags);
    return result;
}

extern void SetupGifPaging(int a);
extern void DoGifPaging(void);
extern void module_l00_call_handler_19(void);

/* Sets up GIF paging, runs one level module handler, finishes paging and returns zero. */
int level_l00_run_setup_return_zero_5_us2(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_19();
    DoGifPaging();
    return 0;
}

