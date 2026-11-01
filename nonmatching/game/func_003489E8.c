#include "include_asm.h"

/* func_003489E8 (boot, 1240 B): menu list update. G8: belongs at the end of
   src/game/00345358-g8.c, with that unit's flags extended to
   `-O2 -G8 -ffunction-sections -frac2-hazard-labels` (its other two functions still
   match with the flag; without it one branch lands after the hazard nop instead of on it).
   31 October 2026, USA v1.01: same size, one instruction off at +0x1B0 in every place:
   the two spilled values swap stack slots. Retail keeps the E4 widget address at 4($sp)
   and `pad & 0x1000` at 8($sp); here they are the other way round.
   In this draft both are allocated in order of pseudo number: `pressed` is a user variable
   (low number, slot 4) and the final call's `m + 0xE4` is a gcse copy (high number, slot 8).
   Retail needs the E4 pseudo below the mask's. Tried: the mask as a gcse temporary (the
   `if` repeats `pad & 0x1000`: it becomes 289, below the E4 copy 290); a `wE4` user
   variable (any declaration order, assigned before or after the fifth func_00335E10 call,
   or chained `wE4 = d = ...`): regmove then folds the fifth call's register into the
   spilled variable and a, b, c move to other callee-saved registers.
   Matched along the way: calls first and a/b/c assigned after them in both branches (cse
   reuses the prologue pointers only on the `if` side), the origin store in each branch,
   a const offset table, the final call recomputing `m + 0xE4`, and the
   `if (v < 0) v = lim;` wrap, which gives retail's `slt` against -1. */

typedef unsigned char u8;

extern float D_001AE5EC __attribute__((sda));
extern const float D_001AE760[10] __attribute__((section(".sdata")));

extern void func_00335E68(void *, int);
extern void func_003363C0(void *, float);
extern float *func_00335E10(void *);
extern unsigned int *func_00335E20(void *);
extern void func_00335F88(void *, float, float, float, float);
extern void func_002A9588(int, int, int, int, int);

#define MODE (*(int *)(m + 0x44C))
#define ORG (*(float **)(m + 0x434))

int func_003489E8(u8 *m, int pad)
{
    u8 *w98 = m + 0x98;
    u8 *w4C = m + 0x4C;
    u8 *w130 = m + 0x130;
    u8 *w17C = m + 0x17C;
    u8 *w1C8 = m + 0x1C8;
    u8 *wE4;
    u8 *a, *b, *c;
    float *p;
    int *flags;
    int pressed, step, i, n, idx, v, start, lim;

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
    pressed = pad & 0x1000;

    p = func_00335E10(m);
    p[0] = D_001AE760[0] + ORG[0];
    p[1] = D_001AE760[1] + ORG[1];
    p = func_00335E10(a);
    p[0] = D_001AE760[2] + ORG[0];
    p[1] = D_001AE760[3] + ORG[1];
    p = func_00335E10(b);
    p[0] = D_001AE760[4] + ORG[0];
    p[1] = D_001AE760[5] + ORG[1];
    p = func_00335E10(c);
    p[0] = D_001AE760[6] + ORG[0];
    p[1] = D_001AE760[7] + ORG[1];
    p = func_00335E10(m + 0xE4);
    p[0] = D_001AE760[8] + ORG[0];
    p[1] = D_001AE760[9] + ORG[1];

    for (i = 0; i < *(int *)(m + 0x444); i++) {
        u8 *row = m + 0x218 + i * 0x48;

        p = func_00335E10(row);
        p[0] = ((float *)(*(int *)(m + 0x414) + i * 12))[0] + ORG[0];
        p[1] = ((float *)(*(int *)(m + 0x414) + i * 12))[1] + ORG[1];
        func_00335F88(row, ((float *)(*(int *)(m + 0x414) + i * 12))[2], 0.0f, 0.0f, 0.0f);
        if (*(int *)(m + 0x418 + i * 4) != 0)
            *func_00335E20(row) = 0x80F0F0F0;
        else
            *func_00335E20(row) = 0x80808080;
    }

    step = 0;
    if (pressed) {
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
        flags = (int *)(m + 0x418);
        do {
            v = *(int *)(m + 0x43C) + step;
            if (lim < v)
                v = 0;
            if (v < 0)
                v = lim;
            idx = v;
            *(int *)(m + 0x43C) = idx;
            if (flags[idx] != 0)
                break;
        } while (start != idx);
    }
    func_003363C0(m + 0xE4, (float)*(int *)(m + 0x43C));
    *func_00335E20(m + (*(int *)(m + 0x43C) * 0x48 + 0x218)) = 0x70FFFEED;
    return *(int *)(m + 0x43C);
}
