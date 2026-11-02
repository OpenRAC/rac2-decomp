/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* opus-1 (xhigh), v2041: NOT A MATCH. Best check.py result, default flags
 * (-O2 -G0 -ffunction-sections): 1564/1572 bytes, 0/1 USA places; 84 of 393
 * instructions differ after alignment (the previous draft's 1572-byte form: 109).
 * The raw row count is 280 only because the missing 8 bytes shift the tail.
 *
 * FORBIDDEN CONSTRUCT, DISCLOSED: `int regen = 1; if (regen) { ... } else { ... }`
 * is an always-true test on a placeholder condition. WORKER2 forbids it, so this
 * can only ever be reported as FAILED until the maintainers rule on it. The real
 * condition in the original source is unknown (retail decrements and clamps the
 * timer, then resets it to 2 and the alpha to 64 unconditionally).
 *
 * Why it is here: gcse's first cprop pass may not touch jumps, only the last does,
 * after PRE. The constant test therefore survives PRE and is then deleted. One
 * mechanism reproduces all of retail's: `addiu v1,zero,1` at +4 (cse reuses regen
 * in the dispatch `beq v0,v1`), no sp+0x10 insert in the default arm, `addiu s0,sp,
 * 0x10` per outer iteration, `addiu sN,sp,0x20` in the inner preheader with no spill
 * slot, and `daddu s5,s0,zero`. The else arm gives PRE's i+1 insert a block of its
 * own that dies with the test, so i+1 stays in place (`addiu s1,s1,1; ...; sw s1`).
 *
 * Confirmed by the dumps:
 * - Scan: the start label dies, so loop.c prints "Loop ... is phony": no hoist, no
 *   giv. Retail's `nop` at +324 is the aligned label reorg makes when it steals k++
 *   into the back branch's slot, which needs the LOOP_BEG note. Sequence right.
 * - Clear loop: `off` per row, then `D + off` inside the inner loop. The la in the
 *   loop breaks check_dbra_loop's count equality, so col stays a counter, and the
 *   tree is (m + r) + D, then +0x10. Tree order and registers now match retail.
 *
 * What still differs:
 * 1. +280: ours `mult v1,v1,a2`; retail `mult zero,v1,a2; mflo v1` (the last 8 bytes,
 *    with the alignment nop). m needs a use at its own loop depth so it is allocated
 *    to LO, then copied; the source of that copy was not found.
 * 2. Spill slots swapped: ours o+0x10 at 0x84, i+1 at 0x80; retail the reverse.
 * 3. +074: `daddu a0,sp,zero` and `swc1 f0,0xF0(fp)` in the opposite order.
 * 4. Case 0: ours keeps o+0x10 in s0 for its second use and the query in s1; retail's
 *    second use is `lw a0,0x80(sp)` and the query takes s0.
 * 5. Scan registers: ours first load v0, k a0, loop load v1; retail v1, a1, a0.
 * 6. Outer head: ours `lui v0; addiu v0; sll a0,s1,1`; retail `sll v0,s1,1; lui v1;
 *    addiu v1; addu a1,v0,v1; daddu a0,v0,zero`, a surviving PRE copy of i<<1. A
 *    likely cause is cse2 replacing the copy's uses across the skipped clamp block.
 * 7. Inner preheader: ours s2 axis, s1 offset; retail the reverse.
 *
 * Declarations are below. func_002761F8 and func_002A8C00 take `void *` fifth
 * arguments here, which conflicts with L06_00458138.c, so this needs its own unit.
 * Scratch caveat from the earlier draft stands: collision[112] is inferred, not a
 * recovered type. Corrections it made are kept: an owner hit still copies the new
 * position, a null hit emits at the collision point, the state index is reloaded per
 * segment, the <= 0 guard, the unsigned sound-active byte, the upper angle constant.
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
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
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
extern int D_L06_001B3778[], D_L06_001B3760[];
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
    union { char collision[112]; struct { Vec velocity, axis; } vectors; } scratch;
    int regen = 1;
    char *st = *(char **)(o + 0x68);
    int i, j, sign, snd;
    typedef NotakQuad Trail[6][4];
    float direction;
    float size;
    switch (*(unsigned char *)(o + 0x20)) {
    case 0:
        *(float *)(o + 0xF0) = func_00283B98(*(float *)(o + 0xF0), 0.104719773f);
        func_00282CC0(pos, o + 0x10, st);
        func_002A8C00(scratch.collision, o, 1, st, *(float *)(st + 0x40));
        *(unsigned short *)(scratch.collision + 0x1A) = *(unsigned short *)(o + 0xAA);
        if (func_002761F8(o + 0x10, pos, 0, o, scratch.collision) ||
            func_0031EBF8(0.3f, o + 0x10, 0, o) || func_00282948(st + 0x38)) {
            char *hit = D_L06_001BFC80.hit;
            float *impact = D_L06_001BFC80.point;
            if (hit) {
                if (hit == *(char **)(st + 0x3C)) goto update_position;
                if (*(short *)(hit + 0xAA) != 0x4E)
                    func_002A8C28(o, o + 0x10, 0x10001, 0, 1, 0, 0.5f, *(float *)(st + 0x40), 1.0f);
                impact = (float *)(o + 0x10);
            }
            func_L06_00459828(impact, 20);
            snd = *(int *)(st + 0x4C);
            if (snd != -1) {
                char *s = D_00188660 + snd * 0x70;
                if (*(char **)(s + 0x88) == o && *(unsigned char *)(s + 0x74)) func_002E59F8(snd);
            }
            *(int *)(st + 0x4C) = -1;
            func_002A7750(o, 1, -1);
            return;
        }
    update_position:
        qcopy(o + 0x10, pos);
        break;
    case 1: {
        int index, row, col;
        index = D_L06_001B3778[*(int *)(st + 0x48)];
        if (index >= 0) {
            char *p = D_L06_001C79C0 + index * 32;
            *(float *)(p + 0x1C) -= 0.166666672f;
            if (!(*(float *)(p + 0x1C) <= 0)) return;
            func_00291450(D_L06_001B3778[*(int *)(st + 0x48)]);
            D_L06_001B3778[*(int *)(st + 0x48)] = -1;
            D_L06_001B3760[*(int *)(st + 0x48)] = 0;
            for (row = 0; row < 6; row++) {
                int off = *(int *)(st + 0x48) * 0x180 + (row << 6);
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
    qcopy(pos, o + 0x10);
    {
        int k = 0;
        if (D_L06_001B3790[k]) goto scanned;
    next:
        k++;
        while (k < 6) {
            if (!D_L06_001B3790[k]) goto next;
            break;
        }
    scanned:;
    }
    for (i = 0; i < 6; i++) {
        if (--D_L06_001B3790[i] < 0) D_L06_001B3790[i] = 0;
        if (regen) {
            D_L06_001B3790[i] = 2;
            D_L06_001B37A0[i] = 64;
            func_002A7988(scratch.vectors.velocity.f, 0.2f, 0.2f);
            if (func_00282DF0(scratch.vectors.velocity.f) > 0.2f) func_00282F20((char *)scratch.vectors.velocity.f, (char *)scratch.vectors.velocity.f, 0.2f);
            qcopy(&((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][0], pos);
            direction = 1.0f;
            for (j = 1; j < 4; j++) {
                func_00282CF0(scratch.vectors.axis.f, (float *)(&((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][j - 1]), (float *)D_L06_001B9840);
                func_002ACEC0(scratch.vectors.velocity.f, scratch.vectors.velocity.f, scratch.vectors.axis.f, func_002A7878(0.17453295f, 0.7853982448577881f) * direction);
                direction = -direction;
                func_00282CC0(&((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][j], &((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][j - 1], scratch.vectors.velocity.f);
            }
        } else {
            direction = 0.0f;
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
