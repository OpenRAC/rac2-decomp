#include "names.h"
/* func_00131DE8 (snd_StartSoundSystem): binds the two sound RPC servers, waits for them and sends
 * the init request. A game-compiler unit of its own (00131780.c is an SDK unit). The last stores
 * before the request's jal are the plain payload stores and then the volatile D_001A7110 store;
 * the compiler's default set-side volatile rule (GCC 2.95's) leaves that slot empty, as retail
 * does, where the EE tree's rule fills it with `move $a2,$sp` (docs/build/compiler-notes.md). */
#include "common.h"

/* Adapted from RAC1's GPL-3.0 989snd.c StartSoundSystem reconstruction,
 * originally from Lombyte; declarations and the eight-byte init payload
 * follow the RAC2 retail caller and RPC consumers.
 */
extern u8 g_snd_command_buffer0[], g_snd_command_buffer1[];
extern u8 g_snd_buffer_a[], g_snd_buffer_b[], g_snd_buffer_c[], g_snd_buffer_d[];
extern u8 *g_snd_command_buffers[] SDATA(D_001A74A0) __attribute__((sda));
extern u8 *D_001A74A0_pair[] __asm__("D_001A74A0") __attribute__((sda));
extern u8 *g_snd_callback_tables[] SDATA(D_001A74B0) __attribute__((sda));
extern u8 *D_001A74B0_pair[] __asm__("D_001A74B0") __attribute__((sda));
extern u8 *g_snd_reply_buffers[] SDATA(D_001A74B8) __attribute__((sda));
extern u8 *D_001A74B8_pair[] __asm__("D_001A74B8") __attribute__((sda));
extern int g_snd_quiet_flag[] SDATA(D_001A74F8) __attribute__((sda));
extern int g_snd_cd_read_active[] SDATA(D_001A74C8) __attribute__((sda));
extern int g_snd_cd_read_callback[] SDATA(D_001A74D0) __attribute__((sda));
extern int g_snd_command_space_left[] SDATA(D_001A74A8) __attribute__((sda));
extern int g_snd_command_space_extra[] __attribute__((sda));
extern long g_snd_cd_read_callback_arg[] __attribute__((sda));
extern int g_bank_rpc_result[] __attribute__((sda));
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
extern SifClientData g_sound_rpc_client __attribute__((sda));
extern SifClientData g_bank_rpc_client __attribute__((sda));
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
extern volatile int g_cd_read_count[] __attribute__((sda));
extern volatile int g_cd_read_error[] __attribute__((sda));
extern char g_str_snd_error_format[], g_str_snd_source_file[];

extern void sceSifInitRpc(int);
extern int sceSifBindRpc(void *, int, int);
extern void printf(const char *, ...);
extern int snd_SendCommandSync(int, int, void *);

/* Starts the sound system: connects to the two sound servers on the IOP, resets the sound buffers and sends the first setup request. */
int snd_StartSoundSystem(int options)
{
    int bind_result;
    int delay;
    void *server;
    void *server1;
    struct {
        int *read_active;
        int options;
    } init;
    u8 *const command_buffer1 = g_snd_command_buffer1;
    u8 *const command_buffer0 = g_snd_command_buffer0;

    g_snd_command_buffers[0] = command_buffer0;
    D_001A74A0_pair[1] = command_buffer1;
    g_snd_reply_buffers[0] = g_snd_buffer_c;
    D_001A74B8_pair[1] = g_snd_buffer_d;
    g_snd_callback_tables[0] = g_snd_buffer_a;
    D_001A74B0_pair[1] = g_snd_buffer_b;
    if (options & 2)
        g_snd_quiet_flag[0] = 1;
    else
        g_snd_quiet_flag[0] = 0;
    sceSifInitRpc(0);

    for (;;) {
        bind_result = sceSifBindRpc(&g_sound_rpc_client, 0x123456, 0);
        if (bind_result < 0) {
            printf(g_str_snd_error_format, g_str_snd_source_file, 0xB1);
            for (;;) {}
        }
        delay = 9999;
        server = g_sound_rpc_client.serve;
        do {
            delay--;
        } while (delay != -1);
        if (server != 0)
            break;
    }

    g_snd_cd_read_active[0] = 0;
    g_snd_cd_read_callback[0] = 0;
    g_snd_cd_read_callback_arg[0] = 0;
    g_bank_rpc_result[0] = 0;

    do {
        bind_result = sceSifBindRpc(&g_bank_rpc_client, 0x123457, 0);
        if (bind_result < 0) {
            printf(g_str_snd_error_format, g_str_snd_source_file, 0xC6);
            for (;;) {}
        }
        delay = 9999;
        server1 = g_bank_rpc_client.serve;
        do {
            delay--;
        } while (delay != -1);
    } while (server1 == 0);

    g_cd_read_count[0] = 0;
    *(int *)g_snd_command_buffer0 = 0;
    *(int *)g_snd_command_buffer1 = 0;
    g_snd_command_space_left[0] = 0xFFC;
    g_snd_command_space_extra[0] = 0xFFC;
    init.read_active = g_cd_read_count;
    init.options = options;
    g_cd_read_error[0] = 0;
    return snd_SendCommandSync(0, 8, &init);
}
