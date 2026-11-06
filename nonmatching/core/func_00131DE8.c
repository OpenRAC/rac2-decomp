/* 6 November 2026, round ten: 572/576 bytes, 0/1 USA boot, 25 differing
 * instruction positions after relocation (was 32). Same game -O2 -G0 unit.
 * D_001A7100/D_001A7110 are the CdSafeState count and error that the IOP
 * writes through SIF DMA; AGENTS.md allows volatile there (001334B8-g8.c already
 * declares them so). Volatile on them keeps retail's store order: 7100 first,
 * 7110 last after the payload, with no one-pass groups. The tail now equals
 * retail's sched2 order; only reorg still moves `daddu $a2,$sp` into the jal
 * slot (retail: nop). -frac2-sticky-volatile-refs, an array payload and
 * a 45-step tail hill-climb do not change it. Volatile on the RPC server
 * fields changes nothing. Server/limit registers remain: global alloc ranks
 * server (refs 10, live 10) above each hoisted -1 limit (refs 5, live 6).
 * Unit flags -fno-sched-interblock, -fno-schedule-insns (34 rows) and nine
 * other -fno-* flags do not help; split server locals, a limit local and
 * server-before-delay (556) neither. About 45 check.py runs.
 */
/* 6 November 2026, plain-C follow-up (supersedes the qualified source below).
 * Game -O2 -G0 -ffunction-sections, separate unit; USA boot check.py only:
 * removing all volatile qualifiers from the previous best gives 552/576 bytes,
 * 0/1 places, 70 differing instruction positions after resolving relocations.
 * Retained below: 572/576 bytes, 0/1 places, 32 differing instruction positions.
 * The complete first block and both 9999 bgez delay slots now match. A one-pass
 * group around each real server snapshot plus a decrement-first do/while delay
 * prevents speculative slot filling without an extra loop guard. Both snapshots
 * still precede their busy delays. Reordering the independent initialization
 * stores and grouping the two read-state clears improves the tail further.
 * Remaining: server v1 / loop limit a0 instead of retail a0 / v1 (five words
 * per bind loop), and final store/argument scheduling with a filled jal slot
 * instead of retail's nop; the epilogue is four bytes early.
 * New controls: separate per-loop locals, nested decrement groups, reusing the
 * bind result for the delay, explicit loop-limit locals, scalar/read-state
 * owner views, sda client fields and bounded final-store permutations. None
 * resolves the remaining allocation/tail scheduling. Non-sda globals worsen
 * address forms; unsigned limit comparisons materialize 0xFFFFFFFF in two
 * instructions and are not a remedy. About 200 check.py calls, no linked build.
 * No volatile qualifiers, inline instruction asm, macro symbol aliases,
 * hardcoded addresses, padding locals, dead stores or use-before-set remain.
 * Existing file-scope symbol names for the real two-pointer buffer pairs are
 * retained; they are declarations, not inline instruction sequences.
 * Next: explain the server/limit allocation and final-store scheduling from
 * compiler dumps with this plain-C input. Old volatile-specific measurements
 * below are historical, not evidence that the new rule permits that method.
 */
/* Superseded history, 6 November 2026, hill-climb: ~380 runs over independent store orders and server/delay
 * order give the C below, 80 -> 78 rows (volatile read_active/read_error order kept). No
 * order puts 9999 ahead of the volatile server load, so the bgez slot still differs.
 */
/* 6 November 2026: new best C below (556/576, 0/1 USA, 80 differing rows after relocation
 * noise, was 108). Same game -O2 -G0 separate unit (the SDK profile gives frame 0xB0). Each
 * buffer pair is one array, [0] through the SDATA gp name and [1] through a plain sda alias of
 * the same symbol: sym+4 is a two-instruction macro store (`lui $at; sw`), so it stays out of
 * the beqz delay slot and the whole first block now equals retail. Left: retail sets the 9999
 * delay count first in the bgez target so reorg pulls it into that slot; here the volatile
 * server load is scheduled first and the slot takes the error-path argument, which shifts
 * the rest (server a0/-1 v1 in retail). No change from: delay set before the server read,
 * delay-- before it, bind_result reused as the counter; delay set before the bind test (584);
 * -fno-gcse (540); -fno-schedule-insns.
 */
/* Newly reconstructed sound initializer near miss, 2 November 2026.
 * Profile: game -O2 -G0 -ffunction-sections, separate unit.
 * Retained source:556/576 bytes,0/1 USA boot; frame0x40 and five saved GPRs.
 * Nine bounded checks: gameG8 pair596; SDK572 with wrongframe0xB0;
 * G8scalars612; opaqueG0/SDATA588; direct server fields572/frame0x50;
 * direct read-state fields572/frame0x40; explicit server snapshots556;
 * real buffer-pair field556(tie); SDApair/earlier delay birth584/frame0x50.
 * The retained556-byte form reads each RPC server before its busy delay,
 * matching the observed asynchronous sampling order; do not prefer a shorter
 * snapshot-free wording that reads after the delay merely by size.
 * Complete8-byte init payload contains the read-state pointer and options;
 * return is the real32-bit SendIOPCommandAndWait result. Bind/InitRpc/
 * diagnostic contracts were checked against current definitions. Direct
 * server/read-state views and the buffer-pair prefix name actual fields;
 * incomplete address views do not guess the owners' full extents.
 * Remaining: initial absolute/GP store forms, register allocation, spin-loop
 * constant birth and scheduling. Reopen with independently justified original
 * buffer/client declaration lifetimes, not invented volatile or barriers.
 * USA v2.00/PAL have no separate row: their old main row still includes this
 * body. No other-release or linked match; production marker restored.
 */
#include "common.h"

/* Adapted from RAC1's GPL-3.0 989snd.c StartSoundSystem reconstruction,
 * originally from Lombyte; declarations and the eight-byte init payload
 * follow the RAC2 retail caller and RPC consumers.
 */
extern u8 D_00146CC0[], D_00147CC0[];
extern u8 D_00148CC0[], D_00149CC0[], D_0014ACC0[], D_0014B100[];
extern u8 *D_001A74A0[] SDATA(D_001A74A0) __attribute__((sda));
extern u8 *D_001A74A0_pair[] __asm__("D_001A74A0") __attribute__((sda));
extern u8 *D_001A74B0[] SDATA(D_001A74B0) __attribute__((sda));
extern u8 *D_001A74B0_pair[] __asm__("D_001A74B0") __attribute__((sda));
extern u8 *D_001A74B8[] SDATA(D_001A74B8) __attribute__((sda));
extern u8 *D_001A74B8_pair[] __asm__("D_001A74B8") __attribute__((sda));
extern int D_001A74F8[] SDATA(D_001A74F8) __attribute__((sda));
extern int D_001A74C8[] SDATA(D_001A74C8) __attribute__((sda));
extern int D_001A74D0[] SDATA(D_001A74D0) __attribute__((sda));
extern int D_001A74A8[] SDATA(D_001A74A8) __attribute__((sda));
extern int D_001A74AC[] __attribute__((sda));
extern long D_001A74D8[] __attribute__((sda));
extern int D_001A7180[] __attribute__((sda));
extern u8 D_001A7040[] __attribute__((sda));
extern u8 D_001A7140[] __attribute__((sda));
/* CdSafeState count and error (RAC1 sound_read_work): the IOP writes them through
 * SIF DMA, as in 001334B8-g8.c, so they are volatile. */
extern volatile int D_001A7100[] __attribute__((sda));
extern volatile int D_001A7110[] __attribute__((sda));
extern void *D_001A7064[] __attribute__((sda));
extern void *D_001A7164[] __attribute__((sda));
extern char D_001A7500[], D_001A7528[];

extern void func_0011CF78(int);
extern int func_0011D450(void *, int, int);
extern void func_00115D48(const char *, ...);
extern int func_00132C48(int, int, void *);

int func_00131DE8(int options)
{
    int bind_result;
    int delay;
    void *server;
    struct {
        int *read_active;
        int options;
    } init;
    u8 *const command_buffer1 = D_00147CC0;
    u8 *const command_buffer0 = D_00146CC0;

    D_001A74A0[0] = command_buffer0;
    D_001A74A0_pair[1] = command_buffer1;
    D_001A74B8[0] = D_0014ACC0;
    D_001A74B8_pair[1] = D_0014B100;
    D_001A74B0[0] = D_00148CC0;
    D_001A74B0_pair[1] = D_00149CC0;
    if (options & 2)
        D_001A74F8[0] = 1;
    else
        D_001A74F8[0] = 0;
    func_0011CF78(0);

    for (;;) {
        bind_result = func_0011D450(D_001A7040, 0x123456, 0);
        if (bind_result < 0) {
            func_00115D48(D_001A7500, D_001A7528, 0xB1);
            for (;;) {}
        }
        delay = 9999;
        do {
            server = D_001A7064[0];
        } while (0);
        do {
            delay--;
        } while (delay != -1);
        if (server != 0)
            break;
    }

    D_001A74C8[0] = 0;
    D_001A74D0[0] = 0;
    D_001A74D8[0] = 0;
    D_001A7180[0] = 0;

    do {
        bind_result = func_0011D450(D_001A7140, 0x123457, 0);
        if (bind_result < 0) {
            func_00115D48(D_001A7500, D_001A7528, 0xC6);
            for (;;) {}
        }
        delay = 9999;
        do {
            server = D_001A7164[0];
        } while (0);
        do {
            delay--;
        } while (delay != -1);
    } while (server == 0);

    D_001A7100[0] = 0;
    *(int *)D_00146CC0 = 0;
    *(int *)D_00147CC0 = 0;
    D_001A74A8[0] = 0xFFC;
    D_001A74AC[0] = 0xFFC;
    init.read_active = D_001A7100;
    init.options = options;
    D_001A7110[0] = 0;
    return func_00132C48(0, 8, &init);
}
