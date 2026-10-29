/* Retained bounded near miss, 2026-10-28: 616/616 bytes with
 * -O2 -G0 -ffunction-sections -g -mno-split-addresses. First mismatch +0x70:
 * the template address is built contiguously, rather than scheduling its high
 * half before the width shift. Eight narrower declaration/profile trials
 * reach 608/612 bytes or this 616-byte allocation. No ordinary-field volatile.
 * Reopen on a supported address-model witness preserving the byte guard and
 * independently split template addresses. Two required GP dual views below
 * bind exactly the same scalar/pointer storage, without shortened objects.
 */
#include "common.h"

extern int D_001B15A8 __attribute__((sda));
extern int D_001B15AC __attribute__((sda));
/* The retail counter uses GP for its increment and ordinary addressing elsewhere. */
extern int D_001B15AC_gp SDATA(D_001B15AC);
extern unsigned char D_001A7BB1 __attribute__((nosda));
extern unsigned char *D_001B22A8 __attribute__((sda));
/* Only the first packet write selects the GP view of the same live cursor. */
extern unsigned char *D_001B22A8_gp SDATA(D_001B22A8);
extern u64 D_001AC7E0[], D_001AC7F0[];
extern int D_001A7350 __attribute__((sda));
extern int D_001A7354 __attribute__((sda));
extern int D_001A7358 __attribute__((sda));
extern int D_001A735C __attribute__((sda));

/* Emit the complete 0x80-byte packet, including two full aligned templates.
 * The live cursor advances in the same stages as the packet fields it exposes. */
void func_0027D900(void)
{
    int width;
    unsigned char *current, *next;
    const u64 mask = 0xFFFFF300000000ULL;
    if (D_001B15A8) {
        if (D_001B15AC_gp < 52) ++D_001B15AC_gp;
    } else {
        if (!D_001B15AC) return;
        --D_001B15AC;
    }
    width = D_001B15AC;
    if (!width || D_001A7BB1) return;
    *(u32 *)(D_001B22A8_gp + 0) = 0x10000007;
    *(u32 *)(D_001B22A8 + 4) = 0;
    *(u32 *)(D_001B22A8 + 8) = 0;
    *(u32 *)(D_001B22A8 + 12) = 0x50000007;
    width <<= 4;
    {
        unsigned char *base = D_001B22A8;
        unsigned char *header = base + 16;
        D_001B22A8 = header;
        qcopy(header, D_001AC7E0);
        *(s16 *)(base + 16) = -32767;
    }
    {
        unsigned char *base = D_001B22A8;
        unsigned char *color = base + 16;
        D_001B22A8 = color;
        *(u64 *)(base + 16) = 0x104;
        *(u64 *)(color + 8) = 0x80000000ULL;
    }
    {
        unsigned char *base = D_001B22A8;
        unsigned char *header = base + 16;
        D_001B22A8 = header;
        qcopy(header, D_001AC7F0);
        *(s16 *)(base + 16) = -32760;
    }
    current = D_001B22A8;
    next = current + 16;
    D_001B22A8 = next;
    *(u64 *)(current + 16) = (u64)D_001A7350 | ((u64)D_001A7354 << 16) | mask;
    *(u64 *)(next + 8) = (u64)D_001A7350 | ((u64)(D_001A7354 + width) << 16) | mask;
    *(u64 *)(next + 16) = (u64)D_001A7358 | ((u64)D_001A7354 << 16) | mask;
    *(u64 *)(next + 24) = (u64)D_001A7358 | ((u64)(D_001A7354 + width) << 16) | mask;
    *(u64 *)(next + 32) = (u64)D_001A7358 | ((u64)D_001A735C << 16) | mask;
    *(u64 *)(next + 40) = (u64)D_001A7358 | ((u64)(D_001A735C - width) << 16) | mask;
    *(u64 *)(next + 48) = (u64)D_001A7350 | ((u64)D_001A735C << 16) | mask;
    *(u64 *)(next + 56) = (u64)D_001A7350 | ((u64)(D_001A735C - width) << 16) | mask;
    D_001B22A8 += 64;
}
