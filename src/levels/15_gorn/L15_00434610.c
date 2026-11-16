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
extern char *SpawnFreeLevelObjectById(int, int);
extern int moby_process_collision_hit(void *, int, int, int);
extern int follower_has_reached_target(void *);
extern void follower_set_state(void *, int);
extern void moby_update_movement_state(void *);
extern int math_fast_helper_a(void *, float);
extern int CollLine(void *, void *, int, void *, int);
extern void snd_stop_voice(int);
extern void mat_get_euler_angles(void *, void *);
/* Returns a pointer (src/levels/shared/L05_003D33E8.c); this caller ignores it, but the
   call must still set $v0 for local-alloc to give the joint-table base $v0. */
extern char *part_spawn_shockwave_burst(void *, int, int, float, int, int, int, int, int, int, int, int);
extern void gorn_ship_aim_parts(char *);
extern void gorn_path_mover_fire_shots(char *);
extern void part_l15_spawn_exhaust(void *);
extern void SpawnLinkedPart(void *, int);
extern void gorn_ship_spawn_damage_effects(void *);

/* Updates the Gorn enemy ship while it flies its route: fires shots, reacts to hits and shows damage as it loses parts. */
void gorn_ship_update_flight(char *object, int flag) {
    float up[4], point[4], matrix[16];
    char *vars = *(char **)(object + 0x68);
    GornOwner *owner;
    char *shot, *shot_vars, *route, *entry;
    int i, j, route_index, parts_left, sound;
    *(GornQuad *)up = 0;
    up[2] = 1.0f;
    owner = (GornOwner *)moby_get_motion_data((unsigned char *)object);
    owner->flag11C = 1;
    owner->target = g_moby_base + (*(int *)(vars + 0x260) << 8);
    if (math_fast_float_d(vars + 0x444)) {
        *(int *)(vars + 0x444) = 300;
        for (i = *(int *)(vars + 0x440) * 3; i < *(int *)(vars + 0x440) * 3 + 3; i++) {
            qcopy_nc(point, g_ship_route_points + i * 16);
            matrix_mul_vec3(point, point, object + 0xC0);
            FastVecAdd(point, point, object + 0x10);
            shot = SpawnFreeLevelObjectById(0x957 /* moby class 2391 */, 1);
            if (shot) {
                shot_vars = (char *)moby_get_motion_data((unsigned char *)shot);
                qcopy_nc(shot + 0x10, point);
                vec_scale_to_length(shot + 0xC0, object + 0xD0, *(int *)(vars + 0x440) ? -1.0f : 1.0f);
                qcopy_nc(shot_vars + 0x90, shot + 0xC0);
                FastVecCross(shot + 0xD0, shot + 0xC0, up);
                vec_scale_to_length(shot + 0xD0, shot + 0xD0, 1.0f);
                FastVecCross(shot + 0xE0, shot + 0xD0, shot + 0xC0);
                FastVecScale(shot_vars + 0x60, shot + 0xC0, 10.0f);
                FastVecAdd(shot_vars + 0x60, shot + 0x10, shot_vars + 0x60);
                *(int *)(shot_vars + 0x130) = 500;
            }
        }
        *(int *)(vars + 0x440) ^= 1;
    }
    if (*(int *)(vars + 0x264)) {
        for (j = 0; j < 6; j++) {
            qcopy_nc(point, g_ship_route_points + j * 16);
            matrix_mul_vec3(point, point, object + 0xC0);
            FastVecAdd(point, point, object + 0x10);
        }
    }
    gorn_ship_aim_parts(object);
    route = g_path_l15_table[*(int *)(vars + 0x448)];
    if (follower_has_reached_target(object)) {
        route_index = *(int *)(vars + 0x44C);
        *(int *)(vars + 0x44C) = route_index + 1;
        follower_set_push_vector(object, route + 16 + route_index * 16);
        owner->timer = 2000000;
        if (*(int *)(vars + 0x44C) >= *(int *)route) *(int *)(vars + 0x44C) = 0;
    }
    follower_set_state(object, 2);
    moby_update_movement_state(object);
    qcopy_nc(point, object + 0x10);
    point[3] = *(float *)(object + 0xC) * 0.0009765599970705807f;
    if (math_fast_helper_a(point, 100.0f) != -1 &&
        CollLine(object + 0x10, owner->target + 0x10, 0, object, 0) &&
        g_line_hit_result[0] && *(short *)(g_line_hit_result[0] + 0xAA) == *(short *)(owner->target + 0xAA))
        gorn_path_mover_fire_shots(object);
    if (math_fast_helper_a(point, 192.0f) != -1 && (unsigned char)object[0x20] != 2)
        part_l15_spawn_exhaust(object);
    if (!flag && moby_process_collision_hit(object, 1, 1, 1)) {
        object[0x20] = 6;
        PlayMobySound(1, 0, object);
        sound = *(int *)(vars + 0x458);
        if (sound != -1) {
            entry = (char *)(g_sound_state + sound * 0x70);
            if (*(char **)(entry + 0x88) == object && *(unsigned char *)(entry + 0x74)) snd_stop_voice(sound);
        }
        *(int *)(vars + 0x458) = -1;
        qcopy_nc(matrix, object + 0xC0);
        qcopy_nc(matrix + 4, object + 0xD0);
        qcopy_nc(matrix + 8, object + 0xE0);
        mat_get_euler_angles(matrix, vars + 0x400);
    }
    if ((unsigned char)object[0x20] == 4) {
        if (*(float *)(vars + 0x180) <= 400.0f) {
            *(int *)(vars + 0x268) = 0;
            if (!*(int *)(vars + 0x45C)) {
                PlayMobySound(4, 0, object);
                *(int *)(vars + 0x45C) = 1;
            }
            parts_left = FloatToInt(*(float *)(vars + 0x180) * 0.02f);
            if (parts_left < 7 && parts_left != *(int *)(vars + 0x26C)) {
                part_spawn_shockwave_burst(object + 0x10, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                moby_transform_joint_to_world(object, g_gorn_ship_part_joints[7-parts_left], matrix);
                part_spawn_shockwave_burst(matrix, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                SpawnLinkedPart(object, parts_left-1);
            }
            gorn_ship_spawn_damage_effects(object);
            *(int *)(vars + 0x26C) = parts_left;
            if (parts_left > 0) *(short *)(object + 0x7C) = (1 << (parts_left-1)) - 1;
            else *(short *)(object + 0x7C) = 0;
        }
    }
    else {
        if (*(float *)(vars + 0x180) <= 100.0f) {
            *(int *)(vars + 0x268) = 0;
            if (!*(int *)(vars + 0x45C)) {
                PlayMobySound(4, 0, object);
                *(int *)(vars + 0x45C) = 1;
            }
            parts_left = FloatToInt(*(float *)(vars + 0x180) * 0.08f);
            if (parts_left < 7 && parts_left != *(int *)(vars + 0x26C)) {
                part_spawn_shockwave_burst(object + 0x10, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                moby_transform_joint_to_world(object, g_gorn_ship_part_joints[7-parts_left], matrix);
                part_spawn_shockwave_burst(matrix, 0, 50, 2.5f, 30, 30, 30, 40, 1, 1, 0, 0);
                SpawnLinkedPart(object, parts_left-1);
            }
            gorn_ship_spawn_damage_effects(object);
            *(int *)(vars + 0x26C) = parts_left;
            if (parts_left > 0) *(short *)(object + 0x7C) = (1 << (parts_left-1)) - 1;
            else *(short *)(object + 0x7C) = 0;
        }
    }
}
