/* func_L22_003FB9B8 - 568 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Sibling of func_L22_003FD958 (same body, different gp constants:
   D_L22_001B0C34/38/24/28/20, ints C44/C48, a1 = 30). New file
   L22_003FB9B8-g8.c, flags `-O2 -G8 -ffunction-sections`.
   Only register numbers differ: retail n=$s2, &v10=$s1; draft n=$s1, &v10=$s2
   (and the count-down `addiu -1` sits at the top of the body in the draft,
   after the 2nd jal in retail).
   Tried: for(i=0;i<n;i++), do/while(--n), for(;n>0;n--), array v[4] for the
   quads, declaration order. */

#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern f32 D_L22_001B0C34 __attribute__((sda));
extern f32 D_L22_001B0C38 __attribute__((sda));
extern f32 D_L22_001B0C24 __attribute__((sda));
extern f32 D_L22_001B0C28 __attribute__((sda));
extern f32 D_L22_001B0C20 __attribute__((sda));
extern s32 D_L22_001B0C44 __attribute__((sda));
extern s32 D_L22_001B0C48 __attribute__((sda));
extern f32 func_002A7878(f32 a0, f32 a1);
extern f32 func_002A78D8(f32 a0, f32 a1);
extern f32 func_002A7940(void);
extern s32 func_002A77E0(s32 a0);
extern void func_002AF000(void *a0, f32 a1, f32 a2, f32 a3);
extern void func_00282D30(void *a0, void *a1, f32 a2);
extern void func_00282CD8(void *a0, void *a1, void *a2);
extern void func_002C2210(void *a0, s32 a1, s32 a2, s32 a3, s32 t0, void *t1, s32 t2, f32 f12, f32 f13, f32 f14);

typedef struct { f32 f[4]; } __attribute__((aligned(16))) L22_Quad;

void func_L22_003FB9B8(L22_Quad *a0, L22_Quad *a1, s32 n)
{
    L22_Quad v0, v10, v20, v30;
    s32 i;

    for (i = 0; i < n; i++) {
        f32 f22 = func_002A7878(D_L22_001B0C34, D_L22_001B0C38);
        s32 sign = func_002A77E0(2);
        f32 f21;
        f32 f20;

        if (sign == 0)
            sign = sign - 1;
        f21 = func_002A7940();
        f20 = func_002A7878(0.6981318f, 1.5358899f);
        func_002AF000(&v0, func_002A7878(D_L22_001B0C24 * 0.016666668f, D_L22_001B0C28 * 0.016666668f), f21, f20);
        *(TI128 *)&v20 = *(TI128 *)a1;
        func_00282D30(&v20, a1, func_002A7878(0.75f, 0.95f));
        func_00282CD8(&v30, &v0, &v20);
        *(TI128 *)&v10 = *(TI128 *)a0;
        v10.f[0] += func_002A78D8(0.0f, 0.0375f);
        v10.f[1] += func_002A78D8(0.0f, 0.0375f);
        v10.f[2] += func_002A78D8(0.0f, 0.0375f);
        func_002C2210(&v10, 30, D_L22_001B0C44, 0, sign, &v0, 0, f22 * 0.1f, f22, D_L22_001B0C20);
        func_002C2210(&v10, 30, D_L22_001B0C48, 1, -sign, &v0, 0, f22 * 0.07f, f22 * 0.7f, D_L22_001B0C20);
    }
}
