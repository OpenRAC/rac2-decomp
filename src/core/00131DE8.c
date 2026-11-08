/* func_00131DE8 (snd_StartSoundSystem): binds the two sound RPC servers, waits for them and sends
 * the init request. A game-compiler unit of its own (00131780.c is an SDK unit). The last stores
 * before the request's jal are the plain payload stores and then the volatile D_001A7110 store;
 * the compiler's default set-side volatile rule (GCC 2.95's) leaves that slot empty, as retail
 * does, where the EE tree's rule fills it with `move $a2,$sp` (docs/COMPILER-NOTES.md). */
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
typedef struct {
    void *paddr;
    unsigned int pid;
    int tid;
    unsigned int mode;
} SifRpcData;
typedef struct {
    SifRpcData rpcd;
    unsigned int command;
    void *buff;
    void *cbuff;
    void (*func)(void *);
    void *para;
    void *serve;
} SifClientData;
extern SifClientData D_001A7040 __attribute__((sda));
extern SifClientData D_001A7140 __attribute__((sda));
/* The CD read status block at 0x001A7100..0x001A713F (RAC1's CdSafeState: count at 0,
 * error at 0x10) is written by the IOP, so its fields are volatile. RAC2's retail EE
 * code shows that second writer (no IOP code is read):
 * - this function hands the block's address to the IOP: init.read_active is copied
 *   into the RPC send buffer and sent by func_00132C48 through sceSifCallRpc
 *   (func_0011D620) on the sound client;
 * - func_001334B8 stores the count and error, then calls func_0011B3D0(0x001A7100,
 *   0x001A713F), SyncDCache (DIntr, _sceSDC's index writeback-invalidate of each
 *   cache line in the range, EIntr), before asking the IOP for the read;
 * - func_00133580 calls func_0011B500 on the same range, InvalidDCache (_sceIDC's
 *   index invalidate, no writeback), before each poll read of the count. Discarding
 *   the cached lines unwritten is only right for memory another bus master writes.
 * _sceSDC (0x0011B328) and _sceIDC (0x0011B458) are symbol_addrs' digest-matched SDK
 * names (USA v1.01 addresses). 001334B8-g8.c declares the same two fields volatile. */
extern volatile int D_001A7100[] __attribute__((sda));
extern volatile int D_001A7110[] __attribute__((sda));
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
    void *server1;
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
        bind_result = func_0011D450(&D_001A7040, 0x123456, 0);
        if (bind_result < 0) {
            func_00115D48(D_001A7500, D_001A7528, 0xB1);
            for (;;) {}
        }
        delay = 9999;
        server = D_001A7040.serve;
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
        bind_result = func_0011D450(&D_001A7140, 0x123457, 0);
        if (bind_result < 0) {
            func_00115D48(D_001A7500, D_001A7528, 0xC6);
            for (;;) {}
        }
        delay = 9999;
        server1 = D_001A7140.serve;
        do {
            delay--;
        } while (delay != -1);
    } while (server1 == 0);

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
