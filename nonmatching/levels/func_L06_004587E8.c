/* 9 November 2026 (switch sweep s40): -fno-cse-follow-jumps: size 1564 -> 1572 matches, 139 differing rows; still far. */
/* 8 November 2026 (Sonnet round, s28): lesson 49 pass on the C below (type, s, p, snd, hit, index inlined one by one; count/one literal; duplicated impact tails): none beats 1564/1572, 19 aligned diffs; C unchanged. */
/* 8 November 2026 (Sonnet round): re-measured the round-3 body 1564/1572; 1 permuter run (1500 s, -j2) best score 1230 vs 1285, still 1564 bytes, no real row fixed, nothing adopted. */
/* 8 November 2026: not a match. check.py: 1564/1572 bytes, 0/1 USA v1.01
 * placement; 26 of 393 instructions differ after alignment (2 November body:
 * 1596 bytes, 123 differ; the forbidden regen draft: 61). No always-true test.
 * What changed, and why:
 * - `int count = 6;` bounds the regeneration loop. cse1 cannot fold the entry
 *   test `0 < count` (other block), so gcse sees a loop that may be skipped and
 *   does not hoist sp+0x10/sp+0x20 into the default arm; the final cprop then
 *   folds the test. This is what the old regen test did.
 * - All scalars at function scope with `i` declared last: i's pseudo number
 *   moves the i+1 PRE expression after o+0x10 in hash order, so the spill slots
 *   match (o+0x10 at 0x80, i+1 at 0x84).
 * - collision[112] is local to case 0 and velocity/axis to the loop body; the
 *   compiler shares their slots (0xF0 frame, as retail).
 * - `direction = 1.0f` before the row qcopy shortens the axis live range, so
 *   axis takes s1 and the segment offset s2 (as retail).
 * - impact = point only in the else arm gives retail's beql.
 * - func_002C2210's last two parameters as (float, int): same registers,
 *   fixes the tail argument order.
 * Still different: (1) retail sets `li v1,1` at +4 for the case-1 compare
 *   (a 1-valued `first` loop start fixes it but breaks the axis/offset pair);
 *   (2) case 0 keeps o+0x10 in s0 for func_002761F8, retail reloads 0x80 and
 *   gives sp+0x10 s0; (3) case 1 register names at +0x1D8; (4) `mult` vs
 *   `mult zero; mflo` in the clear loop; (5) loop head: retail `sll v0,s1,1`
 *   plus a copy `daddu a0,v0,zero` for the alpha index; (6) direction's mtc1
 *   now lands before the row qcopy (retail: after it).
 * Tried and worse: scan written as a for loop (56), `first` on the clear loop
 *   (51), -fno-gcse (92). Needs its own unit (prototype clash with
 *   L06_00458138.c); default flags.
 * Round 2 (8 November 2026), body unchanged (still best, 26):
 * - mult: `mult zero; mflo` appears only when st->0x48 * 0x180 is written
 *   inside the col loop (loop.c moves it twice); the giv tree then becomes
 *   (m+16)+(D+r) instead of retail's ((m+r)+D)+16 (28). Separate product
 *   locals, operand order and unsigned all keep the 3-operand mult.
 * - i<<1 copy: a timer pointer, an index local or a group around the clamp
 *   do not create it. Grouping the two resets (`do { t=2; a=64; } while (0)`)
 *   gives retail's 1572-byte size but 32 diffs.
 * - case 0: `impact = o + 0x10` before func_00282CC0 gives sp+0x10 s0 as
 *   retail, but impact then keeps s1 (29). s/hit/p as the temp: worse.
 * Round 3 (8 November 2026), new body below: still 1564/1572 bytes, 0/1.
 *   Aligned diff (difflib, relocations masked) 19 lines; the round-2 body
 *   gives 30 on the same count. What changed:
 * - `int one = 1;` plus a goto dispatch (`if (type == 0) goto c0; if (type ==
 *   one) goto c1; goto def;`) inside an extra `{ }`: gives retail's early
 *   `li v1,1` and the switch layout. Literal 1 loses the hoist; plain if/else
 *   gives a bnez layout; without the extra braces the frame grows to 0x110.
 * - D_L06_001B3778 declared __attribute__((sda)): its address becomes one
 *   unsplit `la`, so case 1 gets retail's `lui s0; addiu s0,s0` and register
 *   names. sda on 37A0 or off 3790 is worse (35, 36).
 * Still different: case-0 o+0x10 kept in s1 for func_002761F8 (retail reloads
 *   0x80); 3-operand mult; loop-head i<<1 copy; direction's mtc1.
 * Tried this round, no gain: impact = o+0x10 before func_00282CC0 (30), a
 *   named `opos` local (37); Trail/row-pointer/in-col-loop products all give
 *   `mult; mflo` but the giv becomes (m+16)+(D+r) (28), a row-offset local
 *   or row pointer outside the col loop with the product inside: same;
 *   clamp as `x--; if`, `-= 1`, byte-offset store, do-while groups around the
 *   clamp or resets (resets group: 1572 bytes but 31); `short *t` timer
 *   pointer; -fno-cse-skip-blocks (61, but it does create the copy),
 *   -fno-cse-follow-jumps (33); direction = 1.0f after the qcopy fixes the
 *   mtc1 but swaps axis/offset s1/s2 (22); axis via a pointer local or
 *   declared in the j loop: worse.
 */
#include "common.h"
extern short D_L06_001B3790[] __attribute__((sda));
extern short D_L06_001B37A0[] __attribute__((sda));
extern char D_L06_0025FFC0[];
extern float func_00283B98(float, float);
typedef unsigned int NotakQuad __attribute__((mode(TI)));
extern char D_00188660[];
extern char D_L06_001A8F20[] __attribute__((sda));
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern char D_L06_001B9840[];
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern int func_002A77E0(int);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, float, int);
extern void func_002A7750(char *, int, int);
extern float func_002A7878(float, float);
extern void func_00350388(char *);
typedef struct {
    char prefix[0x18];
    char *hit;
    int count;
    float point[4];
} NotakCollision;
extern NotakCollision D_L06_001BFC80;
extern char D_L06_001C79C0[];
extern int D_L06_001B3778[] __attribute__((sda));
extern int D_L06_001B3760[];
extern void func_002A8C00(void *, char *, int, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_0031EBF8(float, void *, int, void *);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern void func_L06_00459828(float *, int);
extern void func_00291450(int);
extern void func_002A7988(void *, float, float);
extern float func_00282DF0(void *);
extern int func_002E59B0(void *, int);
extern int func_002E5DA0(int, int, void *, int);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L06_00458F30(char *);

void func_L06_004587E8(char *o) {
    float pos[4];
    typedef union { NotakQuad q; float f[4]; } Vec;
    char *st = *(char **)(o + 0x68);
    char *hit;
    float *impact;
    char *s;
    int snd, index, row, col;
    char *p;
    int off, k, j, sign;
    int count = 6;
    typedef NotakQuad Trail[6][4];
    float direction;
    float size;
    int i;
    int one = 1;
    int type = *(unsigned char *)(o + 0x20);
    {
    if (type == 0) goto c0;
    if (type == one) goto c1;
    goto def;
    c0: {
        char collision[112];
        *(float *)(o + 0xF0) = func_00283B98(*(float *)(o + 0xF0), 0.104719773f);
        func_00282CC0(pos, o + 0x10, st);
        func_002A8C00(collision, o, 1, st, *(float *)(st + 0x40));
        *(unsigned short *)(collision + 0x1A) = *(unsigned short *)(o + 0xAA);
        if (func_002761F8(o + 0x10, pos, 0, o, collision) ||
            func_0031EBF8(0.3f, o + 0x10, 0, o) || func_00282948(st + 0x38)) {
            hit = D_L06_001BFC80.hit;
            if (hit) {
                if (hit == *(char **)(st + 0x3C)) goto update_position;
                if (*(short *)(hit + 0xAA) != 0x4E)
                    func_002A8C28(o, o + 0x10, 0x10001, 0, 1, 0, 0.5f, *(float *)(st + 0x40), 1.0f);
                impact = (float *)(o + 0x10);
            } else {
                impact = D_L06_001BFC80.point;
            }
            func_L06_00459828(impact, 20);
            snd = *(int *)(st + 0x4C);
            if (snd != -1) {
                s = D_00188660 + snd * 0x70;
                if (*(char **)(s + 0x88) == o && *(unsigned char *)(s + 0x74)) func_002E59F8(snd);
            }
            *(int *)(st + 0x4C) = -1;
            func_002A7750(o, 1, -1);
            return;
        }
    update_position:
        qcopy(o + 0x10, pos);
        goto def;
    }
    c1: {
        index = D_L06_001B3778[*(int *)(st + 0x48)];
        if (index >= 0) {
            p = D_L06_001C79C0 + index * 32;
            *(float *)(p + 0x1C) -= 0.166666672f;
            if (!(*(float *)(p + 0x1C) <= 0)) return;
            func_00291450(D_L06_001B3778[*(int *)(st + 0x48)]);
            D_L06_001B3778[*(int *)(st + 0x48)] = -1;
            D_L06_001B3760[*(int *)(st + 0x48)] = 0;
            for (row = 0; row < 6; row++) {
                off = *(int *)(st + 0x48) * 0x180 + (row << 6);
                for (col = 1; col < 4; col++)
                    qzero_nc(&((NotakQuad *)(D_L06_0025FFC0 + off))[col]);
            }
            func_00350388(o);
            return;
        }
        D_L06_001B3760[*(int *)(st + 0x48)] = 0;
        func_00350388(o);
        return;
    }
    }
def:
    qcopy(pos, o + 0x10);
    {
        k = 0;
        if (D_L06_001B3790[k]) goto scanned;
    next:
        k++;
        while (k < 6) {
            if (!D_L06_001B3790[k]) goto next;
            break;
        }
    scanned:;
    }
    for (i = 0; i < count; i++) {
        Vec velocity, axis;
        if (--D_L06_001B3790[i] < 0) D_L06_001B3790[i] = 0;
        D_L06_001B3790[i] = 2;
        D_L06_001B37A0[i] = 64;
        func_002A7988(velocity.f, 0.2f, 0.2f);
        if (func_00282DF0(velocity.f) > 0.2f) func_00282F20((char *)velocity.f, (char *)velocity.f, 0.2f);
        direction = 1.0f;
        qcopy(&((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][0], pos);
        for (j = 1; j < 4; j++) {
            func_00282CF0(axis.f, (float *)(&((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][j - 1]), (float *)D_L06_001B9840);
            func_002ACEC0(velocity.f, velocity.f, axis.f, func_002A7878(0.17453295f, 0.7853982448577881f) * direction);
            direction = -direction;
            func_00282CC0(&((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][j], &((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][j - 1], velocity.f);
        }
    }
    if (!func_002A77E0(2)) {
        size = func_002A7878(0.2f, 0.9f);
        sign = func_002A77E0(2);
        if (!sign) sign--;
        func_002C2210(o + 0x10, 2, size * 0.1f, size, 0x7F7F2020, 0, sign, D_L06_001A8F20, 0, 0);
        func_002C2210(o + 0x10, 2, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, D_L06_001A8F20, 0, 0);
    }
    if (!func_002E59B0(o, *(int *)(st + 0x4C)))
        *(int *)(st + 0x4C) = func_002E5DA0(7, 4, o, *(short *)(*(char **)(st + 0x3C) + 0xAA));
    func_L00_002E6EF8(func_L06_00458F30, o);
}
