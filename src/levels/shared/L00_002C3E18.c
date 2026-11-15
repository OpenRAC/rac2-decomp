#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"
typedef int Vector __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[0x80]; float position[4];
    unsigned char pad1[8]; float heading;
    unsigned char pad2[0x64C - 0x9C]; float alternate_heading;
    unsigned char pad3[0xAA4 - 0x650]; void *selected_aa4; int ready_aa8;
    unsigned char pad4[12]; int value_ab8;
    unsigned char pad5[4]; float value_ac0; float score_ac4;
    unsigned char pad6[8]; void *selected_ad0;
    unsigned char pad7[4]; float score_ad8;
    unsigned char pad8[2]; short ready_ade;
    unsigned char pad9[0xB10 - 0xAE0]; void *selected_b10; int ready_b14;
    unsigned char pad10[0x2294 - 0xB18]; int mode, field_2298, state;
} HeroSelectionState;
extern HeroSelectionState g_hero_state;

extern unsigned char *D_L00_001B1EA8 __attribute__((sda));
extern float hero_score_target_by_heading(void *, int *, float, float, float, float);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern int IsPointInCuboid(void *, int);
extern int CollLine(void *, void *, int, void *, int);

/* Finds the nearest Swingshot Node that is switched on and in front of the hero. It also copies
 * the node's settings and says if the hero can reach it. */
int hero_find_active_swingshot_node(void)
{
    unsigned char *node, *best;
    float closest;
    float first[4], second[4];
    int blocked[4];
    if (g_hero_state.state == 0xD) return g_hero_state.ready_aa8;
    {
        best = 0;
        closest = 100000000.0f;
        g_hero_state.ready_aa8 = 0;
        for (node = D_L00_001B1EA8; node; node = *(unsigned char **)(node + 0x28)) {
            char *data;
            float horizontal, vertical, heading, range, score;
            if (*(short *)(node + 0xAA) != MOBY_CLASS_SWINGSHOT_NODE) continue;
            if (*(unsigned short *)(node + 0x34) & 1) continue;
            if ((*(unsigned short *)(node + 0x34) & 0x1000) == 0) continue;
            data = *(char **)(node + 0x68);
            if (*(int *)data != 0) continue;
            if (*(float *)(data + 0x20) != 0.0f &&
                *(float *)(data + 0x20) < fast_vec_dist(g_hero_state.position, node + 0x10)) continue;
            horizontal = 0.5235988497734069824f;
            vertical = -1.0f;
            if (g_hero_state.mode == 1 || g_hero_state.mode == 0x1D)
                horizontal = vertical = 0.087266474962234497f;
            heading = g_hero_state.heading;
            if (g_hero_state.state == 0xF) heading = g_hero_state.alternate_heading;
            range = 30.0f;
            if (*(float *)(data + 0x20) != 0.0f) range = *(float *)(data + 0x20);
            score = hero_score_target_by_heading(node, blocked, heading, range, horizontal, vertical);
            if (blocked[0] != 0) continue;
            if (vec_distance_xy(g_hero_state.position, node + 0x10) < 4.0f) continue;
            if ((unsigned char)node[0x31] == 0) score += 10.0f;
            if (*(int *)(data + 0x1C) >= 0 && IsPointInCuboid(g_hero_state.position, *(int *)(data + 0x1C))) continue;
            if (score < closest) { closest = score; best = node; }
        }
        if (best) {
            unsigned char *data;
            float value;
            g_hero_state.selected_aa4 = best;
            *(Vector *)first = *(Vector *)g_hero_state.position;
            first[2] += 0.5f;
            *(Vector *)second = *(Vector *)(best + 0x10);
            data = *(unsigned char **)(best + 0x68);
            g_hero_state.value_ab8 = *(int *)(data + 8);
            value = *(float *)(data + 4);
            g_hero_state.score_ac4 = closest;
            g_hero_state.value_ac0 = value;
            if (!CollLine(first, second, 2, 0, 0)) g_hero_state.ready_aa8 = 1;
        }
    }
    return g_hero_state.ready_aa8;
}
