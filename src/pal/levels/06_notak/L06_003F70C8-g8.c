#include "names.h"
/* func_PAL_L06_003F70C8, the PAL copy of func_L06_003F3800: the same C, where the launch timer is
 * scaled for 50 Hz and the launch speed and gravity constants change.  slot is declared at its first
 * use: its later pseudo number gives the gcse buckets, and so the spill slots, retail's order. */
#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));
extern void spawner_update_damage_timer_pal(char *, char *);
extern int FastDecTimer(void *);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern int FindHeroOrMobyTarget(void *, void *, void *, int, void *, int, float);
extern int flock_count_members_find_free(void *, void *);
extern char *g_path_list[];
extern char *g_region_table __attribute__((sda));
extern int g_game_l06_frame_counter __attribute__((sda));
extern Vector g_hero_position;
extern Vector g_hero_l06_position;
extern char g_effect_vector[] MACRO_ADDR;
extern float fast_vec_dist(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_fast_divide_helper(void *, void *, float);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void math_random_planar_offset(void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_add_random_offset(float *, float);
extern float weapon_compute_shot_launch_speed(void *, void *, int, float, float);
extern char *flock_create_member_pal(void *, void *, void *, int, int);
extern int PlayMobySound(int, int, void *);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float,
                         int, float, int, int, int, int, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void *part_spawn_flying_fragment(void *, int, void *, void *, int, int, float, void *, void *, void *);
extern void moby_mark_spawned(void *);
extern int GetFirstMobyInGroup(void *, int, int, int);
extern void moby_update_ground_check(void *);

/* regions[] holds indices into the 0x80-byte region table at D_L06_001B290C,
 * -1 for an empty slot. */
typedef struct {
    char pad[0x90];
    int regions[4];
    char *children[20];
} SpawnerSlots;

/* Select a spawn point, launch a child and retire the spawner when destroyed. */
void spawner_moby_update_pal(char *moby)
{
    Vector point, delta, origin, step;
    char *region;
    void *anchor;
    int has_anchor;
    char *path_points;
    int path_count;
    char *path;
    char *target;
    int first;
    char *state = *(char **)(moby + 0x68);

    spawner_update_damage_timer_pal(moby, state);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0: {
        char *child;
        if (g_game_l06_frame_counter) {
            child = 0;
            while (!GetFirstMobyInGroup(&child, *(int *)(state + 0x84), 0, 0))
                moby_mark_spawned(child);
            *(unsigned char *)(moby + 0x20) = 1;
        }
        break;
    }
    case 1: {
        spawner_update_damage_timer_pal(moby, state);
        if (!FastDecTimer(state + 0x7E))
            break;
        if (!math_random_int_below(7)) {
            anchor = 0;
            has_anchor = 0;
            path_points = 0;
            path_count = 0;
            if (*(int *)(state + 0x74) != -1) {
                anchor = state + 0x74;
                has_anchor = 1;
            }
            if (*(int *)(state + 0x78) != -1) {
                path = g_path_list[*(int *)(state + 0x78)];
                path_points = path + 0x10;
                path_count = *(int *)path;
            }
            FindHeroOrMobyTarget(moby, state + 0xF0, anchor, has_anchor,
                             path_points, path_count,
                             *(float *)(state + 0x70));
        } else {
            target = *(char **)(state + 0x130);
            if (target && *(unsigned char *)(target + 0x20) != 0xFE &&
                *(unsigned char *)(target + 0x20) != 0xFD) {
                qcopy((state + 0xF0), (target + 0x10));
            } else {
                *(int *)(state + 0x130) = 0;
                *(int *)(state + 0x134) = 2;
            }
        }
        if (*(int *)(state + 0x134) == 2)
            break;
        {
            int slot = flock_count_members_find_free(moby, state);
            if (*(unsigned char *)(state + 0x81) >= *(unsigned char *)(state + 0x80) || slot == -1)
                break;
            region = 0;
            if (*(unsigned char *)(state + 0x82)) {
                int i;
                float nearest = 100000.0f;
                for (i = 0; i < 4; i++) {
                    int index = ((int *)(state + 0x90))[i];
                    if (index != -1) {
                        char *candidate = g_region_table + index * 0x80;
                        float current = fast_vec_dist(g_hero_position, candidate + 0x30);
                        if (current < nearest) {
                            region = candidate;
                            nearest = current;
                        }
                    }
                }
                if (!region) {
                    FastVecSub(point, state + 0xF0, moby + 0x10);
                    FastVecScale(point, point, 0.5f);
                    if (*(float *)(state + 0x70) > 3.0f)
                        vec_fast_divide_helper(point, point, 3.0f);
                    if (FastVecLength(point) < 3.0f)
                        vec_scale_to_length(point, point, 3.0f);
                    FastVecAdd(point, point, moby + 0x10);
                } else {
                    qcopy(point, region + 0x30);
                }
            } else {
                int i;
                first = math_random_int_range(0, 3);
                /* regions[k] is read twice (cse merges the loads): that keeps the
                 * search at 30 insns at expand time, so jump1 does not copy the
                 * loop's exit test in front of the loop. */
                for (i = 0; i < 4; i++) {
                    int k = (i + first) % 4;
                    if (((SpawnerSlots *)state)->regions[k] != -1) {
                        region = g_region_table + ((SpawnerSlots *)state)->regions[k] * 0x80;
                        break;
                    }
                }
                if (!region) {
                    float radius = *(float *)(state + 0x70);
                    if (radius < 3.0f)
                        radius = 3.0f;
                    math_random_planar_offset(point, radius);
                    FastVecAdd(point, point, moby + 0x10);
                } else {
                    qcopy(point, region + 0x30);
                }
            }
            if (region) {
                FastVecScale(delta, region, math_random_float_range(-1.0f, 1.0f));
                FastVecAdd(point, point, delta);
                FastVecScale(delta, region + 0x10, math_random_float_range(-1.0f, 1.0f));
                FastVecAdd(point, point, delta);
            }
            {
                float height = coll_probe_ground_height_below(point, 0, 0.5f);
                if (height != 0.0f)
                    point[2] = height;
            }
            FastVecSub(delta, point, moby + 0x10);
            {
                float distance = FastVecLength(delta) * 0.012000001f;
                vec_scale_to_length(delta, delta, distance);
                moby_transform_joint_to_world(moby, 0, origin);
                vec_scale_to_length(step, delta, 0.05f);
                vec_add_random_offset(step, 0.025f);
                FastVecAdd(origin, origin, step);
                delta[2] = weapon_compute_shot_launch_speed(origin, point, 0, distance, -0.00392f);
            }
            ((SpawnerSlots *)state)->children[slot] = flock_create_member_pal(moby, origin, delta,
                                               *(unsigned char *)(state + 0x83), (unsigned char)slot);
            PlayMobySound(0, 0, moby);
            *(short *)(state + 0x7E) = ((s32)(*(short *)(state + 0x7C)) * 5 + 2) / 6;
            (*(unsigned char *)(state + 0x81))++;
        }
        break;
    }
    case 2:
        SpawnExplosionEffects(moby, state + 0x60, 0, 0.0f, 0.0f, 30, 8, 20, 8.0f, 4.0f, 18.0f, 1.0f, 1, 15.0f, 1, 1, -1, 0,
                      0x810001);
        snd_play_from_class_bank(1, 0, moby, 0x75D);
        part_spawn_flying_fragment(moby, 0x6C5, moby + 0x10, moby + 0xF0, 0, 0, 0.0f,
                          g_effect_vector, g_effect_vector, g_effect_vector);
        part_spawn_flying_fragment(moby, 0x6C6, moby + 0x10, moby + 0xF0, 0, 0, 0.0f,
                          g_effect_vector, g_effect_vector, g_effect_vector);
        part_spawn_flying_fragment(moby, 0x6C7, moby + 0x10, moby + 0xF0, 0, 0, 0.0f,
                          g_effect_vector, g_effect_vector, g_effect_vector);
        moby_mark_spawned(moby);
        return;
    }
    if (*(unsigned char *)(moby + 0x31) && fast_vec_dist(moby + 0x10, g_hero_l06_position) < 24.0f) {
        moby_update_ground_check(moby);
        *(unsigned char *)(moby + 0x6F) = 0x16;
    }
}
