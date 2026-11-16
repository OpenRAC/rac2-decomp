#include "include_asm.h"
#include "common.h"

/* Small-data unit of func_L00_003B0DA0. Its flags (config/cflags.txt) are its own:
   -frac2-hazard-labels keeps the k loop's guard label on the padding before the first
   division, and -frac2-gcse-unsplit-edges lets PRE set the node table's %hi once, at the
   end of the entry block, so both later uses rematerialize it. */

extern unsigned char g_trail_slot_head __attribute__((sda));
extern unsigned char g_trail_slot_tail __attribute__((sda));
extern int g_frame_l00_counter MACRO_ADDR;
/* The hero record: its position at 0x80, the pad buttons word at 0x1230 and the hero moby at 0x2290. */
typedef struct {
    char pad0[0x80];
    float position[4];
    char pad90[0x11A0];
    int buttons;
    char pad1234[0x105C];
    char *moby;
} HeroL00;
extern HeroL00 g_hero_state;
extern void node_free_slot(int);
typedef struct { float xyz[3]; int used; int particle; u8 links[8]; } TrailNode;
extern TrailNode g_effect_path_node_table[];
extern u8 g_effect_path_node_buffer[];
extern u8 g_chain_link_count __attribute__((sda));
extern float g_chain_min_gap __attribute__((sda));
extern float g_chain_limit_distance __attribute__((sda));
extern int g_chain_max_count __attribute__((sda));
extern float g_chain_range __attribute__((sda));
extern float fast_vec_dist(void *, void *);
extern void node_free_effect_object(int);
extern int path_find_between_nodes(unsigned char, unsigned char, unsigned char *);
extern void trail_spawn_group_burst(float, float, float);
/* Adds a trail point at the hero's position when the hero has moved far enough, links nearby points and merges close groups. */
char *RecordHeroTrailNode(void *unused)
{
    u8 joined[32];
    float previous[4];
    TrailNode *node;
    u8 cursor;
    int count = 0;
    int i, j, k, n;
    float x, y, z, divisor;

    if (g_trail_slot_tail != g_trail_slot_head) {
        TrailNode *last = &g_effect_path_node_table[g_trail_slot_head - 1];
        float gap;
        previous[0] = last->xyz[0];
        previous[1] = last->xyz[1];
        previous[2] = last->xyz[2];
        gap = fast_vec_dist(g_hero_state.position, previous);
        if (gap < g_chain_min_gap) return 0;
    }
    node = &g_effect_path_node_table[g_trail_slot_head];
    node->used = g_frame_l00_counter;
    node->xyz[0] = g_hero_state.position[0];
    node->xyz[1] = g_hero_state.position[1];
    node->xyz[2] = g_hero_state.position[2];
    {
        int l;
        u8 *link = &node->links[7];
        for (l = 7; l >= 0; --l) *link-- = g_trail_slot_head;
    }
    for (cursor = g_trail_slot_head - 1; cursor != (u8)(g_trail_slot_tail - 1); --cursor) {
        float dx, dy, dz, distance;
        u8 entry;
        int a, already;
        if (!g_effect_path_node_table[cursor].used) continue;
        dx = node->xyz[0] - g_effect_path_node_table[cursor].xyz[0];
        dy = node->xyz[1] - g_effect_path_node_table[cursor].xyz[1];
        dz = node->xyz[2] - g_effect_path_node_table[cursor].xyz[2];
        distance = dx * dx + dy * dy + dz * dz;
        if (distance < g_chain_range * g_chain_range) {
            for (entry = g_trail_slot_tail; entry != g_trail_slot_head; ++entry) {
                int b;
                if (entry == cursor) continue;
                for (b = 0; b < 8; ++b)
                    if (g_effect_path_node_table[entry].links[b] == cursor)
                        g_effect_path_node_table[entry].links[b] = g_trail_slot_head;
            }
            node_free_effect_object(cursor);
            node_free_slot(cursor);
        } else {
            float limit;
            /* cse1 ends its block at this group's loop-end note, so row's multiply below
               survives until cse2 makes it the copy of the loop-top product. */
            do { limit = g_chain_limit_distance; } while (0);
            if (distance < limit) {
                int row = cursor * sizeof(TrailNode);
                already = 0;
                for (a = 0; a < 8; ++a) {
                    u8 linked = g_effect_path_node_table[0].links[a + row];
                    int b;
                    if (linked == cursor) continue;
                    for (b = 0; b < 8; ++b)
                        if (g_effect_path_node_table[linked].links[b] == g_trail_slot_head) already = 1;
                }
                if (!already) {
                    u8 *p = g_effect_path_node_table[cursor].links;
                    u8 head;
                    int free = 0;
                    head = g_trail_slot_head;
                    for (; free < 8; free++, p++) {
                        if (*p == cursor) {
                            *p = head;
                            joined[count++] = cursor;
                            break;
                        }
                    }
                }
            }
        }
    }
    if (++g_trail_slot_head == g_trail_slot_tail) node_free_slot(g_trail_slot_tail);
    for (i = 0; i < count; ++i) {
        for (j = i + 1; j < count; ++j) {
            n = path_find_between_nodes(joined[j], joined[i], g_effect_path_node_buffer);
            g_effect_path_node_buffer[n++] = g_trail_slot_head - 1;
            if (n > g_chain_max_count) {
                g_chain_link_count = n;
                z = x = y = 0.0f;
                divisor = n;
                for (k = 0; k < n; ++k) {
                    node_free_effect_object(g_effect_path_node_buffer[k]);
                    x += g_effect_path_node_table[g_effect_path_node_buffer[k]].xyz[0];
                    y += g_effect_path_node_table[g_effect_path_node_buffer[k]].xyz[1];
                    z += g_effect_path_node_table[g_effect_path_node_buffer[k]].xyz[2];
                    node_free_slot(g_effect_path_node_buffer[k]);
                }
                trail_spawn_group_burst(x / divisor, y / divisor, z / divisor);
            }
        }
    }
    return (char *)&g_effect_path_node_table[g_trail_slot_head - 1];
}
