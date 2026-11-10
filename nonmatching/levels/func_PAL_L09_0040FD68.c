/* 10 November 2026, round 7 (about 80 scratch compiles of case 3 in batches, 4 check.py runs): no
   match; the C below is unchanged and still the best form (984/984 bytes, the same four register
   rows). New model, measured: an extra GPR insn X between the lhu and the conversion
   gives retail's whole assignment. With X the conversion is ready one cycle later, so sched1
   emits lhu, 300.0f, +1, 2.0f, sh, X, 1/6, cvt; X's result is tied to ticks (ticks dies in X),
   so the quantity has 5 refs (7142 against 5000 for ticks + 1) and takes $v0, and the converted
   ticks is born after 1/6 (1428 = 1428, 1/6 first) and beats 2.0f (1111): $f2, $f3, $f4, $f5 as
   retail. Two forms show it, both with X as real code: the post-increment (X = andi 0xFFFF, also
   through a 16-bit bit-field and through an inline accessor) and long wide = ticks;
   (float)(int)wide (X = truncdisi2, dsll/dsra; the sign extension before it is folded into a
   paradoxical subreg). Retail therefore fits an X that emits nothing: mips_move_1word prints no
   code for a move or an extendsidi2 whose two registers are equal. No lawful source found for
   one: cse replaces every in-block copy, combine folds a copy with a single use into
   floatsisf2, a copy into a variable shared with another case (next, sound, speed, accel) makes
   that variable global (no tie; $s2, $a1 or $f20 appear), and floatdisf2 needs double float.
   Without effect (block identical to the C below): the limit, sum or converted ticks through
   shared or new locals, compare reversed or negated (c.le.s), statement expression, comma form,
   += 1, T = T + 1, an unsigned short local, inline helpers for the tick, the conversion, the
   compare and the 50 Hz scale, (x * 60.0f) * 5.0f (adds a multiply), and 34 flag profiles
   (-fno-gcse, -fno-regmove, -fno-rerun-cse-after-loop, -fno-sched-interblock, -fno-sched-spec,
   -fno-schedule-insns2, -fno-cse-follow-jumps, -fno-cse-skip-blocks, -fno-thread-jumps,
   -fforce-addr, -fno-force-mem, -ffloat-store, -fcaller-saves, -O3, -O1 with both schedulers,
   -frac2-keep-block-order, -mno-split-addresses and others). Worse: the limit or the sum
   computed before the store (the two lwc1 move to the top); (float)(unsigned int)ticks (bltz
   fix-up path); old = ticks++ (a daddu copy); T++ after the read (loads first). A do {} while (0)
   around the if doubles the references inside it (flow weights by loop depth) and gives ticks
   $v0 and ticks + 1 $v1, but its loop note is a scheduling barrier (constants after the
   conversion, $f5 for it), and around the whole case it changes nothing. Open point: whether
   sched2 would put cvt back before 1/6 once X is gone (retail's final order) is not measured.
   Next: find what real construct leaves a tied no-op move (or SI-to-DI extension) of the counter
   at local-alloc, e.g. in a matched USA or PAL function whose retail code shows the same
   lhu/addiu/sh/mtc1 idiom with a wider or re-typed counter; otherwise leave it. */
/* 10 November 2026, round 6 (instrumented cc1): a private cc1 built from the same sources with a
   quantity dump in local-alloc.c's block_alloc (control: identical assembly with and without the
   dump) prints case 3's block exactly as modelled. No quantity has a suggested register. ticks
   (r89, refs 3, birth 4, death 14) has priority 3000 against ticks + 1 (r159, 5000), so ticks + 1
   takes $v0. The converted ticks (r160, 14..30) ties 2.0f (r166, 10..26) at 1250 and loses on
   quantity number, so 2.0f takes $f3. 1/6 (r168, 1666) takes $f2 and 300.0f (r164, 1111) $f5.
   Retail needs ticks above ticks + 1 and the conversion above 2.0f. Measured probes, not
   proposals (an invented test is not acceptable without retail evidence): a dead test on ticks is
   gone before allocation (no change), and a later use of ticks makes it a global pseudo, so
   ticks + 1 keeps $v0. Next: a source difference with retail evidence that changes these counts,
   e.g. an inline or macro shape for the 50 Hz conversion that the PAL code shares elsewhere. */
/* 10 November 2026, round 5 (5 compiles): matched PAL code that reads the same u16 frame counter
   (src/pal/levels/18_damosel/L18_003FF850.c) uses an inline moby_timer() accessor and writes
   the 50 Hz conversion as (x * 5.0f + 2.0f) / 6.0f in a -ffast-math unit. Here: the accessor
   (ticks = moby_timer(obj)) is unchanged; moby_timer(obj) - 1 after the store is 992 bytes;
   (x * 300.0f + 2.0f) / 6.0f is 980 bytes without -ffast-math and, with it, compiles to the
   multiply form, so the swap stays. About 55 compiles in all. Next: an instrumented cc1 printing
   the case-3 block's REG_N_REFS and qty priorities, to find what retail's source changes before
   local-alloc. */
/* 10 November 2026, round 4 (5 compiles plus the sched1 trace): casts and widths on the counter
   ((unsigned short)(ticks + 1), + 1u, += 1, (float)(unsigned short)ticks, an s16 local) change
   nothing (the s16 local adds an andi). The -dS trace shows why the schedule cannot move. The r5900 model
   issues the const_double moves on the memory unit with lhu, sh and the loads, and at t = 1 it
   picks lhu (300) over 300.0f (316), because only lhu's chain runs through the sh and the two
   dependent lwc1. Both retail-compatible orders need 300.0f at t = 1, which rank_for_schedule's
   priority rule excludes while that dependence exists, and retail keeps the loads after the
   sh, so the dependence is there too. The round-3 "global pseudo" account would need real uses of
   those values in other blocks, which retail does not have: treat it as unlikely. Conclusion:
   retail's RTL differs before local-alloc (ticks with more references, or an insn that is gone by
   the final code), not in its schedule. Next: find what in PAL's source adds a reference to
   the counter, e.g. compare other PAL ports whose USA original reads a u16 timer field. */
/* 10 November 2026, round 3 (2 compiles plus dumps): compared with the matched PAL timer test in
   func_PAL_L17_003CBDF4 (src/pal/levels/17_smolg/L17_003CBDF4-tilt-g8.c). There sched1 hoists the
   300.0f, 2.0f and 1/6 constants to the start of their block, as the two retail-compatible orders
   here need. Here the counter's sh is the critical path because both lwc1 depend on it, so the
   store and its inputs take the early slots. A const-qualified pointer for the two timer fields does
   not mark the loads unchanging (no change). A second account fits retail exactly: if ticks + 1, 300.0f and
   2.0f were global pseudos (live in more than this block, as when cse reuses a constant register
   across an extended block), local-alloc would give ticks $v0, 1/6 $f2 and the converted ticks
   $f3, and global-alloc then $v1, $f4 and $f5, which is retail's assignment. Next: look for the source shape
   that makes those three pseudos non-local without adding instructions. */
/* 10 November 2026, round 2 (about 30 more compiles): the swap is local-alloc priority, not source
   order. tools/regalloc.py shows case 3's block after sched1 as lhu, 300.0f, +1, 2.0f, sh, cvt,
   1/6, the two lwc1 (which depend on the sh: obj and data may alias), add, mul, add, mul, c.lt.
   With floor_log2(refs)*refs/(death-birth), ticks (3 refs, 5 insns) loses $v0 to ticks+1 (2 refs,
   2 insns), and the converted ticks ties 2.0f, which is born first and takes $f3. The USA original
   schedules the conversion before the sh (no 2.0f there), so ticks wins, as in retail. Of the
   16,098 orders the block's dependencies allow, only 2 give retail's assignment under that
   priority: 300.0f, lhu, 2.0f, +1, 1/6, cvt, sh, then the loads. Every constant is set before the
   conversion, and the conversion comes before the store. Tried without effect: operand orders of the
   compare and the 50 Hz expression, the counter and the timer fields as struct members (alias
   classes), unsigned short/unsigned int counters, read-back and pre-increment forms, the
   constants as named locals (cse folds them back), and the profiles -frac2-gcse-unsplit-edges,
   -fno-expensive-optimizations, -fno-schedule-insns (988 bytes), -g, -fstrict-aliasing (case 2
   and the loads move). Post-increments give retail's registers only with an andi; the recorded
   wider-local remedy ("16-bit counters read through a wider local") gives a daddu copy instead.
   Next: an RTL difference that makes sched1 set the constants first, e.g. what retail's other
   PAL timer conversions look like before sched1 in a matched function with the same idiom. */
/* 10 November 2026: func_PAL_L09_0040FD68 (984 bytes, level 9), PAL. 984/984 bytes, 0 of 1 places:
   only case 3's tick test differs, a register swap. Retail keeps the tick count in $v0 (its +1 in
   $v1) and in $f3, with 2.0f in $f4 and 300.0f in $f5; this C gives $v1/$v0 and $f4/$f3. Tried
   (10 compiles): the comparison reversed; (float)(count)++; the post-increment into ticks (exact
   registers, but an extra andi 0xFFFF before the conversion); a pointer to the count; the
   assignment inside the store; the limit or the converted ticks in a named local; the 50 Hz
   conversion as an inline helper. Next: a form that reads the count once as retail does without
   the extra zero-extension of the post-increment. Needs -G8 (its own L09_0040FD68-g8.c unit). */
#include "common.h"

/* func_PAL_L09_0040FD68, the PAL copy of func_L09_0040AC48 (src/levels/09_dobbo/L09_0040AC48-g8.c):
   the same C at 50 Hz, where 0.000277777785f becomes 0.00040000002f, the 240-frame hold becomes
   200, the timer's 60.0f becomes the scaled (x * 300.0f + 2.0f) * 0.16666667f, and
   func_L09_0040B0C8 becomes func_PAL_L09_00410200. */
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern void func_L09_0040B008(char *);
extern void func_PAL_L09_00410200(char *);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void func_002AA548(float *, float *, float, float, float, float);
extern float D_L09_001B15A8 __attribute__((sda));
extern float D_L09_001B15AC __attribute__((sda));
extern char D_00188660[];
typedef struct { float value[2]; float rate[2]; } DobboDoorMotion;
void func_PAL_L09_0040FD68(char *obj) {
    char *data = *(char **)(obj+0x68);
    int next, next4, sound, ticks;
    float speed, accel, speed4, accel4;
    char *entry;
    switch (*(unsigned char *)(obj+0x20)) {
    case 0:
        *(int *)(obj+0x98) = 0;
        *(unsigned short *)(obj+0x34) = (*(unsigned short *)(obj+0x34) | 0x2141) & 0xEFFF;
        func_002A7750(obj,1,-1);
        break;
    case 1:
        if (*(unsigned char *)(obj+0xBC)) func_002A7750(obj,2,-1);
        else {
            *(int *)(obj+0x98) = 0;
            *(unsigned short *)(obj+0x34) = (*(unsigned short *)(obj+0x34) | 0x41) & 0xEFFF;
        }
        break;
    case 2:
        if (func_002B3868(obj)) {
            *(unsigned short *)(obj+0x34) = (*(unsigned short *)(obj+0x34) & 0xFFBE) | 0x1000;
            *(int *)(obj+0x98) = *(int *)(*(char **)(obj+0x24)+0x10);
            func_L09_0040B008(obj);
            *(int *)(data+0x1C) = func_002E5CF8(0,4,obj);
        }
        next = (*(int *)(data+0x14)+1)&1;
        speed = D_L09_001B15A8 * 0.00040000002f;
        accel = D_L09_001B15AC * 0.00040000002f;
        if (((DobboDoorMotion *)data)->value[*(int *)(data+0x14)] < 1.0f)
            func_002AA548(&((DobboDoorMotion *)data)->value[*(int *)(data+0x14)],(float *)(data+8)+*(int *)(data+0x14),1.0f,speed,accel,1.0f);
        if (((DobboDoorMotion *)data)->value[*(int *)(data+0x14)] > 0.6f)
            func_002AA548(&((DobboDoorMotion *)data)->value[next],(float *)(data+8)+next,1.0f,speed,accel,1.0f);
        func_PAL_L09_00410200(obj);
        if (((DobboDoorMotion *)data)->value[next] >= 1.0f) func_002A7750(obj,3,-1);
        break;
    case 3:
        if (func_002B3868(obj)) *(int *)(data+0x18) = 200;
        ticks = *(unsigned short *)(obj+0x96);
        *(unsigned short *)(obj+0x96) = ticks + 1;
        if ((float)ticks > ((*(float *)(data+0x20)+*(float *)(data+0x24))*300.0f + 2.0f) * 0.16666667f)
            func_002A7750(obj,4,-1);
        func_PAL_L09_00410200(obj);
        break;
    case 4:
        next4 = (*(int *)(data+0x14)+1)&1;
        speed4 = D_L09_001B15A8 * 0.00040000002f;
        accel4 = D_L09_001B15AC * 0.00040000002f;
        if (((DobboDoorMotion *)data)->value[next4] > 0.2f)
            func_002AA548(&((DobboDoorMotion *)data)->value[next4],(float *)(data+8)+*(int *)(data+0x14),0.2f,speed4,accel4,1.0f);
        if (((DobboDoorMotion *)data)->value[next4] < 0.6f)
            func_002AA548(&((DobboDoorMotion *)data)->value[*(int *)(data+0x14)],(float *)(data+8)+next4,0.2f,speed4,accel4,1.0f);
        func_PAL_L09_00410200(obj);
        if (((DobboDoorMotion *)data)->value[*(int *)(data+0x14)] <= 0.2f) {
            obj[0xBC] = 0;
            *(int *)(obj+0x98) = 0;
            *(unsigned short *)(obj+0x34) = (*(unsigned short *)(obj+0x34) | 0x41) & 0xEFFF;
            func_002A7750(obj,1,-1);
            sound = *(int *)(data+0x1C);
            if (sound != -1) {
                entry = D_00188660 + sound*0x70;
                if (*(char **)(entry+0x88) == obj && *(unsigned char *)(entry+0x74)) func_002E59F8(sound);
            }
            *(int *)(data+0x1C) = -1;
        }
        break;
    }
}
