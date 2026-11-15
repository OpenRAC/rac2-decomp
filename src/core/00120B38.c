#include "common.h"

/* The value is taken through a named s64 local: writing `(int)*(s64 *)p`
   directly folds the load into a 32-bit `lw`, while the local keeps retail's
   `ld` plus the truncdisi2 pair (dsll32/dsra32). */
extern char *__frame_state_for(int, int);
extern void *eh_get_saved_register_addr(int, void *, int);

/* Works out the stack frame of the caller, filling in its saved register data. */
char *eh_next_stack_level(int pc, char *udata, int subUdata) {
    char *nextFrame = __frame_state_for(pc, subUdata);
    int reg;
    s64 value;

    if (nextFrame == 0)
        return 0;
    reg = *(u16 *)(nextFrame + 0x298);
    if (*(s8 *)(udata + reg + 0x29C) != 0) {
        value = *(s64 *)eh_get_saved_register_addr(reg, udata, 0);
        *(int *)nextFrame = value;
    } else {
        *(int *)nextFrame = *(int *)udata;
    }
    *(int *)nextFrame += *(int *)(nextFrame + 8);
    return nextFrame;
}
