#include "include_asm.h"

/* Menu list update: shows the widgets for the current mode, places the five fixed widgets and
   the list rows relative to the menu origin, greys out disabled rows, then steps the selection
   on up/down (wrapping at both ends, skipping disabled rows) and highlights it. Its own unit:
   - -G8 for the $gp-relative D_001AE5EC;
   - -frac2-hazard-labels: the branch out of the `if` arm lands on the hazard nop after the
     shared `mtc1` of the origin height, as in retail;
   - -frac2-gcse-unsplit-edges: with the low wrap through a pointer (WrapLow, as in
     func_00347F80), its branch only becomes a conditional move after the loop pass, which
     keeps retail's -1 inside the selection loop;
   - -fmove-all-movables: loop.c's pass 1 would otherwise leave the 0x80808080 constant of the
     row loop for the rerun pass, after the induction-variable inits.
   The four initialised locals (i, v, start, lim) bring the RTL to 284 insns, so gcse's PRE table
   has 143 buckets and numbers the E4 widget copy before the `pad & 0x1000` mask: the two spilled
   values then take retail's stack slots (4 and 8). The enabled flags are read through a struct
   pointer so that the index is added to its own base register (`addu base, index`). */

typedef unsigned char u8;
typedef struct { int enabled[7]; } EnabledSet; /* at menu + 0x418, one per list row */

extern float D_001AE5EC __attribute__((sda));
extern const float D_001AE760[10] __attribute__((section(".sdata")));

extern void func_00335E68(void *, int);
extern void func_003363C0(void *, float);
extern int func_00335E10(void *);
extern int func_00335E20(void *);
extern void func_00335F88(void *, float, float, float, float);
extern int func_002A9588(int, int, int, int, int);
extern int func_002E5E58(int, int, void *);

static inline void WrapLow(int *index, int last)
{
    if (*index < 0)
        *index = last;
}

#define MODE (*(int *)(m + 0x44C))
#define ORG (*(float **)(m + 0x434))

int func_003489E8(u8 *m, int pad)
{
    u8 *w98 = m + 0x98;
    u8 *w4C = m + 0x4C;
    u8 *w130 = m + 0x130;
    u8 *w17C = m + 0x17C;
    u8 *w1C8 = m + 0x1C8;
    u8 *a, *b, *c;
    float *p;
    EnabledSet *flags;
    int step, i = 0, v = 0, start = 0, lim = 0;

    func_00335E68(m, MODE == 0);
    func_00335E68(w98, MODE == 0);
    func_00335E68(w4C, MODE == 0);
    func_00335E68(m + 0xE4, MODE == 0);
    func_00335E68(w130, MODE == 0);
    func_00335E68(w17C, MODE == 1);
    func_00335E68(w1C8, MODE == 1);
    func_003363C0(w17C, D_001AE5EC);
    func_003363C0(w1C8, D_001AE5EC);

    if (MODE == 0 && *(int *)(m + 0x448) != 0) {
        func_003363C0(m, 1.0f);
        func_003363C0(m + 0x98, 1.0f);
        func_003363C0(m + 0x4C, 1.0f);
        func_003363C0(m + 0x130, 1.0f);
        c = m + 0x98;
        b = m + 0x4C;
        a = m + 0x130;
        ORG[1] = 170.0f;
    } else {
        func_003363C0(m, 0.0f);
        func_003363C0(m + 0x98, 0.0f);
        func_003363C0(m + 0x4C, 0.0f);
        func_003363C0(m + 0x130, 0.0f);
        c = m + 0x98;
        b = m + 0x4C;
        a = m + 0x130;
        ORG[1] = 190.0f;
    }

    p = ((float *)func_00335E10(m));
    p[0] = D_001AE760[0] + ORG[0];
    p[1] = D_001AE760[1] + ORG[1];
    p = ((float *)func_00335E10(a));
    p[0] = D_001AE760[2] + ORG[0];
    p[1] = D_001AE760[3] + ORG[1];
    p = ((float *)func_00335E10(b));
    p[0] = D_001AE760[4] + ORG[0];
    p[1] = D_001AE760[5] + ORG[1];
    p = ((float *)func_00335E10(c));
    p[0] = D_001AE760[6] + ORG[0];
    p[1] = D_001AE760[7] + ORG[1];
    p = ((float *)func_00335E10(m + 0xE4));
    p[0] = D_001AE760[8] + ORG[0];
    p[1] = D_001AE760[9] + ORG[1];

    for (i = 0; i < *(int *)(m + 0x444); i++) {
        u8 *row = m + 0x218 + i * 0x48;

        p = ((float *)func_00335E10(row));
        p[0] = ((float *)(*(int *)(m + 0x414) + i * 12))[0] + ORG[0];
        p[1] = ((float *)(*(int *)(m + 0x414) + i * 12))[1] + ORG[1];
        func_00335F88(row, ((float *)(*(int *)(m + 0x414) + i * 12))[2], 0.0f, 0.0f, 0.0f);
        if (*(int *)(m + 0x418 + i * 4) != 0)
            *((unsigned int *)func_00335E20(row)) = 0x80F0F0F0;
        else
            *((unsigned int *)func_00335E20(row)) = 0x80808080;
    }

    step = 0;
    if (pad & 0x1000) {
        func_002E5E58(3, 0, 0);
        step = -1;
    } else if (pad & 0x4000) {
        func_002E5E58(3, 0, 0);
        step = 1;
    }
    if (step != 0) {
        start = *(int *)(m + 0x43C);
        func_002A9588(0, 0, 1, 0, 1);
        lim = *(int *)(m + 0x444) - 1;
        flags = (EnabledSet *)(m + 0x418);
        do {
            int wrapped;
            v = *(int *)(m + 0x43C) + step;
            if (lim < v)
                v = 0;
            wrapped = v;
            WrapLow(&wrapped, lim);
            *(int *)(m + 0x43C) = wrapped;
            if (flags->enabled[wrapped] != 0)
                break;
        } while (start != *(int *)(m + 0x43C));
    }
    func_003363C0(m + 0xE4, (float)*(int *)(m + 0x43C));
    *((unsigned int *)func_00335E20(m + (*(int *)(m + 0x43C) * 0x48 + 0x218))) = 0x70FFFEED;
    return *(int *)(m + 0x43C);
}
