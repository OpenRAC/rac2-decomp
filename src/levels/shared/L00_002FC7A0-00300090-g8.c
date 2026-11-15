/* Adapted from RAC1 src/game/loaders.c, initialize_tfrag_render_data. */
#include "common.h"

extern int D_L00_001B24D4 __attribute__((section(".sdata")));
extern float D_L00_001B24DC __attribute__((section(".sdata")));
extern float D_L00_001B24E0[];
extern int D_L00_001C9358 __attribute__((nosda));
extern unsigned char *D_L00_001B24D0 __attribute__((section(".sdata")));
extern int D_001A72F4 __attribute__((section(".sdata")));
extern void SetTfragDists(void);
extern int log2dim(int);
typedef struct { int x0; int x4; float scale; int extra; } TfragRenderHeader;
typedef struct {
    char pad0[0x10];
    int glyphs;            /* 0x10 */
    char pad14[8];
    unsigned short off1C;  /* 0x1C */
    char pad1E[0xA];
    unsigned char count;   /* 0x28 */
    char pad29[0x17];
} TfragRenderRecord;
typedef struct {
    int x0;
    char pad4[0xC];
    int x10;
    int x14;
    char pad18[8];
    int x20;
    int x24;
    char pad28[0x28];
} TfragMaterialPacket;
typedef struct { long lo; long hi; } TfragPacketQword;
typedef struct { short x0; short x2; unsigned short x4; short x6; short x8; short xA; short xC; short xE; } TfragTexture;
/* Sets up the level's tfrag (terrain) render data and writes the GS texture setup words for each material. */
void initialize_tfrag_render_data(TfragRenderHeader *hdr, char *tbl) {
    char *base;
    float scale;
    int i;
    int j;
    int n;
    int k;

    D_L00_001B24D4 = *(int *)((char *)hdr + 4);
    scale = *(float *)((char *)hdr + 8);
    D_L00_001B24DC = scale;
    D_L00_001C9358 = *(int *)((char *)hdr + 12);
    D_L00_001B24E0[0] = scale * 6.0f;
    D_L00_001B24E0[1] = scale * 4.0f;
    D_L00_001B24E0[2] = scale + scale;
    SetTfragDists();
    base = (char *)hdr + *(int *)hdr;
    D_L00_001B24D0 = base;
    n = D_L00_001B24D4;
    for (k = 0; k < n; k++) {
        *(int *)(base + k * 0x40 + 0x10) = (int)base + *(int *)(base + k * 0x40 + 0x10);
    }
    for (i = 0; i < D_L00_001B24D4; i++) {
        for (j = 0; j < ((TfragRenderRecord *)D_L00_001B24D0)[i].count; j++) {
            TfragRenderRecord *run = (TfragRenderRecord *)((i << 6) + (int)D_L00_001B24D0);
            unsigned long *o = (unsigned long *)((char *)run->glyphs + run->off1C + j * 0x50);
            int k0 = ((TfragMaterialPacket *)o)->x0;
            int k10 = ((TfragMaterialPacket *)o)->x10;
            int k14 = ((TfragMaterialPacket *)o)->x14;
            int k20 = ((TfragMaterialPacket *)o)->x20;
            int k24 = ((TfragMaterialPacket *)o)->x24;
            TfragTexture *m = (TfragTexture *)(tbl + k0 * 16);
            int t = m->x4 << 16;
            int a17 = t >> 22;
            int a19 = t >> 23;
            long u;
            int v;
            int gs;
            unsigned long tex0, tex1, clamp, mip1;

            if (!(0 < a17)) {
                a17 = 1;
            }
            if (!(0 < a19)) {
                a19 = 1;
            }
            u = log2dim(t >> 16);
            v = log2dim(m->x6);
            gs = D_001A72F4 >> 8;
            /* The s64/u64 casts keep every OR chain at three operands of one type, so
               fold's reduce_expression_tree_depth leaves the left-to-right GS word trees
               as written (the same idiom as func_L00_002FFAB8). */
            tex0 = (s64)((u64)((s64)a17 << 14 | (s64)0x13 << 20 | (s64)u << 26)
                         | (u64)v << 30 | (u64)1 << 34 | (u64)(m->xA + gs) << 37)
                   | (s64)4 << 61;
            t = m->x8 - 1;
            tex1 = (s64)((u64)t << 2 | (u64)1 << 5 | (u64)k14 << 6) | (s64)(unsigned int)k10 << 32;
            clamp = (u64)k20 | (u64)k24 << 2 | (u64)k0 << 24;
            mip1 = (s64)((u64)a19 << 14 | (u64)(m->xC + gs) << 20 | (u64)1 << 34
                         | (u64)(m->xE + gs) << 40)
                   | (s64)1 << 54;
            *o = tex0;
            o += 2;
            *o = tex1;
            o += 2;
            *o = clamp;
            o += 2;
            *o = mip1;
            ((TfragPacketQword *)o)[1].lo = 0;
        }
    }
}
