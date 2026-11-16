#include "names.h"
/* func_L00_002C40C0 (544 bytes, 25 places), in its own -G8 unit: the list head
 * D_L00_001B1EA8 is read through $gp, and this function's view of D_00189E20 differs
 * from the HeroProbeState declared in L00_002C2DE8-g8.c. The byte and flag tests read
 * their fields into int locals first: a zero-extending load from memory is one RTL insn,
 * while a test shortened to QImode/HImode loads and extends separately. Those two insns
 * decide loop.c's hoisting (threshold * savings * lifetime >= loop insns): 0x99D moves in
 * the first loop pass, then the &D_00189E20 copy, 1 and 0x1D in the rerun, as in retail. */
#include "common.h"
typedef struct {
    unsigned char pad0[0x80]; float position[4];
    unsigned char pad1[8]; float heading;
    unsigned char pad2[0x64C - 0x9C]; float alternate_heading;
    unsigned char pad3[0xB10 - 0x650]; void *selected_b10; int ready_b14;
    unsigned char pad4[0x2294 - 0xB18]; int mode, field_2298, state;
} HeroSelectionState;
extern HeroSelectionState g_hero_state;

extern unsigned char *g_moby_l00_list_head __attribute__((sda));
extern int flag_is_third_pending_set(void *);
extern float hero_score_target_by_heading(char *, float, float, int *, float, float);
extern float vec_distance_xy(void *, void *);
extern int CollLine(void *, void *, int, void *, int);

/* Looks through the object list for the best Blue Swingshot Target in front of the hero. It remembers
 * the closest one that is in view, and says if the hero can reach it. */
int hero_find_blue_swingshot_target(void)
{
    unsigned char *node, *best;
    float score, closest;
    float first[4], second[4];
    int blocked;
    if (g_hero_state.state == 0x21) return g_hero_state.ready_b14;
    best = 0;
    closest = 100000000.0f;
    g_hero_state.ready_b14 = 0;
    node = g_moby_l00_list_head;
    if (node) {
        do {
            float horizontal, vertical, heading;
            int flags, active;
            if (*(short *)(node + 0xAA) != MOBY_CLASS_BLUE_SWINGSHOT_TARGET) continue;
            flags = *(unsigned short *)(node + 0x34);
            if (flags & 1) continue;
            if (flag_is_third_pending_set(node)) continue;
            horizontal = 0.5235988497734069824f;
            vertical = -1.0f;
            if (g_hero_state.mode == 1 || g_hero_state.mode == 0x1D)
                horizontal = vertical = 0.087266474962234497f;
            heading = g_hero_state.heading;
            if (g_hero_state.state == 0xF) heading = g_hero_state.alternate_heading;
            score = hero_score_target_by_heading((char *)node, heading, 30.0f, &blocked, horizontal, vertical);
            if (blocked != 0) continue;
            if (vec_distance_xy(g_hero_state.position, node + 0x10) < 4.0f) continue;
            active = node[0x31];
            if (active == 0) score += 10.0f;
            if (score < closest) { closest = score; best = node; }
        } while ((node = *(unsigned char **)(node + 0x28)) != 0);
    }
    if (best) {
        g_hero_state.selected_b10 = best;
        qcopy(first, g_hero_state.position);
        first[2] += 0.5f;
        qcopy(second, best + 0x10);
        if (!CollLine(first, second, 2, 0, 0)) g_hero_state.ready_b14 = 1;
    }
    return g_hero_state.ready_b14;
}
