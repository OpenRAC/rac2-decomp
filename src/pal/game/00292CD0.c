#include "include_asm.h"

typedef unsigned char u8;
extern void func_PAL_00292988(int);
extern void func_00292328(void *);
extern u8 *D_L03_001DAB80[];
extern void func_002934B8(u8 *, u8 *);
extern unsigned char *D_001BAF38;

INCLUDE_ASM("asm/pal/game", func_PAL_00292CD0);





extern int func_00282A18(int);
typedef struct { long w[12]; } GsLoadImage __attribute__((aligned(16)));
extern void func_002FC3C0(unsigned long);
extern short func_PAL_002B8898(int);
extern int func_PAL_002B8838(void *, int, int);
extern int func_00126288(GsLoadImage *, short, short, short, short, short, short, short);
extern void func_0011AEA0(int);
extern int func_001265B0(GsLoadImage *, void *);
extern int func_001244B8(int, unsigned short);
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
void func_PAL_00292FC8(int index)
{
    GsLoadImage packet;
    char *base;
    char *clut;
    UploadState *state;
    UploadTable *table;
    int width, log;

    state = &D_00152C00;
    state->index = index;
    func_002FC3C0(1);
    base = (char *)D_001B22A0[1 - D_001B22B4[0]];
    func_PAL_002B8898(1);
    clut = base + 0x20;
    table = &upload_table;
    func_PAL_002B8838(base, table->entries[index].off + table->base, table->entries[index].size);
    func_00126288(&packet, D_001A72F0[0] >> 8, 1, 0, 0, 0, 16, 16);
    func_0011AEA0(0);
    func_001265B0(&packet, clut);
    func_001244B8(0, 0);
    log = func_00282A18(*(int *)(base + 8));
    width = *(int *)(base + 8) >> 6;
    if (width < 1)
        width = 1;
    func_00126288(&packet, D_001A7300[0] >> 8, width, 27, 0, 0, *(short *)(base + 8), *(short *)(base + 12));
    func_0011AEA0(0);
    func_001265B0(&packet, base + 0x420);
    func_001244B8(0, 0);
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

