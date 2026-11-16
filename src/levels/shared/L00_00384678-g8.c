#include "names.h"
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

extern char *g_sheep_board_tiles[24];
extern float g_sheep_board_base_vector[4] SDATA(D_L00_001AED40);
extern float g_sheep_board_row_step[4] __attribute__((sda));
extern float g_sheep_board_column_step[4] SDATA(D_L00_001AEDE0);
extern float g_sheep_board_y_limit __attribute__((sda));
extern float g_sheep_board_sway_speed __attribute__((sda));
extern float g_sheep_board_scale __attribute__((sda));
extern float g_sheep_board_velocity_length __attribute__((sda));
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
extern void part_spawn_goal_score(char *, void *);
extern void func_002A05A8(char *);
extern void func_002A0F48(char *);
extern s32 math_lerp_int(s32, s32, f32);
extern char *hoverbomb_create_projectile(char *, void *, void *);

/* Runs the board of 24 sheep: sways the grid, lifts hit sheep up and, when some are still standing, launches a Hoverbomb Projectile. */
void sheep_board_update(char *owner)
{
    Board_384678 *board;
    float base[4] __attribute__((aligned(16)));
    union { TI128 q; float f[4]; } va;
    float vb[4] __attribute__((aligned(16)));
    float vc[4] __attribute__((aligned(16)));
    int all, i, hit, chosen;
    int scan = 0, remaining, count;
    float lift_rate, half, one;

    board = *(Board_384678 **)(owner + 0x68);
    if (0.0f < board->drop)
        ApproachValue(&board->drop, 0.0f, 0.004166667f);
    else
        ApproachValue(&board->drop, -0.2f, 0.00033333333f);
    all = 1;
    for (scan = 0; scan < 24; scan++) {
        if ((((Tile_384678 *)g_sheep_board_tiles[scan])->flags ^ 1) & 1) {
            all = 0;
            break;
        }
    }
    if (all) {
        board->timer = 0x2D;
        board->drop = 0.5f;
        board->rounds++;
        for (remaining = 0; remaining < 24; remaining++) {
            ((Tile_384678 *)g_sheep_board_tiles[remaining])->flags &= ~0x41;
            ((Tile_384678 *)g_sheep_board_tiles[remaining])->flags |= 0x1000;
            *(s32 *)(g_sheep_board_tiles[remaining] + 0x98) = *(s32 *)(((Tile_384678 *)g_sheep_board_tiles[remaining])->cls + 0x10);
        }
    }
    if (board->timer != 0 && board->timer % 5 == 0)
        PlayMobySound(0, 0, g_sheep_board_tiles[0]);
    math_fast_float_d(&board->timer);
    *(TI128 *)base = *(TI128 *)g_sheep_board_base_vector;
    base[1] += board->x - board->drop;
    base[2] += board->y;
    if (board->sway == 0.0f)
        board->sway = g_sheep_board_sway_speed * 0.016666668f;
    board->y += board->sway;
    if (g_sheep_board_y_limit < board->y)
        board->sway = -(g_sheep_board_sway_speed * 0.016666668f);
    else if (board->y < -g_sheep_board_y_limit)
        board->sway = g_sheep_board_sway_speed * 0.016666668f;

    hit = 0;
    for (i = 0; i < 24; i++) {
        FastVecScale(va.f, g_sheep_board_row_step, (float)(i / 8));
        FastVecScale(vb, g_sheep_board_column_step, (float)(i % 8));
        FastVecAdd(va.f, va.f, vb);
        FastVecAdd(va.f, va.f, base);
        matrix_mul_vec3(g_sheep_board_tiles[i] + 0x10, va.f, g_camera_l00_position + 0x230);
        FastVecAdd(g_sheep_board_tiles[i] + 0x10, g_sheep_board_tiles[i] + 0x10, g_camera_l00_position);
        *(float *)(g_sheep_board_tiles[i] + 0x2C) = *(float *)(((Tile_384678 *)g_sheep_board_tiles[i])->cls + 0x24) * g_sheep_board_scale;
        if ((((Tile_384678 *)g_sheep_board_tiles[i])->flags ^ 1) & 1) {
            hit++;
            if (part_find_owned_effect_slot(g_sheep_board_tiles[i], -1, 0)) {
                if (!math_random_int_below(3))
                    PlayMobySound(0, 0, g_sheep_board_tiles[i]);
                ((Tile_384678 *)g_sheep_board_tiles[i])->flags |= 0x41;
                ((Tile_384678 *)g_sheep_board_tiles[i])->flags &= 0xEFFF;
                *(s32 *)(g_sheep_board_tiles[i] + 0x98) = 0;
                *(u8 *)(g_sheep_board_tiles[i] + 0xA8) = 0xFF;
                vec_scale_to_length(vc, g_sheep_board_tiles[i] + 0xE0, 0.05f);
                FastVecAdd(vc, vc, g_sheep_board_tiles[i] + 0x10);
                part_spawn_goal_score(g_sheep_board_tiles[i], vc);
            }
            func_002A05A8(g_sheep_board_tiles[i]);
            func_002A0F48(g_sheep_board_tiles[i]);
        }
    }
    chosen = math_random_int_below(hit);
    if (hit != 0 && math_fast_float_d(&board->liftTimer)) {
        for (count = 0; count < 24; count++) {
            if (!((((Tile_384678 *)g_sheep_board_tiles[count])->flags ^ 1) & 1))
                continue;
            if (--chosen != 0)
                continue;
            one = 1.0f;
            half = 0.5f;
            lift_rate = one / ((float)(board->rounds + 1) * half);
            if (1.0f < lift_rate)
                lift_rate = 1.0f;
            else if (lift_rate < 0.0f)
                lift_rate = 0.0f;
            board->liftTimer = math_lerp_int(1, 0xF0, lift_rate);
            va.q = 0;
            va.f[2] = 0.05f;
            matrix_mul_vec3(va.f, va.f, g_sheep_board_tiles[count] + 0xC0);
            FastVecAdd(va.f, va.f, g_sheep_board_tiles[count] + 0x10);
            vec_scale_to_length(vb, g_sheep_board_tiles[count] + 0xC0, g_sheep_board_velocity_length * 0.016666668f);
            hoverbomb_create_projectile(g_sheep_board_tiles[count], va.f, vb);
        }
    }
}
