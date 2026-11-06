/* func_PAL_002948A8, the PAL copy of func_00293F98: the same C, where rename func_002B7CE0 becomes func_PAL_002B8898. */

extern void func_00291788(int);

extern short func_PAL_002B8898(int);
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
/* The callee at 0x00132828 (the catalogue names it func_00132818). */
/* As in RAC1: the disc wait-frame count, a flag set once the load has
   been stepped back, and a mode word that is 1 until then. */
/* The level archive load: stage, busy flag and the two archive buffers
   (archive0 is the level data D_001A7288 points at). */
typedef struct { int stage, busy, archive0, archive1; } ArchiveLoad;
extern ArchiveLoad D_001A7280 __attribute__((sda));
/* The two sound bank statuses: -1 while a load is pending. */
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
extern ClassData *D_001CDB80[];
/* Frozen Batch A A02-list-add-88; acknowledged claim 38ceeb041b6ba12996de10c402ca54295587db96246845b83b2ec894986b096f. */
typedef int s32;

typedef unsigned char u8;

struct Slot { s32 w; s32 rest[4]; };

struct Table1 { char pad[19264]; struct Slot slots[48]; };

struct Table2 { char pad[52]; s32 slots[4]; };

extern struct Table1 Fee2b87d1_D_0014B540;

extern struct Table2 Fee2b87d1_D_00152CD0;

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

/* Hands the three index pairs of one part-table entry to the routines that
   consume them and clears the indices. The index is a 32-bit one: the table
   holds eight entries. The three routines live at another address in every
   program, so they carry no address in their names. */
void func_00291788(int index);

/* func_00291850 is in 00291850.c. */

/* Texture ranges: the particle renderer (func_002B9420) hands this table to
   the toSPR DMA channel; C only ever writes it. */
typedef struct { int a, b; } TextureRange;
extern volatile TextureRange D_001F1F40[];

/* Rebases the offset table of a loaded pack onto the copy of its data in
   D_001F2740, then fills the texture range table from count four-word list
   entries. */
/* func_00291DE0 is matched in its own unit, 00291DE0.c. */

/* func_00291EC0 is in 00291DE0.c. */

/* Boot data words reached at their fixed addresses, which gives the retail
   code's absolute (lui) addressing. */
/* A texture record of the pack: width and height, a 16x16 CLUT and the 8-bit
   image after it. */
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
void func_00292078(int pack);

extern void func_00292078(int);
extern void func_002934B8(u8 *, u8 *);
/* func_00292408 is in 00292408.c. */

typedef struct { int off, size; } UploadPair;
typedef struct { char p0[0x3e24]; int base; char p1[0x48f0-0x3e28]; UploadPair entries[1]; } UploadTable;
extern UploadTable upload_table __asm__("D_0014B540");
typedef struct { char p0[0x30]; int index; char p1[4]; long word; } UploadState;
extern UploadState D_00152C00;
/* Reads entry index of the disc table into the free one of the two buffers at
   D_001B22A0, uploads its 16x16 CLUT (at +0x20) and 8-bit image (at +0x420, width
   and height at +8 and +0xC) to VRAM at the addresses in D_001A72F0 and D_001A7300,
   and stores the image's GS TEX0 word and the index in D_00152C00. */
/* func_00292888 is in 00292888-g8.c. */

/* func_00292B88 is in 00292B88.c. */

/* rac1-decomp src/game/loaders.c: func_00203808 */
/* Fills four A+D qwords (low dwords only) at out: a TEX1-style word
   (MXL bits from the second word of row arg5 of the 3-dword table
   r1_D_0019E640, MMAG 1, MMIN arg2, K arg1), then arg3 | arg4 << 2 |
   arg5 << 24, then the row's first and third words. A negative arg5 has
   no row: -2 and -3 take the rows r1_D_0019E7C0 and r1_D_0019E7D8 (and 5 for
   the second word), -1 a fixed constant and 0. The row is read before
   the sign test, as in retail. The OR operands are named locals so fold
   does not move the 0x20 to the end of the chain. */
/* func_00293000 is in 00293000-g8.c. */

void func_002934B8(u8 *a0, u8 *a1);

/* func_00293890 is in 00291758-g8.c. */

/* RAC1 loaders.c: load_level_chunk_from_disc. Reads the level's data from the
   disc table into the top of memory, below D_01FF7FF0; the ceiling is a linker
   address, so alignment is applied after subtracting the read size. */
/* RAC1 loaders.c: service_level_archive_load. One step of the level archive
   load: while the disc is busy, counts frames and after 720 at full speed
   drops to the slower mode and steps back a stage; a read error does the
   same once. Then by stage: reads the two archives of the disc table below
   the top of memory (the second one highest), waits for the reads, starts
   the sound bank loads and waits for each bank's status. Returns 1 when the
   load is done. */
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

void func_PAL_002948A8(int index, int flag)
{
    PartEntry *r;
    int i;

    func_002B7B18((int)parts_state.rec, parts_toc.files[index].sector + parts_toc.base,
                  parts_toc.files[index].size);
    if (flag != 0) {
        func_PAL_002B8898(0);
        func_0027D330(flag);
    }
    parts_state.index = index;
    func_PAL_002B8898(1);
    for (i = 0, r = parts_state.rec; i < 0x46 && r->count != 0; i++, r++) {
        int offset = r->offset + 0x800;
        parts_state.parts[i] = (int)parts_state.rec + offset;
    }
}

struct SegTable {
    int pad[0x1C];
    int cur;
    int entry[1];
};

extern struct SegTable ref_00294070_00;
/* Copy one entry of the segment table into its current slot, let the world
   update run, then store the sum of the two counters there. */
/* func_00294130 is matched in 00291758-g8.c (-G8 small data). */

void func_00294398(int value, int index);

extern void func_00294398(int a0, int a1);

/* Loads one cached moby class: an optional texture part (data[2], when
   data[3] is set), decompressed into the decode buffer and, when it is a
   16x16-CLUT 8-bit image, uploaded to VRAM; then the class itself (data[0]),
   decompressed into the same buffer and prepared by func_00293890 with the
   slot's one-entry material map and with D_001B1B40 set to the slot for the
   call. The offsets in data are relative to slot index's disc sector. Each
   of the loaded class's 32-byte entries (count at +13, table at +0x28) then
   gets 4 at +0x1C, and func_0026FEB8 prints the values of func_001337F0 and
   func_00133820. The image transfer and the material map share one buffer. */
/* func_00294988 is in 00294988-g8.c. */
