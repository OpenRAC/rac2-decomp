#include "names.h"
/* Carried from rac3-decomp (src/boot_elf/text/398A48.c, func_00398F98): the same
   instructions with rac2's offsets. Selects entry N of the table in D_0014B540: records N
   at +0x18 of D_00152C00, calls func_002FC3C0(1), hands the entry's offset (plus the base
   at +0x3E24) and size to func_002B7C80 for the handle in D_001BAF30, writes the three
   64-bit words of D_001C4DC0 (the GS values at +0x38 of D_00152C00, then two constants)
   and passes them on with func_002934F8. */

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
extern s32 D_001BAF30[];
extern unsigned long D_001C4DC0[3];
extern s32 D_001A91E0 __attribute__((sda));
extern void gfx_wait_for_dma_status_bits(s32);
extern s32 load_read_disc_with_pause(s32, s32, s32);
extern void tex_relocate_block(s32, s32, void *, s32);

/* Reads entry n of the disc table into memory and sends it for drawing. */
void load_disc_table_entry_for_draw(s32 n) {
    SelectTable *table;
    s32 handle;
    g_hero_moby_default.f18 = n;
    gfx_wait_for_dma_status_bits(1);
    table = &g_copy_setup_data;
    handle = D_001BAF30[0];
    load_read_disc_with_pause(handle, table->e[n].a + table->base, table->e[n].b);
    D_001C4DC0[0] = g_hero_moby_default.f38;
    D_001C4DC0[1] = 0xFFA0000000E0;
    D_001C4DC0[2] = 0x40000400004000;
    tex_relocate_block(handle, 0, &D_001A91E0, -1);
}
