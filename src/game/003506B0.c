#include "ps2_hw.h"
#include "names.h"
#include "include_asm.h"

typedef int s32;

typedef unsigned char u8;

extern s32 sceCdRead(s32, s32, u8 *, u8 *);

extern s32 sceCdSyncS(s32);

typedef unsigned int u32;

extern s32 DIntr(void);

extern s32 func_0011F628(void);

extern void F0b028b34_FUN_00350878(char *a, unsigned int b, int c, int d);

extern void F0b028b34_FUN_00350808(int a);

/* func_003512B8 : rounds a field to a multiple of 2048 under a semaphore */
extern s32 WaitSema(s32);

extern s32 SignalSema(s32);

/* func_00351268 : waits, then combines two fields shifted by 11 */
extern s32 WaitSema(s32 a0);

extern s32 SignalSema(s32 a0);

extern void mpeg_vibuf_get_free_regions(int *owner, int *first_address, int *first_count,
                         int *second_address, int *second_count);

/* Reads disc sectors into a buffer and moves the read position forward when it succeeds. */
s32 mpeg_read_disc_sectors(u8 *reader, u8 *dest, s32 byteCount, s32 failFlag) {
    u8 readMode[3];
    s32 sectors = byteCount >> 11;
    s32 result = 0;
    readMode[0] = 100; readMode[1] = 1; readMode[2] = 0;
    sceCdRead(*(s32 *)(reader+4), sectors, dest, readMode);
    if (failFlag == 0) {
        *(s32 *)(reader+4) += sectors;
        sceCdSyncS(0);
        result = byteCount;
    }
    return result;
}

/* Turns a memory address inside the video buffer into a slot number. */
s32 mpeg_vibuf_addr_to_slot(u8 *buf, s32 addr) {
    u32 endAddress = ((*(u32 *)(buf + 8) << 4) + *(u32 *)(buf + 4) + 0x10) & 0x0FFFFFFF;
    if (addr == endAddress) return 0;
    return (u32)(addr - *(u32 *)buf) >> 11;
}

/* Starts DMA channel 3 with the given control value. */
void mpeg_start_dma3(u32 control) {
    DIntr();
    D_ENABLEW = D_ENABLER | 0x10000;
    D3_CHCR = control;
    D_ENABLEW = D_ENABLER & 0xfffeffff;
    func_0011F628();
}

/* Starts DMA channel 4 with the given control value. */
void mpeg_start_dma4(u32 control) {
    DIntr();
    D_ENABLEW = D_ENABLER | 0x10000;
    D4_CHCR = control;
    D_ENABLEW = D_ENABLER & 0xfffeffff;
    func_0011F628();
}

/* Builds a DMA tag from an address, flags and size. */
void scTag2(unsigned long *tag,unsigned long a1,unsigned long flags,unsigned long quadCount) {
 *tag=(a1<<32)|((flags<<32)>>4)|((quadCount<<32)>>32);
}

extern int CreateSema(int *);
extern int mpeg_vibuf_reset(int *);

/* Sets up the video input buffer and then resets it. */
int mpeg_vibuf_init(int *object, int address, unsigned int buffer, int count, int *records, int capacity)
{
    int semaphore[5];
    object[0] = address;
    object[1] = (buffer & 0x0FFFFFFF) | 0x20000000;
    object[20] = (int)records;
    object[21] = capacity;
    object[2] = count;
    object[6] = count << 11;
    semaphore[2] = 1;
    semaphore[1] = 1;
    object[16] = CreateSema(semaphore);
    mpeg_vibuf_reset(object);
    *(long long *)(object + 18) = 0;
    return 1;
}

/* Clears the video input buffer, builds its DMA tag chain and starts DMA channel 4. */
int mpeg_vibuf_reset(int *buf)
{
    int i;

    buf[17] = 1;
    buf[3] = 0;
    buf[4] = 0;
    buf[5] = 0;
    buf[22] = 0;
    buf[23] = 0;
    for (i = 0; i < buf[21]; i++) {
        *(long long *)((char *)buf[20] + i * 24) = -1;
        *(long long *)((char *)buf[20] + i * 24 + 8) = -1;
        *(int *)((char *)buf[20] + i * 24 + 16) = 0;
        *(int *)((char *)buf[20] + i * 24 + 20) = 0;
    }
    for (i = 0; i < buf[2]; i++) {
        F0b028b34_FUN_00350878((char *)(buf[1] + i * 16), (i * 2048 + buf[0]) & 0x0FFFFFFF, 3, 128);
    }
    F0b028b34_FUN_00350878((char *)(buf[1] + i * 16), buf[1] & 0x0FFFFFFF, 2, 0);
    D4_QWC = 0;
    D4_MADR = buf[0] & 0x0FFFFFFF;
    D4_TADR = buf[1] & 0x0FFFFFFF;
    F0b028b34_FUN_00350808(5);
    return 1;
}

/* Works out the free space in the video buffer as one or two memory ranges. */
void mpeg_vibuf_get_free_regions(s32 *buf, s32 *firstAddress, s32 *firstCount, s32 *secondAddress, s32 *secondCount) {
    s32 writePos, freeBytes;
    WaitSema(buf[16]);
    freeBytes = (s32)((long)buf[2] - (long)(buf[4]+2)) * 2048 - buf[5];
    writePos = ((buf[3] + buf[4]) * 2048 + buf[5]) % buf[6];
    if (freeBytes <= buf[6]-writePos) {
        *firstAddress = buf[0]+writePos;
        *firstCount = freeBytes;
        *secondAddress = 0;
        *secondCount = 0;
    } else {
        *firstAddress = buf[0]+writePos;
        *firstCount = buf[6]-writePos;
        *secondAddress = buf[0];
        *secondCount = freeBytes - (buf[6]-writePos);
    }
    SignalSema(buf[16]);
}
