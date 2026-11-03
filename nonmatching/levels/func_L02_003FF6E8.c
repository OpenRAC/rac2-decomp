/* v2169 (opus-2, 3 November 2026): the saved-but-unused $s2 is explained; still no landable source.
   Level 2's display mode is D_L02_001B3E00 (the word before the scale D_L02_001B3E04; 66 loads in
   level 2, compared with a constant held in a saved register, e.g. `bne $v0,$fp` at 0x0034E6AC).
   MEASURED PROBE (not acceptable source: invented dead store), 696/696 bytes, retail's 0xF0 frame,
   $s2 saved and never used, state in $s3, `addiu $a0,$sp,0x10` rebuilt at every call:
       static __inline__ int hud_scaled(int mode, float v, int adjust)
       { float y; if (D_L02_001B3E00 == 1) y = 1.0f; y = v * D_L02_001B3E04 + 0.5f; return (int)y; }
   used for all seven scaled coordinates (`hud_scaled(mode, (float)D_L02_001B1444, 0)` etc., the
   three per call written as arguments of func_002802E0, no ctx variable, buf1 passed directly).
   Mechanism (read in the dumps): cse shares one constant-1 pseudo for the `== 1` tests of the first
   two draws, global-alloc gives it $s2 (it crosses calls), the arms are emptied by flow1, the tests
   survive to greg and vanish at flow2's block cleanup, which then deletes the mode loads and the
   constant: $s2 stays in regs_ever_live.  Left: scheduling (sched2 sees one block, so the colour
   and int argument loads rise into the chains) and 0.5/x swapped between $f21 and $f22.  The
   original construct must be a mode==1 test whose arm is dead after flow1 but not after cse (a
   never-read target dies in cse: test after the chain with `z = 1.0f` gave 688 bytes, no $s2).
   Also measured: the guide's 002D3D88 helper (`if (mode != 0) return (int)(..)+adjust; return
   (int)(..);`, mode in a local) vanishes only at jump2 and leaves `lw $s2,mode` (760 bytes, 0.5 no
   longer shared); `int r = (int)(..); if (mode != 0) return r + adjust; return r;` folds before
   gcse (700 bytes, mode load left in $s3 by combine's (use)).  So the overseer's lead is right
   about the mechanism, but the vanished test is `mode == 1` with a dead arm, not the 002D3D88 form.

/* NEAR MISS (measured 22 October 2026).  Needs a `-G8` unit (built here with
   `-O2 -G8 -ffunction-sections`; the $gp reads of D_L02_001B143C..1460 and 1470 are outside delay
   slots).  This body is 700 bytes against retail's 696, with retail's 0xF0 frame and retail's
   five GPR saves; 0 of 1 places match.

   The extra callee-saved register.  Retail saves s0..s3 and $ra but never touches $s2 in the
   body; `state` is in $s3.  This C (`char *ctx = buf1;` set before the first call and passed to
   the five draw calls) gives retail's register assignment exactly: ctx in $s2, state in $s3,
   the texts in $s1, buf2 and the colours in $s0 (the else block's colour in $s1), and the
   then/else blocks are retail's word for word except for ctx.  But this cc1 keeps ctx in $s2
   (`addiu $s2,$sp,0x10` in the first call's slot, `daddu $a0,$s2,$zero` at the five calls)
   where retail rematerialises the address at each call (`addiu $a0,$sp,0x10`) and has no set
   of $s2 at all, while still saving it.  112 of retail's 174 words are in a longest common
   subsequence with this body (103 for the earlier C that passes buf1 directly).  Without
   ctx (passing buf1 directly) state lands in $s2 and the frame is 0xE0 (688 bytes, about 140
   words off); every other shape tried also gives 0xE0 or keeps the extra register in use
   (second names for a0 or state, a second load of state, per-part text / float / int variables,
   a struct for the state, `len` variables).
   Why, read in the sources of this cc1: a pseudo with a frame-address REG_EQUIV is
   rematerialised by reload only when it has NO hard register (every reg_equiv_constant path in
   reload1.c tests reg_renumber < 0), and reload takes a callee-saved register away from its
   pseudo only when it needs it as a spill register at an insn where $v0..$t7 are all
   unavailable (order_regs_for_reload works per insn), which never happens here.  Retail's
   output is what a pseudo allocated to $s2 by global-alloc and then spilled by reload looks like
   (home marked live, so saved; every use replaced by its equivalence).  It is not alone: 21
   retail game functions save a GPR they never use, none of them in C, e.g. func_00326A10 and
   its copies func_0032F3D0 / func_L00_003DDEC8 / func_L00_004003F0 ($s0, a stack buffer passed to
   two calls and rematerialised at each), func_002D2188, func_0034A4E0, func_L02_003C43F0,
   func_L02_003FE8B8, func_L04_00416E38, func_L05_00421B98 / func_L10_00424CD0 /
   func_L15_00431590 / func_L25_0040DE40.  Hypothesis, not measured: the retail compiler chose
   spill registers for the whole function, as gcc 2.8's reload did (new_spill_reg marked the reg
   live and spill_hard_reg evicted every pseudo in it), so a cheap callee-saved register could
   become a spill register that no reload ended up using.  A compiler-side question, not a
   source shape.

   Also still different (scheduling):
   - the first block: retail issues `addiu $a0,$zero,0x2F45` before the lookup call and the state
     load in its slot (here the other way round), and the prologue's $s2 save comes late (no
     dependents in retail, since $s2 is never set);
   - the last block: retail keeps every global read of the func_002802E0 call after the three
     scaled-coordinate chains (the chains in $f0, scale $f1, 0.5 $f2, conversion scratch $f3);
     here sched1 issues those loads and the stack store into the chains' latency gaps, and the
     chain registers come out scale $f0, 0.5 $f1, t $f2.  Separate float/int variables for the
     last part do not change it.

   What is established (each measured earlier, each moved the diff):
   - the draws: func_0027F640(colour, text, x, y, scale, len, font, style), func_002802E0(ctx, ...
     nine arguments, the ninth on the stack), func_00280270 / func_00280190(ctx, colour, text,
     strlen(text)), func_00115DA8 (the sprintf) and func_00288FB8 (the text lookup); buf1 is the
     0x20-byte block at sp+0x10 (declared FIRST), buf2 the 0x70-byte buffer at sp+0x30;
   - the text lookups are statements of their own, before the call that uses them;
   - the colour arguments are `long long` in the prototypes (a 64-bit argument is a pseudo made
     before the next call: retail's `lw $s0,0x244C($gp)` in front of func_0027C878);
   - the order of func_0027F640's int and float parameters sets the order its arguments are
     evaluated in (text call, then the float chains, then the font call);
   - f20/f21/f22 come out as retail's (0.5 in f22) with the default scheduler;
   - the three `(int)(x * scale + 0.5f)` arguments are steps on ONE float variable; any
     one-expression spelling lets sched1 interleave the three chains. */

#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef float f32;

extern void func_L02_003FDDE8(char *, int);
extern char *func_00288FB8(int);
extern long long func_0027C878(int);
extern void func_0027F640(long long, char *, float, float, float, int, long long, char *);
extern void func_002802E0(char *, int, int, int, int, int, int, int, int);
extern int func_L02_003F9B70(int);
extern unsigned int func_001157AC(char *);
extern void func_00280270(char *, long long, char *, int);
extern void func_00280190(char *, long long, char *, int);
extern void func_00115DA8(char *, char *, ...);

extern float D_L02_001B1438 __attribute__((sda));
extern int D_L02_001B143C __attribute__((sda));
extern int D_L02_001B1440 __attribute__((sda));
extern int D_L02_001B1444 __attribute__((sda));
extern int D_L02_001B1448 __attribute__((sda));
extern int D_L02_001B144C __attribute__((sda));
extern int D_L02_001B1450 __attribute__((sda));
extern int D_L02_001B1454 __attribute__((sda));
extern int D_L02_001B1458 __attribute__((sda));
extern int D_L02_001B145C __attribute__((sda));
extern int D_L02_001B1460 __attribute__((sda));
extern int D_L02_001B1464;
extern int D_L02_001B1468;
extern int D_L02_001B146C;
extern int D_L02_001B1470 __attribute__((sda));
extern float D_L02_001B3E04;
extern char D_L02_001B1228[];
extern char D_L02_0028E990[];
extern u8 D_001395B8[0x100];

void func_L02_003FF6E8(char *a0) {
    char buf1[0x20];
    char buf2[0x70];
    char *ctx;
    char *state;
    char *text;
    char *msg;
    float t;
    int r1;
    int r2;
    int r3;

    ctx = buf1;
    func_L02_003FDDE8(a0, 0);
    state = *(char **)(a0 + 0x68);
    text = func_00288FB8(0x2F45);
    func_0027F640(D_L02_001B143C, text, (float)D_L02_001B1440,
                  (float)(int)((float)D_L02_001B1444 * D_L02_001B3E04 + 0.5f), D_L02_001B1438, -1,
                  func_0027C878(1), D_L02_0028E990);
    t = (float)D_L02_001B1460;
    t = t * D_L02_001B3E04;
    t = t + 0.5f;
    r1 = (int)t;
    t = (float)D_L02_001B1464;
    t = t * D_L02_001B3E04;
    t = t + 0.5f;
    r2 = (int)t;
    t = (float)D_L02_001B1450;
    t = t * D_L02_001B3E04;
    t = t + 0.5f;
    r3 = (int)t;
    func_002802E0(ctx, r1, r2, D_L02_001B1468, D_L02_001B146C, D_L02_001B144C, r3,
                  D_L02_001B1470, 3);
    if (*(s16 *)(state + 0x118) == 0 && D_001395B8[func_L02_003F9B70(0)] < 2) {
        text = func_00288FB8(0x2F46);
        func_00280270(ctx, D_L02_001B1448, text, func_001157AC(text));
    } else {
        text = func_00288FB8(0x2F62);
        msg = func_00288FB8(0x2F5E);
        func_00115DA8(buf2, D_L02_001B1228, text, *(int *)(state + 0x110), msg);
        func_00280270(ctx, D_L02_001B1448, buf2, func_001157AC(buf2));
    }
    text = func_00288FB8(0x2F47);
    t = (float)D_L02_001B1460;
    t = t * D_L02_001B3E04;
    t = t + 0.5f;
    r1 = (int)t;
    t = (float)D_L02_001B1464;
    t = t * D_L02_001B3E04;
    t = t + 0.5f;
    r2 = (int)t;
    t = (float)D_L02_001B145C;
    t = t * D_L02_001B3E04;
    t = t + 0.5f;
    r3 = (int)t;
    func_002802E0(ctx, r1, r2, D_L02_001B1468, D_L02_001B146C, D_L02_001B1458, r3,
                  D_L02_001B1470, 3);
    func_00280190(ctx, D_L02_001B1454, text, func_001157AC(text));
}
