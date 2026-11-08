/* 8 November 2026 (Sonnet round): no gain, C below unchanged (944/964, 52 rows). Permuter 1500 s -j2 from this C: score 3610 -> 3280, only declaration/statement reorders, no $f20 or 0x30 frame. */
/* 8 November 2026, round 14: no change (944/964, USA v1.01 0/1). Tried on the C below:
 * -fmove-all-movables, -fno-gcse (+/- -fno-sched-interblock), -fno-expensive-optimizations,
 * -ffast-math, -fno-cse-follow-jumps, -frac2-keep-block-order, -frac2-gcse-unsplit-edges,
 * -frac2-zero-ti-por, -fno-rerun-loop-opt, -fno-strength-reduce, -fno-thread-jumps: all give
 * identical code (-fstrict-aliasing 940 bytes, worse). A named `rate = 15.0f` set at function
 * entry or before the index test (with or without -fno-gcse, with a later rate/15.0f use) is
 * folded the same way; a two-argument inline set_times(state, 15.0f, 12.8f) too. RTL dump:
 * combine folds the 15.0 pseudo (reg 127) into the $f12 move. Diagnostic: passing 15.0f to
 * both calls gives retail's $f20/0x30 frame, but with two mov.s reads (combine does not fold
 * the second use either), so a removed second use does not explain retail's single read.
 * No RAC1 twin (no shared constants/oclass set).
 */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 944/964 bytes, 52 differences (retail keeps 15.0f in a saved $f20 with a 0x30 frame; no source form keeps it). */
/* 7 November 2026, round 13: no better admissible C; the C below is unchanged
 * (944/964 bytes, USA v1.01 0/1, 52 real differences). Frame: 0x30 is only the
 * $f20 save slot (s0/s1/ra at 0-0x17, $f20 at 0x20); no temporary slot is
 * needed (lesson 40 ruled out). Retail reads $f20 once (mov.s $f12) and stores
 * 15.0 nowhere, so no later field takes it. -O2 sets -fexpensive-optimizations,
 * so preserve_subexpressions_p is 1 and every call argument starts in a pseudo
 * (calls.c precompute_register_parameters); combine then folds the constant
 * into $f12 unless that pseudo has another use. Inline helpers (two float
 * parameters, one parameter, a u8 wrapper) and t-2.2f / t*k second uses all
 * fold to li.s $f12. Matched func_002C2658 keeps 0.7 in $f20 because its
 * arguments are precomputed before an inner call in the same argument list;
 * FloatToInt has one argument, so that does not apply. The only compiler route
 * found is a stale REG_N_CALLS_CROSSED: sched1 keeps the flow count for a
 * pseudo live in more than one block (haifa-sched.c, end of
 * find_post_sched_live), so a cross-block use removed by combine would leave
 * $f20; no admissible source shape for that was found. Tail: `impact: if (hit)`
 * reproduces retail's a0 copy and beqz recheck exactly (tail matches; local
 * aligned count 78 -> 69), but it is a redundant test and is not kept. target
 * copy / clear-hit forms are worse (81-91); -frac2-no-null-pointer-checks and
 * -frac2-keep-block-order do not change them.
 */
/* 6 November 2026, round 10: hill-climbed order of the cached inputs and the
 * independent parameter stores; 944/964 bytes, USA v1.01 0/1, 52 real differing
 * instructions (was 58). No matched sibling exists: no other retail routine has
 * this field/constant set. -fno-schedule-insns (+/- -fno-sched-interblock) gives
 * 101; -frac2-keep-block-zero-copy ties. $f20 reasoning: retail's 15.0 pseudo was
 * not combined into the $f12 move, so it must have had a later use that crossed
 * the first call and vanished after flow. CSE folds every later use tried
 * (r/3600, r*4 to short, r+5 to u8, r/15, (u8)r, (short)r, an inline two-timer
 * helper); none gave $f20. Recheck: a `target` copy (0 or hit) and clearing
 * `hit` on a mismatch both give a retest, but GCC does not thread the
 * other==0/mismatch paths (60-63).
 */
/* 6 November 2026, Codex own-unit replay: retained C, not a linked match.
 * Profile: game -O2 -G8 -ffunction-sections -frac2-qcopy.
 * USA v1.01 and v2.00: 944/964 bytes, 0/1 places each; PAL absent.
 * The complete state layout (including the overlapping 0x6C0 vector / 0x6CC float)
 * and snapshots of the initialization inputs reduce allocation/scheduling differences
 * against the old raw-offset draft. Independent store swaps improve the initialization
 * further. All cached inputs are assigned before use; stores touch disjoint fields.
 * Still missing: retail's saved $f20 containing 15.0f (frame 0x30 versus our 0x20),
 * plus its defensive hit-candidate recheck. Initialization GPR/FPR choices, load/store
 * scheduling and copy placement also differ. No redundant candidate test is retained.
 * New negative results: one real state struct alone is insufficient; cached inputs
 * help, but single-operation/suffix one-pass groups regress. Moving/reusing a real
 * float rate across the initialization and final damage arguments, including with
 * -fno-gcse, does not recover $f20. qcopy-barrier and no interblock scheduling tie.
 * Reopen with evidence for the original float lifetime or parameter-group layout;
 * another constant spelling or one-pass store group is unlikely to help.
 * No linked build run (worker restriction). The existing zero-argument declaration in
 * L17_003E7068-g8.c remains a separate native-interface issue.
 * Historical measurements: ordinary raw-offset C was 936/964 without the copy
 * profile and 944/964 with it. Neither the old nor this draft has the retail frame.
 */
#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } Vec;
typedef struct FighterState {
    u8 pad0[0x26];
    u16 f26;
    u8 f28;
    u8 f29;
    u8 pad2A[0x6];
    float f30;
    u8 f34;
    u8 pad35[0x13];
    u8 f48;
    u8 pad49[0x1];
    u8 f4A;
    u8 pad4B[0x25];
    u8 f70;
    u8 f71;
    u8 pad72[0x3];
    u8 f75;
    u8 f76;
    u8 f77;
    u8 pad78[0x4];
    float f7C;
    float f80;
    float f84;
    float f88;
    float f8C;
    float f90;
    float f94;
    short f98;
    u8 pad9A[0x2];
    float f9C;
    float fA0;
    u8 padA4[0x4];
    int fA8;
    u8 padAC[0xC];
    float fB8;
    u8 padBC[0x10];
    u8 fCC;
    u8 fCD;
    u8 fCE;
    u8 fCF;
    u8 padD0[0x2];
    u8 fD2;
    u8 fD3;
    u8 padD4[0x1];
    u8 fD5;
    u8 padD6[0x3A];
    float f110;
    u8 pad114[0x4];
    float f118;
    float f11C;
    float f120;
    u8 pad124[0x18];
    float f13C;
    u8 pad140[0x8];
    int f148;
    int f14C;
    u8 pad150[0x100];
    int f250;
    u8 pad254[0x42C];
    int f680;
    int f684;
    u8 pad688[0x16];
    short f69E;
    u8 pad6A0[0x4];
    int f6A4;
    u8 pad6A8[0x10];
    int f6B8;
    u8 pad6BC[0x4];
    Vec f6C0;
    u8 pad6D0[0x18];
    int f6E8;
    int f6EC;
    u8 pad6F0[0x10];
    float f700;
    u8 pad704[0x1C];
    char * f720;
    u8 pad724[0xC];
    int f730;
    u8 pad734[0x10];
    char * f744;
    u8 pad748[0x8];
    int f750;

} FighterState;
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u8 *)((char *)(p)+(o)))
extern char *D_L17_001B2C1C;
extern float D_L17_001B0E40 __attribute__((sda)),D_L17_001B0F38 __attribute__((sda)),D_L17_001B0E48 __attribute__((sda));
extern char D_L17_001B9BC0[];
extern int func_00283CF0(float);
extern void func_0029F338(void *);
extern void func_002A7750(void *,int,int);
extern int func_L02_0032E508(void *,int,void *,int);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *);
extern char *func_002A9640(void *,u32,int);
extern int func_002B0ED8(void *,void *,int);
extern int func_002B3BA8(void *,int,void *,int,float,float);
/* Initializes the fighter's complete parameter groups, then handles proximity and damage. */
void func_L17_003E8A58(char *object)
{
    FighterState *state=(FighterState *)P(object,0x68);
    char *hit;
    int index;
    float vf80;
    float vf84;
    float vf94;
    float vf7C;
    float vf88;
    float vf8C;
    float vf9C;
    float vf700;
    float vfB8;
    float vf90;
    int vf14C;
    float vfA0;
    float vf11C;
    float vf120;
    float vf13C;
    float vf30;
    float vf118;
    if(!U(object,0x20)) {
        F(object,0x2c)=F(P(object,0x24),0x24)*0.85f;
        index=state->f6B8;
        if((unsigned)(index+1)>=2) F(object,0x18)=F(D_L17_001B2C1C+index*256,0x18)+1.4f;
        state->f6C0.q=*(Q *)(object+0x10);
        state->f110=D_L17_001B0E40;
        state->f6E8=0;state->f6EC=0;state->f6C0.f[3]=F(object,0xf8);
        state->f48=func_00283CF0(15.0f);state->f4A=func_00283CF0(12.8f);
        state->f70=14;state->f71=13;state->f76=8;state->f29=1;state->f75=7;state->f77=9;
        vf7C=0.333333343f;
        vf8C=0.00138888892f;
        vf700=(float)state->f34;
        vf118=D_L17_001B0E48;
        vf94=D_L17_001B0E40+0.1f;
        vf9C=0.4f;
        vf88=0.00833333377f;
        vfB8=0.01f;
        vf90=D_L17_001B0E40;
        vf14C=state->f684;
        vf84=0.00416666688f;
        vf120=1.308997035f;
        vf80=D_L17_001B0F38*0.016666668f;
        vf13C=0.01111111138f;
        vfA0=40.0f;
        vf30=1.0f;
        vf11C=D_L17_001B0E48;
        state->fD3=12;
        state->f84=vf84;
        state->fCC=7;
        state->fA8=3;
        state->f94=vf94;
        state->fCE=4;
        state->fCD=20;
        state->fD5=1;
        state->f14C=vf14C;
        state->f7C=vf7C;
        state->fA0=vfA0;
        state->f80=vf80;
        state->fD2=6;
        state->f8C=vf8C;
        state->f88=vf88;
        state->f9C=vf9C;
        state->fCF=9;
        state->f700=vf700;
        state->f26=60;
        state->fB8=vfB8;
        state->f90=vf90;
        state->f11C=vf11C;
        state->f13C=vf13C;
        state->f98=0;
        state->f120=vf120;
        state->f148|=16;
        state->f28=3;
        state->f30=vf30;
        state->f118=vf118;
        if(state->f680==-1 || state->f684==-1) {func_0029F338(object);return;}
        if((unsigned)(state->f6B8+1)<2) func_002A7750(object,3,0);else func_002A7750(object,1,5);
        state->f730=1;state->f720=state->f744;
        if(state->f744) I(state->f744,0)=-1;
        state->f750=func_L02_0032E508(object,state->f684,(char *)state+0x280,32);
    }
    if(U(object,0x31) && func_00282E48(object+16,D_L17_001B9BC0)<24.0f) {func_002A93B0(object);U(object,0x6f)=22;}
    hit=func_002A9640(object,0x10000,1);
    if(hit && P(hit,0x20) && (H(P(hit,0x20),0xaa)==0x31a || H(P(hit,0x20),0xaa)==0x1256 || H(P(hit,0x20),0xaa)==0x1305)) goto impact;
    if(U(object,0x20)!=1) func_002B0ED8(object,(char *)state+0x60,0);
    goto damage;
impact:
    U(object,0xa8)=255;
damage:;
    state->f69E=func_002B3BA8(object,state->f680,0,0,0.0f,0.0f);
    state->f6A4=state->f250;
}

