#include "common.h"
#include "structs.h"
#include <stdarg.h>

     /* DeleteSema */
extern int r1_func_00118CB0(int);

typedef signed int s32_1B4C8;

extern s32_1B4C8 r1_func_00118CB0();

extern int r1_D_0012FDA0;

extern char r1_D_00157E80[];

extern s32 r1_func_00118C90(s32);

extern s32 r1_func_00118CB0(s32);

extern int r1_func_00118C70(void *);

extern s32_1B4C8 r1_func_00118C70();

extern int r1_D_0012FD9C;

extern void func_0011DD48(void);

extern int r1_D_0012FD9C NOT_SDA;

/* rac1-decomp src/core/00119D88.c: func_0011B7F8 */
/* The out-of-range guard comes first and returns 0: 2.9-ee then branches
   to the in-range block on the true side of the sltiu, as retail does
   (bnez). The in-range-first if/else that matched under 2.95.3 is laid
   out the other way round by 2.9-ee. */
/* Returns the file table entry for a file number, or 0 if the number is out of range. */
void *func_0011D950(unsigned int index) {
    void *slot;
    InitFileSemaphores();
    r1_func_00118CB0(r1_D_0012FDA0);
    if (index >= 0x20) {
        r1_func_00118C90(r1_D_0012FDA0);
        return 0;
    }
    slot = &r1_D_00157E80[index * 0x10];
    r1_func_00118C90(r1_D_0012FDA0);
    return slot;
}

extern int r1_func_00118CA0(int);
typedef struct {
    s32 v;
} __attribute__((packed)) Word;
typedef struct {
    Word ret;
    Word func;
    Word dest;
    Word size;
} FsRcvHead;
typedef struct {
    void *dest;
} __attribute__((packed)) FsRcvPtr;
typedef struct {
    Word dest;
    Word size;
} FsRcvBuf;
typedef struct {
    s32 n1;
    s32 n2;
    u8 *d1;
    u8 *d2;
    u8 buf1[0x40];
    u8 buf2[0x40];
} FsRcvRead;
typedef struct {
    u8 b[0x144];
} __attribute__((packed)) FsDirent;
typedef struct {
    u8 b[0x40];
} __attribute__((packed)) FsStat;
extern volatile s32 r1_D_0012FD10[];
extern u32 r1_D_0012FD90[];
extern s32 r1_D_0012FD98[];
extern u8 r1_D_00157600[];
extern void *r1_func_00115248(void *, const void *, u32);


/* rac1-decomp src/core/00119D88.c: func_0011D9C0 */
/* Handles the reply to a file request from the IOP: copies the returned data to its destination and wakes the waiting thread. */
void func_0011D9C0(s32 *message) {
    FsRcvHead head;
    FsRcvHead *headSrc;
    FsRcvBuf *bufSrc;
    union {
        FsRcvPtr p;
        FsRcvBuf b;
    } u;
    FsRcvRead *readReply;
    u8 *packet;
    u8 *buffers;
    u8 *copyDest;
    u32 *bank = r1_D_0012FD90;
    s32 bankIndex;
    s32 i;
    s64 ret;
    u32 byteCount;
    u32 packetAddr;

    bankIndex = r1_D_0012FD98[0] != 0 ? message[3] : 0;
    *bank = bankIndex;
    buffers = r1_D_00157600;
    packetAddr = (u32)buffers;
    packetAddr += (u32)bankIndex * 0x440;
    packet = (u8 *)(packetAddr | 0x20000000);
    headSrc = (FsRcvHead *)packet;
    head.ret = headSrc->ret;
    head.func = headSrc->func;
    head.dest = headSrc->dest;
    head.size = headSrc->size;
    if (head.ret.v >= 0) {
        r1_func_00115248((void *)head.dest.v, packet + 0x10, head.size.v);
    }
    switch (head.func.v) {
    case 2:
        readReply = (FsRcvRead *)(packet + 0x14);
        if (readReply->n1 > 0) {
            copyDest = readReply->d1;
            for (i = 0; i < readReply->n1; i++) {
                copyDest[i] = readReply->buf1[i];
            }
        }
        if (readReply->n2 > 0) {
            copyDest = readReply->d2;
            for (i = 0; i < readReply->n2; i++) {
                copyDest[i] = readReply->buf2[i];
            }
        }
        break;
    case 11:
        u.p = *(FsRcvPtr *)(packet + 0x14);
        *(FsDirent *)u.p.dest = *(FsDirent *)(packet + 0x18);
        break;
    case 12:
        u.p = *(FsRcvPtr *)(packet + 0x14);
        *(FsStat *)u.p.dest = *(FsStat *)(packet + 0x18);
        break;
    case 23:
    case 25:
    case 26:
        bufSrc = (FsRcvBuf *)(packet + 0x14);
        u.b.dest = bufSrc->dest;
        u.b.size = bufSrc->size;
        byteCount = u.b.size.v;
        if (byteCount > 0x400) {
            u.b.size.v = 0x400;
            byteCount = 0x400;
        }
        r1_func_00115248((void *)u.b.dest.v, packet + 0x1C, byteCount);
        break;
    }
    if (head.ret.v < 0) {
        u32 semaphore = 0u - (u32)head.ret.v;
        ret = (s32)semaphore;
        head.ret.v = (s32)semaphore;
        for (i = 0; i < 32; i++) {
            if (((s32 *)r1_D_0012FD10)[i] == ret) {
                r1_D_0012FD10[i] = -1;
                break;
            }
        }
        return;
    }
    r1_func_00118CA0(head.ret.v);
}

/* rac1-decomp src/core/00119D88.c: func_0011BBF0 */
/* Creates the file system lock the first time it is called. */
void func_0011DD48(void) {
    int buf[8];
    if (r1_D_0012FD9C == -1) {
        buf[5] = 0;
        buf[2] = 1;
        buf[1] = 1;
        r1_D_0012FD9C = r1_func_00118C70(buf);
    }
}
