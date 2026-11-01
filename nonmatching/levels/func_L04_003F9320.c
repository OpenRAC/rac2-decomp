/* func_L04_003F9320: near miss, 1012/1016 bytes, 0 of 2 places (USA v1.01, 31 October 2026).

   Profile: its own unit, `-O2 -G0 -ffunction-sections -frac2-qcopy -frac2-zero-ti-por -g`
   (qcopy for the register-address copies, zero-ti-por for the zeroed spark vector, -g for the
   nops before div.s). The fifth float argument of func_002A7AA8 travels in $f16.

   Calls, constants, both branches and the glow-sprite loop follow retail. Left:
   - stack layout: retail has p, d, the hit record, `from`, w, v at 0x00..0x70; `from` is a
     Quad loaded with an offset (`lq 0x10($s4)`), so it is a pseudo that goes to the stack at
     purge_addressof, after the w/v arrays already took 0x50/0x60. Quad scalars for w and v
     put them in the right form but keep v's lanes in registers (mfc1/and/or inserts);
     unions behave like the arrays.
   - retail keeps &p and &d in $s5/$s1 and later reuses $s5 for `obj + 0x10`; here cse folds
     &p to $sp and an extra pair of saved registers ($s7, $fp) appears in the first draft.
   - $f20/$f21 roles for the -1/1 random bounds. */

#include "common.h"

typedef int Quad __attribute__((mode(TI)));

typedef struct {
    f32 v[4];
    s32 owner;
    s32 flags;
    u8 kind;
    u8 mode;
    u16 source;
    f32 scale;
    s32 extra;
} Hit3F9320;

extern Quad D_L04_001BFAE0;
extern f32 D_L04_001BFB00[];
extern char D_001A8F20[] __attribute__((sda));

extern u8 *func_0029EFD0(int);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern float func_002A7878(float, float);
extern void func_00283028(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A7820(int, int);
extern void func_L04_00358AE8(void *, void *, int, int, float);
extern void func_L04_003F9C60(u8 *, int);
extern void func_0029F338(void *);
extern void *func_L04_00358868(void *, float, int, int, int);
extern u8 *func_L04_0035F3E0(void *, void *, int, float);
extern float func_00283CE0(int);
extern float func_002A7AA8(float, float, float, float, float);
extern int func_00283CF0(float);

/* Spawns the kind-0xABC shot from `owner` at `pos` along `dir`. When the way from the owner
   is blocked it sparks five times at the contact and removes itself (returning 0); otherwise
   it starts its trail and lays out seventeen glow sprites whose size and alpha ease along it.
   Returns the object, or 0. */
u8 *func_L04_003F9320(u8 *owner, Quad *pos, Quad *dir, s32 target)
{
    f32 p[4] __attribute__((aligned(16)));
    f32 d[4] __attribute__((aligned(16)));
    Hit3F9320 t __attribute__((aligned(16)));
    Quad from;
    f32 w[4] __attribute__((aligned(16)));
    f32 v[4] __attribute__((aligned(16)));
    f32 *pp;
    f32 *dp;
    u8 *obj;
    u8 *st;
    u8 **slot;
    u8 *q;
    f32 e;
    int i;

    pp = p;
    dp = d;
    *(Quad *)pp = *pos;
    *(Quad *)dp = *dir;
    obj = func_0029EFD0(0xABC);
    if (obj != 0) {
    st = *(u8 **)(obj + 0x68);
    *(u8 **)(st + 0x18) = owner;
    *(s16 *)(obj + 0x32) = 0x7F;
    obj[0x31] = 1;
    obj[0x30] = 0x7F;
    *(long *)(obj + 0x38) = *(long *)(owner + 0x38);
    *(s32 *)(obj + 0xF0) = 0;
    *(f32 *)(obj + 0xF4) = -func_00283248(func_00282E20(dp), dp[2]);
    *(f32 *)(obj + 0xF8) = func_00283248(dp[0], dp[1]);
    *(Quad *)(obj + 0x10) = *(Quad *)pp;
    *(Quad *)st = *(Quad *)dp;
    *(s32 *)(st + 0x14) = target;
    *(s32 *)(st + 0x10) = target;
    t.owner = *(s32 *)(st + 0x18);
    t.flags = 0x30000;
    t.scale = 13.0f;
    t.extra = 1;
    *(Quad *)t.v = *(Quad *)st;
    func_00282F70(&t, &t, 1.0f);
    t.v[3] = 5627.9248046875f;
    t.mode = 1;
    t.v[2] = 1.0f;
    t.kind = 1;
    t.source = *(u16 *)(obj + 0xAA);
    from = *(Quad *)(owner + 0x10);
    ((f32 *)&from)[2] = pp[2];
    if (func_002761F8(&from, pp, 0, owner, &t)) {
        *(Quad *)(obj + 0x10) = D_L04_001BFAE0;
        for (i = 4; i >= 0; i--) {
            *(Quad *)v = 0;
            v[0] = func_002A7878(-1.0f, 1.0f);
            v[1] = func_002A7878(-1.0f, 1.0f);
            v[2] = func_002A7878(-1.0f, 1.0f);
            *(Quad *)w = *(Quad *)v;
            func_00283028(v, st, D_L04_001BFB00);
            func_00282F20(w, w, func_00282DF0(v) * 0.5f);
            func_00282CC0(v, v, w);
            func_00282F20(v, v, func_002A7878(0.05000000447f, 0.10000000894f));
            func_L04_00358AE8(obj + 0x10, v, 0x7F2F4F6F, func_002A7820(10, 15), 15000.0f);
        }
        func_L04_003F9C60(obj, 0);
        func_0029F338(obj);
        return 0;
    }
    func_L04_00358868(obj, 100000.0f, 0x2F4F7F7F, *(s32 *)(st + 0x10), -1);
    slot = (u8 **)(st + 0x1C);
    for (i = 0; i < 17; i++, slot++) {
        q = func_L04_0035F3E0(obj + 0x10, D_001A8F20, 1, 0.0f);
        if (q == 0) {
            *slot = 0;
            continue;
        }
        *(f32 *)(q + 0xC) = func_002A7878(15000.0f, 25000.0f);
        e = func_002A7AA8(-1.5f, 0.0f, 1.0f, 0.0f, func_00283CE0(i) / func_00283CE0(16));
        *(f32 *)(q + 0xC) = *(f32 *)(q + 0xC) + (8000.0f - *(f32 *)(q + 0xC)) * e;
        *(u32 *)(q + 4) = (func_00283CF0(e * -64.0f + 128.0f) << 24) | 0xFFFFFF;
        *slot = q;
    }
    }
    return obj;
}
