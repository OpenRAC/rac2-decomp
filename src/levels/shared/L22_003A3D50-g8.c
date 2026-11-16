#include "common.h"
typedef int Quad0792 __attribute__((mode(TI)));
extern char *g_pickup_slot_table[3][60] __attribute__((section(".data")));
extern int g_pickup_counts[] MACRO_ADDR;
extern int g_pickup_spawn_budget[] MACRO_ADDR;
extern char *g_space_ship_pickup_slots[] MACRO_ADDR;
typedef struct Globals_3D50 {
    char pad[0x1874];
    int mode;
    char gap[0xA18];
    char *player;
} Globals_3D50;
extern Globals_3D50 g_hero_state;
extern float g_pickup_pull_distance __attribute__((sda));
extern float g_enemy_random_scale __attribute__((sda));
extern Quad0792 g_spawn_point __attribute__((section(".data")));
extern float moby_get_class_setting_value(void *);
extern int pickup_apply_to_ship(void *, void *, int, int);
extern void moby_set_state(void *, int, int);
extern float fast_vec_dist(void *, void *);
extern int math_fast_float_d(void *);
extern int math_random_int_below(int);
extern int lane_pick_random_point_away_from_ship(void *, int, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void arena_push_point_out(void *, float);
extern int CollLine(void *, void *, int, int, int);
extern void SpawnRandomKindAt(void *, int);

/* Every frame, checks the spawned pickups: collects the ones the ship reaches, fades the ones near it, and now and then spawns a new one. */
void pickup_update_spawned(char *obj) {
    struct { Quad0792 point, high; } v;
    char *st = *(char **)(obj + 0x68);
    int i, n;
    int *counts = g_pickup_counts;
    int offset;
    i = 0;
    offset = 0;
    do {
        int *count = counts;
        char **slot = (char **)((char *)g_pickup_slot_table + offset);
        for (n = 49; n >= 0; n--, slot++) {
            if (*slot) {
                if (g_hero_state.mode > 0 &&
                    *(unsigned char *)(g_hero_state.player + 0x43) != 6 &&
                    moby_get_class_setting_value(*slot) < g_pickup_pull_distance) {
                    if (pickup_apply_to_ship(obj, *slot, i, 1)) {
                        if (!*(unsigned char *)(*slot + 0x20)) {
                            moby_set_state(*slot, 16, 0);
                            *(unsigned char *)(*slot + 0x23) = 127;
                        }
                        (*count)--;
                        *slot = 0;
                        g_pickup_spawn_budget[0]--;
                    } else {
                        float ratio = moby_get_class_setting_value(*slot) / g_pickup_pull_distance;
                        if (ratio > 1.0f) ratio = 1.0f;
                        else if (ratio < 0.1f) ratio = 0.1f;
                        *(unsigned char *)(*slot + 0x23) = (int)(ratio * 127.0f);
                        continue;
                    }
                } else {
                    if (!(*(float *)(st + 0x20) > 0.0f) || (unsigned char)obj[0x43] == 4 || (unsigned char)obj[0x43] == 8)
                        continue;
                    if (!(fast_vec_dist(*slot + 0x10, obj + 0x10) < g_pickup_pull_distance) || !pickup_apply_to_ship(obj, *slot, i, 0))
                        continue;
                    if (!*(unsigned char *)(*slot + 0x20)) moby_set_state(*slot, 17, 0);
                    (*count)--;
                    *slot = 0;
                    g_pickup_spawn_budget[0]--;
                }
            }
        }
        counts++;
        offset += 240;
        i++;
    } while (i < 3);
    for (i = 1; i >= 0; i--) {
        math_fast_float_d(g_space_ship_pickup_slots[0] + 4);
        math_fast_float_d(g_space_ship_pickup_slots[0]);
    }
    if (math_random_int_below(30) == 0 && g_pickup_spawn_budget[0] < 12) {
        int group;
        Quad0792 *high;
        lane_pick_random_point_away_from_ship(&v.point, 1, 0.0f);
        high = &v.high;
        group = 0;
        while (group < 3) {
            int next_group = group + 1;
            char **slot = g_pickup_slot_table[group];
            int remaining;
            for (remaining = 49; remaining >= 0; remaining--, slot++) {
                if (*slot && fast_vec_dist(*slot + 0x10, &v.point) < 4.0f) {
                    char *axis = *slot + 0xC0 + math_random_int_below(2) * 16;
                    float scale;
                    if (math_random_int_below(2)) scale = g_enemy_random_scale;
                    else scale = -g_enemy_random_scale;
                    FastVecScale(high, axis, scale);
                    FastVecAdd(&v.point, &v.point, high);
                    arena_push_point_out(&v.point, 0.0f);
                }
            }
            group = next_group;
        }
        qcopy(high, &v.point);
        arena_push_point_out(high, 3.0f);
        if (CollLine(high, &v.point, 0x12, 0, 0)) qcopy(&v.point, &g_spawn_point);
        SpawnRandomKindAt(&v.point, 0);
    }
}
