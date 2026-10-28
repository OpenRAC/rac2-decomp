/* functional: high. Same instructions as retail; only the callee-saved registers $s3/$s4 are swapped, which does not change behaviour. */
#include "include_asm.h"

typedef struct Group_00291EC0 {
    int count;
    unsigned char pad_04[0x1C];
    int *rel;
} Group_00291EC0;

typedef struct Entry_00291EC0 {
    unsigned char pad_00[8];
    short s8;
    short sA;
    short sC;
    short sE;
} Entry_00291EC0;

typedef struct Header_00291EC0 {
    unsigned char pad_00[4];
    short s4;
    short count6;
    unsigned char pad_08[4];
    short countC;
    short padE;
    Entry_00291EC0 *entries;
    int w14;
    int w18;
    int w1C;
    int tab[1];
} Header_00291EC0;

extern Header_00291EC0 *D_001B20C0[] __attribute__((sda));

extern short func_00282A18(int);

void func_00291EC0(Header_00291EC0 *h)
{
    int *src;
    int i;
    int j;
    int a;
    int b;
    int c;
    int d;
    int e0;
    int e1;
    int e2;
    int e3;
    int *g;
    Header_00291EC0 *cur;

    e0 = (int)h->entries;
    e1 = h->w14;
    e2 = h->w18;
    e3 = h->w1C;
    D_001B20C0[0] = h;
    h->s4 = 1;
    h->entries = (Entry_00291EC0 *)(e0 + (int)h);
    h->w14 = e1 + (int)h;
    h->w18 = e2 + (int)h;
    if (e3 != 0)
        h->w1C = e3 + (int)h;
    cur = D_001B20C0[0];
    src = (int *)cur->entries;
    for (i = 0; i < cur->countC; i++) {
        a = src[0];
        src++;
        b = src[0];
        src++;
        c = src[0];
        src++;
        d = src[0];
        src++;
        cur->entries[i].sA = a >> 4;
        cur->entries[i].s8 = b >> 4;
        D_001B20C0[0]->entries[i].sC = func_00282A18(c);
        D_001B20C0[0]->entries[i].sE = func_00282A18(d);
        cur = D_001B20C0[0];
        *(long long *)&cur->entries[i] = 0;
    }
    cur = D_001B20C0[0];
    for (i = 0; i < cur->count6; i++) {
        g = (int *)((int *)((char *)cur + 0x20))[i];
        g = (int *)((int)g + (int)h);
        ((int *)((char *)cur + 0x20))[i] = (int)g;
        for (j = 0; j < *g; j++)
            g[8 + j * 8] += (int)h;
    }
}
