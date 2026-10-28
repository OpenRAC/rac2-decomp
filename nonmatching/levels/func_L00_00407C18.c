/* func_L00_00407C18 - 540 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_L00_00407C18: draft.c is a whole new file
   src/levels/shared/L00_00407C18-g64.c; cflags line
   `src/levels/shared/L00_00407C18-g64.c  -O2 -G64 -Wa,-G64 -ffunction-
   sections` (the 64-byte 4-vector table at gp+0x1F30 is only gp-addressable
   under -G64, like L00_00396078-g64.c); remove the marker from
   L00_003FFA70.c. Size matches (540 B) with the sda floats/words and the
   table as `f32 [4][4] sda`; stack temps order (r,t,u,q,v,p) gives retail's
   sp offsets.
   Left: (1) retail loads the word D_L00_001B1F7C into $a2 and builds the
   64-bit consts in $a0/$v1 (0xFF90..0260 in a0, 0x8000<<24|0x48 in v1); mine
   puts the word in $v1 and the constants in a0/a2; (2) the four word stores
   in retail order 0x40,0x4C,0x48,0x44 (both the D_L00_001B1F7C stores and the
   later -1 stores), mine 0x44,0x40,0x4C,0x48; written as w0,w3,w2,w1 and as
   one chain. The loops, the matrix helper calls and the rest match.
   NOTE: the gp-relative names in draft.c were corrected to level-0 addresses
   (gp = 0x1AEFF0 + offset); verify with check.py. */

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
} Draw407C18;

extern f32 D_L00_001B0F20[4][4] __attribute__((sda));
extern f32 D_L00_001B0F60 __attribute__((sda));
extern f32 D_L00_001B0F64 __attribute__((sda));
extern f32 D_L00_001B0F68 __attribute__((sda));
extern s32 D_L00_001B0F6C __attribute__((sda));
extern char D_L00_00254A60[];
extern char D_L00_001B8DC0[];
extern char D_00189E20[];
extern long long func_0027C878(int);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, f32);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, int, int);

extern char D_L00_0018A0E0[];

void func_L00_00407C18(char *obj)
{
    Draw407C18 d __attribute__((aligned(16)));
    f32 r[4] __attribute__((aligned(16)));
    f32 t[4] __attribute__((aligned(16)));
    f32 u[4] __attribute__((aligned(16)));
    f32 q[4] __attribute__((aligned(16)));
    f32 v[4] __attribute__((aligned(16)));
    f32 p[4] __attribute__((aligned(16)));
    int i;

    d.q78 = func_0027C878(0xB);
    d.w[1] = d.w[2] = d.w[3] = d.w[0] = D_L00_001B0F6C;
    d.z50 = 0;
    d.z54 = 0;
    d.z58 = 0;
    d.f5C = 1.0f;
    d.f60 = 1.0f;
    d.z64 = 0;
    d.f68 = 1.0f;
    d.f6C = 1.0f;
    d.q70 = 0;
    d.q80 = 0xFF9000000260LL;
    d.q88 = 0x8000000048LL;
    func_00282F20(p, obj + 0xD0, D_L00_001B0F68);
    func_00282CC0(q, D_L00_00254A60, p);
    func_00282CF0(p, D_L00_001B8DC0, q);
    func_00282F20(r, p, 1.0f);
    func_00282DD8(t, r, D_L00_0018A0E0);
    func_00282F20(t, t, -1.0f);
    func_00282DD8(u, t, r);
    for (i = 3; i >= 0; i--) {
        func_00282D30(v, D_L00_001B0F20[3 - i], D_L00_001B0F60);
        func_002830C0(d.m[3 - i], v, r);
    }
    func_00280B90(&d, 0, 0);
    d.w[1] = d.w[2] = d.w[3] = d.w[0] = -1;
    for (i = 3; i >= 0; i--) {
        func_00282D30(v, D_L00_001B0F20[3 - i], D_L00_001B0F64);
        func_002830C0(d.m[3 - i], v, r);
    }
    func_00280B90(&d, 0, 0);
}
