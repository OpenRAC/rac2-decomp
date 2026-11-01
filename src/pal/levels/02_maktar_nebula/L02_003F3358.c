#include "include_asm.h"

#include "common.h"
extern char D_L02_001BA500;
extern char *D_L02_001FF1C0[];
extern float func_00282C48(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern void func_002AAC80(void *, float, float, float, float);
extern void func_L00_00424B48(int);
extern void func_L00_00424C28(void);
extern float D_L02_001B0E90 __attribute__((sda));
extern char *D_L02_001FF1C0[];
extern char *D_L02_001FF1C0[];
extern float func_00283B98(float, float);

/* Updates the heading (float at +0x38 of the actor's state) from the path D_L02_001FF1C0[*state]:
   its first word is the point count and its 16-byte points start at +0x10. The segment runs from
   point i (the index at +0x30, one back when it is the last point) to point j (i plus the
   lookahead at +0x3C, at most the last point). The segment's angle (func_00283248) minus the
   angle of the hero's direction vector (floats at +0x160 of its state, the pointer at +0x70 of the
   object at D_L02_001BA500 + 0x50) turned by pi, wrapped by func_00283B98 and func_00283BE0, clears
   the heading when it is under about a tenth of a degree; otherwise func_002AAC80 eases the
   heading towards it, weighted by the progress (+0x34, minus 6, over 8, at least 0). The heading
   is then copied into the hero's state at +0x1D4, +0x1DC gets 1.0 and, from a progress of 0.9, the
   two shared calls run. Nothing happens while the hero's halfword at +0x86 is not 0. */
void func_PAL_L02_003F3358(char *arg0) {
    char *hero = *(char **)(&D_L02_001BA500 + 0x50);
    char *state;
    char *hs;
    char *cam;
    float *dir;
    char *path;
    float scale;
    float a1;
    float a2;
    float t;
    int last;
    int i;
    int j;

    if (*(short *)(hero + 0x86) != 0)
        return;
    state = *(char **)(arg0 + 0x68);
    hs = *(char **)(hero + 0x70);
    cam = hs + 0x1C0;
    dir = (float *)(hs + 0x160);
    path = D_L02_001FF1C0[*(int *)state];
    scale = (*(float *)(state + 0x34) - 6.0f) * 0.125f;
    if (scale < 0.0f)
        scale = 0.0f;
    last = *(int *)path - 1;
    i = *(int *)(state + 0x30);
    if (i == last)
        i--;
    j = i + *(int *)(state + 0x3C);
    if (j > last)
        j = last;
    {
        char *p0 = path + i * 16;
        char *p1 = path + j * 16;

        a1 = func_00283248(*(float *)(p1 + 0x10) - *(float *)(p0 + 0x10),
                           *(float *)(p1 + 0x14) - *(float *)(p0 + 0x14));
    }
    a2 = func_00283248(dir[0], dir[1]);
    a2 = func_00283B98(a2, 3.1415927f);
    a1 = func_00283BE0(a1, a2);
    if (func_00282C48(a1) < 0.0017453294713050127f) {
        *(float *)(state + 0x38) = 0.0f;
    } else {
        t = scale * D_L02_001B0E90;
        func_002AAC80(state + 0x38, a1, (t + 0.5f) * 0.00040000002f,
                      (t + 0.5f) * 0.00040000002f, t * 0.020000001f);
    }
    *(float *)(cam + 0x1C) = 1.0f;
    *(float *)(cam + 0x14) = *(float *)(state + 0x38);
    if (scale >= 0.9f) {
        func_L00_00424B48(0);
        func_L00_00424C28();
    }
}

