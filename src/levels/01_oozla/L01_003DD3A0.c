#include "names.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef union { Quadword whole; float f[4]; } Vector;
extern Vector D_L01_001B94C0;
extern struct { unsigned char prefix[0x80]; Vector position; } g_hero_state;
extern int D_L01_001B2088 __attribute__((sda));
extern char *g_moby_l01_table __attribute__((sda));
extern float fast_vec_dist(void *, void *), vec_distance_xy(void *, void *), level_get_water_height(void);
extern void moby_update_ground_check(void *), muckdweller_alert_group(int), part_spawn_moving_bubbles(void *);
extern int moby_apply_damage_to_object(void *, void *, int), math_random_int_below(int);
extern void weapon_select_aim_target(void *, int, void *, int, float, float);
extern int GetFirstMobyInGroup(char **, int, int, int), GetNextMobyInGroup(char **, char *, int, int);

/* Refresh linked targets and choose the nearest live member of the object's group. */
void muckdweller_update_targeting(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    char *linked;
    char *cursor;
    float nearest, distance, floor;
    *(float *)(object + 0x2c) = *(float *)(*(char **)(object + 0x24) + 0x24) * 1.5f;
    if (object[0x31] && fast_vec_dist(object + 0x10, &D_L01_001B94C0) < 24.0f) {
        moby_update_ground_check(object);
        object[0x6f] = 0x16;
    }
    if (moby_apply_damage_to_object(object, state + 0x110, 0)) {
        *(int *)(state + 0x18c) = *(float *)(state + 0x20) <= 0 ? -1 : *(int *)(state + 0x1fc);
        muckdweller_alert_group((int)object);
    }
    weapon_select_aim_target(object, *(int *)(state + 0x3f8), 0, 0, 0, 0);
    if (*(int *)(state + 0x408) != -1) {
        linked = g_moby_l01_table + (*(int *)(state + 0x408) << 8);
        if (linked && *(unsigned char *)(linked + 0x20) != 0xfe && *(unsigned char *)(linked + 0x20) != 0xfd)
            *(char **)(state + 0x2f0) = linked;
    }
    if (object[0x95] >= 3 && (*(int *)(state + 0x2f4) == 1 || *(int *)(state + 0x408) != -1) && *(int *)(state + 0x1fc) != -1) {
        if (*(int *)(state + 0x41c) != -1) *(int *)(state + 0x3f8) = *(int *)(state + 0x41c);
        if (*(int *)(state + 0x3c0) != -1) *(int *)(state + 0x1fc) = *(int *)(state + 0x3c0);
        ((Vector *)(state + 0x390))->whole = ((Vector *)(*(char **)(state + 0x2f0) + 0x10))->whole;
    }
    if (object[0x21] != 0xff && **(int **)(state + 0x3fc) != D_L01_001B2088) {
        if (**(int **)(state + 0x400) != -1 && D_L01_001B2088 - 10 <= **(int **)(state + 0x3fc)) goto ground;
        **(int **)(state + 0x400) = -1;
        nearest = 100000.0f;
        GetFirstMobyInGroup(&cursor, object[0x21], 0, 0);
        while (cursor) {
            if (*(short *)(cursor + 0xaa) == *(short *)(object + 0xaa)) {
                distance = vec_distance_xy(cursor + 0x10, &g_hero_state.position);
                if (distance < nearest && *(unsigned char *)(cursor + 0x95) == 3 && *(unsigned char *)(cursor + 0x20) != 4) {
                    **(int **)(state + 0x400) = *(short *)(cursor + 0xb2);
                    nearest = distance;
                }
            }
            GetNextMobyInGroup(&cursor, cursor, 0, 0);
        }
        **(int **)(state + 0x3fc) = D_L01_001B2088;
    }
ground:
    if (object[0x31]) {
        floor = level_get_water_height();
        if (*(float *)(object + 0x18) <= floor - 0.3f && (object[0x95] > 1 || math_random_int_below(9) == 0))
            part_spawn_moving_bubbles(object);
    }
}
