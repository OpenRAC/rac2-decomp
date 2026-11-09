/* 9 November 2026: corner ownership/type trial, no gain. Current master retained C
 * reproduced 740/740 bytes, frame 0x1D0, 0/6 USA v1.01 with default game G0.
 * Named x/y/z/w fields (anonymous/named struct), passing the complete corner
 * instead of its field struct, and two owning coordinate-pair fields emit the
 * same instructions as float f[4]. Only +0x224/+0x230/+0x238 differ, as before.
 * Field alias/dependency shape alone does not recover the missing sched1 slot.
 * Reopen on a new, evidenced pre-reload operation/dependency; no store-order
 * search or compiler/flag sweep was repeated. Marker restored; no linked match.
 */
/* 9 November 2026 (Sonnet s50, lesson 53): no gain, 3 words. No integer `active` literal here; tried `half = 0.5f` local (in the UV loop, before it, subtract-only, add-only) and a `one` local for the 1.0f/-1/1 corner values and the two 1.0f scale args: equal or worse (22 -> 22/43/95/173 masked). */
/* 8 November 2026 (Sonnet round s25, lesson 49 audit): re-measured 3 words. tmp[2] as two scalars 119 words, named h (kept value) 105, UV +0.5f folded into the expression 108, a kept -1 local 3 (no change). Retail's corner stores differ only at +0x224/+0x230/+0x238 (0x148 store early, 0x144 late). No gain. */
/* 8 November 2026 (Sonnet round s16, lesson 48, scripted scorer): every single corner store/clear moved to every slot between the packet setup and the vertex loop, packet state/colour/uv stores moved across the call window, and all pairwise corner-block moves (~800 compiles): none below 3 words. */
/* 8 November 2026 (Sonnet round 2, s13, ~12 check.py runs + 25 min permuter -j2, no gain): retained C re-measured 3 words. New, all still 3: h two-step (`h = skew*0.3f; h = 1-h;`) with and without a separate nh, h computed mid-block, a `third = 0.3f` local before the clears; the corner stores written exactly in retail's order: 11 (sched1 reorders). Permuter from the retained C: no score below base 30. */
/* 8 November 2026 (Sonnet round): re-measured 740/740, 3 words (+0x224/+0x230/+0x238); permuter 25 min -j2: best 1170 (base 1225) is a fake-temporary B971Packet pointer, inadmissible. */
/* 8 November 2026, region donors (v101/m8h): retail's corner-store window (+0x224..+0x238) has no matched opcode twin beyond 6 generic insns (L00_00395A88+0x128 uv stores, ascending order). Nothing to transcribe. */
/* 8 November 2026, round 16 (twin func_L14_004308D0): unchanged, 3 real words. Twin-style UV loop
 * (separate u/v cursor steps) and twin vertex loop (j = 3..0, dst/mat pointers) give identical code;
 * loop-init placement inside the corner block, natural per-corner order (with/without named h),
 * per-corner clears, a `one` local, -corners[0].f[2] for -h, and inline SetCorner(ptr, y, z[, w])
 * (frame 0x1F0) gain nothing. Flags: twin's default is ours; -G8, -g, -frac2-qcopy,
 * -fmove-all-movables, -fforce-mem/-addr, -fno-rerun-loop-opt, -fno-cse-follow-jumps: same 3;
 * -fno-force-mem 7, -fno-gcse/-fno-rerun-cse-after-loop/-fno-expensive-optimizations far worse. */
/* 8 November 2026: decomp-permuter, corner block only, 20 min -j4: best 1175 (base 1225) uses fake int temporaries and is 39 words off in check.py; no admissible gain, still 3 words. */
/* 8 November 2026, round 15: unchanged, 3 real words. sched1 dump: 0.3 and -1.0 const loads
 * are memory-typed (t23/t24), the four TImode const-0 clears are alu-typed, so t25 is
 * issue-bound and only four stores fit t26-t30. No float rounding here, so label_y/hud_coord
 * do not apply. New negatives: 0.3f*skew operand order; named h before the clears;
 * do/while groups around the early stores, around c0.w alone or c2.z alone (all reshuffle
 * s-register allocation and loop inits); a TI zero copy with -frac2-keep-block-zero-copy
 * (cse still folds the clears to const 0). */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 740/740, 3 words with the owner-allowed shared scratch type (0x1D0 frame matches; c2.z/c3.z/c2.y store order: sched1 has five free memory slots after the last call and only four stores that may fill them). */
/* 7 November 2026, round 14: unchanged, 3 real words (c2.z/c3.z/c2.y at +0x224/+0x230/
 * +0x238). The 64-byte scratch type is now allowed (owner ruling: shared with the matched
 * func_L30_0041B848); frame 0x1D0 as retail. Re-measured: sched2 has h ready at t33, so at
 * t34 both h stores and the 1.0 stores are ready and it picks by sched1 order; retail's
 * order needs the h stores ahead of c1.w/c2.y in sched1. sched1 has h at t31 and five
 * memory slots t26-t30 (t25 is issue-bound), but only four stores (c1.y, c0.y, c3.w,
 * c0.w) may come first. Four order climbs (about 3000 compiles each, plain, named h and
 * h/nh forms) stop at 3. The L30 do-while loop with explicit vertex/corner pointers gives
 * identical code. The only no-op copy (corner giv init r192 = r190, deleted by reload)
 * crosses the loop calls, so sched1 hoists it to t4; a $1-based init would anchor it
 * after the call but moves addiu s2 into block 2. h computed before the last call takes
 * f21 (wrong allocation). */
/* 6 November 2026, round 12: unchanged, 3 real words. sched1 ready lists show t25 is
 * issue-bound (2 issues: sq clear + mul), not memory-bound, so retail needs one more
 * pre-reload issue before t28 (e.g. a copy reload deletes, or a register zero with
 * memory-typed sq). A TI zero variable, chained or looped clears are all folded back to
 * const 0 by cse. No temp-slot shape found for the 48 bytes: designated/compound-literal
 * corners store in place but clear with memset (BLKmode); an inline MakeCorner returning
 * the union adds temps plus ld/sd copies (frame 0x240); an inline SetCorner(ptr) costs
 * callee-saved regs (frame 0x1F0). Also no gain: pointer/early out init loops, h = -h
 * in place (ties h and -h to one register), cast TI clears on a float[4][4]. */
/* 6 November 2026, round 10: frame now 0x1D0 like retail; 3 real words left (c2.y/c2.z/c3.z
 * store order at +0x224/+0x230/+0x238). The offset vector is the first member of the same
 * 64-byte scratch type func_L30_0041B848 uses ({angles; rotation[3]}, angles reused as the
 * size offset); its rotation[3] puts the corners at sp+0x120 as in retail. rotation is unused
 * here, so this needs a ruling before src/. sched1 model: 2 issues/cycle, one memory unit;
 * ties go by priority, then REG_DEAD weight (the last use of 1.0 is picked first), then
 * LUID. h is ready at t31 and slots t26-t30 hold five stores; retail holds four, so one
 * memory op is still missing. Store-order climbs (120 + 110 + 250 steps, with clears and a
 * named h), -fno-sched-interblock/-fno-sched-spec and do/while groups (748 bytes) gain nothing. */
/* 6 November 2026, round 9: unchanged, 3 real words (c2.y/c2.z/c3.z store order). sched1 has h ready only at t31 and four early stores to fill t26-t30, so one 1.0 store is forced at t30; retail needs one more memory op before reload. 170-step climb with a corrected metric (frame offset +0x30 masked), chained clears, corner copies and -fno-regmove/-fno-caller-saves stay at 3. The 0x1A0/0x1D0 frame gap closes only with an unused 48-byte local (rejected as padding). */
/* 6 November 2026, round 5: corner-store order 3 words off (was 5);
 * USA v1.01 default -O2 -G0 -ffunction-sections, 740/740, 0/6 places.
 * A hill-climb over the corner field stores (same values, clears first)
 * found the order below. Retail stores c2.z, c3.z, c2.y at +0x224/+0x230/
 * +0x238; this C stores c2.y, c2.z, c3.z there. Frame 0x1A0 vs 0x1D0 is
 * unchanged (48-byte gap before the corners in retail). No further gain
 * from: a named h or h/-h pair, 1-3 move climbs, moving the four clears.
 */
/* 6 November 2026: defined UV cursor storage recovers 740/740 bytes;
 * USA v1.01 default -O2 -G0 -ffunction-sections, 0/6 places. Retained, not linked.
 * Walk both UV components through the complete packet's unsigned-byte object
 * representation. Both cursors remain inside that object, including the final
 * v cursor at packet+0x74; no float-array pointer advances beyond its bound.
 * A separate UV counter and block-local v cursor recover retail's entire UV
 * loop, allocation and delay slots. The union-owned corners remain defined.
 * Remaining: frame 0x1A0 versus 0x1D0, corner/save offsets lower by 0x30, and
 * five corner-store words at +0x224..+0x238. No unused rotation array or
 * artificial stack padding was introduced to fill that independently open gap.
 * New negative trials: same-scope byte cursors 744/740; separate counter but
 * same-scope cursors 740/740 with u/v registers swapped; one union containing
 * both complete corner views ties the latter. Grouping both positive-height
 * stores gives 748/740; grouping only the first gives 748/740 and disrupts
 * preceding scheduling. Reopen on evidenced stack storage and the store DAG.
 */
/* Historical, 3 November 2026: owning vector/UV storage; still not matching.
 * Default game -O2 -G0 -ffunction-sections. US, PAL and US2 each:
 * 728/740 bytes, 0/6 places. This supersedes the historical 740-byte draft.
 * Corners use complete quadword/float unions, with each input and output
 * vertex addressed within its own array member. The copied matrix row is
 * explicitly 16-byte aligned. The unused rotation array is removed.
 * UVs are four owning pairs: the old second float cursor advanced to uv+9
 * after its last use, beyond the eight-float allocation. The pair cursor
 * instead ends at the array's one-past position. Union vertices and an
 * indexed vertex loop alone preserved the old five store-order differences;
 * the defined paired UV accesses change the body to 728 bytes.
 * Do not recover the historical size by restoring the invalid cursor or
 * crossing a float subarray. Reopen on the actual UV-loop/corner-store
 * dependence and scheduling, with complete storage and truthful interfaces.
 */
/* func_L04_0040DCA8 (740 bytes, 6 places). Tier opus-1, 28 October 2026.
 * Unit: default flags (-O2 -G0 -ffunction-sections), in L04_00402D90.c or a
 * file of its own. Best check.py: 740/740 bytes, 0/6 places, the corner
 * stores at +0x224..+0x23c in another order (5 words): retail stores
 * c2.z, c0.z, c1.w, c3.z, c1.z, c2.y; this C stores c1.w, c2.z, c0.z, c2.y,
 * c1.z, c3.z. Everything else matches (frame, allocation, the por/sq clears).
 * Retail's tail is exactly this C's statement order: sched2 keeps sched1's
 * order for ready ties, and sched1 puts c1.w (1.0, ready since the clears)
 * in the memory slot at t30 because h = 1-skew*0.3 is ready only at t31
 * (0.3 load t23, mul t25, sub t28). With the R5900 model (one memory unit,
 * two issues, TImode const-0 stores typed alu before reload) the memory unit
 * has one idle slot (t25) between the call and t31; retail's order needs a
 * second one, so no ordering of these stores reproduces it. Probably the
 * original RTL had one more pre-reload insn there (a coalesced copy, or
 * register-source clears that use the memory unit). Tried without gain:
 * chained/pointer/variable forms of the field stores, a TImode zero
 * variable (constant-propagated), an aggregate initializer (stores every
 * element, no TImode clear), -fno-schedule-insns (breaks the earlier blocks).
 * Declarations: below.
 */
#include "common.h"
typedef unsigned int B781AimQuad __attribute__((mode(TI)));
typedef union { B781AimQuad bits; float f[4]; } Corner;
extern void func_00282CF0(void *,void *,void *), func_00282F20(void *,void *,float);
extern void func_00282DD8(void *,void *,void *), func_00282D30(void *,void *,float), func_00282CC0(void *,void *,void *);
typedef struct { float u, v; } UVPair;
typedef struct { float vertices[4][4]; int colors[4]; UVPair uv[4]; long state[4]; } B971Packet;
extern void func_00281DE8(void *, int, int, int);
extern float func_00283180(float), func_00283198(float);
extern void func_002830C0(void *, void *, void *);
extern void func_002FC560(int, unsigned long long);
extern void func_00280B90(void *, int, int);
extern char D_L04_001B9680[], D_0018A0E0[];
void func_L04_0040DCA8(B781AimQuad *position, int texture, int color, int flags, float scale, float size, float angle, float skew)
{
    B971Packet packet;
    float tmp[2];
    float transform[4][4] __attribute__((aligned(16)));
    /* scratch type shared with func_L30_0041B848, allowed by owner ruling */
    struct { float angles[4]; float rotation[3][4]; } scratch;
    Corner corners[4];
    float c, sn;
    float *out;
    u8 *u;
    int i;
    func_00281DE8(&packet, texture, flags, 128);
    packet.state[0] = 5;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = color;
    packet.uv[0].u = 0; packet.uv[0].v = 0; packet.uv[1].u = 0; packet.uv[1].v = 1;
    packet.uv[2].u = 1; packet.uv[2].v = 0; packet.uv[3].u = 1; packet.uv[3].v = 1;
    c = func_00283180(angle);
    sn = func_00283198(angle);
    {
        int k;
        u8 *v = (u8 *)&packet + 0x54;
        for (u = (u8 *)&packet + 0x50, k = 3; k >= 0; k--, u += 8, v += 8) {
            tmp[0] = *(float *)u - 0.5f;
            tmp[1] = *(float *)v - 0.5f;
            *(float *)u = tmp[0] * c - tmp[1] * sn;
            *(float *)v = tmp[0] * sn + tmp[1] * c;
            *(float *)u += 0.5f;
            *(float *)v += 0.5f;
        }
    }
    qcopy(transform[3], position);
    func_00282CF0(transform[0], D_L04_001B9680, transform[3]);
    func_00282F20(transform[0], transform[0], 1.0f);
    func_00282DD8(transform[1], transform[0], D_0018A0E0);
    func_00282F20(transform[1], transform[1], 1.0f);
    func_00282DD8(transform[2], transform[1], transform[0]);
    func_00282D30(scratch.angles, transform[0], size);
    func_00282CC0(transform[3], transform[3], scratch.angles);
    corners[0].bits = 0; corners[1].bits = 0; corners[2].bits = 0; corners[3].bits = 0;
    corners[0].f[1] = -1;
    corners[3].f[2] = -(1 - skew * 0.3f);
    corners[0].f[3] = 1;
    corners[2].f[1] = 1;
    corners[1].f[3] = 1;
    corners[2].f[2] = 1 - skew * 0.3f;
    corners[2].f[3] = 1;
    corners[0].f[2] = 1 - skew * 0.3f;
    corners[1].f[2] = -(1 - skew * 0.3f);
    corners[1].f[1] = -1;
    corners[3].f[1] = 1;
    corners[3].f[3] = 1;
    for (i = 0; i < 4; i++) {
        out = packet.vertices[i];
        func_00282D30(out, corners[i].f, scale);
        func_002830C0(out, out, transform);
    }
    func_002FC560(0x47, 0x33001);
    func_00280B90(&packet, 0, 0);
    func_002FC560(0x47, 0x5360b);
}
