/* 6 November 2026, lead: block-local a/b (and t for D_001A8BD0) in either assignment order and *&D_001AE92C all tie at 5 words. */
/* 6 November 2026, round 8: closer (468/468, 0/28 USA, 5 words). The absolute settings
 * words are offset reads of the $gp words before them (doc rule: symbol+offset has length
 * 2, never fills a slot, assembler expands lui/lw): D_001AE900 block [1],[2],[3],[5],[6]
 * for 904/908/90C/914/918, D_001AE920 [1], D_001AE8E8 [1], D_001AE8F0 [2]; the $gp reads
 * use SDATA(...) aliases so the canonical names stay absolute. This fixes the 002A7878
 * f12/f13 and 00283D38 a0/a1 setups. Left: func_002C2210 setup is a1, t1, a2 (retail a2,
 * t1, a1): sched1/sched2 tie on luid in argument order. Same 5: all 84 float positions in
 * the prototype, locals for either value (any order), D_001AE92C as SDATA D_001AE928[1],
 * ternary k, local for D_001A8BD0 or the life float. Worse: a2 read in both arms (98),
 * do/while(0) around either load or the call (86-92, +nop), split (plain) a2 base (10, lui
 * hoisted to v0 but a2/t1/a1 order right).
 */
/* 6 November 2026, round 2: no change (468/468, 0/28 USA, 12 words; checked in
 * src/game/00300618-g8.c). sched1 dump: the call block's arg moves are in argument
 * order and tie, so a1 (D_001AE92C) goes before a2 (D_001AE904); retail has a2 first.
 * Same result: a block local for D_001AE92C, the -g (00300618-draw-g8) and -g8-qcopy
 * units. Worse: local before the branch (114), D_001AE92C as an incomplete
 * MACRO_ADDR or sda view (472, absolute), D_001AE8EC[4] sda (13, macro in jal slot),
 * D_001AE8EC[] sda (464), -mno-split-addresses with or without plain arrays (472,
 * bnel head, a1/a2 still swapped), plain arrays with split addresses (46).
 */
/* 6 November 2026: retained source below unchanged (468/468, 0/28 USA, 12 words).
 * -mno-split-addresses with the 16-byte arrays and D_001A8BD0 as plain (non-sda) externs
 * gives 472 bytes and about 80 differing words (puff store block and branch-likely tail).
 */
/* 3 November 2026, second pass, current qualified compiler, default G8:
 * Fresh baseline: 468/468 bytes, 0/28 USA places, first mismatch +0x174.
 * The only remaining region is 00283D38's colour-load / f12 call setup.
 * Its actual contract is two 32-bit GP colours, one float, no stack inputs,
 * and a packed 32-bit return. The FP-first form used by matched 0027D4B8
 * produces an identical complete checker listing: ordering the banks does
 * not change this candidate. Pointer returns of the constructors remain real.
 * Incomplete MACRO_ADDR views for the two colour words give 464 bytes, 0/28:
 * the assembler chooses a GP-relative load in the jal slot. Plain incomplete
 * views give 468 bytes, 0/28, first reported mismatch +0x178, but split the
 * address bases into v0/v1 rather than retail's argument registers. Neither
 * is retained. The baseline below remains the closest measured source.
 * Reopen on a truthful scalar-load/address-class or scheduler explanation;
 * the legacy 16-byte extern-array bounds also need independent evidence or
 * faithful replacement before promotion. No new padding, flags or barriers.
 * Four USA checks (baseline plus three hypotheses); no alternate-release
 * or linked build was run for these failed candidates. Marker restored.
 */
/* 2 November 2026, remaining-function review: nonmatching; no linked credit.
 * Profile: -O2 -G8 -ffunction-sections.
 * US check: 468/468 bytes, 0/28 placements.
 * Both particle constructors return pointers in their matched production definitions. Correcting the ignored returns preserves the same 468-byte object and +0x174 first mismatch; call-argument/address scheduling remains.
 */
/* func_00302848 (468 bytes, 28 places), closer M2: 464 bytes under
 *     -O2 -G8 -ffunction-sections   (no -mno-split-addresses needed)
 * Fixed against the earlier draft: func_002A77E0 takes one argument (every caller passes
 * one; the a1 load in retail's bnez slot is the later D_001AE900 argument); the vertical
 * speed goes into the second (velocity) vector at sp+0, not the position vector; the zero
 * vector is qzero(), which puts the D_001AE930 argument in the jal slot; func_002C2210
 * takes (char *, float, float, s32, s32, float, s32, s32, char *, s32), found by trying all
 * 84 float positions; the macro-form words are sized sda arrays. Head, the spawn calls
 * and the epilogue match. Left: retail copies the func_002A7820 result into $s0 and masks
 * it in place (daddu + andi, 4 bytes more); this cc1 combines them into one andi, and the
 * callee-saved roles then rotate (tint/colour/vector s0/s1/s2 against s2/s0/s1). Twelve
 * spellings of the mask (u8 local, separate &=, (u8) cast, colour argument split out), with
 * and without -g, all compile to the same code.
 * M16: func_002C3150 is (void *, void *, int, u8, u8, int, float) as its matched callers in
 * L01_00397110 declare it (float last, the two bytes promoted at the call): that gives
 * retail's daddu + andi and the register roles, 468/468 bytes. D_001AE8EC as a plain
 * incomplete array keeps its load out of the jal slot. Left (12 lines, order only): cc1
 * counts the 16-byte sda arrays' loads as one instruction, so it puts them in jal slots
 * (the assembler expands them to two) and sched1 orders the func_002C2210 a1/a2/t1 setup,
 * the func_002A7878 f12/f13 loads and the func_00283D38 a0/f12 setup differently from
 * retail. Under -mno-split-addresses those three spots match but the head does not. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F302848;

extern s32 D_001AE930 __attribute__((sda));
extern s32 D_001AE900 SDATA(D_001AE900);
extern s32 D_001AE928 __attribute__((sda));
extern float D_001AE920 SDATA(D_001AE920);
extern s32 D_001AE92C __attribute__((sda));
extern float D_001AE8F0 SDATA(D_001AE8F0);
extern float D_001AE8E8 SDATA(D_001AE8E8);
extern s32 D_001AE900_blk[] __asm__("D_001AE900") MACRO_ADDR;
extern float D_001AE920_blk[] __asm__("D_001AE920") MACRO_ADDR;
extern float D_001AE8E8_blk[] __asm__("D_001AE8E8") MACRO_ADDR;
extern float D_001AE8F0_blk[] __asm__("D_001AE8F0") MACRO_ADDR;
extern char D_001A8BD0[16] __attribute__((sda));
extern u8 *D_001F0000[];
extern s32 D_001B1688[4] __attribute__((sda));

extern s32 func_002A77E0(s32);
extern void *func_002C2210(char *, float, float, s32, s32, float, s32, s32, char *, s32);
extern char *func_002C2FD8(char *, s32, s32, s32, s32, s32, s32, float);
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, char *);
extern float func_002A7878(float, float);
extern s32 func_002A7820(s32, s32);
extern s32 func_00283D38(s32, s32, float);
extern void *func_002C3150(void *, void *, int, unsigned char, unsigned char, int, float);

/* Spawns the object's trail puff; when not suppressed and flag one of the resident word is set it also emits the tinted streak. */
void func_00302848(char *obj, s32 quiet)
{
    V4_F302848 zero;
    V4_F302848 vec;
    char *rec = *(char **)(obj + 0x68);
    char *puff;
    char *pos;
    s32 tint, color, k;

    qzero(&zero);
    if (func_002A77E0(D_001AE930) == 0) {
        char *first = obj + 0x10;
        if (func_002A77E0(1) != 0)
            k = -D_001AE928;
        else
            k = D_001AE928;
        func_002C2210(first, D_001AE920, D_001AE920_blk[1], D_001AE92C, D_001AE900_blk[1], 0.0f, 2, k, D_001A8BD0, 0);
    }
    pos = obj + 0x10;
    puff = func_002C2FD8(pos, D_001AE900, *(u8 *)(rec + 0x41), 0, 0, 2, 0, D_001AE8F0);
    if (puff != 0)
        puff[2] = *D_001F0000[0x98E];
    if (quiet == 0 && (D_001B1688[0] & 1)) {
        func_002A7A00(&vec, 0.0f, 0.05f);
        func_00282CC0(&vec, &vec, pos);
        zero.f[2] = -(func_002A7878(D_001AE8E8, D_001AE8E8_blk[1]) * 0.016666668f);
        tint = func_002A7820(D_001AE900_blk[5], D_001AE900_blk[6]);
        color = func_00283D38(D_001AE900_blk[2], D_001AE900_blk[3], func_002A7878(0.0f, 1.0f));
        func_002C3150(&vec, &zero, color, tint, func_002A77E0(0xFF), 0, D_001AE8F0_blk[2]);
    }
}
