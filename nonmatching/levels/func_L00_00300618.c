/* Object and ABI review, 3 November 2026; retained, not linked.
 * Profile: -O2 -G8 -ffunction-sections.
 * Fresh US check: 11288/11348 bytes, 0/27 places.
 * Both vector transforms now pass the actual 64-byte instance matrix as
 * third argument. Retail explicitly establishes a2 before the tie transform.
 * Class +0x50 is a 16-byte centre/radius sphere; variable-count group entries
 * use genuine trailing storage. The remaining 60-byte gap involves absolute
 * store slots, shrub/moby spills and group loops. Do not omit real inputs
 * to recover the historical smaller result. No functional-port credit.
 * Earlier measurements follow.
 */
/* Level-data loader: relocates section tables, ties, shrubs and mobys into the
 * aligned level heap. Retained reconstruction, not functional-gated.
 * USA v1.01: 11,280/11,348 bytes, 0/27 placements, measured 2026-11-01.
 * Use a separate L00_00300618-g8.c unit with -O2 -G8 -ffunction-sections.
 * The previous retained source emitted 11,272 bytes. Its section-8 do-loop was
 * strength-reduced into extra address induction variables. The explicit goto
 * loop below preserves the four real cursor advances; its complete 24-word copy
 * sequence now equals retail in every USA placement, without a compiler patch.
 * This is only a local sequence, not a match of the 11 KB function.
 * Remaining: absolute macro-global stores enter delay slots, shrub/moby spill
 * allocation, and group-list induction variables. NOT_SDA hoists the address high
 * halves; global -fno-strength-reduce loses required reductions elsewhere. Keep
 * the actual grouped globals and sequential record reads when investigating these.
 */
#include "common.h"

typedef int TI128_00618 __attribute__((mode(TI)));
typedef union { TI128_00618 q; float f[4]; int i[4]; } Vec00618;

#define ALIGN64_00618(p) ((char *)(((int)(p) + 0x3F) & 0xFFFFFFC0u))
#define SECTION_00618(off) (hdr + *(int *)(hdr + (off)))
#define SAVE_CELL_00618(uid) D_001A54A8[(D_001A79F0 << 10) + ((uid) >> 1)]

typedef struct {
    char pad00[0xC];
    char *data;                   /* 0x0C: the level data image */
    int i10;
    int i14;
    int i18;
    char pad1C[0x2C];
    char *heap;                   /* 0x48 */
    char *mark4C;
    char *mark50;
    char *mark54;
    char *mark58;
    char *mark5C;
    char *mark60;
    char *mark64;
} LoadCtx00618;

typedef struct { char pad00[0x529C]; int i529C; char pad52A0[0x18]; int i52B8; int i52BC; } Boot00618;
typedef struct { char pad00[0x23C]; int i23C; int i240; int i244; } Cfg00618;
typedef struct { void *hero; char pad04[0x3C]; int i40; int i44; int i48; } Sel00618;
typedef struct { char pad00[0x1730]; int count; char *table; } Slots00618;
typedef struct { char pad00[0xC]; int count; int i10; unsigned short *bits; int i18; int i1C; } Tutorial00618;
typedef struct { char pad00[4]; char *p4; char *p8; int iC; int i10; int i14; } Coll00618;

typedef struct {
    Vec00618 bounds;              /* 0x00 */
    unsigned short h10;
    short h12;
    unsigned short h14;
    short h16;
    short h18;
    unsigned short h1A;
    unsigned char b1C;
    unsigned char b1D;            /* class index */
    unsigned char b1E;
    unsigned char b1F;
} Tie00618;                       /* 0x20 */

typedef struct { Vec00618 row[4]; } Matrix00618;   /* 0x40 */

typedef struct {
    char pad00[0x20];
    Tie00618 *first;              /* 0x20 */
    char pad24[0xC];
    char *table;                  /* 0x30 */
    char pad34[4];
    short h38;
    char pad3A[4];
    unsigned short h3E;
    float f40;
    char pad44[0xC];
    Vec00618 sphere;              /* 0x50: centreXYZ and radius */
} TieClass00618;

typedef struct {
    Vec00618 bounds;              /* 0x00 */
    float f10;
    char pad14[3];
    unsigned char b17;
    short h18;
    unsigned char b1A;            /* class index */
    unsigned char b1B;
    unsigned short h1C;
    unsigned short h1E;
} Shrub00618;                     /* 0x20 */

typedef struct {
    char pad00[0xC];
    float fC;
    char pad10[6];
    unsigned short h16;
    Shrub00618 *first;            /* 0x18 */
    float *p1C;
    float f20;
} ShrubClass00618;

typedef struct {
    char pad00[0x10];
    Vec00618 pos;                 /* 0x10 */
    unsigned char state;          /* 0x20 */
    unsigned char b21;
    char pad22[2];
    char *pClass;                 /* 0x24 */
    char pad28[4];
    float f2C;
    unsigned char b30;
    char pad31;
    unsigned short h32;
    unsigned short h34;
    unsigned short h36;
    int i38;
    char pad3C[0x27];
    unsigned char b63;
    int i64;
    int i68;
    char pad6C[0x12];
    unsigned char b7E;
    char pad7F[0x2B];
    short oClass;                 /* 0xAA */
    char padAC[4];
    unsigned char bB0;
    unsigned char bB1;
    short hB2;
    short hB4;
    short hB6;
    char padB8[0x38];
    float rot[4];                 /* 0xF0 */
} Moby00618;                      /* 0x100 */

typedef struct { char pad00[0x24]; float f24; char pad28[0x1C]; unsigned short h44; } MobyClass00618;

typedef struct {
    short h0, h2, h4, h6, h8;
    char pad0A[2];
    int iC, i10, i14, i18, i1C;
    char pad20[0x10];
} GroupEntry00618;                /* 0x30 */

typedef struct {
    int count;                    /* 0x00 */
    char *p4;
    char *p8;
    char *pC;
    char *p10;
    char *p14;
    char pad18[0x18];
    GroupEntry00618 entries[0];   /* 0x30 */
} Groups00618;

typedef struct { int p14; int i18; int p1C; int i20; } Reloc00618;
extern Reloc00618 D_L00_001A9014 MACRO_ADDR;
typedef struct { int pFC; int p00; } GroupTab00618;
extern GroupTab00618 D_L00_001B1AFC MACRO_ADDR;
typedef struct { char * p84; int i88; char * p8C; int i90; char * p94; int i98; char * p9C; int iA0; int iA4; char * pA8; } Tabs00618;
extern Tabs00618 D_L00_001B1F84 MACRO_ADDR;
typedef struct { char * pC0; int iC4; } Rails00618;
extern Rails00618 D_L00_001B16C0 MACRO_ADDR;
typedef struct { char * pB0; int iB4; int iB8; int iBC; } Parts00618;
extern Parts00618 D_L00_001B20B0 MACRO_ADDR;

extern LoadCtx00618 D_L00_001BF140;
extern Boot00618 D_0014B540;
extern char *D_001A728C MACRO_ADDR;
extern char D_00189E20[];
extern char D_L00_001B8C80[];
extern char D_L00_001D1740[];
extern int D_001A7B90 MACRO_ADDR;
extern float D_001A790C __attribute__((sda));
extern Coll00618 D_L00_001BF200;
extern char D_L00_001BF280[];
extern char D_L00_001B1A80[];
extern char D_L00_001DE860[];
extern char D_L00_001FA860[];
extern Cfg00618 D_L00_001BD2C0;
extern unsigned char D_L00_001B1980 MACRO_ADDR;
extern unsigned char D_L00_001B1981 MACRO_ADDR;
extern unsigned char D_L00_001B1982 MACRO_ADDR;
extern float D_L00_001B1984 MACRO_ADDR;
extern float D_L00_001B1988 MACRO_ADDR;
extern float D_L00_001B198C MACRO_ADDR;
extern float D_L00_001B1990 MACRO_ADDR;
extern int D_L00_001A8FF0 MACRO_ADDR;
extern float D_L00_001B1AE8 MACRO_ADDR;
extern float D_L00_001B1B10 MACRO_ADDR;
extern float D_L00_001B1B14 MACRO_ADDR;
extern float D_L00_001B1B18 MACRO_ADDR;
extern float D_L00_001B1B1C MACRO_ADDR;
extern Sel00618 D_00152C00;
extern Tutorial00618 D_L00_001C9340;
extern int D_L00_001A8F0C __attribute__((sda));
extern int D_L00_001B20C0 MACRO_ADDR;
extern float D_L00_001B2500 MACRO_ADDR;
extern float D_L00_001B2408 MACRO_ADDR;
extern int D_L00_001B1EB4 MACRO_ADDR;
extern int D_L00_001B255C __attribute__((sda));
extern char D_00100AE0[];
extern char D_L00_001C6F40[];
extern char D_L00_001C7040[];
extern char D_L00_001C6B40[];
extern char D_L00_002A0ED0[];
extern int D_L00_001B1CDC MACRO_ADDR;
extern char D_L00_001C5940[];
extern char D_L00_001C5B40[];
extern int D_L00_001B24D4 MACRO_ADDR;
extern char *D_L00_001B24D0 MACRO_ADDR;
extern char D_L00_00277848[];
extern unsigned char D_001A7BB4 MACRO_ADDR;
extern char *D_L00_001B1B80 MACRO_ADDR;
extern int D_L00_001B2520 MACRO_ADDR;
extern Tie00618 *D_L00_001B2514 MACRO_ADDR;
extern Tie00618 *D_L00_001B2518 MACRO_ADDR;
extern Matrix00618 *D_L00_001B251C MACRO_ADDR;
extern int D_L00_001B2524 MACRO_ADDR;
extern int D_L00_001B2540 MACRO_ADDR;
extern int D_L00_001B2544 MACRO_ADDR;
extern int D_L00_001B2548 __attribute__((sda));
extern int D_L00_001B2510 MACRO_ADDR;
extern TieClass00618 *D_L00_00226700[];
extern unsigned char D_L00_00226A00[];
extern Shrub00618 *D_L00_001B23F8 MACRO_ADDR;
extern int D_L00_001B23F4 MACRO_ADDR;
extern Matrix00618 *D_L00_001B2400 MACRO_ADDR;
extern unsigned char *D_L00_001B2404 MACRO_ADDR;
extern Shrub00618 *D_L00_001B23FC __attribute__((sda));
extern char D_L00_001ACE90[];
extern ShrubClass00618 *D_L00_0021EA20[];
extern unsigned char D_L00_0021EBA0[];
extern char *D_L00_001B1844 MACRO_ADDR;
extern int D_L00_001B1848 MACRO_ADDR;
extern Slots00618 D_00188660;
extern int D_L00_001C5480[][3];
extern int D_L00_001C5540[][3];
extern Moby00618 *D_L00_001B1E9C MACRO_ADDR;
extern Moby00618 *D_L00_001B18DC MACRO_ADDR;
extern Moby00618 *D_L00_001B1EA0 MACRO_ADDR;
extern Moby00618 *D_L00_001B1EA4 MACRO_ADDR;
extern char *D_L00_001B1EAC MACRO_ADDR;
extern short D_L00_001FB660[];
extern int D_001A79F0 MACRO_ADDR;
extern unsigned char D_001A52E8[];
extern unsigned char D_001A54A8[];
extern unsigned char D_L00_0021DDB0[];
extern unsigned char D_L00_001B1CE0[];
extern int D_L00_001FA920[];
extern int D_L00_001B1EB8 MACRO_ADDR;
extern char *D_L00_001FDA80[];
extern char *D_L00_001B1880 MACRO_ADDR;
extern char *D_L00_001B1CD8 MACRO_ADDR;
extern int D_L00_001B1CD4 MACRO_ADDR;
extern char *D_L00_001B1F40 MACRO_ADDR;
extern int D_L00_001B1F10 MACRO_ADDR;
extern char D_L00_001FE140[];
#define GROUPS_00618 ((Groups00618 *)D_L00_001B1AFC.p00)
extern int D_L00_001B1A40 MACRO_ADDR;
extern unsigned short *D_L00_001B19F0 MACRO_ADDR;
extern int D_L00_001B1A50 MACRO_ADDR;
extern short D_L00_001FDE78 NOT_SDA;
extern short D_L00_001FDEF8 NOT_SDA;
extern short D_L00_001B1FB0 MACRO_ADDR;
extern short D_L00_001B1FF0 MACRO_ADDR;
extern short D_L00_001B2030 __attribute__((sda));
extern int D_L00_00220DA0[];
extern int D_L00_001B19C8 MACRO_ADDR;
extern int D_L00_001B1AEC MACRO_ADDR;
extern int D_L00_001AA0F8 __attribute__((sda));
extern char D_L00_001A8A78[] __attribute__((sda));
extern char D_L00_001A8A48[] __attribute__((sda));
extern char *D_L00_001B18D0 MACRO_ADDR;
extern char *D_L00_001A8AA8 MACRO_ADDR;

extern int func_002B7C80(void *, int, int);
extern void func_0011AEA0(int);
extern void func_0029D4D0(void *, void *);
extern void func_00282A60(void *, int, int);
extern void func_0029FAE0(void);
extern void func_001163A0(int);
extern void func_L00_00322428(int);
extern void func_00282A88(void *, int);
extern void func_00279FF0(void);
extern void func_00284E18(int, int, int);
extern void func_002FC070(void *);
extern void func_0026FEB8(const char *, ...);
extern void func_00282AB0(void *, void *, int);
extern void func_002F0468(void *);
extern void func_00283098(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_L00_002EE050(float, float);
extern void func_00282D60(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282B50(void *, void *, int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern void func_002E2C38(void *);
extern void func_L00_0035F7E8(void *);
extern int func_L00_002E3B38(int);
extern void func_0029F0C8(void *, int);
extern float func_002A89A8(void *, int, float);
extern void func_002A0F48(void *);
extern void func_002A0468(void *, u64, u64, u64, u64);
extern void func_L00_00309140(void *, int);
extern Moby00618 *func_0029EFD0(int);
extern void func_0027B7E0(void);
extern void func_L00_002A4928(void);
extern void func_L00_002A4D18(void);
extern void func_L00_002D9E80(void);
extern void func_00272368(void);
extern void func_002B8518(void);
extern void func_L00_0037E418(void);
extern void func_L00_00367308(void);
extern void func_L00_0032A0E8(void);
extern void func_L00_0032A138(void);
extern void func_L00_0032A170(void);
extern void func_L00_003E8150(void);
extern void func_L00_002E9098(void);
extern void func_L00_00403BF8(void);
extern void func_00272198(float);

char *func_L00_00300618(int reload)
{
    char *hdr = D_L00_001BF140.data;
    char *heap = D_L00_001BF140.heap;
    float *startPos;
    char *p;

    if (!reload)
        func_002B7C80(heap, D_0014B540.i52B8 + D_0014B540.i529C, D_0014B540.i52BC);
    D_001A728C = heap;
    func_0011AEA0(0);
    func_0029D4D0(D_001A728C, hdr);
    func_0011AEA0(0);
    func_00282A60(D_00189E20, 0, 0x2540);
    func_00282A60(D_L00_001B8C80, 0, 0x410);
    func_00282A60(D_L00_001D1740, 0, 0x180);
    func_0029FAE0();
    func_001163A0(1234);
    if (D_001A7B90) {
        if (D_001A790C == 1.0f)
            func_L00_00322428(1);
    } else {
        if (D_001A790C != 1.0f)
            func_L00_00322428(0);
    }
    D_L00_001BF200.p4 = D_L00_001BF280;
    D_L00_001BF200.p8 = D_L00_001B1A80;
    D_L00_001BF200.i14 = 0;
    D_L00_001BF200.iC = 0;
    D_L00_001BF200.i10 = 0;
    func_00282A88(D_L00_001DE860, 0x1C000);
    func_00282A88(D_L00_001FA860, 0xC0);

    /* section 0: the level header */
    p = SECTION_00618(0);
    D_L00_001BD2C0.i23C = *(int *)p;
    p += 4;
    D_L00_001BD2C0.i240 = *(int *)p;
    p += 4;
    D_L00_001BD2C0.i244 = *(int *)p;
    p += 4;
    D_L00_001B1980 = *(unsigned char *)p;
    p += 4;
    D_L00_001B1981 = *(unsigned char *)p;
    p += 4;
    D_L00_001B1982 = *(unsigned char *)p;
    p += 4;
    D_L00_001B1984 = *(float *)p;
    D_L00_001B1988 = *(float *)(p + 4);
    D_L00_001B198C = *(float *)(p + 8);
    D_L00_001B1990 = *(float *)(p + 0xC);
    D_L00_001B1AE8 = *(float *)(p + 0x10);
    D_L00_001A8FF0 = 0;
    p += 0x14;
    if (*(int *)p) {
        D_L00_001A8FF0 = 1;
        D_L00_001B1B10 = *(float *)(p + 4);
        D_L00_001B1B14 = *(float *)(p + 8);
        D_L00_001B1B1C = 1.0f;
        D_L00_001B1B18 = *(float *)(p + 0xC);
    }
    startPos = (float *)(p + 0x10);
    p += 0x20;
    D_00152C00.i40 = *(int *)p;
    D_00152C00.i44 = *(int *)(p + 4);
    D_00152C00.i48 = *(int *)(p + 8);
    D_L00_001C9340.count = 0;
    p += 0x10;
    if (*(int *)(p + 0xC)) {
        Tutorial00618 *t = &D_L00_001C9340;
        char *e;
        int i;

        D_L00_001C9340.count = *(int *)(p + 0xC);
        e = (char *)t;
        for (i = 0; i < t->count; i++) {
            *(float *)(e + 0x20) = *(float *)p;
            *(float *)(e + 0x24) = *(float *)(p + 4);
            *(float *)(e + 0x28) = *(float *)(p + 8);
            *(float *)(e + 0x40) = *(float *)(p + 0x10);
            *(float *)(e + 0x44) = *(float *)(p + 0x14);
            *(float *)(e + 0x48) = *(float *)(p + 0x18);
            p += 0x20;
            e += 0x10;
        }
    } else {
        p += 0x20;
    }
    D_L00_001A8F0C = *(int *)p;
    func_00279FF0();
    D_L00_001B20C0 = 0x1F4000;
    D_L00_001B2500 = 983040.0f;
    D_L00_001B2408 = 500.0f;
    D_L00_001B1EB4 = 0x3C0;
    D_L00_001B255C = 0x3C0;
    func_00284E18(D_L00_001BD2C0.i23C, D_L00_001BD2C0.i240, D_L00_001BD2C0.i244);
    func_002FC070(D_00100AE0);
    func_00282A88(D_L00_001C6F40, 0x100);
    func_00282A88(D_L00_001C7040, 0x180);
    func_00282A88(D_L00_001C6B40, 0x400);

    /* section 4: up to twelve 64-byte records */
    {
        char *s = SECTION_00618(4);
        int n = *(int *)s;

        s += 0x10;
        if (n >= 12) {
            func_0026FEB8(D_L00_002A0ED0);
            n = 12;
        }
        if (n)
            func_00282AB0(D_L00_001C6B40, s, n << 6);
    }

    /* section 0x84 */
    if (*(int *)(hdr + 0x84)) {
        char *s = SECTION_00618(0x84);
        int n = *(int *)s;

        s += 0x10;
        D_L00_001B1CDC = n;
        if (n) {
            char *entries;

            func_00282AB0(D_L00_001C5940, s, n << 4);
            entries = D_L00_001C5B40;
            func_00282AB0(entries, s + (D_L00_001B1CDC << 4), D_L00_001B1CDC << 7);
            if (D_L00_001B1CDC > 0) {
                char *e = entries;
                int left = D_L00_001B1CDC;

                do {
                    if (*(int *)(e + 0x48) < 0)
                        *(int *)(e + 0x48) = 11;
                    if (*(int *)(e + 0x4C) < 0)
                        *(int *)(e + 0x4C) = 11;
                    e += 0x80;
                } while (--left);
            }
        }
    } else {
        D_L00_001B1CDC = 0;
    }
    if (D_L00_001B24D4 > 0) {
        char *e = D_L00_001B24D0 + 0x36;
        int left = D_L00_001B24D4;

        do {
            *(unsigned short *)e = 0xFFFF;
            e += 0x40;
        } while (--left);
    }
    {
        int i = 0;

        while (i < D_L00_001B24D4) {
            unsigned short *q = (unsigned short *)0x70003000;
            int k = 0;

            while (k < 0x3FF && i < D_L00_001B24D4) {
                *q++ = i;
                k++;
                i++;
            }
            *q = 0xFFFF;
            func_002F0468((void *)0x70003000);
        }
    }
    D_L00_001BF140.mark4C = heap;

    /* section 0x10: the variant table selected by D_001A7BB4 */
    if (*(int *)(hdr + 0x10)) {
        char *s = hdr + *(int *)(hdr + 0x10 + D_001A7BB4 * 4);
        char *rec = D_L00_00277848;
        int size;

        *(int *)(rec + 0x2C) = *(int *)s;
        s += 4;
        size = *(int *)s;
        D_L00_001B1B80 = heap;
        size += 3;
        size &= ~3;
        size -= 8;
        func_00282AB0(heap, s + 4, size);
        {
            char *e = D_L00_001B1B80;
            int delta = (int)(e - 8);
            int i;

            for (i = 0; i < *(int *)(rec + 0x2C); i++) {
                *(int *)e += delta;
                e += 0x10;
            }
        }
        heap = ALIGN64_00618(heap + size);
    }
    D_L00_001BF140.mark50 = heap;

    /* section 0x34: the ties */
    {
        char *s = SECTION_00618(0x34);
        int n = *(int *)s;
        char *mark;
        int last;
        int i;

        s += 0x10;
        D_L00_001B2520 = n;
        if (n >= 0x1000)
            D_L00_001B2520 = 0xFFF;
        D_L00_001B2514 = (Tie00618 *)heap;
        D_L00_001B2524 = D_L00_001BF140.i14;
        heap += D_L00_001B2520 << 5;
        D_L00_001B2540 = 0;
        D_L00_001B2544 = 0;
        D_L00_001B2548 = 0;
        if (D_L00_001B2520)
            func_00282A60(D_L00_001B2514, 0, D_L00_001B2520 << 5);
        heap = ALIGN64_00618(heap);
        D_L00_001B251C = (Matrix00618 *)heap;
        heap += D_L00_001B2520 << 6;
        if (D_L00_001B2520)
            func_00282A60(D_L00_001B251C, 0, D_L00_001B2520 << 6);
        mark = heap;
        last = -1;
        D_L00_001B2518 = D_L00_001B2514 + D_L00_001B2520;
        for (i = 0; i < D_L00_001B2520; i++) {
            Tie00618 *tie = D_L00_001B2514 + i;
            Matrix00618 *m = D_L00_001B251C + i;
            int draw;
            int occl;

            tie->b1D = D_L00_00226A00[*(int *)s];
            if (tie->b1D != last) {
                D_L00_00226700[tie->b1D]->first = tie;
                D_L00_00226700[tie->b1D]->h3E = 0;
                D_L00_00226700[tie->b1D]->table = mark;
                last = tie->b1D;
            }
            D_L00_00226700[tie->b1D]->h3E++;
            mark += ((D_L00_00226700[tie->b1D]->h38 + 3) >> 1) << 2;
            draw = *(int *)(s + 4) >> 4;
            if (draw >= 0x100)
                draw = 0xFF;
            tie->h18 = 0;
            tie->h1A = 0xFFFF;
            tie->h16 = 0;
            tie->h14 = 0xFFFF;
            tie->b1C = draw;
            tie->b1F = 0xFF;
            occl = *(int *)(s + 0xC);
            qcopy(&m->row[0], s + 0x10);
            qcopy(&m->row[1], s + 0x20);
            qcopy(&m->row[2], s + 0x30);
            qcopy(&m->row[3], s + 0x40);
            tie->h10 = occl;
            s += 0x50;
            tie->h12 = i;
            m->row[3].f[3] = D_L00_00226700[tie->b1D]->f40;
            func_00283098(tie, &D_L00_00226700[tie->b1D]->sphere, m);
            tie->bounds.f[3] = D_L00_00226700[tie->b1D]->sphere.f[3]
                * func_L00_002EE050(func_L00_002EE050(func_00282DF0(&m->row[0]), func_00282DF0(&m->row[1])), func_00282DF0(&m->row[2]));
            func_00282D60(tie, tie, m->row[3].f[3]);
            func_00282CC0(tie, tie, &m->row[3]);
            (D_L00_001B251C + i)->row[0].f[3] = 1.0f / func_00282DF0(&(D_L00_001B251C + i)->row[0]);
            (D_L00_001B251C + i)->row[1].f[3] = 1.0f / func_00282DF0(&(D_L00_001B251C + i)->row[1]);
            (D_L00_001B251C + i)->row[2].f[3] = 1.0f / func_00282DF0(&(D_L00_001B251C + i)->row[2]);
            tie->h18 = *(unsigned short *)s;
            s += 0x10;
        }
        if (D_L00_001B2510 >= 0x80)
            D_L00_001B2510 = 0x7F;
        heap = ALIGN64_00618(mark);
    }

    /* section 0x94: tie groups */
    if (*(int *)(hdr + 0x94)) {
        short *s = (short *)SECTION_00618(0x94);
        int idx = *s++;

        while (idx != -1) {
            if (idx < D_L00_001B2520) {
                Tie00618 *tie = D_L00_001B2514 + idx;
                TieClass00618 *cls = D_L00_00226700[tie->b1D];

                func_00282AB0(cls->table + ((((cls->h38 + 3) >> 1) * (tie - cls->first)) << 2), s + 1, *s << 1);
            }
            s += *s + 1;
            idx = *s++;
        }
    }

    /* section 0x38: a relocated pointer table */
    {
        int *s = (int *)SECTION_00618(0x38);
        int n = *s++;
        int size = *s++;
        int *offs;
        char *base;

        s += 2;
        offs = s;
        D_L00_001A9014.p14 = (int)heap;
        heap += n << 2;
        heap = ALIGN64_00618(heap);
        s += (n + 3) & ~3;
        base = heap;
        heap += size;
        heap = ALIGN64_00618(heap);
        if (n) {
            int i;

            for (i = 0; i < n; i++) {
                if (offs[i] != -1) {
                    D_L00_001A9014.i18 = i + 1;
                    ((int *)D_L00_001A9014.p14)[i] = (int)(base + offs[i]);
                } else {
                    ((int *)D_L00_001A9014.p14)[i] = 0;
                }
            }
        }
        if (size)
            func_00282B50(base, (char *)(((int)s + 0xF) & ~0xF), size);
    }
    D_L00_001BF140.mark54 = heap;

    /* section 0x40: the shrubs */
    {
        char *s = SECTION_00618(0x40);
        int n = *(int *)s;
        int last;
        int i;

        D_L00_001B23F8 = (Shrub00618 *)heap;
        s += 0x10;
        D_L00_001B23F4 = n;
        heap += n << 5;
        if (n)
            func_00282A60(D_L00_001B23F8, 0, n << 5);
        heap = ALIGN64_00618(heap);
        D_L00_001B2400 = (Matrix00618 *)heap;
        heap += D_L00_001B23F4 << 6;
        if (D_L00_001B23F4)
            func_00282A60(D_L00_001B2400, 0, D_L00_001B23F4 << 6);
        D_L00_001B2404 = (unsigned char *)heap;
        heap += D_L00_001B23F4 * 0x60;
        heap = ALIGN64_00618(heap);
        if (D_L00_001B23F4)
            func_00282A60(D_L00_001B2404, 0, D_L00_001B23F4 * 0x60);
        last = -1;
        *(unsigned char **)(D_L00_001ACE90 + 4) = D_L00_001B2404;
        D_L00_001B23FC = D_L00_001B23F8 + D_L00_001B23F4;
        for (i = 0; i < D_L00_001B23F4; i++) {
            int cls = D_L00_0021EBA0[*(int *)s];
            Shrub00618 *shrub = D_L00_001B23F8 + i;
            Matrix00618 *m = D_L00_001B2400 + i;
            float radius, a, b;
            int w, h, r, g, bl;

            shrub->b1A = cls;
            if (cls != last) {
                last = cls;
                D_L00_0021EA20[cls]->first = shrub;
                D_L00_0021EA20[cls]->h16 = 0;
            }
            D_L00_0021EA20[cls]->h16++;
            shrub->h18 = i;
            radius = *(float *)(s + 4);
            shrub->f10 = radius;
            if (radius < 16.0f)
                shrub->f10 = 16.0f;
            shrub->b1B = 0;
            shrub->h1E = 0xFFFF;
            if (D_L00_0021EA20[cls]->p1C) {
                float t;

                shrub->b17 = func_00283CF0(*D_L00_0021EA20[cls]->p1C);
                t = func_00283CE0(shrub->b17) + 24.0f;
                if (shrub->f10 < t)
                    shrub->f10 = t;
            }
            qcopy(&m->row[0], s + 0x10);
            qcopy(&m->row[1], s + 0x20);
            qcopy(&m->row[2], s + 0x30);
            qcopy(&m->row[3], s + 0x40);
            s += 0x50;
            m->row[3].f[3] = D_L00_0021EA20[cls]->f20;
            a = (func_00282DF0(&m->row[0]) + func_00282DF0(&m->row[1])) * 0.5f;
            b = func_00282DF0(&m->row[2]);
            w = func_00283CF0(a * 4096.0f);
            h = func_00283CF0(b * 4096.0f);
            if (h > 0x10000)
                h = 0x10000;
            if (w > 0x10000)
                w = 0x10000;
            m->row[2].i[3] = w | (h << 16);
            r = *(int *)s;
            s += 4;
            g = *(int *)s;
            s += 4;
            bl = *(int *)s;
            s += 8;
            m->row[0].i[3] = ((bl << 16) | ((g << 8) | 0x80000000)) | r;
            shrub->h1C = *(unsigned short *)s;
            s += 0x10;
            func_00283098(shrub, D_L00_0021EA20[cls], m);
            shrub->bounds.f[3] = D_L00_0021EA20[cls]->fC
                * func_L00_002EE050(func_L00_002EE050(func_00282DF0(&m->row[0]), func_00282DF0(&m->row[1])), func_00282DF0(&m->row[2]));
            func_00282D60(shrub, shrub, m->row[3].f[3]);
            func_00282CC0(shrub, shrub, &m->row[3]);
        }
    }
    {
        unsigned short *q = (unsigned short *)0x70000000;
        int i;

        for (i = 0; i < D_L00_001B23F4; i++)
            *q++ = i;
        *q = 0xFFFF;
        func_002E2C38((void *)0x70000000);
    }
    {
        int i;

        for (i = 0; i < D_L00_001B23F4; i++) {
            unsigned char *c = D_L00_001B2404 + i * 0x60;
            int r = 0, g = 0, b = 0;
            int k;

            for (k = 0; k < 24; k++) {
                r += c[0];
                g += c[1];
                b += c[2];
                c += 4;
            }
            (D_L00_001B2400 + i)->row[1].i[3] = ((b / 24) << 16) | ((g / 24) << 8) | (r / 24);
        }
    }

    /* section 0x44: another relocated pointer table */
    {
        int *s = (int *)SECTION_00618(0x44);
        int n = *s++;
        int size = *s++;
        int *offs;
        char *base;

        s += 2;
        offs = s;
        D_L00_001A9014.p1C = (int)heap;
        heap += n << 2;
        heap = ALIGN64_00618(heap);
        s += n;
        base = heap;
        heap += size;
        heap = ALIGN64_00618(heap);
        if (n) {
            int i;

            for (i = 0; i < n; i++) {
                if (offs[i] != -1) {
                    D_L00_001A9014.i20 = i + 1;
                    ((int *)D_L00_001A9014.p1C)[i] = (int)(base + offs[i]);
                } else {
                    ((int *)D_L00_001A9014.p1C)[i] = 0;
                }
            }
        }
        if (size)
            func_00282B50(base, (char *)(((int)s + 0xF) & ~0xF), size);
    }

    /* section 8: 32-byte records */
    if (*(int *)(hdr + 8)) {
        char *s = SECTION_00618(8);
        int n = *(int *)s;

        D_L00_001B1844 = heap;
        s += 0x10;
        D_L00_001B1848 = n;
        heap += n << 5;
        if (n)
            func_00282A60(D_L00_001B1844, 0, n << 5);
        heap = ALIGN64_00618(heap);
        if (D_L00_001B1848 > 0) {
            char *e = D_L00_001B1844;
            int left = D_L00_001B1848;

        copy_record:
            *(int *)(e + 0xC) = *(int *)s;
            s += 4;
            *(float *)e = *(float *)s;
            *(float *)(e + 4) = *(float *)(s + 4);
            *(float *)(e + 8) = *(float *)(s + 8);
            s += 0xC;
            *(float *)(e + 0x10) = *(float *)s;
            *(float *)(e + 0x14) = *(float *)(s + 4);
            *(float *)(e + 0x18) = *(float *)(s + 8);
            s += 0xC;
            *(int *)(e + 0x1C) = *(int *)s;
            s += 4;
            e += 0x20;
            if (--left)
                goto copy_record;
        }
    }

    /* section 0xC: 0x90-byte records */
    if (*(int *)(hdr + 0xC)) {
        char *s = SECTION_00618(0xC);
        int n = *(int *)s;

        s += 0x10;
        D_00188660.count = n;
        if (n) {
            int i, off;

            D_00188660.table = heap;
            heap += n * 0x90;
            heap = ALIGN64_00618(heap);
            func_00282A60(D_00188660.table, 0, n * 0x90);
            for (i = 0, off = 0; i < D_00188660.count; i++, off += 0x90) {
                char *e = D_00188660.table + off;

                func_00282AB0(e, s, 0x90);
                s += 0x90;
                func_L00_0035F7E8(e);
            }
        } else {
            D_00188660.table = 0;
        }
    }

    /* section 0x4C: the mobys */
    D_L00_001BF140.mark58 = heap;
    {
        int *s = (int *)SECTION_00618(0x4C);
        int count = 0;
        short *cursor = D_L00_001FB660;
        int n, extra;

        n = *s++;
        extra = *s++;
        s += 2;
        D_L00_001B1E9C = (Moby00618 *)heap;
        func_00282A60(heap, 0, (n + extra) << 8);
        func_00282A60(D_L00_001C5480, 0, 0xC0);
        func_00282A60(D_L00_001C5540, 0, 0xC0);
        if (n > 0) {
            do {
                int *next = s + (*s >> 2);
                int skip = 0;
                int cls, w2, flags, uid, bolts, bolts2, xp, xp2, w9;
                Moby00618 *moby;

                s++;
                cls = *s++;
                w2 = *s++;
                flags = *s++;
                uid = *s++;
                bolts = *s++;
                bolts2 = *s++;
                xp = *s++;
                xp2 = *s++;
                w9 = *s++;
                if (cls >= 0 && w9 > 0) {
                    int lvl = (D_001A52E8[(D_001A79F0 << 4) + cls] >> (w2 * 2)) & 3;

                    if (lvl == 0)
                        lvl = func_L00_002E3B38(cls);
                    if (*s == 0x1F5 || *s == 0x200) {
                        skip = w9 < lvl;
                    } else if (lvl < w9) {
                        D_L00_001C5540[cls][w2] += bolts;
                        D_L00_001C5480[cls][w2] += xp;
                        skip = 1;
                    }
                }
                if (!skip && flags) {
                    if (D_L00_0021DDB0[uid + 0x464]) {
                        skip = 1;
                    } else if (flags & 3) {
                        if (D_L00_001B1CE0[cls] & 0x80) {
                            if (flags & 2) {
                                int odd = uid & 1;
                                int c = SAVE_CELL_00618(uid);

                                if (!(odd ? (c >> 4) & 8 : c & 8)) {
                                    unsigned char *cell = &SAVE_CELL_00618(uid);
                                    int c2 = *cell;
                                    int v = odd ? c2 | 0x80 : c2 | 8;
                                    unsigned char v8 = v;
                                    unsigned char w = odd ? v8 & 0x8F : v8 & 0xF8;

                                    *cell = w;
                                }
                                bolts = bolts2;
                                xp = xp2;
                            } else {
                                skip = 1;
                            }
                        } else {
                            skip = !(flags & 1);
                        }
                    } else if (flags & 8) {
                        int odd = uid & 1;

                        if (reload) {
                            unsigned char *cell = &SAVE_CELL_00618(uid);
                            int c = *cell;
                            unsigned char w = odd ? c & 0x8F : c & 0xF8;

                            *cell = w;
                        } else {
                            int c = SAVE_CELL_00618(uid);

                            if (odd ? (c >> 4) & 7 : c & 7)
                                skip = 1;
                        }
                    } else if ((flags & 0xC) == 4) {
                        int odd = uid & 1;
                        int c = SAVE_CELL_00618(uid);

                        if (odd ? (c >> 4) & 7 : c & 7)
                            skip = 1;
                    }
                }
                if (skip) {
                    *cursor = -1;
                } else {
                    int snap;
                    float lift;
                    int r, g, b, pvar;

                    *cursor = count;
                    moby = D_L00_001B1E9C + count;
                    func_0029F0C8(moby, *s++);
                    moby->hB2 = uid;
                    moby->bB0 = cls;
                    moby->bB1 = w2 & 0xF;
                    if (flags == 0)
                        moby->bB1 |= 0x80;
                    moby->hB4 = bolts;
                    moby->hB6 = xp;
                    if (moby->pClass)
                        moby->f2C = ((MobyClass00618 *)moby->pClass)->f24 * *(float *)s;
                    s++;
                    moby->h32 = *(unsigned short *)s;
                    s++;
                    moby->b30 = *(unsigned char *)s;
                    s += 3;
                    moby->pos.f[0] = *(float *)s;
                    moby->pos.f[1] = *(float *)(s + 1);
                    moby->pos.f[2] = *(float *)(s + 2);
                    s += 3;
                    moby->rot[0] = *(float *)s;
                    moby->rot[1] = *(float *)(s + 1);
                    moby->rot[2] = *(float *)(s + 2);
                    s += 3;
                    moby->b21 = *(unsigned char *)s;
                    s++;
                    snap = *s++;
                    lift = *(float *)s++;
                    if (snap) {
                        float h = func_002A89A8(&moby->pos, 0, 0.5f);

                        if (0.0f < h)
                            moby->pos.f[2] = h + lift;
                    }
                    s++;
                    moby->h36 = 0x7F80;
                    moby->i68 = *s++;
                    if (*s == 0)
                        moby->h36 = 0;
                    s++;
                    if (moby->pClass)
                        ((MobyClass00618 *)moby->pClass)->h44 |= *(unsigned short *)s;
                    moby->h34 |= *(unsigned short *)s;
                    s++;
                    if (moby->pClass)
                        func_002A0F48(moby);
                    r = *s++;
                    g = *s++;
                    b = *s++;
                    pvar = *s++;
                    func_002A0468(moby, (b << 16) + (g << 8) + r, 0, 0, 0);
                    moby->i38 = pvar;
                    moby->b7E &= 0xFE;
                    if (D_001A79F0 >= 0 && *s != -1)
                        func_L00_00309140(moby, *s);
                    count++;
                }
                cursor++;
                s = next;
            } while (--n);
        }
        {
            Moby00618 *tail = D_L00_001B1E9C + count;
            int total = (count + extra) << 8;

            D_L00_001B18DC = tail;
            func_0029F0C8(tail, 0);
            heap += total;
            tail->state = 0xFD;
            D_L00_001B1EA0 = D_L00_001B18DC + 1;
            D_L00_001B1EA0->state = 0xFF;
            D_L00_001B1EAC = heap;
            heap += extra << 7;
            heap = ALIGN64_00618(heap);
            D_L00_001BF140.mark5C = heap;
            D_L00_001B1EA4 = (Moby00618 *)((char *)D_L00_001B1E9C + total - 0x100);
        }
    }

    /* sections 0x60 / 0x5C: pointed-to blobs copied into the heap */
    if (*(int *)(hdr + 0x60)) {
        char *blob = SECTION_00618(0x60);
        int *dir = (int *)SECTION_00618(0x5C);
        Moby00618 *moby;
        int i;

        for (i = 0; i < D_L00_001B1848; i++) {
            int *slot = (int *)(D_L00_001B1844 + (i << 5) + 0x1C);
            int idx = *slot;

            if (idx < 0) {
                *slot = 0;
            } else {
                int *e = (int *)((char *)dir + (idx << 3));
                int size = e[1];

                *slot = (int)heap;
                func_00282B50(heap, blob + e[0], size);
                e[0] = (int)heap;
                heap += size;
            }
        }
        for (i = 0; i < D_00188660.count; i++) {
            int *slot = (int *)(D_00188660.table + i * 0x90 + 8);
            int idx = *slot;

            if (idx < 0) {
                *slot = 0;
            } else {
                int *e = (int *)((char *)dir + (idx << 3));
                int size = e[1];

                *slot = (int)heap;
                func_00282B50(heap, blob + e[0], size);
                e[0] = (int)heap;
                heap += size;
            }
        }
        for (moby = D_L00_001B1E9C; moby != D_L00_001B1EA0; moby++) {
            if (moby->oClass == 0) {
                moby->i68 = 0;
            } else {
                int idx = moby->i68;

                if (idx < 0) {
                    moby->i68 = 0;
                } else {
                    int *e = (int *)((char *)dir + (idx << 3));
                    int size = e[1];

                    moby->i68 = (int)heap;
                    func_00282B50(heap, blob + e[0], size);
                    e[0] = (int)heap;
                    heap += size;
                }
            }
        }
    }
    heap = ALIGN64_00618(heap);
    D_L00_001BF140.mark60 = heap;

    /* section 0x58: fix-ups through the blob directory */
    if (*(int *)(hdr + 0x58)) {
        int *s = (int *)SECTION_00618(0x58);
        int *dir = (int *)SECTION_00618(0x5C);

        while (s[0] >= 0) {
            int *e = (int *)((char *)dir + (s[0] << 3));

            if (e[0] >= D_L00_001BF140.i18) {
                int *slot = (int *)(e[0] + s[1]);

                if (*slot >= 0)
                    *slot = D_L00_001FB660[*slot];
            }
            s += 2;
        }
    }
    if (*(int *)(hdr + 0x64)) {
        int *s = (int *)SECTION_00618(0x64);
        int *dir = (int *)SECTION_00618(0x5C);

        while (s[0] >= 0) {
            int *e = (int *)((char *)dir + (s[0] << 3));

            if (e[0] >= D_L00_001BF140.i18)
                *(int *)(e[0] + s[1]) += e[0];
            s += 2;
        }
    }

    /* section 0x50: moby groups */
    if (*(int *)(hdr + 0x50)) {
        int *s = (int *)SECTION_00618(0x50);
        char *base = heap;
        int n = *s++;
        int size = *s++;
        int *offs = s + 2;
        int i;

        heap += size;
        heap = ALIGN64_00618(heap);
        if (size)
            func_00282B50(base, offs + n, size);
        func_00282A60(D_L00_001FA920, 0, 0x3C0);
        for (i = 0; i < n; i++) {
            int off = *offs++;

            if (off >= 0) {
                short *list = (short *)(base + off);
                short *src = list;
                short *dst = list;
                int end;

                D_L00_001FA920[i] = (int)list;
                D_L00_001B1EB8 = i + 1;
                do {
                    int id = D_L00_001FB660[*(unsigned short *)src & 0x7FFF];

                    end = *src & 0x8000;
                    if (id >= 0)
                        *dst++ = id;
                    if (end) {
                        if (D_L00_001FA920[i] < (int)dst)
                            dst[-1] |= 0x8000;
                        else
                            D_L00_001FA920[i] = 0;
                    }
                    src++;
                } while (!end);
            }
        }
    }

    /* section 0x54 */
    if (*(int *)(hdr + 0x54)) {
        int *s = (int *)SECTION_00618(0x54);
        char *base = heap;
        int size = *s++;
        int n = *s++;
        int *dir;
        int i;

        s += 2;
        heap += size;
        heap = ALIGN64_00618(heap);
        if (size)
            func_00282B50(base, s, size);
        s = (int *)((char *)s + size);
        dir = (int *)SECTION_00618(0x5C);
        for (i = 0; i < n; i++) {
            int word = s[0];
            int *e = (int *)((char *)dir + ((word & 0xFFFF) << 3));

            if (e[0] >= D_L00_001BF140.i18)
                *(int *)(e[0] + (word >> 16)) = (int)(base + s[1]);
            s += 2;
        }
    }

    /* section 0x78 */
    if (*(int *)(hdr + 0x78)) {
        int *s = (int *)SECTION_00618(0x78);
        char *blob;
        int size;

        D_L00_001B1F84.iA4 = s[0];
        blob = (char *)s + s[1];
        size = s[2];
        D_L00_001B1F84.pA8 = heap;
        heap += size;
        s += 4;
        heap = ALIGN64_00618(heap);
        if (size)
            func_00282B50(D_L00_001B1F84.pA8, blob, size);
        if (D_L00_001B1F84.iA4 > 0) {
            char *base = D_L00_001B1F84.pA8;
            char **q = D_L00_001FDA80;
            int left = D_L00_001B1F84.iA4;

            do {
                *q++ = base + *s++;
            } while (--left);
        }
    }

    /* section 0x7C */
    if (*(int *)(hdr + 0x7C)) {
        int *s = (int *)SECTION_00618(0x7C);
        int n = s[0];
        char *blob;
        char *copy;
        int size;

        D_L00_001B16C0.iC4 = n;
        blob = (char *)s + s[1];
        size = s[2];
        D_L00_001B16C0.pC0 = heap;
        heap += n << 5;
        s += 4;
        heap = ALIGN64_00618(heap);
        if (n > 0) {
            char *e = D_L00_001B16C0.pC0;
            int left = n;

            do {
                qcopy(e, s);
                s += 4;
                *(int *)(e + 0x14) = *s;
                s += 4;
                e += 0x20;
            } while (--left);
        }
        copy = heap;
        heap += size;
        heap = ALIGN64_00618(heap);
        if (size)
            func_00282B50(copy, blob, size);
        if (D_L00_001B16C0.iC4 > 0) {
            char *e = D_L00_001B16C0.pC0 + 0x10;
            int left = D_L00_001B16C0.iC4;

            do {
                *(char **)e = copy + *s++;
                e += 0x20;
            } while (--left);
        }
    }

    /* section 0x74: 0x90-byte records from 0x80-byte source records */
    if (*(int *)(hdr + 0x74)) {
        char *s = SECTION_00618(0x74);
        int n = *(int *)s;

        D_L00_001B1F84.p84 = heap;
        D_L00_001B1F84.i88 = n;
        s += 0x10;
        heap += n * 0x90;
        heap = ALIGN64_00618(heap);
        if (n)
            func_00282A60(D_L00_001B1F84.p84, 0, n * 0x90);
        {
            int i, off;

            for (i = 0, off = 0; i < D_L00_001B1F84.i88; i++, off += 0x90) {
                func_00282AB0(D_L00_001B1F84.p84 + off, s, 0x90);
                s += 0x80;
            }
        }
    }

    /* sections 0x68, 0x6C, 0x70: 0x80-byte records */
    if (*(int *)(hdr + 0x68)) {
        char *s = SECTION_00618(0x68);
        int n = *(int *)s;
        int i;

        D_L00_001B1F84.p8C = heap;
        s += 0x10;
        D_L00_001B1F84.i90 = n;
        heap += n << 7;
        heap = ALIGN64_00618(heap);
        if (n)
            func_00282A60(D_L00_001B1F84.p8C, 0, n << 7);
        for (i = 0; i < D_L00_001B1F84.i90; i++) {
            func_00282AB0(D_L00_001B1F84.p8C + (i << 7), s, 0x80);
            s += 0x80;
        }
    }
    if (*(int *)(hdr + 0x6C)) {
        char *s = SECTION_00618(0x6C);
        int n = *(int *)s;
        int i;

        D_L00_001B1F84.p94 = heap;
        s += 0x10;
        D_L00_001B1F84.i98 = n;
        heap += n << 7;
        heap = ALIGN64_00618(heap);
        if (n)
            func_00282A60(D_L00_001B1F84.p94, 0, n << 7);
        for (i = 0; i < D_L00_001B1F84.i98; i++) {
            func_00282AB0(D_L00_001B1F84.p94 + (i << 7), s, 0x80);
            s += 0x80;
        }
    }
    if (*(int *)(hdr + 0x70)) {
        char *s = SECTION_00618(0x70);
        int n = *(int *)s;
        int i;

        D_L00_001B1F84.p9C = heap;
        s += 0x10;
        D_L00_001B1F84.iA0 = n;
        heap += n << 7;
        heap = ALIGN64_00618(heap);
        if (n)
            func_00282A60(D_L00_001B1F84.p9C, 0, n << 7);
        for (i = 0; i < D_L00_001B1F84.iA0; i++) {
            func_00282AB0(D_L00_001B1F84.p9C + (i << 7), s, 0x80);
            s += 0x80;
        }
    }

    /* section 0x88 */
    if (*(int *)(hdr + 0x88)) {
        char *s = SECTION_00618(0x88);
        int size = *(int *)s + 0x4000;

        D_L00_001B1880 = heap;
        func_00282AB0(heap, s + 0x10, size);
        heap += size;
    }
    heap = ALIGN64_00618(heap);

    /* section 0x80 */
    if (*(int *)(hdr + 0x80)) {
        char *s = SECTION_00618(0x80);
        int n = *(int *)s;

        D_L00_001B1CD8 = heap;
        D_L00_001B1CD4 = n;
        heap = (char *)(((int)heap + (n << 4) + 0x83F) & 0xFFFFFFC0u);
        if (n)
            func_00282AB0(D_L00_001B1CD8, s + 0x10, (n << 4) + 0x800);
        else
            func_00282AB0(D_L00_001B1CD8, s + 0x10, 0x800);
    }

    /* section 0x8C */
    if (*(int *)(hdr + 0x8C)) {
        char *s = SECTION_00618(0x8C);
        int n = *(int *)s;

        D_L00_001B1F40 = heap;
        D_L00_001B1F10 = n;
        heap += n << 5;
        heap = ALIGN64_00618(heap);
        if (n)
            func_00282AB0(D_L00_001B1F40, s + 0x10, n << 5);
    }
    D_L00_001B20B0.pB0 = heap;
    D_L00_001BF140.mark64 = heap;
    D_L00_001B20B0.iB8 = -1;
    heap += 0x20000;
    D_L00_001B20B0.iB4 = 0;
    D_L00_001B20B0.iBC = 0;
    func_00282A88(D_L00_001FE140, 0x200);

    if (D_001A79F0 >= 0) {
        D_00152C00.hero = 0;
        if (0.0f < startPos[0]) {
            Moby00618 *m = func_0029EFD0(0xD54);

            m->pos.f[0] = startPos[0];
            m->pos.f[1] = startPos[1];
            m->pos.f[2] = startPos[2];
            m->rot[2] = startPos[3];
            m->h32 = 0xFF;
            m->b30 = 0x10;
            m->i64 = 0x3603C0;
            m->h34 &= 0xFFFD;
            if (m->b63)
                m->b63 = 8;
            func_002A0F48(m);
            D_00152C00.hero = m;
            func_L00_00309140(m, 0);
        }
    }
    heap = (char *)(((int)heap + 0xF) & ~0xF);

    /* section 0x98: the group record and its five tables */
    {
        char *s = SECTION_00618(0x98);
        int size = *(int *)s;
        Groups00618 *g;
        int i;

        D_L00_001B1AFC.p00 = (int)heap;
        func_00282AB0(heap, s + 4, size);
        heap += size;
        g = GROUPS_00618;
        if (g->p4)
            g->p4 += (int)g;
        else
            g->p4 = 0;
        g = GROUPS_00618;
        if (g->p8)
            g->p8 += (int)g;
        else
            g->p8 = 0;
        g = GROUPS_00618;
        if (g->pC)
            g->pC += (int)g;
        else
            g->pC = 0;
        g = GROUPS_00618;
        if (g->p10)
            g->p10 += (int)g;
        else
            g->p10 = 0;
        g = GROUPS_00618;
        if (g->p14)
            g->p14 += (int)g;
        else
            g->p14 = 0;
        g = GROUPS_00618;
        for (i = 0; i < g->count; i++) {
            if (g->entries[i].h0 == 0)
                g->entries[i].iC = 0;
            else
                g->entries[i].iC += (int)g->p4;
            if (g->entries[i].h2 == 0)
                g->entries[i].i10 = 0;
            else
                g->entries[i].i10 += (int)g->p8;
            if (g->entries[i].h4 == 0)
                g->entries[i].i14 = 0;
            else
                g->entries[i].i14 += (int)g->pC;
            if (g->entries[i].h6 == 0)
                g->entries[i].i18 = 0;
            else
                g->entries[i].i18 += (int)g->p10;
            if (g->entries[i].h8 == 0)
                g->entries[i].i1C = 0;
            else
                g->entries[i].i1C += (int)g->p14;
        }
        {
            int bytes = GROUPS_00618->count * 0x1C;

            D_L00_001B1AFC.pFC = (int)heap;
            func_00282A60(heap, 0, bytes);
            heap += bytes;
        }
        for (i = 0; i < GROUPS_00618->count; i++)
            ((int *)D_L00_001B1AFC.pFC)[i] = D_L00_001B1AFC.pFC + (GROUPS_00618->count << 2) + i * 0x18;
    }

    if (D_L00_001B1A40 && *(int *)(hdr + 0x90)) {
        int *s = (int *)SECTION_00618(0x90);
        int *base = s;
        int nTies = s[0];
        int nShrubs = s[1];
        int nMobys = s[2];
        int *rec;
        int tiesChanged = 1;
        int shrubsChanged;
        int tieSize;
        int i;

        s += 4;
        rec = s;
        if (D_L00_001C9340.count) {
            tieSize = nTies << 3;
            rec += nTies << 1;
            if (D_L00_001C9340.i18 == nTies)
                tiesChanged = 0;
            D_L00_001C9340.i1C = tiesChanged == 0;
        } else if (D_L00_001B24D4 == nTies) {
            tiesChanged = 0;
            tieSize = nTies << 3;
            if (nTies > 0) {
                unsigned char *e = (unsigned char *)D_L00_001B24D0 + 0x3D;
                int left = nTies;

                do {
                    if (*e != rec[1])
                        tiesChanged = 1;
                    e += 0x40;
                    rec += 2;
                } while (--left);
            }
        } else {
            tieSize = nTies << 3;
            rec += nTies << 1;
        }
        shrubsChanged = 1;
        if (D_L00_001B2518 - D_L00_001B2514 == nShrubs) {
            shrubsChanged = 0;
            if (nShrubs > 0) {
                unsigned short *e = &D_L00_001B2514->h10;
                int left = nShrubs;

                do {
                    if (*e != *(unsigned short *)(rec + 1))
                        shrubsChanged = 1;
                    e += 0x10;
                    rec += 2;
                } while (--left);
            }
        } else {
            rec += nShrubs << 1;
        }
        {
            unsigned short *table = D_L00_001B19F0;
            int *r = rec;
            Moby00618 *moby;

            func_00282A60(table, -1, 0x10000);
            for (i = 0; i < nMobys; i++) {
                if ((unsigned)(r[1] + 0x4000) < 0x8000)
                    table[r[1] + 0x4000] = *(unsigned short *)r;
                r += 2;
            }
            for (moby = D_L00_001B1E9C; moby->state != 0xFF; moby++) {
                if (moby->h36 != 0x7F80) {
                    if ((unsigned)(moby->hB2 + 0x4000) < 0x8000) {
                        short v = table[moby->hB2 + 0x4000];

                        if (v < 0)
                            moby->h36 = 0x7F80;
                        else
                            moby->h36 = ((v >> 3) << 8) | (1 << (v & 7));
                    } else {
                        moby->h36 = 0x7F80;
                    }
                }
            }
        }
        if (tiesChanged) {
            if (D_L00_001B24D4 > 0) {
                unsigned short *e = (unsigned short *)(D_L00_001B24D0 + 0x3A);
                int left = D_L00_001B24D4;

                do {
                    *e = 0x7F80;
                    e = (unsigned short *)((char *)e + 0x40);
                } while (--left);
            }
        } else if (D_L00_001C9340.count) {
            int *r = base + 4;

            for (i = 0; i < nTies; i++) {
                D_L00_001C9340.bits[i] = ((r[0] >> 3) << 8) | (1 << (r[0] & 7));
                r += 2;
            }
        } else {
            int *r = base + 4;

            for (i = 0; i < nTies; i++) {
                *(unsigned short *)(D_L00_001B24D0 + 0x3A + i * 0x40) = ((r[0] >> 3) << 8) | (1 << (r[0] & 7));
                r += 2;
            }
        }
        if (shrubsChanged) {
            unsigned short *table = D_L00_001B19F0;
            int *r = (int *)((char *)base + 0x10 + tieSize);
            Tie00618 *tie;

            func_00282A60(table, 0xFFFEFFFE, 0x8000);
            for (i = 0; i < nShrubs; i++) {
                if ((unsigned)r[1] < 0x4000)
                    table[r[1]] = *(unsigned short *)r;
                r += 2;
            }
            for (tie = D_L00_001B2514; tie != D_L00_001B2518; tie++) {
                if ((unsigned)tie->h10 < 0x4000) {
                    short v = table[tie->h10];

                    if (v < 0)
                        tie->h10 = 0x7F80;
                    else
                        tie->h10 = ((v >> 3) << 8) | (1 << (v & 7));
                } else {
                    tie->h10 = 0x7F80;
                }
            }
        } else {
            int *r = (int *)((char *)base + 0x10 + tieSize);
            Tie00618 *tie = D_L00_001B2514;

            for (i = 0; i < nShrubs; i++) {
                tie->h10 = ((r[0] >> 3) << 8) | (1 << (r[0] & 7));
                r += 2;
                tie++;
            }
        }
        D_L00_001B1A50 = 2;
    } else {
        Moby00618 *moby;
        Tie00618 *tie;

        for (moby = D_L00_001B1E9C; moby != D_L00_001B1EA4; moby++)
            moby->h36 = 0x7F80;
        for (tie = D_L00_001B2514; tie != D_L00_001B2518; tie++)
            tie->h10 = 0x7F80;
        if (D_L00_001B24D4 > 0) {
            unsigned short *e = (unsigned short *)(D_L00_001B24D0 + 0x3A);
            int left = D_L00_001B24D4;

            do {
                *e = 0x7F80;
                e = (unsigned short *)((char *)e + 0x40);
            } while (--left);
        }
    }
    D_L00_001B1A50 = 0;
    D_L00_001C9340.i1C = 0;
    func_0027B7E0();
    func_L00_002A4928();
    func_L00_002A4D18();
    func_L00_002D9E80();
    func_00272368();
    func_002B8518();
    func_L00_0037E418();
    func_L00_00367308();
    func_L00_0032A0E8();
    func_L00_0032A138();
    func_L00_0032A170();
    func_L00_003E8150();
    func_L00_002E9098();
    D_L00_001FDE78 = 0;
    D_L00_001FDEF8 = 0;
    D_L00_001B1FB0 = 0;
    D_L00_001B1FF0 = 0;
    D_L00_001B2030 = 0;
    func_L00_00403BF8();
    {
        int i;

        for (i = 0x13; i >= 0; i--)
            D_L00_00220DA0[i] = 0;
    }
    D_L00_001B19C8 = 0;
    D_L00_001B1AEC = 0;
    D_L00_001AA0F8 = 0xE0;
    if (D_00152C00.hero) {
        Moby00618 *m = D_00152C00.hero;

        *(long long *)((char *)m + 0x38) = *(long long *)(*(char **)(D_00189E20 + 0x2290) + 0x38);
    }
    func_00272198(8.0f);
    switch (D_001A79F0) {
    case 2:
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
        D_L00_001B18D0 = D_L00_001A8A78;
        break;
    default:
        D_L00_001B18D0 = D_L00_001A8A48;
        break;
    }
    D_L00_001A8AA8 = D_L00_001B18D0;
    return heap;
}
