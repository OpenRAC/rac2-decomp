#include "include_asm.h"
#include "names.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
extern char *D_001A8CFC;
extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern int func_PAL_L00_0030F998(int);
extern char *func_PAL_00344418(void *);
extern void func_PAL_002D6A70(int);
extern int ref_PAL_L00_00350F30_00(int);

int func_PAL_L00_00350F30(void)
{
    struct { short reserved; unsigned short key; int value; } message;
    CallbackMenuState *state = &g_pad_state;
    int flags = state->flags;
    int result = 0;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        int status;
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
    finish:
        return status;
    }
    if (flags & 0x900) {
        result = 1;
    } else {
        ref_PAL_L00_00350F30_00(flags);
        if ((state->flags & 0x40) && D_001A8CFC != 0) {
            char *data = func_PAL_00344418(D_001A8CFC + 0x3E810);
            message.key = *(unsigned short *)(data + 8);
            message.value = *(int *)(data + 0xC);
            func_PAL_002D6A70((int)&message);
        }
    }
    return result;
}
