/* Current retained result, 1 November 2026: 2996/2988 bytes. Explicit goto alternatives for the two strip
 * loops kept that size and reduced opcode agreement; retain the structured loops. No new volatile access or
 * artificial loop was introduced. The preheader and wide-shift scheduling constraints below remain.
 * Not a functional-port qualification or a complete matching-build result.
 * Profile: -O2 -G0 -ffunction-sections -fno-rerun-loop-opt.
 * Earlier measurements below remain historical where superseded by this note.
 */
/*
 * Tier: Opus 5.5 xhigh, task v1829. Flags (a unit of its own, not 0027F128.c):
 *   -O2 -G0 -ffunction-sections -fno-rerun-loop-opt
 * Best check.py: 2996/2988 bytes, 0 of 28 places match. Aligned against retail
 * with a private script that ignores relocated symbol values (check.py cannot
 * compare those until the size matches), only 9 rows differ, in two places, both
 * order only. The two extra words come from difference 1: the else arm keeps its
 * own lui $s0 and p init, and an alignment nop appears. All other instructions and
 * register allocation agree. 27 compiles, 3 of them regalloc.py; stopped on a tie.
 *
 * Remaining differences:
 * 1. Pre-header of both D_001A6860 loops. Retail order is i = 0, the gcse %hi
 *    loads, the loop pass's constants, then addiu p,q,0x60 last; lui $s0 fills
 *    the beqz slot. Here p's init comes first and fills the slot. Only insns the
 *    loop pass emits land after those constants (compare a plain cursor, whose
 *    reduced givs do), but the reduction of p is "not worth while" at biv_count 4.
 *    `for (p = .., i = 0;`, `i = 0; p = ..; for (;`, `p = ..; for (i = 0;` tie.
 * 2. First statement of the D_001A6600 loop. Retail: sll; sd; addiu i; addiu p;
 *    slti. Here: sll; addiu i; sd; slti; addiu p. The extendsidi2 between sll and
 *    sd lives until final and costs a clock in sched2; retail has no such clock.
 *    mips.md has sign_extend:DI patterns for plus/minus but not ashift. i * 0x200,
 *    i << 9, an int or long temporary and *p = ..; p++ tie; (long)i << 9 is worse.
 *
 * What the earlier drafts lacked (all measured, see gcc/loop.c, reorg.c, alias.c):
 * - loop.c strength_reduce converts a multi-increment biv into separate pointers
 *   unless loop_has_volatile. Retail keeps one cursor, so these loops have a
 *   volatile access. A volatile short field gives lhu;sll;sra (retail has lh), so
 *   it is the store: a volatile cursor. The D_00138990 if/else loop does not need
 *   it and must not have it: reorg never puts a volatile access in a delay slot,
 *   and retail has sd through p and the pointer read in slots in that loop.
 *   The same rule shows D_001A742C is not volatile; the earlier volatile pointer
 *   plus per-statement locals were a wrong model. Plain RAC1 FA-> wording then
 *   reloads it in every statement by itself. The volatile cursor is a declaration,
 *   but the q[] header stores are not volatile (q[81] is in a jal slot), so the
 *   orchestrator should rule on it if this ever matches.
 * - Header stores through a sequential cursor (*out++): not in-struct, unlike
 *   q[n], so the scalar D_001A7BB8 and pointer reads stay behind them, while
 *   frame.FBP stores (in-struct) do not hold them back.
 * - *(long *)&FA->draw0[1]: with (unsigned long *) there is no reload before the TI
 *   clear, with (long *) there is, as in retail. Inferred cause: the differing type
 *   keeps the cast from folding, so the store is not in-struct.
 * - The snapshot words are zero-offset [] sda symbols: as elements they conflict
 *   with FA->display (retail rereads it each time), and only a plain symbol has
 *   the one-word model that lets D_001A744C go into the jal slot as $gp.
 * - The last packet: r[2] before r[10], through its own pointer, int temporary.
 * - The texture word is func_00284088's wording (four-term OR kept from rebalancing).
 * - Count-up i < 16 loops: the compiler reverses the last two itself.
 * Next: find what emits p's init from the loop pass in the first loops, and a
 * wording with no extendsidi2 before the first store of the second.
 * Linked build not run: check.py has not passed.
 */
#include "include_asm.h"

/* Adapted from RAC1 framebuf.c, SetupFS_AA_buffer. */
typedef unsigned int u128_FAB40 __attribute__((mode(TI)));

typedef struct {
    unsigned long NLOOP:15;
    unsigned long EOP:1;
    unsigned long pad16:16;
    unsigned long id:14;
    unsigned long PRE:1;
    unsigned long PRIM:11;
    unsigned long FLG:2;
    unsigned long NREG:4;
    unsigned long REGS0:4;
    unsigned long REGS1:4;
    unsigned long REGS2:4;
    unsigned long REGS3:4;
    unsigned long REGS4:4;
    unsigned long REGS5:4;
    unsigned long REGS6:4;
    unsigned long REGS7:4;
    unsigned long REGS8:4;
    unsigned long REGS9:4;
    unsigned long REGS10:4;
    unsigned long REGS11:4;
    unsigned long REGS12:4;
    unsigned long REGS13:4;
    unsigned long REGS14:4;
    unsigned long REGS15:4;
} GifTag_FAB40;

typedef struct {
    unsigned long FBP:9;
    unsigned long rest:55;
} GsFbp_FAB40;

typedef struct {
    unsigned long pmode;
    unsigned long smode2;
    GsFbp_FAB40 dispfb;
    unsigned long display;
    unsigned long bgcolor;
    unsigned long pad028;
    GifTag_FAB40 giftag0;       /* 0x030 */
    GsFbp_FAB40 frame0;         /* 0x040 */
    unsigned long draw0[15];
    GifTag_FAB40 giftag1;       /* 0x0C0 */
    GsFbp_FAB40 frame1;         /* 0x0D0 */
    unsigned long draw1[15];
    short display_width;        /* 0x150 */
    short display_height;
    short psm;
    short fbp0;
    short storage_width;        /* 0x158 */
    short storage_height;
    short storage_psm;
    short fbp1;
    short target_width;         /* 0x160 */
    short target_height;
    short target_psm;
    short target_fbp;
    short display_offset_x;     /* 0x168 */
    short display_offset_y;
    short zpsm;
    short zbp;
    int reserved170;            /* 0x170 */
} FsAa_FAB40;

#define MACRO_ADDR __attribute__((section(".sdata")))
extern FsAa_FAB40 D_001A6480;
extern void *D_001A742C MACRO_ADDR;
extern int D_001A72D8 MACRO_ADDR, D_001A72DC MACRO_ADDR, D_001A72E0 MACRO_ADDR;
extern int D_001A7BB8 MACRO_ADDR;
extern int D_001A7438[] __attribute__((sda)), D_001A743C[] __attribute__((sda));
extern int D_001A7440[] __attribute__((sda)), D_001A7444[] __attribute__((sda));
extern int D_001A7448[] __attribute__((sda)), D_001A744C[] __attribute__((sda));
extern int D_001A7450[] __attribute__((sda)), D_001A7454[] __attribute__((sda));
extern int D_001A7458[] __attribute__((sda)), D_001A745C[] __attribute__((sda));
extern int D_001A7460[] __attribute__((sda)), D_001A7464[] __attribute__((sda));
extern char D_001A6860[], D_001A6600[], D_001A6D40[], D_001A6E90[];
extern char D_00138850[], D_00138990[], D_00138AD0[], D_00138DC0[], D_001390B0[];
extern void func_00125A20(void *, short, short, short, short, short);
extern int func_00125F20(void *, short, short, short, short, short);
extern void func_00284088(int, int);
extern void func_0011AEA0(int);
extern void func_00282AB0(void *, void *, int);

#define FA ((FsAa_FAB40 *)D_001A742C)

void func_00284268(int display_width, int display_height, int storage_width, int storage_height,
                   int display_offset_x, int display_offset_y) {
    unsigned long *q;
    unsigned long *out;

    D_001A742C = &D_001A6480;
    D_001A6480.display_width = display_width;
    D_001A6480.display_height = display_height;
    D_001A6480.reserved170 = 0;
    D_001A6480.storage_width = storage_width;
    D_001A6480.storage_height = storage_height;
    D_001A6480.display_offset_x = display_offset_x;
    D_001A6480.display_offset_y = display_offset_y;
    D_001A6480.storage_psm = 1;
    D_001A6480.psm = 0;
    D_001A6480.target_psm = 0;
    D_001A6480.zpsm = 0x31;
    D_001A6480.fbp1 = D_001A72D8 >> 13;
    D_001A6480.fbp0 = D_001A72DC >> 13;
    D_001A6480.zbp = D_001A72E0 >> 13;
    func_00125A20(&D_001A6480, 1, storage_width, storage_height, display_offset_x,
                  display_offset_y);
    FA->dispfb.FBP = D_001A6480.fbp1;
    if (D_001A7BB8) FA->display = 0x1BF4FF00834140UL;
    {
        int dx, dy, magh, magv, dw, dh;
        D_001A7438[0] = dx = FA->display & 0xFFF;
        D_001A743C[0] = dy = (FA->display >> 12) & 0x7FF;
        D_001A7440[0] = magh = (FA->display >> 23) & 0xF;
        D_001A7444[0] = magv = (FA->display >> 27) & 3;
        D_001A7448[0] = dw = (FA->display >> 32) & 0xFFF;
        dh = (FA->display >> 44) & 0x7FF;
        D_001A7450[0] = dx;
        D_001A7454[0] = dy;
        D_001A7458[0] = magh;
        D_001A745C[0] = magv;
        D_001A7460[0] = dw;
        D_001A7464[0] = dh;
        D_001A744C[0] = dh;
    }
    func_00125F20(&FA->frame0, D_001A6480.psm, D_001A6480.display_width,
                  D_001A6480.display_height, 3, D_001A6480.zpsm);
    FA->frame0.FBP = D_001A6480.fbp0;
    *(long *)&FA->draw0[1] =
        (long)D_001A6480.zbp | ((unsigned long)(D_001A6480.zpsm & 0xF) << 24);
    *(u128_FAB40 *)&FA->giftag0 = 0;
    FA->giftag0.NLOOP = 8;
    FA->giftag0.EOP = 1;
    FA->giftag0.NREG = 1;
    FA->giftag0.REGS0 = 0xE;
    func_00125F20(&FA->frame1, D_001A6480.storage_psm, D_001A6480.storage_width,
                  D_001A6480.storage_height, 0, 0);
    FA->frame1.FBP = D_001A6480.fbp1;
    *(long *)&FA->draw1[1] = 1UL << 32;
    *(u128_FAB40 *)&FA->giftag1 = 0;
    FA->giftag1.NLOOP = 8;
    FA->giftag1.EOP = 1;
    FA->giftag1.NREG = 1;
    FA->giftag1.REGS0 = 0xE;

    q = (unsigned long *)D_001A6860;
    out = q;
    *out++ = 0x408B400000000001UL;
    *out++ = 0xEEEE;
    *out++ = 0x30000;
    *out++ = 0x47;
    *out++ = 5;
    *out++ = 8;
    *out++ = 0x100000261UL;
    *out++ = 0x14;
    *out++ = (((long)FA->fbp0 << 5) | ((long)((FA->display_width >> 6) & 0x3F) << 14) |
           ((long)FA->psm << 20)) | 0xEA8000000UL;
    *out++ = 6;
    *out++ = 0x4400000000008010UL;
    *out = 0x5353;
    if (D_001A7BB8) {
        volatile unsigned long *p;
        int i;
        for (i = 0, p = q + 12; i < 16; i++) {
            *p++ = i * FA->display_width;
            *p++ = (i * 0x280 + (0x8000 - FA->storage_width * 8)) |
                   ((long)(0x7FF8 - FA->storage_height * 8) << 16);
            *p++ = (i + 1) * FA->display_width | ((long)FA->display_height << 20);
            *p++ = ((i + 1) * 0x280 + (0x8000 - FA->storage_width * 8)) |
                   ((long)(FA->storage_height * 8 + 0x7FF8) << 16);
        }
    } else {
        volatile unsigned long *p;
        int i;
        for (i = 0, p = q + 12; i < 16; i++) {
            *p++ = i * FA->display_width;
            *p++ = (i * FA->storage_width + (0x8000 - FA->storage_width * 8)) |
                   ((long)(0x7FF8 - FA->storage_height * 8) << 16);
            *p++ = (i + 1) * FA->display_width | ((long)FA->display_height << 20);
            *p++ = ((i + 1) * FA->storage_width + (0x8000 - FA->storage_width * 8)) |
                   ((long)(FA->storage_height * 8 + 0x7FF8) << 16);
        }
    }
    out = q + 76;
    *out++ = 0x4400000000008001UL;
    *out++ = 0x4410;
    *out++ = 0x181;
    *out++ = 0x80000000UL;
    *out++ = (0x7FF8 - FA->storage_width * 8) | ((long)(0x7FF8 - FA->storage_height * 8) << 16);
    *out++ = (0x7FF8 - FA->storage_width * 8) | ((long)(FA->storage_height * 8 + 0x7FF8) << 16);

    func_00284088(0, 0);

    q = (unsigned long *)D_001A6600;
    out = q;
    *out++ = 0x408B400000000001UL;
    *out++ = 0xEEEE;
    *out++ = 0x31001;
    *out++ = 0x47;
    *out++ = 5;
    *out++ = 8;
    *out++ = 0x100000261UL;
    *out++ = 0x14;
    *out++ = (((long)FA->fbp0 << 5) | ((long)((FA->display_width >> 6) & 0x3F) << 14) |
           ((long)FA->psm << 20)) | 0xEA8000000UL;
    *out++ = 6;
    *out++ = 0x4400000000008010UL;
    *out = 0x5353;
    {
        volatile unsigned long *p = q + 12;
        int i;
        for (i = 0; i < 16; i++) {
            *p++ = i << 9;
            *p++ = (i * 0x200 + 0x7000) | ((long)(0x8000 - FA->display_height * 8) << 16);
            *p++ = (i * 0x200 + 0x200) | ((long)FA->display_height << 20);
            *p++ = (i * 0x200 + 0x7200) | ((long)(FA->display_height * 8 + 0x7FF0) << 16);
        }
    }

    q = (unsigned long *)D_001A6D40;
    out = q;
    *out++ = 0x1000000000000001UL;
    *out++ = 0xE;
    *out++ = 0x30000;
    *out++ = 0x47;
    *out++ = 0x2400000000008001UL;
    *out++ = 0x10;
    *out++ = 0x106;
    *out++ = 0x80000000UL;
    *out++ = 0x2400000000008010UL;
    *out = 0x44;
    {
        volatile unsigned long *p = q + 10;
        int i;
        for (i = 0; i < 16; i++) {
            *p++ = (i * 0x200 + 0x6FF8) | ((long)(0x7FF8 - FA->display_height * 8) << 16);
            *p++ = (i * 0x200 + 0x71F8) | ((long)(FA->display_height * 8 + 0x7FF8) << 16);
        }
    }

    func_00282AB0(D_001A6E90, D_001A6D40, 0x150);

    q = (unsigned long *)D_00138850;
    {
        volatile unsigned long *p = q + 8;
        int i;
        for (i = 0; i < 16; i++) {
            *p++ = (i * 0x200 + 0x6FF8) | ((long)(0x7FF8 - FA->display_height * 8) << 16);
            *p++ = (i * 0x200 + 0x71F8) | ((long)(FA->display_height * 8 + 0x7FF8) << 16);
        }
    }

    q = (unsigned long *)D_00138990;
    {
        unsigned long *p = q + 8;
        int i;
        for (i = 0; i < 16; i++) {
            if (D_001A7BB8) {
                *p++ = (i * 0x280 + 0x6BF8) | ((long)(0x7FF8 - FA->storage_height * 8) << 16);
                *p++ = ((i + 1) * 0x280 + 0x6BF8) | ((long)(FA->storage_height * 8 + 0x7FF8) << 16);
            } else {
                *p++ = (i * 0x200 + 0x6FF8) | ((long)(0x7FF8 - FA->storage_height * 8) << 16);
                *p++ = ((i + 1) * 0x200 + 0x6FF8) | ((long)(FA->storage_height * 8 + 0x7FF8) << 16);
            }
        }
    }

    q = (unsigned long *)D_00138AD0;
    {
        unsigned int y = 0, x = 0;
        int i;
        volatile unsigned long *p = q + 24;
        for (i = 0; i < 16; i++) {
            *p++ = x;
            *p++ = y;
            x += 0x200;
            *p++ = x | ((long)FA->display_height << 20);
            y += 0x100;
            *p++ = y | 0x10000000;
        }
    }

    q = (unsigned long *)D_00138DC0;
    {
        unsigned int y = 0, x = 0;
        int i;
        volatile unsigned long *p = q + 24;
        for (i = 0; i < 16; i++) {
            *p++ = x;
            *p++ = y;
            x += 0x200;
            *p++ = x | ((long)FA->display_height << 20);
            y += 0x40;
            *p++ = y | 0x4000000;
        }
    }

    {
        unsigned long *r = (unsigned long *)D_001390B0;
        int fbp = D_001A72DC;
        r[2] = ((long)fbp >> 13) | 0xFFFFFF00080000UL;
        r[10] = ((fbp >> 8) | 0x24020000) | 0x640000000UL;
    }
    func_0011AEA0(0);
}
