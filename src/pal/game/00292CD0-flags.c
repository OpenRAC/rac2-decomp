#include "include_asm.h"

#include "common.h"
typedef struct { int a, b, c, d; } PackEntry;
typedef struct {
    char pad0[0x4F04];
    int base;            
    char pad4F08[0x4F98 - 0x4F08];
    PackEntry packs[1];  
} PackToc;
extern PackToc D_0014B540;
extern char *D_001BAF34;
extern int D_001A72EC[] __attribute__((sda));
extern int D_001A72FC[] __attribute__((sda));
extern long D_001A72A0[] __attribute__((sda));
extern void func_0011AEA0(int);
extern int func_00282A18(int);
extern short func_PAL_002B8898(int);
extern void func_002FC3C0(int);
extern void func_PAL_002B8838(void *, int, int);
extern int func_00126288(void *, short, short, short, short, short, short, short);
extern int func_001265B0(void *, void *);
extern int func_001244B8(int, unsigned short);

/* Reads the second part of pack index into the load buffer and uploads the
   one texture record there, as RAC1's LoadPifAsPSMT8H does: its 16x16 CLUT
   (at +0x20 of the record, which starts at +0x10) to the VRAM address in
   D_001A72EC and its 8-bit image to the one in D_001A72FC, keeping the TEX0
   word in slot 5 of D_001A72A0. The pack's first part then replaces the buffer.
   The store goes through the table so that its symbol+offset is the assembler
   macro form (two words, never a delay slot). The named words and the order
   they are built in give retail's registers. */
void func_PAL_00292D18(int index)
{
    long packet[12] __attribute__((aligned(16)));
    char *base;
    char *hdr;
    PackToc *table;
    int width, log;
    char *clut;

    func_002FC3C0(1);
    base = D_001BAF34;
    func_PAL_002B8898(1);
    hdr = base + 0x10;
    clut = base + 0x30;
    table = &D_0014B540;
    func_PAL_002B8838(base, table->packs[index].c + table->base, table->packs[index].d);
    func_00126288(packet, D_001A72EC[0] >> 8, 1, 0, 0, 0, 16, 16);
    func_0011AEA0(0);
    func_001265B0(packet, clut);
    func_001244B8(0, 0);
    log = func_00282A18(*(int *)(hdr + 8));
    width = *(int *)(hdr + 8) >> 6;
    if (width < 1)
        width = 1;
    func_00126288(packet, D_001A72FC[0] >> 8, width, 27, 0, 0, *(short *)(hdr + 8), *(short *)(hdr + 12));
    func_0011AEA0(0);
    func_001265B0(packet, base + 0x430);
    func_001244B8(0, 0);
    {
        long image, tex, format, clut_base, word;

        image = (long)D_001A72FC[0] >> 8;
        tex = image | ((long)width << 14);
        format = ((long)log << 26) | 0x1b00000L;
        tex |= format;
        tex |= (long)log << 30;
        clut_base = (((long)D_001A72EC[0] >> 8) << 37) | 0x400000000L;
        word = tex | clut_base;
        word |= 0x8000000000000000UL;
        D_001A72A0[5] = word;
    }
    func_PAL_002B8838(base, table->packs[index].a + table->base, table->packs[index].b);
}
