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
extern void func_L00_002EBE88(void *, int, int, int, int, int, float, float, float);
extern Vector D_L00_00240080[][10];
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
            for (j = 1; j < 10; j++)
                func_00282CF0(delta[j], D_L00_00240080[i][j], D_L00_00240080[i][j - 1]);
            qcopy(D_L00_00240080[i][0], anchor);
            D_L00_00240080[i][0][3] = 0.03999999910593033f;
            for (j = 1; j < 10; j++) {
                func_00282CC0(D_L00_00240080[i][j], D_L00_00240080[i][j - 1], delta[j]);
                D_L00_00240080[i][j][3] = 0.03999999910593033f;
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
