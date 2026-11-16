#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef int TI16 __attribute__((mode(TI)));
extern void moby_set_state(void *, s32, s32);
extern s32 snd_start_in_slot(s32, s32, s32);
extern void moby_mark_spawned(u8 *object);
typedef struct {
    u8 pad0[0x18];
    u8 b18;
    u8 b19;
    u16 id;
    u8 pad1C[0x14];
} L23Probe;
typedef struct {
    u8 pad0[0x80];
    u8 camera[0x10];
    u8 pad90[0x2290 - 0x90];
    u8 *player;
} L23Game;
typedef struct {
    u8 pad0[0x18];
    u8 *hit;
    u8 pad1C[4];
    float point[4];
} L23RayHit;
typedef struct {
    float dir[4];
    u8 pad10[4];
    float radius;
    u8 pad18[0xC];
    s32 frames;
    u8 pad28[8];
    float vel[4];
} L23Flight;
extern L23Game D_00189E20_2;
extern L23RayHit g_last_ray_hit;
extern float g_player_target_point[4] __attribute__((sda));
extern float g_flying_shot_vel_max_a __attribute__((sda));
extern float g_flying_shot_vel_step_a __attribute__((sda));
extern float g_flying_shot_vel_max_d __attribute__((sda));
extern float g_flying_shot_vel_step_d __attribute__((sda));
extern float g_flying_shot_vel_max_b __attribute__((sda));
extern float g_flying_shot_vel_step_b __attribute__((sda));
extern float g_flying_shot_vel_max_c __attribute__((sda));
extern float g_flying_shot_vel_step_c __attribute__((sda));
extern float g_flying_shot_spin_degrees __attribute__((sda));
extern float g_flying_shot_hit_distance __attribute__((sda));
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_clear_128(void *);
extern float fast_vec_dist(void *, void *);
extern void make_hit_descriptor(void *, u8 *, s32, void *, float);
extern s32 CollLine(void *, void *, s32, void *, s32);
extern void *SpawnExplosion(void *, s32, s32, s32, s32, s32, s32, s32, float, float, s32, s32, s32, s32);
extern char *part_create_flash(void *, s32, s32, s32, s32, s32, s32, s32, float, s32, s32);
extern void cam_play_effect_on_target(u8 *, s32, s32, void *, s32, s32);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void gfx_add_draw_callback_third(void *, void *);
extern void blast_projectile_draw_glow(u8 *);

/* per-frame update of the object whose state at +0x68 holds a direction vector, a frame counter
   and a clamped velocity: it ends the object after 0xF0 frames; in state 0 it casts a ray along
   the direction and, on a hit, spawns the hit effects (the first arm when the player is struck
   or the hit is near, else a second probe) and leaves, otherwise it moves the object; state 1
   spawns the burst and removes it. It then integrates the velocity, turns two matrix rows and
   registers the next update. */
void flying_l23_shot_update_pal(u8 *moby) {
    L23Flight *vars = *(L23Flight **)(moby + 0x68);
    TI16 target[1];
    L23Probe hit_desc_1;
    TI16 vec_a[1];
    TI16 vec_b[1];
    L23Probe hit_desc_2;

    if (moby[0xBC] == 0) {
        vars->frames += 1;
        if (vars->frames > 0xF0) {
            if (moby[0xBC] == 0) {
                moby_set_state(moby, 1, -1);
            }
        }
        switch (moby[0x20]) {
        case 0: {
            FastVecAdd(target, moby + 0x10, vars);
            make_hit_descriptor(&hit_desc_1, moby, 0x90003, vars, vars->radius);
            hit_desc_1.id = *(u16 *)(moby + 0xAA);
            if (CollLine(moby + 0x10, target, 0, moby, 0) != 0) {
                float dist = fast_vec_dist(g_player_target_point, g_last_ray_hit.point);
                u8 *player = D_00189E20_2.player;
                s32 is_player = g_last_ray_hit.hit == player;

                if (is_player || dist < g_flying_shot_hit_distance) {
                    TI16 origin;
                    s32 radius;

                    FastVecScale(vec_a, player + 0xE0, 3.5f);
                    FastVecAdd(vec_a, vec_a, D_00189E20_2.camera);
                    SpawnExplosion(vec_a, 1, 5, 5, 5, 0x19, 0x4B, 0, 1.5f, 20.0f, 0, 1, 0, 0);
                    radius = (s32)vars->radius;
                    origin = *(TI16 *)(moby + 0x10);
                    vec_b[0] = origin;
                    cam_play_effect_on_target(moby, 0x10007, radius, vec_b, 0, 0);
                    if (is_player) {
                        snd_start_in_slot(0x20, 0, 0);
                    }
                    if (moby[0xBC] == 0) {
                        moby_set_state(moby, 1, -1);
                    }
                } else {
                    vec_a[0] = *(TI16 *)vars;
                    FastVecScale(vec_a, vec_a, 3.0f);
                    ((float *)vec_a)[2] = 1.0f;
                    ((float *)vec_a)[3] = 5627.9248046875f;
                    make_hit_descriptor(&hit_desc_2, moby, 0x90003, vec_a, vars->radius);
                    hit_desc_2.b19 = 1;
                    hit_desc_2.id = *(u16 *)(moby + 0xAA);
                    hit_desc_2.b18 = 0;
                    if (moby[0xBC] == 0) {
                        moby_set_state(moby, 1, -1);
                    }
                }
                return;
            }
            if (moby[0xBC] == 0) {
                *(TI16 *)(moby + 0x10) = target[0];
            }
            FastVecScale(vec_a, vars, -0.5f);
            vec_clear_128(vec_b);
            break;
        }
        case 1:
            part_create_flash(moby + 0x10, 0, 0x19, 0x19, 0x19, 0x19, 0, 0, 4.5f, 1, 0);
            moby_mark_spawned(moby);
            return;
        }
    }
    vars->vel[0] += g_flying_shot_vel_step_a;
    vars->vel[1] += g_flying_shot_vel_step_b;
    vars->vel[2] += g_flying_shot_vel_step_c;
    vars->vel[3] += g_flying_shot_vel_step_d;
    if (vars->vel[0] > g_flying_shot_vel_max_a) {
        vars->vel[0] = g_flying_shot_vel_max_a;
    }
    if (vars->vel[1] > g_flying_shot_vel_max_b) {
        vars->vel[1] = g_flying_shot_vel_max_b;
    }
    if (vars->vel[2] > g_flying_shot_vel_max_c) {
        vars->vel[2] = g_flying_shot_vel_max_c;
    }
    if (vars->vel[3] > g_flying_shot_vel_max_d) {
        vars->vel[3] = g_flying_shot_vel_max_d;
    }
    math_apply_axis_rotation_to_quat(moby + 0xE0, moby + 0xE0, moby + 0xD0, g_flying_shot_spin_degrees * 0.017453294f);
    math_apply_axis_rotation_to_quat(moby + 0xC0, moby + 0xC0, moby + 0xD0, g_flying_shot_spin_degrees * 0.017453294f);
    gfx_add_draw_callback_third((void *)blast_projectile_draw_glow, moby);
}
