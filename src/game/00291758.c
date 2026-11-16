#include "include_asm.h"
#include "names.h"

typedef struct { unsigned char count[4]; int groups, runs; } RenderHeader;
extern int g_loader_memory[];
extern void tex_draw_batches(int *, char *, unsigned char *, int);

extern int *g_level_data_ptr __attribute__((section(".sdata")));
extern char g_load_memory_ceiling[];
extern int load_read_disc_sectors_blocking(int, int, int);

extern int g_tex_pack_range_index __attribute__((sda));
extern char g_tex_pack_data_buffer[];
extern int g_particle_texture_table[];
extern int log2dim(int);
extern void mem_copy_aligned(void *, void *, int);



extern void load_release_class_cache_slot(int *, int);

extern void build_indexed_resident_render_packet(void *, void *, int, int, int, int, int);

extern void gfx_flush_light_part_indices(int);

extern void CreatePointLight(int);

typedef struct { long w[12]; } GsLoadImage __attribute__((aligned(16)));
extern void gfx_wait_for_dma_status_bits(unsigned long);
extern short snd_pump_music_and_disc_read(int);
extern int load_read_disc_with_pause(void *, int, int);
extern int func_00126288(GsLoadImage *, short, short, short, short, short, short, short);
extern void FlushCache(int);
extern int sceGsExecLoadImage(GsLoadImage *, void *);
extern int gfx_wait_paths_idle(int, unsigned short);
/* The disc table of contents: sectors are relative to base. */
typedef struct { int sector, size, sector2, size2; } DiscPack;
typedef struct { int sector, size; } DiscFile;
typedef struct { int id, sector, size, sector2, size2; } DiscSlot;
typedef struct {
    char pad0[0x32C];
    int level_base;           /* 0x32C */
    char pad330[0x348 - 0x330];
    DiscFile level;           /* 0x348 */
    char pad350[0x4B40 - 0x350];
    DiscSlot slots[48];       /* 0x4B40 */
    int pad_4F00;
    int base;                 /* 0x4F04: of the packs */
    DiscPack packs[9];        /* 0x4F08 */
    char pad_4F98[0x529C - 0x4F98];
    int archive_base;         /* 0x529C */
    int pad2[2];
    DiscFile archive0;        /* 0x52A8 */
    int pad3[2];
    DiscFile archive1;        /* 0x52B8 */
} DiscToc;
extern DiscToc g_copy_setup_data;
extern unsigned long long g_tex_fill_table[] __attribute__((sda));

extern void snd_clear_flag_and_update(void);
extern int snd_Pump(void);
extern int snd_CheckLoadInProgress(int);
extern int snd_run_handler_or_send_cmd37(void);
extern int sceCdGetError(void);
extern void snd_print_status(void);
extern void snd_load_first_bank(void);
extern void snd_load_bank_entry(int);
/* The callee at 0x00132828 (the catalogue names it func_00132818). */
extern void func_00132828(void);
/* As in RAC1: the disc wait-frame count, a flag set once the load has
   been stepped back, and a mode word that is 1 until then. */
extern int g_cd_error_retry_count __attribute__((sda));
extern int g_cd_error_seen __attribute__((sda));
extern int g_load_read_mode __attribute__((sda));
/* The level archive load: stage, busy flag and the two archive buffers
   (archive0 is the level data D_001A7288 points at). */
typedef struct { int stage, busy, archive0, archive1; } ArchiveLoad;
extern ArchiveLoad g_loader_archives __attribute__((sda));
extern int g_archive_end_address;
extern short g_load_header_flag[];
/* The two sound bank statuses: -1 while a load is pending. */
extern unsigned int g_load_relocate_a, g_load_relocate_b;

/* The class cache header: VRAM offsets of the slot's image (in words) and
   CLUT, the one material map entry and the slot. */
typedef struct {
    int image_offset;           /* 0x00 */
    short pad04[3];
    unsigned short clut_offset; /* 0x0A */
    short pad0C[2];
    short map;                  /* 0x10 */
    short slot;                 /* 0x12 */
} ClassCache;
extern ClassCache g_load_slots;
/* A loaded class: the count of its 32-byte entries at 0x0D and the table of
   them at 0x28. */
typedef struct {
    char pad00[0x1C];
    int f1C;
} ClassEntry;
typedef struct {
    char pad00[0x0D];
    unsigned char entry_count; /* 0x0D */
    char pad0E[0x28 - 0x0E];
    ClassEntry *entries;       /* 0x28 */
} ClassData;
/* The decode buffer; a texture part starts with a type word, has its width
   at 0x18 and its CLUT and pixels at 0x30 and 0x430. */
typedef struct { int type; } DecodeHeader;
extern DecodeHeader g_decode_header;
extern int g_decoded_image_width;
extern char g_decoded_image_buffer[];
extern char g_decoded_pixels[];
extern char g_str_class_cache_format[];
extern int g_vram_clut_third __attribute__((sda));
extern int g_vram_pixel_base __attribute__((sda));
extern int g_class_cache_count __attribute__((sda));
extern int g_class_cache_sizes[];
extern ClassData *g_class_cache_objects[];
extern unsigned char g_class_slot_lookup[];
extern int fast_decompress(void *, void *);
extern void load_register_class_cache_object(void *, void *, void *, int);
extern int func_001337F0(void);
extern int func_00133820(void);
extern void STUB_printf(const char *, ...);

/* Frozen Batch A A02-list-add-88; acknowledged claim 38ceeb041b6ba12996de10c402ca54295587db96246845b83b2ec894986b096f. */
typedef unsigned char BatchA_A02_u8;

typedef int BatchA_A02_s32;

typedef struct { char _0[0x10]; BatchA_A02_u8 n; char _11[3]; BatchA_A02_s32 off; char _18[4]; BatchA_A02_s32 ent[1]; } BatchA_A02_Blk;

typedef int s32;

typedef unsigned char u8;

extern int F46b43b72_FUN_002B7B18(int value, char *target);

extern short F46b43b72_FUN_002B7CE0(int value);

extern int F46b43b72_D_001B8840[];

extern int F46b43b72_D_0014B540[];

struct Slot { s32 w; s32 rest[4]; };

struct Table1 { char pad[19264]; struct Slot slots[48]; };

struct Table2 { char pad[52]; s32 slots[4]; };

extern struct Table1 Fee2b87d1_D_0014B540;

extern struct Table2 Fee2b87d1_D_00152CD0;

/* Frees the old part data of a light and rebuilds its sections. */
void gfx_refresh_light_parts(int param_1)
{
    gfx_flush_light_part_indices(param_1);
    CreatePointLight(param_1);
}

/* One slot of the moby-part table the loader walks: six 16-bit indices into a
   shared index array, and the array itself. The table's address differs from
   program to program, so it carries no address in its name. */
typedef struct {
    short idx0;
    short idx1;
    short idx2;
    short idx3;
    short idx4;
    short idx5;
    short *index;
    char pad[0x30 - 0x10];
} BatchA_A02_Part;

extern BatchA_A02_Part ref_L00_002FD338_00[];

extern int ref_L00_002FD338_01(short *, short *, int);
extern int ref_L00_002FD338_02(short *, short *, int);
extern int ref_L00_002FD338_03(short *, short *, int);

/* Hands the three index pairs of one part-table entry to the routines that
   consume them and clears the indices. The index is a 32-bit one: the table
   holds eight entries. The three routines live at another address in every
   program, so they carry no address in their names. */
void gfx_flush_light_part_indices(int index)
{
    BatchA_A02_Part *part = ref_L00_002FD338_00 + index;

    if (part->index) {
        ref_L00_002FD338_01(part->index + part->idx0, part->index + part->idx0 + part->idx1, index);
        part->idx0 = 0;
        part->idx1 = 0;
        ref_L00_002FD338_02(part->index + part->idx2, part->index + part->idx2 + part->idx3, index);
        part->idx2 = 0;
        part->idx3 = 0;
        ref_L00_002FD338_03(part->index + part->idx4, part->index + part->idx4 + part->idx5, index);
        part->idx4 = 0;
        part->idx5 = 0;
    }
}

/* func_00291850 is in 00291850.c. */


/* Texture ranges: the particle renderer (func_002B9420) hands this table to
   the toSPR DMA channel; C only ever writes it. */
typedef struct { int a, b; } TextureRange;
extern volatile TextureRange g_texture_ranges[];

/* Rebases the offset table of a loaded pack onto the copy of its data in
   D_001F2740, then fills the texture range table from count four-word list
   entries. */
void tex_rebase_pack_fill_ranges(int *hdr, int base, int *list, int count)
{
    int n = hdr[0];
    int data_off = hdr[2];
    int data_size = hdr[3];
    int *entry = hdr + 4;
    int i;

    for (i = 0; i < n; i++, entry++) {
        if (*entry == 0)
            g_particle_texture_table[i] = (int)g_tex_pack_data_buffer;
        else
            g_particle_texture_table[i] = *entry - (data_off - (int)g_tex_pack_data_buffer);
    }
    mem_copy_aligned(g_tex_pack_data_buffer, (char *)hdr + data_off, data_size);
    for (g_tex_pack_range_index = 0; g_tex_pack_range_index < count; g_tex_pack_range_index++) {
        int src_page = base + *list++;
        int src_offset = *list++;
        int dst_page = base + *list++;
        int dst_size = *list++;

        g_texture_ranges[g_tex_pack_range_index].a = (src_page << 4) + src_offset;
        g_texture_ranges[g_tex_pack_range_index].b = (dst_page << 4) + log2dim(dst_size);
    }
}


/* func_00291DE0 is matched in its own unit, 00291DE0.c. */

/* func_00291EC0 is in 00291DE0.c. */

/* Boot data words reached at their fixed addresses, which gives the retail
   code's absolute (lui) addressing. */
#define LOAD_BUFFER (*(int **)0x001A7294)
#define LOAD_COUNT (*(int *)0x001A7298)
#define CLUT_VRAM (*(int *)0x001A72E8)
#define IMAGE_VRAM (*(int *)0x001A72F8)
#define PACK_FLAG_5 (*(unsigned char *)0x001A7A4A)
#define PACK_FLAG_6 (*(unsigned char *)0x001A7A49)
#define PACK_FLAG_7 (*(unsigned char *)0x001A7A4B)
#define PACK_FLAG_8 (*(unsigned char *)0x001A7A42)

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
void tex_load_pack_to_vram(int pack)
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
    snd_pump_music_and_disc_read(1);

    if (PACK_FLAG_6)
        pack = 6;
    else if (PACK_FLAG_8)
        pack = 8;
    else if (PACK_FLAG_7)
        pack = 7;
    else if (PACK_FLAG_5)
        pack = 5;

    cursor = buffer + 1;
    load_read_disc_with_pause(buffer, g_copy_setup_data.packs[pack].sector2 + g_copy_setup_data.base,
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

    load_read_disc_with_pause(buffer, g_copy_setup_data.packs[pack].sector + g_copy_setup_data.base,
                  g_copy_setup_data.packs[pack].size);
}


extern void tex_load_pack_to_vram(int);
extern void tex_build_draw_packets(void *);
extern u8 *g_object_l03_pointer_table[];
extern void load_copy_header_relocate_pointers(u8 *, u8 *);
extern unsigned char *g_level_pack_data;

/* Loads the texture pack of a level and its draw packets, then remembers the level number. */
void tex_load_level_pack(void *level)
{
    tex_load_pack_to_vram(level);
    tex_build_draw_packets(level);
    load_copy_header_relocate_pointers((u8 *)g_object_l03_pointer_table[0], g_level_pack_data);
    *(int *)0x001A7290 = (int)level;
}


/* func_00292408 is in 00292408.c. */



typedef struct { int off, size; } UploadPair;
typedef struct { char p0[0x3e24]; int base; char p1[0x48f0-0x3e28]; UploadPair entries[1]; } UploadTable;
extern UploadTable upload_table __asm__("D_0014B540");
typedef struct { char p0[0x30]; int index; char p1[4]; long word; } UploadState;
extern UploadState g_hero_moby_default;
extern int g_packet_buffer_table[];
extern int g_packet_buffer_index[] __attribute__((sda));
extern int g_vram_clut_second[] __attribute__((sda));
extern int g_vram_level_image_address[] __attribute__((sda));

/* Reads entry index of the disc table into the free one of the two buffers at
   D_001B22A0, uploads its 16x16 CLUT (at +0x20) and 8-bit image (at +0x420, width
   and height at +8 and +0xC) to VRAM at the addresses in D_001A72F0 and D_001A7300,
   and stores the image's GS TEX0 word and the index in D_00152C00. */
void LoadDiscTableTexture(int index)
{
    GsLoadImage packet;
    char *base;
    char *clut;
    UploadState *state;
    UploadTable *table;
    int width, log;

    state = &g_hero_moby_default;
    state->index = index;
    gfx_wait_for_dma_status_bits(1);
    base = (char *)g_packet_buffer_table[1 - g_packet_buffer_index[0]];
    snd_pump_music_and_disc_read(1);
    clut = base + 0x20;
    table = &upload_table;
    load_read_disc_with_pause(base, table->entries[index].off + table->base, table->entries[index].size);
    func_00126288(&packet, g_vram_clut_second[0] >> 8, 1, 0, 0, 0, 16, 16);
    FlushCache(0);
    sceGsExecLoadImage(&packet, clut);
    gfx_wait_paths_idle(0, 0);
    log = log2dim(*(int *)(base + 8));
    width = *(int *)(base + 8) >> 6;
    if (width < 1)
        width = 1;
    func_00126288(&packet, g_vram_level_image_address[0] >> 8, width, 27, 0, 0, *(short *)(base + 8), *(short *)(base + 12));
    FlushCache(0);
    sceGsExecLoadImage(&packet, base + 0x420);
    gfx_wait_paths_idle(0, 0);
    {
        long image, tex, format, clut_base, word;

        image = (long)g_vram_level_image_address[0] >> 8;
        tex = image | ((long)width << 14);
        format = ((long)log << 26) | 0x1b00000L;
        tex |= format;
        tex |= (long)log << 30;
        clut_base = (((long)g_vram_clut_second[0] >> 8) << 37) | 0x400000000L;
        word = tex | clut_base;
        word |= 0x8000000000000000UL;
        state->word = word;
    }
}

/* func_00292888 is in 00292888-g8.c. */


/* func_00292B88 is in 00292B88.c. */

extern long r1_D_0019E7C0[];

extern long r1_D_0019E640[];

extern long r1_D_0019E7D8[];

/* rac1-decomp src/game/loaders.c: func_00203808 */
/* Fills four A+D qwords (low dwords only) at out: a TEX1-style word
   (MXL bits from the second word of row arg5 of the 3-dword table
   r1_D_0019E640, MMAG 1, MMIN arg2, K arg1), then arg3 | arg4 << 2 |
   arg5 << 24, then the row's first and third words. A negative arg5 has
   no row: -2 and -3 take the rows r1_D_0019E7C0 and r1_D_0019E7D8 (and 5 for
   the second word), -1 a fixed constant and 0. The row is read before
   the sign test, as in retail. The OR operands are named locals so fold
   does not move the 0x20 to the end of the chain. */
void tex_build_packet_words(long *out, int lodK, int minFilter, int clampMode, int flagBits, int rowIndex) {
    long f0 = r1_D_0019E640[rowIndex * 3];
    long f1 = r1_D_0019E640[rowIndex * 3 + 1];
    long f2 = r1_D_0019E640[rowIndex * 3 + 2];

    if (rowIndex >= 0) {
        long minAndFlag = ((long)minFilter << 6) | 0x20;

        *out = (f1 & 0x1C) | minAndFlag | ((long)lodK << 32);
        out += 2;
        *out = clampMode | ((long)flagBits << 2) | ((long)rowIndex << 24);
        out += 2;
        *out = f0;
        out[2] = f2;
    } else if (rowIndex < -1) {
        long *tpl = r1_D_0019E7C0;

        if (rowIndex == -3) {
            tpl = r1_D_0019E7D8;
        }
        {
            long minShifted = (long)minFilter << 6;
            long kAndFlag = ((long)lodK << 32) | 0x20;
            *out = minShifted | kAndFlag;
        }
        out += 2;
        *out = 5;
        out += 2;
        *out = tpl[0];
        out[2] = tpl[2];
    } else {
        {
            long minShifted = (long)minFilter << 6;
            long kAndFlag = ((long)lodK << 32) | 0x20;
            *out = minShifted | kAndFlag;
        }
        out += 2;
        *out = 5;
        out += 2;
        *out = 0x80000004CC007FFBL;
        out[2] = 0;
    }
}

/* func_00293000 is in 00293000-g8.c. */

/* Turns the offsets stored in one asset block into real addresses. */
void relocate_asset_entry_pointers(int *table, int index){
  BatchA_A02_Blk *block;
  int i;
  table += index;
  block = *(BatchA_A02_Blk **)((char *)table + 0x48);
  if (block->off) block->off = (int)block + block->off;
  for (i = 0; i < block->n; i++) block->ent[i] = (int)block + block->ent[i];
}


/* Relocate render groups and remap each run's texture selectors. */
void tex_relocate_render_groups(RenderHeader *base, char *textures, unsigned char *map)
{
    int count = base->count[0] + base->count[1] + base->count[2];
    int *groups = (int *)((char *)base + base->groups);
    int *p = groups;
    int *runs = (int *)((char *)base + base->runs);

    if (count) {
        int n = count;
        do {
            int off = p[0];
            if (off < g_loader_memory[2]) {
                p[0] = off + (int)base;
                p[2] += (int)base;
            }
            n--;
            p += 4;
        } while (n);
    }
    {
        int *r = runs;
        for (;;) {
            unsigned char *sel = (unsigned char *)r;
            r[3] += (int)base;
            if (*sel != 255) {
                do {
                    *sel = map[*sel];
                    sel++;
                } while (*sel != 255);
            }
            if (r[3] < 0)
                break;
            r += 4;
        }
    }
    tex_draw_batches(groups, textures, map, count);
}



/* Copies four header bytes and turns two stored offsets into real addresses. */
void load_copy_header_relocate_pointers(u8 *dest, u8 *src) {
    *(u8 *)(dest + 4) = *(u8 *)(src + 0);
    *(u8 *)(dest + 5) = *(u8 *)(src + 1);
    *(u8 *)(dest + 6) = *(u8 *)(src + 2);
    *(u8 *)(dest + 7) = *(u8 *)(src + 3);
    *(u8 **)(dest + 0x0) = src + *(s32 *)(src + 4);
    *(u8 **)(dest + 0x20) = src + *(s32 *)(src + 8);
}


/* func_00293890 is in 00291758-g8.c. */


/* RAC1 loaders.c: load_level_chunk_from_disc. Reads the level's data from the
   disc table into the top of memory, below D_01FF7FF0; the ceiling is a linker
   address, so alignment is applied after subtracting the read size. */
int LoadLevelChunkFromDisc(void)
{
    DiscToc *toc = &g_copy_setup_data;
    int sectors = toc->level.size;
    int bytes = ((sectors << 11) + 0x1057) & 0xFFFFF000;
    int addr = ((int)g_load_memory_ceiling - bytes) & -16;

    g_level_data_ptr = (int *)addr;
    *(unsigned int *)addr = 0x60;
    load_read_disc_sectors_blocking((int)g_level_data_ptr + *g_level_data_ptr, toc->level.sector + toc->level_base, toc->level.size);
    return 1;
}


/* RAC1 loaders.c: service_level_archive_load. One step of the level archive
   load: while the disc is busy, counts frames and after 720 at full speed
   drops to the slower mode and steps back a stage; a read error does the
   same once. Then by stage: reads the two archives of the disc table below
   the top of memory (the second one highest), waits for the reads, starts
   the sound bank loads and waits for each bank's status. Returns 1 when the
   load is done. */
int ServiceLevelArchiveLoad(void)
{
    snd_clear_flag_and_update();
    snd_Pump();
    if (snd_CheckLoadInProgress(1)) {
        ++g_cd_error_retry_count;
        if (g_load_read_mode == 1 && g_cd_error_retry_count > 720) {
            g_cd_error_seen = 1;
            g_load_read_mode = 0;
            if (g_loader_archives.stage < 3)
                g_loader_archives.stage--;
            snd_run_handler_or_send_cmd37();
        }
        return 0;
    }
    if (sceCdGetError() && !g_cd_error_seen) {
        g_cd_error_seen = 1;
        g_load_read_mode = 0;
        if (g_loader_archives.stage < 3)
            g_loader_archives.stage--;
    }
    switch (g_loader_archives.stage) {
    case 0: {
        DiscToc *toc = &g_copy_setup_data;
        unsigned int bytes;

        bytes = ((toc->archive1.size << 11) + 4095) & 0xFFFFF000;
        g_loader_archives.archive1 = g_archive_end_address - bytes;
        bytes = ((toc->archive0.size << 11) + 4095) & 0xFFFFF000;
        g_loader_archives.archive0 = g_loader_archives.archive1 - bytes;
        g_load_header_flag[0] = 0;
        load_read_disc_sectors_blocking(g_loader_archives.archive0, toc->archive0.sector + toc->archive_base, toc->archive0.size);
        g_loader_archives.stage++;
        break;
    }
    case 1:
        load_read_disc_sectors_blocking(g_loader_archives.archive1, g_copy_setup_data.archive1.sector + g_copy_setup_data.archive_base,
                      g_copy_setup_data.archive1.size);
        g_loader_archives.stage++;
        break;
    case 2:
        if (g_loader_archives.busy)
            return 0;
        snd_print_status();
        snd_load_first_bank();
        g_loader_archives.stage++;
        break;
    case 3:
        snd_Pump();
        if (g_load_relocate_a != -1)
            g_loader_archives.stage++;
        break;
    case 4:
        snd_load_bank_entry(0);
        g_loader_archives.stage++;
        break;
    case 5:
        snd_Pump();
        if (g_load_relocate_b != -1) {
            func_00132828();
            return 1;
        }
        break;
    }
    return 0;
}


/* Reads the part of the current chunk between this entry and the next one from the disc, when it is not empty. Always returns 1. */
int load_chunk_part_from_disc(int index)
{
    int nextIndex = index + 1;
    int *state = F46b43b72_D_001B8840;
    int *toc = F46b43b72_D_0014B540;
    int *offsetTable = (int *)((char *)toc + 25416);
    int size = state[12] * 332;
    int buffer = state[28];
    int nextOffset = nextIndex * 4;
    int startOffset = *(int *)((char *)offsetTable + (size + index * 4));
    int endOffset = *(int *)((char *)offsetTable + (nextOffset + size));

    size = endOffset - startOffset;
    if (size > 0) {
        F46b43b72_FUN_002B7B18(buffer, (char *)(startOffset + toc[6341]));
        F46b43b72_FUN_002B7CE0(0);
    }
    return 1;
}

/* The streamed parts table: the base sector at 0x3E24 and a sector/size
   pair per set of parts. */
typedef struct { int sector, size; } PartsFile;
typedef struct {
    char pad0[0x3E24];
    int base;              /* 0x3E24 */
    PartsFile files[1];    /* 0x3E28 */
} PartsToc;
extern PartsToc parts_toc __asm__("D_0014B540");
/* The record a part load reads: per part, its offset and a count. */
typedef struct { int offset, count; } PartEntry;
typedef struct {
    char pad0[0x30];
    int index;             /* 0x30 */
    char pad34[0x70 - 0x34];
    PartEntry *rec;        /* 0x70 */
    int parts[0x46];       /* 0x74 */
} PartsState;
extern PartsState parts_state __asm__("D_001B8840");
extern int load_start_disc_read(int, int, int);
extern void FadeToBlack(int);

/* Loads a set of parts from the disc into the record buffer and points each part at its data. */
void load_parts_set_from_disc(int index, int flag)
{
    PartEntry *entry;
    int i;

    load_start_disc_read((int)parts_state.rec, parts_toc.files[index].sector + parts_toc.base,
                  parts_toc.files[index].size);
    if (flag != 0) {
        snd_pump_music_and_disc_read(0);
        FadeToBlack(flag);
    }
    parts_state.index = index;
    snd_pump_music_and_disc_read(1);
    for (i = 0, entry = parts_state.rec; i < 0x46 && entry->count != 0; i++, entry++) {
        int offset = entry->offset + 0x800;
        parts_state.parts[i] = (int)parts_state.rec + offset;
    }
}

struct SegTable {
    int pad[0x1C];
    int cur;
    int entry[1];
};

extern struct SegTable ref_00294070_00;
extern int ref_00294070_01;
extern int ref_00294070_02 __attribute__((sda));
extern void load_relocate_world_object_parts(void);

/* Copy one entry of the segment table into its current slot, let the world
   update run, then store the sum of the two counters there. */
void load_select_segment_update_world(int index)
{
    struct SegTable *table = &ref_00294070_00;

    table->cur = table->entry[index];
    load_relocate_world_object_parts();
    table->cur = ref_00294070_01 + ref_00294070_02;
}

/* Clears the class cache table and marks all its slots as empty. */
void load_clear_class_cache_table(void)
{
    extern void mem_clear(unsigned int *, unsigned int, int);
    struct Table2 *table = &Fee2b87d1_D_00152CD0;
    int i;
    mem_clear((unsigned int *)table, 0, 0x35840);
    *(short *)((char *)table + 0x14) = -1;
    for (i = 2; i >= 0; --i)
        table->slots[i] = -1;
}


/* func_00294130 is matched in 00291758-g8.c (-G8 small data). */



extern s32 load_start_disc_entry(int, int, int, int);

/* Looks the id up in the class table and starts loading it into the given cache slot if it is not already there. */
void load_class_into_cache_slot(int id, int index)
{
    int i = 0;
    if (Fee2b87d1_D_0014B540.slots[0].w == id) goto after;
    while (++i < 48) {
        if (Fee2b87d1_D_0014B540.slots[i].w == id) break;
    }
after:
    if (i == 48) return;
    if (Fee2b87d1_D_00152CD0.slots[index] == i) return;
    load_start_disc_entry(i, index, (int)((char *)&Fee2b87d1_D_00152CD0 + 0x40 + index * 0xC800), 0);
}


extern void load_class_into_cache_slot(int a0, int a1);

/* Loads a class into a cache slot, waiting for pending disc reads before and after. */
void load_class_into_cache_slot_synced(void *id, void *slotIndex)
{
    F46b43b72_FUN_002B7CE0(1);
    load_class_into_cache_slot(id, slotIndex);
    F46b43b72_FUN_002B7CE0(1);
}

/* Checks whether the class with this id is already in one of the three cache slots. Returns 1 if it is unknown or loaded. */
s32 load_is_class_cached(s32 value) {
    s32 i = 0;
    s32 *q;
    if (Fee2b87d1_D_0014B540.slots[0].w == value) goto after1;
    while (++i < 48) {
        if (Fee2b87d1_D_0014B540.slots[i].w == value) break;
    }
after1:
    if (i == 48) return 1;
    value = 0;
    if (Fee2b87d1_D_00152CD0.slots[0] == i) goto after2;
    while (++value < 3) {
        if (Fee2b87d1_D_00152CD0.slots[value] == i) break;
    }
after2:
    return value != 3;
}

/* Loads one cached moby class: an optional texture part (data[2], when
   data[3] is set), decompressed into the decode buffer and, when it is a
   16x16-CLUT 8-bit image, uploaded to VRAM; then the class itself (data[0]),
   decompressed into the same buffer and prepared by func_00293890 with the
   slot's one-entry material map and with D_001B1B40 set to the slot for the
   call. The offsets in data are relative to slot index's disc sector. Each
   of the loaded class's 32-byte entries (count at +13, table at +0x28) then
   gets 4 at +0x1C, and func_0026FEB8 prints the values of func_001337F0 and
   func_00133820. The image transfer and the material map share one buffer. */
void load_cached_moby_class(int id, int index, int *data)
{
    union { GsLoadImage image; unsigned char map[16]; } work;
    int saved, i;
    ClassData *loaded;

    if (data[3]) {
        char *src = (char *)data + data[2] - (g_copy_setup_data.slots[index].sector << 11);

        FlushCache(0);
        fast_decompress(src, &g_decode_header);
        FlushCache(0);
        if (g_decode_header.type == 1) {
            int tbw, width, offset;
            char *pixels;

            func_00126288(&work.image, (g_vram_clut_third >> 8) + g_load_slots.clut_offset, 1, 0, 0, 0, 16, 16);
            FlushCache(0);
            sceGsExecLoadImage(&work.image, g_decoded_image_buffer);
            gfx_wait_paths_idle(0, 0);
            offset = g_load_slots.image_offset << 2;
            width = g_decoded_image_width;
            tbw = width >> 6;
            pixels = g_decoded_pixels;
            if (tbw < 1)
                tbw = 1;
            func_00126288(&work.image, (g_vram_pixel_base + offset) >> 8, tbw, 0x1B, 0, 0, width, width);
            FlushCache(0);
            sceGsExecLoadImage(&work.image, pixels);
            gfx_wait_paths_idle(0, 0);
        }
    }
    {
        char *src = (char *)data + data[0] - (g_copy_setup_data.slots[index].sector << 11);

        FlushCache(0);
        fast_decompress(src, &g_decode_header);
        FlushCache(0);
    }
    {
        ClassCache *cache = &g_load_slots;
        DecodeHeader *decoded = &g_decode_header;

        saved = g_class_cache_count;
        work.map[0] = cache->map;
        g_class_cache_count = cache->slot;
        load_register_class_cache_object(decoded, (char *)cache - (cache->map << 4), work.map, id);
        g_class_cache_sizes[cache->slot] = 0xFFF00000;
        loaded = g_class_cache_objects[g_class_slot_lookup[id]];
        g_class_cache_count = saved;
    }
    for (i = 0; i < loaded->entry_count; i++)
        loaded->entries[i].f1C = 4;
    {
        char *format = g_str_class_cache_format;
        int first = func_001337F0();
        int second = func_00133820();

        STUB_printf(format, first, second);
    }
}

/* func_00294988 is in 00294988-g8.c. */
