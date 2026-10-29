/* func_0027E1A0 - 764 bytes, 28 places (the boot and every level).
   Screened in wave 13 (worker g4): 4 call(s), 0 $gp-relative small-data access(es), 0 MMI lq/sq word(s), 12 64-bit daddu copy(ies), 0 float constant(s).
   12 pointers are copied with daddu $d,$s,$zero, where this cc1 sign-extends with dsll/dsra; the body is straight-line code whose register allocation has to be reproduced word for word.
   Not matched in wave 13 (worker g4): screening only; no C candidate was tested in this wave. */
/* Retained bounded near miss, 2026-10-28: default752/764 bytes, four trials.
 * Four screen floats preserve FP bank order, followed by four UV integers,
 * a true four-u32 color pointer and a complete64-bit texture word. LWU color
 * loads and sign-extended32-bit UV results are deliberately distinct.
 * Compiler consumes screen width before the first conversion call, leaving
 * four persistentFPRs and0x80 frame instead of retail's five/0x90. Disabling
 * first scheduling, both scheduling passes, or then GCSE does not restore
 * that lifetime. No broad profile is retained. Reopen on an actual screen
 * width lifetime and packet-word expression witness; no fake parameter type,
 * register pin, extra access or scheduling-only volatile may substitute.
 * Packet extent is160 bytes and every byte is written: DMA16, header16 and
 * sixteen64-bit data words. Input color span is16 bytes. Packed shifts use
 * unsigned32/64 arithmetic; the full-width coordinate mask is preserved.
 */
#include "common.h"

extern int func_00283CF0(float);
extern int D_001A7350 __attribute__((sda)), D_001A7354 __attribute__((sda));
extern unsigned char *D_001B22A8 __attribute__((sda));

/* The four screen floats and six integer-bank inputs preserve their separate
 * retail bank orders. Colors are genuinely unsigned32-bit (retail LWU), and
 * the texture state is a complete64-bit word. Emit a complete160-byte packet:
 * DMA16, GS header16 and sixteen64-bit data words. */
void func_0027E1A0(float x, float y, float width, float height,
                  int u, int v, int uv_width, int uv_height,
                  const unsigned int *colors, unsigned long long texture)
{
    int x0, x1, y0, y1, u1, v1;
    int uv0, uv1, uv2, uv3;
    u64 clamp, xy0, xy1, xy2, xy3;
    unsigned char *current, *next;
    const u64 coordinate_mask = 0xFFFFF000000000ULL;
    x0 = func_00283CF0(x * 16.0f) + D_001A7350 - 8;
    x += width;
    x1 = func_00283CF0(x * 16.0f) + D_001A7350 - 8;
    y0 = func_00283CF0(y * 16.0f) + D_001A7354 - 8;
    y += height;
    y1 = func_00283CF0(y * 16.0f) + D_001A7354 - 8;
    if (x0 > 0x9000) return;
    if (x1 < 0x7000) return;
    if (y0 > 0x9000) return;
    if (y1 < 0x7000) return;
    u1 = u + uv_width;
    v1 = v + uv_height;
    *(u32 *)(D_001B22A8 + 0) = 0x10000009;
    *(u32 *)(D_001B22A8 + 4) = 0;
    *(u32 *)(D_001B22A8 + 8) = 0;
    *(u32 *)(D_001B22A8 + 12) = 0x50000009;
    clamp = ((u64)u1 << 14) | 10;
    clamp |= (u64)u << 4;
    clamp |= (u64)v << 24;
    clamp |= (u64)v1 << 34;
    xy0 = (u64)x0 | ((u64)y0 << 16) | coordinate_mask;
    xy1 = (u64)x1 | ((u64)y0 << 16) | coordinate_mask;
    xy2 = (u64)x0 | ((u64)y1 << 16) | coordinate_mask;
    xy3 = (u64)x1 | ((u64)y1 << 16) | coordinate_mask;
    uv0 = (int)(((u32)v << 20) + ((u32)u << 4));
    uv1 = (int)(((u32)v << 20) + ((u32)u1 << 4));
    uv2 = (int)(((u32)v1 << 20) + ((u32)u << 4));
    uv3 = (int)(((u32)v1 << 20) + ((u32)u1 << 4));
    current = D_001B22A8;
    next = current + 16;
    D_001B22A8 = next;
    *(u64 *)(current + 16) = 0x400000000008001ULL;
    *(u64 *)(D_001B22A8 + 8) = 0x8531531531531068ULL;
    current = D_001B22A8;
    next = current + 16;
    D_001B22A8 = next;
    *(u64 *)(current + 16) = clamp;
    *(u64 *)(next + 16) = 0x15c;
    *(u64 *)(next + 8) = texture;
    *(u64 *)(next + 32) = (long)uv0;
    *(u64 *)(next + 24) = (u64)colors[0];
    *(u64 *)(next + 40) = xy0;
    *(u64 *)(next + 56) = (long)uv1;
    *(u64 *)(next + 48) = (u64)colors[1];
    *(u64 *)(next + 64) = xy1;
    *(u64 *)(next + 80) = (long)uv2;
    *(u64 *)(next + 72) = (u64)colors[2];
    *(u64 *)(next + 88) = xy2;
    *(u64 *)(next + 104) = (long)uv3;
    *(u64 *)(next + 96) = (u64)colors[3];
    *(u64 *)(next + 112) = xy3;
    *(u64 *)(next + 120) = 5;
    D_001B22A8 += 128;
}
