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
extern int func_PAL_L00_0030F768(int);
extern void ref_PAL_L00_0034EC80_00(int);

int func_PAL_L00_0034EC80(void) {
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

int func_PAL_L00_0034ED08(void)
{
  SetupGifPaging(0);
  level_l00_call_module_handler_pal();
  DoGifPaging();
  return 0;
}

