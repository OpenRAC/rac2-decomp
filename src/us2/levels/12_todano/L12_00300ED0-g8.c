#include "include_asm.h"
#include "common.h"

/* func_US2_L12_00300ED0, the USA v2.00 copy of func_L12_00300410: the same C, with the event
   gate D_001A79F0 != 0x33 added to the class 0xFA0 test (as the PAL copies have it). The element
   address computed before the 0x18C offset spares loop.c one hoist, so 0xFA0 still moves in its
   first pass, ahead of the strength-reduced pointer, while 0x33 waits for the second. */

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
extern State g_trail_slice_state;

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
extern Scene g_hero_state_copy_a;

extern char *g_moby_list_start[] __attribute__((sda));
extern char *g_moby_list_end_alt[] __attribute__((sda));
extern int g_frame_l12_counter[] __attribute__((sda));
extern int g_current_map_index;
extern float g_scene_random_min __attribute__((sda));
extern float g_scene_random_max[] __attribute__((sda));
extern int g_scene_spawn_param_a __attribute__((sda));
extern int g_scene_spawn_param_g __attribute__((sda));
extern int g_scene_spawn_param_b[] __attribute__((sda));
extern int g_scene_spawn_param_c[] __attribute__((sda));
extern int g_scene_spawn_param_d[] __attribute__((sda));
extern int g_scene_spawn_param_e[] __attribute__((sda));
extern int g_scene_spawn_param_f[] __attribute__((sda));
extern int g_scene_spawn_param_i[] __attribute__((sda));
extern int g_scene_spawn_param_h[] __attribute__((sda));

extern void anim_start_startup_animations(void);
extern void func_US2_002E72D8(void *);
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

void func_US2_L12_00300ED0(void)
{
    V a, b, c, d;
    V *velocity;
    int i, j, k;
    char *obj;
    State *st;
    char **entries;

    anim_start_startup_animations();
    for (i = 0; i < g_trail_slice_state.count; i++) {
        char *slot = (char *)&g_trail_slice_state + i * 4;

        obj = *(char **)(slot + 0x18C);
        if (obj && *(short *)(obj + 0xAA) == 0xE29) {
            *(unsigned short *)(obj + 0x34) |= 0x800;
        }
        if (*(short *)(obj + 0xAA) == 0xD54) {
            func_US2_002E72D8(obj);
        }
        if (obj && *(short *)(obj + 0xAA) == 0xFA0 && g_current_map_index != 0x33) {
            char *p = *(char **)(obj + 0x68);
            if (p) {
                math_store_angle_update_result(obj, p + 0xC, 0x80AAAAD2, 0x80396464, 0.061086535f);
            }
        }
    }
    gfx_add_draw_callback_first(todano_refresh_scene_tuning, 0);

    st = &g_trail_slice_state;
    if (st->mode != 5) {
        return;
    }
    entries = st->emitters;
    velocity = &c;
    for (j = 1; j >= 0; j--) {
        char *emitter = *entries;

        moby_transform_joint_to_world(emitter, 3, &a);
        moby_transform_joint_to_world(emitter, 5, &b);
        lerp_vector(&a, &a, &b, 0.5f);
        d.q = 0;
        d.f[2] = -(math_random_float_range(g_scene_random_min, g_scene_random_max[0]) * 0.016666668f);
        c.q = d.q;
        if (g_frame_l12_counter[0] & 1) {
            part_spawn_scaling(&a, velocity, g_scene_spawn_param_a, g_scene_spawn_param_b[0], math_random_int_range(18, 22),
                          g_scene_spawn_param_g, -10, 1);
        } else {
            part_spawn_scaling(&a, velocity, g_scene_spawn_param_c[0], g_scene_spawn_param_d[0], math_random_int_range(20, 24),
                          g_scene_spawn_param_h[0], -10, 1);
        }
        entries++;
        part_spawn_scaling(&a, velocity, g_scene_spawn_param_e[0], g_scene_spawn_param_f[0], math_random_int_range(10, 15),
                      g_scene_spawn_param_i[0], -10, 1);
    }

    switch (g_trail_slice_state.event) {
    case 2:
        for (obj = g_moby_list_start[0]; obj < g_moby_list_end_alt[0]; obj += 0x100) {
            int cls = *(short *)(obj + 0xAA);
            if (cls == 0x11EB || cls == 0x1F5 || cls == 0x326) {
                moby_mark_spawned(obj);
            }
        }
        break;
    case 0x603:
        g_hero_state_copy_a.fade = 0.5f;
        g_hero_state_copy_a.time = 45;
        g_hero_state_copy_a.flag = 0;
        moby_transform_joint_to_world(g_trail_slice_state.objects[4], 0, &a);
        SpawnExplosion(&a, 1, 25, 20, 20, 20, 45, 1, 0.666f, 20.0f, 1, 1, 0, 0);
        break;
    case 0x6F5:
        g_hero_state_copy_a.fade = 0.5f;
        g_hero_state_copy_a.time = 60;
        g_hero_state_copy_a.flag = 0;
        vec_scale_to_length(&a, &g_hero_state_copy_a.rot, 4.0f);
        FastVecAdd(&a, &a, &g_hero_state_copy_a.pos);
        vec_scale_to_length(&b, &g_hero_state_copy_a.rot, -1.0f);
        part_spawn_blast_effect_moby(g_trail_slice_state.objects[2], &a, &b, 0.0f);
        break;
    case 0x8D2:
        g_hero_state_copy_a.fade = 0.5f;
        a.q = 0;
        a.f[0] = 4.0f;
        a.f[1] = -1.0f;
        a.f[2] = 1.0f;
        g_hero_state_copy_a.time = 45;
        g_hero_state_copy_a.flag = 0;
        matrix_mul_vec3(&a, &a, &g_hero_state_copy_a.rot);
        FastVecAdd(&a, &a, &g_hero_state_copy_a.pos);
        SpawnExplosion(&a, 1, 25, 20, 20, 20, 45, 1, 0.666f, 20.0f, 1, 1, 0, 0);
        for (k = 24; k >= 0; k--) {
            qcopy(&b, &a);
            vec_add_random_offset(&b, 0.3f);
            FastVecSub(velocity, &b, &a);
            vec_scale_to_length(velocity, velocity, math_random_float_range(0.0f, 1.0f) * 0.016666668f);
            part_l00_spawn_spinning(&b, velocity, 300);
        }
        break;
    }
}
