#include "include_asm.h"
#include "names.h"

/* func_PAL_00292988, the PAL copy of func_00292078: the same C, where the
   absolutely addressed boot words move, the buffer, count and VRAM cursors
   by 0x80 and the pack flags by 0x88. */
extern int log2dim(int);
typedef struct { long w[12]; } GsLoadImage __attribute__((aligned(16)));
extern void gfx_wait_for_dma_status_bits(unsigned long);
extern short snd_pump_music_and_disc_read_pal(int);
extern int load_read_disc_with_pause_pal(void *, int, int);
extern int func_00126288(GsLoadImage *, short, short, short, short, short, short, short);
extern void FlushCache(int);
extern int sceGsExecLoadImage(GsLoadImage *, void *);
extern int gfx_wait_paths_idle(int, unsigned short);
/* The disc table of contents: sectors are relative to base. */
typedef struct { int sector, size, sector2, size2; } DiscPack;
typedef struct {
    char pad0[0x4F04];
    int base;                 /* 0x4F04: of the packs */
    DiscPack packs[9];        /* 0x4F08 */
} DiscToc;
extern DiscToc g_copy_setup_data;
extern unsigned long long g_tex_fill_table[] __attribute__((sda));

#define LOAD_BUFFER (*(int **)0x001A7314)
#define LOAD_COUNT (*(int *)0x001A7318)
#define CLUT_VRAM (*(int *)0x001A7368)
#define IMAGE_VRAM (*(int *)0x001A7378)
#define PACK_FLAG_5 (*(unsigned char *)0x001A7AD2)
#define PACK_FLAG_6 (*(unsigned char *)0x001A7AD1)
#define PACK_FLAG_7 (*(unsigned char *)0x001A7AD3)
#define PACK_FLAG_8 (*(unsigned char *)0x001A7ACA)

/* A texture record of the pack: width and height, a 16x16 CLUT and the 8-bit
   image after it. */
typedef struct {
    int pad00[2];
    int width;       /* 0x08 */
    int height;      /* 0x0C */
    int pad10[4];
    char clut[0x400]; /* 0x20 */
    char pixels[1];   /* 0x420 */
} TextureRecord;

/* Loads the texture pack of a program (the caller passes the level number;
   four boot flags replace it with packs 5 to 8) from the disc table: the
   pack's second part into the load buffer, whose first word is a count and
   whose next words are offsets of texture records. Each record's 16x16 CLUT
   (at +0x20) and 8-bit image (at +0x420, width and height at +8 and +0xC)
   are uploaded to VRAM, the CLUT from the address in CLUT_VRAM and the
   image from the one in IMAGE_VRAM, and the record's TEX0 word is stored in
   D_001A72A0. The pack's first part then replaces the buffer's contents.
   The buffer, the count, the VRAM cursors and the flags are words addressed
   absolutely. */
void tex_load_pack_to_vram_pal(int pack)
{
    GsLoadImage work;
    TextureRecord *record;
    char *clut;
    int *buffer;
    int *cursor;
    int i;
    int clut_page;
    int image_page;
    int tbw;
    int n;
    int clut_vram;
    int image_vram;
    unsigned long long tag;
    unsigned long long f;
    unsigned long long a;

    gfx_wait_for_dma_status_bits(1);
    buffer = LOAD_BUFFER;
    snd_pump_music_and_disc_read_pal(1);

    if (PACK_FLAG_6)
        pack = 6;
    else if (PACK_FLAG_8)
        pack = 8;
    else if (PACK_FLAG_7)
        pack = 7;
    else if (PACK_FLAG_5)
        pack = 5;

    cursor = buffer + 1;
    load_read_disc_with_pause_pal(buffer, g_copy_setup_data.packs[pack].sector2 + g_copy_setup_data.base,
                  g_copy_setup_data.packs[pack].size2);

    image_vram = IMAGE_VRAM;
    LOAD_COUNT = buffer[0];
    clut_vram = CLUT_VRAM;

    for (i = 0; i < LOAD_COUNT; i++) {
        record = (TextureRecord *)((char *)buffer + *cursor);
        clut_page = clut_vram >> 8;
        clut = record->clut;
        func_00126288(&work, clut_page, 1, 0, 0, 0, 16, 16);
        FlushCache(0);
        sceGsExecLoadImage(&work, clut);
        gfx_wait_paths_idle(0, 0);
        clut_vram += 0x400;
        n = log2dim(record->width);
        tbw = record->width >> 6;
        if (tbw < 1)
            tbw = 1;
        image_page = image_vram >> 8;
        func_00126288(&work, image_page, tbw, 0x1B, 0, 0, record->width, record->height);
        FlushCache(0);
        sceGsExecLoadImage(&work, record->pixels);
        gfx_wait_paths_idle(0, 0);
        a = ((unsigned long long)n << 26) | 0x1B00000;
        tag = (unsigned long long)image_page | ((unsigned long long)tbw << 14);
        tag |= a;
        tag |= (unsigned long long)n << 30;
        f = ((unsigned long long)clut_page << 37) | 0x400000000ULL;
        tag |= f;
        g_tex_fill_table[i] = tag | 0x8000000000000000ULL;
        image_vram += record->width * record->height * 4;
        cursor++;
    }

    load_read_disc_with_pause_pal(buffer, g_copy_setup_data.packs[pack].sector + g_copy_setup_data.base,
                  g_copy_setup_data.packs[pack].size);
}
