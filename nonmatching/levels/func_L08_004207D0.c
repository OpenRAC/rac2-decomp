/* 8 November 2026, cse path probe (USA v1.01): PATHLENGTH is 10 in our cse.c, the EE 991111 source and
 * upstream 2.95.2 alike, and SN 2.95.2 (273a) and all three 991111 cc1 builds also load the loop 0.5 fresh
 * (`li.s $f23,0.5`, no copy) on this C. An env-gated cc1 with PATHLENGTH 13+ gives the copy: 5 -> 2 words
 * (mov.s lands in the beqz slot, retail has `daddu s2,v0` there); 13/14/16/20/32/64 all 2. Forced on over
 * all 8775 units: 47 matched units change code (PL 13 and 64 alike), so the hypothesis is falsified. */
/* 8 November 2026, round three (USA v1.01, check.py only, master compiler): best C below 1156/1156
 * bytes, 0/2 places, first difference at +0x24c; 5 differing words, all the loop preheader's 0.5
 * (retail `mov.s f23,f24` copy, here `lui/mtc1 f23`, which also moves one addiu/lui). Was 28 rows.
 * Fixes: loop y via hud_coord (L05_0037A5F8-g8.c form, allowed by owner ruling of 8 November 2026)
 * gives the alpha copy in $a0 and the final block order with no ghost saved register; the scale
 * written into `y` (as the L05 twin) fixes every loop FP register (size f21, y f20, x f22) and the
 * anchor y f20; the second sprite's label_y handle is `first` (second now in $s3).
 * label_y with `one = 1` after the alpha call is also ghost-free (one row worse: mfc1 $v1).
 * Left: cse2 makes the copy only when its path from the function start reaches the preheader.
 * cse.c PATHLENGTH is 10 (at most 9 skipped blocks); the four top labels skip 12 dead-test blocks.
 * A plain anchor y (9 skips) gives the copy but breaks the anchor's schedule (13 words); a plain
 * sprite is worse (38-70). Every label_y/hud_coord mix keeps 12 skips; none gives the copy.
 * No gain: one/i/declaration orders, other handles, -fno-gcse, -fno-rerun-loop-opt (D_9D30 lui not
 * hoisted, s6 ghost). */
/* 7 November 2026, round two: 1156/1156 bytes (size now right), 0/2 placements; 48 -> 28 masked
 * aligned rows (check.py --diff, own metric; the 51 below is another harness). Body below. Fixes: color is an s64 local set
 * from the (s32) value before the texture call (retail's `daddu s0,s0,zero` sign-extend, the 4
 * missing bytes); `scale *= D_L08_001B1B9C` right after the divide; indexed list loop `cursor[i]`
 * (retail's `lw v0; beqz v0; daddu s2,v0` copy). Left: second in s2 (retail s3; the shared active-1
 * pseudo takes s3 in ours), anchor y f22 (retail f20), loop x/y/size f20/f22/f21 (retail f22/f20/f21),
 * the loop's 0.5 is a fresh lui/mtc1 (retail `mov.s f23,f24` copy of the top 0.5), and the final
 * block issues `sll alpha` first (retail: y chain, then lw D_1BA8/sll/or, alpha copied to a0).
 * Tried: label_y on the loop y (handle object/cursor): final block order exact, but the hoisted
 * active-1 takes a ghost s7 (52); a do/while(0) group around x/y: right order (29) but its
 * LOOP_BEG aligns the loop-continue label (.p2align 3, +1 nop), -malign-loops=2 loses retail's
 * other alignment; donor-style `base = 0x8710; one = 1; half = 0.5f` (with/without -fno-gcse),
 * separate anchor y, var reuse for scale/size, statement orders, call-as-argument: no gain;
 * -fno-schedule-insns 141, -fno-sched-interblock/-fno-sched-spec/-fno-rerun-loop-opt no gain. */
/* 7 November 2026, label_y sweep: the three sprite ys use label_y(first/second/third, ...), the anchor y label_y(object, ...): 141 -> 51 differences, 1144 -> 1152/1156 bytes (loop y with label_y: worse, alpha 68, state 75). The body below is the retained C with that change (label_y is
 * the accepted HUD label idiom, definition as in src/levels/15_gorn/L15_00431590-g8.c). Counts are
 * masked aligned instruction differences from a cc1 -S diff harness, not check.py rows. */
/* 2 November 2026, remaining-function review: nonmatching; no linked credit.
 * Profile: -O2 -G8 -ffunction-sections -g -frac2-zero-ti-por.
 * US check: 1144/1156 bytes, 0/2 placements.
 * Current matched projection-state helpers00300090/003000C0 return s32;00300100 is void. Correcting the first two ties at 1144/1156,0/2. Full48-byte matrix buffers and wide colors are preserved.
 */
/* func_L08_004207D0: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections -g -frac2-zero-ti-por.
   Complete radar UI with two 48-byte matrices. Retail func_002833F0 and func_002836E8 each write exactly three quadwords. Signed 32-bit dynamic color is sign-extended into the actual 64-bit RGBA parameter; texture descriptors retain 64 bits. Frame/allocation and rounding/scheduling remain.
   No linked match is claimed.
*/

#include "common.h"
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern u8 *D_L08_001A904C MACRO_ADDR, *D_L08_001B29DC MACRO_ADDR;
extern f32 D_L08_001B3244 MACRO_ADDR;
extern f32 D_L08_001B1B84 __attribute__((sda)), D_L08_001B1B88 __attribute__((sda));
extern f32 D_L08_001B1B8C __attribute__((sda)), D_L08_001B1B90 __attribute__((sda));
extern s32 D_L08_001B1B94 __attribute__((sda)), D_L08_001B1B98 __attribute__((sda));
extern f32 D_L08_001B1B9C __attribute__((sda));
extern s32 D_L08_001B1BA0 __attribute__((sda));
extern f32 D_L08_001B1BA4 __attribute__((sda));
extern u32 D_L08_001B1BA8 __attribute__((sda));
extern u16 *D_L08_001FB660[];
extern u8 D_L08_001B9D30[];
extern s32 func_L08_00300090(void), func_L08_003000C0(void);
extern void func_L08_00300100(void);
extern char *func_00336D50(void *, s32);
extern void func_00300A00(char *, u32, f32, f32, f32, f32, f32);
extern u64 func_0027C878(s32);
extern void func_L05_003008C0(f32, f32, f32, f32, s32, s32, s32, s32, u64, u64);
extern f32 func_00282E48(void *, void *);
extern void func_002833F0(void *, void *), func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32), func_002836E8(void *, void *);
extern void func_00283098(void *, void *, void *);
extern s32 func_00283CF0(f32);

extern int D_L08_001B3240;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L08_001B3240;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L08_001B3240;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

void func_L08_004207D0(u8 *object)
{
    Vector difference, euler;
    f32 rotation[12], inverse[12];
    u8 *state, *entry, *anchor;
    char *first, *second, *third;
    u16 *cursor;
    s32 i;
    f32 y, distance, size, x;
    s32 alpha;
    s64 color;
    u64 texture;
    func_L08_00300090();
    func_L08_00300100();
    state = *(u8 **)(object + 0x68);
    first = func_00336D50(D_L08_001A904C + 0x8710, 0xBA);
    second = func_00336D50(D_L08_001A904C + 0x8710, 0xBB);
    third = func_00336D50(D_L08_001A904C + 0x8710, 0xBC);
    func_00300A00(first, 0x60442D00, D_L08_001B1B84 + 4.0f, (f32)label_y(first, D_L08_001B1B88 + 4.0f, D_L08_001B3244, 0.5f, 1), 0.8f, -0.8f, 0.0f);
    func_00300A00(second, 0x60241700, D_L08_001B1B84 + 4.0f, (f32)label_y(first, D_L08_001B1B88 + 4.0f, D_L08_001B3244, 0.5f, 1), 0.8f, -0.8f, 0.0f);
    func_00300A00(third, 0x55F0C070, D_L08_001B1B84 + 4.0f, (f32)label_y(third, D_L08_001B1B88 + 4.0f, D_L08_001B3244, 0.5f, 1), 0.8f, -0.8f, 0.0f);
    y = (f32)label_y(object, D_L08_001B1B88, D_L08_001B3244, 0.5f, 1);
    texture = func_0027C878(D_L08_001B1BA0);
    func_L05_003008C0(D_L08_001B1B84, y, D_L08_001B1B8C, D_L08_001B1B90,
                     0, 0, D_L08_001B1B94, D_L08_001B1B98, 0x80808080UL, texture);
    func_L08_003000C0();
    anchor = *(u8 **)(state + 0x1B0);
    if (!anchor) return;
    cursor = D_L08_001FB660[anchor[0x21]];
    if (!cursor) return;
    i = 0;
    do {
        entry = D_L08_001B29DC + ((cursor[i] & 0x7FFF) << 8);
        if (!entry || entry[0x20] == 0xFE || entry[0x20] == 0xFD || *(s16 *)(entry + 0xAA) == 0x96A) return;
        distance = func_00282E48(object + 0x10, entry + 0x10);
        if (distance <= D_L08_001B1BA4) {
            y = distance / D_L08_001B1BA4;
            y *= D_L08_001B1B9C;
            euler.q = 0;
            euler.f[2] = 1.5707964f;
            func_002833F0(rotation, &euler);
            func_00282CF0(&difference, entry + 0x10, object + 0x10);
            func_00282F20(&difference, &difference, y);
            func_002836E8(inverse, D_L08_001B9D30);
            func_00283098(&difference, &difference, inverse);
            func_00283098(&difference, &difference, rotation);
            alpha = func_00283CF0((1.0f - distance / D_L08_001B1BA4) * 128.0f);
            size = difference.f[2] * 0.125f + D_L08_001B1B8C * 0.5f;
            if (size > D_L08_001B1B8C + D_L08_001B1B8C) size = D_L08_001B1B8C + D_L08_001B1B8C;
            else if (size < 0.0f) size = 0.0f;
            x = difference.f[0] + D_L08_001B1B84;
            y = (f32)hud_coord(D_L08_001B1B88 - difference.f[1], D_L08_001B3244, 0.5f);
            color = (s32)(D_L08_001B1BA8 | ((u32)alpha << 24));
            texture = func_0027C878(D_L08_001B1BA0);
            func_L05_003008C0(x, y, size, size, 0, 0, D_L08_001B1B94, D_L08_001B1B98, color, texture);
        }
    } while ((s16)cursor[i++] >= 0);
}
