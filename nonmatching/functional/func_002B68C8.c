/* functional: high. Same stores and calls in retail order; retail issues the +0x24 store in the delay slot of the func_002B66F0 call, here it is a plain store before the call. $v1 holds 0x20 and $a0 holds -1 at the call, as in retail, because the callee chain reads them. */
#include "include_asm.h"

extern void func_0026FEB8(void *);
extern char D_001AA198[];
extern char D_001A63A8[];
extern void func_002B66F0(void);
extern void func_002B6938(void);

void func_002B68C8(void)
{
    char *state;
    int minus1;
    int flags;

    func_0026FEB8(D_001AA198);
    state = D_001A63A8;
    minus1 = -1;
    flags = 0x20;
    *(short *)(state + 0x3C) = minus1;
    state[0x40] = flags;
    state[0x41] = 0;
    state[0x42] = 0;
    state[0x43] = 0;
    *(int *)(state + 0x44) = 0;
    *(short *)(state + 0x4E) = 0;
    *(int *)(state + 0x68) = 0;
    *(short *)(state + 0x72) = 0;
    *(int *)(state + 0x8C) = 0;
    *(short *)(state + 0x96) = 0;
    *(int *)(state + 0x24) = minus1;
    func_002B66F0();
    func_002B6938();
}
