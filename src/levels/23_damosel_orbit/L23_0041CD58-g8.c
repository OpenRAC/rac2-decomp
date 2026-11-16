#include "common.h"

/* func_L23_0041CD58 is a unit of its own: it reads $gp data and needs the opt-in quadword-copy
   profile and its scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt).
   The one MACRO_ADDR count gives retail's absolute reads and its $gp write in a branch's delay
   slot. The row pointer is a local so its address lives long enough for loop.c to move it out
   of the first, 83-instruction loop; taken inline, only its %hi is hoisted. */

typedef int TI128 __attribute__((mode(TI)));

extern char *g_mothership_boss_moby __attribute__((sda));
extern char g_hero_state[];
extern s32 g_effect_pools[3][60];
extern s32 g_effect_pool_counts[3] __attribute__((sda));
extern s32 g_effect_pool_total MACRO_ADDR;
extern float g_boss_effect_pool_scale __attribute__((sda));
extern TI128 g_coll_line_hit_point_2;
extern float fast_vec_dist(char *, char *);
extern int boss_raise_stat_by_step(char *, int, int, int);
extern void moby_set_state(unsigned char *, unsigned char, int);
extern float moby_get_scale_by_class(char *);
extern int math_random_int_below(int);
extern int boss_pick_random_spawn_point(char *, int, float);
extern void FastVecScale(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern void mothership_project_point_onto_surface(char *, float);
extern int CollLine(void *, void *, int, void *, int);
extern void part_spawn_random_row_effect(void *, int);

/* Refresh the active effect pools, then choose a new free spawn position. */
void boss_update_effect_pools(char *object) {
    TI128 loc[2];
    TI128 *offset;
    char *state = *(char **)(g_mothership_boss_moby + 0x68);
    int group = 0;
    int remaining;
    int next;
    int oldCount;
    int oldTotal;
    int spawnGroup;
    char **slot;
    char **spawnSlot;
    s32 *count;
    float alpha;
    char *axis;
    float scale;
    do {
        s32 (*rows)[60] = g_effect_pools;

        count = &g_effect_pool_counts[group];
        slot = (char **)rows[group];
        next = group + 1;
        remaining = 49;
        do {
            if (*slot && *(float *)(state + 0x20) > 0.0f) {
                char *hero = g_hero_state;

                if ((*(unsigned char **)(hero + 0x2290))[0x43] != 6 && fast_vec_dist(*slot + 0x10, hero + 0x80) < 12.0f) {
                    if (boss_raise_stat_by_step(object, (int)*slot, group, 1)) {
                        if (((unsigned char *)*slot)[0x20] == 0) {
                            moby_set_state((unsigned char *)*slot, 16, 0);
                            (*slot)[0x23] = 127;
                        }
                        oldCount = *count;
                        oldTotal = g_effect_pool_total;
                        *slot = 0;
                        *count = oldCount - 1;
                        g_effect_pool_total = oldTotal - 1;
                    } else {
                        alpha = moby_get_scale_by_class(*slot) * 0.083333336f;
                        if (alpha > 1.0f) alpha = 1.0f;
                        else if (alpha < 0.1f) alpha = 0.1f;
                        (*slot)[0x23] = (int)(alpha * 127.0f);
                    }
                }
            }
            remaining--;
            slot++;
        } while (remaining >= 0);
        group = next;
    } while (group < 3);
    if (!math_random_int_below(30) && g_effect_pool_total < 12) {
        boss_pick_random_spawn_point((char *)&loc[0], 1, 0.0f);
        offset = &loc[1];
        spawnGroup = 0;
        do {
            spawnSlot = (char **)g_effect_pools[spawnGroup];
            next = spawnGroup + 1;
            remaining = 49;
            do {
                if (*spawnSlot && fast_vec_dist(*spawnSlot + 16, (char *)&loc[0]) < 4.0f) {
                    axis = *spawnSlot + (math_random_int_below(2) * 16 + 0xC0);
                    if (math_random_int_below(2)) scale = g_boss_effect_pool_scale;
                    else scale = -g_boss_effect_pool_scale;
                    FastVecScale((char *)offset, axis, scale);
                    FastVecAdd((char *)&loc[0], (char *)&loc[0], (char *)offset);
                    mothership_project_point_onto_surface((char *)&loc[0], 0.0f);
                }
                remaining--;
                spawnSlot++;
            } while (remaining >= 0);
            spawnGroup = next;
        } while (spawnGroup < 3);
        *offset = loc[0];
        mothership_project_point_onto_surface((char *)offset, 3.0f);
        if (CollLine(offset, &loc[0], 18, 0, 0))
            loc[0] = g_coll_line_hit_point_2;
        part_spawn_random_row_effect(&loc[0], 0);
    }
}
