#include "common.h"
#include "structs.h"

extern int r1_D_00132EA8;

extern int func_00127508(int, int, int, int);

extern void r1_func_00118C90(int);

extern int r1_D_00132EAC;

extern char r1_D_00159B00[];

extern int r1_D_00159B80;

extern char r1_D_0015B0C0[];

extern int r1_func_0011B4C8();

extern int r1_func_00118CC0(int);

extern void func_001277F8(void *);

/* rac1-decomp src/core/001236F0.c: func_001239D8 */
/* Makes a new folder on a memory card. It opens with a special mode and marks the command as a folder creation. */
int func_00127630(int port, int slot, int dirName) {
    int result = SceMcOpen(port, slot, dirName, 0x40);
    if (result == 0) {
        r1_D_00132EA8 = 0xB;
    }
    return result;
}

/* rac1-decomp src/core/001236F0.c: func_00123A10 */
/* RPC 3 on the client r1_D_00159B00, in func_00127630's shape: -100 with
   no server bound, -200 when the semaphore wait fails. */
/* Closes an open memory card file. */
int func_00127668(int fd) {
    char *client = r1_D_00159B00;
    int result;

    if (*(int *)(client + 0x24) == 0) {
        return -100;
    }
    if (r1_func_00118CC0(r1_D_00132EAC) < 0) {
        return -200;
    }
    r1_D_00159B80 = fd;
    result = r1_func_0011B4C8(client, 3, 1, &r1_D_00159B80, 0x30, r1_D_0015B0C0, 4, 0, 0);
    if (result == 0) {
        r1_D_00132EA8 = 3;
    } else {
        r1_func_00118C90(r1_D_00132EAC);
    }
    return result;
}

/* rac1-decomp src/core/001236F0.c: func_00123AC8 */
/* RPC 4, the same shape with three request words. `buf` is assigned
   after the semaphore call, so retail builds its address in a temp. */
/* Moves the read/write position inside an open memory card file. */
int func_00127720(int fd, int offset, int origin) {
    char *client = r1_D_00159B00;
    int *request;
    int result;

    if (*(int *)(client + 0x24) == 0) {
        return -100;
    }
    if (r1_func_00118CC0(r1_D_00132EAC) < 0) {
        return -200;
    }
    request = &r1_D_00159B80;
    request[0] = fd;
    request[4] = offset;
    request[5] = origin;
    result = r1_func_0011B4C8(client, 4, 1, request, 0x30, r1_D_0015B0C0, 4, 0, 0);
    if (result == 0) {
        r1_D_00132EA8 = 4;
    } else {
        r1_func_00118C90(r1_D_00132EAC);
    }
    return result;
}

/* rac1-decomp src/core/001236F0.c: func_00123BA0 */
/*
 * Unpack a scratchpad-resident descriptor: arg0 is forced into the SPR
 * window (| 0x20000000), then two counted byte runs are copied out of
 * it -- the one at +0x10 to the pointer at +0x8 for the count at +0x0,
 * and the one at +0x50 to the pointer at +0xC for the count at +0x4.
 * The counts are re-read from the descriptor on every iteration, so
 * they are written out in full rather than cached.
 *
 * The explicit zero-trip guard around each do/while is what makes this
 * match, and it is worth knowing why. Written as a plain `for`, the
 * source base (p + 0x10) is loop-invariant, so GCC hoists it ABOVE the
 * guard; retail computes it BELOW, between the guard and the loop head.
 * That one position shifts the loop head by a word, which in turn costs
 * the alignment nop retail carries -- two instructions per loop, 16
 * bytes over the two loops. Spelling the guard yourself puts the
 * invariant where retail has it. (Folding the +0x10 into the load
 * offset instead of keeping a base pointer costs another 8.)
 */
/* Copies the leftover bytes at the start and end of a memory card read into the caller's buffer. */
void func_001277F8(void *descAddr) {
    char *desc = (char *)((unsigned int)descAddr | 0x20000000);
    unsigned char *src;
    char *dst;
    int i;

    if (*(int *)(desc + 0x0) != 0) {
        dst = *(char **)(desc + 0x8);
        i = 0;
        if (i < *(int *)(desc + 0x0)) {
            src = (unsigned char *)(desc + 0x10);
            do {
                *dst++ = src[i];
                i++;
            } while (i < *(int *)(desc + 0x0));
        }
    }
    if (*(int *)(desc + 0x4) != 0) {
        dst = *(char **)(desc + 0xC);
        i = 0;
        if (i < *(int *)(desc + 0x4)) {
            src = (unsigned char *)(desc + 0x50);
            do {
                *dst++ = src[i];
                i++;
            } while (i < *(int *)(desc + 0x4));
        }
    }
}
