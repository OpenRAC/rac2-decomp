#include "include_asm.h"

#include "common.h"

extern f32  g_fan_rotation_rate __attribute__((sda));
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern s32  func_31BA30(s32 a0, s32 a1);
extern s32  func_31B9F0(s32 a0);
extern f32  func_2F0000(f32 a0, f32 a1);

/* Gives a spinning object a random turn speed and direction when it starts, then keeps turning it at that rate. */
void fan_l03_update(char *moby)
{
    if (*(u8 *)(moby + 0x31) == 0) {
        return;
    }
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(u8 *)(moby + 0xBC) = (u8)func_31BA30(5, 10);
        if (func_31B9F0(2) != 0) {
            *(u8 *)(moby + 0xBC) += 15;
        }
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        *(f32 *)(moby + 0xF8) = func_2F0000(*(f32 *)(moby + 0xF8),
            g_fan_rotation_rate * 0.000290888245f * (f32)(*(u8 *)(moby + 0xBC) - 15));
        break;
    }
}

typedef int TI128 __attribute__((mode(TI)));

extern void moby_build_effect_packet(char *a0);
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void func_31B920(char *a0, s32 a1, s32 a2);
extern void func_2E77F0(void *fn, void *entity);
extern char *func_3113F0(s32 a0);
extern void func_32AA20(char *a0, char *a1);
extern f32  func_2EF670(f32 a0, f32 a1);
extern f32  func_2EF110(f32 *a0);

extern f32 g_fan_float_table[] SDATA(D_L03_001B0350);
extern f32 g_trail_projectile_scale __attribute__((sda));

/* case 0 makes the object opaque and moves it to state 1; case 1 scrolls the three
   offsets in its vars by the table's rates per frame (wrapping below -1) and queues
   its draw callback with the object as argument (AddDrawCallback in rac1-decomp) */
/* Slowly scrolls the texture of an object so it looks like moving water or energy. */
void UpdateThreeScrollOffsets(char *moby)
{
    s32 state = *(u8 *)(moby + 0x20);
    char *vars = *(char **)(moby + 0x68);

    switch (state) {
    case 0:
        *(u8 *)(moby + 0x30) = 0xFF;
        func_31B920(moby, 1, -1);
        *(s32 *)(vars + 0xC) = 1;
        break;
    case 1: {
        f32 *dst = (f32 *)vars;
        f32 *src = &g_fan_float_table[0];
        s32 i;

        for (i = 2; i >= 0; i--) {
            f32 scrolled = *dst - *src * 0.016666668f;

            *dst = scrolled;
            if (scrolled < -1.0f)
                *dst = scrolled + 1.0f;
            src++;
            dst++;
        }
        func_2E77F0(moby_build_effect_packet, moby);
        break;
    }
    }
}

/* spawns the actor and seeds its aim from the caller's vector */
/* func_L03_003D18F8 is defined in L03_003D18F8-g8.c. */

/* The object the level's state points at: the retail writes six floats, a run
   of bytes and shorts, and two counters into it. */
typedef struct {
    f32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    f32 f10;
    f32 f14;
    u8  b18;
    u8  b19;
    u16 h1A;
    u16 pad1C;
    u8  b1E;
    u8  b1F;
    u8  pad20[0x10];
    u16 h30;
    u16 h32;
    s32 i34;
} L03_003D21F8_Obj;

/* The object pointer is small data (the retail reaches it through $gp in
   ordinary flow, not only in a delay slot), the state word is not: the retail
   reads it with an absolute lui/%lo pair and clears it from a delay slot. */
extern L03_003D21F8_Obj *g_camera_override_slot __attribute__((sda));
extern u32 g_shared_record_pending;
extern void *cam_alloc_override_slot(s32 size);

extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(char *a0, char *a1, char *a2);
extern void matrix_from_basis_rows(char *a0, char *a1);
extern s32  flag_is_third_pending_set(char *a0);
extern s32  PlayMobySound(s32 a0, s32 a1, char *a2);
extern void snd_stop_voice(s32 a0);
extern void moby_set_state_in_list(int a0, int a1);
extern u8  *g_moby_record_base;
extern u8   g_sound_state[];
extern s32  g_ant_bridge_divisor __attribute__((sda));
extern f32  g_ant_bridge_angle_limit __attribute__((sda));

/* The actor's per-frame update: state 0 spawns it and aims, state 2 looks the
   target up, states 3 and 4 turn it by a rate that decays; every other state
   does nothing.  The actor's angle is at 0xF4, its rate at 0x74 of the state. */
/* Swings an object around a pivot until it reaches an end stop, bounces back with less force each time, and plays a sound on each hit. */
void ant_bridge_update(char *moby)
{
    char *self = moby;
    char *vars = *(char **)(self + 0x68);
    char buf[0x40];
    char *offset;

    switch (*(u8 *)(self + 0x20)) {
    case 0:
        if (*(s32 *)(vars + 0x70) != -1) {
            moby_set_state(self, 2, -1);
            offset = vars + 0x60;
            FastVecSub(offset, g_moby_record_base + *(s32 *)(vars + 0x70) * 0x100 + 0x10, self + 0x10);
            *(s32 *)(vars + 0x7C) = -1;
            *(s32 *)(vars + 0x78) = 0;
            matrix_from_basis_rows(buf, self + 0xC0);
            matrix_mul_vec3(offset, offset, buf);
        } else {
            moby_set_state(self, 1, -1);
        }
        break;
    case 2: {
        char *sound_slot;

        if (flag_is_third_pending_set(g_moby_record_base + *(s32 *)(vars + 0x70) * 0x100) == 0) {
            break;
        }
        sound_slot = g_sound_state + *(s32 *)(vars + 0x7C) * 0x70;
        if (*(char **)(sound_slot + 0x88) != self || *(u8 *)(sound_slot + 0x74) == 0) {
            *(s32 *)(vars + 0x7C) = PlayMobySound(0, 4, self);
        }
        moby_set_state_in_list(*(u8 *)(self + 0x21), 4);
        moby_set_state(self, 3, -1);
        break;
    }
    case 3: {
        char *sound_slot;
        char *anchor_pos;
        f32 angle;
        f32 rate;

        *(f32 *)(vars + 0x74) = *(f32 *)(vars + 0x74)
            + (*(f32 *)(self + 0xF4) / (f32)g_ant_bridge_divisor + 9.69627508e-05f);
        angle = *(f32 *)(self + 0xF4) + *(f32 *)(vars + 0x74);
        *(f32 *)(self + 0xF4) = angle;
        if (1.69646013f < angle) {
            if (*(s32 *)(vars + 0x78) < 5) {
                if (*(s32 *)(vars + 0x7C) != -1) {
                    sound_slot = g_sound_state + *(s32 *)(vars + 0x7C) * 0x70;
                    if (*(char **)(sound_slot + 0x88) == self && *(u8 *)(sound_slot + 0x74) != 0) {
                        snd_stop_voice(*(s32 *)(vars + 0x7C));
                    }
                }
                *(s32 *)(vars + 0x7C) = -1;
                PlayMobySound(1, 0, self);
                (*(s32 *)(vars + 0x78))++;
            }
            *(f32 *)(self + 0xF4) = 1.69646013f;
            rate = *(f32 *)(vars + 0x74);
            if (0.00058177649f < rate) {
                *(f32 *)(vars + 0x74) = rate * -0.5f;
            } else {
                *(s32 *)(vars + 0x74) = 0;    /* the retail stores the word, not the float */
                moby_set_state(self, 5, -1);
            }
        }
        anchor_pos = g_moby_record_base + *(s32 *)(vars + 0x70) * 0x100 + 0x10;
        matrix_mul_vec3(anchor_pos, vars + 0x60, self + 0xC0);
        FastVecAdd(anchor_pos, anchor_pos, self + 0x10);
        break;
    }
    case 4: {
        f32 limit;
        f32 angle;
        f32 rate;

        limit = g_ant_bridge_angle_limit * 3.14159274f;
        *(f32 *)(vars + 0x74) = *(f32 *)(vars + 0x74)
            + (*(f32 *)(self + 0xF4) / (f32)g_ant_bridge_divisor + 9.69627508e-05f);
        angle = *(f32 *)(self + 0xF4) + *(f32 *)(vars + 0x74);
        *(f32 *)(self + 0xF4) = angle;
        if (limit < angle) {
            *(f32 *)(self + 0xF4) = limit;
            rate = *(f32 *)(vars + 0x74);
            if (0.00058177649f < rate) {
                *(f32 *)(vars + 0x74) = rate * -0.5f;
            } else {
                *(s32 *)(vars + 0x74) = 0;    /* the retail stores the word, not the float */
                moby_set_state(self, 5, -1);
            }
        }
        break;
    }
    }
}

/* case 0 spawns the object and points the actor at it; case 1 clears the
   object while the state word still reads zero, and clears the word otherwise */
/* Sets up the level's shared record when it starts and later resets all its values to unused. */
void shared_record_reset_update(char *moby)
{
    char *self = moby;

    switch (*(u8 *)(self + 0x20)) {
    case 0:
        g_camera_override_slot = cam_alloc_override_slot(4);
        moby_set_state(self, 1, -1);
        *(u8 *)(self + 0x30) = 0xFF;
        break;
    case 1: {
        u32 pending = g_shared_record_pending;

        if (pending == 0) {
            g_camera_override_slot->f00 = -1.0f;
            g_camera_override_slot->f04 = -1.0f;
            g_camera_override_slot->f08 = -1.0f;
            g_camera_override_slot->f0C = -1.0f;
            g_camera_override_slot->f10 = -1.0f;
            g_camera_override_slot->f14 = -1.0f;
            g_camera_override_slot->b18 = 0;
            g_camera_override_slot->b19 = 0;
            g_camera_override_slot->h1A = 0;
            g_camera_override_slot->b1E = 0;
            g_camera_override_slot->b1F = 0;
            g_camera_override_slot->h30 = 0;
            g_camera_override_slot->i34 = 6;
            g_camera_override_slot->h32 = 120;
        } else {
            g_shared_record_pending = 0;
        }
        break;
    }
    }
}

extern s32  g_camera_trigger_active __attribute__((sda));
extern char g_hero_position[];
extern char g_camera_pose_buffer[];

typedef struct {
    s32 index;
    u8 pad04[0x14];
    f32 f18;
    f32 f1C;
    f32 f20;
} L03_22C8State;

typedef struct {
    u32 field00;
    u8 pad04[0xC];
} L03_22C8Entry;

extern L03_22C8Entry *g_path_l03_entry_table[];
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void moby_mark_spawned(char *a0);
extern s32  point_in_path_xy(char *a0, void *a1, u32 a2);
extern void SetCamera5Pose(char *a0, char *a1, s32 a2, s32 a3, s32 a4);
extern void cam_compute_aim_and_angles(char *a0, f32 *a1, f32 *a2);
extern void FastVecSub(void *, void *, void *);
extern f32  FastVecLength(f32 *a0);
extern void math_approach_target_with_braking(f32 *a0, f32 a1, f32 a2, f32 a3, f32 a4);
extern void vec_scale_to_length(f32 *a0, f32 *a1, f32 a2);
extern void FastVecAdd(void *, void *, void *);
extern void object_copy_vector_to_selected(char *a0);
extern f32 math_approach_target_with_direction_mode(char *a0, f32 *a1, f32 a3, f32 a4, f32 a5, f32 a6, s32 a2);
extern void cam_set_state_rotation(char *a0);
extern void cam_set_mode_state(s32 a0);

/* Takes over the camera while the hero is inside a trigger area, easing it toward a set view, and gives it back when the hero leaves. */
void camera_trigger_area_update(char *moby)
{
    L03_22C8State *vars = *(L03_22C8State **)(moby + 0x68);
    f32 target_pos[4] __attribute__((aligned(16)));
    f32 target_angles[4] __attribute__((aligned(16)));
    f32 offset[4] __attribute__((aligned(16)));
    f32 follow_rate;
    f32 len;
    f32 one;
    f32 turn_rate;

    if (g_camera_trigger_active != 0) {
        return;
    }
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        moby_set_state(moby, 1, -1);
        if (vars->index == -1) {
            moby_mark_spawned(moby);
        }
        break;
    case 1:
        if (point_in_path_xy(g_hero_position, ((u8 *)g_path_l03_entry_table[vars->index] + 0x10), g_path_l03_entry_table[vars->index]->field00) != 0) {
            SetCamera5Pose(g_camera_pose_buffer, g_camera_pose_buffer + 0x10, 1, 0, 0);
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        follow_rate = 0.0027777778450399637f;
        cam_compute_aim_and_angles(moby, target_pos, target_angles);
        one = 1.0f;
        FastVecSub(offset, target_pos, g_camera_pose_buffer);
        turn_rate = 0.0008726647356525064f;
        len = FastVecLength(offset);
        math_approach_target_with_braking(&vars->f18, len, follow_rate, follow_rate, one);
        vec_scale_to_length(offset, offset, vars->f18);
        FastVecAdd(g_camera_pose_buffer, offset, g_camera_pose_buffer);
        object_copy_vector_to_selected(g_camera_pose_buffer);
        math_approach_target_with_direction_mode(g_camera_pose_buffer + 0x14, &vars->f1C, target_angles[1], turn_rate, turn_rate, one, 0);
        math_approach_target_with_direction_mode(g_camera_pose_buffer + 0x18, &vars->f20, target_angles[2], turn_rate, turn_rate, one, 0);
        cam_set_state_rotation(g_camera_pose_buffer + 0x10);
        if (point_in_path_xy(g_hero_position, ((u8 *)g_path_l03_entry_table[vars->index] + 0x10), g_path_l03_entry_table[vars->index]->field00) == 0) {
            cam_set_mode_state(1);
            moby_set_state(moby, 1, -1);
        }
        break;
    }
}
