#include "common.h"


#include "common.h"

/* func_L23_004402D8 is a unit of its own: it reads $gp (hence -g8), and it is built with -g,
   whose line labels make the assembler pad its two divisions with two nops each, as retail
   has them (the same effect as func_L23_003BF9B0). Each division stays on a line of its own.
   The structs are partial layouts measured from this function.
   Measured on this body:
   - the plain (unmarked) externs D_L22_001B1AC4, D_L22_001A8FF0, D_001A79F0 and D_L22_001B1CCC
     come out absolute (`lui`+op) outside delay slots and $gp-relative inside them, as retail;
     the floats marked sda are $gp-relative everywhere;
   - the entry address is an integer sum with the scaled index first, which gives retail's
     `addu $a2,$v1,$v0` (a pointer sum puts the table first);
   - the slot scan is a do-while: with a for loop, cc1 rolls the `< 0` break to the bottom and
     duplicates it before the loop;
   - each pair of interpolated values is computed before the two calls that take them;
   - the block that ends in `return` is written inside the loop: cc1 itself moves it behind
     the last clamp, where retail has it. */

typedef struct Vars_004402D8 {
    u8 pad00[0x20];
    s32 f20; /* 0x20 */
    f32 f24; /* 0x24 */
    s32 f28[6]; /* 0x28 */
    f32 f40; /* 0x40 */
    f32 f44; /* 0x44 */
    f32 f48; /* 0x48 */
    f32 f4C; /* 0x4C */
    s32 f50; /* 0x50 */
} Vars_004402D8;

typedef struct Entry_004402D8 {
    f32 x; /* 0x00 */
    f32 y; /* 0x04 */
    f32 z; /* 0x08 */
    u8 pad0C[0x10];
    Vars_004402D8 *vars; /* 0x1C */
} Entry_004402D8;

typedef struct Moby_004402D8 {
    u8 pad00[0x84];
    s16 f84; /* 0x84 */
} Moby_004402D8;

typedef struct Player_004402D8 {
    u8 pad000[0x80];
    f32 f80[4]; /* 0x080 */
    u8 pad090[0x20];
    f32 fB0[4]; /* 0x0B0 */
    u8 pad0C0[0xB0];
    f32 f170; /* 0x170 */
    u8 pad174[0x32A];
    u8 f49E; /* 0x49E */
    u8 pad49F[0x81];
    f32 f520; /* 0x520 */
    u8 pad524[0xF30];
    s16 f1454; /* 0x1454 */
    u8 pad1456[0xE3A];
    u8 *f2290; /* 0x2290 */
    s32 f2294; /* 0x2294 */
    u8 pad2298[0x4];
    s32 f229C; /* 0x229C */
    u8 pad22A0[0x14];
    u8 f22B4; /* 0x22B4 */
} Player_004402D8;

typedef struct Pad_004402D8 {
    u8 pad000[0x100];
    f32 f100; /* 0x100 */
    f32 f104; /* 0x104 */
} Pad_004402D8;

typedef struct CamSub_004402D8 {
    u8 pad000[0x250];
    s32 f250; /* 0x250 */
} CamSub_004402D8;

typedef struct Cam_004402D8 {
    u8 pad00[0x70];
    CamSub_004402D8 *f70; /* 0x70 */
    u8 pad74[0x12];
    s16 f86; /* 0x86 */
} Cam_004402D8;

typedef struct CamMgr_004402D8 {
    u8 pad000[0x140];
    f32 f140[4]; /* 0x140 */
    u8 pad150[0x40];
    Cam_004402D8 *cam; /* 0x190 */
} CamMgr_004402D8;

extern Entry_004402D8 *D_L22_001B1AC4;

extern s32 D_L22_001A8FF0;

extern s32 g_current_map_index;

extern s32 D_0018C0B4 __attribute__((nosda));

extern Player_004402D8 g_hero_state;

extern Pad_004402D8 g_pad_state;

extern CamMgr_004402D8 D_L22_001B9B40;

extern s32 D_L22_001B1CCC;

extern f32 D_L22_001B16BC __attribute__((sda));

extern f32 D_L22_001B183C __attribute__((sda));

extern f32 D_L22_001B1844 __attribute__((sda));

extern f32 D_L22_001B1848 __attribute__((sda));

extern f32 D_L22_001B184C __attribute__((sda));

extern f32 D_L22_001B1850 __attribute__((sda));

extern f32 D_L22_001B1854 __attribute__((sda));

extern f32 D_L22_001B1858 __attribute__((sda));

extern f32 D_L22_001B185C __attribute__((sda));

extern f32 D_L22_001B1860 __attribute__((sda));

extern f32 D_L22_001B1864 __attribute__((sda));

extern f32 D_L22_001B1868 __attribute__((sda));

extern f32 D_L22_001B186C __attribute__((sda));

extern f32 D_L22_001B1870 __attribute__((sda));

extern f32 fast_vec_dist(void *, void *);

extern f32 gravity_get_center_distance(void *);

extern s32 cam_release_request_slot(void *);

extern s32 cam_claim_request_slot(void *);

extern s32 IsPointInCuboid(void *, s32);

extern f32 math_fabs(f32);

extern void cam_set_snap_flag(void);

extern void set_follow_camera_orbit_clamp_mode(s32);

extern void cam_set_lock_flag(void);

extern void cam_set_speeds_if_nonzero(f32, f32);

extern s32 math_fast_float_d(void *);

extern void cam_set_strength_and_steer(void *, f32, f32);

extern f32 hero_find_collision_time(f32, f32, f32);

extern s32 FloatToInt(f32);

extern void cam_set_turn_speeds_if_nonzero(f32, f32);

extern void moby_push_axis_to_linked_node(f32, f32);

extern void cam_set_aim_offset_target(s32, f32, f32);

extern void follow_camera_set_distance(s32, f32, f32);

extern void follow_camera_set_height(f32, f32);

extern void cam_set_tuning_value(f32);


/* Same body as func_L23_004402D8, with this function's own callees. */
/* Controls the camera and player while on this ride: picks camera distance, height and speed settings from the player state and distance travelled. */
void ride_update_camera_control(Moby_004402D8 *moby)
{
    Entry_004402D8 *entry = (Entry_004402D8 *)(moby->f84 * 32 + (s32)D_L22_001B1AC4);
    Vars_004402D8 *vars = entry->vars;
    s32 i;

    if (vars->f20 == 0) {
        if (D_L22_001A8FF0 != 0 || (g_current_map_index == 16 && D_0018C0B4 == 0x81)) {
            f32 tmp[4];

            tmp[0] = entry->x;
            tmp[1] = entry->y;
            tmp[2] = entry->z;
            tmp[3] = 0.0f;
            vars->f24 = fast_vec_dist(tmp, g_hero_state.fB0);
            vars->f20 = 1;
        }
        return;
    }
    if (D_L22_001B9B40.cam->f86 != 0
        || (D_L22_001A8FF0 == 0 && (g_current_map_index != 16 || D_0018C0B4 != 0x81))) {
        if (D_L22_001B1870 < gravity_get_center_distance(D_L22_001B9B40.f140)) {
            D_L22_001B1CCC = 3;
        } else {
            D_L22_001B1CCC = 0;
        }
        cam_release_request_slot(moby);
        return;
    }
    if (cam_claim_request_slot(moby) <= 0) {
        return;
    }
    i = 0;
    do {
        if (vars->f28[i] < 0) {
            break;
        }
        if (IsPointInCuboid(g_hero_state.f80, vars->f28[i]) != 0) {
            cam_set_turn_speeds_if_nonzero(0.04f, 0.2f);
            follow_camera_set_distance(0, vars->f40, 0.003f);
            follow_camera_set_height(vars->f44, 0.003f);
            return;
        }
        i++;
    } while (i < 6);
    if (g_hero_state.f22B4 == 2) {
        if (g_hero_state.f1454 != 0 || g_hero_state.f2294 == 0x5B
            || math_fabs(g_pad_state.f100) >= 0.3f || math_fabs(g_pad_state.f104) >= 0.3f) {
            cam_set_snap_flag();
            set_follow_camera_orbit_clamp_mode(0);
        }
    } else {
        cam_set_snap_flag();
        set_follow_camera_orbit_clamp_mode(0);
    }
    cam_set_lock_flag();
    cam_set_speeds_if_nonzero(D_L22_001B1844, 0.2f);
    if (math_fast_float_d(&vars->f50) != 0 && !(g_hero_state.f170 > 0.005f)) {
        cam_set_strength_and_steer(g_hero_state.f2290 + 0xC0, 0.0052359886f, 0.0f);
    }
    if (math_fabs(g_pad_state.f100) >= 0.3f || math_fabs(g_pad_state.f104) >= 0.3f) {
        vars->f50 = 300;
    }
    if (g_hero_state.f22B4 == 2) {
        s32 n;

        D_L22_001B9B40.cam->f70->f250 = 2;
        n = 0;
        if (g_hero_state.f49E != 0) {
            n = FloatToInt(hero_find_collision_time(90.0f, g_hero_state.f520, -1.0f));
        }
        if (g_hero_state.f2294 == 0x5B && (g_hero_state.f49E == 0 || n >= 20)) {
            cam_set_speeds_if_nonzero(0.5f, 1.0f);
            cam_set_turn_speeds_if_nonzero(0.05f, 0.2f);
            moby_push_axis_to_linked_node(0.04f, 0.0f);
            cam_set_aim_offset_target(0, D_L22_001B1864, 0.005f);
            follow_camera_set_distance(1, D_L22_001B1858, 0.01f);
            follow_camera_set_height(D_L22_001B185C, 0.01f);
            D_L22_001B16BC = D_L22_001B186C * 0.017453294f;
            cam_set_tuning_value(D_L22_001B1868 * 0.017453294f);
        } else {
            f32 d;
            f32 t;
            f32 a;
            f32 b;

            cam_set_aim_offset_target(0, D_L22_001B1860, 0.03f);
            if (g_hero_state.f229C == 2) {
                cam_set_turn_speeds_if_nonzero(0.04f, 0.2f);
            } else {
                cam_set_turn_speeds_if_nonzero(0.015f, 0.2f);
            }
            d = fast_vec_dist(g_hero_state.f80, g_hero_state.fB0) - vars->f24;
            if (D_L22_001B183C < d) {
                d = D_L22_001B183C;
            } else if (d < 0.0f) {
                d = 0.0f;
            }
            t = d / D_L22_001B183C;
            a = (D_L22_001B1850 - D_L22_001B1848) * t + D_L22_001B1848;
            b = (D_L22_001B1854 - D_L22_001B184C) * t + D_L22_001B184C;
            follow_camera_set_distance(1, a, 0.005f);
            follow_camera_set_height(b, 0.005f);
        }
        if (D_L22_001B1870 < gravity_get_center_distance(D_L22_001B9B40.f140)) {
            D_L22_001B1CCC = 3;
        } else {
            D_L22_001B1CCC = 0;
        }
    } else if (g_hero_state.f2294 == 0x81) {
        cam_set_turn_speeds_if_nonzero(0.05f, 0.2f);
        moby_push_axis_to_linked_node(0.04f, 0.0f);
        if (g_current_map_index == 16) {
            cam_set_aim_offset_target(0, 0.5f, 0.04f);
            follow_camera_set_distance(0, 4.0f, 0.002f);
            follow_camera_set_height(2.0f, 0.04f);
        } else {
            cam_set_aim_offset_target(0, 1.0f, 0.04f);
            follow_camera_set_distance(0, 2.0f, 0.002f);
            follow_camera_set_height(7.0f, 0.04f);
        }
    } else {
        if (g_hero_state.f229C == 2) {
            cam_set_turn_speeds_if_nonzero(0.04f, 0.2f);
        } else {
            cam_set_turn_speeds_if_nonzero(0.015f, 0.2f);
        }
        if (g_hero_state.f229C == 5) {
            follow_camera_set_distance(0, 4.0f, 0.003f);
            follow_camera_set_height(6.0f, 0.003f);
        } else {
            f32 d;
            f32 t;
            f32 a;
            f32 b;

            d = fast_vec_dist(g_hero_state.f80, g_hero_state.fB0) - vars->f24;
            if (D_L22_001B183C < d) {
                d = D_L22_001B183C;
            } else if (d < 0.0f) {
                d = 0.0f;
            }
            t = d / D_L22_001B183C;
            a = (vars->f48 - vars->f40) * t + vars->f40;
            b = (vars->f4C - vars->f44) * t + vars->f44;
            follow_camera_set_distance(0, a, 0.003f);
            follow_camera_set_height(b, 0.003f);
        }
    }
}
