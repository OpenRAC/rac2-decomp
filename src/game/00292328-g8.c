#include "common.h"

typedef struct {
    u64 data;
    u64 tag1;
    u64 tag2;
} Func00292328Packet;

extern int g_render_group_count MACRO_ADDR;
extern void *g_render_group_ptr MACRO_ADDR;
extern u64 g_tex_fill_table[] MACRO_ADDR;
extern Func00292328Packet g_tex_draw_packets[];
extern u64 g_tex_render_group_reloc_state __attribute__((sda));
extern char *g_class_cache_objects[];
extern void tex_relocate_render_groups(void *, int, void *);

/* Builds a list of draw packets from the loaded texture words and sends them off to be drawn. */
void tex_build_draw_packets(void *param)
{
    int i;

    for (i = 0; i < g_render_group_count; i++) {
        g_tex_draw_packets[i].data = g_tex_fill_table[i];
        g_tex_draw_packets[i].tag1 = 0x0000FFA0000000E0ULL;
        g_tex_draw_packets[i].tag2 = 0x0040000400004000ULL;
    }
    tex_relocate_render_groups(g_render_group_ptr, 0, &g_tex_render_group_reloc_state);
    g_class_cache_objects[0][9] = g_class_cache_objects[0][8];
}
