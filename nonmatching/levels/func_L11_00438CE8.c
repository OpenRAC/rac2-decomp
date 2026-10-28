/* func_L11_00438CE8 - 560 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   New file L11_00438CE8-qcopy.c, flags `-O2 -G0 -ffunction-sections
   -frac2-qcopy` (lq/sq with address regs $s1/$s3, TI copy `*(TI128 *)&v60 =
   *(TI128 *)&v70`). Returns int (-1 early, 0 / new idx at the end: v0 is live
   out).
   556 vs 560 B, ~125 masked diff lines mostly from the first loop and the
   shifted frame: retail loop is
   `a0=idx; if (flags[a0]) do { v0=a0+1 (also computed in the bnez delay
   slot); sh v0; v1=(s16)v0; a0=v0 } while (flags[v1])` with an extra `nop`
   after the addiu; draft increments $a0 in place and has no nop.
   Frame size now matches (0xC0 with v50). Tried:
   while(flags[*(s16*)(q+0x374)]) with ++ on memory (lhu reloads), s16 idx
   (worse), s32 idx + (s16) cast (current). */

#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern int D_L11_001B359C __attribute__((sda));

extern s32 func_00282978(void *a0);
extern void func_0029FCC0(void *a0, s32 a1, void *a2);
extern void func_0029FC20(void *a0, s32 a1, void *a2);
extern void func_00282F20(void *a0, void *a1, f32 a2);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern void func_00282CF0(void *a0, void *a1, void *a2);
extern void func_002A7A00(void *a0, f32 a1, f32 a2);
extern void *func_L07_003F6B88(s32 a0);
extern void func_L11_00458A98(f32 f12, f32 f13, void *a0, void *a1, void *a2, s32 a3, void *t0, void *t1, s32 t2);

typedef struct { f32 f[4]; } __attribute__((aligned(16))) L11_Quad;

s32 func_L11_00438CE8(u8 *p)
{
    u8 *q = *(u8 **)(p + 0x68);
    L11_Quad v0;
    L11_Quad m[4];
    L11_Quad v50, v60, v70, v80;
    void *r;
    u8 *flags;
    s32 n;
    s32 done;
    s32 idx = *(s16 *)(q + 0x374);

    if (idx == -1)
        return -1;
    flags = q + 0x380;
    if (flags[idx] != 0) {
        do {
            idx = idx + 1;
            *(s16 *)(q + 0x374) = idx;
        } while (flags[(s16)idx] != 0);
    }
    if (*(s16 *)(q + 0x374) < 10) {
        done = func_00282978(q + 0x376);
        if (done != 0) {
            func_0029FCC0((u8 *)D_L11_001B359C + (*(s32 *)(*(u8 **)(p + 0x68) + *(s16 *)(q + 0x374) * 4 + 0x330) << 8), 0, &v0);
            func_0029FC20((u8 *)D_L11_001B359C + (*(s32 *)(*(u8 **)(p + 0x68) + *(s16 *)(q + 0x374) * 4 + 0x330) << 8), 0, &m[0]);
            func_00282F20(&v50, &m[2], -0.3f);
            func_00282CC0(&v0, &v0, &v50);
            func_002A7A00(&v70, 0.016666668f, 0.05f);
            v70.f[2] = -0.083333336f;
            *(TI128 *)&v60 = *(TI128 *)&v70;
            func_00282CF0(&v80, q + 0x50, &v0);
            func_00282F20(&v80, &v80, 0.33333334f);
            func_00282CC0(&v60, &v60, &v80);
            r = func_L07_003F6B88(*(s32 *)(q + 0x368));
            if (r != 0)
                func_L11_00458A98(0.0027777778f, (f32)q[0x35], r,
                                  (u8 *)D_L11_001B359C + (*(s32 *)(*(u8 **)(p + 0x68) + *(s16 *)(q + 0x374) * 4 + 0x330) << 8),
                                  *(void **)(p + 0xB8), *(s32 *)(q + 0x60), &v0, &v60, 0x78);
            *(s16 *)(q + 0x376) = 0xF;
            n = *(u16 *)(q + 0x374) + 1;
            *(u16 *)(q + 0x374) = n;
            return n;
        }
        return done;
    }
    return -1;
}
