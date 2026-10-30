/* func_L07_0040FA90: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections.
   Local checks: 444/444 bytes, 0/1 in each of USA v1.01, v2.00 and PAL.
   No strict linked match is claimed.

   Corrected standalone variant; the historical func_L07_0040FA90.c remains
   unchanged. Retail func_00283658 takes two pointers, reads 48 bytes and
   writes 64 bytes, including the fourth matrix row. Keep one complete
   matrix[16], then replace its translation row at +0x30 with the object
   position. The old three-argument declaration and separate base[12] plus
   pos[4] are not used here. Equal size still fails at +0x20; allocator
   evidence assigns state to s5 and current-vector address to s4, against
   retail s4/s5. Source and tested standard profiles leave that conflict.
*/

#include "common.h"
extern u8 D_L07_002A0100[];
extern u8 *D_L07_001B1F40 MACRO_ADDR;
extern s32 *D_L07_001FDEC0[];
extern void func_00283658(void *out, void *source);
extern void func_002830C0(u8 *a, u8 *b, f32 *c);

#define REC(i) (D_L07_002A0100 + (i) * 0x120)
#define W(p) (*(f32 *)((p) + 0xC))

void func_L07_0040FA90(u8 *a0, s32 index)
{
    struct { f32 matrix[16]; f32 cur[4]; } frame;
    u8 *state = *(u8 **)(a0 + 0x68);
    s32 *out;
    u8 *src;
    u8 *rec;
    u8 *dst;
    u8 *wp;
    u8 *entry;
    f32 w;

    if (*(s32 *)(state + 0xBC) == -1)
        return;
    entry = D_L07_001B1F40 + *(s32 *)(state + 0xBC) * 0x30;
    out = D_L07_001FDEC0[**(s32 **)(entry + 0x3C)];
    *out = 0;
    func_00283658(frame.matrix, a0 + 0xC0);
    qcopy((frame.matrix + 12), a0 + 0x10);
    (frame.matrix + 12)[3] = 1.0f;
    rec = REC(index);
    if (W(rec) == 1.0f) {
        src = rec;
        wp = REC(index) + 0xC;
        dst = (u8 *)out + 0x10;
        do {
            func_002830C0(dst, src, frame.matrix);
            dst += 0x10;
            wp += 0x10;
            src += 0x10;
            (*out)++;
        } while (*(f32 *)wp == 1.0f);
    }
    qcopy(frame.cur, REC(index) + *out * 0x10);
    w = frame.cur[3];
    frame.cur[3] = 1.0f;
    func_002830C0(D_L07_001B1F40 + (*(s32 *)(state + 0xBC) * 0x30 + 0x20), (u8 *)frame.cur, frame.matrix);
    entry = D_L07_001B1F40;
    entry += *(s32 *)(state + 0xBC) * 0x30;
    ((f32 *)entry)[11] = w;
}
