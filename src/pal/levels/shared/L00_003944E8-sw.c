#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef union { u8 b[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; } Hero;
typedef struct { u16 count; u16 pad; u32 maximum; u32 levels; } Statistics;
typedef struct {
    Vector start, end;
    char *target;
    float length;
    short targetAge, secondaryAge;
    int timer, light, fade;
    char *secondary;
    short ammoTimer, cooldown, targetReady, secondaryReady, targetTimer, secondaryTimer;
    int sound;
} DualBeamState;
extern Hero g_hero_state;
extern u32 g_pad_state[];
extern u8 g_sound_state[];
extern float D_0025C64C NOT_SDA;
extern u8 D_0013957A[];
typedef struct { u8 pad[4]; u8 flag; u8 rest[0xDB]; } LevelInfo;
extern LevelInfo g_weapon_l00_table[];
typedef struct { float color[3]; float pad; float pos[3]; float radius; } Light;
extern Light D_L00_001C6F40[];
extern int D_L00_001AF130 __attribute__((sda)), D_L00_001B2748 __attribute__((sda));
extern u32 D_001A7390, g_current_map_index;
extern Statistics D_0018C360[], g_progress_statistics[];
extern int get_ammo(int);
extern int weapon_spend_ammo(int, int);
extern int math_fast_float_d(int *), FastDecTimer(short *);
extern void hud_add_moby_marker(void *, u32, void *, int, int, int, float, float, float);
extern s16 gfx_add_point_light(void *, int, float, float);
extern int PlayMobySound(int, int, char *), snd_is_voice_playing_for_owner(void *, int);
extern float mat_fast_helper_a(float, float), FastDiffRots(float, float), fast_vec_dist(void *, void *), IntToFloat(int);
extern void cam_compute_view_direction(void *, void *, int), FastVecScale(void *, void *, float), FastVecAdd(void *, void *, void *);
extern char *moby_get_private_value_0(char *);
extern void matrix_mul_vec3(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void func_PAL_0030B4E0(char *), func_PAL_L00_00396350(char *), func_PAL_0030CE20(void *);
extern void ref_L00_00392530_00(void (*)(void *), void *), snd_stop_voice(int);
extern void func_PAL_L00_002AF458(void), func_PAL_L00_002AF6C0(void), gfx_free_point_light(int);

/* Maintains two beam targets, their acquisition delays, ammunition and the light/sound state. */
void func_PAL_L00_00395680(char *actor) {
    Vector direction, offset;
    float local[4] __attribute__((aligned(16)));
    DualBeamState *beam;
    char *entry;
    u8 *sound;
    int stopping, active, permitted, ammo, limit;
    float fade;

    stopping = g_hero_state.i[0x1244 / 4] == 3;
    beam = *(DualBeamState **)(actor + 0x68);
    if ((g_pad_state[0x1A4 / 4] & g_hero_state.u[0x1230 / 4]) && !g_hero_state.b[0x22BC]) beam->length = 0.8f;
    D_0025C64C = 0.9f;
    active = 0;
    permitted = 1;
    ammo = get_ammo(-1);
    if (g_hero_state.i[0x2294 / 4] == 1) {
        if (!math_fast_float_d(&g_hero_state.i[0x2534 / 4])) permitted = 0;
        else hud_add_moby_marker(actor, !get_ammo(-1) ? 0x600000FF : 0x600FFF0F, 0, 31, -1, 4, 1, 0, 90);
    } else g_hero_state.i[0x2534 / 4] = 33;
    if ((g_pad_state[0x1A0 / 4] & g_hero_state.u[0x1230 / 4]) && (u8)actor[0x20] != 4 && (u8)actor[0x20] &&
        !g_hero_state.b[0x22BC] && g_hero_state.i[0x2294 / 4] != 0x6F && g_hero_state.i[0x1240 / 4] >= 19 && permitted) {
        if (!beam->timer) {
            if (ammo > 0) {
            if (FastDecTimer(&beam->ammoTimer)) {
                FastDecTimer(&beam->targetTimer);
                FastDecTimer(&beam->secondaryTimer);
                weapon_spend_ammo(-1, 1);
                beam->ammoTimer = 8;
            }
            if (beam->light == -1) beam->light = gfx_add_point_light(actor + 0x10, 0, 7.5f, 0);
            else if (beam->fade < 8) beam->fade++;
            active = 1;
            if (beam->target) {
                if (FastDiffRots(g_hero_state.f[0x98 / 4],
                                  mat_fast_helper_a(*(float *)(beam->target + 0x10) - g_hero_state.f[0x80 / 4],
                                                *(float *)(beam->target + 0x14) - g_hero_state.f[0x84 / 4])) > 2.0943f ||
                    !((u8 *)beam->target)[0x31] || fast_vec_dist(beam->target + 0x10, &g_hero_state.f[0x80 / 4]) > 20) {
                    beam->target = 0;
                    beam->targetReady = 0;
                }
            }
            if (beam->secondary) {
                if (FastDiffRots(g_hero_state.f[0x98 / 4],
                                  mat_fast_helper_a(*(float *)(beam->secondary + 0x10) - g_hero_state.f[0x80 / 4],
                                                *(float *)(beam->secondary + 0x14) - g_hero_state.f[0x84 / 4])) > 2.0943f ||
                    !((u8 *)beam->secondary)[0x31] || fast_vec_dist(beam->secondary + 0x10, &g_hero_state.f[0x80 / 4]) > 20) {
                    beam->secondary = 0;
                    beam->secondaryReady = 0;
                }
            }
            cam_compute_view_direction(beam, &direction, 1);
            qcopy(&beam->start, actor + 0x10);
            FastVecScale(&offset, &direction, 0.7f);
            FastVecAdd(&beam->start, &beam->start, &offset);
            qcopy(&beam->end, &beam->start);
            if (beam->target && beam->targetReady) {
                limit = 50;
                beam->targetAge++;
                entry = moby_get_private_value_0(beam->target);
                if (entry && *(short *)(entry + 4) == 1) limit = 5;
                if (beam->targetAge >= ((s32)(limit) * 5 + 2) / 6) {
                    beam->target = 0;
                    beam->targetReady = 0;
                }
            } else beam->targetAge = 0;
            if (beam->secondary && beam->secondaryReady) {
                limit = 50;
                beam->secondaryAge++;
                entry = moby_get_private_value_0(beam->secondary);
                if (entry && *(short *)(entry + 4) == 1) limit = 5;
                if (beam->secondaryAge >= ((s32)(limit) * 5 + 2) / 6) {
                    beam->secondary = 0;
                    beam->secondaryReady = 0;
                }
            } else beam->secondaryAge = 0;
            beam->length += (((g_weapon_l00_table + D_0013957A[0])->flag ? 18.0f : 12.0f) - beam->length) * 0.08400001f;
            if (g_hero_state.h[0x24EC / 2] == 1) {
                moby_transform_joint_to_world(actor, 0, &beam->start);
                local[0] = 0;
                local[1] = -beam->length;
                local[2] = 0;
                matrix_mul_vec3(local, local, actor + 0xC0);
                FastVecAdd(&beam->end, &beam->start, local);
            } else {
                moby_transform_joint_to_world(actor, 0, &beam->start);
                vec_scale_to_length(&beam->end, &g_hero_state.f[0x730 / 4], beam->length);
                FastVecAdd(&beam->end, &beam->start, &beam->end);
            }
            func_PAL_0030B4E0(actor);
            func_PAL_L00_00396350(actor);
            ref_L00_00392530_00(func_PAL_0030CE20, actor);
            } else {
                beam->target = 0;
                beam->secondary = 0;
                beam->targetReady = 0;
                beam->secondaryReady = 0;
                beam->targetTimer = 0;
                beam->secondaryTimer = 0;
            }
        }
    } else {
        beam->target = 0;
        beam->secondary = 0;
        beam->targetReady = 0;
        beam->secondaryReady = 0;
    }
    if (!active) {
        D_L00_001AF130 = 1;
        if (beam->fade > 0) beam->fade--;
        if (beam->sound != -1) {
            sound = g_sound_state + beam->sound * 0x70;
            if (*(char **)(sound + 0x88) == actor && sound[0x74]) snd_stop_voice(beam->sound);
        }
        beam->sound = -1;
    } else {
        if (!snd_is_voice_playing_for_owner(actor, beam->sound)) beam->sound = PlayMobySound(4, 4, actor);
    }
    if (!beam->target || (u8)beam->target[0x20] == 0xFE || (u8)beam->target[0x20] == 0xFD ||
        !(*(u16 *)(beam->target + 0x34) & 0x1000))
        beam->targetReady = 1;
    if (!beam->secondary || (u8)beam->secondary[0x20] == 0xFE || (u8)beam->secondary[0x20] == 0xFD ||
        !(*(u16 *)(beam->secondary + 0x34) & 0x1000))
        beam->secondaryReady = 1;
    switch ((u8)actor[0x20]) {
    case 0:
        beam->timer = 13;
        beam->light = gfx_add_point_light(&beam->start, 0, 0, 0);
        D_L00_001AF130 = 1;
        actor[0x20] = 1;
        beam->cooldown = 20;
        beam->sound = -1;
        beam->secondary = 0;
        beam->target = 0;
        beam->targetReady = 0;
        beam->secondaryReady = 0;
        beam->secondaryTimer = 0;
        beam->targetTimer = 0;
        D_L00_001B2748 = 8;
        break;
    case 1:
        math_fast_float_d(&beam->timer);
        if (active) {
            func_PAL_L00_002AF458();
            actor[0x20] = 3;
        }
        if ((g_pad_state[0x1A4 / 4] & g_hero_state.u[0x1230 / 4]) && !g_hero_state.b[0x22BC]) {
            if (active) {
                if (D_0018C360[18].count < 0xFFFF) D_0018C360[18].count++;
                if (D_0018C360[18].maximum < ((s32)D_001A7390 * 5 + 2) / 6) D_0018C360[18].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
                D_0018C360[18].levels = (D_0018C360[18].levels | (1u << g_current_map_index)) | 0x80000000u;
                func_PAL_L00_002AF458();
                actor[0x20] = 3;
            } else {
                beam->target = 0;
                beam->secondary = 0;
                beam->targetReady = 0;
                beam->secondaryReady = 0;
                actor[0x20] = 1;
                PlayMobySound(0, 0, actor);
                func_PAL_L00_002AF6C0();
            }
        }
        break;
    case 3:
        if (!(g_pad_state[0x1A8 / 4] & g_hero_state.u[0x1230 / 4]) && active && !g_hero_state.b[0x22BC]) break;
        if (g_hero_state.i[0x1D8 / 4] > 58) {
            if (g_progress_statistics[26].count < 0xFFFF) g_progress_statistics[26].count++;
        }
        if (g_progress_statistics[26].maximum < ((s32)D_001A7390 * 5 + 2) / 6) g_progress_statistics[26].maximum = ((s32)D_001A7390 * 5 + 2) / 6;
        g_progress_statistics[26].levels = (g_progress_statistics[26].levels | (1u << g_current_map_index)) | 0x80000000u;
        if (g_hero_state.i[0x1D8 / 4] < 25) g_hero_state.b[0x22C5]++;
        else g_hero_state.b[0x22C5] = 0;
        beam->target = 0;
        beam->secondary = 0;
        beam->targetReady = 0;
        beam->secondaryReady = 0;
        beam->length = 0;
        func_PAL_L00_002AF6C0();
        actor[0x20] = 1;
        break;
    case 2:
    case 4:
    case 5:
        break;
    }
    if (beam->light != -1) {
        qzero_nc(&direction);
        direction.f[0] = 2;
        direction.f[2] = 2;
        matrix_mul_vec3(&direction, &direction, &g_hero_state.f[0x730 / 4]);
        (D_L00_001C6F40 + beam->light)->pos[0] = g_hero_state.f[0x80 / 4] + direction.f[0];
        (D_L00_001C6F40 + beam->light)->pos[1] = g_hero_state.f[0x84 / 4] + direction.f[1];
        (D_L00_001C6F40 + beam->light)->pos[2] = g_hero_state.f[0x88 / 4] + direction.f[2];
        (D_L00_001C6F40 + beam->light)->radius = 7.5f;
        fade = IntToFloat(beam->fade) * 0.125f;
        (D_L00_001C6F40 + beam->light)->color[2] = fade;
        (D_L00_001C6F40 + beam->light)->color[1] = fade * 0.7f;
        (D_L00_001C6F40 + beam->light)->color[0] = (D_L00_001C6F40 + beam->light)->color[1];
        if (stopping && beam->light != -1) {
            gfx_free_point_light(beam->light);
            beam->light = -1;
        }
    }
    if (stopping && beam->light == -1) actor[0x20] = 4;
}
