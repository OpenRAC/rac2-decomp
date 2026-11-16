#include "include_asm.h"
#include "names.h"

extern int ref_L00_002FC030_00 __attribute__((sda));

extern int ref_L00_002FC048_00 __attribute__((sda));

/* Starts a request if none is running yet. */
void hud_request_open(void)
{
    if (ref_L00_002FC030_00 == 0)
        ref_L00_002FC030_00 = 1;
}

/* Tells whether the request has reached its finished state. */
int hud_is_open_done(void)
{
    return ref_L00_002FC048_00 == 3;
}

extern void load_register_disc_read_callback(void), gfx_select_packet_buffer_setup(void), InitMemSlots(void);
extern void gfx_init_view_context(void), UpdateViewContext(void), text_clear_font_queue_buffer(void);
extern void gfx_reset_packet_buffer(void), part_init_update_table(void), gfx_install_dma_handlers(void), level_grant_starting_items(void);
extern void mem_clear(void *, int, int);
extern void moby_mark_flag_and_append_to_list(int);
extern int g_vram_texture_base;
extern int g_vram_cursor[] __attribute__((sda));
extern int g_vram_frame_base, g_current_map_index, g_mission_menu_depth;
extern char g_guard_word_block[], g_class_slot_lookup[], g_class_cache_flags[], g_class_cache_sizes[];
extern char g_level_init_buffer_d[], g_level_init_buffer_f[], g_level_init_buffer_e[], g_level_init_buffer_a[], g_level_init_buffer_c[], g_level_init_buffer_b[];

/* Gets the game systems ready at the start of a level: memory, tables, graphics and the starting items. */
void level_init_systems(void)
{
    int base;
    load_register_disc_read_callback();
    gfx_select_packet_buffer_setup();
    InitMemSlots();
    base = g_vram_texture_base;
    g_vram_cursor[0] = base;
    g_vram_frame_base = base;
    mem_clear(g_guard_word_block, 0x87654321u, 16);
    mem_clear(g_class_slot_lookup, -1, 0x2000);
    mem_clear(g_class_cache_flags, -1, 0xF00);
    mem_clear(g_class_cache_sizes, 0, 0xF0);
    mem_clear(g_level_init_buffer_d, -1, 0x2000);
    mem_clear(g_level_init_buffer_f, -1, 0x800);
    mem_clear(g_level_init_buffer_e, 0, 0x80);
    mem_clear(g_level_init_buffer_a, -1, 0x1000);
    mem_clear(g_level_init_buffer_c, -1, 0x400);
    mem_clear(g_level_init_buffer_b, 0, 0x40);
    gfx_init_view_context();
    UpdateViewContext();
    text_clear_font_queue_buffer();
    gfx_reset_packet_buffer();
    part_init_update_table();
    gfx_install_dma_handlers();
    level_grant_starting_items();
    if (g_current_map_index != 0)
        moby_mark_flag_and_append_to_list(g_current_map_index % 28);
    g_mission_menu_depth = 0;
}
