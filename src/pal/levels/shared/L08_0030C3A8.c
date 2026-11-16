#include "include_asm.h"

#include "common.h"
extern void LoadPackSingleTexture();
extern void gfx_send_gs_register_packet();
extern void load_copy_header_relocate_pointers();
extern u8 g_screen_update_index;
extern s32 g_screen_update_headers[];
extern s32 g_screen_update_param;
extern u8 *g_moby_array __attribute__((sda));
extern u8 *g_moby_array_end __attribute__((sda));
extern u8 *g_moby_array __attribute__((sda));
extern u8 *g_hero_moby;

void gfx_run_screen_update_steps_pal(s32 x) {
    LoadPackSingleTexture(x);
    gfx_send_gs_register_packet(x);
    load_copy_header_relocate_pointers(g_screen_update_headers[g_screen_update_index], g_screen_update_param);
}

