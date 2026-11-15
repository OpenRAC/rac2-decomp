#include "names.h"
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
extern char g_camera_l00_position[];

extern float ApproachValue(float *, float, float);
extern int PlayMobySound(int, int, char *);
extern int math_fast_float_d(void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern int math_random_int_below(int);
extern void vec_scale_to_length(void *, void *, float);
extern void func_PAL_L00_00388038(void *, void *);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(char *);
extern s32 math_lerp_int(s32, s32, f32);
extern char *hoverbomb_create_projectile(char *, void *, void *);

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
        ApproachValue(&st->drop, 0.0f, 0.0050000004f);
    else
        ApproachValue(&st->drop, -0.2f, 0.00040000002f);
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
        PlayMobySound(0, 0, D_L00_00232A60[0]);
    math_fast_float_d(&st->timer);
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
        FastVecScale(va.f, D_L00_001AEDF0, (float)(i / 8));
        FastVecScale(vb, D_L00_001AEDE0, (float)(i % 8));
        FastVecAdd(va.f, va.f, vb);
        FastVecAdd(va.f, va.f, base);
        matrix_mul_vec3(D_L00_00232A60[i] + 0x10, va.f, g_camera_l00_position + 0x230);
        FastVecAdd(D_L00_00232A60[i] + 0x10, D_L00_00232A60[i] + 0x10, g_camera_l00_position);
        *(float *)(D_L00_00232A60[i] + 0x2C) = *(float *)(((Tile_384678 *)D_L00_00232A60[i])->cls + 0x24) * D_L00_001AED60;
        if ((((Tile_384678 *)D_L00_00232A60[i])->flags ^ 1) & 1) {
            hit++;
            if (part_find_owned_effect_slot(D_L00_00232A60[i], -1, 0)) {
                if (!math_random_int_below(3))
                    PlayMobySound(0, 0, D_L00_00232A60[i]);
                ((Tile_384678 *)D_L00_00232A60[i])->flags |= 0x41;
                ((Tile_384678 *)D_L00_00232A60[i])->flags &= 0xEFFF;
                *(s32 *)(D_L00_00232A60[i] + 0x98) = 0;
                *(u8 *)(D_L00_00232A60[i] + 0xA8) = 0xFF;
                vec_scale_to_length(vc, D_L00_00232A60[i] + 0xE0, 0.05f);
                FastVecAdd(vc, vc, D_L00_00232A60[i] + 0x10);
                func_PAL_L00_00388038(D_L00_00232A60[i], vc);
            }
            func_PAL_002A0F68(D_L00_00232A60[i]);
            func_002A0F48(D_L00_00232A60[i]);
        }
    }
    pick = math_random_int_below(hit);
    if (hit != 0 && math_fast_float_d(&st->liftTimer)) {
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
            st->liftTimer = (math_lerp_int(1, 0xF0, t) * 5 + 2) / 6;
            va.q = 0;
            va.f[2] = 0.05f;
            matrix_mul_vec3(va.f, va.f, D_L00_00232A60[count] + 0xC0);
            FastVecAdd(va.f, va.f, D_L00_00232A60[count] + 0x10);
            vec_scale_to_length(vb, D_L00_00232A60[count] + 0xC0, D_L00_001AEDB8 * 0.020000001f);
            hoverbomb_create_projectile(D_L00_00232A60[count], va.f, vb);
        }
    }
}
