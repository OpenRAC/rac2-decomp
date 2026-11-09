/* 9 November 2026 (o121, set-once constant locals ruling): separate locals per use with store-matched types (u8/u16/s16/int/unsigned for QI 255, HI 255, 0x100), as function-scope initialiser, block declaration, block top or at the use, x all 6 store orders (29,478 compiles, local cc1 scorer): every 255 local of any type is merged by cse (484 bytes); best 488-byte form is still 4 rows (0x100 local, as o114). No check.py run. */
/* 9 November 2026, full-width field and defaults-record follow-up:
 * Game -O2 -G0 -ffunction-sections -g, unchanged compiler/assembler.
 * Checked 132 new C variants in the build container. Full-width bit-fields
 * on each nonempty subset of the three real header fields, both draw-distance
 * signednesses and all six store orders: 84 variants, 42 at 488 bytes and
 * 42 at 484 bytes; none improves the five differing nonrelocated words.
 * A three-field defaults record (u8 update distance, s16/u16 draw distance,
 * u16 flags), all six declaration orders, with aggregate/field initialization
 * directly or through an inline returning constructor: 48 variants, 504-644
 * bytes. These records retain stack/copy work, not a useful constant lifetime.
 * Original C rechecked: 0/3 places in each of us, pal and us2. No linked build.
 * Retain the original reconstruction; a full-width field model alone does not
 * explain retail's split constant/store ordering. No one-field local used.
 */
/* 9 November 2026 (o114, set-once constant sweep after func_L06_00382608): scripted every set-once int local for the 0x100/QI 255/HI 255 constants (singly, pairs, shared 255), at every position among the five header statements and before the if (about 9,000 compiles, local cc1 scorer): best 4 rows (check.py 0/3 us, pal, us2): `kA = 0x100;` first, then the byte store, then `*(u16 *)(object + 0x34) = kA;`, then the 0x32 store (constants 256, QI, HI; stores 0x30, 0x34: sched1 still breaks the constant tie by LUID). Any int local for a 255 merges both 255s in cse (484 bytes). Retail needs QI 255 first with the 0x34 store first: a store-side key (0x34 store priority/dependents or a live QI value at the 0x30 store), not a constant placement. */
/* 9 November 2026 (o109): still 5 rows (0/3). Lesson 54: func_L09_003364E0 is defined (char *, int, float, u32, float, int); the C below now uses that prototype: identical code. sched1 deps explain the tie: each constant's dependents are {231 block end, 58 qcopy asm (sets_all), own store}; each store's are {231, 80 = sched_before_next_call anti dep (value pseudo crosses no call), 58}. QI-before-256 needs prio(st30) > prio(st34), which also puts st30 first; so only key 5 can split them, and that needs a 4th dependent (another use of the QI pseudo, or a load overlapping 0x34 before the qcopy) that retail does not have. Tried *(u8 *) (no /s), QI-first source order, signed char -1 / short forms: same or worse order. */
/* 9 November 2026 (o75, dump-driven): deciding pass sched1 (.sched, block after `if (object)`). Constants 35 (HI 256), 40 (QI 255), 45 (HI 255) tie on every key: prio 44, weight 1, class 3, 3 dependents each ({231, 58 qcopy, own store}); stores 37/42/47 tie too (prio 43, weight 0, deps {231,80,58}), so LUID decides both and the constant order equals the store order. Retail's regs (QI a0, 256 v0, HI v1) and its slot `li a0` need sched1 order QI, 256, HI, st34, st30, st32: local-alloc then gives 256 len 2, HI 3, QI 4 (retail's order), and reorg takes the first insn (QI) for the beqz slot. That needs the QI constant ahead of its own store's LUID rank (a 4th dependent on st34 or QI const, or weight 0 on QI const); no plain store gives it. Every scalar 255 local is promoted to SI and cse's wider-mode lookup merges the HI 255 (484 bytes). Checked here: -frac2-qcopy, qcopy-barrier, zero-ti-por, keep-block-order, -fno-sched-interblock, qcopy_nc on either copy: same order; -fno-schedule-insns worse. */
/* 9 November 2026, typed-header follow-up: a complete measured object view
 * (state, update/draw distances, flags, state pointer, rotation fields) gives
 * the same five flag words at 488 bytes. An inline three-field initializer
 * with u8/s16/u16 parameters merges the two 255 constants: 484/488 bytes.
 * A static const three-field defaults record retains memory loads: 496/488.
 * Baseline RTL keeps separate QI 255 and HI 255 through cse2; sched1 orders
 * HI 256, QI 255, HI 255, rather than retail's QI 255, HI 256, HI 255.
 * Baseline rechecked in the build container: 0/3 places in us, pal and us2.
 * No linked build; original reconstruction and assembly marker retained.
 */
/* 9 November 2026 (Sonnet round s44, lesson 52): scripted a nonempty do { real_op; } while (0) group around every 1-3 consecutive statements of the body (436 variants, each also with -frac2-sticky-volatile-refs, -frac2-hazard-labels and both): no variant scored below base (same diff rows, masked and unmasked); the switches alone change nothing here. */
/* 8 November 2026 (Sonnet round s33, lesson 49): `angle` is a fake local (retail passes f0/f12 straight on): removing it for the 0xf4 store is identical (5 rows); removing it for the divide gives 480 bytes (lost nops before div.s). `lifetime` is real (v0 across the 0x24 store). Same five constant/store rows; struct local still banned. */
/* 8 November 2026, twin search: transcribing matched twin func_L09_003AE8C8 (its unit flags -O2 -G8 -ffunction-sections -g; state loaded first, byte 255 then signed short 256) adds nothing: the twin has no halfword 255 at 0x32, and its retail stores the byte first. All six orders of the three header stores in that spelling give 5 rows or more (best 0x34, 0x30, 0x32: byte constant still lands in $v0, not $a0); one-pass groups around each store and an int 255 local give 5 rows or worse. */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss. Final state: exact (3/3 in us, us2, pal) only with a one-field struct local that keeps cse from merging two 255 constants; the owner ruled that construct out, so it stays a held near miss. */
/* 6 November 2026, round 9: exact (3/3 in us, us2, pal; own -O2 -G0 -ffunction-sections -g unit) when the byte flag at 0x30 is stored from a local `struct { unsigned short value; } mark` set to 255 before the 0x34 store and the halfword at 0x32 from an `int half = 255` after it: cse2 then keeps the two 255 constants apart as retail does. A plain `unsigned short mark` gives 0/3. Held, not landed: the one-field struct exists only to steer cse, so it needs a maintainer ruling (compare blocker 26). */
/* 6 November 2026, round 3: unchanged, 488/488 bytes, 0/3 places, 5 rows.
 * All 120 orders of the three header stores, the state load and the 0x20 store,
 * with and without -frac2-qcopy, give 5 rows or more. sched1 issues two ALU
 * insns per cycle; the three constants tie on priority, so luid order decides,
 * and stores follow the same order. Retail needs the byte constant first but
 * the 0x34 store first: that needs a priority difference no plain store gives.
 * A byte local set before the stores merges with the halfword 255 (484 bytes).
 */
/* 6 November 2026: current game compiler, -O2 -G0 -ffunction-sections -g:
 * 488/488 bytes, 0/3 places in each release; five flag setup words remain.
 * New one-pass groups around individual/adjacent header writes either tie
 * or worsen the constant/store order. Grouped byte-constant initialization,
 * before or inside the null guard with char/int locals, also does not improve.
 * Retain the existing C; reopen with a measured constant lifetime explanation.
 */
/* 6 November 2026: on the current compiler, still 5 rows. Retail makes the byte 255, then 0x100,
 * then the halfword 255, but stores +0x34, +0x30, +0x32. Signed short stores in that store order
 * (as matched spawners write them) give 5 rows; the +0x30/+0x34/+0x32 order gives retail's
 * constant order but 6 rows; a struct view of the header ties; without -g about 43 rows differ. */
/* 5 November 2026: Scoped byte/word flag locals merge constants and give 484/488 bytes. Grouping the real header writes keeps 488 bytes but the same five flag constant/store words still differ. No variant is promoted.
 */
/* Retained nonmatching reconstruction, 27 October 2026.
 * Profile: -O2 -G0 -ffunction-sections -g. Candidate and retail: 488 bytes. USA v1.01, USA v2.00 and PAL each reject all three carrying places. Only five initial flag constant/store words differ: the byte and halfword 255 constants take different registers/order. The later spawn, vector operations, division hazards, stores and return agree. Reordering the stores either changes their order or merges the constants. A separately tested partial object-header view tied. Reopen with a measured allocation explanation; no volatile or artificial dependencies.
 */
#include "common.h"
extern void *func_0029EFD0(int);
extern float func_00283248(float, float);
extern float func_00282E20(void *);
extern char *func_L09_003364E0(char *, int, float, unsigned int, float, int);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DF0(void *);
extern int func_00283CF0(float);
extern int func_002E5CF8(int, int, char *);
extern char D_0018A0E0[];
char *func_L18_0043FFF8(void *position, char *owner, float *direction,
                       int kind, int flags, float x, float y, float z)
{
    char *object = func_0029EFD0(0x1263);
    char *state;
    float angle;
    int lifetime;
    if (object) {
        *(unsigned short *)(object + 0x34) = 0x100;
        ((unsigned char *)object)[0x30] = 255;
        *(unsigned short *)(object + 0x32) = 255;
        state = *(char **)(object + 0x68);
        object[0x20] = 0;
        qcopy(state, direction);
        qcopy(object + 0x10, position);
        *(float *)(object + 0xf8) = func_00283248(direction[0], direction[1]);
        angle = func_00282E20(direction);
        *(float *)(object + 0xf4) = -func_00283248(angle, direction[2]);
        *(char **)(state + 0x30) = func_L09_003364E0(object, -1, 0.1f, 0xf0208080, 0.01f, 0x60);
        *(float *)(state + 0x1c) = y;
        qcopy(object + 0xc0, state);
        func_00282DD8(object + 0xd0, object + 0xc0, D_0018A0E0);
        func_00282F20(object + 0xd0, object + 0xd0, -1.0f);
        func_00282DD8(object + 0xe0, object + 0xd0, object + 0xc0);
        angle = func_00282DF0(direction);
        angle = *(float *)(state + 0x1c) / angle;
        lifetime = func_00283CF0(angle);
        *(float *)(state + 0x24) = z;
        *(int *)(state + 0x34) = lifetime;
        *(float *)(state + 0x20) = x;
        *(int *)(state + 0x28) = kind;
        *(int *)(state + 0x2c) = flags;
        *(char **)(state + 0x10) = owner;
        if (*(short *)(owner + 0xaa) == 0xee1)
            func_002E5CF8(5, 0, owner);
        object[0x31] = 0;
        *(unsigned short *)(object + 0x34) |= 1;
    }
    return object;
}
