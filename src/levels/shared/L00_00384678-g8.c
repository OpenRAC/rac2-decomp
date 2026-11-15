/* func_L00_00384678: built with -G8 (gp-relative vectors) and the qcopy/zero-TI
 * profile in config/cflags.txt.  The `scan = 0` declaration init sizes gcse's
 * expression table (167 buckets), which numbers the gp-vector PRE copy before
 * &st->timer (retail s0/s1).  `one` and `half` hold the clamp constants so that
 * loop.c hoists 1.0 and 0.5 in its first pass and the clamp zero in its second
 * (retail f20/f22/f21).
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

/* Runs the board of 24 sheep: sways the grid, lifts hit sheep up and, when some are still standing, launches a Hoverbomb Projectile. */
void func_L00_00384678(char *owner)
{
    Board_384678 *board;
    float base[4] __attribute__((aligned(16)));
    union { TI128 q; float f[4]; } va;
    float vb[4] __attribute__((aligned(16)));
    float vc[4] __attribute__((aligned(16)));
    int all, i, hit, chosen;
    int scan = 0, remaining, count;
    float liftRate, half, one;

    board = *(Board_384678 **)(owner + 0x68);
    if (0.0f < board->drop)
        ApproachValue(&board->drop, 0.0f, 0.004166667f);
    else
        ApproachValue(&board->drop, -0.2f, 0.00033333333f);
    all = 1;
    for (scan = 0; scan < 24; scan++) {
        if ((((Tile_384678 *)D_L00_00232A60[scan])->flags ^ 1) & 1) {
            all = 0;
            break;
        }
    }
    if (all) {
        board->timer = 0x2D;
        board->drop = 0.5f;
        board->rounds++;
        for (remaining = 0; remaining < 24; remaining++) {
            ((Tile_384678 *)D_L00_00232A60[remaining])->flags &= ~0x41;
            ((Tile_384678 *)D_L00_00232A60[remaining])->flags |= 0x1000;
            *(s32 *)(D_L00_00232A60[remaining] + 0x98) = *(s32 *)(((Tile_384678 *)D_L00_00232A60[remaining])->cls + 0x10);
        }
    }
    if (board->timer != 0 && board->timer % 5 == 0)
        PlayMobySound(0, 0, D_L00_00232A60[0]);
    FastFloatHelperD(&board->timer);
    *(TI128 *)base = *(TI128 *)D_L00_001AED40;
    base[1] += board->x - board->drop;
    base[2] += board->y;
    if (board->sway == 0.0f)
        board->sway = D_L00_001AEE04 * 0.016666668f;
    board->y += board->sway;
    if (D_L00_001AEE00 < board->y)
        board->sway = -(D_L00_001AEE04 * 0.016666668f);
    else if (board->y < -D_L00_001AEE00)
        board->sway = D_L00_001AEE04 * 0.016666668f;

    hit = 0;
    for (i = 0; i < 24; i++) {
        FastVecScale(va.f, D_L00_001AEDF0, (float)(i / 8));
        FastVecScale(vb, D_L00_001AEDE0, (float)(i % 8));
        FastVecAdd(va.f, va.f, vb);
        FastVecAdd(va.f, va.f, base);
        matrix_mul_vec3(D_L00_00232A60[i] + 0x10, va.f, gCameraPosition_L00 + 0x230);
        FastVecAdd(D_L00_00232A60[i] + 0x10, D_L00_00232A60[i] + 0x10, gCameraPosition_L00);
        *(float *)(D_L00_00232A60[i] + 0x2C) = *(float *)(((Tile_384678 *)D_L00_00232A60[i])->cls + 0x24) * D_L00_001AED60;
        if ((((Tile_384678 *)D_L00_00232A60[i])->flags ^ 1) & 1) {
            hit++;
            if (FindOwnedEffectSlot(D_L00_00232A60[i], -1, 0)) {
                if (!RandomIntBelow(3))
                    PlayMobySound(0, 0, D_L00_00232A60[i]);
                ((Tile_384678 *)D_L00_00232A60[i])->flags |= 0x41;
                ((Tile_384678 *)D_L00_00232A60[i])->flags &= 0xEFFF;
                *(s32 *)(D_L00_00232A60[i] + 0x98) = 0;
                *(u8 *)(D_L00_00232A60[i] + 0xA8) = 0xFF;
                vec_scale_to_length(vc, D_L00_00232A60[i] + 0xE0, 0.05f);
                FastVecAdd(vc, vc, D_L00_00232A60[i] + 0x10);
                SpawnGoalScoreParticles(D_L00_00232A60[i], vc);
            }
            func_002A05A8(D_L00_00232A60[i]);
            func_002A0F48(D_L00_00232A60[i]);
        }
    }
    chosen = RandomIntBelow(hit);
    if (hit != 0 && FastFloatHelperD(&board->liftTimer)) {
        for (count = 0; count < 24; count++) {
            if (!((((Tile_384678 *)D_L00_00232A60[count])->flags ^ 1) & 1))
                continue;
            if (--chosen != 0)
                continue;
            one = 1.0f;
            half = 0.5f;
            liftRate = one / ((float)(board->rounds + 1) * half);
            if (1.0f < liftRate)
                liftRate = 1.0f;
            else if (liftRate < 0.0f)
                liftRate = 0.0f;
            board->liftTimer = LerpInt(1, 0xF0, liftRate);
            va.q = 0;
            va.f[2] = 0.05f;
            matrix_mul_vec3(va.f, va.f, D_L00_00232A60[count] + 0xC0);
            FastVecAdd(va.f, va.f, D_L00_00232A60[count] + 0x10);
            vec_scale_to_length(vb, D_L00_00232A60[count] + 0xC0, D_L00_001AEDB8 * 0.016666668f);
            CreateHoverbombProjectile(D_L00_00232A60[count], va.f, vb);
        }
    }
}
