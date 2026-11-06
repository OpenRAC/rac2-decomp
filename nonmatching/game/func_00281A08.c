/* 7 November 2026, decomp-permuter: not usable here: with -g the permuter's reprinted C changes line notes (base 296 rows off, score 5520), so no result. Setup: /tmp/claude-1000/-home-lynder063-rac2-decomp/lead/work/perm. */
/* 6 November 2026 (round 11): gcse expr-table size is not the fix. Upstream 2.95.3
 * alloc_expr_hash_table (max_cuid/2 |1) equals this tree. Forcing the size to every odd
 * 11..301 matches here only at 23 or 47 (7/7; = max_cuid/8 or /4), but max_cuid/4 forced
 * on changes 203 of 8597 units (/8: 242), and sampled matched ones break (00119BF8 1->0/1,
 * func_002B88F0 28->0/28). Falsified as a compiler difference.
/* 6 November 2026 (round 12): fuller-source probes do not improve five words.
 * USA v1.01, v2.00 and PAL each replay at 980/980 bytes, 0/7 places, with
 * the profile below. Whole-union/struct translation copies, vector-by-value
 * or return helpers, complete frame helpers and indexed packet initialization
 * change allocation/size; a direct TI-pointer copy helper ties the baseline.
 * Measured fuller forms have 184..195 real pre-gcse insns (93..97 buckets),
 * not the roughly 230 needed by the earlier bucket model. No new donor C was
 * identified in the current RAC1/RAC4 sources. Retain this source unchanged;
 * reopen on a genuinely different operation or PRE expression/lifetime.
 * No linked build was run (worker checks only).
 */
/* 6 November 2026 (round 10): still five words. Measured: the PRE table size
 * stayed 89..97 buckets over ~7,000 generated equivalent forms (pointer/index
 * packet and uv forms, struct or .bits translation copy, ring/cur/clamp forms,
 * shared or separate loop counters, scoped step, blend as first parameter),
 * 19 cse/loop/address flags and -G0..-G64 (all 93), and an inlined frame
 * helper (93). In that window only 97 buckets put matrix before &matrix[3],
 * and there half (bucket 64) falls before &matrix[3] (86), so the bucket model
 * cannot give retail order without ~45 more pre-gcse insns. A single one-pass
 * group at each of 164 placements (top or scoped step) gives no gain. The
 * D_001A89E0_gp SDATA view is the reviewed header macro, not a #define alias.
 */
/* 6 November 2026 (round 8): declaring `step` right after `ring` leaves five
 * words, all one swap: retail step+1 0x964 / &matrix[3] 0x96C, ours reversed.
 * Slots follow gcse PRE reaching-register order = expression-hash bucket order
 * (gcse dump): &matrix[3] (plus fp 2352) bucket 14, matrix (plus fp 2304) 59,
 * step+1 81, half 86 with a 93-bucket table (max_cuid ~186). Retail order
 * step+1 < matrix < &matrix[3] < half needs matrix before &matrix[3], which no
 * table of 61..113 buckets gives; 115 or 119 buckets (~230-240 pre-gcse insns,
 * +45) do. Block-scoped `step` already puts step+1 before matrix. 70-step
 * declaration hill-climb, step reusing k, unsigned step, matrix pointer locals,
 * inline transform/packet helpers and -frac2-gcse-unsplit-edges /
 * keep-block-order / hazard-labels gave nothing better.
 */
/* 6 November 2026: current game compiler, isolated unit with the profile below:
 * 980/980 bytes, 0/7 in each of USA v1.01, USA v2.00 and PAL. The current
 * retained draft differs at eight non-relocated words, all PRE spill offsets
 * (the older ten-row count below is superseded by this replay).
 * New trials: qcopy for either/both matrix translation transfers ties; scoped
 * step/all loop indices, an explicit pair count, and a zero-based outer step
 * change allocation without matching. One-pass groups around the initial
 * transform, packet setup, outer loop or translation copy give 976-1004 bytes
 * or earlier allocation differences. No trial improves the retained source.
 * Reopen with a measured PRE expression/lifetime change that fixes slot order.
 */
/* Claude Opus 5.5, task v2193; NOT MATCHING.
   Own unit, flags: -O2 -G8 -ffunction-sections -g -frac2-qcopy -frac2-qcopy-barrier
   check.py: 0 of 7 places; 980/980 bytes, frame 0xA00 matches. Only 10 rows
   differ, all spill-slot offsets of four gcse PRE registers: ours trans 0x964,
   matrix 0x968, half 0x96C, step+1 0x970; retail step+1 0x964, matrix 0x968,
   trans 0x96C, half 0x970. Bucket model (raw step+1 = 14030+step regno,
   half = 14044+85, matrix 16334, trans 16382; T = 93 now): matrix before trans
   needs T 85 or 97, and then step/half bases near pseudo 130/110, so retail
   probably differs in structure (half or step+1 not a pass-1 PRE register).
   colors[0] before colors[1] keeps sched1's dead-base preference off the
   other stores (retail store order). -G8 + SDATA view gives GP .u loads and
   the incomplete sda array keeps .v absolute; declarations below.
*/

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 bits; float f[4]; } UiVector;
typedef struct { UiVector vertices[4]; unsigned int colors[4]; float uv[4][2];
                 u64 primitive, texture, state, flags; } UiDrawPacket;
extern float func_00283CE0(int);
extern unsigned int func_00283D38(int, int, float);
extern u64 func_0027C878(int);
extern void func_002839D0(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, int, int);
extern int D_001A89D0 __attribute__((sda));
extern int D_001A89D4 __attribute__((sda));
extern int D_001A89D8 __attribute__((sda));
typedef struct { float u, v; } UiTexCoord;
extern UiTexCoord D_001A89E0[] __attribute__((sda));
extern UiTexCoord D_001A89E0_gp[] SDATA(D_001A89E0);

void func_00281A08(UiVector *vertices, int vertex_count, UiVector *positions,
                   UiVector *rotations, int phase, int steps,
                   int first_color, int last_color, float blend)
{
    UiDrawPacket packets[16];
    UiVector matrix[4];
    int ring, step, i, j, k, n, v, cur;
    float increment, t;
    unsigned int color;

    if (steps < 2)
        return;
    ring = 2;
    increment = 1.0f / func_00283CE0(steps - 1);
    t = increment * blend;
    color = func_00283D38(first_color, last_color, increment);
    for (i = 0; i < (vertex_count >> 1); i++) {
        packets[i].texture = func_0027C878(D_001A89D0);
        packets[i].state = 0xFF9000000260UL;
        packets[i].primitive = 5;
        packets[i].flags = ((long)D_001A89D4 << 2) | ((long)D_001A89D8 << 6) | 0x8000000000UL;
        packets[i].colors[0] = color;
        packets[i].colors[1] = color;
        for (j = 0; j < 4; j++) {
            packets[i].uv[j][0] = D_001A89E0_gp[j].u;
            packets[i].uv[j][1] = D_001A89E0[j].v;
        }
    }
    cur = phase;
    func_002839D0(&rotations[cur], matrix);
    matrix[3].bits = positions[cur].bits;
    matrix[3].f[3] = 1.0f;
    for (k = 0; k < vertex_count; k++)
        func_002830C0(&packets[k >> 1].vertices[k & 1], vertices + k, matrix);
    for (step = 1; step < steps; step++) {
        unsigned int next_color;
        cur = (cur + steps - 1) % steps;
        func_002839D0(&rotations[cur], matrix);
        matrix[3].bits = positions[cur].bits;
        matrix[3].f[3] = 1.0f;
        next_color = func_00283D38(first_color, last_color, t);
        t += increment;
        if (t > 1.0f)
            t = 1.0f;
        for (v = 0; v < vertex_count; v++) {
            func_002830C0(&packets[v >> 1].vertices[ring + (v & 1)], vertices + v, matrix);
            packets[v >> 1].colors[ring + (v & 1)] = next_color;
        }
        ring = (ring + 2) % 4;
        for (n = 0; n < (vertex_count >> 1); n++)
            func_00280B90(&packets[n], 0, 1);
    }
}
