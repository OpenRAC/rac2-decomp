#include "common.h"

/* The value is taken through a named s64 local: writing `(int)*(s64 *)p`
   directly folds the load into a 32-bit `lw`, while the local keeps retail's
   `ld` plus the truncdisi2 pair (dsll32/dsra32). */
extern char *func_001240C8(int, int);
extern void *func_00120A30(int, void *, int);

/* Works out the stack frame of the caller, filling in its saved register data. */
char *func_00120B38(int pc, char *udata, int subUdata) {
    char *nextFrame = GetFrameStateForPc(pc, subUdata);
    int reg;
    s64 value;

    if (nextFrame == 0)
        return 0;
    reg = *(u16 *)(nextFrame + 0x298);
    if (*(s8 *)(udata + reg + 0x29C) != 0) {
        value = *(s64 *)GetSavedRegisterAddress(reg, udata, 0);
        *(int *)nextFrame = value;
    } else {
        *(int *)nextFrame = *(int *)udata;
    }
    *(int *)nextFrame += *(int *)(nextFrame + 8);
    return nextFrame;
}
