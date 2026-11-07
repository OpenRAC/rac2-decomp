/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 972/972, 8 rows, all in the inner texture block (retail loads the whole D_L02_001B0A00 address into a2 as a spilled hoisted address; every hoisting form breaks the setup block). */
/* 7 November 2026, final round: 972/972, USA 0/1, 8 real rows (was 10), all in the inner
 * texture block; the whole setup block now matches. Profile for the C below:
 * -O2 -G0 -ffunction-sections -fno-rerun-loop-opt (17 units use it). The separate idx statement
 * makes the D_L02_001B0A00 low part live 2 insns, so loop.c finds it "not desirable"; without
 * -fno-rerun-loop-opt the second loop pass (105 insns) still hoists it. Remaining blocker: that
 * low part stays a local pseudo in the loop ($a0, high rematerialised in $v0); retail rematerialises
 * the whole address in $a2 (band stride $v0, D_L02_002A53B0 $a1), the pattern of a hoisted, spilled
 * pseudo. Every form that hoists it (life >= 3) puts its high/lo pair in the setup block, where it
 * outranks band = 0 in sched1; then the inner block matches but setup stays at 12 lines (~25000
 * setup orders, 4 texture/index forms, 4 piece-loop orders). -mno-split-addresses fixes the inner
 * block but leaves setup at 26; -fno-gcse gives 194 rows. Reopen only on a form that hoists the
 * table address outside the setup block. */
/* 7 November 2026, round 12: 972/972, USA 0/1, 10 real rows (was 11). New setup order:
 * tex0[0..3], tex1[1], tex1[3], mode, primitive, tex1[2], tex1[0], colour chain, flags.
 * This gives retail's mode $a1, flags $a2 and band $a1; left are colour $a0/primitive $v1
 * (retail $v1/$a0) and the primitive store slot. Sched1 model (-fsched-verbose): one memory
 * insn per cycle; stores whose register dies rank first by LUID, then the hoisted ALU queue
 * high/lo D_L02_001B0A00, high/lo D_L02_002A53B0, state+0x60, then band = 0. Band lands in
 * the cycle of the sixth such store, so primitive can never still be live at band's birth
 * (needed for band to avoid $a0). Removing one hoisted chain (diagnostic only) gives retail's
 * whole setup block in 6 of 720 kill-store orders; no legitimate form found that keeps that
 * chain out of block 4: separate index temp, *(p + i), i[p], unsigned index, local table
 * pointers, phase set before the loop/branch, band = 0 hoisted (12 places), colour forms,
 * a separate texLast constant (diagnostic), -mno-split-addresses (48 rows). 6000 random
 * 12-statement orders never reach colour $v1/primitive $a0/band $a1; hill-climb from here
 * stays at 10. Reopen on evidence that retail kept one table address out of the pre-header. */
/* 6 November 2026 (round 11c, prototype audit): every callee prototype agrees with its matched C in src or the established asm prototype; void helpers never write $v0; every int/float/pointer result is read. No correction to test. */
/* 6 November 2026, Codex round 11: retained C unchanged, 972/972 bytes,
 * USA v1.01 0/1 places, 11 real instruction differences; final baseline diff
 * is identical to the initial baseline. 46 candidate checks tested whole-file
 * scheduling/CSE options and distinct real initialization forms, without
 * instruction patches or artificial accesses. Counted differences exclude
 * symbol relocations; rows from unequal-size bodies are not improvement scores.
 * Three four-color fill loops emit 1012 bytes normally, 980 with unrolling.
 * Duplicating selected constant packet assignments in both arms of the existing
 * flip branch (15 subsets) emits 980-1028 bytes. A genuine four-member color
 * struct ties at 11 rows; a compound-literal assignment emits 988 bytes and
 * assignment from an initialized local color struct emits 1020. No source
 * form improves the retained 11-row result. -fno-sched-spec, -fno-cse-follow-jumps,
 * -fno-cse-skip-blocks, -fno-strength-reduce and -fno-thread-jumps also tie;
 * -fno-force-mem, -fno-gcse and -fno-rerun-cse-after-loop enlarge the body.
 * Remaining blocker: color/primitive local-allocation priority and packet-store
 * scheduling. Reopen on independently evidenced packet initialization/lifetimes,
 * rather than more permutations of the same scalar assignments.
 */
/* 6 November 2026, round 10: unchanged, 11 real rows. -fno-sched-interblock ties (11) on this
 * and all five earlier forms; -fno-schedule-insns (alone or with it) gives 92. Local-alloc ranks
 * primitive (2 refs, 4-insn span after sched1) just above colour (7 refs, 30-insn span). Order
 * searches (~3400 compiles, chained or split colour, band = 0 hoisted) reach colour $v1/primitive
 * $a0/mode $a1/flags $a2 (best 24 rows), but then band always takes $a0, never retail's $a1: the
 * primitive store never lands after sched1's band init. */
/* 6 November 2026, Codex worker: best unchanged, 972/972, 0/1 USA, 11 real
 * instruction differences, excluding relocations. 148 new variants: all 78
 * contiguous one-pass groups of the 12 packet-setup statements (best 43 rows),
 * 24 colour/primitive local initializations with and without one-pass groups,
 * 16 logical packet-initializer helper variants, six shared complemented-U
 * lifetime forms, and 24 reuses of band/piece/tile for the earlier real colour
 * or primitive value. None improves the retained source. Allocator diagnostics
 * reproduce the baseline object and identify colour/primitive as local allocations
 * (SI pseudo 104 in a0, DI pseudo 101 in v1); the loop spills already agree.
 * No donor with the distinctive strip-width/scaling constants was found in the
 * current RAC1/RAC4 sources. Final baseline check reproduces all 11 differences.
 */
/* 6 November 2026, round 9: 972/972, 0/1, 11 real rows (18 before, counting stack-offset
 * rows that the earlier "11" ignored). Writing phase inside the band loop
 * (`float *phase = (float *)(state + 0x60)`) lets gcse hoist it into a late pseudo, so
 * reload gives stride/band/phase retail's 0x160/0x164/0x168 slots; `off = band * 4`
 * gives retail's addu operand order. Left: colour $a0/primitive $v1 (retail $v1/$a0) and
 * the packet store order. Putting colour before primitive (needed for $v1) moves mode,
 * primitive and band registers (19-33 rows). Hill-climbs over declarations and setup
 * order (~450 runs, chained or split colour stores) and band types tie or worsen. */
/* 6 November 2026, lead: hill-climb over the packet setup order (60 runs) cuts real instruction differences from 20 to 11; the band loop registers now match. Left: colour constant in $a0 (retail $v1), primitive in $v1 (retail $a0), band/phase stack slots 0x160 vs 0x168 and their store order. Split colour stores, a grey local, declaration orders and -freduce-all-givs/-fno-rerun-loop-opt/-fexpensive-optimizations tie at 11. Source below is the 11-row form. */
/* 6 November 2026, round 3: unchanged, 972/972, 0/1, 22 rows. Slot order here is
 * phase 0x160, stride 0x164, band 0x168; retail is stride, band, phase. Writing phase[band]
 * inline from state (four forms, no phase local) gives 61 rows. A hill-climb over the
 * declaration order (60 orders) stays at 22. Original best C retained.
 */
/* 6 November 2026: 972/972, 0/1 USA, 22 rows (was first diff +0x7C). `state = ...; flip = 0.0f;`
 * (flip set after the state load) fixes the lhu/andi/mtc1 order. This source order gives retail's
 * colour register ($v1) and its whole packet store order. Left: mode $a0/primitive $a1/band $a0
 * (retail $a1/$a0/$a1), and the phase spill slot 0x160 (retail 0x168, above stride 0x160 and
 * band 0x164). Local-alloc needs colour > primitive > mode. A hill-climb over the setup order
 * (about 500 orders) only trades this for colour/primitive $a0/$v1 (16 rows). Declaring band
 * before phase, and phase inside the loop (folds 0x60 into lwc1), do not move the slot.
 * Colour chain/split/local forms all tie.
 */
/* Retained reconstruction, updated 2 November 2026; not a linked match.
 * Profile: -O2 -G0 -ffunction-sections.
 * Current US check: 972/972 bytes, 0/1 placements, first difference +0x7C.
 * The faithful assignment of the complete aligned 192-byte StripGeometry now
 * emits retail's full lq/lq/sq/sq/addiu/bne/addiu copy loop without padding.
 * This supersedes the earlier block-copy refusal: the maintained compiler's
 * block_move_quad support is the independently verified changed input.
 * The 0x200 frame and prologue/copy through +0x78 agree. Remaining differences
 * include flag-mask/float-zero scheduling, mode/primitive register allocation,
 * phase spill at 0x160 rather than 0x168 and band/texture-loop address lifetimes.
 * A real flag snapshot and primitive-before-mode assignment still gave 972
 * bytes and 0/1, changed packet allocation without improving it, and were
 * reverted. Two bounded checks; US2/PAL not rerun for this nonmatching body.
 * Reopen on independent packet-field and phase/loop lifetime evidence.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { float point[3][4][4]; } StripGeometry __attribute__((aligned(16)));
typedef struct {
    float corner[4][4];
    unsigned int color[4];
    float tex0[4];
    float tex1[4];
    unsigned long long primitive, texture, mode, flags;
} StripPacket __attribute__((aligned(16)));
extern StripGeometry D_L02_002A52F0;
extern int D_L02_002A53B0[3][9];
extern int D_L02_001B0A00[];
extern unsigned long long func_0027C878(int);
extern int func_00283CF0(float);
extern void func_00282D08(void *, void *, void *, float);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern void func_00280B90(void *, void *, int);

void func_L02_003E7B58(char *actor) {
    StripGeometry geometry;
    StripPacket packet;
    char *state;
    float flip;
    float sample[4] __attribute__((aligned(16)));
    int band, piece;
    geometry = D_L02_002A52F0;
    state = *(char **)(actor + 0x68);
    flip = 0.0f;
    if (*(unsigned short *)(actor + 0x34) & 0x8000) flip = 1.0f;
    packet.tex0[0] = flip;
    packet.tex0[1] = 0.0f;
    packet.tex0[2] = 1.0f - flip;
    packet.tex0[3] = 0.0f;
    packet.tex1[2] = 1.0f - flip;
    packet.tex1[1] = 1.0f;
    packet.tex1[0] = flip;
    packet.tex1[3] = 1.0f;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = 0x7F7F7F7F;
    packet.mode = 0xFF9000000260ULL;
    packet.primitive = 5;
    packet.flags = 0x8000000000ULL;
    for (band = 0; band < 3; band++) {
        int off = band * 4;
        float *phase = (float *)(state + 0x60);
        float scroll = *(float *)((char *)phase + off) + 0.15f;
        for (piece = 0; piece < 3; piece++) {
            float first = ((float)func_00283CF0(scroll) - scroll) * 0.43094158f;
            int tile;
            float last;
            float texFirst;
            float texLast;
            first += (float)piece * 0.43094158f;
            tile = func_00283CF0((scroll + (float)piece - 1.0f) + 9.0f) % 9;
            last = first + 0.43094158f;
            {
                int idx = D_L02_002A53B0[band][tile];
                packet.texture = func_0027C878(D_L02_001B0A00[idx]);
            }
            texFirst = 0.0f;
            texLast = 1.0f;
            if (last < 0.1f || first > 0.9f) continue;
            if (first < 0.1f) {
                texFirst = (0.1f - first) * 2.3205001f;
                first = 0.1f;
            } else if (last > 0.9f) {
                texLast = (0.9f - last) * 2.3205001f + texLast;
                last = 0.9f;
            }
            packet.tex0[1] = packet.tex0[3] = texFirst;
            packet.tex1[1] = packet.tex1[3] = texLast;
            func_00282D08(sample, geometry.point[band][0], geometry.point[band][2], first);
            func_L01_0031A278(actor, packet.corner[0], sample[0], sample[1], sample[2]);
            func_00282D08(sample, geometry.point[band][1], geometry.point[band][3], first);
            func_L01_0031A278(actor, packet.corner[1], sample[0], sample[1], sample[2]);
            func_00282D08(sample, geometry.point[band][0], geometry.point[band][2], last);
            func_L01_0031A278(actor, packet.corner[2], sample[0], sample[1], sample[2]);
            func_00282D08(sample, geometry.point[band][1], geometry.point[band][3], last);
            func_L01_0031A278(actor, packet.corner[3], sample[0], sample[1], sample[2]);
            func_00280B90(&packet, 0, 0);
        }
    }
}
