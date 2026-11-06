#include "include_asm.h"

/* func_US2_00292928, the USA v2.00 copy of func_00292078: the same C, where the
   four pack flags sit 8 bytes higher. */

extern int func_00282A18(int);

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
} DiscToc;
extern DiscToc D_0014B540;
extern unsigned long long D_001A72A0[] __attribute__((sda));

/* Boot data words reached at their fixed addresses, which gives the retail
   code's absolute (lui) addressing. */
#define LOAD_BUFFER (*(int **)0x001A7294)
#define LOAD_COUNT (*(int *)0x001A7298)
#define CLUT_VRAM (*(int *)0x001A72E8)
#define IMAGE_VRAM (*(int *)0x001A72F8)
#define PACK_FLAG_5 (*(unsigned char *)0x001A7A52)
#define PACK_FLAG_6 (*(unsigned char *)0x001A7A51)
#define PACK_FLAG_7 (*(unsigned char *)0x001A7A53)
#define PACK_FLAG_8 (*(unsigned char *)0x001A7A4A)

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

/* Loads the texture pack of a program: see func_00292078. */
void func_US2_00292928(int pack)
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

    func_002FC3C0(1);
    buffer = LOAD_BUFFER;
    func_002B7CE0(1);

    if (PACK_FLAG_6)
        pack = 6;
    else if (PACK_FLAG_8)
        pack = 8;
    else if (PACK_FLAG_7)
        pack = 7;
    else if (PACK_FLAG_5)
        pack = 5;

    cursor = buffer + 1;
    func_002B7C80(buffer, D_0014B540.packs[pack].sector2 + D_0014B540.base,
                  D_0014B540.packs[pack].size2);

    image_vram = IMAGE_VRAM;
    LOAD_COUNT = buffer[0];
    clut_vram = CLUT_VRAM;

    for (i = 0; i < LOAD_COUNT; i++) {
        record = (TextureRecord *)((char *)buffer + *cursor);
        clut_page = clut_vram >> 8;
        clut = record->clut;
        func_00126288(&work, clut_page, 1, 0, 0, 0, 16, 16);
        func_0011AEA0(0);
        func_001265B0(&work, clut);
        func_001244B8(0, 0);
        clut_vram += 0x400;
        n = func_00282A18(record->width);
        tbw = record->width >> 6;
        if (tbw < 1)
            tbw = 1;
        image_page = image_vram >> 8;
        func_00126288(&work, image_page, tbw, 0x1B, 0, 0, record->width, record->height);
        func_0011AEA0(0);
        func_001265B0(&work, record->pixels);
        func_001244B8(0, 0);
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

    func_002B7C80(buffer, D_0014B540.packs[pack].sector + D_0014B540.base,
                  D_0014B540.packs[pack].size);
}
