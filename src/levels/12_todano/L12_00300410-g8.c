#include "include_asm.h"
#include "common.h"

/* Per-frame Todano scene update: flag, refresh or rotate the tracked objects, register the
   tuning callback, then, in mode 5, emit effects at the two emitters and run the current event.
   The state pointer is a local set after the callback registration; it crosses no call, so
   sched1 keeps its set after the call (its anti-dependence persists into sched2), and the
   block-local emitter object in the loop gives it a preference for $s0. */

typedef unsigned int Q __attribute__((mode(TI)));
typedef union {
    Q q;
    float f[4];
} V;

typedef struct {
    char p[0x30];
    int mode;
    int event;
    char p2[0xC];
    short count;
    char p3[0x146];
    char *objects[5];
    char *emitters[2];
} State;
extern State D_L12_001BDB00;

typedef struct {
    char p[0x140];
    V pos;
    char p2[0x1C];
    int flag;
    char p3[0x10];
    float fade;
    int p4;
    int time;
    char p5[0x1E4];
    V rot;
} Scene;
extern Scene D_L12_001B9CC0;

extern char *D_L12_001B2E9C[] __attribute__((sda));
extern char *D_L12_001B2EA4[] __attribute__((sda));
extern int D_L12_001B29C8[] __attribute__((sda));
extern float D_L12_001A93E0 __attribute__((sda));
extern float D_L12_001A93E4[] __attribute__((sda));
extern int D_L12_001A93E8 __attribute__((sda));
extern int D_L12_001A9400 __attribute__((sda));
extern int D_L12_001A93EC[] __attribute__((sda));
extern int D_L12_001A93F0[] __attribute__((sda));
extern int D_L12_001A93F4[] __attribute__((sda));
extern int D_L12_001A93F8[] __attribute__((sda));
extern int D_L12_001A93FC[] __attribute__((sda));
extern int D_L12_001A9408[] __attribute__((sda));
extern int D_L12_001A9404[] __attribute__((sda));

extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces(void *);
extern void math_store_angle_update_result(void *, void *, unsigned int, unsigned int, float);
extern void gfx_add_draw_callback_first(void (*)(void), void *);
extern void todano_refresh_scene_tuning(void);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void lerp_vector(void *, void *, void *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern void part_spawn_scaling(void *, void *, unsigned int, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern void SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void part_spawn_blast_effect_moby(void *, void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_add_random_offset(void *, float);
extern void FastVecSub(void *, void *, void *);
extern void part_l00_spawn_spinning(void *, void *, int);

/* Todano cutscene scene update (runs every frame). It marks and refreshes the scene objects,
   and in mode 5 it sprays effects from the two emitters and runs the current story event. */
void todano_scene_update_events(void)
{
    V posA, posB, velBuf, zeroVec;
    V *velPtr;
    int objIndex, emitterIndex, sparkIndex;
    char *obj;
    State *scene;
    char **emitterList;

    anim_start_startup_animations();
    for (objIndex = 0; objIndex < D_L12_001BDB00.count; objIndex++) {
        obj = D_L12_001BDB00.objects[objIndex];
        if (obj && *(short *)(obj + 0xAA) == 0xE29) {
            *(unsigned short *)(obj + 0x34) |= 0x800;
        }
        if (*(short *)(obj + 0xAA) == 0xD54) {
            UpdateEquipmentPieces(obj);
        }
        if (obj && *(short *)(obj + 0xAA) == 0xFA0 /* TV Screens */) {
            char *p = *(char **)(obj + 0x68);
            if (p) {
                math_store_angle_update_result(obj, p + 0xC, 0x80AAAAD2, 0x80396464, 0.061086535f);
            }
        }
    }
    gfx_add_draw_callback_first(todano_refresh_scene_tuning, 0);

    scene = &D_L12_001BDB00;
    if (scene->mode != 5) {
        return;
    }
    emitterList = scene->emitters;
    velPtr = &velBuf;
    for (emitterIndex = 1; emitterIndex >= 0; emitterIndex--) {
        char *emitter = *emitterList;

        moby_transform_joint_to_world(emitter, 3, &posA);
        moby_transform_joint_to_world(emitter, 5, &posB);
        lerp_vector(&posA, &posA, &posB, 0.5f);
        zeroVec.q = 0;
        zeroVec.f[2] = -(math_random_float_range(D_L12_001A93E0, D_L12_001A93E4[0]) * 0.016666668f);
        velBuf.q = zeroVec.q;
        if (D_L12_001B29C8[0] & 1) {
            part_spawn_scaling(&posA, velPtr, D_L12_001A93E8, D_L12_001A93EC[0], math_random_int_range(18, 22),
                          D_L12_001A9400, -10, 1);
        } else {
            part_spawn_scaling(&posA, velPtr, D_L12_001A93F0[0], D_L12_001A93F4[0], math_random_int_range(20, 24),
                          D_L12_001A9404[0], -10, 1);
        }
        emitterList++;
        part_spawn_scaling(&posA, velPtr, D_L12_001A93F8[0], D_L12_001A93FC[0], math_random_int_range(10, 15),
                      D_L12_001A9408[0], -10, 1);
    }

    switch (D_L12_001BDB00.event) {
    case 2:
        for (obj = D_L12_001B2E9C[0]; obj < D_L12_001B2EA4[0]; obj += 0x100) {
            int cls = *(short *)(obj + 0xAA);
            if (cls == 0x11EB || cls == 0x1F5 /* Nanotech Crate */ || cls == 0x326) {
                moby_mark_spawned(obj);
            }
        }
        break;
    case 0x603:
        D_L12_001B9CC0.fade = 0.5f;
        D_L12_001B9CC0.time = 45;
        D_L12_001B9CC0.flag = 0;
        moby_transform_joint_to_world(D_L12_001BDB00.objects[4], 0, &posA);
        SpawnExplosion(&posA, 1, 25, 20, 20, 20, 45, 1, 0.666f, 20.0f, 1, 1, 0, 0);
        break;
    case 0x6F5:
        D_L12_001B9CC0.fade = 0.5f;
        D_L12_001B9CC0.time = 60;
        D_L12_001B9CC0.flag = 0;
        vec_scale_to_length(&posA, &D_L12_001B9CC0.rot, 4.0f);
        FastVecAdd(&posA, &posA, &D_L12_001B9CC0.pos);
        vec_scale_to_length(&posB, &D_L12_001B9CC0.rot, -1.0f);
        part_spawn_blast_effect_moby(D_L12_001BDB00.objects[2], &posA, &posB, 0.0f);
        break;
    case 0x8D2:
        D_L12_001B9CC0.fade = 0.5f;
        posA.q = 0;
        posA.f[0] = 4.0f;
        posA.f[1] = -1.0f;
        posA.f[2] = 1.0f;
        D_L12_001B9CC0.time = 45;
        D_L12_001B9CC0.flag = 0;
        matrix_mul_vec3(&posA, &posA, &D_L12_001B9CC0.rot);
        FastVecAdd(&posA, &posA, &D_L12_001B9CC0.pos);
        SpawnExplosion(&posA, 1, 25, 20, 20, 20, 45, 1, 0.666f, 20.0f, 1, 1, 0, 0);
        for (sparkIndex = 24; sparkIndex >= 0; sparkIndex--) {
            qcopy(&posB, &posA);
            vec_add_random_offset(&posB, 0.3f);
            FastVecSub(velPtr, &posB, &posA);
            vec_scale_to_length(velPtr, velPtr, math_random_float_range(0.0f, 1.0f) * 0.016666668f);
            part_l00_spawn_spinning(&posB, velPtr, 300);
        }
        break;
    }
}
