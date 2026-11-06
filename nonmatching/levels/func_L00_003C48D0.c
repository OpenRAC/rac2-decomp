/* 6 November 2026, round 2: no change. Own -O2 -G0 unit, plain indexed body with
 * `next = i + 1`: 684/708. Outer loop as goto: 656 (gcse hoists D_1B2990 instead,
 * D-16 built from D); goto with -fno-gcse: 652 (addresses rebuilt as retail, but
 * D-16 from D and no madd). do-while or while outer loop: 684. sda attributes on the
 * arrays: 684. -fno-rerun-loop-opt: 692. Loop dump: threshold is about 45-54, so a
 * savings-2 life-4 address in a 152-insn loop is always desirable; retail's outer
 * loop is a real loop (aligned top label, nop) that moved nothing.
 */
/* 6 November 2026: two new checks, no match; the body below is kept (696/708).
 * Plain indexed C (`func_00282CF0(delta[j], D[i][j], D[i][j - 1])`, j = 1..9, own
 * -O2 -G0 unit) gives retail's D_240070 operand but strength-reduces the outer loop
 * (frame 0x140). Writing the outer loop `for (i = 0; i < 5; i = next) { next = i + 1;`
 * gives retail's s7 = i + 1 in the beqz slot and the per-iteration sll/mult (no outer
 * givs), 684/708. Left: loop.c still hoists the D_1B2990/D_240080 addresses out of
 * the outer loop (dump: savings 2, matched refs); retail rebuilds each one, so the
 * outer loop got no loop.c work at all. Reopen with a reason the outer movables are
 * not desirable (or the loop is skipped), not with alias tricks.
 */
/* Complete-strand offset reconstruction, 2026-11-03; not linked.
 * Check: USA v1.01, -O2 -G0 -ffunction-sections -fno-rerun-loop-opt,
 * 696/708 bytes, 0/27 placements; frame 0x130 rather than retail 0x120.
 * Two int32 byte-offset streams describe previous/current points within the
 * one real 800-byte owner. Pointers form only at accessed points, not at a
 * synthetic pre-array symbol. The scalar color contract is u32 in the matched
 * renderer; its six GPR and three FP arguments consume exactly 160 input bytes.
 * This form is 696 bytes (prior indexed form 680), and still misses retail's
 * address re-materialization, loop scheduling or register allocation.
 * Reopen with independent source evidence for those operand lifetimes.
 */

/* Retained strand refresh/draw, 2026-10-28: best680/708B,0/27US.
 * Six bounded trials. Cached record pointer612; narrow no-rerun-loop-opt632;
 * explicit owner indexing680. Adding no-strength-reduce656; broad no-gcse680
 * (no improvement, rejected). Both real color loads and unsigned alpha shift
 * retain680. Best required profile -O2 -G0 -ffunction-sections -fno-rerun-loop-opt.
 * The one canonical array owns five real160B records. Retail separately forms
 * 00240070/00240080 views around adjacent points; this source preserves that
 * overlap without independent alias declarations to manufacture CSE failures.
 * Remaining gap: address re-materialization, multiply/add and store scheduling.
 * Scratch delta[10] indexes1..9 only, matching retail unused slotsp10 and
 * nine initialized delta vectorssp20..AF. Anchor16B, private minimum40B.
 * Draw002EBE88 has six GPR and three FP arguments, void contract; its 776B
 * retail loops count-1 from point1 through9, consuming exactly160 inputbytes.
 */
#include "common.h"
typedef float Vector[4] __attribute__((aligned(16)));
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_L00_002EBE88(void *, int, int, int, u32, u32, float, float, float);
extern Vector D_L00_00240080[5][10];
extern s16 D_L00_001B2990[], D_L00_001B29A0[], D_L00_001B29B0[];
extern float D_L00_001AFF8C_gp SDATA(D_L00_001AFF8C);
extern int D_L00_001AFF24_gp SDATA(D_L00_001AFF24);
extern int D_L00_001AFF20_gp SDATA(D_L00_001AFF20);
extern float D_L00_001B29D4 __attribute__((sda));

/* Five independent ten-point strands. Both previous/current point views use
 * one canonical storage declaration, preserving their true overlap. Scratch
 * index0 is unused because differences are indexed by the target point1..9.
 * The draw helper consumes exactly ten complete16-byte points including W. */
void func_L00_003C48D0(u8 *object)
{
    Vector anchor, delta[10];
    int i, j, color, alternate;
    u32 alpha;
    float numerator, ratio;
    qcopy(anchor, *(u8 **)(object + 0x68) + 0x30);
    for (i = 0; i < 5; i++) {
        if (D_L00_001B2990[i]) {
            {
                int previous_offset = i * (int)sizeof(D_L00_00240080[0]);
                int current_offset = previous_offset + (int)sizeof(Vector);
                for (j = 1; j < 10; j++) {
                    void *current = (u8 *)&D_L00_00240080 + current_offset;
                    void *previous = (u8 *)&D_L00_00240080 + previous_offset;
                    func_00282CF0(delta[j], current, previous);
                    previous_offset = current_offset;
                    current_offset += (int)sizeof(Vector);
                }
            }
            qcopy(D_L00_00240080[i][0], anchor);
            D_L00_00240080[i][0][3] = 0.03999999910593033f;
            {
                int previous_offset = i * (int)sizeof(D_L00_00240080[0]);
                int current_offset = previous_offset + (int)sizeof(Vector);
                for (j = 1; j < 10; j++) {
                    void *current = (u8 *)&D_L00_00240080 + current_offset;
                    void *previous = (u8 *)&D_L00_00240080 + previous_offset;
                    func_00282CC0(current, previous, delta[j]);
                    ((float *)current)[3] = 0.03999999910593033f;
                    previous_offset = current_offset;
                    current_offset += (int)sizeof(Vector);
                }
            }
            if (D_L00_001B2990[i] > 0) {
                numerator = func_00283CE0(D_L00_001B2990[i]);
                ratio = numerator / func_00283CE0(D_L00_001B29B0[i]);
                D_L00_001B29A0[i] = func_00283CF0(D_L00_001AFF8C_gp * ratio);
            } else
                D_L00_001B29A0[i] = 0;
        }
    }
    for (i = 0; i < 5; i++) {
        if (D_L00_001B2990[i]) {
            alpha = (u32)func_00283CF0(func_00283CE0(D_L00_001B29A0[i]) * D_L00_001B29D4) << 24;
            alternate = D_L00_001AFF24_gp;
            color = D_L00_001AFF20_gp;
            if (*(s16 *)(object + 0xAA) == 0x1192)
                color = alternate;
            func_L00_002EBE88(D_L00_00240080[i], 23, 14, 10, alpha | 0x7F7F7F, alpha | color, 0.0f, 4.0f, 0.0f);
        }
    }
}
