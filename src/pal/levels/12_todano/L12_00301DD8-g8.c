#include "names.h"
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
extern int g_current_map_index[] __attribute__((sda));
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
extern void update_equipment_pieces_pal(void *);
extern void math_store_angle_update_result(void *, void *, unsigned int, unsigned int, float);
extern void gfx_add_draw_callback_first(void (*)(void), void *);
extern void todano_refresh_scene_tuning(void);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void lerp_vector(void *, void *, void *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern char *part_spawn_scaling(void *, void *, unsigned int, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *part_spawn_blast_effect_moby_pal(void *, void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_add_random_offset(void *, float);
extern void FastVecSub(void *, void *, void *);
extern unsigned char *part_l00_spawn_spinning_pal(void *, void *, int);

void todano_scene_update_events_pal(void)
{
    V point_a, point_b, vel_vec, vel_tmp;
    V *velocity;
    int i, emitter_index, spark_index;
    char *moby;
    State *state;
    char **emitter_list;

    anim_start_startup_animations();
    for (i = 0; i < g_trail_slice_state.count; i++) {
        moby = ((State *)((char *)&g_trail_slice_state + i * 4))->objects[0];
        if (moby && *(short *)(moby + 0xAA) == 0xE29) {
            *(unsigned short *)(moby + 0x34) |= 0x800;
        }
        if (*(short *)(moby + 0xAA) == 0xD54) {
            update_equipment_pieces_pal(moby);
        }
        if (moby && *(short *)(moby + 0xAA) == MOBY_CLASS_TV_SCREENS && g_current_map_index[0] != 0x33) {
            char *anim_state = *(char **)(moby + 0x68);
            if (anim_state) {
                math_store_angle_update_result(moby, anim_state + 0xC, 0x80AAAAD2, 0x80396464, 0.07330384f);
            }
        }
    }
    gfx_add_draw_callback_first(todano_refresh_scene_tuning, 0);

    state = &g_trail_slice_state;
    if (state->mode != 5) {
        return;
    }
    emitter_list = state->emitters;
    velocity = &vel_vec;
    for (emitter_index = 0; emitter_index < 2; emitter_index++) {
        char *emitter_moby = *emitter_list;

        moby_transform_joint_to_world(emitter_moby, 3, &point_a);
        moby_transform_joint_to_world(emitter_moby, 5, &point_b);
        lerp_vector(&point_a, &point_a, &point_b, 0.5f);
        vel_tmp.q = 0;
        vel_tmp.f[2] = -(math_random_float_range(g_scene_random_min, g_scene_random_max[0]) * 0.020000001f);
        vel_vec.q = vel_tmp.q;
        if (g_frame_l12_counter[0] & 1) {
            part_spawn_scaling(&point_a, velocity, g_scene_spawn_param_a, g_scene_spawn_param_b[0], ((s32)(math_random_int_range(18, 22)) * 5 + 2) / 6,
                          g_scene_spawn_param_g, -10, 1);
        } else {
            part_spawn_scaling(&point_a, velocity, g_scene_spawn_param_c[0], g_scene_spawn_param_d[0], ((s32)(math_random_int_range(20, 24)) * 5 + 2) / 6,
                          g_scene_spawn_param_h[0], -10, 1);
        }
        emitter_list++;
        part_spawn_scaling(&point_a, velocity, g_scene_spawn_param_e[0], g_scene_spawn_param_f[0], ((s32)(math_random_int_range(10, 15)) * 5 + 2) / 6,
                      g_scene_spawn_param_i[0], -10, 1);
    }

    switch (g_trail_slice_state.event) {
    case 2:
        for (moby = g_moby_list_start[0]; moby < g_moby_list_end_alt[0]; moby += 0x100) {
            int class_id = *(short *)(moby + 0xAA);
            if (class_id == 0x11EB || class_id == MOBY_CLASS_NANOTECH_CRATE || class_id == 0x326) {
                moby_mark_spawned(moby);
            }
        }
        break;
    case 0x603:
        g_hero_state_copy_a.fade = 0.5f;
        g_hero_state_copy_a.time = 37;
        g_hero_state_copy_a.flag = 0;
        moby_transform_joint_to_world(g_trail_slice_state.objects[4], 0, &point_a);
        SpawnExplosion_pal(&point_a, 1, 25, 20, 20, 20, 45, 1, 0.666f, 20.0f, 1, 1, 0, 0);
        break;
    case 0x6F5:
        g_hero_state_copy_a.fade = 0.5f;
        g_hero_state_copy_a.time = 50;
        g_hero_state_copy_a.flag = 0;
        vec_scale_to_length(&point_a, &g_hero_state_copy_a.rot, 4.0f);
        FastVecAdd(&point_a, &point_a, &g_hero_state_copy_a.pos);
        vec_scale_to_length(&point_b, &g_hero_state_copy_a.rot, -1.0f);
        part_spawn_blast_effect_moby_pal(g_trail_slice_state.objects[2], &point_a, &point_b, 0.0f);
        break;
    case 0x8D2:
        g_hero_state_copy_a.fade = 0.5f;
        point_a.q = 0;
        point_a.f[0] = 4.0f;
        point_a.f[1] = -1.0f;
        point_a.f[2] = 1.0f;
        g_hero_state_copy_a.time = 37;
        g_hero_state_copy_a.flag = 0;
        matrix_mul_vec3(&point_a, &point_a, &g_hero_state_copy_a.rot);
        FastVecAdd(&point_a, &point_a, &g_hero_state_copy_a.pos);
        SpawnExplosion_pal(&point_a, 1, 25, 20, 20, 20, 45, 1, 0.666f, 20.0f, 1, 1, 0, 0);
        for (spark_index = 24; spark_index >= 0; spark_index--) {
            qcopy(&point_b, &point_a);
            vec_add_random_offset(&point_b, 0.3f);
            FastVecSub(velocity, &point_b, &point_a);
            vec_scale_to_length(velocity, velocity, math_random_float_range(0.0f, 1.0f) * 0.020000001f);
            part_l00_spawn_spinning_pal(&point_b, velocity, 250);
        }
        break;
    }
}
