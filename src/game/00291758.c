#include "include_asm.h"
#include "names.h"

typedef struct { unsigned char count[4]; int groups, runs; } RenderHeader;
extern int D_001BAEC0[];
extern void func_002932B8(int *, char *, unsigned char *, int);

extern int *D_001A7288 __attribute__((section(".sdata")));
extern char D_01FF7FF0[];
extern int func_002B7C10(int, int, int);

extern int D_001B1DA4 __attribute__((sda));
extern char D_001F2740[];
extern int D_001F2540[];
extern int func_00282A18(int);
extern void func_00282AB0(void *, void *, int);



extern void func_00294130(int *, int);

extern void func_00292B88(void *, void *, int, int, int, int, int);

extern void func_00291788(int);

extern void func_00291640(int);

typedef struct { long w[12]; } GsLoadImage __attribute__((aligned(16)));
extern void func_002FC3C0(unsigned long);
extern short func_002B7CE0(int);
extern int func_002B7C80(void *, int, int);
extern int func_00126288(GsLoadImage *, short, short, short, short, short, short, short);
extern void func_0011AEA0(int);
extern int func_001265B0(GsLoadImage *, void *);
extern int func_001244B8(int, unsigned short);
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
extern DiscToc D_0014B540;
extern unsigned long long D_001A72A0[] __attribute__((sda));

extern void func_00133230(void);
extern int func_00132028(void);
extern int func_00133580(int);
extern int func_00133640(void);
extern int func_00125588(void);
extern void func_002E4A68(void);
extern void func_002B6788(void);
extern void func_002B6828(int);
/* The callee at 0x00132828 (the catalogue names it func_00132818). */
extern int func_00132828(void);
/* As in RAC1: the disc wait-frame count, a flag set once the load has
   been stepped back, and a mode word that is 1 until then. */
extern int D_001A7430 __attribute__((sda));
extern int D_001A7434 __attribute__((sda));
extern int D_001A7900 __attribute__((sda));
/* The level archive load: stage, busy flag and the two archive buffers
   (archive0 is the level data D_001A7288 points at). */
typedef struct { int stage, busy, archive0, archive1; } ArchiveLoad;
extern ArchiveLoad D_001A7280 __attribute__((sda));
extern int D_001BAF2C;
extern short D_00152C2C[];
/* The two sound bank statuses: -1 while a load is pending. */
extern unsigned int D_00189E00, D_00189E04;

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
extern ClassCache D_00152CD0;
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
extern DecodeHeader D_00178510;
extern int D_00178528;
extern char D_00178540[];
extern char D_00178940[];
extern char D_001A9340[];
extern int D_001A72F4 __attribute__((sda));
extern int D_001A7304 __attribute__((sda));
extern int D_001B1B40 __attribute__((sda));
extern int D_001D0E00[];
extern ClassData *D_001CDB80[];
extern unsigned char D_001CE4E0[];
extern int func_0029D4D0(void *, void *);
extern void func_00293890(void *, void *, void *, int);
extern int func_001337F0(void);
extern int func_00133820(void);
extern void func_0026FEB8(const char *, ...);

/* Frozen Batch A A02-list-add-88; acknowledged claim 38ceeb041b6ba12996de10c402ca54295587db96246845b83b2ec894986b096f. */
typedef unsigned char BatchA_A02_u8;

typedef int BatchA_A02_s32;

typedef struct { char _0[0x10]; BatchA_A02_u8 n; char _11[3]; BatchA_A02_s32 off; char _18[4]; BatchA_A02_s32 ent[1]; } BatchA_A02_Blk;

typedef int s32;

typedef unsigned char u8;

extern void F46b43b72_FUN_002B7B18(int value, char *target);

extern void F46b43b72_FUN_002B7CE0(int value);

extern int F46b43b72_D_001B8840[];

extern int F46b43b72_D_0014B540[];

struct Slot { s32 w; s32 rest[4]; };

struct Table1 { char pad[19264]; struct Slot slots[48]; };

struct Table2 { char pad[52]; s32 slots[4]; };

extern struct Table1 Fee2b87d1_D_0014B540;

extern struct Table2 Fee2b87d1_D_00152CD0;

/* Frees the old part data of a light and rebuilds its sections. */
void func_00291758(int param_1)
{
    FlushLightPartIndices(param_1);
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
void func_00291788(int index)
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
extern volatile TextureRange D_001F1F40[];

/* Rebases the offset table of a loaded pack onto the copy of its data in
   D_001F2740, then fills the texture range table from count four-word list
   entries. */
void func_00291CA8(int *hdr, int base, int *list, int count)
{
    int n = hdr[0];
    int data_off = hdr[2];
    int data_size = hdr[3];
    int *entry = hdr + 4;
    int i;

    for (i = 0; i < n; i++, entry++) {
        if (*entry == 0)
            D_001F2540[i] = (int)D_001F2740;
        else
            D_001F2540[i] = *entry - (data_off - (int)D_001F2740);
    }
    CopyMemoryAligned(D_001F2740, (char *)hdr + data_off, data_size);
    for (D_001B1DA4 = 0; D_001B1DA4 < count; D_001B1DA4++) {
        int src_page = base + *list++;
        int src_offset = *list++;
        int dst_page = base + *list++;
        int dst_size = *list++;

        D_001F1F40[D_001B1DA4].a = (src_page << 4) + src_offset;
        D_001F1F40[D_001B1DA4].b = (dst_page << 4) + log2dim(dst_size);
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
void func_00292078(int pack)
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

    WaitForDmaStatusBits(1);
    buffer = LOAD_BUFFER;
    PumpMusicAndDiscRead(1);

    if (PACK_FLAG_6)
        pack = 6;
    else if (PACK_FLAG_8)
        pack = 8;
    else if (PACK_FLAG_7)
        pack = 7;
    else if (PACK_FLAG_5)
        pack = 5;

    cursor = buffer + 1;
    ReadDiscWithPause(buffer, gCopySetupData.packs[pack].sector2 + gCopySetupData.base,
                  gCopySetupData.packs[pack].size2);

    image_vram = IMAGE_VRAM;
    LOAD_COUNT = buffer[0];
    clut_vram = CLUT_VRAM;

    for (i = 0; i < LOAD_COUNT; i++) {
        record = (TextureRecord *)((char *)buffer + *cursor);
        clut_page = clut_vram >> 8;
        clut = record->clut;
        func_00126288(&work, clut_page, 1, 0, 0, 0, 16, 16);
        FlushCache(0);
        ExecGsLoadImage(&work, clut);
        WaitGsPathsIdle(0, 0);
        clut_vram += 0x400;
        n = log2dim(record->width);
        tbw = record->width >> 6;
        if (tbw < 1)
            tbw = 1;
        image_page = image_vram >> 8;
        func_00126288(&work, image_page, tbw, 0x1B, 0, 0, record->width, record->height);
        FlushCache(0);
        ExecGsLoadImage(&work, record->pixels);
        WaitGsPathsIdle(0, 0);
        a = ((unsigned long long)n << 26) | 0x1B00000;
        tag = (unsigned long long)image_page | ((unsigned long long)tbw << 14);
        tag |= a;
        tag |= (unsigned long long)n << 30;
        f = ((unsigned long long)clut_page << 37) | 0x400000000ULL;
        tag |= f;
        D_001A72A0[i] = tag | 0x8000000000000000ULL;
        image_vram += record->width * record->height * 4;
        cursor++;
    }

    ReadDiscWithPause(buffer, gCopySetupData.packs[pack].sector + gCopySetupData.base,
                  gCopySetupData.packs[pack].size);
}


extern void func_00292078(int);
extern void func_00292328(void *);
extern u8 *D_L03_001DAB80[];
extern void func_002934B8(u8 *, u8 *);
extern unsigned char *D_001BAF38;

/* Loads the texture pack of a level and its draw packets, then remembers the level number. */
void func_002923C0(void *level)
{
    LoadTexturePackToVram(level);
    BuildTextureDrawPackets(level);
    CopyHeaderAndRelocatePointers((u8 *)D_L03_001DAB80[0], D_001BAF38);
    *(int *)0x001A7290 = (int)level;
}


/* func_00292408 is in 00292408.c. */



typedef struct { int off, size; } UploadPair;
typedef struct { char p0[0x3e24]; int base; char p1[0x48f0-0x3e28]; UploadPair entries[1]; } UploadTable;
extern UploadTable upload_table __asm__("D_0014B540");
typedef struct { char p0[0x30]; int index; char p1[4]; long word; } UploadState;
extern UploadState D_00152C00;
extern int D_001B22A0[];
extern int D_001B22B4[] __attribute__((sda));
extern int D_001A72F0[] __attribute__((sda));
extern int D_001A7300[] __attribute__((sda));

/* Reads entry index of the disc table into the free one of the two buffers at
   D_001B22A0, uploads its 16x16 CLUT (at +0x20) and 8-bit image (at +0x420, width
   and height at +8 and +0xC) to VRAM at the addresses in D_001A72F0 and D_001A7300,
   and stores the image's GS TEX0 word and the index in D_00152C00. */
void func_002926B8(int index)
{
    GsLoadImage packet;
    char *base;
    char *clut;
    UploadState *state;
    UploadTable *table;
    int width, log;

    state = &gHeroMoby_00152C00;
    state->index = index;
    WaitForDmaStatusBits(1);
    base = (char *)D_001B22A0[1 - D_001B22B4[0]];
    PumpMusicAndDiscRead(1);
    clut = base + 0x20;
    table = &upload_table;
    ReadDiscWithPause(base, table->entries[index].off + table->base, table->entries[index].size);
    func_00126288(&packet, D_001A72F0[0] >> 8, 1, 0, 0, 0, 16, 16);
    FlushCache(0);
    ExecGsLoadImage(&packet, clut);
    WaitGsPathsIdle(0, 0);
    log = log2dim(*(int *)(base + 8));
    width = *(int *)(base + 8) >> 6;
    if (width < 1)
        width = 1;
    func_00126288(&packet, D_001A7300[0] >> 8, width, 27, 0, 0, *(short *)(base + 8), *(short *)(base + 12));
    FlushCache(0);
    ExecGsLoadImage(&packet, base + 0x420);
    WaitGsPathsIdle(0, 0);
    {
        long image, tex, format, clut_base, word;

        image = (long)D_001A7300[0] >> 8;
        tex = image | ((long)width << 14);
        format = ((long)log << 26) | 0x1b00000L;
        tex |= format;
        tex |= (long)log << 30;
        clut_base = (((long)D_001A72F0[0] >> 8) << 37) | 0x400000000L;
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
void func_00292EB0(long *out, int lodK, int minFilter, int clampMode, int flagBits, int rowIndex) {
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
void func_00293260(int *table, int index){
  BatchA_A02_Blk *block;
  int i;
  table += index;
  block = *(BatchA_A02_Blk **)((char *)table + 0x48);
  if (block->off) block->off = (int)block + block->off;
  for (i = 0; i < block->n; i++) block->ent[i] = (int)block + block->ent[i];
}


/* Relocate render groups and remap each run's texture selectors. */
void func_002933D0(RenderHeader *base, char *textures, unsigned char *map)
{
    int count = base->count[0] + base->count[1] + base->count[2];
    int *groups = (int *)((char *)base + base->groups);
    int *p = groups;
    int *runs = (int *)((char *)base + base->runs);

    if (count) {
        int n = count;
        do {
            int off = p[0];
            if (off < D_001BAEC0[2]) {
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
    DrawTextureBatches(groups, textures, map, count);
}



/* Copies four header bytes and turns two stored offsets into real addresses. */
void func_002934B8(u8 *dest, u8 *src) {
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
int func_002939D0(void)
{
    DiscToc *toc = &gCopySetupData;
    int sectors = toc->level.size;
    int bytes = ((sectors << 11) + 0x1057) & 0xFFFFF000;
    int addr = ((int)D_01FF7FF0 - bytes) & -16;

    D_001A7288 = (int *)addr;
    *(unsigned int *)addr = 0x60;
    ReadDiscSectorsBlocking((int)D_001A7288 + *D_001A7288, toc->level.sector + toc->level_base, toc->level.size);
    return 1;
}


/* RAC1 loaders.c: service_level_archive_load. One step of the level archive
   load: while the disc is busy, counts frames and after 720 at full speed
   drops to the slower mode and steps back a stage; a read error does the
   same once. Then by stage: reads the two archives of the disc table below
   the top of memory (the second one highest), waits for the reads, starts
   the sound bank loads and waits for each bank's status. Returns 1 when the
   load is done. */
int func_00293A60(void)
{
    ClearSoundFlagAndUpdate();
    snd_Pump();
    if (snd_CheckLoadInProgress(1)) {
        ++D_001A7430;
        if (D_001A7900 == 1 && D_001A7430 > 720) {
            D_001A7434 = 1;
            D_001A7900 = 0;
            if (D_001A7280.stage < 3)
                D_001A7280.stage--;
            RunHandlerOrSendSoundCommand37();
        }
        return 0;
    }
    if (GetCdLastError() && !D_001A7434) {
        D_001A7434 = 1;
        D_001A7900 = 0;
        if (D_001A7280.stage < 3)
            D_001A7280.stage--;
    }
    switch (D_001A7280.stage) {
    case 0: {
        DiscToc *toc = &gCopySetupData;
        unsigned int bytes;

        bytes = ((toc->archive1.size << 11) + 4095) & 0xFFFFF000;
        D_001A7280.archive1 = D_001BAF2C - bytes;
        bytes = ((toc->archive0.size << 11) + 4095) & 0xFFFFF000;
        D_001A7280.archive0 = D_001A7280.archive1 - bytes;
        D_00152C2C[0] = 0;
        ReadDiscSectorsBlocking(D_001A7280.archive0, toc->archive0.sector + toc->archive_base, toc->archive0.size);
        D_001A7280.stage++;
        break;
    }
    case 1:
        ReadDiscSectorsBlocking(D_001A7280.archive1, gCopySetupData.archive1.sector + gCopySetupData.archive_base,
                      gCopySetupData.archive1.size);
        D_001A7280.stage++;
        break;
    case 2:
        if (D_001A7280.busy)
            return 0;
        PrintSoundStatus();
        LoadFirstSoundBank();
        D_001A7280.stage++;
        break;
    case 3:
        snd_Pump();
        if (D_00189E00 != -1)
            D_001A7280.stage++;
        break;
    case 4:
        LoadSoundBankEntry(0);
        D_001A7280.stage++;
        break;
    case 5:
        snd_Pump();
        if (D_00189E04 != -1) {
            func_00132828();
            return 1;
        }
        break;
    }
    return 0;
}


/* Reads the part of the current chunk between this entry and the next one from the disc, when it is not empty. Always returns 1. */
int func_00293CA8(int index)
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
extern int func_002B7B18(int, int, int);
extern void func_0027D330(int);

/* Loads a set of parts from the disc into the record buffer and points each part at its data. */
void func_00293F98(int index, int flag)
{
    PartEntry *entry;
    int i;

    StartDiscRead((int)parts_state.rec, parts_toc.files[index].sector + parts_toc.base,
                  parts_toc.files[index].size);
    if (flag != 0) {
        PumpMusicAndDiscRead(0);
        FadeToBlack(flag);
    }
    parts_state.index = index;
    PumpMusicAndDiscRead(1);
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
extern void func_00293D30(void);

/* Copy one entry of the segment table into its current slot, let the world
   update run, then store the sum of the two counters there. */
void func_00294070(int index)
{
    struct SegTable *table = &ref_00294070_00;

    table->cur = table->entry[index];
    RelocateWorldObjectParts();
    table->cur = ref_00294070_01 + ref_00294070_02;
}

/* Clears the class cache table and marks all its slots as empty. */
void func_002940C0(void)
{
    extern void func_00282A60(unsigned int *, unsigned int, int);
    struct Table2 *table = &Fee2b87d1_D_00152CD0;
    int i;
    ClearMemory((unsigned int *)table, 0, 0x35840);
    *(short *)((char *)table + 0x14) = -1;
    for (i = 2; i >= 0; --i)
        table->slots[i] = -1;
}


/* func_00294130 is matched in 00291758-g8.c (-G8 small data). */



extern void func_002942A0(int, int, int, int);

/* Looks the id up in the class table and starts loading it into the given cache slot if it is not already there. */
void func_00294398(int id, int index)
{
    int i = 0;
    if (Fee2b87d1_D_0014B540.slots[0].w == id) goto after;
    while (++i < 48) {
        if (Fee2b87d1_D_0014B540.slots[i].w == id) break;
    }
after:
    if (i == 48) return;
    if (Fee2b87d1_D_00152CD0.slots[index] == i) return;
    StartDiscEntryLoad(i, index, (int)((char *)&Fee2b87d1_D_00152CD0 + 0x40 + index * 0xC800), 0);
}


extern void func_00294398(int a0, int a1);

/* Loads a class into a cache slot, waiting for pending disc reads before and after. */
void func_002945E8(void *id, void *slotIndex)
{
    F46b43b72_FUN_002B7CE0(1);
    LoadClassIntoCacheSlot(id, slotIndex);
    F46b43b72_FUN_002B7CE0(1);
}

/* Checks whether the class with this id is already in one of the three cache slots. Returns 1 if it is unknown or loaded. */
s32 func_00294630(s32 value) {
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
void func_002946C0(int id, int index, int *data)
{
    union { GsLoadImage image; unsigned char map[16]; } work;
    int saved, i;
    ClassData *loaded;

    if (data[3]) {
        char *src = (char *)data + data[2] - (gCopySetupData.slots[index].sector << 11);

        FlushCache(0);
        fast_decompress(src, &D_00178510);
        FlushCache(0);
        if (D_00178510.type == 1) {
            int tbw, width, offset;
            char *pixels;

            func_00126288(&work.image, (D_001A72F4 >> 8) + D_00152CD0.clut_offset, 1, 0, 0, 0, 16, 16);
            FlushCache(0);
            ExecGsLoadImage(&work.image, D_00178540);
            WaitGsPathsIdle(0, 0);
            offset = D_00152CD0.image_offset << 2;
            width = D_00178528;
            tbw = width >> 6;
            pixels = D_00178940;
            if (tbw < 1)
                tbw = 1;
            func_00126288(&work.image, (D_001A7304 + offset) >> 8, tbw, 0x1B, 0, 0, width, width);
            FlushCache(0);
            ExecGsLoadImage(&work.image, pixels);
            WaitGsPathsIdle(0, 0);
        }
    }
    {
        char *src = (char *)data + data[0] - (gCopySetupData.slots[index].sector << 11);

        FlushCache(0);
        fast_decompress(src, &D_00178510);
        FlushCache(0);
    }
    {
        ClassCache *cache = &D_00152CD0;
        DecodeHeader *decoded = &D_00178510;

        saved = D_001B1B40;
        work.map[0] = cache->map;
        D_001B1B40 = cache->slot;
        RegisterClassCacheObject(decoded, (char *)cache - (cache->map << 4), work.map, id);
        D_001D0E00[cache->slot] = 0xFFF00000;
        loaded = D_001CDB80[D_001CE4E0[id]];
        D_001B1B40 = saved;
    }
    for (i = 0; i < loaded->entry_count; i++)
        loaded->entries[i].f1C = 4;
    {
        char *format = D_001A9340;
        int first = func_001337F0();
        int second = func_00133820();

        STUB_printf(format, first, second);
    }
}

/* func_00294988 is in 00294988-g8.c. */
