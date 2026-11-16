#include "include_asm.h"

#include "common.h"
typedef struct { int a, b, c, d; } PackEntry;
typedef struct {
    char pad0[0x4F04];
    int base;            
    char pad4F08[0x4F98 - 0x4F08];
    PackEntry packs[1];  
} PackToc;
extern PackToc g_copy_setup_data;
extern char *g_load_base_pointer;
extern int g_vram_clut_first[] __attribute__((sda));
extern int g_vram_image_address[] __attribute__((sda));
extern long g_tex_fill_table[] __attribute__((sda));
extern void FlushCache(int);
extern int log2dim(int);
extern short snd_pump_music_and_disc_read_pal(int);
extern void gfx_wait_for_dma_status_bits(int);
extern int load_read_disc_with_pause_pal(void *, int, int);
extern int func_00126288(void *, short, short, short, short, short, short, short);
extern int sceGsExecLoadImage(void *, void *);
extern int gfx_wait_paths_idle(int, unsigned short);

/* Reads the second part of pack index into the load buffer and uploads the
   one texture record there, as RAC1's LoadPifAsPSMT8H does: its 16x16 CLUT
   (at +0x20 of the record, which starts at +0x10) to the VRAM address in
   D_001A72EC and its 8-bit image to the one in D_001A72FC, keeping the TEX0
   word in slot 5 of D_001A72A0. The pack's first part then replaces the buffer.
   The store goes through the table so that its symbol+offset is the assembler
   macro form (two words, never a delay slot). The named words and the order
   they are built in give retail's registers. */
void LoadPackSingleTexture_pal(int index)
{
    long packet[12] __attribute__((aligned(16)));
    char *base;
    char *hdr;
    PackToc *table;
    int width, log;
    char *clut;

    gfx_wait_for_dma_status_bits(1);
    base = g_load_base_pointer;
    snd_pump_music_and_disc_read_pal(1);
    hdr = base + 0x10;
    clut = base + 0x30;
    table = &g_copy_setup_data;
    load_read_disc_with_pause_pal(base, table->packs[index].c + table->base, table->packs[index].d);
    func_00126288(packet, g_vram_clut_first[0] >> 8, 1, 0, 0, 0, 16, 16);
    FlushCache(0);
    sceGsExecLoadImage(packet, clut);
    gfx_wait_paths_idle(0, 0);
    log = log2dim(*(int *)(hdr + 8));
    width = *(int *)(hdr + 8) >> 6;
    if (width < 1)
        width = 1;
    func_00126288(packet, g_vram_image_address[0] >> 8, width, 27, 0, 0, *(short *)(hdr + 8), *(short *)(hdr + 12));
    FlushCache(0);
    sceGsExecLoadImage(packet, base + 0x430);
    gfx_wait_paths_idle(0, 0);
    {
        long image, tex, format, clut_base, word;

        image = (long)g_vram_image_address[0] >> 8;
        tex = image | ((long)width << 14);
        format = ((long)log << 26) | 0x1b00000L;
        tex |= format;
        tex |= (long)log << 30;
        clut_base = (((long)g_vram_clut_first[0] >> 8) << 37) | 0x400000000L;
        word = tex | clut_base;
        word |= 0x8000000000000000UL;
        g_tex_fill_table[5] = word;
    }
    load_read_disc_with_pause_pal(base, table->packs[index].a + table->base, table->packs[index].b);
}
