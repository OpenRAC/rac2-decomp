/* 6 November 2026: -g ties at 556; -fno-gcse 540; sdk 572. Swapping the delay set before the server read ties. Retail sched2 puts 9999 before the volatile server load, so dbr steals it into the bgez slot and the loop label needs one more alignment nop. */
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
typedef struct {
    u8 reserved[0x24];
    void *volatile server;
} SoundRpcClient;

typedef struct {
    volatile int read_active;
    u8 reserved[12];
    volatile int read_error;
} SoundReadState;

typedef struct {
    u8 *first, *second;
} SoundBufferPair;

extern u8 D_00146CC0[], D_00147CC0[];
extern u8 D_00148CC0[], D_00149CC0[], D_0014ACC0[], D_0014B100[];
extern u8 *D_001A74A0[] SDATA(D_001A74A0) __attribute__((sda));
extern u8 *D_001A74B0[] SDATA(D_001A74B0) __attribute__((sda));
extern u8 *D_001A74B8[] SDATA(D_001A74B8) __attribute__((sda));
extern u8 *D_001A74A4[] __attribute__((sda));
extern SoundBufferPair command_pair __asm__("D_001A74B0");
extern u8 *D_001A74BC[] __attribute__((sda));
extern int D_001A74F8[] SDATA(D_001A74F8) __attribute__((sda));
extern int D_001A74C8[] SDATA(D_001A74C8) __attribute__((sda));
extern int D_001A74D0[] SDATA(D_001A74D0) __attribute__((sda));
extern int D_001A74A8[] SDATA(D_001A74A8) __attribute__((sda));
extern int D_001A74AC[] __attribute__((sda));
extern volatile long D_001A74D8[] __attribute__((sda));
extern int D_001A7180[] __attribute__((sda));
extern u8 D_001A7040[] __attribute__((sda));
extern u8 D_001A7140[] __attribute__((sda));
extern volatile int D_001A7100[] __attribute__((sda));
extern volatile int D_001A7110[] __attribute__((sda));
extern void *volatile D_001A7064[] __attribute__((sda));
extern void *volatile D_001A7164[] __attribute__((sda));
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
        volatile int *read_active;
        int options;
    } init;
    u8 *const command_buffer1 = D_00147CC0;
    u8 *const command_buffer0 = D_00146CC0;

    D_001A74A0[0] = command_buffer0;
    D_001A74A4[0] = command_buffer1;
    D_001A74B8[0] = D_0014ACC0;
    D_001A74BC[0] = D_0014B100;
    D_001A74B0[0] = D_00148CC0;
    command_pair.second = D_00149CC0;
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
        server = D_001A7064[0];
        delay = 10000;
        for (delay--; delay != -1; delay--) {}
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
        server = D_001A7164[0];
        delay = 10000;
        for (delay--; delay != -1; delay--) {}
    } while (server == 0);

    *(int *)D_00146CC0 = 0;
    D_001A7100[0] = 0;
    *(int *)D_00147CC0 = 0;
    D_001A7110[0] = 0;
    D_001A74A8[0] = 0xFFC;
    D_001A74AC[0] = 0xFFC;
    init.read_active = D_001A7100;
    init.options = options;
    return func_00132C48(0, 8, &init);
}
