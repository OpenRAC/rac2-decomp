/* functional: high. The near-miss draft (4 scheduling lines off) with the callees under their real names (level 00's 0x2EE0D0/0x2EE108/0x2EE138/0x2EE178/0x2EE1F8 are func_00282C88/CC0/CF0/D30/DB0) and the hero quadwords named by their addresses (0x18A0E0, 0x189EA0); same calls, arguments, copies and order as retail. */
/* func_L00_00423290 (shared, 27 places): sets up a follow camera's frame from the hero. Unless the
 * control's mode halfword (+0x86) is set: the reversed hero facing (0x18A0E0 * -1), the hero position
 * (0x189EA0) into state+0x60 and +0xC0, the projection onto the facing into +0x70, clears +0xD0/+0xE0/
 * +0x100, the two offset points +0xB0 / +0xF0 (copied to +0xA0), the aim (+0x160, copied to +0x170)
 * towards the control's target (+0x30, copied to +0x00), the look vector +0x210, and clears +0x240.
 * From the near-miss draft nonmatching/levels/func_L00_00423290.c. */
#include "common.h"

typedef int CamQ __attribute__((mode(TI)));

extern CamQ D_00189EA0;
extern CamQ D_0018A0E0;

extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);

void func_L00_00423290(char *a0)
{
    char *obj;
    char *pos;
    char buf0[16] __attribute__((aligned(16)));
    char buf1[16] __attribute__((aligned(16)));

    if (*(short *)(a0 + 0x86) != 0)
        return;

    obj = *(char **)(a0 + 0x70);
    pos = obj + 0x60;

    func_00282D30(buf0, &D_0018A0E0, -1.0f);
    *(CamQ *)pos = D_00189EA0;
    *(CamQ *)(obj + 0xC0) = *(CamQ *)pos;
    func_00282D30(obj + 0x70, buf0, func_00282DB0(pos, buf0));
    func_00282C88(obj + 0xD0);
    func_00282C88(obj + 0xE0);
    func_00282C88(obj + 0x100);
    func_00282D30(buf1, buf0, *(float *)(obj + 0x190));
    func_00282CC0(obj + 0xB0, buf1, pos);
    func_00282D30(buf1, buf0, *(float *)(pos + 0xB0));
    func_00282CC0(obj + 0xF0, buf1, pos);
    *(CamQ *)(obj + 0xA0) = *(CamQ *)(obj + 0xF0);
    func_00282CF0(obj + 0x160, a0 + 0x30, obj + 0xB0);
    *(CamQ *)(obj + 0x170) = *(CamQ *)(obj + 0x160);
    *(CamQ *)obj = *(CamQ *)(a0 + 0x30);
    func_00282CC0(obj + 0x210, obj + 0xB0, obj + 0x160);
    *(int *)(obj + 0x240) = 0;
}
