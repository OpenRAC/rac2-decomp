/* 9 November 2026 (Sonnet round 3, lesson 48/49 sweeps): 6 differing rows (was 7), one swap left: 0x18 $a3 (retail $v1) and c $v1 (retail $a3); upd $a1 and page $a2 now match. Form: `upd` a function-scope local assigned in case 8 just before its store, stores in source order a, next, c, upd=, page, b, init (b late). Scripted sweeps with a local scorer (~100k variants: every order of the 7 stores x local/expression/declared-early/assigned-late for page, c, upd, 0x18, init x every declaration order; init/0x18 as locals): none below 6. This is now the body C below. */
/* 8 November 2026 (Sonnet round 2, lesson 49; permuter-found, hand-cleaned): the upd value kept in one function-scope local (`upd = func_002CB648;` before the c store, `D_00210A40.upd = upd;`) gives 7 differing rows (was 10): page now $a2 as retail; still 0x18 $a1 (retail $v1), c $v1 (retail $a3), upd $a3 (retail $a1). Page/c/0x18 as extra locals, both orders of upd/c: no gain (7-10). 1500 s permuter run -j2 only found this local (65 -> 60). */
/* 8 November 2026 (Sonnet round, measured): the retained C gives 4 register rows in case 8 (page $a1/c $a2/upd $a3 against retail upd $a1/page $a2/c $a3). Statement orders (upd before page, a/b chained, next from page, a repeated upd store) leave 4 rows or worsen to 7. */
/* 8 November 2026 (m2z, caller-save angle): global.c:1516 tries caller-saves only when find_reg found no register (best_reg < 0), so CALLER_SAVE_PROFITABLE (4*calls < refs) never decides s-register versus call-clobbered while an s-register is free. cc1 -S on the retained C with and without -fno-caller-saves: identical body (0 lines differ). Uses s0-s2 with s3-s7 free across 22 calls; the 7 rows are not decided by caller-saves. Angle closed; no check.py runs. */
/* 7 November 2026 (opus, DrLegitamate): current master compiler, own unit -O2 -G16 -Wa,-G16.
 * This draft: 10 rows differ, all in case 8 (upd/page/c registers); everything else is relocations.
 * Retail's allocation is init $v0, 0x18 $v1, upd $a1, page $a2, c $a3, i.e. local-alloc priority
 * init > 0x18 > upd > page > c. With cc1 -dl the block-10 sched1 order confirms the priority
 * model (floor_log2(refs) * refs / life): with refs fixed (page 5, init 5, c 4, upd 4, 0x18 3) the
 * only way is sched1 emitting the init store before the upd and c stores and the 0x14 page store
 * last (next, a0, a, b, init, upd, c, page). Haifa's rank_for_schedule prefers the lower
 * INSN_REG_WEIGHT before LUID, so the stores that kill their value (upd, c, the last page store)
 * always precede the init store, whose value the call still uses.
 * Measured: 28 single per-file flags (none better; most far worse); all 15,120 orders of the
 * seven stores with the four addresses in locals (every local declaration order with page first);
 * 100,000 random forms (locals or constants per value, Menu/Cutscene pointers, chained page/next
 * and a/b stores, three call spellings). The best of all of them gets 3 of the 5 registers.
 * Locals declared page, c, upd, init with stores next, upd, page, c, init (a, b first) give page
 * $a2 and c $a3 as retail but swap upd and 0x18 (7 rows). Reopen only with a source cause for one
 * more reference to the init or upd value, or a different call/struct shape for case 8.
 * Same day, second pass. An instrumented local-alloc (printing each qty's refs, birth/death in half-luids
 * and QTY_CMP_PRI) gives this draft's case-8 block: init 5 refs [12,44] 3125 $v0, 0x18 3 refs
 * [24,34] 3000 $v1, page 5 [6,40] 2941 $a1, c 4 [8,36] 2857 $a2, upd 4 [10,38] 2857 $a3.
 * Retail needs upd > page > c below 3000: with these refs, page life >= 36 and c life >= 30
 * while upd stays at 28. The only schedule that does it loads page's %hi before D_00210A40's
 * and stores ..., init, upd, page, c (c last). rank_for_schedule compares INSN_REG_WEIGHT before
 * LUID, so page's last store (it ends page and the menu base, weight -2) always goes early.
 * Also measured: a function-wide `list` variable shared by the cases (as retail's shared case
 * tails suggest) makes page's value global and unties its %hi, but reaches at most 6 of 10
 * register checks; a 300,000-sample grammar mixing constants, case-local and function-wide
 * variables for all five values, chained stores and both call spellings: at most 6 of 10;
 * every single flag and every pair of 48 flags on three base drafts: no gain; a direct
 * func_002CB510(0) call gives all five registers but compiles to jal (MIPS defines
 * NO_FUNCTION_CSE), where retail calls through the stored value; a null-guarded call keeps the
 * branch.
 */
/* 5 November 2026: retained reconstruction, not linked or counted.
 * Retain the measured int returns of func_002CB510 and func_0029D830 and the void contract of func_002DE3A0.
 * The 1372-byte source remains a near miss; interface corrections do not qualify its allocation/scheduling.
 * Earlier measurements below describe earlier sources or toolchains.
 */
#include "common.h"
/* func_002CA070 - 1,372 bytes, 27 places (the boot and 26 levels). Finisher F1, 2026-10-26,
   on f5fab978 (qzero_nc default). Unit profile: -O2 -G16 -Wa,-G16 -ffunction-sections, as its
   own unit (src/game/002CA070-g16.c). 343 of 343 instructions, everything equal except five
   registers in case 8.
   Closed here (on top of big31's draft):
   - qzero_nc at the two camera clears (the fresh lui for D_001C2AD0 + 0x10).
   - The bnez slot: the screen size and frame-buffer reads are sym+offset reads of sda pairs,
     D_001A7340[1] (g_screenHeight) and D_001A72D8[1] (g_vramFrameBufB). simple_memory_operand
     gives a (const (plus sym off)) address length 2, so reorg leaves the slot empty and gas
     expands the macro to lui/lw, as retail. [0] of an sda array is length 1 and fills the slot.
   - The last loop: D_001A7398 as an sda incomplete array is one `la` insn (gas: lui/addiu on the
     same register), so the src giv has no %hi pseudo whose local $v1 global-alloc would prefer;
     dst then takes $v1, the counter $a0, src $a1, as retail.
   - Case 8 store order: source a, b, c, upd (b carries the 0x18 register's death, so all four
     are weight 0 and keep LUID order in sched1).
   Left: case 8's local-alloc. Retail: init $v0, 0x18 $v1, upd $a1, page $a2, c $a3; here
   0x18 $v0, init $v1, page $a1, c $a2, upd $a3. Instrumented local-alloc (QTY_CMP_PRI,
   floor_log2(refs) * refs / life): 0x18 3750 > init 3125 > page 2941 > c 2857 = upd 2857; retail
   needs init > 0x18 > upd > page > c, i.e. a longer 0x18 life (>= 10 half-insns), upd shorter
   than c and page longer than 1.25 x upd. 13,000 orders of the seven statements, with and
   without locals for the constants and with chained assignments, never got there (sched1 places
   the high/lo pairs by priority, not source order).
   F3 (2026-10-26) re-measure, same result. Exact local-alloc numbers (block 10, F1_LA; lives in
   half-insn luids after sched1): page refs 5 [6,40] 2941, c refs 4 [8,36] 2857, upd refs 4
   [10,38] 2857, init refs 5 [12,44] 3125, 0x18 refs 3 [26,34] 3750. sched1 puts the five %hi
   at 4..12 (A40, page, c, upd, init), the %lo and 0x18 at 14..26, then the stores page->next,
   a0 = 0, 0x18->a, 0x18->b, c, upd, page->page, init, call. One store order that satisfies
   retail's priorities with these births: next, a0, a, init, b, upd, c, page (0x18 [26,36] 3000,
   upd 28, c 32, page 36: init 3125 > 0x18 3000 > upd 2857 > page 2778 > c 2500). The lever is
   sched1's store order (init's store before b, upd's before c), not the statement order.
   v2160 (opus-1, 2026-11-03, c05 compiler): sched1 -fsched-verbose-5 for block 10: every %hi prio 7
   (A40 first: 3 dependents via the combined count store), %lo/&D_001F2840/0x18 prio 6, stores and
   a0 = 0 prio 5; stores rank by weight (later page/next -1; a, b, c, upd 0; earlier page/next and
   init +1), then LUID. A model over every hi order (locals), 0x18 before/after &D_001F2840, and
   every store order the weights allow finds no schedule that gives retail's registers; with init's
   qty at 6 refs instead of 5 (one more reference to the init pointer, no extra code) the current
   hi order works if upd is stored before c. An inline menu-list helper (params a, b, c, upd, init;
   init(0) or list->init(0)) and a list pointer compile identically. This draft stores a and b
   first so 0x18 is issued before &D_001F2840 (0x18 life 10): init $v0 and 0x18 $v1 now match;
   page $a1, c $a2, upd $a3 remain (retail upd $a1, page $a2, c $a3). check.py: 0/28, first
   difference +0x168, 126 of 343 rows differ (130 with the earlier case 8).
 */
#include "common.h"

typedef struct {
    u8 pad0[0x8];
    int state;          /* 0x08 */
    u8 pad1[0x8];
    int *page;          /* 0x14 */
    int *next;          /* 0x18 */
    u8 pad2[0x4];
    int unk20;          /* 0x20 */
    u8 pad3[0x4];
    int unk28;          /* 0x28 */
    u8 pad4[0x4];
    int unk30[4];       /* 0x30 */
    int unk40[4];       /* 0x40 */
    u8 v50[0x10];       /* 0x50 */
    u8 v60[0x10];       /* 0x60 */
    u8 pad5[0x60];
    int unkD0;          /* 0xD0 */
    u8 pad6[0xC];
    int unkE0;          /* 0xE0 */
    u8 pad7[0x10];
    int unkF4;          /* 0xF4 */
    float unkF8;        /* 0xF8 */
    u8 pad8[0x4];
    int *queued;        /* 0x100 */
    int hasQueued;      /* 0x104 */
    u8 pad9[0x4];
    int unk10C;         /* 0x10C */
    int unk110;         /* 0x110 */
    int unk114;         /* 0x114 */
    int unk118;         /* 0x118 */
    int unk11C;         /* 0x11C */
    u8 padA[0x14];
    int unk134;         /* 0x134 */
    u8 padB[0x8];
    int unk140;         /* 0x140 */
} Menu;

typedef struct {
    u8 pad0[0xB0];
    float fB0;
    u8 pad1[0x218 - 0xB4];
    int i218;
    float f21C;
    u8 pad2[0x228 - 0x220];
    float f228;
    int i22C;
} View;

typedef struct {
    u8 pad0[0xC];
    int fC;
    int f10;
} Buffers;

typedef struct {
    u8 pad0[0x24C];
    int unk24C;
    int unk250;
    int bufs[4];
} Snd;

typedef struct {
    int a;
    int b;
    int *c;
    u8 pad[0x8C - 0xC];
    void (*init)(int);
    void (*upd)(void);
} Cutscene;

extern int D_001BAF80[];
extern Menu D_001F2840;
extern View D_001B9040;
extern Buffers D_001BAEC0;
extern Snd D_001C4FA0;
extern Cutscene D_00210A40;
extern int D_0025A190[], D_0025E488[], D_00261238[], D_00259458[], D_00259328[], D_0025A738[], D_00259018[], D_00258D70[];
extern int D_001A8C8C[] __attribute__((sda));
extern int D_001A7478[] __attribute__((sda));
extern int D_001B22B0[] __attribute__((sda));
extern int D_001A8BC0 __attribute__((sda));
extern int D_001B1598[] __attribute__((sda));
extern int D_001B1598_sda __attribute__((sda));
extern int D_001A72D4[] __attribute__((sda));
extern int D_001A72D8[] __attribute__((sda));   /* the two frame buffers */
extern int D_001A7340[] __attribute__((sda));   /* the screen size pair: [0] width, [1] height */
extern int D_001A7398[] __attribute__((sda));
extern u8 D_001AA4B0[16] __attribute__((sda));
extern u8 D_001AA490[16] __attribute__((sda));
extern u8 D_001AA4A0[16] __attribute__((sda));
extern u8 D_001C2AD0[];
extern u8 D_001B5340[];

extern void func_002C9C60(float);
extern void func_002D5E98(void *);
extern void func_002CB648(void);
extern int func_002CB510(int);
extern void func_002C9AD8(void *);
extern void func_00295C50(int);
extern int func_0029D830(void);
extern void func_00282D30(void *, void *, float);
extern void func_0027AB40(void);
extern void func_002C9C90(void);
extern void func_00279D18(void);
extern void func_002FC3C0(int);
extern int func_001261F0(int);
extern void func_002DE3A0(int);
extern void func_002FC1D8(void);
extern void func_002954C0(void);
extern void func_0028AFE8(int);
extern void func_0028ACB0(int);
extern void func_002FC8D0(int, int, int);
extern void func_002C9F68(void);
extern void func_0028B338(int);

void func_002CA070(void)
{
    int queued = 0;
    int s, j, k, n, t, u;
    int *p;
    void (*upd)(void);

    D_001BAF80[4] |= 0x80000000;
    D_001F2840.unk134 = 0;
    D_001F2840.unkE0 = 0;
    switch (D_001F2840.state) {
    case 0:
    case 7:
    case 9:
        break;
    case 2:
        queued = 1;
        D_001F2840.page = D_0025A190;
        D_001F2840.next = D_0025A190;
        break;
    case 3:
        D_001F2840.page = 0;
        D_001F2840.next = 0;
        break;
    case 4:
        D_001F2840.page = D_0025E488;
        D_001F2840.next = D_0025E488;
        queued = 1;
        func_002C9C60(6.0f);
        break;
    case 11:
        D_001F2840.next = D_001F2840.page = D_00261238;
        D_001A8C8C[0] = D_001F2840.unk134 = 1;
        D_001F2840.state = 5;
        func_002D5E98(D_001AA4B0);
        break;
    case 5:
        D_001F2840.page = D_00261238;
        D_001F2840.next = D_00261238;
        D_001F2840.unk134 = 1;
        D_001A8C8C[0] = 1;
        break;
    case 6:
        D_001F2840.page = D_00259458;
        D_001F2840.next = D_00259458;
        break;
    case 1:
        D_001F2840.page = D_00259328;
        D_001F2840.next = D_00259328;
        break;
    case 10:
        D_001F2840.page = D_0025A738;
        D_001F2840.next = D_0025A738;
        break;
    case 8:
        D_00210A40.a = 0x18;
        D_001F2840.next = D_00259018;
        D_00210A40.c = D_00258D70;
        upd = func_002CB648;
        D_00210A40.upd = upd;
        D_001F2840.page = D_00259018;
        D_00210A40.b = 0x18;
        D_00210A40.init = func_002CB510;
        D_00210A40.init(0);
        func_002C9AD8(&D_00210A40);
        break;
    }

    if (D_001F2840.hasQueued != 0) {
        D_001A7478[0] = D_001F2840.unk140;
        D_001F2840.page = D_001F2840.queued;
        D_001F2840.next = D_001F2840.queued;
        if (D_001F2840.state == 2 || D_001F2840.state == 4) {
            func_00295C50(D_001F2840.unkF4);
            queued = 1;
            func_0029D830();
        }
        D_001F2840.queued = 0;
        D_001F2840.hasQueued = 0;
    }

    {
        u8 *r = D_001C2AD0;
        func_00282D30(r, D_001AA490, 1.0f);
        qcopy(r - 0x10, D_001AA4A0);
        r += 0x20;
        qzero_nc(r);
    }
    qzero_nc(D_001C2AD0 + 0x10);
    qcopy(D_001F2840.v50, D_001B5340);
    qcopy(D_001F2840.v60, D_001B5340 + 0x10);
    {
        float zfar = 524288.0f;
        float fog = 255.0f;
        float scale = 0.62f;
        D_001F2840.unkF8 = D_001B9040.fB0;
        D_001B9040.fB0 = scale;
        D_001B9040.f21C = zfar;
        D_001B9040.f228 = fog;
        D_001B9040.i22C = 0;
        D_001B9040.i218 = 0;
    }
    func_0027AB40();
    func_002C9C90();
    func_00279D18();
    func_002FC3C0(1);
    func_001261F0(0);
    D_001B1598_sda = D_001B1598[0] + 1;

    if (queued) {
        int a, b, c, d;
        a = D_001BAEC0.fC + 0x30000;
        b = D_001BAEC0.f10 + 0x30000;
        c = a + 0x3C000;
        d = b + 0xE0000;
        D_001F2840.unk10C = c + 0x11800;
        D_001B22B0[0] = 0x30000;
        D_001F2840.unk114 = a;
        D_001F2840.unk20 = b;
        D_001F2840.unk118 = c;
        D_001F2840.unk11C = d;
        D_001F2840.unk110 = d;
        func_002DE3A0(0);
    } else {
        int a, b, c, d, e, f;
        a = D_001BAEC0.fC + 0x60000;
        b = D_001BAEC0.f10 + 0x60000;
        b = b + 0xC000;
        a = a + 0xC000;
        c = a + 0x30000;
        d = b + 0xE0000;
        e = c + 0xC1000;
        f = d + 0x60800;
        D_001F2840.unk10C = e;
        D_001B22B0[0] = 0x60000;
        D_001F2840.unk114 = a;
        D_001F2840.unk20 = b;
        D_001F2840.unk118 = c;
        D_001F2840.unk11C = d;
        D_001F2840.unk110 = f;
        func_002DE3A0(1);
    }
    D_001A8BC0 = 0x2000;
    func_002FC1D8();
    if (queued) {
        func_002954C0();
    }
    func_0028AFE8(0);
    if (queued) {
        func_0028ACB0(1);
    } else {
        func_0028ACB0(0);
    }
    if (D_001F2840.unkD0 == 0) {
        func_002FC8D0(D_001F2840.unk20, D_001A72D8[1], D_001A7340[1] << 11);
    } else {
        func_002C9F68();
    }
    t = D_001A72D4[0];
    D_001F2840.unk28 = t;
    if (queued) {
        D_001C4FA0.unk24C = t;
        u = t + 0x40000;
        D_001C4FA0.unk250 = u;
        D_001A72D4[0] = u + 0x400;
        for (j = 0; j < 4; j++) {
            int v = D_001A72D4[0];
            D_001C4FA0.bufs[j] = v;
            D_001A72D4[0] = v + 0x4000;
        }
    } else {
        int z;
        D_001C4FA0.unk24C = 0;
        D_001C4FA0.unk250 = 0;
        p = &D_001C4FA0.bufs[3];
        for (z = 0; z < 4; z++) {
            *p = 0;
            p--;
        }
    }
    func_0028B338(1);
    for (k = 0; k < 4; k++) {
        D_001F2840.unk40[k] = D_001A7398[k];
        D_001F2840.unk30[k] = D_001A7398[k];
    }
}
