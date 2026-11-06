/* 6 November 2026: unchanged, 460/460, 0/2, 4 rows (the preheader copy). Tied: a second
 * row pointer copied from the first, two pointer bivs a/b from the row, a separate q row,
 * `p + j * 64 + 0x460`, a per-iteration local for the 0x460 cell, q = p + 0x100. An int
 * offset summed three times is far worse (113 rows). Loop dump: both givs (1120, 1376) come
 * from reg 108 = (i << 4) + s with no copy; retail's copy must come from another pseudo. */
/* 4 November 2026 source-layout review, retained near miss.
 * Four new grid/address/group forms with -O2 -G8 -ffunction-sections -g
 * remain 460/460 bytes, 0/2 USA places (first +0x78 or +0x84).
 * Both borrowed grids have three rows of four 16-byte cells: the second
 * ends at counter +0x620. A four-row owning view would overlap that counter.
 * Typed cell pointers and signed/unsigned EE-word row sums do not preserve
 * the second preheader copy. A real inner-loop or row-assignment one-pass
 * group does not resolve it either. The older best C below is retained.
 * Reopen with evidence of the row pseudo's lifetime across loop reduction;
 * no dummy pointer, false return or register pin was introduced.
 */
/* Nonmatching C reconstruction (opus-1, v2196, USA v1.01, 2026-11-03).
 * Tier: near miss. Profile: -O2 -G8 -ffunction-sections -g in its own unit
 * (-g supplies the two nops before each div.s).
 * Best cdiff: 460 compiled bytes / 460 retail, 0 of 2 places; one block differs.
 * Only remaining difference, nested-loop preheader: retail computes the row
 * v1 = (i<<4) + s, copies it (daddu v0,v1,zero), then s0 = v1+0x460 and
 * s1 = v0+0x560; here there is no copy and an alignment nop follows.
 * The integer row sum below fixes the addu operand order (pointer arithmetic
 * puts s first); `char *p = i * 16 + s;` is otherwise identical.
 * Computing idx = s + 0x18 inside the last loop reproduces retail's PRE copy
 * into a2; the current/next index split reproduces v1/s4.
 * Tied or worse: two pointer bivs, two identical row bases, recomputing the
 * row inside the inner loop, q = p + j*64, a struct with [4][4] vec arrays.
 * Likely cause: retail's copy destination is a separate pseudo still live at
 * cse2 (e.g. a reduced row giv from loop pass 1 re-reduced in pass 2).
 * All declarations are below.
 */
#include "common.h"

extern void func_00282CC0(char *, char *, char *);
extern float func_00283CE0(int);
extern int func_00283D38(int, int, float);
extern int D_L13_001B1624 __attribute__((sda));
extern int D_L13_001B1628 __attribute__((sda));
extern int D_L13_001B1650 __attribute__((sda));
extern int D_L13_001B1654 __attribute__((sda));
extern int D_L13_001B1658 __attribute__((sda));
void func_L13_0041AB30(char *obj)
{
    char *s = *(char **)(obj + 0x68);
    int j;
    if (*(short *)(s + 0x12)) {
        (*(short *)(s + 0x12))--;
        {
            int i;
            for (i = 0; i < 23; i++)
                func_00282CC0(s + 0x60 + i * 16, s + 0x60 + i * 16, s + 0x260 + i * 16);
        }
        {
            int i = 0;
            do {
                int next = i + 1;
                char *p = (char *)(i * 16 + (int)s);
                for (j = 0; j < 3; j++)
                    func_00282CC0(p + 0x460 + j * 64, p + 0x460 + j * 64, p + 0x560 + j * 64);
                i = next;
            } while (i < 4.0f);
        }
        {
            int i;
            for (i = 0; i < 4; i++) {
                unsigned char *idx = (unsigned char *)s + 0x18;
                qcopy(s + 0x420 + i * 16, s + 0x20 + idx[i] * 16);
            }
        }
    }
    if (*(short *)(s + 0x12) > D_L13_001B1624) {
        float a = func_00283CE0(*(short *)(s + 0x12) - D_L13_001B1624);
        float b = func_00283CE0(*(int *)(s + 0x620) - D_L13_001B1624);
        *(int *)(s + 0x14) = func_00283D38(D_L13_001B1654, D_L13_001B1650, a / b);
    } else if (*(short *)(s + 0x12) > D_L13_001B1628) {
        float a = func_00283CE0(*(short *)(s + 0x12) - D_L13_001B1628);
        float b = func_00283CE0(D_L13_001B1624 - D_L13_001B1628);
        *(int *)(s + 0x14) = func_00283D38(D_L13_001B1658, D_L13_001B1654, a / b);
    } else *(int *)(s + 0x14) = 0;
}
