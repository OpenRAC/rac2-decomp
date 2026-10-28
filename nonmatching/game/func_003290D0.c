/* func_003290D0 - 600 bytes.  Worker attempt, 27 October 2026 (draft below).

   draft.c is a full src/game/003290D0-qcopy.c; needs cflags line
   `src/game/003290D0-qcopy.c       -O2 -G0 -ffunction-sections -frac2-qcopy`;
   marker removed from 00327038.c. 592 vs 600 B (prologue now matches with
   `base = D_0022C9A0; p = &base[i]`).
   Remaining diffs: retail copies p into a callee-saved $s4 before the 2nd
   rand call (used as qcopy dst later; one extra save/restore of $s4 and one
   daddu), stores w38 BEFORE the second func_002A7820 call and w34 in its
   delay slot (mine reversed), and the colour/other stores order (0x30 then
   0x2C, mine 0x2C then 0x30). Chain assignments and separate statements both
   give the same scheduler order.
   Same particle array as func_00329328/func_00329488 (300 x 0x50 at
   D_0022C9A0; owner at +0x48; counters owner->0x4C/0x50). */

#include "include_asm.h"
#include "common.h"

typedef struct {
    float pos[4];
    float v[4];
    float f20;
    float f24;
    float f28;
    int w2C;
    int w30;
    int w34;
    int w38;
    int w3C;
    int w40;
    int w44;
    void *owner;
    int pad4C;
} F3290D0Particle;

extern F3290D0Particle D_0022C9A0[300];
extern int func_002A7820(int, int);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern void func_00282C88(void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);

void func_003290D0(char *obj, float *pos, float angle) {
    float tmp[4] __attribute__((aligned(16)));
    char *owner = *(char **)(obj + 0x68);
    F3290D0Particle *base = D_0022C9A0;
    F3290D0Particle *p;
    int i, r, c;

    for (i = 0; i < 300; i++) {
        p = &base[i];
        if (p->owner != 0)
            continue;
        p->w34 = p->w38 = func_002A7820(0x50, 0xC8);
        c = func_002A7820(0x60, 0x80);
        p->w2C = p->w30 = c + ((c << 7) & 0xFF00) + ((c << 14) & 0xFF0000);
        p->w3C = *(int *)(owner + 0x50) % 2 + 1;
        r = func_002A7820(0x32, 0x3C);
        p->w44 = p->w40 = r;
        p->f28 = angle;
        p->f24 = p->f20 = func_002A78D8(180.0f, 720.0f) * 0.00029088825f;
        func_002A7940();
        p->owner = obj;
        *(int *)(owner + 0x4C) = *(int *)(owner + 0x4C) + 1;
        if (pos[3] == -1.0f) {
            func_00282C88(tmp);
            tmp[3] = 1.0f;
            tmp[0] = -0.3f;
            func_00283098(tmp, tmp, obj + 0xC0);
            func_00282CC0(p, tmp, obj + 0x10);
        } else {
            qcopy(p, pos);
        }
        p->pos[0] += func_002A7878(-0.015f, 0.015f);
        p->pos[1] += func_002A7878(-0.015f, 0.015f);
        p->pos[2] += func_002A7878(-0.015f, 0.015f);
        func_00282C88(p->v);
        p->v[2] = func_002A7878(0.01f, 0.015f);
        *(int *)(owner + 0x50) = *(int *)(owner + 0x50) + 1;
        break;
    }
}
