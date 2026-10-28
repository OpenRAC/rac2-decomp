/* func_L04_003EDD40 - 572 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   New file L04_003EDD40-qcopy.c, flags `-O2 -G0 -ffunction-sections
   -frac2-qcopy`. Structure matches retail (obj in a stack slot sp+0x10 re-
   read before every access, result in a reg reused for 0xFF). 568 B vs 572.
   Left: retail keeps the stack copy of a1's quad as `lq v0,0(a1); sq
   v0,0(sp)` and later reads it back with `lq v0,0(s2)` where $s2 = copy of
   $sp made in the prologue (frame 0x50, parent in $s3); the draft folds the
   address (`lq v0,0(sp)`, frame 0x40, parent in $s2). A plain TI local goes
   to a register ($s0); `Quad16 pos[1]` puts it on the stack. Tried pointer
   var `pp = pos` (cse folds it), float[4] struct (ld/sd).
   Also retail stores 0x24 before 0x20 around the cvt.s.w in the final `p`
   block and uses a `beql` after func_L00_00345AF0. */

#include "include_asm.h"

typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));

extern int func_002A8600(unsigned char **out, int a1, int a2, int a3);
extern void func_0029F390(unsigned char *a0);
extern int func_L00_00345AF0(unsigned char *a0);
extern void func_002AB650(unsigned char *a0);
extern void func_002A0F48(void *a0);
extern unsigned char *func_002AB1F0(unsigned char *a0);
extern void func_0026FEB8(void *a0, int a1, int a2);
extern unsigned char D_L04_001B0160[];
extern int D_L04_001B2008;

typedef struct {
    Q16_B0e5d8f83 q;
} Quad16 __attribute__((aligned(16)));

/* Allocates an object for a1's position under the parent a0 and sets its default fields. */
unsigned char *func_L04_003EDD40(unsigned char *a0, void *a1) {
    Quad16 pos[1];
    Quad16 *pp = pos;
    unsigned char *obj;
    unsigned char *state;
    unsigned char *result;
    unsigned char *p;

    *pp = *(Quad16 *)a1;
    if (a0 == 0)
        return 0;
    state = *(unsigned char **)(a0 + 0x68);
    obj = 0;
    result = 0;
    if (func_002A8600(&obj, *(int *)(state + 0x84), 1, 1) == 0) {
        state[0x81] = state[0x81] + 1;
        *(Quad16 *)(obj + 0x10) = *pp;
        *(int *)(obj + 0x1C) = 0;
        obj[0x20] = 0;
        obj[0xBC] = 0;
        *(unsigned short *)(obj + 0x34) = *(unsigned short *)(*(unsigned char **)(obj + 0x24) + 0x44);
        *(float *)(obj + 0x2C) = *(float *)(*(unsigned char **)(obj + 0x24) + 0x24);
        obj[0x30] = 0xFF;
        *(unsigned short *)(obj + 0x32) = 0xFF;
        obj[0x31] = 1;
        obj[0x40] = 0;
        obj[0x41] = 0;
        obj[0x42] = 0;
        obj[0x43] = 0;
        func_0029F390(obj);
        if (*(int *)(*(unsigned char **)(obj + 0x24) + 0x40) != 0)
            *(unsigned short *)(obj + 0x34) |= 0x10;
        if ((*(unsigned char **)(obj + 0x24))[0xF] != 0)
            *(unsigned short *)(obj + 0x34) |= 0x400;
        *(unsigned short *)(obj + 0x36) = 0x7F80;
        obj[0x61] = 0xFF;
        obj[0x62] = 0xFF;
        obj[0xA8] = 0xFF;
        if (state[0x83] != 0)
            *(float *)(obj + 0x2C) = *(float *)(*(unsigned char **)(obj + 0x24) + 0x24) * 0.1f;
        if (func_L00_00345AF0(obj) != 0) {
            *(int *)(obj + 0x6C) = 0;
            *(int *)(obj + 0x94) = 0;
            *(short *)(obj + 0x68) = 0;
        }
        *(unsigned char **)(obj + 0xB8) = a0;
        *(int *)(obj + 0x98) = *(int *)(*(unsigned char **)(obj + 0x24) + 0x10);
        func_002AB650(obj);
        func_002A0F48(obj);
        result = obj;
        p = func_002AB1F0(result);
        if (p != 0) {
            *(float *)p = (float)*(short *)(p + 4);
            *(int *)(p + 0x24) = 0;
            *(int *)(p + 0x20) = 0;
        }
        obj[0x7F] = 0;
    } else {
        func_0026FEB8(D_L04_001B0160, *(short *)(a0 + 0xB2), D_L04_001B2008);
    }
    return result;
}
