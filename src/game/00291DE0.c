#include "names.h"
/* Reads `count` records of four words (two scaled positions and two ids) into the shared
   table of 16-byte entries, resetting the table cursor first. */
typedef struct {
    long long clear;
} Pad8;

typedef struct {
    Pad8 head;
    short b;
    short a;
    short c;
    short d;
} Entry_001B9740;

extern int g_gfx_entry_count __attribute__((sda));
extern Entry_001B9740 g_texture_upload_params[];
extern short log2dim(int);

void func_00291DE0(int *p, int count) {
    for (g_gfx_entry_count = 0; g_gfx_entry_count < count; g_gfx_entry_count++) {
        int w0 = *p++;
        int w1 = *p++;
        int w2 = *p++;
        int w3 = *p++;
        g_texture_upload_params[g_gfx_entry_count].a = w0 >> 4;
        g_texture_upload_params[g_gfx_entry_count].b = w1 >> 4;
        g_texture_upload_params[g_gfx_entry_count].c = log2dim(w2);
        g_texture_upload_params[g_gfx_entry_count].d = log2dim(w3);
        g_texture_upload_params[g_gfx_entry_count].head.clear = 0;
    }
}

/* The sky definition (RAC1 loaders.c: relocate_sky_definition): its GIF pages
   and shells, reached through the current definition D_001B20C0. */
typedef struct {
    long tag;
    short unk08;
    short unk0A;
    short unk0C;
    short unk0E;
} SkyPage;
/* A shell is a row of 0x20-byte records: a header holding the count, then one
   record per item whose first word is an offset to relocate. */
typedef struct {
    char *ptr;
    char pad04[0x1C];
} SkyShellItem;
typedef struct {
    int count;
    char pad04[0x1C];
} SkyShell;
typedef struct {
    int unk00;
    short unk04;
    short count;      /* 0x06: shells */
    int unk08;
    short npages;     /* 0x0C */
    short unk0E;
    SkyPage *pages;   /* 0x10 */
    char *unk14;
    char *unk18;
    char *unk1C;
    SkyShell *shells[1]; /* 0x20 */
} SkyDef;
extern SkyDef *g_sky_shell_definition __attribute__((section(".sdata")));

/* Relocates the sky definition s just loaded (its pointers are offsets from s)
   and makes it the current one: the page table and the +0x14/+0x18/+0x1C blocks
   (+0x1C only when present), then each GIF page, whose four words are rewritten
   in place as two 1/16 values, two func_00282A18 results and a cleared tag, then
   each shell and the items in it. This unit has no strength reduction, so the
   item pointer retail walks is written out, set up behind the loop's guard. */
void RelocateSkyDefinition(SkyDef *s)
{
    int i;

    g_sky_shell_definition = s;
    s->unk04 = 1;
    s->pages = (SkyPage *)((char *)s->pages + (int)s);
    s->unk14 = s->unk14 + (int)s;
    s->unk18 = s->unk18 + (int)s;
    if (s->unk1C != 0) {
        s->unk1C = s->unk1C + (int)s;
    }
    {
        int *src = (int *)g_sky_shell_definition->pages;

        for (i = 0; i < g_sky_shell_definition->npages; i++) {
            int a = *src++;
            int b = *src++;
            int c = *src++;
            int d = *src++;

            g_sky_shell_definition->pages[i].unk0A = a >> 4;
            g_sky_shell_definition->pages[i].unk08 = b >> 4;
            g_sky_shell_definition->pages[i].unk0C = log2dim(c);
            g_sky_shell_definition->pages[i].unk0E = log2dim(d);
            g_sky_shell_definition->pages[i].tag = 0;
        }
    }
    {
        int j;

        for (j = 0; j < g_sky_shell_definition->count; j++) {
            SkyShell *sh;
            int k;

            g_sky_shell_definition->shells[j] = (SkyShell *)((char *)g_sky_shell_definition->shells[j] + (int)s);
            sh = g_sky_shell_definition->shells[j];
            k = 0;
            if (k < sh->count) {
                SkyShellItem *it = (SkyShellItem *)sh;

                do {
                    it[1].ptr = it[1].ptr + (int)s;
                    k++;
                    it++;
                } while (k < sh->count);
            }
        }
    }
}
