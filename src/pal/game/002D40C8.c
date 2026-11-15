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
extern int D_00138344;
extern int D_00138344;
extern void func_PAL_0029D1D8(int);

int func_PAL_002D40C8(void) {
    int result = 0;
    int flags = D_00138344;
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
        func_PAL_0029D1D8(flags);
    return result;
}


#include "common.h"
extern void SetupGifPaging(long);
extern void func_PAL_0029D218(void);
extern void DoGifPaging(void);

int func_PAL_002D4150(void)
{
  SetupGifPaging(0);
  func_PAL_0029D218();
  DoGifPaging();
  return 0;
}

