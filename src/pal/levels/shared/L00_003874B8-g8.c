/* func_PAL_L00_003874B8, the PAL copy of func_L00_00384678 (src/levels/shared/L00_00384678-g8.c):
 * the same C, with the frame steps at 50 Hz and the lift delay rescaled. Built with -G8
 * (gp-relative vectors) and the qcopy and gcse-unsplit-edges profile in config/cflags.txt.
 *
 * `scan = 0, remaining = 0` are dead initial values (each loop's `for` sets its counter
 * again); they size gcse's expression table (171 buckets; 167 also gives retail's s0/s1
 * order, 169 swaps them). Dropping either or both swaps &st->timer and the gp vector
 * between s0 and s1. The USA copy keeps `scan = 0` for the same reason; this copy needs both.
 * Unlike the USA copy, the clamp constants are literals (no `one` or `half` local), so that
 * loop.c hoists only 1.0 and the divisor 6. The hazard nop between `mtc1 $0,$f0` and `c.lt.s`
 * behind the clamp's `b` is the assembler's: gas keeps it after an unconditional branch
 * (tools/compiler/transformers/restrict_mtc1_exemption.py).
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char pad00[0x24];
    char *cls;
    char pad28[0x34 - 0x28];
    u16 flags;
} Tile_384678;

typedef struct {
    char pad00[0x50];
    float x;
    float y;
    float pad58;
    float sway;
    char pad60[0x6C - 0x60];
    s32 liftTimer;
    s32 rounds;
    float drop;
    s32 timer;
} Board_384678;

extern char *D_L00_00232A60[24];
extern float D_L00_001AED40[4] SDATA(D_L00_001AED40);
extern float D_L00_001AEDF0[4] __attribute__((sda));
extern float D_L00_001AEDE0[4] SDATA(D_L00_001AEDE0);
extern float D_L00_001AEE00 __attribute__((sda));
extern float D_L00_001AEE04 __attribute__((sda));
extern float D_L00_001AED60 __attribute__((sda));
extern float D_L00_001AEDB8 __attribute__((sda));
extern char D_L00_001B8DC0[];

extern float func_002AA2E8(float *, float, float);
extern int func_002E5CF8(int, int, char *);
extern int func_00282948(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void *func_002A9640(void *, s32, s32);
extern int func_002A77E0(int);
extern void func_00282F20(void *, void *, float);
extern void func_PAL_L00_00388038(void *, void *);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(char *);
extern s32 func_L00_0031D620(s32, s32, f32);
extern char *func_L00_00384D40(char *, void *, void *);

void func_PAL_L00_003874B8(char *obj)
{
    Board_384678 *st;
    float base[4] __attribute__((aligned(16)));
    union { TI128 q; float f[4]; } va;
    float vb[4] __attribute__((aligned(16)));
    float vc[4] __attribute__((aligned(16)));
    int all, i, hit, pick;
    int scan = 0, remaining = 0, count;
    float t;

    st = *(Board_384678 **)(obj + 0x68);
    if (0.0f < st->drop)
        func_002AA2E8(&st->drop, 0.0f, 0.0050000004f);
    else
        func_002AA2E8(&st->drop, -0.2f, 0.00040000002f);
    all = 1;
    for (scan = 0; scan < 24; scan++) {
        if ((((Tile_384678 *)D_L00_00232A60[scan])->flags ^ 1) & 1) {
            all = 0;
            break;
        }
    }
    if (all) {
        st->timer = 0x2D;
        st->drop = 0.5f;
        st->rounds++;
        for (remaining = 0; remaining < 24; remaining++) {
            ((Tile_384678 *)D_L00_00232A60[remaining])->flags &= ~0x41;
            ((Tile_384678 *)D_L00_00232A60[remaining])->flags |= 0x1000;
            *(s32 *)(D_L00_00232A60[remaining] + 0x98) = *(s32 *)(((Tile_384678 *)D_L00_00232A60[remaining])->cls + 0x10);
        }
    }
    if (st->timer != 0 && st->timer % 5 == 0)
        func_002E5CF8(0, 0, D_L00_00232A60[0]);
    func_00282948(&st->timer);
    *(TI128 *)base = *(TI128 *)D_L00_001AED40;
    base[1] += st->x - st->drop;
    base[2] += st->y;
    if (st->sway == 0.0f)
        st->sway = D_L00_001AEE04 * 0.020000001f;
    st->y += st->sway;
    if (D_L00_001AEE00 < st->y)
        st->sway = -(D_L00_001AEE04 * 0.020000001f);
    else if (st->y < -D_L00_001AEE00)
        st->sway = D_L00_001AEE04 * 0.020000001f;

    hit = 0;
    for (i = 0; i < 24; i++) {
        func_00282D30(va.f, D_L00_001AEDF0, (float)(i / 8));
        func_00282D30(vb, D_L00_001AEDE0, (float)(i % 8));
        func_00282CC0(va.f, va.f, vb);
        func_00282CC0(va.f, va.f, base);
        func_00283098(D_L00_00232A60[i] + 0x10, va.f, D_L00_001B8DC0 + 0x230);
        func_00282CC0(D_L00_00232A60[i] + 0x10, D_L00_00232A60[i] + 0x10, D_L00_001B8DC0);
        *(float *)(D_L00_00232A60[i] + 0x2C) = *(float *)(((Tile_384678 *)D_L00_00232A60[i])->cls + 0x24) * D_L00_001AED60;
        if ((((Tile_384678 *)D_L00_00232A60[i])->flags ^ 1) & 1) {
            hit++;
            if (func_002A9640(D_L00_00232A60[i], -1, 0)) {
                if (!func_002A77E0(3))
                    func_002E5CF8(0, 0, D_L00_00232A60[i]);
                ((Tile_384678 *)D_L00_00232A60[i])->flags |= 0x41;
                ((Tile_384678 *)D_L00_00232A60[i])->flags &= 0xEFFF;
                *(s32 *)(D_L00_00232A60[i] + 0x98) = 0;
                *(u8 *)(D_L00_00232A60[i] + 0xA8) = 0xFF;
                func_00282F20(vc, D_L00_00232A60[i] + 0xE0, 0.05f);
                func_00282CC0(vc, vc, D_L00_00232A60[i] + 0x10);
                func_PAL_L00_00388038(D_L00_00232A60[i], vc);
            }
            func_PAL_002A0F68(D_L00_00232A60[i]);
            func_002A0F48(D_L00_00232A60[i]);
        }
    }
    pick = func_002A77E0(hit);
    if (hit != 0 && func_00282948(&st->liftTimer)) {
        for (count = 0; count < 24; count++) {
            if (!((((Tile_384678 *)D_L00_00232A60[count])->flags ^ 1) & 1))
                continue;
            if (--pick != 0)
                continue;
            t = 1.0f / ((float)(st->rounds + 1) * 0.5f);
            if (1.0f < t)
                t = 1.0f;
            else if (t < 0.0f)
                t = 0.0f;
            st->liftTimer = (func_L00_0031D620(1, 0xF0, t) * 5 + 2) / 6;
            va.q = 0;
            va.f[2] = 0.05f;
            func_00283098(va.f, va.f, D_L00_00232A60[count] + 0xC0);
            func_00282CC0(va.f, va.f, D_L00_00232A60[count] + 0x10);
            func_00282F20(vb, D_L00_00232A60[count] + 0xC0, D_L00_001AEDB8 * 0.020000001f);
            func_L00_00384D40(D_L00_00232A60[count], va.f, vb);
        }
    }
}
