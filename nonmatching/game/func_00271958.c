/* func_00271958 - 568 bytes.  Worker attempt, 27 October 2026 (draft below).

   draft.c is a full src/game/00271958-g8.c (-G8 by name; D_001A95C8 is the
   sda float at -0x6A38($gp); D_001B5390 nosda). Marker must be removed from
   0026EA00.c. Frame matches with `float m[16]` (0x80 frame).
   552 vs 568 B (about 24 masked diff lines, all branch layout): retail shape
   is `lw v1,8(s1); beql v1,zero,EPILOGUE; sw zero,0xC(s1)` (likely-branch
   with the store in its slot, straight to the shared epilogue at 0x271B70)
   and its switch dispatch is `beq mode,1; slti; beql ..; beqz mode; nop; b
   EPI; beq mode,2 ...` with the nop after beqz. Mine produces `bnel ...; lw;
   b; sw` for the zero test and fewer duplicated epilogue sequences. Case 0
   and 1 share the tail (goto common), case 0 block comes first with base
   D_001B5590, case 1 with D_001B5570.
   Tried: early-return form, if/else chain, else-if with == 0 first. */

#include "include_asm.h"

extern char *D_001B5390 __attribute__((nosda));
extern char D_001B5340[];
extern char D_001B5570[];
extern char D_001B5590[];
extern float D_001A95C8 __attribute__((sda));

extern int func_00282948(void *);
extern float func_00283CE0(int);
extern float func_00283C28(float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACE78(void *, void *, float);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);

typedef struct {
    float f0;
    float f4;
    int w8;
    int wC;
} F1958State;

void func_00271958(F1958State *st, int mode) {
    float m[16] __attribute__((aligned(16)));
    char *base;
    float t, cube, f, g, h;

    if (D_001B5390 != 0 && *(short *)(D_001B5390 + 0x86) == 6) {
        st->wC = 0;
        st->w8 = 0;
    } else if (st->w8 == 0) {
        st->wC = 0;
    } else {
        if (st->wC < st->w8)
            st->wC = st->w8;
        func_00282948(&st->w8);
        t = func_00283CE0(st->w8);
        t /= func_00283CE0(st->wC);
        switch (mode) {
        case 0:
            h = func_00283180(func_00283C28(func_00283CE0(st->w8) * 2.0f));
            base = D_001B5590;
            goto common;
        case 1:
            h = func_00283180(func_00283C28(func_00283CE0(st->w8) * 2.0f));
            base = D_001B5570;
        common:
            st->f4 = st->f0 * h * t * t;
            func_00282F20(m, base, st->f4);
            func_00282CC0(D_001B5340, D_001B5340, m);
            break;
        case 2:
            cube = t * t * t;
            f = D_001A95C8 * 0.017453293f;
            g = func_00283CE0(st->wC - st->w8) * (1.0f / 60.0f);
            t = g * 6.0f;
            if (t > 1.0f)
                t = 1.0f;
            st->f4 = st->f0 * func_00283198(func_00283C28(g * f - f * 10.0f)) * cube * t;
            func_002ACE78(m, D_001B5570, st->f4);
            func_00283958(m, m + 4);
            func_00283738(D_001B5570, m + 4, D_001B5570);
            break;
        }
    }
}
