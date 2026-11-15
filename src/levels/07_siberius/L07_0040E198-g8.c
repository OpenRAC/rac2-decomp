#include "common.h"

/* func_L07_0040E198's state machine. A unit of its own: $gp data, a jump table and float
 * constants, with the copy and gcse options it needs (config/cflags.txt). */

typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vector;

typedef struct {
    u8 pad[0x6C];
    s16 f6C;
    u8 pad6E[4];
    s16 f72;
} GameStatus;

typedef struct {
    u8 pad[0x140];
    float pos[4];
    u8 pad150[0x16C - 0x150];
    int f16C;
    u8 pad170[0x180 - 0x170];
    float f180;
    int f184;
    int f188;
} CameraObject;

typedef struct {
    u8 pad00[0x90];
    int f90;
    u8 pad94[0xD0 - 0x94];
    int fD0;
    u8 padD4[0x100 - 0xD4];
    void *f100;
    u8 pad104[0x110 - 0x104];
    float f110;
    float f114;
    float f118;
    float f11C;
    u8 pad120[0x1AC - 0x120];
    int f1AC;
    u8 pad1B0[0x16B0 - 0x1B0];
    float f16B0;
    float f16B4;
    float f16B8;
    int f16BC;
    u8 pad16C0[8];
    float f16C8;
    int f16CC;
} ShipState;

typedef struct {
    u8 pad00[0x10];
    float pos[4];
    u8 state;
    u8 pad21[15];
    u8 f30;
    u8 f31;
    u16 f32;
    u16 flags;
    u8 pad36[0x68 - 0x36];
    ShipState *vars;
    u8 pad6C[0xAA - 0x6C];
    s16 classId;
    u8 padAC[4];
    u8 fB0;
    u8 padB1[0xC0 - 0xB1];
    float mtx[12];
    float rot[4];
} ShipObject;

extern void path_compute_centers_and_radii(void *);
extern void flag_block_clear(void *);
extern void ship_start_chain(void *);
extern void ship_start_second_phase(void *, int);
extern void ship_move_riders_along_path(void *);
extern void ship_run_sequence_events(void *);
extern void ship_update_attached_parts(void *);
extern void boss_enter_second_phase(void *);
extern void moby_build_matrix(void *);
extern void func_L07_00423B28(void *);
extern void func_L07_00423B80(void *);
extern void moby_set_state(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern int flag_set_first_pending(void *);
extern float math_approach_target_with_direction_mode(void *, void *, float, float, float, float, int);
extern void timer_start_countdown(int, float);
extern void load_scene_chunk(int, int);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void snd_resume_music_stream(void);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern float math_lerp_float(float, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_fabs(float);
extern void euler_rotation_basis(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float ApproachValue(void *, float, float);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(void *, void *);
extern float FastAddRotations(float, float);
extern void mat_combine_and_store(void *, void *, void *, void *);

extern int D_L07_001B1740 __attribute__((sda));
extern int D_L07_001C9780 NOT_SDA;
extern int D_L07_001B19F8;
extern u8 D_0018C0E2 NOT_SDA;
extern u8 D_001A7BD0;
extern int g_current_map_index;
extern u8 D_0019B2E8[][16];
extern void *D_0018A15C[3] NOT_SDA;
extern float D_L07_001B1D20;
extern GameStatus g_music_state;
extern int D_L07_001B9330 NOT_SDA;
extern CameraObject D_L07_001B90C0;
extern float D_L07_001B9200[4];
extern float D_L07_001B1744 __attribute__((sda));
extern float D_L07_001B1748 __attribute__((sda));
extern float D_L07_001B174C __attribute__((sda));
extern float D_L07_001B1750 __attribute__((sda));
extern float D_L07_001B1758 __attribute__((sda));
extern float D_L07_001B175C __attribute__((sda));
extern float D_L07_001B1760[2] __attribute__((sda));
/* Other code in this level reads a halfword at 0x1B2024; the int follows it. */
extern struct {
    s16 f0;
    s16 f2;
    int f4;
} D_L07_001B2024;

/* Main update for the Siberius ship objects (moby classes 4569 to 4573): starts them, runs the ride along the path, and plays the final crash sequence. */
void siberius_ship_update(ShipObject *ship)
{
    Vector savedPos, savedRot, v, w, x, y;
    ShipState *vars = ship->vars;
    float bounceSpeed, spin, offsetX, fadeState;
    int i;

    if (!vars)
        return;

    switch (ship->state) {
    case 0:
        ship->flags |= 1;
        ship->f31 = 0;
        path_compute_centers_and_radii(ship);
        vars->f1AC = -1;
        if (vars->f90 == -1) {
            if (ship->classId == 0x11D9 /* moby class 4569 */)
                moby_set_state(ship, 3, -1);
            else
                moby_set_state(ship, 4, -1);
        } else {
            ship->f30 = 255;
            flag_block_clear(ship);
            ship_start_chain(ship);
            moby_set_state(ship, 2, -1);
        }
        break;
    case 2:
        if (D_L07_001B1740) {
            D_L07_001B1740 = 0;
            ship_start_second_phase(vars->f100, vars->fD0);
        }
        if (D_L07_001C9780) {
            moby_set_state(ship, 1, -1);
            vars->f16CC = PlayMobySound(2, 4, ship);
            vars->f16C8 = 6.0f;
        }
        break;
    case 1:
        D_0018C0E2 = 1;
        D_L07_001B19F8 = 1;
        ship_move_riders_along_path(ship);
        ship_run_sequence_events(ship);
        break;
    case 3:
        if (flag_set_first_pending(ship))
            PlayMobySound(1, 0, ship);
        ship_update_attached_parts(ship);
        if (D_001A7BD0 || (D_0019B2E8[g_current_map_index][ship->fB0] & 0x80)) {
            ship_update_attached_parts(ship);
            ship->flags |= 2;
            break;
        }
        if (D_0018A15C[0] == ship) {
            if (vars->f110 >= 0.5f)
                PlayMobySound(1, 0, ship);
            math_approach_target_with_direction_mode(&vars->f110, &vars->f118, -1.0f, 0.0017453294713050127f,
                          0.0017453294713050127f, 0.10471977f, 0);
            if (vars->f110 <= -1.0f) {
                timer_start_countdown(1, 10.0f);
                if (D_L07_001B1D20 >= 1.0f) {
                    savedPos.q = 0;
                    savedRot.q = 0;
                    savedPos.f[0] = 191.5800018310547f;
                    savedPos.f[1] = 501.15f;
                    savedPos.f[2] = 457.69000244140625f;
                    savedRot.f[2] = 3.1415927f;
                    load_scene_chunk(1, 0);
                    hero_reset_position_and_direction(&savedPos, &savedRot, 0, 1);
                }
            }
        } else {
            math_approach_target_with_direction_mode(&vars->f110, &vars->f118, 0.5f, 0.0017453294713050127f,
                          0.0017453294713050127f, 0.10471977f, 0);
        }
        break;
    case 5:
        if (vars->f16B8 >= 1.0f && D_L07_001B1D20 >= 1.0f) {
            if (g_music_state.f72 != 3 || g_music_state.f6C >= 6000)
                break;
            D_L07_001B9330 = 0;
            snd_resume_music_stream();
        }
        savedPos.q = *(TI128 *)ship->pos;
        savedRot.q = *(TI128 *)ship->rot;
        if (vars->f16B8 > 0.0f) {
            math_step_value_toward_target(ship->pos, &vars->f11C, 400.0f, 0.0f, D_L07_001B1748 * 0.00027777778f,
                          D_L07_001B1744 * 0.016666668f);
            vars->f16B8 = (ship->pos[0] - 400.0f) * 0.014285714f;
            ship->rot[2] = math_lerp_float(D_L07_001B1750, 0.0f, vars->f16B8);
            ship->rot[0] = math_lerp_float(0.7853975296020508f, 0.0f, vars->f16B8);
            ship->pos[2] = 213.0f - vars->f16B8 * 3.0f;
        } else if ((fadeState = D_L07_001B1D20) == 0.0f) {
            matrix_mul_vec3(&v, D_L07_001B1760, ship->mtx);
            vars->f16B4 += ship->rot[0] * 7.272206130437553e-05f + 7.272206130437553e-05f;
            ship->rot[0] += vars->f16B4;
            if (ship->rot[0] > 1.5707964f) {
                ship->rot[0] = 1.5707964f;
                bounceSpeed = math_fabs(vars->f16B4);
                if (bounceSpeed < 0.0005817764904350042f)
                    timer_start_countdown(1, 15.0f);
                else
                    vars->f16B4 *= -0.333f;
                if (!vars->f16BC) {
                    D_L07_001B90C0.f16C = 0;
                    D_L07_001B90C0.f188 = 90;
                    D_L07_001B90C0.f180 = 0.02f;
                    vars->f16BC = 1;
                }
            }
            euler_rotation_basis(ship->mtx, ship->rot);
            matrix_mul_vec3(&w, D_L07_001B1760, ship->mtx);
            FastVecSub(&v, &w, &v);
            FastVecSub(ship->pos, ship->pos, &v);
        } else if (fadeState >= 1.0f) {
            boss_enter_second_phase(ship);
            break;
        }

        D_L07_001B2024.f4 = 1;
        ApproachValue(&vars->f16B0, 1.0f, D_L07_001B174C * 0.00027777778f);
        offsetX = vars->f11C + vars->f16B0;
        if (offsetX > 0.0f)
            offsetX = 0.0f;
        v.q = *(TI128 *)D_L07_001B9200;
        v.f[0] += offsetX;
        v.f[2] += D_L07_001B175C * 0.016666668f;
        func_L07_00423B28(&v);

        qzero_nc(&w);
        x.q = *(TI128 *)ship->pos;
        x.f[2] += 6.0f;
        w.f[2] = mat_fast_helper_a(ship->pos[0] - D_L07_001B90C0.pos[0], ship->pos[1] - D_L07_001B90C0.pos[1]);
        w.f[1] = mat_fast_helper_a(vec_distance_xy(&x, D_L07_001B90C0.pos), D_L07_001B90C0.pos[2] - x.f[2]);
        w.f[0] = D_L07_001B1758 * 0.017453294f;
        func_L07_00423B80(&w);

        moby_build_matrix(ship);

        spin = vars->f16B8 * 0.04363323748111725f + 0.008726648f;
        for (i = 0; i < 8; i++)
            *(float *)((u8 *)vars + 0x15B4 + i * 0x20) = FastAddRotations(*(float *)((u8 *)vars + 0x15B4 + i * 0x20), spin);

        FastVecSub(&y, ship->pos, &savedPos);
        mat_combine_and_store((u8 *)vars + 0x20, &y, &savedRot, ship->rot);
        break;
    }
}
