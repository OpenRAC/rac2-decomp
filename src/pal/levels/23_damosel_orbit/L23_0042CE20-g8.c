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
extern float D_L23_001B36C0[4] __attribute__((sda));
extern float D_L23_001B1A10 __attribute__((sda));
extern float D_L23_001B1A18 __attribute__((sda));
extern float D_L23_001B1A1C __attribute__((sda));
extern float D_L23_001B1A24 __attribute__((sda));
extern float D_L23_001B1A28 __attribute__((sda));
extern float D_L23_001B1A30 __attribute__((sda));
extern float D_L23_001B1A34 __attribute__((sda));
extern float D_L23_001B1A3C __attribute__((sda));
extern float D_L23_001B1A40 __attribute__((sda));
extern float D_L23_001B1ADC __attribute__((sda));
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_clear_128(void *);
extern float fast_vec_dist(void *, void *);
extern void make_hit_descriptor(void *, u8 *, s32, void *, float);
extern s32 CollLine(void *, void *, s32, void *, s32);
extern void *SpawnExplosion(void *, s32, s32, s32, s32, s32, s32, s32, float, float, s32, s32, s32, s32);
extern void part_create_flash(void *, s32, s32, s32, s32, s32, s32, s32, float, s32, s32);
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
void func_PAL_L23_0042D230(u8 *moby) {
    L23Flight *vars = *(L23Flight **)(moby + 0x68);
    TI16 target[1];
    L23Probe q1;
    TI16 vecA[1];
    TI16 vecB[1];
    L23Probe q2;

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
            make_hit_descriptor(&q1, moby, 0x90003, vars, vars->radius);
            q1.id = *(u16 *)(moby + 0xAA);
            if (CollLine(moby + 0x10, target, 0, moby, 0) != 0) {
                float dist = fast_vec_dist(D_L23_001B36C0, g_last_ray_hit.point);
                u8 *player = D_00189E20_2.player;
                s32 isPlayer = g_last_ray_hit.hit == player;

                if (isPlayer || dist < D_L23_001B1ADC) {
                    TI16 t;
                    s32 radius;

                    FastVecScale(vecA, player + 0xE0, 3.5f);
                    FastVecAdd(vecA, vecA, D_00189E20_2.camera);
                    SpawnExplosion(vecA, 1, 5, 5, 5, 0x19, 0x4B, 0, 1.5f, 20.0f, 0, 1, 0, 0);
                    radius = (s32)vars->radius;
                    t = *(TI16 *)(moby + 0x10);
                    vecB[0] = t;
                    cam_play_effect_on_target(moby, 0x10007, radius, vecB, 0, 0);
                    if (isPlayer) {
                        snd_start_in_slot(0x20, 0, 0);
                    }
                    if (moby[0xBC] == 0) {
                        moby_set_state(moby, 1, -1);
                    }
                } else {
                    vecA[0] = *(TI16 *)vars;
                    FastVecScale(vecA, vecA, 3.0f);
                    ((float *)vecA)[2] = 1.0f;
                    ((float *)vecA)[3] = 5627.9248046875f;
                    make_hit_descriptor(&q2, moby, 0x90003, vecA, vars->radius);
                    q2.b19 = 1;
                    q2.id = *(u16 *)(moby + 0xAA);
                    q2.b18 = 0;
                    if (moby[0xBC] == 0) {
                        moby_set_state(moby, 1, -1);
                    }
                }
                return;
            }
            if (moby[0xBC] == 0) {
                *(TI16 *)(moby + 0x10) = target[0];
            }
            FastVecScale(vecA, vars, -0.5f);
            vec_clear_128(vecB);
            break;
        }
        case 1:
            part_create_flash(moby + 0x10, 0, 0x19, 0x19, 0x19, 0x19, 0, 0, 4.5f, 1, 0);
            moby_mark_spawned(moby);
            return;
        }
    }
    vars->vel[0] += D_L23_001B1A18;
    vars->vel[1] += D_L23_001B1A30;
    vars->vel[2] += D_L23_001B1A3C;
    vars->vel[3] += D_L23_001B1A24;
    if (vars->vel[0] > D_L23_001B1A10) {
        vars->vel[0] = D_L23_001B1A10;
    }
    if (vars->vel[1] > D_L23_001B1A28) {
        vars->vel[1] = D_L23_001B1A28;
    }
    if (vars->vel[2] > D_L23_001B1A34) {
        vars->vel[2] = D_L23_001B1A34;
    }
    if (vars->vel[3] > D_L23_001B1A1C) {
        vars->vel[3] = D_L23_001B1A1C;
    }
    math_apply_axis_rotation_to_quat(moby + 0xE0, moby + 0xE0, moby + 0xD0, D_L23_001B1A40 * 0.017453294f);
    math_apply_axis_rotation_to_quat(moby + 0xC0, moby + 0xC0, moby + 0xD0, D_L23_001B1A40 * 0.017453294f);
    gfx_add_draw_callback_third((void *)blast_projectile_draw_glow, moby);
}
