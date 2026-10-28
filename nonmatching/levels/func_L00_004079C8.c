/* func_L00_004079C8 - 592 bytes.  Worker attempt, 27 October 2026 (draft below).

   dropped (40 differing lines): 584B vs 592B draft, new file
   L00_004079C8-g64.c with '-O2 -G64 -Wa,-G64 -ffunction-sections'. Sibling of
   func_L00_00407C18 (same draw struct and 3-iteration matrix loop inside an
   outer loop over 3 table entries); retail spills three locals to
   sp+0xE0/E4/E8 and keeps the pair of qcopy sources in addressed temps;
   vector roles in draft are guessed. */

#include "include_asm.h"
#include "common.h"

typedef struct {
    f32 m[4][4];
    s32 w[4];
    s32 z50, z54, z58;
    f32 f5C, f60;
    s32 z64;
    f32 f68, f6C;
    long long q70;
    long long q78;
    long long q80;
    long long q88;
} Draw4079C8;

typedef struct { char pad[0x4]; u8 f4; char pad5[0xDB]; } Weapon4079C8;

extern f32 D_L00_001B0F20[4][4] __attribute__((sda));
extern s32 D_L00_001B0EBC __attribute__((sda));
extern s32 D_L00_001B0EC0 __attribute__((sda));
extern u8 D_00139578[];
extern Weapon4079C8 D_L00_00262570[];
extern s32 D_L00_001B2D30[3];
extern f32 D_L00_001B2D00[3];
extern f32 D_L00_001B2D20[3];
extern f32 D_L00_001B2C90[3][4];
extern f32 D_L00_001B2CC0[3][4];
extern char D_L00_0018A0E0[];
extern long long func_0027C878(int);
extern int func_002EF250(float);
extern void func_00282F20(void *, void *, f32);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, f32);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, int, int);

void func_L00_004079C8(void)
{
    Draw4079C8 d __attribute__((aligned(16)));
    f32 r[4] __attribute__((aligned(16)));
    f32 t[4] __attribute__((aligned(16)));
    f32 u[4] __attribute__((aligned(16)));
    f32 q[4] __attribute__((aligned(16)));
    f32 v[4] __attribute__((aligned(16)));
    int base;
    int i;
    int k;

    d.q78 = func_0027C878(8);
    d.q80 = 0xFF9000000260LL;
    d.q88 = 0x8000000048LL;
    d.f6C = 1.0f;
    d.q70 = 0;
    d.z50 = 0;
    d.z54 = 0;
    d.z58 = 0;
    d.f5C = 1.0f;
    d.f60 = 1.0f;
    d.z64 = 0;
    d.f68 = 1.0f;
    if (D_L00_00262570[D_00139578[0]].f4 != 0)
        base = D_L00_001B0EC0;
    else
        base = D_L00_001B0EBC;
    base &= 0xFFFFFF;
    for (i = 0; i < 3; i++) {
        if (D_L00_001B2D30[i] != 0) {
            int c = base | (func_002EF250(D_L00_001B2D00[i]) << 24);
            d.w[0] = c;
            d.w[3] = c;
            d.w[2] = c;
            d.w[1] = c;
            qcopy(q, D_L00_001B2C90[i]);
            qcopy(r, D_L00_001B2CC0[i]);
            func_00282D30(v, D_L00_0018A0E0, -1.0f);
            func_00282DD8(u, r, v);
            func_00282F20(u, u, 1.0f);
            func_00282DD8(t, u, r);
            for (k = 3; k >= 0; k--) {
                func_00282D30(v, D_L00_001B0F20[3 - k], D_L00_001B2D20[i]);
                func_002830C0(d.m[3 - k], v, r);
            }
            func_00280B90(&d, 0, 0);
        }
    }
}
