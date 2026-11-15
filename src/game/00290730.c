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
extern int D_001A72E4;
extern int D_001A72D0[] __attribute__((sda));
extern int D_001A72D4, g_current_map_index, D_001A9A50;
extern char D_001B1740[], D_001CE4E0[], D_001D1580[], D_001D0E00[];
extern char D_00216480[], D_0021D880[], D_0021D480[], D_00212720[], D_00214520[], D_00213F20[];

/* Gets the game systems ready at the start of a level: memory, tables, graphics and the starting items. */
void level_init_systems(void)
{
    int base;
    load_register_disc_read_callback();
    gfx_select_packet_buffer_setup();
    InitMemSlots();
    base = D_001A72E4;
    D_001A72D0[0] = base;
    D_001A72D4 = base;
    mem_clear(D_001B1740, 0x87654321u, 16);
    mem_clear(D_001CE4E0, -1, 0x2000);
    mem_clear(D_001D1580, -1, 0xF00);
    mem_clear(D_001D0E00, 0, 0xF0);
    mem_clear(D_00216480, -1, 0x2000);
    mem_clear(D_0021D880, -1, 0x800);
    mem_clear(D_0021D480, 0, 0x80);
    mem_clear(D_00212720, -1, 0x1000);
    mem_clear(D_00214520, -1, 0x400);
    mem_clear(D_00213F20, 0, 0x40);
    gfx_init_view_context();
    UpdateViewContext();
    text_clear_font_queue_buffer();
    gfx_reset_packet_buffer();
    part_init_update_table();
    gfx_install_dma_handlers();
    level_grant_starting_items();
    if (g_current_map_index != 0)
        moby_mark_flag_and_append_to_list(g_current_map_index % 28);
    D_001A9A50 = 0;
}
