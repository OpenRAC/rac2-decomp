#include "include_asm.h"

typedef int s32;
typedef float f32;
extern s32 D_L08_001B29DC __attribute__((sda));
extern f32 func_002A7878(f32, f32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern char D_00189EA0[];
extern void func_00282CF0(void *, void *, void *);
extern f32 func_00282DF0(void *);
extern void func_00282F20(void *, void *, f32);
extern void func_L08_00425398(char *);
extern int func_PAL_002B1A50(char *, char *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern char D_00189EA0[];
extern s32 D_L08_001B39A0[];
extern s32 D_L08_001B39E0[];
extern s32 D_L08_001B39F0[];
extern s32 D_L08_001B3A30[];

/* The record's whole per-frame pass: the sibling step, the aim vector copied out of the
   sub-object, the shared sprite pass, then the dispatch the shared tag call returns. */
void func_PAL_L08_0042B610(char *a0) {
    char *q = *(char **)(a0 + 0x68);
    int r;

    func_L08_00425398(a0);
    *(f32 *)(a0 + 0x2C) = *(f32 *)(*(char **)(a0 + 0x24) + 0x24);
    func_L08_00425EB0(a0);
    r = func_PAL_002B1A50(a0, q + 0x50, 0);
    if (r == 0) {
        return;
    }
    if (r == 1) {
        float v[4];

        func_00282CF0(v, a0 + 0x10, D_00189EA0);
        func_00282F20(q + 0x1A0, v, 0.20000002f);
    } else {
        if (r == 4) {
            *(unsigned char *)(q + 0xC6) = 0;
            *(s32 *)(q + 0xCC) = -1;
        }
        func_L08_00424ED0(a0);
    }
    func_L08_00425448(a0);
}


