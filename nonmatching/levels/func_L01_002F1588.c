/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 768/768, 2 words with the owner-allowed dead-test helper (icon block delay slots swapped; sched1 ties a0=0xEAA7 / a1=count-1 and cse folds any temp back to a constant). */
/* 7 November 2026, round 14: unchanged, 768/768 bytes, 0/5 USA, 2 words off (icon
 * block beqz/jal slots). The dead-test helpers are allowed by owner ruling. Why the slots
 * swap: sched1 ties a0 = 0xEAA7 and a1 = count - 1 on priority, then picks the lower
 * INSN_REG_WEIGHT (a1: 0, the count dies; a0: 1). reorg fills the jal slot first from the
 * insn before it, then the beqz slot from the fall-through, so the sched1 order decides.
 * Proof: passing the count as `active` to the icon block's top rounding keeps it live,
 * and both slots become retail's, but the count then crosses the call and moves to a
 * saved register (lw s0, 7 words off). cse always folds a 0xEAA7 temp (CONST_COSTS is 0),
 * so a0 cannot kill a pseudo. No gain: inline icon wrapper in either parameter order;
 * hud_round in the precedent form (display-mode load) gives 30 rows (x2 copied early).
 * unit/zero copies through `height` are live copies, not dead stores; hud_camera() is
 * an inline accessor, not a reload.
 */
/* 6 November 2026, round 10: 768/768 bytes, 0/5 USA, still 2 words off. The round-9
 * second `camera = D_L01_001BD9C0;` was a redundant reload (the address is a link-time
 * constant; nothing in between can change it). Now an inline accessor `hud_camera()`
 * is used at all three sites, no camera local: same code (s2 = %hi, %lo again at the
 * end). Writing the global directly, or a local set once, gives 760 bytes (full
 * address kept in s2). Icon block: confirmed in the sched dump that sched1 picks
 * `a1 = count - 1` first only because the count dies there (INSN_REG_WEIGHT 0 vs 1 for
 * a0 = 0xEAA7); with the count kept live the order flips (diagnostic, extra code).
 * No gain: count in y/entry/x2/top/bottom, count reused as the call result, nested
 * call, 0xEAA7 in a variable before the if (cprop folds it back, also with
 * -fno-gcse), and flags -fno-sched-interblock, -fno-sched-spec, -fno-cse-follow-jumps,
 * -fno-thread-jumps, -frac2-keep-block-order, -frac2-hazard-labels, -frac2-zero-ti-por,
 * -frac2-gcse-unsplit-edges, -frac2-keep-block-zero-copy, -g (all 2 words or worse).
 */
/* 6 November 2026, round 9: 768/768 bytes, 0/5 USA, 2 words off (was ~25). Own unit
 * src/levels/shared/L01_002F1588.c, -O2 -G0 -ffunction-sections (gcse ON, no -fno-gcse).
 * Missing word was retail's second `addiu v0,s2,%lo(D_1BD9C0)`: s2 holds only the %hi,
 * shared by gcse across the draw blocks, so `camera = D_L01_001BD9C0;` again before the
 * restore. gcse cprop of unit/zero is stopped by copying them from `height` and
 * reassigning height in the same block (the copies are then not available at block end).
 * Rect/icon roundings use a check without a load (`result == active`), so the call
 * results (x2, icon) get $v0 and are copied late, as in retail.
 * Left: icon block only, beqz/jal delay slots swapped (retail ori a0,0xEAA7 in beqz slot,
 * addiu a1,a1,-1 in jal slot). Cause: sched1 picks `a1 = count - 1` first because it
 * kills the count pseudo (lower INSN_REG_WEIGHT). No gain: local count, --count, inline
 * wrapper, `+ -1`, int temp for 0xEAA7 or for count - 1, -frac2-sticky-volatile-refs.
 */
/* 6 November 2026, round 5: best body below (764/768, 0/5 USA, ~25 words off after
 * alignment, was ~44). Own unit src/levels/shared/L01_002F1588.c, -O2 -G0
 * -ffunction-sections -fno-gcse. New: the top/bottom (and icon) roundings share one
 * `height = D_L01_001B2DC4[0]` load (retail lwc1 f1 once, mul f1*k, cvt into f2).
 * Left: %hi(D_1BD9C0) in $s2 (one word), the f21 = 0.5 placement, and the icon block's
 * a0/a1 delay-slot order (local `entry` for the count is worse). Finding: with gcse on,
 * `camera = D_L01_001BD9C0;` again before the final store gives retail's exact camera
 * code (daddu s2 = %hi, addiu %lo at both ends, ghost s0, s1 = 0x8710), but gcse
 * const-prop (gcse.c cprop_insn) still turns unit/zero into per-draw constants (frame
 * 0x60). Copy chains (`h = 1.0f; unit = h;`) do not stop it; fewer helper branches
 * under -fno-gcse do not let cse share the %hi.
 * Also no gain: a do/while(0) group around unit/zero with gcse on (still propagated),
 * and a 250-run hill-climb over the constant-assignment order (stays at ~25 words).
 */
/* Nonmatching interface overlay reconstruction, 2026-10-28. No C credit.
 * Four US checks, 0/5. Retained 736/768B, frame0x70 exact, with -O2 -G0
 * -ffunction-sections. First diagnostic728B had rectangle-top375 rather
 * than the actual later374; retained code corrects that constant. Explicit
 * coordinate/factor lifetimes and narrow unsplit edges give736B; broad
 * -fno-gcse and one truthful bank-equivalent interleaving are identical.
 * Three forms converge. Canonical actual object/flags/five-FP declaration
 * is retained, with no useless profile option. Remaining: camera high-half
 * lifetime and saved GPR versus extra saved FP, literal250 retention, FP
 * conversion/call scheduling and projection restore order.
 * Reopen with independent original source/lifetime evidence.
 *
 * Actual callback user002F14E8 confirms int(void); each exit returns the
 * GP control word. Actual00336D50 returns signed32 address, explicitly
 * cast; actual00300A00 takes a0 object,a1 flags and f12..f16 five floats,
 * returns void. Actual0028E588 returns int and0028E868 returns void.
 * Actual0027EAE8 forwards its color pointer to actual0027EA28, which reads
 * exactly two32-bit words. Both words are assigned before the full8B struct
 * copy and drawing call; no third color or unstored padding is consumed.
 * Raw-only0027AB40 mutation/return interface remains provisional.
 * Unknown external data extents are incomplete; scalar float-to-int casts
 * naturally reproduce the observed cvt.w.s mechanism without handwritten asm.
 */

#include "common.h"
typedef struct { int first, second; } OverlayColorPair;
extern unsigned char *D_L01_001A908C __attribute__((sda));
extern unsigned char D_L01_0027EAC8[];
extern int D_L01_001A90D0[] SDATA(D_L01_001A90D0);
extern int D_L01_001A90CC[] SDATA(D_L01_001A90CC);
extern float D_L01_001A90C4[] SDATA(D_L01_001A90C4);
extern float D_L01_001B2DC4[] __attribute__((sda));
extern unsigned char D_L01_001BD9C0[];
extern void func_0027AB40(void);
extern int func_00336D50(void *, int);
extern void func_00300A00(void *, int, float, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_0027EAE8(int, int, int, int, int, const void *);
extern int func_0028E588(int, int);
extern void func_0028E868(int, int, int, int, int, int);

extern int D_L01_001B2DC0[] __attribute__((sda));

/* dead-test helper allowed by owner ruling (master precedent: src/game/002D2188-g8.c) */

static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && D_L01_001B2DC0[0] == active)
        scaled = 1.0f;
    return result;
}

static __inline__ int hud_round(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && result == active)
        scaled = 1.0f;
    return result;
}

static __inline__ unsigned char *hud_camera(void)
{
    return D_L01_001BD9C0;
}

int func_L01_002F1588(void)
{
    OverlayColorPair colors, source;
    float oldProjection, span, rounding, unit, zero, height;
    int top, bottom;
    unsigned char *node;
    int x2, y, one, entry;
    if (!D_L01_001A908C || *(int *)D_L01_0027EAC8 || *(int *)(D_L01_0027EAC8 + 0x24) != -1)
        return D_L01_001A90D0[0];
    oldProjection = *(float *)(hud_camera() + 0xB0);
    *(float *)(hud_camera() + 0xB0) = 0.6200000047683716f;
    span = 375.0f;
    func_0027AB40();
    rounding = 0.5f;
    one = 1;
    entry = 0x8710;
    node = (unsigned char *)func_00336D50(D_L01_001A908C + entry, 142);
    y = hud_coord(span, D_L01_001B2DC4[0], rounding, one);
    height = 1.0f;
    unit = height;
    height = 0.0f;
    zero = height;
    height = (float)y;
    func_00300A00(node, 0x60442D00, 250.0f, height, unit, unit, zero);
    node = (unsigned char *)func_00336D50(D_L01_001A908C + entry, 143);
    y = hud_coord(span, D_L01_001B2DC4[0], rounding, one);
    height = (float)y;
    func_00300A00(node, 0x60241700, 250.0f, height, unit, unit, zero);
    node = (unsigned char *)func_00336D50(D_L01_001A908C + entry, 144);
    y = hud_coord(span, D_L01_001B2DC4[0], rounding, one);
    height = (float)y;
    func_00300A00(node, 0x55F0C070, 250.0f, height, unit, unit, zero);
    source.first = (int)0x800050C0;
    source.second = func_00283D38(0x800050C0, 0x80C04000, D_L01_001A90C4[0]);
    colors = source;
    x2 = func_00283CF0(190.0f + func_00283CE0(198) * D_L01_001A90C4[0]);
    height = D_L01_001B2DC4[0];
    top = hud_round(374.0f, height, rounding, one);
    bottom = hud_round(388.0f, height, rounding, one);
    func_0027EAE8(190, top, x2, bottom, 0, &colors);
    if (D_L01_001A90CC[0]) {
        int icon = func_0028E588(0xEAA7, D_L01_001A90CC[0] - 1);
        height = D_L01_001B2DC4[0];
        top = hud_round(352.0f, height, rounding, one);
        bottom = hud_round(43.0f, height, rounding, one);
        func_0028E868(icon, 139, top, 43, bottom, 128);
    }
    *(float *)(hud_camera() + 0xB0) = oldProjection;
    func_0027AB40();
    return D_L01_001A90D0[0];
}
