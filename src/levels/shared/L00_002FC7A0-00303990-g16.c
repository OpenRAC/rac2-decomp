/* Level loader: unpacks the level archive, uploads textures, builds the GS template words and
 * the class/texture tables, and returns the next free heap pointer. The LD store goes before the
 * fx/fy loads so combine keeps the first GS word's low half a DI register (retail's or tie). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef union { unsigned char b[0x400]; short h[0x200]; unsigned short uh[0x200]; int i[0x100];
                char *p[0x100]; unsigned long long d[0x80]; TI128 q[0x40]; } Blk;
typedef struct { int i[0x40]; } Hdr;
typedef struct {
    unsigned char pad0[4];
    unsigned char b4;
    unsigned char pad5[0xDB];
} ClassEntry;
typedef struct {
    unsigned char pad0[0x1A];
    short h1A;
    int i1C;
} Slot32;
typedef struct { char *data; int count; int pad8[2]; } Frame;
typedef struct {
    Frame *frames;
    unsigned char pad4[2];
    unsigned char b6;
    unsigned char b7;
    unsigned char pad8[4];
    unsigned char bC;
    unsigned char bD;
    unsigned char padE[0x28 - 0xE];
    Slot32 *slots;
    unsigned char pad2C[0x48 - 0x2C];
    int f48[1];
} Bank;

extern int D_L00_001BF140[];
extern int D_L00_001C9340[];
typedef struct { int stage, busy; int *archive0; int archive1; } ArchiveLoad;
extern ArchiveLoad D_001A7280 MACRO_ADDR;
typedef struct { int offset; unsigned short kind; unsigned short pad6; int pad8[2]; } TexRef;
typedef struct { short off; short count; } Span;
extern int D_001A79F0;
extern int D_001A72F4;
extern int D_001A7304;
extern unsigned char D_0019B2E8[];
extern unsigned char D_L00_001B1CE0[] MACRO_ADDR;
extern unsigned long long D_L00_001B1CF0[3];
extern unsigned long long D_L00_001B1D08[3];
extern int D_L00_001B24D8;
extern int D_L00_001B1E8C;
extern int D_L00_001B2550;
extern int D_L00_001B2410;
extern int D_L00_00225900[];
extern int D_L00_001DC980[];
extern int D_L00_0022D200[];
extern int D_L00_0021FBA0[];
extern Blk D_00152CD0;
extern Blk D_00152C00;
extern int D_L00_001B1A40;
extern int D_L00_001B2420;
extern int D_L00_001B1A44;
extern int D_L00_001B1A48;
extern unsigned long long D_L00_001C91C0[3];
extern int D_L00_001A9520[4] __attribute__((sda));
extern int D_L00_001B1E80;
extern int D_L00_001DD180[];
extern short D_L00_001DA680[];
extern Bank *D_L00_001D9F00[];
extern unsigned char D_L00_001DA860[];
extern short D_001A7A18;
extern int D_001A7290;
extern int D_001A72C0;
extern int D_001A72C4;
extern unsigned char D_00139568[];
extern ClassEntry D_L00_00262570[];
extern int D_L00_00226700[];
extern int D_L00_0021EA20[];
extern int D_L00_001B1944;
extern TI128 D_L00_001B1D20 MACRO_ADDR, D_L00_001B1D30 MACRO_ADDR, D_L00_001B1D40 MACRO_ADDR, D_L00_001B1D50 MACRO_ADDR;
extern int D_L00_001B1D60;
extern int D_L00_001B24D4;
extern Slot32 *D_L00_001B19EC;
extern int D_L00_001B19E8;
extern char D_L00_001A95B8[];
extern char D_L00_001A95D8[];
extern short D_00152CE4[];
typedef struct { unsigned char pad0[0xA]; unsigned char enabled; } Global001A7A00;
extern Global001A7A00 D_001A7A00 MACRO_ADDR;
typedef struct { int pad[2]; int f8; } SceneTrigger;
extern SceneTrigger D_L00_001B1AD0 MACRO_ADDR;
extern int D_L00_001B1E9C __attribute__((sda));
extern int D_L00_001B1EA0[] MACRO_ADDR;
extern int D_L00_001B19C8;

extern void func_00292888(void);
extern void func_L00_0036ADB0(void);
extern void func_00282B50(void *, void *, int);
extern void func_00282AB0(void *, void *, int);
extern void func_00293000(void *, int, int, void *);
extern void func_0011AEA0(int);
extern int func_0029D4D0(void *, char *);
extern int func_00282A18(int);
extern void func_L00_00300090(char *, void *);
extern void func_00291EC0(char *);
extern void func_L00_00300378(char *);
extern void func_00293890(char *, void *, void *, int);
extern void func_L00_00300438(void *, int, void *);
extern void func_00292328(int);
extern void func_002934B8(Bank *, int);
extern void func_L00_002FE268(int);
extern void func_00293260(Bank *, int);
extern void func_L00_002FF6A8(char *, void *, void *, int);
extern void ref_L00_00303990_00();
extern void func_L00_002FFAB8(char *, void *, void *, void *, int);
extern void func_00291DE0(void *, int);
extern void func_L00_002FD480(char *);
extern void func_00291CA8(void *, char *, void *, int);
extern void func_0026FEB8(const char *, ...);
extern int func_L00_00300618(int);
extern void func_L00_003032F0(void);
extern void func_L00_00303418(int);
extern void func_L00_00358B30(void);
extern void func_L00_003588A8(void);
extern void func_L00_002E3BA0(int);
extern void func_L00_0032CF60(void);

int func_L00_00303990(int load, int resume)
{
    Hdr *h = (Hdr *)((Blk *)&D_L00_001BF140)->p[0xC / 4];
    int *f = D_001A7280.archive0;
    char *base;
    char *end;
    int used;
    int i;
    int c1, c2, c3, c4;
    int fx;
    int fy;
    char *e;
    TexRef *t1, *tex, *t3, *t4;
    int slot8;
    int *list;
    int j;
    char *tab;
    Span *span;
    unsigned short *us;
    char *q2, *q, *p;
    int sq, a3, ci, k;

    if (load)
        func_00292888();
    base = ((Blk *)&D_L00_001BF140)->p[0x18 / 4];
    if (load) {
        func_L00_0036ADB0();
        ((Blk *)&D_L00_001C9340)->i[0] = 0;
        func_00282B50(h, (char *)(f[2] + (int)f), f[3]);
        func_00282AB0(D_L00_001B1CE0, D_0019B2E8 + D_001A79F0 * 16, 16);
        func_00293000((char *)(f[4] + (int)f), h->i[0], h->i[0x84 / 4], (char *)h + h->i[1]);
        func_0011AEA0(0);
        used = func_0029D4D0((char *)(f[0x12] + (int)f), base);
        ((Blk *)&D_L00_001BF140)->p[0x2C / 4] = base + h->i[0x60 / 4];
        fx = D_001A72F4;
        fy = D_001A7304;
        D_L00_001B1CF0[0] = (int)((fy + h->i[0x90 / 4] * 4) >> 8) | 0x1DB08000 | ((long long)0xB800 << 19) |
            ((long long)((fx + h->i[0x94 / 4]) >> 8) << 37) | 0x8000000000000000LL;
        D_L00_001B1CF0[1] = 0xFFA0000000E0ULL;
        D_L00_001B1CF0[2] = 0x40000400004000ULL;
        D_L00_001B1D08[0] = (int)((fy + h->i[0x98 / 4] * 4) >> 8) | 0x19B04000 | ((long long)0xB000 << 19) |
            ((long long)((fx + h->i[0x9C / 4]) >> 8) << 37) | 0x8000000000000000LL;
        D_L00_001B1D08[1] = 0xFFA0000000E0ULL;
        D_L00_001B1D08[2] = 0x40000400004000ULL;

        t1 = (TexRef *)((char *)h + h->i[0x34 / 4]);
        D_L00_001B24D8 = h->i[0x30 / 4];
        for (c1 = 0; c1 < D_L00_001B24D8; c1++)
            D_L00_00225900[c1] = ((Blk *)&D_L00_001BF140)->i[0x2C / 4] + t1[c1].offset + (func_00282A18(t1[c1].kind) << 28);
        tex = (TexRef *)((char *)h + h->i[0x3C / 4]);
        D_L00_001B1E8C = h->i[0x38 / 4];
        for (c2 = 0; c2 < D_L00_001B1E8C; c2++) {
            int value = ((Blk *)&D_L00_001BF140)->i[0x2C / 4] + tex[c2].offset + (func_00282A18(tex[c2].kind) << 28);
            D_L00_001DC980[c2] = value;
        }
        qcopy(&D_00152CD0, &tex[h->i[0x80 / 4]]);
        D_00152CD0.uh[0x10 / 2] = ((unsigned short *)h)[0x80 / 2];
        t3 = (TexRef *)((char *)h + h->i[0x44 / 4]);
        D_L00_001B2550 = h->i[0x40 / 4];
        for (c3 = 0; c3 < D_L00_001B2550; c3++) {
            int value = ((Blk *)&D_L00_001BF140)->i[0x2C / 4] + t3[c3].offset + (func_00282A18(t3[c3].kind) << 28);
            D_L00_0022D200[c3] = value;
        }
        t4 = (TexRef *)((char *)h + h->i[0x4C / 4]);
        D_L00_001B2410 = h->i[0x48 / 4];
        for (c4 = 0; c4 < D_L00_001B2410; c4++) {
            int value = ((Blk *)&D_L00_001BF140)->i[0x2C / 4] + t4[c4].offset + (func_00282A18(t4[c4].kind) << 28);
            D_L00_0021FBA0[c4] = value;
        }
        ((Blk *)&D_L00_001BF140)->p[0x1C / 4] = base + h->i[0x8 / 4];
        func_L00_00300090(((Blk *)&D_L00_001BF140)->p[0x1C / 4], (char *)h + h->i[0x34 / 4]);
        ((Blk *)&D_L00_001C9340)->p[0x8 / 4] = ((Blk *)&D_L00_001BF140)->p[0x1C / 4];
        if (h->i[0xC / 4] != 0) {
            char *p = base + h->i[0xC / 4];
            ((Blk *)&D_L00_001BF140)->p[0x20 / 4] = p;
            D_L00_001B1A40 = (int)p;
        } else {
            ((Blk *)&D_L00_001BF140)->p[0x20 / 4] = 0;
            D_L00_001B1A40 = 0;
        }
        if (h->i[0x10 / 4] != 0) {
            char *p = base + h->i[0x10 / 4];
            ((Blk *)&D_L00_001BF140)->p[0x24 / 4] = p;
            func_00291EC0(p);
        } else {
            D_L00_001B2420 = 0;
            ((Blk *)&D_L00_001BF140)->p[0x24 / 4] = 0;
        }
        {
            char *p = base + h->i[0x14 / 4];
            ((Blk *)&D_L00_001BF140)->p[0x28 / 4] = p;
            func_L00_00300378(p);
        }
        ((Blk *)&D_L00_001C9340)->p[0x4 / 4] = ((Blk *)&D_L00_001BF140)->p[0x28 / 4];
        for (i = 0, q2 = (char *)h + h->i[0x1C / 4]; i < h->i[0x18 / 4]; i++, q2 += 0x20) {
            char *p = *(int *)q2 != 0 ? base + *(int *)q2 : 0;
            if (*(int *)(q2 + 8) != 0) {
                D_L00_001C91C0[0] = D_00152C00.d[0x38 / 8];
                D_L00_001C91C0[1] = 0xFFA0000000E0ULL;
                D_L00_001C91C0[2] = 0x40000400004000ULL;
                func_00293890(p, 0, D_L00_001A9520, *(int *)(q2 + 4));
                D_L00_001DD180[D_L00_001B1E80 - 1] = 0xFFFC0000;
            } else {
                func_00293890(p, (char *)h + h->i[0x3C / 4], q2 + 0x10, *(int *)(q2 + 4));
            }
        }
        ((Blk *)&D_L00_001BF140)->p[0x38 / 4] = (char *)D_L00_001D9F00[0];
        func_L00_00300438((char *)h + h->i[0x1C / 4], h->i[0x18 / 4], (char *)h + h->i[0x24 / 4]);
        {
            int count = D_L00_001B1E80;
            D_00152C00.i[0x1C / 4] = count++;
            D_L00_001DD180[D_00152C00.i[0x1C / 4]] = 0xFFFC0000;
            D_L00_001DA680[D_00152C00.i[0x1C / 4]] = 0xD54;
            D_L00_001D9F00[D_00152C00.i[0x1C / 4]] = (Bank *)((Blk *)&D_L00_001BF140)->p[0x70 / 4];
            D_L00_001DA860[0xD54] = D_00152C00.i[0x1C / 4];
            D_00152CD0.h[0x12 / 2] = count;
            D_L00_001B1E80 = count + 1;
        }
        if (D_001A7290 != D_001A7A18) {
            func_00292328(D_001A7A18);
            D_001A7290 = D_001A7A18;
        }
        func_002934B8(D_L00_001D9F00[0], ((Blk *)&D_L00_001BF140)->i[0x78 / 4]);
        D_L00_001DD180[0] = 0xFFFC0000;
        slot8 = D_L00_001DA860[0xD54];
        if (slot8 != 0xFF) {
            Bank *bank = D_L00_001D9F00[slot8];
            if (bank->b6 != 0) {
                Frame *fr = &bank->frames[bank->b7];
                char *pkt = fr->data + fr->count * 16;
                *(unsigned long long *)(pkt - 0x20) = D_L00_001B1CF0[0];
                *(unsigned long long *)(pkt - 0x10) = D_L00_001B1CF0[2];
            }
        }
        {
            int want = (D_00139568[0xA] + D_L00_00262570)->b4;
            if (D_001A72C0 != want)
                func_L00_002FE268(want);
        }
        {
            int hero = D_L00_001DA860[0x47];
            D_001A72C4 = hero;
            func_002934B8(D_L00_001D9F00[hero], ((Blk *)&D_L00_001BF140)->i[0x74 / 4]);
        }
        D_L00_001DD180[D_001A72C4] = 0xFFFC0000;
        us = (unsigned short *)((char *)h + h->i[0xAC / 4]);
        while ((short)*us >= 0) {
            int slot = D_L00_001DA860[(short)*us];
            if (slot != 0xFF)
                D_L00_001DD180[slot] = 0xFFF00000;
            us++;
        }
        for (sq = 0, p = (char *)h + h->i[0x78 / 4]; sq < D_L00_001D9F00[0]->bC; sq++, p += 4) {
            if (*(int *)p != 0) {
                D_L00_001D9F00[0]->f48[sq] = (int)(base + *(int *)p);
                func_00293260(D_L00_001D9F00[0], sq);
            }
        }
        ((Blk *)&D_L00_001BF140)->i[0x44 / 4] = D_L00_001D9F00[0]->f48[0];
        for (i = 0, q2 = (char *)h + h->i[0x24 / 4]; i < h->i[0x20 / 4]; i++, q2 += 0x20)
            func_L00_002FF6A8(base + *(int *)q2, (char *)h + h->i[0x44 / 4], q2 + 0x10, *(int *)(q2 + 4));
        if (D_L00_00226700[0] != 0)
            ((Blk *)&D_L00_001BF140)->i[0x3C / 4] = D_L00_00226700[0];
        ref_L00_00303990_00((char *)h + h->i[0x24 / 4], h->i[0x20 / 4]);
        for (i = 0, q2 = (char *)h + h->i[0x2C / 4]; i < h->i[0x28 / 4]; i++, q2 += 0x30)
            func_L00_002FFAB8(base + *(int *)q2, (char *)h + h->i[0x4C / 4], q2 + 0x10, q2 + 0x20, *(int *)(q2 + 4));
        if (D_L00_0021EA20[0] != 0)
            ((Blk *)&D_L00_001BF140)->i[0x40 / 4] = D_L00_0021EA20[0];
        {
            char *p = base + h->i[0x68 / 4];
            ((Blk *)&D_L00_001BF140)->p[0x34 / 4] = p;
            D_L00_001B1944 = (int)p;
        }
        func_00291DE0((char *)h + h->i[0x5C / 4], h->i[0x58 / 4]);
        if (h->i[0xA4 / 4] != 0) {
            func_L00_002FD480(base + h->i[0xA4 / 4]);
        } else {
            qzero(&D_L00_001B1D20);
            qzero(&D_L00_001B1D30);
            qzero(&D_L00_001B1D40);
            qzero(&D_L00_001B1D50);
            D_L00_001B1D60 = 0;
        }
        if (h->i[0xA8 / 4] != 0)
            D_L00_001B1A44 = (int)(base + h->i[0xA8 / 4]);
        else
            D_L00_001B1A44 = 0;
        if (h->i[0xB0 / 4] != 0)
            D_L00_001B1A48 = (int)(base + h->i[0xB0 / 4]);
        else
            D_L00_001B1A48 = 0;
        {
            char *x1 = base + h->i[0x64 / 4];
            char *x2;
            ((Blk *)&D_L00_001BF140)->p[0x30 / 4] = x1;
            x2 = (char *)h + h->i[0x54 / 4];
            func_00291CA8((char *)h + h->i[0x6C / 4], x1, x2, h->i[0x50 / 4]);
        }
        base = (char *)((unsigned int)(base + used + 0x3F) & ~0x3F);
        if (D_L00_001B24D4 != ((Blk *)&D_L00_001C9340)->i[0x18 / 4]) {
            char *dst;
            int size;
            do {
                ((Blk *)&D_L00_001C9340)->p[0x10 / 4] = base;
                size = h->i[0x30 / 4];
            } while (0);
            dst = base;
            size *= 16;
            base += size;
            func_00282B50(dst, (char *)h + h->i[0x34 / 4], size);
            ((Blk *)&D_L00_001C9340)->p[0x14 / 4] = base;
            base = (char *)(((unsigned int)(base + ((Blk *)&D_L00_001C9340)->i[0x18 / 4] * 2) + 0x7F) & ~0x3F);
        }
        tab = (char *)h + h->i[0x70 / 4];
        span = (Span *)tab;
        {
            int nslots = span->count;
            D_L00_001B19EC = (Slot32 *)base;
            D_L00_001B19E8 = nslots;
            func_00282AB0(base, tab + span->off, nslots * 32);
            span++;
            base += nslots * 32;
        }
        e = tab + span->off;
        for (a3 = 0; a3 < D_L00_001B19E8; a3++) {
            if (D_L00_001B19EC[a3].h1A >= span->count) {
                func_0026FEB8(D_L00_001A95B8);
                D_L00_001B19EC[a3].h1A = -1;
            } else {
                D_L00_001B19EC[a3].h1A = *(unsigned short *)(e + D_L00_001B19EC[a3].h1A * 4);
            }
            D_L00_001B19EC[a3].i1C = 0;
        }
        end = base + 0x3F;
        span++;
        for (ci = 0, q = (char *)h + h->i[0x1C / 4]; ci < h->i[0x18 / 4]; ci++, span++, q += 0x20) {
            int cls = D_L00_001DA860[*(int *)(q + 4)];
            if (D_L00_001DA680[cls] == *(int *)(q + 4)) {
                if ((span->count != 0 || D_L00_001D9F00[cls]->bD != 0) && span->count - 1 != D_L00_001D9F00[cls]->bD)
                    func_0026FEB8(D_L00_001A95D8, D_L00_001DA680[cls], span->count - 1, D_L00_001D9F00[cls]->bD);
                {
                    int first;
                    e = tab + span->off;
                    first = *(int *)e;
                    e += 4;
                    for (k = 0; k < D_L00_001D9F00[cls]->bD; k++, e += 4) {
                        D_L00_001D9F00[cls]->slots[k].h1A = *(unsigned short *)e;
                        D_L00_001D9F00[cls]->slots[k].i1C = first + 1;
                    }
                }
            }
        }
        base = (char *)((unsigned int)end & ~0x3F);
        ((Blk *)&D_L00_001BF140)->p[0x48 / 4] = base;
    }
    ((Blk *)&D_L00_001BF140)->i[0x68 / 4] = func_L00_00300618(load);
    if (load)
        D_00152CE4[0] = -1;
    if (((Blk *)&D_L00_001C9340)->i[0xC / 4] != 0) {
        if (load)
            func_L00_003032F0();
        func_L00_00303418(((Blk *)&D_L00_001C9340)->i[0]);
    }
    if (resume)
        func_L00_00358B30();
    else
        func_L00_003588A8();
    D_L00_001B1AD0.f8 = 0;
    if (D_001A7A00.enabled != 0) {
        int m;
        for (m = D_L00_001B1E9C; m != D_L00_001B1EA0[0]; m += 0x100)
            func_L00_002E3BA0(m);
    }
    func_L00_0032CF60();
    D_L00_001B19C8++;
    return 0;
}
