/* functional: high. Same stores and calls in retail order; retail issues the +0x24 store in the delay slot of the func_002B66F0 call, here it is a plain store before the call. func_002B66F0 takes no arguments: it sets every register it passes on. */
#include "include_asm.h"

extern void func_0026FEB8(void *);
extern char D_001AA198[];
extern char D_001A63A8[];
extern void func_002B66F0(void);
extern void func_002B6938(void);

void func_002B68C8(void)
{
    char *state;

    func_0026FEB8(D_001AA198);
    state = D_001A63A8;
    *(short *)(state + 0x3C) = -1;
    state[0x40] = 0x20;
    state[0x41] = 0;
    state[0x42] = 0;
    state[0x43] = 0;
    *(int *)(state + 0x44) = 0;
    *(short *)(state + 0x4E) = 0;
    *(int *)(state + 0x68) = 0;
    *(short *)(state + 0x72) = 0;
    *(int *)(state + 0x8C) = 0;
    *(short *)(state + 0x96) = 0;
    *(int *)(state + 0x24) = -1;
    func_002B66F0();
    func_002B6938();
}
