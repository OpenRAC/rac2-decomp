#include "include_asm.h"
#include "names.h"

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;
extern CallbackState g_pause_menu_state;
extern int g_menu_input_flags;
extern int g_menu_input_flags;
extern int module_l00_call_handler_with_arg_20_pal(int);
extern void ref_PAL_L00_0034EC80_00(int);

/* Handles menu input: reports the pause-menu value when the pending bit is set, otherwise reports 1 for a confirm or cancel button, or passes the flags on to a level module handler. */
int level_l00_menu_input_update_pal(void) {
    int result = 0;
    int flags = g_menu_input_flags;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
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
        ref_PAL_L00_0034EC80_00(flags);
    return result;
}


#include "common.h"
extern void SetupGifPaging(long);
extern void level_l00_call_module_handler_pal(void);
extern void DoGifPaging(void);

/* Brackets a level module handler call with GIF paging setup and flush, then returns zero. */
int level_l00_paging_call_handler_pal(void)
{
  SetupGifPaging(0);
  level_l00_call_module_handler_pal();
  DoGifPaging();
  return 0;
}

