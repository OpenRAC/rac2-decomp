#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned char u8;

/* func_003512B8 : rounds a field to a multiple of 2048 under a semaphore */
extern s32 WaitSema(s32);

extern s32 SignalSema(s32);

/* func_00351268 : waits, then combines two fields shifted by 11 */
extern s32 WaitSema(s32 a0);

extern s32 SignalSema(s32 a0);

extern void sceMpegAddStrCallback();

extern void mpeg_vibuf_get_free_regions(int *owner, int *first_address, int *first_count,
                         int *second_address, int *second_count);

extern int mpeg_vibuf_get_queued_bytes(unsigned char *owner);

typedef unsigned int u32;

extern int voBufIsFull(unsigned char *);

extern s32 DIntr(void);

extern s32 func_0011F628(void);

/* Rounds the waiting byte count up to a whole 2048-byte sector. */
void mpeg_vibuf_align_pending_bytes(u8 *buf) {
    WaitSema(*(s32 *)(buf + 0x40));
    *(s32 *)(buf + 0x14) = (*(s32 *)(buf + 0x14) + 0x7ff) / 0x800 * 0x800;
    SignalSema(*(s32 *)(buf + 0x40));
}

/* func_00351578 is matched in 00351578.c. */

typedef struct { unsigned long long first, second; int offset, count; } Transfer_3518F0;

extern int viBufModifyPts(void *, Transfer_3518F0 *);

/* a % b as a helper: once inlined, its zero-divisor check is tested against $0 */
static inline int ring_mod(int a, int b) { return a % b; }

/* func_00351310 : walks the transfer ring, trimming one message out of the slots */
int viBufModifyPts(void *owner, Transfer_3518F0 *message)
{
    char *self = (char *)owner;
    Transfer_3518F0 *slot;
    int index = (*(int *)(self + 0x5C) - *(int *)(self + 0x58) + *(int *)(self + 0x54)) %
                *(int *)(self + 0x54);
    int unit = *(int *)(self + 0x8) << 11;
    int go = 1;

    if (*(int *)(self + 0x58) > 0) {
        while (go && (slot = *(Transfer_3518F0 **)(self + 0x50) + index)->count != 0 &&
                     message->count != 0) {
            if (ring_mod(slot->offset + unit - message->offset, unit) < message->count) {
                int take = message->offset + message->count - slot->offset;
                if (slot->count < take) {
                    take = slot->count;
                }
                slot->offset = (slot->offset + take) % unit;
                slot->count = slot->count - take;
                if (slot->count == 0) {
                    if ((long long)slot->first >= 0) {
                        slot->first = -1;
                        slot->second = -1;
                        slot->offset = 0;
                        slot->count = 0;
                    }
                    *(int *)(self + 0x58) = (*(int *)(self + 0x58) - 1 < 0) ?
                                             0 : *(int *)(self + 0x58) - 1;
                }
            } else {
                go = 0;
            }
            index = (index + 1) % *(int *)(self + 0x54);
        }
    }

    return 0;
}

/* Adds a timestamp entry to the video buffer's list, if there is room. */
int mpeg_vibuf_add_timestamp(void *owner, Transfer_3518F0 *message, int unusedArg)
{
    char *self = owner;
    int result = 0;
    WaitSema(*(int *)(self + 0x40));
    if (*(int *)(self + 0x58) < *(int *)(self + 0x54)) {
        viBufModifyPts(self, message);
        if ((long long)message->first >= 0 || (long long)message->second >= 0) {
            (*(Transfer_3518F0 **)(self + 0x50))[*(int *)(self + 0x5C)].first = message->first;
            (*(Transfer_3518F0 **)(self + 0x50))[*(int *)(self + 0x5C)].second = message->second;
            {
                int offset = message->offset;
                (*(Transfer_3518F0 **)(self + 0x50))[*(int *)(self + 0x5C)].offset = offset;
            }
            {
                int count = message->count;
                (*(Transfer_3518F0 **)(self + 0x50))[*(int *)(self + 0x5C)].count = count;
            }
            {
                int next = *(int *)(self + 0x5C) + 1;
                int capacity = *(int *)(self + 0x54);
                *(int *)(self + 0x58) += 1;
                *(int *)(self + 0x5C) = next % capacity;
            }
        }
        result = 1;
    }
    SignalSema(*(int *)(self + 0x40));
    return result;
}

/* func_00351720 is matched in 00351720.c. */


/* Calls an engine helper and returns 1. */
s32 mpeg_call_helper_return_one(void) {
    sceMpegAddStrCallback();
    return 1;
}

/* Passes the free-space query on to the video buffer inside the decoder. */
void mpeg_dec_get_free_regions(unsigned char *owner, int *first_address, int *first_count,
                  int *second_address, int *second_count)
{
    mpeg_vibuf_get_free_regions((int *)(owner + 0x48), first_address, first_count,
                 second_address, second_count);
}

extern void mpeg_vibuf_add_pending_bytes(u8 *, s32);

/* Forwards the byte count to the object's transfer buffer. */
void mpeg_dec_add_pending_bytes(char *object, s32 count) {
    mpeg_vibuf_add_pending_bytes((u8 *)object + 0x48, count);
}

/* Measured target: byte-identical across all 27 levels. */
/* Sets the video decoder's state to 0. */
void mpeg_dec_reset_state(u8 *decoder) { *(s32 *)(decoder + 0xa8) = 0; }

extern void mpeg_vibuf_stop_dma(void *);
extern int mpeg_return_one(void *);

/* Shuts down the video decoder's buffer and then the decoder itself. */
int mpeg_dec_shutdown(u8 *decoder) {
    mpeg_vibuf_stop_dma(decoder + 0x48);
    mpeg_return_one(decoder);
    return 1;
}

/* Sets the video decoder's state to 1. */
void mpeg_dec_set_state_running(u8 *decoder) {s32 state=1;*(s32 *)(decoder+0xa8)=state;}

/* Measured target: byte-identical across all 27 levels. */
s32 videoDecGetState(u8 *a0) { return *(s32 *)(a0 + 0xa8); }

/* Sets the video decoder's state and returns the old state. */
s32 mpeg_dec_swap_state(u8 *decoder, s32 newState) { s32 oldState = *(s32 *)(decoder + 0xa8); *(s32 *)(decoder + 0xa8) = newState; return oldState; }

extern char *g_movie_player_state[] __attribute__((sda));
extern int mpeg_vibuf_add_timestamp(void *, Transfer_3518F0 *, int);

/* Adds a timestamp for a chunk of video data to the decoder's buffer. */
int mpeg_dec_add_timestamp(char *object, unsigned long long first, unsigned long long second, int end, int count)
{
    Transfer_3518F0 transfer;
    transfer.first = first;
    transfer.second = second;
    transfer.offset = end - *(int *)(object + 0x48);
    transfer.count = count;
    return mpeg_vibuf_add_timestamp(g_movie_player_state[0] + 0xD9090, &transfer, *(int *)(object + 0x48));
}

/* Returns how many bytes are waiting in the decoder's video buffer. */
int mpeg_dec_get_queued_bytes(unsigned char *owner)
{
    return mpeg_vibuf_get_queued_bytes(owner + 0x48);
}


/* func_00351960 : builds a 16-byte packet (a 4-byte header copied from D_001AE860 and a
   12-byte body), asks the object for the two memory ranges it holds, and moves them into
   the packet.  The two addresses are turned into 32-bit engine addresses. */
typedef struct { char tag[4]; } Header_351960;

typedef struct { Header_351960 header; char body[12]; } Packet_351960;

extern Header_351960 D_001AE860;

extern s32 mpeg_copy_split_buffer(u32 first_address, s32 first_count, u32 second_address,
                         s32 second_count, u32 packet, s32 header_size, s32 unused1,
                         s32 unused2);

/* These wrappers have different targets in the level programs. */
extern void ref_L00_00351960_00(u8 *, s32 *, s32 *, s32 *, s32 *);
extern void ref_L00_00351960_01(char *, s32);

/* Takes the video data that is ready, sends it for decoding, and marks the decoder as running if idle. */
s32 mpeg_dec_send_packet(u8 *decoder)
{
    Packet_351960 packet;
    s32 first_address, first_count, second_address, second_count;
    s32 result;

    packet.header = D_001AE860;
    ref_L00_00351960_00(decoder, &first_address, &first_count, &second_address, &second_count);
    if (first_count + second_count < 4) {
        return 0;
    }
    result = mpeg_copy_split_buffer((first_address & 0x0FFFFFFF) | 0x20000000, first_count,
                            (second_address & 0x0FFFFFFF) | 0x20000000, second_count,
                            (u32)&packet, 4, 0, 0);
    ref_L00_00351960_01(g_movie_player_state[0] + 0xD9048, result);
    mpeg_vibuf_align_pending_bytes(decoder + 0x48);
    if (*(s32 *)(decoder + 0xA8) == 0) {
        *(s32 *)(decoder + 0xA8) = 2;
    }
    return 1;
}

extern int mpeg_has_no_pictures_decoded(void *);



extern void mpeg_vibuf_reset(void *);
extern void mpeg_vobuf_reset(u8 *);
extern int mpeg_dec_run_loop(void *);
/* Starts the video decoder: resets its buffer, runs the decode loop, and waits until it is told to stop. */
void mpeg_dec_start(unsigned char *object)
{
    char *base;
    mpeg_vibuf_reset(object + 0x48);
    mpeg_vobuf_reset(g_movie_player_state[0] + 0xD9168);
    mpeg_dec_run_loop(object);
    base = g_movie_player_state[0];
    while (*(int *)(base + 0xD9174)) {
        if (videoDecGetState(object) == 1) break;
        base = g_movie_player_state[0];
    }
    mpeg_dec_swap_state(object, 3);
}


extern void STUB_printf();
extern char D_001AE868[];
extern char D_001AE880[];
extern int mpeg_read_indirect_word(void *);
extern void sceMpegReset(void *);
extern int func_0012F950(void *, void *, int);
extern void mpeg_start_decoder_dma(void);
extern void mpeg_set_debug_value(char *);
extern void *mpeg_vobuf_get_next_frame(char *);
extern void mpeg_vobuf_advance_write(u8 *);
extern void mpeg_build_frame_packet(void *, void *, int, int, int);

/* Main video decode loop: waits for a free output frame, decodes into it, and passes it on until stopped. */
int mpeg_dec_run_loop(void *decoder)
{
    int *object = decoder;
    int result = 1;
    void *packet;
    int i;

    while (mpeg_read_indirect_word(object) == 0) {
        if (videoDecGetState((u8 *)object) == 1) {
            result = -1;
            STUB_printf(D_001AE868);
            break;
        }
        while ((packet = mpeg_vobuf_get_next_frame(g_movie_player_state[0] + 0xD9168)) == 0)
            mpeg_start_decoder_dma();
        if (func_0012F950(object, packet, 0x340) < 0)
            mpeg_set_debug_value(D_001AE880);
        if (object[2] == 0) {
            int a = object[0];
            int b = object[1];
            for (i = 0; i < *(int *)(g_movie_player_state[0] + 0xD9178); i++)
                mpeg_build_frame_packet(*(char **)(g_movie_player_state[0] + 0xD916C) + i * 0x138C0 + 0x40,
                              *(char **)(g_movie_player_state[0] + 0xD9168) + i * 0xD0000, a, b, i);
        }
        mpeg_vobuf_advance_write((u8 *)(g_movie_player_state[0] + 0xD9168));
        mpeg_start_decoder_dma();
    }
    sceMpegReset(object);
    return result;
}

extern char D_001AE8A8[];
extern void STUB_printf(void *, int);

/* Prints a message about the video decoder. */
int mpeg_dec_print_message(void *unusedArg, int *object) {
    STUB_printf(D_001AE8A8, object[1]);
    return 1;
}

/* Video decoder callback that adds more data to the input buffer. */
int mpeg_dec_callback_add_dma(void)
{
    extern void mpeg_start_decoder_dma(void);
    extern char *g_movie_player_state[] __attribute__((sda));
    extern void viBufAddDMA(void *);
    mpeg_start_decoder_dma();
    viBufAddDMA(g_movie_player_state[0] + 0xD9090);
    return 1;
}

extern char *g_movie_player_state[] __attribute__((sda));
extern void mpeg_save_ipu_dma_state(void *);

/* Video decoder callback that saves the DMA and IPU state. */
int mpeg_dec_callback_save_state(void) {
    mpeg_save_ipu_dma_state(g_movie_player_state[0] + 0xD9090);
    return 1;
}

extern char *g_movie_player_state[] __attribute__((sda));
extern void mpeg_restore_ipu_dma_state(void *);

/* Video decoder callback that restores the DMA and IPU state. */
int mpeg_dec_callback_restore_state(void) {
    mpeg_restore_ipu_dma_state(g_movie_player_state[0] + 0xD9090);
    return 1;
}

extern char *g_movie_player_state[] __attribute__((sda));
extern void VideoBufferTakeTimestamp(void *, void *);

/* Video decoder callback that fetches the timestamp of the frame being decoded. */
int mpeg_dec_callback_get_timestamp(void *unusedArg, void *reply) {
    unsigned long long timestamp[4];
    VideoBufferTakeTimestamp(g_movie_player_state[0] + 0xD9090, timestamp);
    *(unsigned long long *)((u8 *)reply + 8) = timestamp[0];
    *(unsigned long long *)((u8 *)reply + 0x10) = timestamp[1];
    return 1;
}

/* Sets up the pool of video output frame slots. */
void mpeg_vobuf_init(volatile s32 *pool, s32 param0, s32 frames, s32 frameCount) {
    s32 i;
    pool[3] = 0;
    i = 0;
    pool[0] = param0;
    pool[1] = frames;
    pool[4] = frameCount;
    pool[2] = 0;
    if (frameCount > 0) {
        frames = 0x138C0;
        param0 = 0;
        do {
            *(s32 *)(param0 + pool[1]) = 0;
            *(s32 *)(param0 + pool[1] + 4) = i;
            i++;
            param0 += frames;
        } while (i < frameCount);
    }
}

/* Does nothing. */
void mpeg_noop(void)
{
}

/* Empties the video output frame queue. */
void mpeg_vobuf_reset(u8 *pool) {
    volatile s32 *p = (volatile s32 *)pool;
    p[3] = 0;
    p[2] = 0;
}

/* lot13 -- measured bodies with sizes recorded in the catalogue. */
s32 voBufIsFull(u8 *a0) {
    return (*(u32 *)(a0 + 0xC) ^ *(u32 *)(a0 + 0x10)) < 1;
}

/* Marks the next output frame as filled and moves to the following one. */
void mpeg_vobuf_advance_write(u8 *pool) {
    DIntr();
    *(s32 *)(*(u8 **)(pool+4) + *(s32 *)(pool+8) * 0x138c0) = 2;
    *(volatile s32 *)(pool+0xc) += 1;
    *(volatile s32 *)(pool+8) = (*(volatile s32 *)(pool+8) + 1) % *(s32 *)(pool+0x10);
    func_0011F628();
}
