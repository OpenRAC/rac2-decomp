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

extern int D_001B1600 __attribute__((sda));
extern Entry_001B9740 D_001B9740[];
extern short func_00282A18(int);

void func_00291DE0(int *p, int count) {
    for (D_001B1600 = 0; D_001B1600 < count; D_001B1600++) {
        int w0 = *p++;
        int w1 = *p++;
        int w2 = *p++;
        int w3 = *p++;
        D_001B9740[D_001B1600].a = w0 >> 4;
        D_001B9740[D_001B1600].b = w1 >> 4;
        D_001B9740[D_001B1600].c = log2dim(w2);
        D_001B9740[D_001B1600].d = log2dim(w3);
        D_001B9740[D_001B1600].head.clear = 0;
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
extern SkyDef *D_001B20C0 __attribute__((section(".sdata")));

/* Relocates the sky definition s just loaded (its pointers are offsets from s)
   and makes it the current one: the page table and the +0x14/+0x18/+0x1C blocks
   (+0x1C only when present), then each GIF page, whose four words are rewritten
   in place as two 1/16 values, two func_00282A18 results and a cleared tag, then
   each shell and the items in it. This unit has no strength reduction, so the
   item pointer retail walks is written out, set up behind the loop's guard. */
void func_00291EC0(SkyDef *s)
{
    int i;

    D_001B20C0 = s;
    s->unk04 = 1;
    s->pages = (SkyPage *)((char *)s->pages + (int)s);
    s->unk14 = s->unk14 + (int)s;
    s->unk18 = s->unk18 + (int)s;
    if (s->unk1C != 0) {
        s->unk1C = s->unk1C + (int)s;
    }
    {
        int *src = (int *)D_001B20C0->pages;

        for (i = 0; i < D_001B20C0->npages; i++) {
            int a = *src++;
            int b = *src++;
            int c = *src++;
            int d = *src++;

            D_001B20C0->pages[i].unk0A = a >> 4;
            D_001B20C0->pages[i].unk08 = b >> 4;
            D_001B20C0->pages[i].unk0C = log2dim(c);
            D_001B20C0->pages[i].unk0E = log2dim(d);
            D_001B20C0->pages[i].tag = 0;
        }
    }
    {
        int j;

        for (j = 0; j < D_001B20C0->count; j++) {
            SkyShell *sh;
            int k;

            D_001B20C0->shells[j] = (SkyShell *)((char *)D_001B20C0->shells[j] + (int)s);
            sh = D_001B20C0->shells[j];
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
