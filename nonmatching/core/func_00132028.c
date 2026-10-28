/* SDATA follow-up: an incomplete count table with SDATA still compiles to
 * 484/488 bytes under -mno-split-addresses; the default profile gives 468.
 * An explicit GP alias without the section attribute also remains 484/488.
 * Address metadata alone does not separate the indexed address from its load.
 * Reopen with new source-lifetime or compiler address-formation evidence.
 */
/* func_00132028 (989snd command pump, rac1 func_0012DDC0 twin), 488 bytes, boot.
 * 26 October 2026 (M32): 484/488 as its own unit src/core/00132028-g8.c with
 * -O2 -G8 -ffunction-sections -mno-split-addresses and the declarations below:
 * sda scalars for the $gp words, NOT_SDA for the doubleword D_001A74D8 (keeps it out
 * of the jalr slot, retail's lui/ld + lui $at/sd), plain D_001A7084[] and sda
 * D_001A7180[] (absolute in flow, $gp in the beql slot). Everything matches except
 * the idle-send test: retail forms the count table's address with its own
 * addiu $a0,$gp,-0x7B50 before the indexed load, this cc1 folds it into the load
 * (addu $v1,$v0,$gp; lw %gprel). An incomplete D_001A74A0[] makes it absolute instead
 * (488/488, 2 lines off in both table uses).
 *
 * Earlier notes follow.
 */

/* func_00132028, 488 bytes: 989snd's command pump (rac1's func_0012DDC0 twin).
   Once the pending RPC completes it runs the return callback or the callbacks
   queued with the other command buffer; it finishes a CD read (cache flush,
   then the read callback with the reply word); sends the next batch when idle;
   and polls a stop request. Returns whether an RPC or a CD read is still in
   flight. $gp is 0x001AEFF0; D_001A7180, D_001A7084 and the doubleword
   D_001A74D8 are read absolutely (incomplete sda arrays). */

typedef void (*SndCallback)(int, long);
typedef struct {
    SndCallback fn;
    int pad4;
    long arg;
} SndCommand;

extern int D_001A7480 __attribute__((sda));                 /* current buffer */
extern void (*D_001A7490)(int) __attribute__((sda));        /* stop callback */
extern int D_001A7494 __attribute__((sda));                 /* stop requested */
extern int D_001A7498 __attribute__((sda));
extern int D_001A749C __attribute__((sda));                 /* return pending */
extern int *D_001A74A0[2] __attribute__((sda));             /* counts */
extern SndCommand *D_001A74B0[2] __attribute__((sda));      /* commands */
extern int *D_001A74B8[2] __attribute__((sda));             /* replies */
extern int D_001A74C0 __attribute__((sda));                 /* batch index */
extern int D_001A74C4 __attribute__((sda));
extern int D_001A74C8 __attribute__((sda));                 /* CD read pending */
extern SndCallback D_001A74D0 __attribute__((sda));         /* CD read callback */
extern SndCallback D_001A74E0 __attribute__((sda));         /* return callback */
extern long D_001A74E8 __attribute__((sda));                /* its argument */
extern long D_001A74D8 NOT_SDA;
extern int D_001A7180[] __attribute__((sda));
extern int D_001A7084[];

extern int func_00132220(void);
extern void func_0011AEA0(int);
extern void func_00133108(void);
extern int func_00133580(int);

int func_00132028(void)
{
    int i;
    int idx;
    SndCallback fn;
    long arg;

    if (D_001A7480 != 0 && func_00132220() != 0) {
        if (D_001A749C != 0) {
            if (D_001A74E0 != 0)
                D_001A74E0(D_001A7084[0], D_001A74E8);
            D_001A74E0 = 0;
            D_001A749C = 0;
        } else {
            idx = D_001A74C0 != 1;
            for (i = 0; i < *D_001A74A0[idx]; i++) {
                if (D_001A74B0[idx][i].fn != 0)
                    D_001A74B0[idx][i].fn(D_001A74B8[idx][i + 1], D_001A74B0[idx][i].arg);
            }
        }
    }
    if (D_001A74C8 != 0) {
        func_0011AEA0(0);
        if (D_001A7180[0] != 0xFFFFFFFF) {
            if (D_001A74D0 != 0) {
                arg = D_001A74D8;
                fn = D_001A74D0;
                D_001A74D0 = 0;
                D_001A74D8 = 0;
                fn(D_001A7180[0], arg);
            }
            D_001A7180[0] = 0;
            D_001A74C8 = 0;
        }
    }
    if (D_001A7480 == 0) {
        if (*D_001A74A0[D_001A74C0] != 0 && D_001A74C4 == 0)
            func_00133108();
    }
    if (D_001A7494 != 0) {
        func_00133580(1);
        if (D_001A7498 != 0) {
            D_001A7494 = 0;
            D_001A7498 = 0;
            if (D_001A7490 != 0)
                D_001A7490(1);
        }
    }
    return D_001A7480 != 0 || D_001A74C8 != 0;
}

/* from src/core/00131780.c: not attempted to a match; it needs the same -g8
 * sibling unit func_001326D8 now has, and the symbol map below.
 *
 * SDK snd_Pump (symbol_addrs's own name), 488 bytes. It reaches sixteen
 * globals through $gp at GP 0x001AEFF0 - `-0x7B70` is D_001A7480, `-0x7B68`
 * D_001A7488, `-0x7B60` D_001A7490, `-0x7B5C` D_001A7494, `-0x7B58`
 * D_001A7498, `-0x7B54` D_001A749C, `-0x7B50` D_001A74A0, `-0x7B40`
 * D_001A74B0, `-0x7B38` D_001A74B8, `-0x7B30` D_001A74C0, `-0x7B2C`
 * D_001A74C4, `-0x7B28` D_001A74C8, `-0x7B20` D_001A74D0, `-0x7B10`
 * D_001A74E0 and `-0x7B08` D_001A74E8 - and three absolutely: the sentinel
 * D_001A7180 (also the `-0x7E70` gp slot), D_001A7084 and the doubleword
 * D_001A74D8.
 *
 * Shape, for whoever picks it up: return 0 at once unless D_001A74C8 is set
 * and func_00132220() agrees; then walk the records of D_001A74B0/
 * D_001A74B8/D_001A74A0 - each entry is 16 bytes with a handler at +0 and an
 * argument at +8, called through `jalr` with the second table's word as the
 * argument - and drop the pending callback (D_001A74D0 with the doubleword
 * D_001A74D8) once the sentinel has moved. The tail sets D_001A74C8 for the
 * busy window the func_00132498/func_001326D8 pair tests, runs
 * func_001133108/func_00133580(1) and an indirect D_001A7490 callback, and
 * returns 1 only when D_001A7480 is clear and D_001A74C8 ends up set.
 *
 * Spent: the disassembly and the symbol map above, by the worker that matched
 * func_001326D8 in the same unit; no compile, because the -g8 route is a
 * prerequisite and the body is 488 bytes of indirect calls.
 */
