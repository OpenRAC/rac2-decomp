#include "include_asm.h"

#include "common.h"
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
extern void ship_start_chain_pal(void *);
extern void ship_start_second_phase_pal(void *, int);
extern void ship_move_riders_along_path_pal(void *);
extern void ship_run_sequence_events_pal(void *);
extern void ship_update_attached_parts_pal(void *);
extern void boss_enter_second_phase_pal(void *);
extern void moby_build_matrix(void *);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern void moby_set_state(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern int flag_set_first_pending(void *);
extern float math_approach_target_with_direction_mode(void *, void *, float, float, float, float, int);
extern void timer_start_countdown(int, float);
extern void load_scene_chunk_pal(int, int);
extern void hero_reset_position_and_direction_pal(void *, void *, int, int);
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
extern struct {
    s16 f0;
    s16 f2;
    int f4;
} D_L07_001B2024;

/* Main update for the Siberius ship objects (moby classes 4569 to 4573): starts them, runs the ride along the path, and plays the final crash sequence (PAL: 50 Hz timings). */
void siberius_ship_update_pal(ShipObject *moby)
{
    Vector position, rotation, offset, aim_rotation, aim_position, delta;
    ShipState *vars = moby->vars;
    float bounce_speed, wheel_spin, camera_shift, fade_amount;
    int i;

    if (!vars)
        return;

    switch (moby->state) {
    case 0:
        moby->flags |= 1;
        moby->f31 = 0;
        path_compute_centers_and_radii(moby);
        vars->f1AC = -1;
        if (vars->f90 == -1) {
            if (moby->classId == 0x11D9)
                moby_set_state(moby, 3, -1);
            else
                moby_set_state(moby, 4, -1);
        } else {
            moby->f30 = 255;
            flag_block_clear(moby);
            ship_start_chain_pal(moby);
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (g_ship_update_pending_flag) {
            g_ship_update_pending_flag = 0;
            ship_start_second_phase_pal(vars->f100, vars->fD0);
        }
        if (g_cutscene_l07_active_flag) {
            moby_set_state(moby, 1, -1);
            vars->f16CC = PlayMobySound(2, 4, moby);
            vars->f16C8 = 6.0f;
        }
        break;
    case 1:
        g_ship_flag_byte = 1;
        g_ship_update_done_flag = 1;
        ship_move_riders_along_path_pal(moby);
        ship_run_sequence_events_pal(moby);
        break;
    case 3:
        if (flag_set_first_pending(moby))
            PlayMobySound(1, 0, moby);
        ship_update_attached_parts_pal(moby);
        if (g_moby_update_inhibit_flag || (g_moby_group_flags[g_current_map_index][moby->fB0] & 0x80)) {
            ship_update_attached_parts_pal(moby);
            moby->flags |= 2;
            break;
        }
        if (g_platform_actor_ref[0] == moby) {
            if (vars->f110 >= 0.5f)
                PlayMobySound(1, 0, moby);
            math_approach_target_with_direction_mode(&vars->f110, &vars->f118, -1.0f, 0.0025132746f,
                          0.0025132746f, 0.12566373f, 0);
            if (vars->f110 <= -1.0f) {
                timer_start_countdown(1, 8.0f);
                if (g_ship_fade_amount >= 1.0f) {
                    position.q = 0;
                    rotation.q = 0;
                    position.f[0] = 191.5800018310547f;
                    position.f[1] = 501.15f;
                    position.f[2] = 457.69000244140625f;
                    rotation.f[2] = 3.1415927f;
                    load_scene_chunk_pal(1, 0);
                    hero_reset_position_and_direction_pal(&position, &rotation, 0, 1);
                }
            }
        } else {
            math_approach_target_with_direction_mode(&vars->f110, &vars->f118, 0.5f, 0.0025132746f,
                          0.0025132746f, 0.12566373f, 0);
        }
        break;
    case 5:
        if (vars->f16B8 >= 1.0f && g_ship_fade_amount >= 1.0f) {
            if (g_music_state.f72 != 3 || g_music_state.f6C >= 6000)
                break;
            g_ship_hit_flag = 0;
            snd_resume_music_stream();
        }
        position.q = *(TI128 *)moby->pos;
        rotation.q = *(TI128 *)moby->rot;
        if (vars->f16B8 > 0.0f) {
            math_step_value_toward_target(moby->pos, &vars->f11C, 400.0f, 0.0f, g_ship_approach_minutes_param * 0.00040000002f,
                          g_ship_fade_seconds_param * 0.020000001f);
            vars->f16B8 = (moby->pos[0] - 400.0f) * 0.014285714f;
            moby->rot[2] = math_lerp_float(g_ship_roll_lerp_start, 0.0f, vars->f16B8);
            moby->rot[0] = math_lerp_float(0.7853975296020508f, 0.0f, vars->f16B8);
            moby->pos[2] = 213.0f - vars->f16B8 * 3.0f;
        } else if ((fade_amount = g_ship_fade_amount) == 0.0f) {
            matrix_mul_vec3(&offset, g_ship_local_offset_vecs, moby->mtx);
            vars->f16B4 += moby->rot[0] * 0.00010471977f + 0.00010471977f;
            moby->rot[0] += vars->f16B4;
            if (moby->rot[0] > 1.5707964f) {
                moby->rot[0] = 1.5707964f;
                bounce_speed = math_fabs(vars->f16B4);
                if (bounce_speed < 0.0006981318f)
                    timer_start_countdown(1, 12.0f);
                else
                    vars->f16B4 *= -0.333f;
                if (!vars->f16BC) {
                    g_hero_l07_state_block.f16C = 0;
                    g_hero_l07_state_block.f188 = 75;
                    g_hero_l07_state_block.f180 = 0.02f;
                    vars->f16BC = 1;
                }
            }
            euler_rotation_basis(moby->mtx, moby->rot);
            matrix_mul_vec3(&aim_rotation, g_ship_local_offset_vecs, moby->mtx);
            FastVecSub(&offset, &aim_rotation, &offset);
            FastVecSub(moby->pos, moby->pos, &offset);
        } else if (fade_amount >= 1.0f) {
            boss_enter_second_phase_pal(moby);
            break;
        }

        g_ship_state_2.f4 = 1;
        ApproachValue(&vars->f16B0, 1.0f, g_ship_roll_approach_rate * 0.00040000002f);
        camera_shift = vars->f11C + vars->f16B0;
        if (camera_shift > 0.0f)
            camera_shift = 0.0f;
        offset.q = *(TI128 *)g_hero_position_block;
        offset.f[0] += camera_shift;
        offset.f[2] += g_ship_velocity_z_param * 0.020000001f;
        object_copy_vector_to_selected(&offset);

        qzero_nc(&aim_rotation);
        aim_position.q = *(TI128 *)moby->pos;
        aim_position.f[2] += 6.0f;
        aim_rotation.f[2] = mat_fast_helper_a(moby->pos[0] - g_hero_l07_state_block.pos[0], moby->pos[1] - g_hero_l07_state_block.pos[1]);
        aim_rotation.f[1] = mat_fast_helper_a(vec_distance_xy(&aim_position, g_hero_l07_state_block.pos), g_hero_l07_state_block.pos[2] - aim_position.f[2]);
        aim_rotation.f[0] = g_ship_angular_speed_deg * 0.017453294f;
        cam_set_state_rotation(&aim_rotation);

        moby_build_matrix(moby);

        wheel_spin = vars->f16B8 * 0.052359886f + 0.010471977f;
        for (i = 0; i < 8; i++)
            *(float *)((u8 *)vars + 0x15B4 + i * 0x20) = FastAddRotations(*(float *)((u8 *)vars + 0x15B4 + i * 0x20), wheel_spin);

        FastVecSub(&delta, moby->pos, &position);
        mat_combine_and_store((u8 *)vars + 0x20, &delta, &rotation, moby->rot);
        break;
    }
}
