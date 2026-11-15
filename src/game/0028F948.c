#include "include_asm.h"
#include "names.h"

/* Family 435a49e62f53b8db - 368 bytes, 2 members.
   Placements: levels/3_endako @0x002FC368, levels/19_grelbin @0x002F8AF8.

   Measured binding.  D_L03_001B3188 is a four-byte pointer in the resident image
   (0x001B3188 = 1782152).  The retail body reads it with a per-site
   `lui $r,%hi` + `lw $r,%lo($r)` pair and writes it with a single
   `sw $r,%lo($gp)`; all three of the latter sit in a compiler delay slot
   (two in the `b` before the branch target, one in the `jr $ra` slot).

   That mix is exactly gas's expansion of the bare-symbol macro form
   `lw $r,D_L03_001B3188` / `sw $r,D_L03_001B3188`: absolute `lui`+`%lo` in ordinary
   flow, `$gp` (GPREL16) inside a `.set nomacro` region.  cc1 emits that
   macro only for an `sda` symbol, so the declaration carries `sda`.
   Without it cc1 computes the symbol's address once, CSEs it into a base
   register and reloads `0($base)` per site, which also costs an extra
   `move` to keep the incoming `$a1` alive across that register - 344
   bytes against the 368 of the reference. */

extern int *D_L03_001B3188 __attribute__((sda));

extern void D_00126288(void *, short, short, int, int, int, short, short);

extern void FlushCache(int);

extern int sceGsExecLoadImage(void *, int);

/* Paired-strip packet emitter, 396 bytes, placed in levels/10_hrugis_cloud and
   levels/5_feltzin_system.  The body writes a 16-byte GIF header into the
   resident packet cursor (a small-data global), advances the cursor, then
   writes the tag words and two packed 64-bit strip descriptors.  The retail
   loads the cursor with LUI/LO and advances it through $gp, so the unit is
   compiled under the qualified small-data profile (-O2 -G8). */
extern int *D_L05_001B2C88_5 __attribute__((sda));

extern int D_001A7350_1 __attribute__((sda));

extern int D_001A7354_1 __attribute__((sda));

/* Paired-strip packet emitter, 396 bytes, placed in levels/19_grelbin and
   levels/3_endako.  The body writes a 16-byte GIF header into the
   resident packet cursor (a small-data global), advances the cursor, then
   writes the tag words and two packed 64-bit strip descriptors.  The retail
   loads the cursor with LUI/LO and advances it through $gp, so the unit is
   compiled under the qualified small-data profile (-O2 -G8). */
extern int *D_L03_001B3188_1 __attribute__((sda));

extern int g_screen_offset_x __attribute__((sda));

extern int g_screen_offset_y __attribute__((sda));

/* Family 9b94f3cd1f5fac83 (372 B, 2 placements).
   Retail builds a 64-byte packet from the resident cursor global D_L02_001B3D08 and
   then advances that global itself, so the closing store addresses the global
   through $gp: the qualified small-data profile is required.
   The four header words are written through the global expression, so each one
   carries its own reload of D_L02_001B3D08 before its store. */

extern int *D_L02_001B3D08 __attribute__((sda));

/* shared native body of family 435a49e62f53b8db (default profile) */
/* Copies an image into video memory, either straight into the draw list or through a temporary buffer. */
void gfx_upload_image_to_vram(int source, int vramBase, int format, int widthLog2, int heightLog2, int immediate)
{
    char buf[96];
    void *work;
    int bufferWidth;
    int quadCount;

    quadCount = 1 << (widthLog2 + heightLog2 - 4);
    bufferWidth = (1 << widthLog2) >> 6;
    if (bufferWidth <= 0)
        bufferWidth = 1;

    if (immediate == 0) {
        *(int *)D_L03_001B3188 = 0x10000006;
        *(int *)((char *)D_L03_001B3188 + 4) = 0;
        *(int *)((char *)D_L03_001B3188 + 8) = 0;
        *(int *)((char *)D_L03_001B3188 + 12) = 0x50000006;
        work = (char *)D_L03_001B3188 + 16;
        D_L03_001B3188 = (int *)((char *)D_L03_001B3188 + 112);
    } else {
        work = buf;
    }

    D_00126288(work, (short)vramBase, (short)bufferWidth, (short)format, 0, 0,
            (short)(1 << widthLog2), (short)(1 << heightLog2));

    if (immediate == 0) {
        *(int *)D_L03_001B3188 = 0x30000000 | quadCount;
        *(int *)((char *)D_L03_001B3188 + 4) = source;
        *(int *)((char *)D_L03_001B3188 + 8) = 0;
        *(int *)((char *)D_L03_001B3188 + 12) = 0x50000000 | quadCount;
        D_L03_001B3188 = (int *)((char *)D_L03_001B3188 + 16);
    } else {
        FlushCache(0);
        sceGsExecLoadImage(work, source);
    }
}

/* shared native body of family a6a1a427e2388f5f */
/* Draws a plain coloured line on the screen between two points. */
void gfx_draw_screen_line(int x0, int y0, int x1, int y1, int color, int isSubpixel)
{
    long long *q;

    *(int *)((char *)D_L05_001B2C88_5 + 0) = 0x10000003;
    *(int *)((char *)D_L05_001B2C88_5 + 4) = 0;
    *(int *)((char *)D_L05_001B2C88_5 + 8) = 0;
    *(int *)((char *)D_L05_001B2C88_5 + 12) = 0x50000003;
    q = (long long *)D_L05_001B2C88_5;
    D_L05_001B2C88_5 = (int *)((char *)q + 16);
    q[2] = 0x4400000000008001LL;
    q[3] = 17424;
    q[4] = 65;
    q[5] = color;
#define LO_D0 (*(int *)((char *)&D_001A7350_1 + 0))
#define HI_D4 (*(int *)((char *)&D_001A7354_1 + 0))

    if (isSubpixel != 0) {
        q[6] = (x0 + LO_D0 - 8)
             | ((long long)(y0 + HI_D4 - 8) << 16)
             | 0xFFFFF000000000LL;
        q[7] = (x1 + LO_D0 - 8)
             | ((long long)(y1 + HI_D4 - 8) << 16)
             | 0xFFFFF000000000LL;
    } else {
        q[6] = ((x0 << 4) + LO_D0 - 16)
             | ((long long)((y0 << 4) + HI_D4 - 16) << 16)
             | 0xFFFFF000000000LL;
        q[7] = ((x1 << 4) + LO_D0 - 16)
             | ((long long)((y1 << 4) + HI_D4 - 16) << 16)
             | 0xFFFFF000000000LL;
    }
    D_L05_001B2C88_5 = (int *)((char *)D_L05_001B2C88_5 + 48);
}

/* shared native body of family 5e27257c03e3aebd */
/* Draws a plain coloured rectangle on the screen between two corners. */
void AppendScreenRectPacket(int x0, int y0, int x1, int y1, unsigned long color, int isSubpixel)
{
    long long *q;

    *(int *)((char *)D_L03_001B3188_1 + 0) = 0x10000003;
    *(int *)((char *)D_L03_001B3188_1 + 4) = 0;
    *(int *)((char *)D_L03_001B3188_1 + 8) = 0;
    *(int *)((char *)D_L03_001B3188_1 + 12) = 0x50000003;
    q = (long long *)D_L03_001B3188_1;
    D_L03_001B3188_1 = (int *)((char *)q + 16);
    q[2] = 0x4400000000008001LL;
    q[3] = 17424;
    q[4] = 70;
    q[5] = color;
#define LO_D0 (*(int *)((char *)&D_001A7350 + 0))
#define HI_D4 (*(int *)((char *)&D_001A7354 + 0))

    if (isSubpixel != 0) {
        q[6] = (x0 + LO_D0 - 8)
             | ((long long)(y0 + HI_D4 - 8) << 16)
             | 0xFFFFF000000000LL;
        q[7] = (x1 + LO_D0 - 8)
             | ((long long)(y1 + HI_D4 - 8) << 16)
             | 0xFFFFF000000000LL;
    } else {
        q[6] = ((x0 << 4) + LO_D0 - 16)
             | ((long long)((y0 << 4) + HI_D4 - 16) << 16)
             | 0xFFFFF000000000LL;
        q[7] = ((x1 << 4) + LO_D0 - 16)
             | ((long long)((y1 << 4) + HI_D4 - 16) << 16)
             | 0xFFFFF000000000LL;
    }
    D_L03_001B3188_1 = (int *)((char *)D_L03_001B3188_1 + 48);
}

/* shared native body of family 9b94f3cd1f5fac83 */
/* Draws a plain coloured rectangle on the screen between two corners, at a chosen depth. */
void gfx_draw_screen_rect_with_depth(int x0, int y0, int x1, int y1, long long color, int depth, int isSubpixel)
{
    int *packet;

    *(int *)D_L02_001B3D08 = 0x10000003;
    *(int *)((char *)D_L02_001B3D08 + 4) = 0;
    *(int *)((char *)D_L02_001B3D08 + 8) = 0;
    *(int *)((char *)D_L02_001B3D08 + 12) = 0x50000003;
    packet = D_L02_001B3D08;
    D_L02_001B3D08 = packet + 4;
    *(long long *)(packet + 4) = 0x4400000000008001LL;
    *(long long *)(packet + 6) = 17424;
    *(long long *)(packet + 8) = 70;
    *(long long *)(packet + 10) = color;
    if (isSubpixel) {
        *(long long *)(packet + 12) = (x0 + g_screen_offset_x - 8)
                               | ((long long)(y0 + g_screen_offset_y - 8) << 16)
                               | ((long long)depth << 32);
        *(long long *)(packet + 14) = (x1 + g_screen_offset_x - 8)
                               | ((long long)(y1 + g_screen_offset_y - 8) << 16)
                               | ((long long)depth << 32);
    } else {
        *(long long *)(packet + 12) = ((x0 << 4) + g_screen_offset_x - 16)
                               | ((long long)((y0 << 4) + g_screen_offset_y - 16) << 16)
                               | ((long long)depth << 32);
        *(long long *)(packet + 14) = ((x1 << 4) + g_screen_offset_x - 16)
                               | ((long long)((y1 << 4) + g_screen_offset_y - 16) << 16)
                               | ((long long)depth << 32);
    }
    D_L02_001B3D08 = (int *)((char *)D_L02_001B3D08 + 48);
}



/* func_00290010 is in the -G8 sibling. */

/* func_002900B8 is defined in 002900B8-bars-g8.c. */



