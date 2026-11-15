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
extern char D_00189E20[] NOT_SDA, D_00138180[] NOT_SDA;
extern u8 D_00188660[] NOT_SDA;
extern float D_0025C64C NOT_SDA;
extern float D_L00_001B8FF0[4][4];
typedef struct { float color[4]; float pos[3]; float radius; } Light;
extern Light D_L00_001C6F40[];
extern int D_L00_001AF2E0 __attribute__((sda));
extern int func_00291308(void *, int, float, float);
extern int func_00282948(void *);
extern void func_0030D430(void *);
extern void func_L00_002AF568(void);
extern void func_0030DE88(void *, int);
extern void func_00291450(int), func_00283098(void *, void *, void *);
extern void func_0029FCC0(void *, int, void *), func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *), func_0030CAD0(void *), func_0030CCD0(void *);
extern void func_L00_002AF7D0(void);
extern void ref_L00_00396288_00(void *, void *);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern float func_00283CE0(int);
/* Maintains the beam's endpoint, light fade and looping sound state. */
/* Moby update: Tractor Beam (class 188). */
void func_L00_00396288(u8 *actor) {
    Vector offset;
    BeamState *beam = *(BeamState **)(actor + 0x68);
    float fade;
    int stopping = ((Hero *)D_00189E20)->i[0x1244 / 4] == 3;
    int active;
    if ((((Pad *)D_00138180)->u[0x1A4 / 4] & ((Hero *)D_00189E20)->u[0x1230 / 4]) && !((Hero *)D_00189E20)->b[0x22BC])
        beam->length = 0.8f;
    D_0025C64C = 0.9f;
    active = 0;
    if (((Hero *)D_00189E20)->i[0x5C0 / 4] && actor[0x20] != 4 && actor[0x20] && !((Hero *)D_00189E20)->b[0x22BC] && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x6F) {
      if (!beam->timer) {
        if (beam->light == -1) beam->light = func_00291308(actor + 0x10, 0, 7.5f, 0);
        else if (beam->fade < 10) beam->fade++;
        active = 1;
        qcopy(&beam->start, actor + 0x10);
        beam->start.f[2] += 0.7f;
        qcopy(&beam->end, &beam->start);
        beam->length += (12.0f - beam->length) * 0.07f;
        if (((Hero *)D_00189E20)->i[0x2294 / 4] == 1) {
            offset.f[0] = 1.2f; offset.f[1] = 0; offset.f[2] = 0;
            matrix_mul_vec3(&offset, &offset, D_L00_001B8FF0);
            beam->start.f[2] = offset.f[2] + *(float *)(actor + 0x18);
            beam->start.f[0] = offset.f[0] + ((Hero *)D_00189E20)->f[0x80 / 4];
            beam->start.f[1] = offset.f[1] + ((Hero *)D_00189E20)->f[0x84 / 4];
            offset.f[0] = beam->length; offset.f[1] = 0; offset.f[2] = 0;
            matrix_mul_vec3(&offset, &offset, D_L00_001B8FF0);
            FastVecAdd(&beam->end, &beam->start, &offset);
        } else if (((Hero *)D_00189E20)->h[0x24EC / 2] == 1) {
            func_0029FCC0(actor, 0, (char *)&beam->start);
            offset.f[0] = 0; offset.f[1] = -beam->length; offset.f[2] = 0;
            matrix_mul_vec3(&offset, &offset, actor + 0xC0);
            FastVecAdd(&beam->end, &beam->start, &offset);
        } else {
            func_0029FCC0(actor, 0, (char *)&beam->start);
            vec_scale_to_length(&beam->end, &((Hero *)D_00189E20)->b[0x730], beam->length);
            FastVecAdd(&beam->end, &beam->start, &beam->end);
        }
        InitializeBoltPointChain(actor); func_0030CCD0(actor);
        ref_L00_00396288_00(func_0030D430, actor);
      }
    } else
        beam->target = 0;
    if (!active) {
        D_L00_001AF2E0 = 1;
        if (beam->fade > 0) beam->fade--;
    }
    switch (actor[0x20]) {
    case 0:
        beam->timer = 16;
        beam->light = func_00291308(&beam->start, 0, 0, 0);
        D_L00_001AF2E0 = 1;
        actor[0x20] = 1;
        beam->cooldown = 20; beam->target = 0; beam->sound = -1;
        PlayMobySound(1, 0, actor);
        break;
    case 1:
        func_00282948(&beam->timer);
        if (beam->sound != -1) {
            u8 *sound = D_00188660 + beam->sound * 0x70;
            if (*(u8 **)(sound + 0x88) == actor && sound[0x74])
                func_002E59F8(beam->sound);
        }
        beam->sound = -1;
        if (active) { start_equipped_item_animation(); actor[0x20] = 3; }
        if ((((Pad *)D_00138180)->u[0x1A4 / 4] & ((Hero *)D_00189E20)->u[0x1230 / 4]) && !((Hero *)D_00189E20)->b[0x22BC]) {
            SpawnEffectBurst(actor, 20);
            if (active) { start_equipped_item_animation(); actor[0x20] = 3; }
            else { PlayMobySound(2, 0, actor); beam->target = 0; actor[0x20] = 1; cancel_hero_item_animation(); }
        }
        break;
    case 3:
        {
            u8 *sound = D_00188660 + beam->sound * 0x70;
            if (*(u8 **)(sound + 0x88) != actor || !sound[0x74]) beam->sound = PlayMobySound(0, 4, actor);
        }
        if ((((Pad *)D_00138180)->u[0x1A8 / 4] & ((Hero *)D_00189E20)->u[0x1230 / 4]) || !active || ((Hero *)D_00189E20)->b[0x22BC]) {
            beam->target = 0; beam->length = 0;
            cancel_hero_item_animation(); actor[0x20] = 1;
        }
        break;
    case 2: case 4: case 5: default: break;
    }
    if (beam->light != -1) {
        Light *lights;
        qzero_nc(&offset);
        offset.f[0] = 2; offset.f[2] = 2;
        matrix_mul_vec3(&offset, &offset, &((Hero *)D_00189E20)->b[0x730]);
        lights = D_L00_001C6F40;
        lights[beam->light].pos[0] = ((Hero *)D_00189E20)->f[0x80 / 4] + offset.f[0];
        lights[beam->light].pos[1] = ((Hero *)D_00189E20)->f[0x84 / 4] + offset.f[1];
        lights[beam->light].pos[2] = ((Hero *)D_00189E20)->f[0x88 / 4] + offset.f[2];
        lights[beam->light].radius = 7.5f;
        fade = IntToFloat(beam->fade) * 0.1f;
        lights[beam->light].color[2] = fade;
        lights[beam->light].color[1] = fade * 0.7f;
        lights[beam->light].color[0] = lights[beam->light].color[1];
        if (!stopping) return;
        if (beam->light != -1) { func_00291450(beam->light); beam->light = -1; }
    }
    if (stopping && beam->light == -1) actor[0x20] = 4;
}

