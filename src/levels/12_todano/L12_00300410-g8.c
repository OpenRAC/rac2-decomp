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
extern char *part_spawn_scaling(void *, void *, unsigned int, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *part_spawn_blast_effect_moby(void *, void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_add_random_offset(void *, float);
extern void FastVecSub(void *, void *, void *);
extern unsigned char *part_l00_spawn_spinning(void *, void *, int);

/* Todano cutscene scene update (runs every frame). It marks and refreshes the scene objects,
   and in mode 5 it sprays effects from the two emitters and runs the current story event. */
void todano_scene_update_events(void)
{
    V pos_a, pos_b, vel_buf, zero_vec;
    V *vel_ptr;
    int obj_index, emitter_index, spark_index;
    char *obj;
    State *scene;
    char **emitter_list;

    anim_start_startup_animations();
    for (obj_index = 0; obj_index < D_L12_001BDB00.count; obj_index++) {
        obj = D_L12_001BDB00.objects[obj_index];
        if (obj && *(short *)(obj + 0xAA) == 0xE29) {
            *(unsigned short *)(obj + 0x34) |= 0x800;
        }
        if (*(short *)(obj + 0xAA) == 0xD54) {
            UpdateEquipmentPieces(obj);
        }
        if (obj && *(short *)(obj + 0xAA) == MOBY_CLASS_TV_SCREENS) {
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
    emitter_list = scene->emitters;
    vel_ptr = &vel_buf;
    for (emitter_index = 1; emitter_index >= 0; emitter_index--) {
        char *emitter = *emitter_list;

        moby_transform_joint_to_world(emitter, 3, &pos_a);
        moby_transform_joint_to_world(emitter, 5, &pos_b);
        lerp_vector(&pos_a, &pos_a, &pos_b, 0.5f);
        zero_vec.q = 0;
        zero_vec.f[2] = -(math_random_float_range(D_L12_001A93E0, D_L12_001A93E4[0]) * 0.016666668f);
        vel_buf.q = zero_vec.q;
        if (D_L12_001B29C8[0] & 1) {
            part_spawn_scaling(&pos_a, vel_ptr, D_L12_001A93E8, D_L12_001A93EC[0], math_random_int_range(18, 22),
                          D_L12_001A9400, -10, 1);
        } else {
            part_spawn_scaling(&pos_a, vel_ptr, D_L12_001A93F0[0], D_L12_001A93F4[0], math_random_int_range(20, 24),
                          D_L12_001A9404[0], -10, 1);
        }
        emitter_list++;
        part_spawn_scaling(&pos_a, vel_ptr, D_L12_001A93F8[0], D_L12_001A93FC[0], math_random_int_range(10, 15),
                      D_L12_001A9408[0], -10, 1);
    }

    switch (D_L12_001BDB00.event) {
    case 2:
        for (obj = D_L12_001B2E9C[0]; obj < D_L12_001B2EA4[0]; obj += 0x100) {
            int cls = *(short *)(obj + 0xAA);
            if (cls == 0x11EB || cls == MOBY_CLASS_NANOTECH_CRATE || cls == 0x326) {
                moby_mark_spawned(obj);
            }
        }
        break;
    case 0x603:
        D_L12_001B9CC0.fade = 0.5f;
        D_L12_001B9CC0.time = 45;
        D_L12_001B9CC0.flag = 0;
        moby_transform_joint_to_world(D_L12_001BDB00.objects[4], 0, &pos_a);
        SpawnExplosion(&pos_a, 1, 25, 20, 20, 20, 45, 1, 0.666f, 20.0f, 1, 1, 0, 0);
        break;
    case 0x6F5:
        D_L12_001B9CC0.fade = 0.5f;
        D_L12_001B9CC0.time = 60;
        D_L12_001B9CC0.flag = 0;
        vec_scale_to_length(&pos_a, &D_L12_001B9CC0.rot, 4.0f);
        FastVecAdd(&pos_a, &pos_a, &D_L12_001B9CC0.pos);
        vec_scale_to_length(&pos_b, &D_L12_001B9CC0.rot, -1.0f);
        part_spawn_blast_effect_moby(D_L12_001BDB00.objects[2], &pos_a, &pos_b, 0.0f);
        break;
    case 0x8D2:
        D_L12_001B9CC0.fade = 0.5f;
        pos_a.q = 0;
        pos_a.f[0] = 4.0f;
        pos_a.f[1] = -1.0f;
        pos_a.f[2] = 1.0f;
        D_L12_001B9CC0.time = 45;
        D_L12_001B9CC0.flag = 0;
        matrix_mul_vec3(&pos_a, &pos_a, &D_L12_001B9CC0.rot);
        FastVecAdd(&pos_a, &pos_a, &D_L12_001B9CC0.pos);
        SpawnExplosion(&pos_a, 1, 25, 20, 20, 20, 45, 1, 0.666f, 20.0f, 1, 1, 0, 0);
        for (spark_index = 24; spark_index >= 0; spark_index--) {
            qcopy(&pos_b, &pos_a);
            vec_add_random_offset(&pos_b, 0.3f);
            FastVecSub(vel_ptr, &pos_b, &pos_a);
            vec_scale_to_length(vel_ptr, vel_ptr, math_random_float_range(0.0f, 1.0f) * 0.016666668f);
            part_l00_spawn_spinning(&pos_b, vel_ptr, 300);
        }
        break;
    }
}
