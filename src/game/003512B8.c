#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned char u8;

/* func_003512B8 : rounds a field to a multiple of 2048 under a semaphore */
extern s32 func_0011AC60(s32);

extern s32 func_0011AC40(s32);

/* func_00351268 : waits, then combines two fields shifted by 11 */
extern s32 func_0011AC60(s32 a0);

extern s32 func_0011AC40(s32 a0);

extern void func_0012EE28();

extern void func_00350A78(int *owner, int *first_address, int *first_count,
                         int *second_address, int *second_count);

extern int func_00351268(unsigned char *owner);

typedef unsigned int u32;

extern int func_00351E58(unsigned char *);

extern s32 func_0011F5E0(void);

extern s32 func_0011F628(void);

/* Rounds the waiting byte count up to a whole 2048-byte sector. */
void func_003512B8(u8 *buf) {
    WaitSema(*(s32 *)(buf + 0x40));
    *(s32 *)(buf + 0x14) = (*(s32 *)(buf + 0x14) + 0x7ff) / 0x800 * 0x800;
    SignalSema(*(s32 *)(buf + 0x40));
}

/* func_00351578 is matched in 00351578.c. */

typedef struct { unsigned long long first, second; int offset, count; } Transfer_3518F0;

extern int func_00351310(void *, Transfer_3518F0 *);

/* a % b as a helper: once inlined, its zero-divisor check is tested against $0 */
static inline int ring_mod(int a, int b) { return a % b; }

/* func_00351310 : walks the transfer ring, trimming one message out of the slots */
int func_00351310(void *owner, Transfer_3518F0 *message)
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
int func_00351468(void *owner, Transfer_3518F0 *message, int unusedArg)
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
s32 func_00351828(void) {
    AddMpegStreamCallback();
    return 1;
}

/* Passes the free-space query on to the video buffer inside the decoder. */
void func_00351848(unsigned char *owner, int *first_address, int *first_count,
                  int *second_address, int *second_count)
{
    ViBufGetFreeRegions((int *)(owner + 0x48), first_address, first_count,
                 second_address, second_count);
}

extern void func_00350B70(u8 *, s32);

/* Forwards the byte count to the object's transfer buffer. */
void func_00351868(char *object, s32 count) {
    ViBufAddPendingBytes((u8 *)object + 0x48, count);
}

/* Measured target: byte-identical across all 27 levels. */
/* Sets the video decoder's state to 0. */
void func_00351888(u8 *decoder) { *(s32 *)(decoder + 0xa8) = 0; }

extern void func_00351210(void *);
extern int func_0012F940(void *);

/* Shuts down the video decoder's buffer and then the decoder itself. */
int func_00351890(u8 *decoder) {
    ViBufStopDma(decoder + 0x48);
    ReturnOne_0012F940(decoder);
    return 1;
}

/* Sets the video decoder's state to 1. */
void func_003518C8(u8 *decoder) {s32 state=1;*(s32 *)(decoder+0xa8)=state;}

/* Measured target: byte-identical across all 27 levels. */
s32 func_003518D8(u8 *a0) { return *(s32 *)(a0 + 0xa8); }

/* Sets the video decoder's state and returns the old state. */
s32 func_003518E0(u8 *decoder, s32 newState) { s32 oldState = *(s32 *)(decoder + 0xa8); *(s32 *)(decoder + 0xa8) = newState; return oldState; }

extern char *D_001B23CC[] __attribute__((sda));
extern int func_00351468(void *, Transfer_3518F0 *, int);

/* Adds a timestamp for a chunk of video data to the decoder's buffer. */
int func_003518F0(char *object, unsigned long long first, unsigned long long second, int end, int count)
{
    Transfer_3518F0 transfer;
    transfer.first = first;
    transfer.second = second;
    transfer.offset = end - *(int *)(object + 0x48);
    transfer.count = count;
    return ViBufAddTimestamp(gMoviePlayerState[0] + 0xD9090, &transfer, *(int *)(object + 0x48));
}

/* Returns how many bytes are waiting in the decoder's video buffer. */
int func_00351938(unsigned char *owner)
{
    return ViBufGetQueuedBytes(owner + 0x48);
}


/* func_00351960 : builds a 16-byte packet (a 4-byte header copied from D_001AE860 and a
   12-byte body), asks the object for the two memory ranges it holds, and moves them into
   the packet.  The two addresses are turned into 32-bit engine addresses. */
typedef struct { char tag[4]; } Header_351960;

typedef struct { Header_351960 header; char body[12]; } Packet_351960;

extern Header_351960 D_001AE860;

extern s32 func_00350460(u32 first_address, s32 first_count, u32 second_address,
                         s32 second_count, u32 packet, s32 header_size, s32 unused1,
                         s32 unused2);

/* These wrappers have different targets in the level programs. */
extern void ref_L00_00351960_00(u8 *, s32 *, s32 *, s32 *, s32 *);
extern void ref_L00_00351960_01(char *, s32);

/* Takes the video data that is ready, sends it for decoding, and marks the decoder as running if idle. */
s32 func_00351960(u8 *decoder)
{
    Packet_351960 packet;
    s32 first_address, first_count, second_address, second_count;
    s32 result;

    packet.header = D_001AE860;
    ref_L00_00351960_00(decoder, &first_address, &first_count, &second_address, &second_count);
    if (first_count + second_count < 4) {
        return 0;
    }
    result = CopySplitBuffer((first_address & 0x0FFFFFFF) | 0x20000000, first_count,
                            (second_address & 0x0FFFFFFF) | 0x20000000, second_count,
                            (u32)&packet, 4, 0, 0);
    ref_L00_00351960_01(gMoviePlayerState[0] + 0xD9048, result);
    ViBufAlignPendingBytes(decoder + 0x48);
    if (*(s32 *)(decoder + 0xA8) == 0) {
        *(s32 *)(decoder + 0xA8) = 2;
    }
    return 1;
}

extern int func_0012F9B8(void *);



extern void func_00350918(void *);
extern void func_00351E48(u8 *);
extern int func_00351B20(void *);
/* Starts the video decoder: resets its buffer, runs the decode loop, and waits until it is told to stop. */
void func_00351A80(unsigned char *object)
{
    char *base;
    ViBufReset(object + 0x48);
    VoBufReset(gMoviePlayerState[0] + 0xD9168);
    VideoDecRunDecodeLoop(object);
    base = gMoviePlayerState[0];
    while (*(int *)(base + 0xD9174)) {
        if (videoDecGetState(object) == 1) break;
        base = gMoviePlayerState[0];
    }
    VideoDecSwapState(object, 3);
}


extern void func_0026FEB8();
extern char D_001AE868[];
extern char D_001AE880[];
extern int func_0012F9A8(void *);
extern void func_0012F9C8(void *);
extern int func_0012F950(void *, void *, int);
extern void func_0034F3B8(void);
extern void func_0034F780(char *);
extern void *func_00351EE8(char *);
extern void func_00351E70(u8 *);
extern void func_0034FE18(void *, void *, int, int, int);

/* Main video decode loop: waits for a free output frame, decodes into it, and passes it on until stopped. */
int func_00351B20(void *decoder)
{
    int *object = decoder;
    int result = 1;
    void *packet;
    int i;

    while (ReadIndirectWord(object) == 0) {
        if (videoDecGetState((u8 *)object) == 1) {
            result = -1;
            STUB_printf(D_001AE868);
            break;
        }
        while ((packet = VoBufGetNextFrame(gMoviePlayerState[0] + 0xD9168)) == 0)
            StartMovieDecoderDma();
        if (func_0012F950(object, packet, 0x340) < 0)
            SetMovieDebugValue(D_001AE880);
        if (object[2] == 0) {
            int a = object[0];
            int b = object[1];
            for (i = 0; i < *(int *)(gMoviePlayerState[0] + 0xD9178); i++)
                BuildMovieFramePacket(*(char **)(gMoviePlayerState[0] + 0xD916C) + i * 0x138C0 + 0x40,
                              *(char **)(gMoviePlayerState[0] + 0xD9168) + i * 0xD0000, a, b, i);
        }
        VoBufAdvanceWrite((u8 *)(gMoviePlayerState[0] + 0xD9168));
        StartMovieDecoderDma();
    }
    ResetMpegDecoder(object);
    return result;
}

extern char D_001AE8A8[];
extern void func_0026FEB8(void *, int);

/* Prints a message about the video decoder. */
int func_00351CD8(void *unusedArg, int *object) {
    STUB_printf(D_001AE8A8, object[1]);
    return 1;
}

/* Video decoder callback that adds more data to the input buffer. */
int func_00351D00(void)
{
    extern void func_0034F3B8(void);
    extern char *D_001B23CC[] __attribute__((sda));
    extern void func_00350BC8(void *);
    StartMovieDecoderDma();
    viBufAddDMA(gMoviePlayerState[0] + 0xD9090);
    return 1;
}

extern char *D_001B23CC[] __attribute__((sda));
extern void func_00350DC8(void *);

/* Video decoder callback that saves the DMA and IPU state. */
int func_00351D38(void) {
    SaveIpuDmaState(gMoviePlayerState[0] + 0xD9090);
    return 1;
}

extern char *D_001B23CC[] __attribute__((sda));
extern void func_00350ED8(void *);

/* Video decoder callback that restores the DMA and IPU state. */
int func_00351D68(void) {
    RestoreIpuDmaState(gMoviePlayerState[0] + 0xD9090);
    return 1;
}

extern char *D_001B23CC[] __attribute__((sda));
extern void func_00351578(void *, void *);

/* Video decoder callback that fetches the timestamp of the frame being decoded. */
int func_00351D98(void *unusedArg, void *reply) {
    unsigned long long timestamp[4];
    VideoBufferTakeTimestamp(gMoviePlayerState[0] + 0xD9090, timestamp);
    *(unsigned long long *)((u8 *)reply + 8) = timestamp[0];
    *(unsigned long long *)((u8 *)reply + 0x10) = timestamp[1];
    return 1;
}

/* Sets up the pool of video output frame slots. */
void func_00351DE8(volatile s32 *pool, s32 param0, s32 frames, s32 frameCount) {
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
void func_00351E40(void)
{
}

/* Empties the video output frame queue. */
void func_00351E48(u8 *pool) {
    volatile s32 *p = (volatile s32 *)pool;
    p[3] = 0;
    p[2] = 0;
}

/* lot13 -- measured bodies with sizes recorded in the catalogue. */
s32 func_00351E58(u8 *a0) {
    return (*(u32 *)(a0 + 0xC) ^ *(u32 *)(a0 + 0x10)) < 1;
}

/* Marks the next output frame as filled and moves to the following one. */
void func_00351E70(u8 *pool) {
    DIntr();
    *(s32 *)(*(u8 **)(pool+4) + *(s32 *)(pool+8) * 0x138c0) = 2;
    *(volatile s32 *)(pool+0xc) += 1;
    *(volatile s32 *)(pool+8) = (*(volatile s32 *)(pool+8) + 1) % *(s32 *)(pool+0x10);
    func_0011F628();
}
