#include "include_asm.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
extern char *D_001A8CFC;
extern SelectionCallback D_001F2840;
extern CallbackMenuState D_00138180;
extern int func_PAL_0029D408(int);
extern char *func_PAL_00344418(void *);
extern void func_PAL_002D6A70(int);

int func_PAL_002D6378(void)
{
    struct { short reserved; unsigned short key; int value; } message;
    CallbackMenuState *state = &D_00138180;
    int flags = state->flags;
    int result = 0;
    if (flags & 0x10) {
        int value = *(int *)(D_001F2840.source + 0xE0);
        int status;
        if (value != 0)
            D_001F2840.value = value;
        else if (D_001F2840.fallback == 0) {
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
        func_PAL_0029D408(flags);
        if ((state->flags & 0x40) && D_001A8CFC != 0) {
            char *data = func_PAL_00344418(D_001A8CFC + 0x3E810);
            message.key = *(unsigned short *)(data + 8);
            message.value = *(int *)(data + 0xC);
            func_PAL_002D6A70((int)&message);
        }
    }
    return result;
}
