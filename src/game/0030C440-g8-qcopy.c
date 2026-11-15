#include "include_asm.h"
/* func_0030C440: the resident copy of func_L00_00396288 (beam actor), over the boot's own
   light table, matrix and flags. */
#include "common.h"
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; } Hero;
typedef union { u8 b[0x200]; u32 u[0x80]; } Pad;
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct {
    Vector start, end;
    void *target;
    float length;
    int unknown28, timer, light, fade;
    short cooldown;
    char unknown3A[6];
    int sound;
} BeamState;
extern char g_hero_state[] NOT_SDA, g_pad_state[] NOT_SDA;
extern u8 g_sound_state[] NOT_SDA;
extern float D_001B323C NOT_SDA;
extern float D_001B5570[4][4];
typedef struct { float color[4]; float pos[3]; float radius; } Light;
extern Light D_001C2B40[];
extern int D_001AEFA0 __attribute__((sda));
extern int gfx_add_point_light(void *, int, float, float);
extern int math_fast_float_d(void *);
extern void beam_draw_ribbons_level(void *);
extern void stub_empty_10(void);
extern void SpawnEffectBurst(void *, int);
extern void gfx_free_point_light(int), matrix_mul_vec3(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecAdd(void *, void *, void *), InitializeBoltPointChain(void *), beam_update_chain_points(void *);
extern void stub_empty_11(void);
extern void gfx_register_overlay_draw_callback(void *, void *);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern float IntToFloat(int);
/* Maintains the beam's endpoint, light fade and looping sound state. */
void beam_actor_update(u8 *actor) {
    Vector offset;
    BeamState *beam = *(BeamState **)(actor + 0x68);
    float fade;
    int stopping = ((Hero *)g_hero_state)->i[0x1244 / 4] == 3;
    int active;
    if ((((Pad *)g_pad_state)->u[0x1A4 / 4] & ((Hero *)g_hero_state)->u[0x1230 / 4]) && !((Hero *)g_hero_state)->b[0x22BC])
        beam->length = 0.8f;
    D_001B323C = 0.9f;
    active = 0;
    if (((Hero *)g_hero_state)->i[0x5C0 / 4] && actor[0x20] != 4 && actor[0x20] && !((Hero *)g_hero_state)->b[0x22BC] && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x6F) {
      if (!beam->timer) {
        if (beam->light == -1) beam->light = gfx_add_point_light(actor + 0x10, 0, 7.5f, 0);
        else if (beam->fade < 10) beam->fade++;
        active = 1;
        qcopy(&beam->start, actor + 0x10);
        beam->start.f[2] += 0.7f;
        qcopy(&beam->end, &beam->start);
        beam->length += (12.0f - beam->length) * 0.07f;
        if (((Hero *)g_hero_state)->i[0x2294 / 4] == 1) {
            offset.f[0] = 1.2f; offset.f[1] = 0; offset.f[2] = 0;
            matrix_mul_vec3(&offset, &offset, D_001B5570);
            beam->start.f[2] = offset.f[2] + *(float *)(actor + 0x18);
            beam->start.f[0] = offset.f[0] + ((Hero *)g_hero_state)->f[0x80 / 4];
            beam->start.f[1] = offset.f[1] + ((Hero *)g_hero_state)->f[0x84 / 4];
            offset.f[0] = beam->length; offset.f[1] = 0; offset.f[2] = 0;
            matrix_mul_vec3(&offset, &offset, D_001B5570);
            FastVecAdd(&beam->end, &beam->start, &offset);
        } else if (((Hero *)g_hero_state)->h[0x24EC / 2] == 1) {
            moby_transform_joint_to_world(actor, 0, (char *)&beam->start);
            offset.f[0] = 0; offset.f[1] = -beam->length; offset.f[2] = 0;
            matrix_mul_vec3(&offset, &offset, actor + 0xC0);
            FastVecAdd(&beam->end, &beam->start, &offset);
        } else {
            moby_transform_joint_to_world(actor, 0, (char *)&beam->start);
            vec_scale_to_length(&beam->end, &((Hero *)g_hero_state)->b[0x730], beam->length);
            FastVecAdd(&beam->end, &beam->start, &beam->end);
        }
        InitializeBoltPointChain(actor); beam_update_chain_points(actor);
        gfx_register_overlay_draw_callback(beam_draw_ribbons_level, actor);
      }
    } else
        beam->target = 0;
    if (!active) {
        D_001AEFA0 = 1;
        if (beam->fade > 0) beam->fade--;
    }
    switch (actor[0x20]) {
    case 0:
        beam->timer = 16;
        beam->light = gfx_add_point_light(&beam->start, 0, 0, 0);
        D_001AEFA0 = 1;
        actor[0x20] = 1;
        beam->cooldown = 20; beam->target = 0; beam->sound = -1;
        PlayMobySound(1, 0, actor);
        break;
    case 1:
        math_fast_float_d(&beam->timer);
        if (beam->sound != -1) {
            u8 *sound = g_sound_state + beam->sound * 0x70;
            if (*(u8 **)(sound + 0x88) == actor && sound[0x74])
                snd_stop_voice(beam->sound);
        }
        beam->sound = -1;
        if (active) { stub_empty_10(); actor[0x20] = 3; }
        if ((((Pad *)g_pad_state)->u[0x1A4 / 4] & ((Hero *)g_hero_state)->u[0x1230 / 4]) && !((Hero *)g_hero_state)->b[0x22BC]) {
            SpawnEffectBurst(actor, 20);
            if (active) { stub_empty_10(); actor[0x20] = 3; }
            else { PlayMobySound(2, 0, actor); beam->target = 0; actor[0x20] = 1; stub_empty_11(); }
        }
        break;
    case 3:
        {
            u8 *sound = g_sound_state + beam->sound * 0x70;
            if (*(u8 **)(sound + 0x88) != actor || !sound[0x74]) beam->sound = PlayMobySound(0, 4, actor);
        }
        if ((((Pad *)g_pad_state)->u[0x1A8 / 4] & ((Hero *)g_hero_state)->u[0x1230 / 4]) || !active || ((Hero *)g_hero_state)->b[0x22BC]) {
            beam->target = 0; beam->length = 0;
            stub_empty_11(); actor[0x20] = 1;
        }
        break;
    case 2: case 4: case 5: default: break;
    }
    if (beam->light != -1) {
        Light *lights;
        qzero_nc(&offset);
        offset.f[0] = 2; offset.f[2] = 2;
        matrix_mul_vec3(&offset, &offset, &((Hero *)g_hero_state)->b[0x730]);
        lights = D_001C2B40;
        lights[beam->light].pos[0] = ((Hero *)g_hero_state)->f[0x80 / 4] + offset.f[0];
        lights[beam->light].pos[1] = ((Hero *)g_hero_state)->f[0x84 / 4] + offset.f[1];
        lights[beam->light].pos[2] = ((Hero *)g_hero_state)->f[0x88 / 4] + offset.f[2];
        lights[beam->light].radius = 7.5f;
        fade = IntToFloat(beam->fade) * 0.1f;
        lights[beam->light].color[2] = fade;
        lights[beam->light].color[1] = fade * 0.7f;
        lights[beam->light].color[0] = lights[beam->light].color[1];
        if (!stopping) return;
        if (beam->light != -1) { gfx_free_point_light(beam->light); beam->light = -1; }
    }
    if (stopping && beam->light == -1) actor[0x20] = 4;
}

