#include "include_asm.h"


#include "common.h"
typedef int GornQuad __attribute__((mode(TI)));
extern char *g_path_l15_table[];
extern char *moby_get_motion_data(unsigned char *);
extern int math_fast_float_d(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void follower_set_push_vector(void *, void *);
extern int FloatToInt(float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecCross(void *, void *, void *);
extern int PlayMobySound(int, int, void *);
extern char *g_moby_base __attribute__((sda));
typedef struct GornOwner {
    char pad00[0x11C];
    int flag11C;
    char *target;
    char pad124[0xC];
    int timer;
} GornOwner;
extern char g_ship_route_points[];
extern char *g_line_hit_result[];
extern int g_gorn_ship_part_joints[] SDATA(D_L15_001B17B0);
extern u8 g_sound_state[];
extern char *SpawnFreeLevelObjectById_pal(int, int);
extern int moby_process_collision_hit(void *, int, int, int);
extern int follower_has_reached_target(void *);
extern void follower_set_state(void *, int);
extern void follower_l05_update_pal(void *);
extern int math_fast_helper_a(void *, float);
extern int CollLine(void *, void *, int, void *, int);
extern void snd_stop_voice(int);
extern void mat_get_euler_angles(void *, void *);
extern char *moby_spawn_large_explosion_pal(void *, int, int, float, int, int, int, int, int, int, int, int);
extern void gorn_ship_aim_parts(char *);
extern void gorn_ship_fire_double_shot_pal(char *);
extern void gorn_ship_spawn_exhaust_particles_pal(void *);
extern void gorn_spawn_linked_part_pal(void *, int);
extern void gorn_ship_spawn_damage_effects(void *);

/* Updates the Gorn enemy ship while it flies its route: fires shots, reacts to hits and shows damage as it loses parts. (PAL: 50 Hz timings) */
void gorn_ship_update_flight_pal(char *object, int flag) {
    float up_vec[4], point[4], matrix[16];
    char *state = *(char **)(object + 0x68);
    GornOwner *owner;
    char *spawn, *spawn_motion, *route, *entry;
    int i, j, next_index, damage_level, sound;
    *(GornQuad *)up_vec = 0;
    up_vec[2] = 1.0f;
    owner = (GornOwner *)moby_get_motion_data((unsigned char *)object);
    owner->flag11C = 1;
    owner->target = g_moby_base + (*(int *)(state + 0x260) << 8);
    if (math_fast_float_d(state + 0x444)) {
        *(int *)(state + 0x444) = 250;
        for (i = *(int *)(state + 0x440) * 3; i < *(int *)(state + 0x440) * 3 + 3; i++) {
            qcopy_nc(point, g_ship_route_points + i * 16);
            matrix_mul_vec3(point, point, object + 0xC0);
            FastVecAdd(point, point, object + 0x10);
            spawn = SpawnFreeLevelObjectById_pal(0x957, 1);
            if (spawn) {
                spawn_motion = (char *)moby_get_motion_data((unsigned char *)spawn);
                qcopy_nc(spawn + 0x10, point);
                vec_scale_to_length(spawn + 0xC0, object + 0xD0, *(int *)(state + 0x440) ? -1.0f : 1.0f);
                qcopy_nc(spawn_motion + 0x90, spawn + 0xC0);
                FastVecCross(spawn + 0xD0, spawn + 0xC0, up_vec);
                vec_scale_to_length(spawn + 0xD0, spawn + 0xD0, 1.0f);
                FastVecCross(spawn + 0xE0, spawn + 0xD0, spawn + 0xC0);
                FastVecScale(spawn_motion + 0x60, spawn + 0xC0, 10.0f);
                FastVecAdd(spawn_motion + 0x60, spawn + 0x10, spawn_motion + 0x60);
                *(int *)(spawn_motion + 0x130) = 417;
            }
        }
        *(int *)(state + 0x440) ^= 1;
    }
    if (*(int *)(state + 0x264)) {
        for (j = 0; j < 6; j++) {
            qcopy_nc(point, g_ship_route_points + j * 16);
            matrix_mul_vec3(point, point, object + 0xC0);
            FastVecAdd(point, point, object + 0x10);
        }
    }
    gorn_ship_aim_parts(object);
    route = g_path_l15_table[*(int *)(state + 0x448)];
    if (follower_has_reached_target(object)) {
        next_index = *(int *)(state + 0x44C);
        *(int *)(state + 0x44C) = next_index + 1;
        follower_set_push_vector(object, route + 16 + next_index * 16);
        owner->timer = 1666667;
        if (*(int *)(state + 0x44C) >= *(int *)route) *(int *)(state + 0x44C) = 0;
    }
    follower_set_state(object, 2);
    follower_l05_update_pal(object);
    qcopy_nc(point, object + 0x10);
    point[3] = *(float *)(object + 0xC) * 0.0009765599970705807f;
    if (math_fast_helper_a(point, 100.0f) != -1 &&
        CollLine(object + 0x10, owner->target + 0x10, 0, object, 0) &&
        g_line_hit_result[0] && *(short *)(g_line_hit_result[0] + 0xAA) == *(short *)(owner->target + 0xAA))
        gorn_ship_fire_double_shot_pal(object);
    if (math_fast_helper_a(point, 192.0f) != -1 && (unsigned char)object[0x20] != 2)
        gorn_ship_spawn_exhaust_particles_pal(object);
    if (!flag && moby_process_collision_hit(object, 1, 1, 1)) {
        object[0x20] = 6;
        PlayMobySound(1, 0, object);
        sound = *(int *)(state + 0x458);
        if (sound != -1) {
            entry = (char *)(g_sound_state + sound * 0x70);
            if (*(char **)(entry + 0x88) == object && *(unsigned char *)(entry + 0x74)) snd_stop_voice(sound);
        }
        *(int *)(state + 0x458) = -1;
        qcopy_nc(matrix, object + 0xC0);
        qcopy_nc(matrix + 4, object + 0xD0);
        qcopy_nc(matrix + 8, object + 0xE0);
        mat_get_euler_angles(matrix, state + 0x400);
    }
    if ((unsigned char)object[0x20] == 4) {
        if (*(float *)(state + 0x180) <= 400.0f) {
            *(int *)(state + 0x268) = 0;
            if (!*(int *)(state + 0x45C)) {
                PlayMobySound(4, 0, object);
                *(int *)(state + 0x45C) = 1;
            }
            damage_level = FloatToInt(*(float *)(state + 0x180) * 0.02f);
            if (damage_level < 7 && damage_level != *(int *)(state + 0x26C)) {
                moby_spawn_large_explosion_pal(object + 0x10, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                moby_transform_joint_to_world(object, g_gorn_ship_part_joints[7-damage_level], matrix);
                moby_spawn_large_explosion_pal(matrix, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                gorn_spawn_linked_part_pal(object, damage_level-1);
            }
            gorn_ship_spawn_damage_effects(object);
            *(int *)(state + 0x26C) = damage_level;
            if (damage_level > 0) *(short *)(object + 0x7C) = (1 << (damage_level-1)) - 1;
            else *(short *)(object + 0x7C) = 0;
        }
    }
    else {
        if (*(float *)(state + 0x180) <= 100.0f) {
            *(int *)(state + 0x268) = 0;
            if (!*(int *)(state + 0x45C)) {
                PlayMobySound(4, 0, object);
                *(int *)(state + 0x45C) = 1;
            }
            damage_level = FloatToInt(*(float *)(state + 0x180) * 0.08f);
            if (damage_level < 7 && damage_level != *(int *)(state + 0x26C)) {
                moby_spawn_large_explosion_pal(object + 0x10, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                moby_transform_joint_to_world(object, g_gorn_ship_part_joints[7-damage_level], matrix);
                moby_spawn_large_explosion_pal(matrix, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                gorn_spawn_linked_part_pal(object, damage_level-1);
            }
            gorn_ship_spawn_damage_effects(object);
            *(int *)(state + 0x26C) = damage_level;
            if (damage_level > 0) *(short *)(object + 0x7C) = (1 << (damage_level-1)) - 1;
            else *(short *)(object + 0x7C) = 0;
        }
    }
}

