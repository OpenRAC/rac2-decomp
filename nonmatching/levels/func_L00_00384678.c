/* 2 November 2026:
 * func_L00_00384D40 returns its allocated object pointer. Correct that ignored return
 * declaration from the matched callee. The current qualified profile still emits 1448/1448
 * bytes, 0/27 US placements; table HIGH reuse, copied-pointer allocation and FP constant
 * ordering remain. No complete match.
 */
/* GPT-6.1 Sol high, v1127, USA v1.01: 1448/1448 bytes, 0/27 places.
 * Profile: -O2 -G8 -ffunction-sections -frac2-zero-ti-por
 *          -frac2-qcopy -frac2-qcopy-barrier -g -frac2-gcse-unsplit-edges.
 * Sixteen check.py trials and one regalloc.py inspection (two diagnostic
 * compiles). The retained draft has 155 differing side-by-side lines,
 * versus 338 in the incoming 1452-byte draft; relocated addresses/calls
 * are included in those counts. The first rejected instruction is +0x9C.
 * The 0xC0 frame, saved registers and vector-pointer spills at 0x40/0x44
 * now agree. Direct array/union addresses let the compiler split vector
 * pointer lifetimes; separate scan/reset/main/final counters recover the
 * loop allocations. SDATA gives the two measured GP-relative vectors.
 * Unsplit GCSE edges recover the initial scan's branch/layout; an explicit
 * lower clamp bound keeps the third FP constant live across the last loop.
 * Remaining: table HIGH is retained in s0 across early calls, instead of
 * using a3 then rebuilding it; this changes timer/copy registers and loop
 * setup. The last loop assigns zero/half to f22/f21 instead of f21/f22,
 * and por/float materialization and the scalar store/table load exchange
 * order. Ordinary TI copy and qcopy/qcopy_nc do not resolve the HIGH reuse.
 * Disabling GCSE, rerun-CSE, or CSE branch following did not improve it.
 * Explicit half initialization hoisted two extra FP constants. Rewriting
 * the lower assignment and using an aligned-array TI clear tied this draft.
 * Reopen on independently supported address/constant lifetime evidence.
 * The signed 32-bit mask prototype follows retail's sign-extended -1;
 * the matched callee consumes only its low 32 bits in the mask operation.
 * All required declarations and measured partial layouts follow below.
 * 0x700014A9 is por v0,zero,zero: it is not handwritten-code evidence.
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
extern void func_L00_003851A0(char *, void *);
extern void func_002A05A8(char *);
extern void func_002A0F48(char *);
extern s32 func_L00_0031D620(s32, s32, f32);
extern char *func_L00_00384D40(char *, void *, void *);

void func_L00_00384678(char *obj)
{
    Board_384678 *st;
    float base[4] __attribute__((aligned(16)));
    union { TI128 q; float f[4]; } va;
    float vb[4] __attribute__((aligned(16)));
    float vc[4] __attribute__((aligned(16)));
    int all, i, hit, pick;
    int scan, remaining, count;
    char **reset;
    char **tile;
    float t, lower;

    st = *(Board_384678 **)(obj + 0x68);
    if (0.0f < st->drop)
        func_002AA2E8(&st->drop, 0.0f, 0.004166667f);
    else
        func_002AA2E8(&st->drop, -0.2f, 0.00033333333f);
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
        for (reset = D_L00_00232A60, remaining = 23; remaining >= 0; remaining--, reset++) {
            ((Tile_384678 *)*reset)->flags &= ~0x41;
            ((Tile_384678 *)*reset)->flags |= 0x1000;
            *(s32 *)(*reset + 0x98) = *(s32 *)(((Tile_384678 *)*reset)->cls + 0x10);
        }
    }
    if (st->timer != 0 && st->timer % 5 == 0)
        func_002E5CF8(0, 0, D_L00_00232A60[0]);
    func_00282948(&st->timer);
    *(TI128 *)base = *(TI128 *)D_L00_001AED40;
    base[1] += st->x - st->drop;
    base[2] += st->y;
    if (st->sway == 0.0f)
        st->sway = D_L00_001AEE04 * 0.016666668f;
    st->y += st->sway;
    if (D_L00_001AEE00 < st->y)
        st->sway = -(D_L00_001AEE04 * 0.016666668f);
    else if (st->y < -D_L00_001AEE00)
        st->sway = D_L00_001AEE04 * 0.016666668f;

    hit = 0;
    for (tile = D_L00_00232A60, i = 0; i < 24; i++, tile++) {
        func_00282D30(va.f, D_L00_001AEDF0, (float)(i / 8));
        func_00282D30(vb, D_L00_001AEDE0, (float)(i % 8));
        func_00282CC0(va.f, va.f, vb);
        func_00282CC0(va.f, va.f, base);
        func_00283098((*tile) + 0x10, va.f, D_L00_001B8DC0 + 0x230);
        func_00282CC0((*tile) + 0x10, (*tile) + 0x10, D_L00_001B8DC0);
        *(float *)((*tile) + 0x2C) = *(float *)(((Tile_384678 *)*tile)->cls + 0x24) * D_L00_001AED60;
        if ((((Tile_384678 *)*tile)->flags ^ 1) & 1) {
            hit++;
            if (func_002A9640(*tile, -1, 0)) {
                if (!func_002A77E0(3))
                    func_002E5CF8(0, 0, *tile);
                ((Tile_384678 *)*tile)->flags |= 0x41;
                ((Tile_384678 *)*tile)->flags &= 0xEFFF;
                *(s32 *)((*tile) + 0x98) = 0;
                *(u8 *)((*tile) + 0xA8) = 0xFF;
                func_00282F20(vc, (*tile) + 0xE0, 0.05f);
                func_00282CC0(vc, vc, (*tile) + 0x10);
                func_L00_003851A0(*tile, vc);
            }
            func_002A05A8(*tile);
            func_002A0F48(*tile);
        }
    }
    pick = func_002A77E0(hit);
    if (hit != 0 && func_00282948(&st->liftTimer)) {
        lower = 0.0f;
        for (tile = D_L00_00232A60, count = 23; count >= 0; count--, tile++) {
            if (!((((Tile_384678 *)*tile)->flags ^ 1) & 1))
                continue;
            if (--pick != 0)
                continue;
            t = 1.0f / ((float)(st->rounds + 1) * 0.5f);
            if (1.0f < t)
                t = 1.0f;
            else if (t < lower)
                t = 0.0f;
            st->liftTimer = func_L00_0031D620(1, 0xF0, t);
            va.q = 0;
            va.f[2] = 0.05f;
            func_00283098(va.f, va.f, *tile + 0xC0);
            func_00282CC0(va.f, va.f, *tile + 0x10);
            func_00282F20(vb, *tile + 0xC0, D_L00_001AEDB8 * 0.016666668f);
            func_L00_00384D40(*tile, va.f, vb);
        }
    }
}
