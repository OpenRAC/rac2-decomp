#include "names.h"
/* func_PAL_L04_003F2028, the PAL copy of func_L04_003EE090: the same C, where the literals 5,
 * 0.01, -0.00272222 and 60 become 4, 0.012, -0.00392 and 50, and p->delay is scaled to 50 Hz. The
 * timer's store moves ahead of p->fired++ so that the division guard precedes that store. */
#include "common.h"

typedef int UpdateQuad __attribute__((mode(TI)));
typedef float L04_EE090Vec[4] __attribute__((aligned(16)));
extern int g_game_tick_counter MACRO_ADDR;
extern L04_EE090Vec g_tether_zero_vec, g_hero_position;
extern unsigned char g_effect_default_params[] MACRO_ADDR;
/* Table of 0x80-byte target records; targets[] below holds indices into it. */
extern unsigned char *g_linked_record_table __attribute__((sda));
extern unsigned char *g_route_path_table[];
extern void moby_start_timed_effect(unsigned char *, unsigned char *);
extern int moby_count_slot_objects_find_free(unsigned char *, unsigned char *);
extern void moby_mark_spawned(void *);
extern int GetFirstMobyInGroup(unsigned char **, int, int, int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int FastDecTimer(short *);
extern int math_random_int_below(int);
extern int FindHeroOrMobyTarget(void *, void *, void *, int, void *, int, float);
extern int math_random_int_range(int, int);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_fast_divide_helper(void *, void *, float);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void math_random_planar_offset(void *, float);
extern float math_random_float_range(float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_add_random_offset(void *, float);
extern float weapon_compute_shot_launch_speed(void *, void *, int, float, float);
extern unsigned char *SpawnChildMoby(void *, void *);
extern void vec_random_direction(void *, float, float);
extern void *level_build_spawn_record(void *, void *, void *, void *, void *, void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void SetDeathBits_pal(void *, int, int);

typedef struct {
    char pad0[0x20];
    float speed;
    char pad24[5];
    unsigned char active;
    char pad2a[0x46];
    float range;
    int idList;
    int pathIndex;
    short delay;
    short timer;
    unsigned char limit;
    unsigned char fired;
    unsigned char nearest;
    char pad83;
    int group;
    char pad88[8];
    int targets[4]; /* indices into D_L04_001B25CC, -1 for an empty slot */
    char padA0[0x50];
    UpdateQuad goal;
    char pad100[0x30];
    unsigned char *link;
    int linkState;
    char pad138[8];
    int shots;
} L04_EE090Vars;

/* Launcher: pick a target point near a record (nearest to the player, or a
 * random one), fire a child towards it, and retire after enough shots. */
void func_PAL_L04_003F2028(unsigned char *m)
{
    float target[4], delta[4], rotation[4], axis[4], position[4], velocity[4];
    L04_EE090Vars *p = *(L04_EE090Vars **)(m + 0x68);
    unsigned char *cursor, *chosen, *child;
    int count, index;
    float scale, z;

    moby_start_timed_effect(m, (unsigned char *)p);
    if (m[0x31] && fast_vec_dist(m + 0x10, g_tether_zero_vec) < 24.0f) {
        moby_update_ground_check(m);
        m[0x6F] = 22;
    }
    switch (m[0x20]) {
    case 0:
        p->active = 1;
        p->speed = 1.0f;
        p->shots = 0;
        if (g_game_tick_counter) {
            cursor = 0;
            count = 0;
            while (!GetFirstMobyInGroup(&cursor, p->group, 0, 0)) {
                moby_mark_spawned(cursor);
                count++;
            }
            if (count < p->limit)
                p->limit = count;
            m[0x20] = 1;
        }
        break;
    case 1: {
        float best, distance;

        moby_start_timed_effect(m, (unsigned char *)p);
        if (m[0x43] == 1 && (m[0x60] & 2))
            func_PAL_002A7E68(m, 0, 0, 4);
        if (!FastDecTimer(&p->timer))
            break;
        if (!math_random_int_below(7)) {
            void *ids, *path;
            int n, pathCount;
            ids = 0;
            n = 0;
            path = 0;
            pathCount = 0;
            if (p->idList != -1) {
                ids = &p->idList;
                n = 1;
            }
            if (p->pathIndex != -1) {
                unsigned char *d = g_route_path_table[p->pathIndex];
                path = d + 0x10;
                pathCount = *(int *)d;
            }
            FindHeroOrMobyTarget(m, &p->goal, ids, n, path, pathCount, p->range);
        } else {
            unsigned char *q = p->link;
            if (q && q[0x20] != 0xFE && q[0x20] != 0xFD) {
                qcopy_nc(&p->goal, q + 0x10);
            } else {
                p->link = 0;
                p->linkState = 2;
            }
        }
        if (p->linkState == 2)
            break;
        index = moby_count_slot_objects_find_free(m, (unsigned char *)p);
        if (p->fired >= p->limit || index == -1)
            break;
        chosen = 0;
        if (p->nearest) {
            int i;
            best = 100000.0f;
            /* Read through an int-pointer view, as in func_L06_003F3800;
             * p->targets[i] here gives different registers and stack slots. */
            for (i = 0; i < 4; i++) {
                int id = ((int *)((unsigned char *)p + 0x90))[i];
                if (id != -1) {
                    unsigned char *q = g_linked_record_table + id * 128;
                    distance = fast_vec_dist(g_hero_position, q + 0x30);
                    if (distance < best) {
                        chosen = q;
                        best = distance;
                    }
                }
            }
            if (!chosen) {
                FastVecSub(target, &p->goal, m + 0x10);
                FastVecScale(target, target, 0.5f);
                if (p->range > 1.0f)
                    vec_fast_divide_helper(target, target, 1.0f);
                if (FastVecLength(target) < 1.0f)
                    vec_scale_to_length(target, target, 1.0f);
                FastVecAdd(target, target, m + 0x10);
            } else {
                qcopy_nc(target, chosen + 0x30);
            }
        } else {
            int i;
            int start = math_random_int_range(0, 3);
            /* targets[k] is read twice (cse merges the loads), keeping the
             * exit test short enough that jump1 does not peel an iteration. */
            for (i = 0; i < 4; i++) {
                int k = (i + start) % 4;
                if (p->targets[k] != -1) {
                    chosen = g_linked_record_table + p->targets[k] * 128;
                    break;
                }
            }
            if (!chosen) {
                float radius = p->range;
                if (radius < 1.0f)
                    radius = 1.0f;
                math_random_planar_offset(target, radius);
                FastVecAdd(target, target, m + 0x10);
            } else {
                qcopy_nc(target, chosen + 0x30);
            }
        }
        if (chosen) {
            FastVecScale(delta, chosen, math_random_float_range(-0.5f, 0.5f));
            FastVecAdd(target, target, delta);
            FastVecScale(delta, chosen + 0x10, math_random_float_range(-0.5f, 0.5f));
            FastVecAdd(target, target, delta);
        }
        z = coll_probe_ground_height_below(target, 0, 3.0f);
        if (z != 0)
            target[2] = z;
        FastVecSub(delta, target, m + 0x10);
        scale = FastVecLength(delta) * 0.012000001f;
        vec_scale_to_length(delta, delta, scale);
        moby_transform_joint_to_world(m, 0, rotation);
        vec_scale_to_length(axis, delta, 0.05f);
        vec_add_random_offset(axis, 0.025f);
        delta[2] = weapon_compute_shot_launch_speed(rotation, target, 0, scale, -0.00392f);
        *(UpdateQuad *)position = *(UpdateQuad *)(m + 0x10);
        child = SpawnChildMoby(m, position);
        *(float *)(child + 0x2C) = *(float *)(*(unsigned char **)(child + 0x24) + 0x24);
        vec_random_direction(position, 2.0f, 3.0f);
        position[2] = 0;
        FastVecAdd(position, position, target);
        rotation[2] += 1.0f;
        *(UpdateQuad *)velocity = 0;
        velocity[2] = 3.0f;
        level_build_spawn_record(child, rotation, velocity, position, velocity, g_effect_default_params, 50, 0, 0);
        p->timer = ((s32)(p->delay) * 5 + 2) / 6;
        p->fired++;
        if (++p->shots >= 19)
            moby_set_state(m, 2, -1);
        PlayMobySound(0, 0, m);
        if (m[0x43] != 1)
            func_PAL_002A7E68(m, 1, 0, 4);
        break;
    }
    case 2:
        SpawnExplosion_pal(m + 0x10, 0, 25, 20, 20, 20, 20, 0, 1, 0, 0, 0, 0.75f, 20.0f);
        p->speed = 0;
        PlayMobySound(1, 0, m);
        SetDeathBits_pal(m, 0, 3);
        moby_mark_spawned(m);
        break;
    }
}
