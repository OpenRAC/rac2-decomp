#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 p0[0x18];
    s32 f18;
    u8 p1c[0x1C];
    unsigned long f38;
} SelectState;
typedef struct {
    u8 p0[0x3E24];
    s32 base;
    u8 p3e28[0x48D8 - 0x3E28];
    struct {
        s32 a;
        s32 b;
    } e[1];
} SelectTable;
extern SelectState g_hero_moby_default;
extern SelectTable g_copy_setup_data;
extern s32 g_disc_table_handles[];
extern unsigned long g_tex_draw_packets[3];
extern s32 g_tex_block_reloc_state __attribute__((sda));
extern void gfx_wait_for_dma_status_bits(s32);
extern s32 load_read_disc_with_pause_pal(s32, s32, s32);
extern void tex_relocate_block(s32, s32, void *, s32);

/* Reads entry n of the disc table into memory and sends it for drawing. */
void load_disc_table_entry_for_draw_pal(s32 n) {
    SelectTable *table;
    s32 handle;
    g_hero_moby_default.f18 = n;
    gfx_wait_for_dma_status_bits(1);
    table = &g_copy_setup_data;
    handle = g_disc_table_handles[0];
    load_read_disc_with_pause_pal(handle, table->e[n].a + table->base, table->e[n].b);
    g_tex_draw_packets[0] = g_hero_moby_default.f38;
    g_tex_draw_packets[1] = 0xFFA0000000E0;
    g_tex_draw_packets[2] = 0x40000400004000;
    tex_relocate_block(handle, 0, &g_tex_block_reloc_state, -1);
}
