/* func_PAL_L12_00301DD8, the PAL copy of func_L12_00300410: the same C, with a level test of 0x33
   around the 0xFA0 objects' update, 1/60 becoming 0.02, the emitters' spawn counts and the
   event timers scaled to 50 Hz and the 0xFA0 update's float going to 0.07330384f (x 6/5).
   The object is read as base + i * 4 + 0x18C rather than objects[i]: without a separate
   base + 0x18C in the loop, loop.c's first pass still hoists 0xFA0 ahead of the pointer's giv
   and leaves 0x33 to the second. The emitter loop counts up, so dbra sets its counter after
   the hoisted 6. */
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
extern int g_current_map_index[] __attribute__((sda));
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
extern void func_PAL_002E7270(void *);
extern void math_store_angle_update_result(void *, void *, unsigned int, unsigned int, float);
extern void gfx_add_draw_callback_first(void (*)(void), void *);
extern void todano_refresh_scene_tuning(void);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void lerp_vector(void *, void *, void *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern void part_spawn_scaling(void *, void *, unsigned int, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void func_PAL_0032F3B8(void *, void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_add_random_offset(void *, float);
extern void FastVecSub(void *, void *, void *);
extern void func_PAL_L00_00342480(void *, void *, int);

void func_PAL_L12_00301DD8(void)
{
    V a, b, c, d;
    V *velocity;
    int i, j, k;
    char *obj;
    State *st;
    char **entries;

    anim_start_startup_animations();
    for (i = 0; i < D_L12_001BDB00.count; i++) {
        obj = ((State *)((char *)&D_L12_001BDB00 + i * 4))->objects[0];
        if (obj && *(short *)(obj + 0xAA) == 0xE29) {
            *(unsigned short *)(obj + 0x34) |= 0x800;
        }
        if (*(short *)(obj + 0xAA) == 0xD54) {
            func_PAL_002E7270(obj);
        }
        if (obj && *(short *)(obj + 0xAA) == 0xFA0 && g_current_map_index[0] != 0x33) {
            char *p = *(char **)(obj + 0x68);
            if (p) {
                math_store_angle_update_result(obj, p + 0xC, 0x80AAAAD2, 0x80396464, 0.07330384f);
            }
        }
    }
    gfx_add_draw_callback_first(todano_refresh_scene_tuning, 0);

    st = &D_L12_001BDB00;
    if (st->mode != 5) {
        return;
    }
    entries = st->emitters;
    velocity = &c;
    for (j = 0; j < 2; j++) {
        char *emitter = *entries;

        moby_transform_joint_to_world(emitter, 3, &a);
        moby_transform_joint_to_world(emitter, 5, &b);
        lerp_vector(&a, &a, &b, 0.5f);
        d.q = 0;
        d.f[2] = -(math_random_float_range(D_L12_001A93E0, D_L12_001A93E4[0]) * 0.020000001f);
        c.q = d.q;
        if (D_L12_001B29C8[0] & 1) {
            part_spawn_scaling(&a, velocity, D_L12_001A93E8, D_L12_001A93EC[0], ((s32)(math_random_int_range(18, 22)) * 5 + 2) / 6,
                          D_L12_001A9400, -10, 1);
        } else {
            part_spawn_scaling(&a, velocity, D_L12_001A93F0[0], D_L12_001A93F4[0], ((s32)(math_random_int_range(20, 24)) * 5 + 2) / 6,
                          D_L12_001A9404[0], -10, 1);
        }
        entries++;
        part_spawn_scaling(&a, velocity, D_L12_001A93F8[0], D_L12_001A93FC[0], ((s32)(math_random_int_range(10, 15)) * 5 + 2) / 6,
                      D_L12_001A9408[0], -10, 1);
    }

    switch (D_L12_001BDB00.event) {
    case 2:
        for (obj = D_L12_001B2E9C[0]; obj < D_L12_001B2EA4[0]; obj += 0x100) {
            int cls = *(short *)(obj + 0xAA);
            if (cls == 0x11EB || cls == 0x1F5 || cls == 0x326) {
                moby_mark_spawned(obj);
            }
        }
        break;
    case 0x603:
        D_L12_001B9CC0.fade = 0.5f;
        D_L12_001B9CC0.time = 37;
        D_L12_001B9CC0.flag = 0;
        moby_transform_joint_to_world(D_L12_001BDB00.objects[4], 0, &a);
        func_PAL_L00_003FB330(&a, 1, 25, 20, 20, 20, 45, 1, 0.666f, 20.0f, 1, 1, 0, 0);
        break;
    case 0x6F5:
        D_L12_001B9CC0.fade = 0.5f;
        D_L12_001B9CC0.time = 50;
        D_L12_001B9CC0.flag = 0;
        vec_scale_to_length(&a, &D_L12_001B9CC0.rot, 4.0f);
        FastVecAdd(&a, &a, &D_L12_001B9CC0.pos);
        vec_scale_to_length(&b, &D_L12_001B9CC0.rot, -1.0f);
        func_PAL_0032F3B8(D_L12_001BDB00.objects[2], &a, &b, 0.0f);
        break;
    case 0x8D2:
        D_L12_001B9CC0.fade = 0.5f;
        a.q = 0;
        a.f[0] = 4.0f;
        a.f[1] = -1.0f;
        a.f[2] = 1.0f;
        D_L12_001B9CC0.time = 37;
        D_L12_001B9CC0.flag = 0;
        matrix_mul_vec3(&a, &a, &D_L12_001B9CC0.rot);
        FastVecAdd(&a, &a, &D_L12_001B9CC0.pos);
        func_PAL_L00_003FB330(&a, 1, 25, 20, 20, 20, 45, 1, 0.666f, 20.0f, 1, 1, 0, 0);
        for (k = 24; k >= 0; k--) {
            qcopy(&b, &a);
            vec_add_random_offset(&b, 0.3f);
            FastVecSub(velocity, &b, &a);
            vec_scale_to_length(velocity, velocity, math_random_float_range(0.0f, 1.0f) * 0.020000001f);
            func_PAL_L00_00342480(&b, velocity, 250);
        }
        break;
    }
}
