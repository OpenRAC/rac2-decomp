#include "names.h"
/* func_L23_0041A7A0 is a unit of its own: it mixes $gp and absolute accesses to the same globals
 * (MACRO_ADDR declarations), which would conflict with the declarations in L23_00416388-g8.c. */

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int g_energy_barrier_timer MACRO_ADDR;
extern float g_energy_barrier_level MACRO_ADDR;
extern float g_barrier_energy_reset __attribute__((sda));
extern float g_barrier_energy_delta __attribute__((sda));
extern int g_beam_frame_count __attribute__((sda));
extern int g_mothership_beam_light __attribute__((sda));
extern int g_barrier_release_effects_flag __attribute__((sda));
extern int g_mothership_barrier_voice __attribute__((sda));
extern float g_barrier_energy_max __attribute__((sda));
extern short g_mothership_barrier_light __attribute__((sda));
extern float g_barrier_random_turn_degrees __attribute__((sda));
extern float g_barrier_surface_radius __attribute__((sda));
extern float g_boss_arena_radius __attribute__((sda));
extern float g_barrier_timer_threshold __attribute__((sda));
extern float g_barrier_cam_effect_param __attribute__((sda));
extern unsigned char g_barrier_trail_red __attribute__((sda));
extern unsigned char g_barrier_trail_green __attribute__((sda));
extern float g_barrier_trail_width_a __attribute__((sda));
extern float g_barrier_trail_width_b __attribute__((sda));
extern float g_barrier_trail_length_a __attribute__((sda));
extern float g_barrier_trail_length_b __attribute__((sda));
extern short g_barrier_trail_alpha_a __attribute__((sda));
extern short g_barrier_trail_alpha_b __attribute__((sda));
extern int g_barrier_trail_life_a __attribute__((sda));
extern int g_barrier_trail_life_b __attribute__((sda));
extern unsigned char g_barrier_trail2_red __attribute__((sda));
extern unsigned char g_barrier_trail2_green __attribute__((sda));
extern float g_barrier_trail2_width_a __attribute__((sda));
extern float g_barrier_trail2_width_b __attribute__((sda));
extern float g_barrier_trail2_length_a __attribute__((sda));
extern float g_barrier_trail2_length_b __attribute__((sda));
extern short g_barrier_trail2_alpha_a __attribute__((sda));
extern short g_barrier_trail2_alpha_b __attribute__((sda));
extern int g_barrier_trail2_life_a __attribute__((sda));
extern int g_barrier_trail2_life_b __attribute__((sda));
extern Quad g_energy_barrier_origin MACRO_ADDR;
extern Quad g_energy_barrier_joint_positions[4] MACRO_ADDR;
extern Quad g_boss_target_pos_a MACRO_ADDR;
extern char *g_mothership_effect_handles[4] MACRO_ADDR;
extern float g_mothership_surface_radius;
extern char *g_mothership_beam_end_handles[8][3];
extern int g_mothership_beam_handles[8][3];
extern Quad g_mothership_barrier_points[8][3];
struct PlayerView {
    unsigned char pad[0x80];
    Quad position;
    unsigned char gap[0x2200];
    char *object;
};
extern struct PlayerView g_hero_state;
extern int math_fast_float_d(int *);
extern float math_fabs(float);
extern int PlayMobySound(int, int, char *);
extern void mothership_restart_beam_effect(char *);
extern void gfx_free_point_light(int);
extern void mothership_release_effect_handles(char *);
extern float math_random_float_range(float, float);
extern int part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);
extern void mothership_project_point_onto_surface(char *, float);
extern float FastAddRotations(float, float);
extern void euler_rotation_basis(char *, char *);
extern void multiply_matrix3x3(char *, char *, char *);
extern void FastVecScale(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern void mothership_spawn_field_beam_segments(char *, char *, char *, Quad *, int *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void *ribbon_trail_create(unsigned char *, unsigned char *, unsigned char *, unsigned char, unsigned char, short, short, float, float, float, float, int, int, int, int, int);
extern float fast_vec_dist(char *, char *);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void cam_play_effect_on_target(unsigned char *, int, int, Quad *, float *, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern int math_random_int_range(int, int);
extern int CollLine(void *, void *, int, void *, void *);

/* Update the radial field, its linked effects and player contact response. */
void mothership_update_energy_barrier(char *object) {
    struct {
        Quad vertex[8], scaled[2], axes[3], euler, matrix[3], blast, position;
    } local;
    struct HitView {
        Quad result;
        char *owner;
        unsigned int flags;
        unsigned char kind, mode;
        unsigned short ownerClass;
        float radius;
        int value;
    } hit;
    char *state = *(char **)(object + 0x68);
    float x, y, z, random;
    int i, j, contactIndex;
    if (*(int *)(state + 0x5B0) == 0) {
        g_energy_barrier_level = g_barrier_energy_reset;
        g_barrier_energy_delta = math_fabs(g_barrier_energy_delta);
        g_energy_barrier_timer = g_beam_frame_count;
        PlayMobySound(5, 0, object);
    } else {
        if (g_energy_barrier_timer) {
            math_fast_float_d(&g_energy_barrier_timer);
            mothership_restart_beam_effect(object);
        } else {
            if (g_mothership_beam_light != -1) gfx_free_point_light(g_mothership_beam_light);
        }
        if (g_energy_barrier_timer < g_beam_frame_count / 2) {
            g_energy_barrier_level = g_energy_barrier_level + g_barrier_energy_delta;
            if (g_barrier_energy_max < g_energy_barrier_level) g_energy_barrier_level = g_barrier_energy_max;
        }
    }
    if (g_barrier_release_effects_flag) mothership_release_effect_handles(object);
    if (g_mothership_barrier_voice == -1) g_mothership_barrier_voice = PlayMobySound(1, 4, object);
    if (g_barrier_energy_max * 0.5f < g_energy_barrier_level) {
        char *joint;
        if (g_mothership_barrier_light != -1) gfx_free_point_light(g_mothership_barrier_light);
        joint = state + 0x3E0;
        x = math_random_float_range(0.0f, 0.5f) + 0.7f;
        y = math_random_float_range(0.0f, 0.5f) + 1.0f;
        z = math_random_float_range(0.0f, 0.55f) + 1.0f;
        g_mothership_barrier_light = part_l00_alloc_effect_slot_2(joint, 35.0f, 0.0f, x, y, z);
    }
    *(int *)(state + 0x5B0) = 1;
    qcopy_nc(&g_energy_barrier_origin,object+16);
    mothership_project_point_onto_surface((char *)&g_energy_barrier_origin, g_barrier_surface_radius);
    qcopy_nc(&local.axes[0],(object + 0xC0));
    qcopy_nc(&local.axes[1],(object + 0xD0));
    qcopy_nc(&local.axes[2],(object + 0xE0));
    random = math_random_float_range(0.98f, 1.02f);
    *(float *)(state + 0x380) = FastAddRotations(*(float *)(state + 0x380), g_barrier_random_turn_degrees * random * 0.00029088825f);
    qzero_nc(&local.euler);
    ((float *)&local.euler)[2] = *(float *)(state + 0x380);
    euler_rotation_basis((char *)local.matrix, (char *)&local.euler);
    multiply_matrix3x3((char *)local.axes, (char *)local.axes, (char *)local.matrix);
    qcopy_nc(&local.scaled[0],&local.axes[0]);
    qcopy_nc(&local.scaled[1],&local.axes[1]);
    FastVecScale((char *)&local.scaled[0], (char *)&local.scaled[0], g_mothership_surface_radius);
    FastVecScale((char *)&local.scaled[1], (char *)&local.scaled[1], g_mothership_surface_radius);
    qcopy_nc(&local.vertex[0],&local.scaled[0]);
    FastVecScale((char *)&local.vertex[4], (char *)&local.vertex[0], -1.0f);
    FastVecAdd((char *)&local.vertex[1], (char *)&local.scaled[0], (char *)&local.scaled[1]);
    FastVecScale((char *)&local.vertex[1], (char *)&local.vertex[1], 0.5f);
    qcopy_nc(&local.vertex[2],&local.scaled[1]);
    FastVecAdd((char *)&local.vertex[3], (char *)&local.scaled[1], (char *)&local.vertex[4]);
    FastVecScale((char *)&local.vertex[3], (char *)&local.vertex[3], 0.5f);
    FastVecScale((char *)&local.vertex[5], (char *)&local.vertex[1], -1.0f);
    FastVecScale((char *)&local.vertex[6], (char *)&local.vertex[2], -1.0f);
    FastVecScale((char *)&local.vertex[7], (char *)&local.vertex[3], -1.0f);
    for (i = 0; i < 8; i++) {
        FastVecAdd((char *)&local.vertex[i], (char *)&local.vertex[i], (char *)&g_energy_barrier_origin);
        mothership_project_point_onto_surface((char *)&local.vertex[i], g_barrier_surface_radius);
        mothership_spawn_field_beam_segments(object, (char *)&g_energy_barrier_origin, (char *)&local.vertex[i], g_mothership_barrier_points[i], g_mothership_beam_handles[i]);
    }
    for (i = 0; i < 4; i++) {
        moby_transform_joint_to_world(object, i + 26, (char *)&g_energy_barrier_joint_positions[i]);
        if (!g_mothership_effect_handles[i]) g_mothership_effect_handles[i] = ribbon_trail_create(
            (unsigned char *)&g_energy_barrier_origin, (unsigned char *)object, (unsigned char *)&g_energy_barrier_joint_positions[i],
            g_barrier_trail2_red, g_barrier_trail2_green, g_barrier_trail2_alpha_a, g_barrier_trail2_alpha_b,
            g_barrier_trail2_width_a, g_barrier_trail2_width_b, g_barrier_trail2_length_a, g_barrier_trail2_length_b, g_barrier_trail2_life_a, g_barrier_trail2_life_b, 0, -1, 0);
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 3; j++) {
            if (!g_mothership_beam_end_handles[i][j]) {
                if (i == 0) g_mothership_beam_end_handles[0][j] = ribbon_trail_create(
                    (unsigned char *)&g_mothership_barrier_points[7][j], (unsigned char *)object, (unsigned char *)&g_mothership_barrier_points[0][j],
                    g_barrier_trail_red, g_barrier_trail_green, g_barrier_trail_alpha_a, g_barrier_trail_alpha_b,
                    g_barrier_trail_width_a, g_barrier_trail_width_b, g_barrier_trail_length_a, g_barrier_trail_length_b, g_barrier_trail_life_a, g_barrier_trail_life_b, 1, -1, 1);
                else g_mothership_beam_end_handles[i][j] = ribbon_trail_create(
                    (unsigned char *)&g_mothership_barrier_points[i - 1][j], (unsigned char *)object, (unsigned char *)&g_mothership_barrier_points[i][j],
                    g_barrier_trail_red, g_barrier_trail_green, g_barrier_trail_alpha_a, g_barrier_trail_alpha_b,
                    g_barrier_trail_width_a, g_barrier_trail_width_b, g_barrier_trail_length_a, g_barrier_trail_length_b, g_barrier_trail_life_a, g_barrier_trail_life_b, 1, -1, 1);
            }
        }
    }
    if (g_energy_barrier_level != g_barrier_energy_max) return;
    if (fast_vec_dist((char *)&g_hero_state.position, (char *)&g_boss_target_pos_a) < g_boss_arena_radius) {
        if ((*(float *)(state + 0x5C0) < g_barrier_timer_threshold) && !*(int *)(state + 0x5C4)) {
            FastVecScale((char *)&local.blast, g_hero_state.object + 0xE0, 3.0f);
            FastVecAdd((char *)&local.blast, (char *)&local.blast, (char *)&g_hero_state.position);
            SpawnExplosion(&local.blast, 1, 35, 20, 20, 15, 25, 1, 2.5f, 20.0f, 0, 1, 0, 0);
            local.position = *(Quad *)(object + 16);
            cam_play_effect_on_target((unsigned char *)object, 3, (int)g_barrier_cam_effect_param, &local.position, 0, 1);
            *(int *)(state + 0x5C4) = 25;
            snd_play_from_class_bank(2, 0, g_hero_state.object, 0xF7F);
        }
    }
    if (*(int *)(state + 0x5C4)) math_fast_float_d((int *)(state+0x5C4));
    i = math_random_int_range(1, 4);
    if ((*(unsigned short *)(object + 0x96) & ((1U << i) - 1)) == 0) {
        hit.owner = object;
        hit.flags = 0x8B0000;
        hit.radius = 10.0f;
        hit.value = 0;
        hit.kind = 3;
        hit.mode = 3;
        hit.ownerClass = *(unsigned short *)(object + 0xAA);
        /* contactIndex + -1, not - 1: the negative index wraps in sizetype, so table-16 stays its own
         * constant and cse does not rebuild it from the table address (use_related_value). */
        for (contactIndex = 1; contactIndex < 3; contactIndex++) {
            CollLine(&g_mothership_barrier_points[0][contactIndex + -1], &g_mothership_barrier_points[0][contactIndex], 0, 0, &hit);
        }
    }
}
