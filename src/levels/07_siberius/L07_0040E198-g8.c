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
extern s32 snd_resume_music_stream(void);
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

extern int g_ship_update_pending_flag __attribute__((sda));
extern int g_cutscene_l07_active_flag NOT_SDA;
extern int g_ship_update_done_flag;
extern u8 g_ship_flag_byte NOT_SDA;
extern u8 g_moby_update_inhibit_flag;
extern int g_current_map_index;
extern u8 g_moby_group_flags[][16];
extern void *g_platform_actor_ref[3] NOT_SDA;
extern float g_ship_fade_amount;
extern GameStatus g_music_state;
extern int g_ship_hit_flag NOT_SDA;
extern CameraObject g_hero_l07_state_block;
extern float g_hero_position_block[4];
extern float g_ship_fade_seconds_param __attribute__((sda));
extern float g_ship_approach_minutes_param __attribute__((sda));
extern float g_ship_roll_approach_rate __attribute__((sda));
extern float g_ship_roll_lerp_start __attribute__((sda));
extern float g_ship_angular_speed_deg __attribute__((sda));
extern float g_ship_velocity_z_param __attribute__((sda));
extern float g_ship_local_offset_vecs[2] __attribute__((sda));
/* Other code in this level reads a halfword at 0x1B2024; the int follows it. */
extern struct {
    s16 f0;
    s16 f2;
    int f4;
} D_L07_001B2024;

/* Main update for the Siberius ship objects (moby classes 4569 to 4573): starts them, runs the ride along the path, and plays the final crash sequence. */
void siberius_ship_update(ShipObject *ship)
{
    Vector saved_pos, saved_rot, v, w, x, y;
    ShipState *vars = ship->vars;
    float bounce_speed, spin, offset_x, fade_state;
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
        if (g_ship_update_pending_flag) {
            g_ship_update_pending_flag = 0;
            ship_start_second_phase(vars->f100, vars->fD0);
        }
        if (g_cutscene_l07_active_flag) {
            moby_set_state(ship, 1, -1);
            vars->f16CC = PlayMobySound(2, 4, ship);
            vars->f16C8 = 6.0f;
        }
        break;
    case 1:
        g_ship_flag_byte = 1;
        g_ship_update_done_flag = 1;
        ship_move_riders_along_path(ship);
        ship_run_sequence_events(ship);
        break;
    case 3:
        if (flag_set_first_pending(ship))
            PlayMobySound(1, 0, ship);
        ship_update_attached_parts(ship);
        if (g_moby_update_inhibit_flag || (g_moby_group_flags[g_current_map_index][ship->fB0] & 0x80)) {
            ship_update_attached_parts(ship);
            ship->flags |= 2;
            break;
        }
        if (g_platform_actor_ref[0] == ship) {
            if (vars->f110 >= 0.5f)
                PlayMobySound(1, 0, ship);
            math_approach_target_with_direction_mode(&vars->f110, &vars->f118, -1.0f, 0.0017453294713050127f,
                          0.0017453294713050127f, 0.10471977f, 0);
            if (vars->f110 <= -1.0f) {
                timer_start_countdown(1, 10.0f);
                if (g_ship_fade_amount >= 1.0f) {
                    saved_pos.q = 0;
                    saved_rot.q = 0;
                    saved_pos.f[0] = 191.5800018310547f;
                    saved_pos.f[1] = 501.15f;
                    saved_pos.f[2] = 457.69000244140625f;
                    saved_rot.f[2] = 3.1415927f;
                    load_scene_chunk(1, 0);
                    hero_reset_position_and_direction(&saved_pos, &saved_rot, 0, 1);
                }
            }
        } else {
            math_approach_target_with_direction_mode(&vars->f110, &vars->f118, 0.5f, 0.0017453294713050127f,
                          0.0017453294713050127f, 0.10471977f, 0);
        }
        break;
    case 5:
        if (vars->f16B8 >= 1.0f && g_ship_fade_amount >= 1.0f) {
            if (g_music_state.f72 != 3 || g_music_state.f6C >= 6000)
                break;
            g_ship_hit_flag = 0;
            snd_resume_music_stream();
        }
        saved_pos.q = *(TI128 *)ship->pos;
        saved_rot.q = *(TI128 *)ship->rot;
        if (vars->f16B8 > 0.0f) {
            math_step_value_toward_target(ship->pos, &vars->f11C, 400.0f, 0.0f, g_ship_approach_minutes_param * 0.00027777778f,
                          g_ship_fade_seconds_param * 0.016666668f);
            vars->f16B8 = (ship->pos[0] - 400.0f) * 0.014285714f;
            ship->rot[2] = math_lerp_float(g_ship_roll_lerp_start, 0.0f, vars->f16B8);
            ship->rot[0] = math_lerp_float(0.7853975296020508f, 0.0f, vars->f16B8);
            ship->pos[2] = 213.0f - vars->f16B8 * 3.0f;
        } else if ((fade_state = g_ship_fade_amount) == 0.0f) {
            matrix_mul_vec3(&v, g_ship_local_offset_vecs, ship->mtx);
            vars->f16B4 += ship->rot[0] * 7.272206130437553e-05f + 7.272206130437553e-05f;
            ship->rot[0] += vars->f16B4;
            if (ship->rot[0] > 1.5707964f) {
                ship->rot[0] = 1.5707964f;
                bounce_speed = math_fabs(vars->f16B4);
                if (bounce_speed < 0.0005817764904350042f)
                    timer_start_countdown(1, 15.0f);
                else
                    vars->f16B4 *= -0.333f;
                if (!vars->f16BC) {
                    g_hero_l07_state_block.f16C = 0;
                    g_hero_l07_state_block.f188 = 90;
                    g_hero_l07_state_block.f180 = 0.02f;
                    vars->f16BC = 1;
                }
            }
            euler_rotation_basis(ship->mtx, ship->rot);
            matrix_mul_vec3(&w, g_ship_local_offset_vecs, ship->mtx);
            FastVecSub(&v, &w, &v);
            FastVecSub(ship->pos, ship->pos, &v);
        } else if (fade_state >= 1.0f) {
            boss_enter_second_phase(ship);
            break;
        }

        g_ship_state_2.f4 = 1;
        ApproachValue(&vars->f16B0, 1.0f, g_ship_roll_approach_rate * 0.00027777778f);
        offset_x = vars->f11C + vars->f16B0;
        if (offset_x > 0.0f)
            offset_x = 0.0f;
        v.q = *(TI128 *)g_hero_position_block;
        v.f[0] += offset_x;
        v.f[2] += g_ship_velocity_z_param * 0.016666668f;
        func_L07_00423B28(&v);

        qzero_nc(&w);
        x.q = *(TI128 *)ship->pos;
        x.f[2] += 6.0f;
        w.f[2] = mat_fast_helper_a(ship->pos[0] - g_hero_l07_state_block.pos[0], ship->pos[1] - g_hero_l07_state_block.pos[1]);
        w.f[1] = mat_fast_helper_a(vec_distance_xy(&x, g_hero_l07_state_block.pos), g_hero_l07_state_block.pos[2] - x.f[2]);
        w.f[0] = g_ship_angular_speed_deg * 0.017453294f;
        func_L07_00423B80(&w);

        moby_build_matrix(ship);

        spin = vars->f16B8 * 0.04363323748111725f + 0.008726648f;
        for (i = 0; i < 8; i++)
            *(float *)((u8 *)vars + 0x15B4 + i * 0x20) = FastAddRotations(*(float *)((u8 *)vars + 0x15B4 + i * 0x20), spin);

        FastVecSub(&y, ship->pos, &saved_pos);
        mat_combine_and_store((u8 *)vars + 0x20, &y, &saved_rot, ship->rot);
        break;
    }
}
