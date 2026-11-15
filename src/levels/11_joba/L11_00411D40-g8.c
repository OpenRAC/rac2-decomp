/* Turret update, adapted from OpenRAC/rac1-decomp (GPL-3.0),
 * src/overlays/l09_gaspar/asteroids_airship_debris.c, turret_update
 * (func_L09_00306030). RAC2 differences were read from retail instructions.
 * -frac2-gcse-unsplit-edges gives the mount branches their shared address setup.
 */
#include "common.h"
typedef int TurretQuad __attribute__((mode(TI)));
typedef union { f32 f[4]; TurretQuad q; } TurretVec __attribute__((aligned(16)));
typedef struct {
 u8 pad0[0x10]; TurretVec unused; u8 pad20[0x20];
 s16 unk40, mount_delay; f32 pitch; s32 unk48, unk4C;
 u8 pad50[2]; s16 dismount_delay, barrel; u8 pad56[6];
 f32 rest_z, yaw_speed, pitch_speed; s32 beam, beam_frames;
 u8 matrix[0x40]; f32 aim[4]; u8 padC0[0x30]; s32 sound;
} TurretVars;
typedef struct { f32 size; u8 pad4[12]; f32 pos[3], alpha; } TurretBeam;
typedef struct {
 u8 pad0[0x80]; TurretVec pos, rot; u8 padA0[0x50]; u8 velocity[0xA0];
 u8 pad190[0x1ac]; u8 *ground; u8 pad340[0x1c70]; f32 stick_x, stick_y;
 u8 pad1FB8[0x2d8]; u8 *moby; s32 state; s32 pad2298, mode;
} TurretHero;
extern TurretHero g_hero_state __attribute__((nosda));
extern struct { u8 pad0[0x6c]; void *owner; u8 slots[0]; } g_sound_state __attribute__((nosda));
extern s32 D_L11_001CAE40 __attribute__((nosda));
extern s32 D_L11_001A7BA4[] __attribute__((sda));
extern s32 D_L11_001A8FB4 SDATA(D_L11_001A8FB4);
extern s32 D_L11_001A8FB4_block[] __asm__("D_L11_001A8FB4") __attribute__((sda));
extern struct { u8 pad[0x1a0]; s32 held, pressed; } g_pad_state __attribute__((nosda));
extern f32 D_L11_001B0C90 __attribute__((sda)), D_L11_001B0C94 __attribute__((sda));
extern TurretVec D_L11_001B0CA0 SDATA(D_L11_001B0CA0);
extern TurretBeam D_L11_001C8A40[];
extern struct { u8 pad[0x160]; f32 unk160; s32 pad164, unk168, unk16C; f32 unk170; s32 pad174, unk178; } D_L11_001BA780;
extern s32 FastDecTimer(void *);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern void FastVecAdd(void *, void *, void *);
extern void mem_fast_helper_b(void *, s32);
extern void cam_set_mode_state(s32);
extern s32 hero_l11_enter_state(s32, s32);
extern void anim_start_blended(void *, s32, s32, s32);
extern void SetCamera5Pose(void *, void *, s32, s32, s32);
extern f32 fast_vec_dist(void *, void *);
extern f32 vec_distance_xy(void *, void *);
extern f32 FastAddRotations(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern f32 mat_fast_helper_a(f32, f32);
extern void matrix_mul_vec3(void *, void *, void *);
extern s32 part_l00_alloc_effect_slot_2(void *, f32, f32, f32, f32, f32);
extern s32 PlayMobySound(s32, s32, void *);
extern void gfx_free_point_light(s32);
extern f32 vec_length_xy(void *);
extern void divide_vector_xyz(void *, void *, f32);
extern void snd_stop_voice(s32);
extern void moby_update_eased_node(void *, void *, s32, f32, f32);
extern f32 moby_get_anim_value(void *);
extern f32 math_fabs(f32);
extern void vec_build_spherical_offset(void *, f32, f32, f32);
extern char *robot_spawn_debris(void *, void *, void *, s32, f32);
extern f32 math_random_float_range(f32, f32);
extern f32 FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, f32);
extern s32 math_random_int_range(s32, s32);
extern u8 *part_spawn_velocity_particle(void *, void *, s32, s32, f32);
extern void func_002A0F48(void *);
extern void overlay_set_shared_flag(void);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern void hud_add_moby_marker(void *, s32, s32, s32, s32, s32, f32, f32, f32);

typedef struct {
 u8 pad0[0x10]; f32 pos[4]; u8 state; u8 pad21[0x13]; u16 flags;
 u8 pad36[0xc]; u8 seq, prev_seq; u8 pad44[4]; f32 speed;
 u8 pad4C[0x14]; u8 anim_flags; u8 pad61[7]; u8 *pvars;
 u8 pad6C[0x50]; u8 command; u8 padBD[3]; u8 matrix[0x30]; f32 rot[4];
} TurretMoby;

/* Updates a turret the hero can climb into. While mounted it follows the hero's stick to turn and tilt the gun, fires shots with a beam, and lets the hero climb out again. */
void TurretUpdate(TurretMoby *moby) {
    TurretVec seat;
    TurretVec offset;
    TurretVec tmp;
    TurretVec shot;
    TurretVec muzzle;
    TurretVec dir;
    TurretVec rnd;
    TurretVars *vars;
    TurretBeam *beam;
    float len;
    float stick_y;
    float yaw;
    int n;
    int i;
    int invert;

    vars = (TurretVars *)moby->pvars;
    if (D_L11_001CAE40 || moby->state == 6) return;
    moby->flags &= ~4;
    moby_transform_joint_to_world(moby, 3, &seat);
    seat.f[2] += 0.4f;
    if (moby->state >= 4) {
        if (FastDecTimer(&vars->mount_delay) != 0 && moby->command == 1 &&
            g_hero_state.mode != 0x14 && g_hero_state.mode != 7 && g_hero_state.state != 0x39 && D_L11_001A8FB4 == 0) {
            qcopy_nc(&g_hero_state.pos, &seat);
            qcopy_nc(&g_hero_state.rot, moby->rot);
            offset.f[0] = math_fast_sin_or_cos_a(g_hero_state.rot.f[2]) * -0.4f;
            offset.f[1] = math_fast_sin_or_cos_b(g_hero_state.rot.f[2]) * -0.4f;
            offset.f[2] = 0.0f;
            FastVecAdd(&g_hero_state.pos, &g_hero_state.pos, &offset);
            mem_fast_helper_b(&g_hero_state.velocity, 0xA0);
            if (g_pad_state.pressed & 0x10) {
                cam_set_mode_state(0);
                hero_l11_enter_state(0, 1);
                moby->command = 2;
                moby->state = 4;
                moby->speed = 1.0f;
                anim_start_blended(moby, 0, 0, 1);
            } else {
                if (moby->state != 5) {
                    vars->dismount_delay = 2;
                    SetCamera5Pose(g_hero_state.moby + 0x10, g_hero_state.moby + 0xf0, 0, 0, 0);
                    if (moby->prev_seq != 4) {
                        anim_start_blended(moby, 4, 0, 5);
                    }
                }
                moby->state = 5;
                moby->speed = 2.0f;
            }
        } else if (moby->command == 2) {
            if (fast_vec_dist(&seat, g_hero_state.moby + 0x10) > 1.2f || g_hero_state.ground != moby) {
                moby->command = 0;
                vars->mount_delay = 60;
            }
        } else if (g_hero_state.mode != 0x14 && g_hero_state.mode != 7 &&
                   g_hero_state.state != 0x39 && g_hero_state.ground == moby &&
                   fast_vec_dist(&seat, g_hero_state.moby + 0x10) < 1.2f && vars->mount_delay == 0 && D_L11_001A8FB4_block[0] == 0) {
            moby->command = 1;
            hero_l11_enter_state(0x31, 1);
        }
    }
    switch (moby->state) {
    case 0:
        moby->state = 4;
        vars->rest_z = moby->pos[2];
        vars->pitch = 0.0f;
        moby->rot[2] = 0.0f;
        vars->beam = -1;
        vars->mount_delay = 0;
        vars->unk48 = 0;
        vars->unk4C = 0;
        vars->unk40 = 0;
        g_sound_state.owner = moby;
        return;
    case 4:
        if (vec_distance_xy(moby->pos, &g_hero_state.pos) < 4.0f) {
            moby->pos[2] += ((vars->rest_z - 1.0f) - moby->pos[2]) * 0.11f;
            if (g_hero_state.ground != moby) {
                yaw = FastAddRotations(vars->yaw_speed,
                FastAddRotations(fast_subtract_rotations(
                    mat_fast_helper_a(g_hero_state.pos.f[0] - moby->pos[0], g_hero_state.pos.f[1] - moby->pos[1]),
                    moby->rot[2]), 3.14159298f) * 0.01f) * 0.9f;
                vars->yaw_speed = yaw;
                moby->rot[2] = FastAddRotations(moby->rot[2], yaw);
            } else vars->yaw_speed = 0.0f;
            matrix_mul_vec3(&tmp, &D_L11_001B0CA0, moby->matrix);
            FastVecAdd(&tmp, &tmp, &seat);
            if (vars->beam == -1) {
                vars->beam_frames = 0;
                vars->beam = part_l00_alloc_effect_slot_2(&tmp, 0.4f, 0.0f, 4.0f, 4.0f, 4.0f);
                PlayMobySound(2, 0, moby);
            } else {
                beam = &D_L11_001C8A40[vars->beam];
                beam->pos[0] = tmp.f[0];
                beam->pos[1] = tmp.f[1];
                beam->pos[2] = tmp.f[2];
                n = ++vars->beam_frames;
                if (n > 40 || !(n & 4)) {
                    beam->size = 4.0f;
                    beam->alpha = 0.4f;
                } else if (n >= 25 && (n & 0xA) == 0xA) {
                    beam->size = 4.0f;
                    beam->alpha = 0.4f;
                } else {
                    beam->alpha = 0.0f;
                }
            }
        } else {
            if (moby->pos[2] < vars->rest_z) {
                moby->pos[2] += 0.016666668f;
            } else {
                moby->pos[2] = vars->rest_z;
            }
            if (g_hero_state.ground != moby && vars->beam != -1) {
                PlayMobySound(0, 0, moby);
                gfx_free_point_light(vars->beam);
                vars->beam = -1;
            }
        }
        break;
    case 5:
        g_sound_state.owner = moby;
        if (moby->pos[2] < vars->rest_z) {
            moby->pos[2] += 0.016666668f;
        } else {
            moby->pos[2] = vars->rest_z;
        }
        tmp.f[0] = g_hero_state.stick_x;
        invert = -1;
        if (D_L11_001A7BA4[0]) invert = 1;
        stick_y = -g_hero_state.stick_y * invert;
        tmp.f[1] = stick_y;
        len = vec_length_xy(&tmp);
        if (len > 1.0f) {
            divide_vector_xyz(&tmp, &tmp, len);
        }
        vars->yaw_speed += -tmp.f[0] * 0.0008726647356525064f;
        if (tmp.f[0] == 0.0f) vars->yaw_speed = 0.0f;
        if (vars->yaw_speed != 0.0f) {
            u8 *slot = (u8 *)&g_sound_state + vars->sound * 0x70;
            if (*(u8 **)(slot + 0x88) != moby || !slot[0x74])
                vars->sound = PlayMobySound(3, 4, moby);
        } else {
            if (vars->sound != -1) {
                u8 *slot = (u8 *)&g_sound_state + vars->sound * 0x70;
                if (*(u8 **)(slot + 0x88) == moby && slot[0x74])
                    snd_stop_voice(vars->sound);
            }
            vars->sound = -1;
        }
        vars->pitch_speed += -tmp.f[1] * 0.00031512894f;
        if (tmp.f[1] == 0.0f) vars->pitch_speed = 0.0f;
        moby->rot[2] = FastAddRotations(moby->rot[2], vars->yaw_speed);
        vars->pitch = FastAddRotations(vars->pitch, vars->pitch_speed);
        if (vars->pitch < -0.52359885f) {
            vars->pitch = -0.52359885f;
            vars->pitch_speed = 0.0f;
        } else if (vars->pitch > 0.52359885f) {
            vars->pitch = 0.52359885f;
            vars->pitch_speed = 0.0f;
        }
        vars->yaw_speed *= 0.97f;
        vars->pitch_speed *= 0.97f;
        vars->aim[1] = -vars->pitch;
        moby_update_eased_node(moby, vars->matrix, 2, 0.03f, 0.3f);
        if (g_pad_state.held & 0x20) {
            if (g_pad_state.pressed & 0x20) {
                anim_start_blended(moby, vars->barrel == 0 ? 3 : 2, 0, 1);
            } else if (moby->seq == 2) {
                if (math_fabs(moby_get_anim_value(moby) - 1.0f) <= 0.25f) {
                    vec_build_spherical_offset(&shot, 1.0f, moby->rot[2], vars->pitch);
                    moby_transform_joint_to_world(moby, 0, &muzzle);
                    robot_spawn_debris(moby, &shot, &muzzle, 0, 6.0f);
                    PlayMobySound(1, 0, moby);
                    D_L11_001BA780.unk160 = 0.03f;
                    D_L11_001BA780.unk168 = 10;
                    D_L11_001BA780.unk170 = 0.03f;
                    D_L11_001BA780.unk178 = 7;
                    D_L11_001BA780.unk16C = 0;
                    vars->barrel = 0;
                    for (i = 0; i < 5; i++) {
                        rnd.q = 0;
                        rnd.f[0] = math_random_float_range(-1.0f, 1.0f);
                        rnd.f[1] = math_random_float_range(-1.0f, 1.0f);
                        rnd.f[2] = math_random_float_range(-1.0f, 1.0f);
                        dir.q = rnd.q;
                        vec_scale_to_length(&dir, &dir, FastVecLength(&shot) * 0.65f);
                        FastVecAdd(&dir, &shot, &dir);
                        vec_scale_to_length(&dir, &dir, math_random_float_range(0.050000004f, 0.10000001f));
                        part_spawn_velocity_particle(&muzzle, &dir, 0x5F2F4F6F, math_random_int_range(5, 10), 50000.0f);
                    }
                    vec_scale_to_length(&shot, &shot, 0.008333334f);
                    part_spawn_velocity_particle(&muzzle, &shot, 0x2F4F7F7F, math_random_int_range(4, 7), 500000.0f);
                } else if (moby->anim_flags & 2) {
                    anim_start_blended(moby, 3, 0, 1);
                }
            } else if (moby->seq == 3) {
                if (math_fabs(moby_get_anim_value(moby) - 1.0f) <= 0.25f) {
                    vec_build_spherical_offset(&shot, 1.0f, moby->rot[2], vars->pitch);
                    moby_transform_joint_to_world(moby, 1, &muzzle);
                    robot_spawn_debris(moby, &shot, &muzzle, 0, 6.0f);
                    PlayMobySound(1, 0, moby);
                    D_L11_001BA780.unk160 = 0.03f;
                    D_L11_001BA780.unk168 = 10;
                    D_L11_001BA780.unk170 = 0.03f;
                    D_L11_001BA780.unk178 = 7;
                    D_L11_001BA780.unk16C = 0;
                    vars->barrel = 1;
                    for (i = 0; i < 5; i++) {
                        rnd.q = 0;
                        rnd.f[0] = math_random_float_range(-1.0f, 1.0f);
                        rnd.f[1] = math_random_float_range(-1.0f, 1.0f);
                        rnd.f[2] = math_random_float_range(-1.0f, 1.0f);
                        dir.q = rnd.q;
                        vec_scale_to_length(&dir, &dir, FastVecLength(&shot) * 0.65f);
                        FastVecAdd(&dir, &shot, &dir);
                        vec_scale_to_length(&dir, &dir, math_random_float_range(0.050000004f, 0.10000001f));
                        part_spawn_velocity_particle(&muzzle, &dir, 0x5F2F4F6F, math_random_int_range(5, 10), 50000.0f);
                    }
                    vec_scale_to_length(&shot, &shot, 0.008333334f);
                    part_spawn_velocity_particle(&muzzle, &shot, 0x2F4F7F7F, math_random_int_range(4, 7), 500000.0f);
                } else if (moby->anim_flags & 2) {
                    anim_start_blended(moby, 2, 0, 1);
                }
            }
        } else if (moby->prev_seq != 4 && (moby->anim_flags & 2)) {
            anim_start_blended(moby, 4, 0, 1);
        }
        if (FastDecTimer(&vars->dismount_delay) != 0) {
            func_002A0F48(moby);
            moby->flags |= 4;
            overlay_set_shared_flag();
            moby_transform_joint_to_world(moby, 2, &tmp);
            vec_build_spherical_offset(&shot, D_L11_001B0C90, moby->rot[2], vars->pitch);
            shot.f[2] += D_L11_001B0C94;
            FastVecAdd(&muzzle, &tmp, &shot);
            object_copy_vector_to_selected(&muzzle);
            dir.f[0] = 0.0f;
            dir.f[1] = -vars->pitch;
            dir.f[2] = moby->rot[2];
            cam_set_state_rotation(&dir);
        }
        hud_add_moby_marker(moby, 0xFF0F0FFF, 0, 0xD, -1, 4, 1.0f, 0.0f, 90.0f);
        break;
    }
}
