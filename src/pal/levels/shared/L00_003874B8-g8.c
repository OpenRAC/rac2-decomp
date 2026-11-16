#include "names.h"
/* func_PAL_L00_003874B8, the PAL copy of func_L00_00384678 (src/levels/shared/L00_00384678-g8.c):
 * the same C, with the frame steps at 50 Hz and the lift delay rescaled. Built with -G8
 * (gp-relative vectors) and the qcopy and gcse-unsplit-edges profile in config/cflags.txt.
 *
 * `scan = 0, remaining = 0` are dead initial values (each loop's `for` sets its counter
 * again); they size gcse's expression table (171 buckets; 167 also gives retail's s0/s1
 * order, 169 swaps them). Dropping either or both swaps &board->timer and the gp vector
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
extern void part_spawn_goal_score_pal(void *, void *);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(char *);
extern s32 math_lerp_int(s32, s32, f32);
extern char *hoverbomb_create_projectile(char *, void *, void *);

/* Updates the sheep board: moves the grid of tiles, respawns it when all are cleared, and lets a random live tile launch a hoverbomb (PAL: 50 Hz timings). */
void sheep_board_update_pal(char *obj)
{
    Board_384678 *board;
    float base[4] __attribute__((aligned(16)));
    union { TI128 q; float f[4]; } vec_a;
    float vec_b[4] __attribute__((aligned(16)));
    float vec_c[4] __attribute__((aligned(16)));
    int all, i, hit, pick;
    int scan = 0, remaining = 0, count;
    float blend;

    board = *(Board_384678 **)(obj + 0x68);
    if (0.0f < board->drop)
        ApproachValue(&board->drop, 0.0f, 0.0050000004f);
    else
        ApproachValue(&board->drop, -0.2f, 0.00040000002f);
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
        board->sway = g_sheep_board_sway_speed * 0.020000001f;
    board->y += board->sway;
    if (g_sheep_board_y_limit < board->y)
        board->sway = -(g_sheep_board_sway_speed * 0.020000001f);
    else if (board->y < -g_sheep_board_y_limit)
        board->sway = g_sheep_board_sway_speed * 0.020000001f;

    hit = 0;
    for (i = 0; i < 24; i++) {
        FastVecScale(vec_a.f, g_sheep_board_row_step, (float)(i / 8));
        FastVecScale(vec_b, g_sheep_board_column_step, (float)(i % 8));
        FastVecAdd(vec_a.f, vec_a.f, vec_b);
        FastVecAdd(vec_a.f, vec_a.f, base);
        matrix_mul_vec3(g_sheep_board_tiles[i] + 0x10, vec_a.f, g_camera_l00_position + 0x230);
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
                vec_scale_to_length(vec_c, g_sheep_board_tiles[i] + 0xE0, 0.05f);
                FastVecAdd(vec_c, vec_c, g_sheep_board_tiles[i] + 0x10);
                part_spawn_goal_score_pal(g_sheep_board_tiles[i], vec_c);
            }
            func_PAL_002A0F68(g_sheep_board_tiles[i]);
            func_002A0F48(g_sheep_board_tiles[i]);
        }
    }
    pick = math_random_int_below(hit);
    if (hit != 0 && math_fast_float_d(&board->liftTimer)) {
        for (count = 0; count < 24; count++) {
            if (!((((Tile_384678 *)g_sheep_board_tiles[count])->flags ^ 1) & 1))
                continue;
            if (--pick != 0)
                continue;
            blend = 1.0f / ((float)(board->rounds + 1) * 0.5f);
            if (1.0f < blend)
                blend = 1.0f;
            else if (blend < 0.0f)
                blend = 0.0f;
            board->liftTimer = (math_lerp_int(1, 0xF0, blend) * 5 + 2) / 6;
            vec_a.q = 0;
            vec_a.f[2] = 0.05f;
            matrix_mul_vec3(vec_a.f, vec_a.f, g_sheep_board_tiles[count] + 0xC0);
            FastVecAdd(vec_a.f, vec_a.f, g_sheep_board_tiles[count] + 0x10);
            vec_scale_to_length(vec_b, g_sheep_board_tiles[count] + 0xC0, g_sheep_board_velocity_length * 0.020000001f);
            hoverbomb_create_projectile(g_sheep_board_tiles[count], vec_a.f, vec_b);
        }
    }
}
