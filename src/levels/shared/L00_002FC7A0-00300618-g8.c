/* func_L00_00300618: the level gameplay loader. It relocates the level file's
 * sections (ties, shrubs, mobys, moby groups, paths, occlusion) into the aligned level
 * heap and returns the heap cursor. RAC1 counterpart: load_level_gameplay
 * (rac1-decomp src/overlays/shared/level_gameplay_loading.c), whose source shapes
 * this follows: the function-scope scratch int `tmp`, sequential record reads through
 * char pointers, and header words read as ints (RAC1 reads them as struct members).
 * The section-8 records are copied by an explicit goto loop: a do loop has its four
 * cursor advances turned into address givs by this cc1 (docs/build/compiler-notes.md).
 */
#include "common.h"

typedef int TI128_00618 __attribute__((mode(TI)));
typedef union { TI128_00618 q; float f[4]; int i[4]; } Vec00618;

#define ALIGN64_00618(p) ((char *)(((int)(p) + 0x3F) & 0xFFFFFFC0u))
#define SECTION_00618(off) (hdr + ((int *)hdr)[(off) / 4])
#define SAVE_CELL_00618(uid) D_0019B4A8[((uid) >> 1) + (D_001A79F0 << 10)]

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
typedef struct { char pad00[8]; int i8; char pad0C[0x84]; } Sound00618;  /* 0x90 */
typedef struct { char pad00[0x1730]; int count; Sound00618 *table; } Slots00618;
typedef struct { char pad00[0xC]; int count; int i10; unsigned short *bits; int i18; int i1C; float pos[2][4]; float dir[2][4]; } Tutorial00618;
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

typedef struct Groups00618 {
    int count;                    /* 0x00 */
    char *p4;
    char *p8;
    char *pC;
    char *p10;
    char *p14;
    char pad18[0x18];
    GroupEntry00618 entries[0];   /* 0x30 */
} Groups00618;

typedef struct { int offset; int size; } Blob00618;
typedef struct { int p14; int i18; int p1C; int i20; } Reloc00618;
extern Reloc00618 D_L00_001A9014 MACRO_ADDR;
extern int D_L00_001B1AFC MACRO_ADDR;
extern struct Groups00618 *D_L00_001B1B00 MACRO_ADDR;
extern char *D_L00_001B1F84 MACRO_ADDR;   /* clip volumes, 0x90 bytes each */
extern int D_L00_001B1F88 MACRO_ADDR;
extern char *D_L00_001B1F8C MACRO_ADDR;   /* cuboids */
extern int D_L00_001B1F90 MACRO_ADDR;
extern char *D_L00_001B1F94 MACRO_ADDR;   /* spheres */
extern int D_L00_001B1F98 MACRO_ADDR;
extern char *D_L00_001B1F9C MACRO_ADDR;   /* cylinders */
extern int D_L00_001B1FA0 MACRO_ADDR;
extern int D_L00_001B1FA4 MACRO_ADDR;     /* path count */
extern char *D_L00_001B1FA8 MACRO_ADDR;   /* path data */
typedef struct { Vec00618 head; char *data; int i14; char pad18[8]; } Rail00618;   /* 0x20 */
extern Rail00618 *D_L00_001B16C0 MACRO_ADDR;
extern int D_L00_001B16C4 MACRO_ADDR;
extern char *D_L00_001B20B0 MACRO_ADDR;
extern int D_L00_001B20B4 MACRO_ADDR;
extern int D_L00_001B20B8 MACRO_ADDR;
extern int D_L00_001B20BC MACRO_ADDR;

extern LoadCtx00618 D_L00_001BF140;
extern Boot00618 D_0014B540;
typedef struct { int stage, busy; int *archive0; int archive1; } ArchiveLoad;
extern ArchiveLoad D_001A7280 MACRO_ADDR;
extern char D_00189E20[];
extern char D_L00_001B8C80[];
extern char D_L00_001D1740[];
extern int D_001A7B90 MACRO_ADDR;
extern float D_001A790C MACRO_ADDR;
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
extern int D_L00_001A8F0C MACRO_ADDR;
extern int D_L00_001B20C0 MACRO_ADDR;
extern float D_L00_001B2500 MACRO_ADDR;
extern float D_L00_001B2408 MACRO_ADDR;
extern int D_L00_001B1EB4 MACRO_ADDR;
extern int D_L00_001B255C MACRO_ADDR;
extern char D_00100AE0[];
extern char D_L00_001C6F40[];
extern char D_L00_001C7040[];
extern char D_L00_001C6B40[];
extern char D_L00_002A0ED0[];
extern int D_L00_001B1CDC MACRO_ADDR;
extern char D_L00_001C5940[];
extern char D_L00_001C5B40[];
extern int D_L00_001B24D4 MACRO_ADDR;
typedef struct { char pad00[0x36]; unsigned short h36; char pad38[2]; unsigned short h3A; char pad3C; unsigned char b3D; char pad3E[2]; } Tfrag00618;   /* 0x40 */
extern char *D_L00_001B24D0 MACRO_ADDR;
typedef struct { char pad00[0x2C]; int count; } TextHdr00618;
extern TextHdr00618 D_L00_0027D848;
extern unsigned char D_001A7BB2[] MACRO_ADDR; /* option bytes; [2] is the language */
typedef struct { int offset; int pad4[3]; } Text00618;
extern Text00618 *D_L00_001B1B80 MACRO_ADDR;
extern int D_L00_001B2520 MACRO_ADDR;
extern Tie00618 *D_L00_001B2514 MACRO_ADDR;
extern Tie00618 *D_L00_001B2518 MACRO_ADDR;
extern Matrix00618 *D_L00_001B251C MACRO_ADDR;
extern int D_L00_001B2524 MACRO_ADDR;
extern int D_L00_001B2540 MACRO_ADDR;
extern int D_L00_001B2544 MACRO_ADDR;
extern int D_L00_001B2548 MACRO_ADDR;
extern int D_L00_001B2510 MACRO_ADDR;
extern TieClass00618 *D_L00_00226700[];
extern unsigned char D_L00_00226A00[];
extern Shrub00618 *D_L00_001B23F8 MACRO_ADDR;
extern int D_L00_001B23F4 MACRO_ADDR;
extern Matrix00618 *D_L00_001B2400 MACRO_ADDR;
extern unsigned char *D_L00_001B2404 MACRO_ADDR;
extern Shrub00618 *D_L00_001B23FC MACRO_ADDR;
extern int D_L00_001ACE90[];
extern ShrubClass00618 *D_L00_0021EA20[];
extern unsigned char D_L00_0021EBA0[];
typedef struct { float f0, f4, f8; int iC; float f10, f14, f18; int i1C; } Cam00618;
extern Cam00618 *D_L00_001B1844 MACRO_ADDR;
extern int D_L00_001B1848 MACRO_ADDR;
extern Slots00618 D_00188660;
extern int D_L00_001C5480[][3];
extern int D_L00_001C5540[][3];
extern Moby00618 *D_L00_001B1E9C[] MACRO_ADDR; /* moby array start (array: in-struct for alias analysis) */
extern Moby00618 *D_L00_001B18DC MACRO_ADDR;
extern Moby00618 *D_L00_001B1EA0 MACRO_ADDR;
extern Moby00618 *D_L00_001B1EA4 MACRO_ADDR;
extern char *D_L00_001B1EAC MACRO_ADDR;
extern short D_L00_001FB660[];
extern int D_001A79F0 MACRO_ADDR;
extern unsigned char D_0019B2E8[];
extern unsigned char D_0019B4A8[];
typedef struct { unsigned char pad[0x464]; unsigned char byUid[0]; } Progress00618;
extern Progress00618 D_L00_0021DDB0;
extern unsigned char D_L00_001B1CE0[] MACRO_ADDR;
extern int D_L00_001FA920[];
extern int D_L00_001B1EB8 MACRO_ADDR;
extern char *D_L00_001FDA80[];
extern char *D_L00_001B1880 MACRO_ADDR;
extern char *D_L00_001B1CD8 MACRO_ADDR;
extern int D_L00_001B1CD4 MACRO_ADDR;
extern char *D_L00_001B1F40 MACRO_ADDR;
extern int D_L00_001B1F10 MACRO_ADDR;
extern char D_L00_001FE140[];
extern int D_L00_001B1A40 MACRO_ADDR;
extern unsigned short *D_L00_001B19F0 MACRO_ADDR;
extern int D_L00_001B1A50 MACRO_ADDR;
extern short D_L00_001FDE78 NOT_SDA;
extern short D_L00_001FDEF8 NOT_SDA;
extern short D_L00_001B1FB0 MACRO_ADDR;
extern short D_L00_001B1FF0 MACRO_ADDR;
extern short D_L00_001B2030 MACRO_ADDR;
extern int D_L00_00220DA0[];
extern int D_L00_001B19C8 MACRO_ADDR;
extern int D_L00_001B1AEC MACRO_ADDR;
extern int D_L00_001AA0F8 MACRO_ADDR;
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
extern void func_L00_003603C0(unsigned char *);

char *func_L00_00300618(int reload)
{
    char *hdr = D_L00_001BF140.data;
    char *heap = D_L00_001BF140.heap;
    float *startPos;
    short *idx = D_L00_001FB660; /* moby index by file order, rebuilt at each use */
    int tmp; /* scratch int: section 0x44's data base, a group's offset and end flag in the group loop */
    char *p;

    if (!reload) {
        func_002B7C80(heap, D_0014B540.i52B8 + D_0014B540.i529C, D_0014B540.i52BC);
        D_001A7280.archive1 = (int)heap;
    }
    func_0011AEA0(0);
    func_0029D4D0((void *)D_001A7280.archive1, hdr);
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
    D_L00_001BF200.iC = 0;
    D_L00_001BF200.i10 = 0;
    D_L00_001BF200.i14 = 0;
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
        D_L00_001B1B18 = *(float *)(p + 0xC);
        D_L00_001B1B1C = 1.0f;
    }
    startPos = (float *)(p + 0x10);
    p += 0x20;
    D_00152C00.i40 = *(int *)p;
    D_00152C00.i44 = *(int *)(p + 4);
    D_00152C00.i48 = *(int *)(p + 8);
    D_L00_001C9340.count = 0;
    p += 0x10;
    if (*(int *)(p + 0xC)) {
        int i;

        D_L00_001C9340.count = *(int *)(p + 0xC);
        for (i = 0; i < D_L00_001C9340.count; i++) {
            float *e = (float *)((char *)&D_L00_001C9340 + (i << 4));

            e[8] = *(float *)p;
            e[9] = *(float *)(p + 4);
            e[10] = *(float *)(p + 8);
            e[16] = *(float *)(p + 0x10);
            e[17] = *(float *)(p + 0x14);
            e[18] = *(float *)(p + 0x18);
            p += 0x20;
        }
    } else {
        p += 0x20;
    }
    D_L00_001A8F0C = *(int *)p;
    func_00279FF0();
    D_L00_001B2500 = 983040.0f;
    D_L00_001B2408 = 500.0f;
    D_L00_001B255C = 0x3C0;
    D_L00_001B1EB4 = 0x3C0;
    D_L00_001B20C0 = 0x1F4000;
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
    if (((int *)hdr)[0x84 / 4]) {
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

    /* section 0x10: the help text of the current language (D_001A7BB2[2]) */
    if (((int *)hdr)[0x10 / 4]) {
        int lang = D_001A7BB2[2] * 4;
        char *s = hdr + *(int *)(hdr + lang + 0x10);
        int size;
        int i;

        D_L00_0027D848.count = *(int *)s;
        s += 4;
        size = *(int *)s;
        s += 4;
        D_L00_001B1B80 = (Text00618 *)heap;
        size += 3;
        size &= ~3;
        size -= 8;
        func_00282AB0(heap, s, size);
        for (i = 0; i < D_L00_0027D848.count; i++) {
            int delta = (int)D_L00_001B1B80 - 8;

            D_L00_001B1B80[i].offset += delta;
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
            float scale;

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
            scale = func_00282DF0(&m->row[0]);
            scale = func_L00_002EE050(scale, func_00282DF0(&m->row[1]));
            tie->bounds.f[3] = D_L00_00226700[tie->b1D]->sphere.f[3] * func_L00_002EE050(scale, func_00282DF0(&m->row[2]));
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
    if (((int *)hdr)[0x94 / 4]) {
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
        D_L00_001ACE90[1] = (int)D_L00_001B2404;
        D_L00_001B23FC = D_L00_001B23F8 + D_L00_001B23F4;
        for (i = 0; i < D_L00_001B23F4; i++) {
            int cls = D_L00_0021EBA0[*(int *)s];
            Shrub00618 *shrub = D_L00_001B23F8 + i;
            Matrix00618 *m = D_L00_001B2400 + i;
            float radius, a, b, scale;
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
            g = (g << 8) | 0x80000000;
            m->row[0].i[3] = (bl << 16) | g | r;
            shrub->h1C = *(unsigned short *)s;
            s += 0x10;
            func_00283098(shrub, D_L00_0021EA20[cls], m);
            scale = func_00282DF0(&m->row[0]);
            scale = func_L00_002EE050(scale, func_00282DF0(&m->row[1]));
            shrub->bounds.f[3] = D_L00_0021EA20[cls]->fC * func_L00_002EE050(scale, func_00282DF0(&m->row[2]));
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
            unsigned char *q = D_L00_001B2404 + i * 0x60;
            int r = 0;
            int g = 0;
            int b = 0;
            int n = 24;
            int j;

            for (j = 0; j < n; j++) {
                r += q[0];
                g += q[1];
                b += q[2];
                q += 4;
            }
            g /= n;
            b /= n;
            r /= n;
            *(int *)((char *)D_L00_001B2400 + i * 0x40 + 0x1C) = (b << 16) | (g << 8) | r;
        }
    }

    /* section 0x44: another relocated pointer table */
    {
        int *s = (int *)SECTION_00618(0x44);
        int n = *s++;
        int size = *s++;
        int *offs;

        s += 2;
        offs = s;
        D_L00_001A9014.p1C = (int)heap;
        heap += n << 2;
        heap = ALIGN64_00618(heap);
        s += n;
        tmp = (int)heap;
        heap += size;
        heap = ALIGN64_00618(heap);
        if (n) {
            int i;

            for (i = 0; i < n; i++) {
                if (offs[i] != -1) {
                    D_L00_001A9014.i20 = i + 1;
                    ((int *)D_L00_001A9014.p1C)[i] = tmp + offs[i];
                } else {
                    ((int *)D_L00_001A9014.p1C)[i] = 0;
                }
            }
        }
        if (size)
            func_00282B50((char *)tmp, (char *)(((int)s + 0xF) & ~0xF), size);
    }

    /* section 8: 32-byte records */
    if (((int *)hdr)[8 / 4]) {
        char *s = SECTION_00618(8);
        int n = *(int *)s;

        D_L00_001B1844 = (Cam00618 *)heap;
        s += 0x10;
        D_L00_001B1848 = n;
        heap += n << 5;
        if (n)
            func_00282A60(D_L00_001B1844, 0, n << 5);
        heap = ALIGN64_00618(heap);
        if (D_L00_001B1848 > 0) {
            Cam00618 *e = D_L00_001B1844;
            int left = D_L00_001B1848;

        copy_record:
            e->iC = *(int *)s;
            s += 4;
            e->f0 = ((float *)s)[0];
            e->f4 = ((float *)s)[1];
            e->f8 = ((float *)s)[2];
            s += 0xC;
            e->f10 = ((float *)s)[0];
            e->f14 = ((float *)s)[1];
            e->f18 = ((float *)s)[2];
            s += 0xC;
            e->i1C = *(int *)s;
            s += 4;
            e++;
            if (--left)
                goto copy_record;
        }
    }

    /* section 0xC: 0x90-byte records */
    if (((int *)hdr)[0xC / 4]) {
        char *s = SECTION_00618(0xC);
        int n = *(int *)s;

        s += 0x10;
        D_00188660.count = n;
        if (n) {
            int size = n * 0x90;
            int i;

            D_00188660.table = (Sound00618 *)heap;
            heap += size;
            heap = ALIGN64_00618(heap);
            func_00282A60(D_00188660.table, 0, size);
            for (i = 0; i < D_00188660.count; i++) {
                Sound00618 *e = D_00188660.table + i;

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
        char *p = SECTION_00618(0x4C);
        int levels = (int)D_0019B2E8;
        int n2;
        int count = 0;
        int n;
        char *next;
        int i;

        n = *(int *)p;
        p += 4;
        n2 = *(int *)p;
        p += 0xC;
        D_L00_001B1E9C[0] = (Moby00618 *)heap;
        func_00282A60(heap, 0, (n + n2) << 8);
        func_00282A60(D_L00_001C5480, 0, 0xC0);
        func_00282A60(D_L00_001C5540, 0, 0xC0);
        for (i = 0; i < n; i++) {
            int cls;
            int w2;
            int flags;
            int uid;
            int bolts;
            int bolts2;
            int xp;
            int xp2;
            int w9;
            int b1;
            int x1;
            char skip = 0;

            next = p + ((*(int *)p >> 2) << 2);
            p += 4;
            cls = *(int *)p;
            p += 4;
            w2 = *(int *)p;
            p += 4;
            flags = *(int *)p;
            p += 4;
            uid = *(int *)p;
            p += 4;
            bolts = *(int *)p;
            p += 4;
            bolts2 = *(int *)p;
            p += 4;
            xp = *(int *)p;
            p += 4;
            xp2 = *(int *)p;
            p += 4;
            w9 = *(int *)p;
            p += 4;
            b1 = bolts;
            x1 = xp;
            if (cls >= 0 && w9 > 0) {
                int k = cls + D_001A79F0 * 16;
                int lvl = (*(unsigned char *)(k + levels) >> (w2 * 2)) & 3;

                if (lvl == 0)
                    lvl = func_L00_002E3B38(cls);
                if (*(int *)p == 0x1F5 || *(int *)p == 0x200) {
                    skip = w9 < lvl;
                } else if (lvl < w9) {
                    D_L00_001C5480[cls][w2] += x1;
                    D_L00_001C5540[cls][w2] += b1;
                    skip = 1;
                }
            }
            if (!skip && flags) {
                if (D_L00_0021DDB0.byUid[uid]) {
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
                                int c3;
                                int w;

                                *cell = v;
                                c3 = *cell;
                                w = odd ? c3 & 0x8F : c3 & 0xF8;
                                *cell = w;
                            }
                            b1 = bolts2;
                            x1 = xp2;
                        } else {
                            skip = 1;
                        }
                    } else {
                        skip = !(flags & 1);
                    }
                } else if (flags & 8) {
                    if (reload) {
                        int odd = uid & 1;
                        unsigned char *cell = &SAVE_CELL_00618(uid);
                        int c = *cell;
                        int w = odd ? c & 0x8F : c & 0xF8;

                        *cell = w;
                    } else {
                        int odd = uid & 1;
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
                idx[i] = -1;
            } else {
                Moby00618 *m;
                int snap;
                float lift;
                int pv;
                int r;
                int g;
                int b;
                int upd;

                idx[i] = count;
                m = D_L00_001B1E9C[0] + count;
                func_0029F0C8(m, *(int *)p);
                p += 4;
                m->hB2 = uid;
                m->bB0 = cls;
                m->bB1 = w2 & 0xF;
                if (flags == 0)
                    m->bB1 |= 0x80;
                m->hB4 = b1;
                m->hB6 = x1;
                if (m->pClass)
                    m->f2C = ((MobyClass00618 *)m->pClass)->f24 * *(float *)p;
                p += 4;
                m->h32 = *(unsigned short *)p;
                p += 4;
                m->b30 = *(unsigned char *)p;
                p += 0xC;
                m->pos.f[0] = ((float *)p)[0];
                m->pos.f[1] = ((float *)p)[1];
                m->pos.f[2] = ((float *)p)[2];
                p += 0xC;
                m->rot[0] = ((float *)p)[0];
                m->rot[1] = ((float *)p)[1];
                m->rot[2] = ((float *)p)[2];
                p += 0xC;
                m->b21 = *(unsigned char *)p;
                p += 4;
                snap = *(int *)p;
                p += 4;
                lift = *(float *)p;
                p += 4;
                if (snap) {
                    float h = func_002A89A8(&m->pos, 0, 0.5f);

                    if (0.0f < h)
                        m->pos.f[2] = h + lift;
                }
                p += 4;
                pv = *(int *)p;
                m->h36 = 0x7F80;
                p += 4;
                m->i68 = pv;
                if (*(int *)p == 0)
                    m->h36 = 0;
                p += 4;
                if (m->pClass)
                    ((MobyClass00618 *)m->pClass)->h44 |= *(unsigned short *)p;
                m->h34 |= *(unsigned short *)p;
                p += 4;
                if (m->pClass)
                    func_002A0F48(m);
                r = *(int *)p;
                p += 4;
                g = *(int *)p;
                p += 4;
                b = *(int *)p;
                p += 4;
                upd = *(int *)p;
                p += 4;
                func_002A0468(m, (b << 16) + (g << 8) + r, 0, 0, 0);
                m->i38 = upd;
                m->b7E &= 0xFE;
                if (D_001A79F0 >= 0 && *(int *)p != -1)
                    func_L00_00309140(m, *(int *)p);
                count++;
            }
            p = next;
        }
        {
            Moby00618 *tail = D_L00_001B1E9C[0] + count;
            int total = (count + n2) << 8;

            D_L00_001B18DC = tail;
            func_0029F0C8(tail, 0);
            heap += total;
            tail->state = 0xFD;
            D_L00_001B1EA0 = D_L00_001B18DC + 1;
            D_L00_001B1EA0->state = 0xFF;
            D_L00_001B1EAC = heap;
            heap += n2 << 7;
            heap = ALIGN64_00618(heap);
            D_L00_001BF140.mark5C = heap;
            D_L00_001B1EA4 = (Moby00618 *)((char *)D_L00_001B1E9C[0] + total - 0x100);
        }
    }

    /* sections 0x60 / 0x5C: pointed-to blobs copied into the heap */
    if (((int *)hdr)[0x60 / 4]) {
        char *pv = SECTION_00618(0x60);
        Blob00618 *tbl = (Blob00618 *)SECTION_00618(0x5C);
        int i;
        Moby00618 *m;

        for (i = 0; i < D_L00_001B1848; i++) {
            int k = D_L00_001B1844[i].i1C;

            if (k < 0) {
                D_L00_001B1844[i].i1C = 0;
            } else {
                int size = tbl[k].size;
                char *src = pv + tbl[k].offset;

                D_L00_001B1844[i].i1C = (int)heap;
                func_00282B50(heap, src, size);
                tbl[k].offset = (int)heap;
                heap += size;
            }
        }
        for (i = 0; i < D_00188660.count; i++) {
            int k = D_00188660.table[i].i8;

            if (k < 0) {
                D_00188660.table[i].i8 = 0;
            } else {
                int size = tbl[k].size;
                char *src = pv + tbl[k].offset;

                D_00188660.table[i].i8 = (int)heap;
                func_00282B50(heap, src, size);
                tbl[k].offset = (int)heap;
                heap += size;
            }
        }
        for (m = D_L00_001B1E9C[0]; m != D_L00_001B1EA0; m++) {
            if (m->oClass == 0) {
                m->i68 = 0;
            } else {
                int k = m->i68;

                if (k < 0) {
                    m->i68 = 0;
                } else {
                    int size = tbl[k].size;
                    char *src = pv + tbl[k].offset;

                    m->i68 = (int)heap;
                    func_00282B50(heap, src, size);
                    tbl[k].offset = (int)heap;
                    heap += size;
                }
            }
        }
        heap = ALIGN64_00618(heap);
    }
    D_L00_001BF140.mark60 = heap;

    /* section 0x58: moby references through the blob directory */
    if (((int *)hdr)[0x58 / 4]) {
        int *q = (int *)SECTION_00618(0x58);
        Blob00618 *tbl = (Blob00618 *)SECTION_00618(0x5C);

        while (q[0] >= 0) {
            int x = tbl[q[0]].offset;
            int off = q[1];

            if (x >= D_L00_001BF140.i18) {
                int *r = (int *)(x + off);

                if (*r >= 0)
                    *r = idx[*r];
            }
            q += 2;
        }
    }

    /* section 0x64: pointer relocations through the blob directory */
    if (((int *)hdr)[0x64 / 4]) {
        int *q = (int *)SECTION_00618(0x64);
        Blob00618 *tbl = (Blob00618 *)SECTION_00618(0x5C);

        while (q[0] >= 0) {
            int x = tbl[q[0]].offset;
            int off = q[1];

            if (x >= D_L00_001BF140.i18) {
                int *r = (int *)(x + off);

                *r += x;
            }
            q += 2;
        }
    }

    /* section 0x50: moby groups */
    if (((int *)hdr)[0x50 / 4]) {
        char *q = SECTION_00618(0x50);
        char *base = heap;
        int *offs;
        int n;
        int size;
        int i;

        n = *(int *)q;
        q += 4;
        size = *(int *)q;
        offs = (int *)(q + 0xC);
        heap += size;
        q = (char *)offs + (n << 2);
        heap = ALIGN64_00618(heap);
        if (size)
            func_00282B50(base, q, size);
        func_00282A60(D_L00_001FA920, 0, 0x3C0);
        for (i = 0; i < n; i++, offs++) {
            tmp = *offs;
            if (tmp >= 0) {
                int g = (int)(base + tmp);
                unsigned short *src;
                short *dst;

                D_L00_001FA920[i] = g;
                src = (unsigned short *)g;
                dst = (short *)src;
                D_L00_001B1EB8 = i + 1;
                do {
                    int id = *src;
                    short t;

                    tmp = *(short *)src;
                    g = (id & 0x7FFF) << 1; /* the entry's slot in the moby index, in two steps */
                    g += (int)idx;
                    tmp &= 0x8000;
                    t = *(short *)g;
                    if (t >= 0)
                        *dst++ = t;
                    if (tmp) {
                        if (D_L00_001FA920[i] < (int)dst)
                            dst[-1] |= 0x8000;
                        else
                            D_L00_001FA920[i] = 0;
                        break;
                    }
                    src++;
                } while (!tmp);
            }
        }
    }

    /* section 0x54: blob pointers into a copied pool */
    if (((int *)hdr)[0x54 / 4]) {
        char *q = SECTION_00618(0x54);
        char *base = heap;
        Blob00618 *tbl;
        int size;
        int n;
        int i;

        size = *(int *)q;
        q += 4;
        n = *(int *)q;
        q += 0xC;
        heap += size;
        heap = ALIGN64_00618(heap);
        if (size)
            func_00282B50(base, q, size);
        q += size;
        tbl = (Blob00618 *)SECTION_00618(0x5C);
        for (i = 0; i < n; i++) {
            int w = *(int *)q;
            int hi = w >> 16;
            int x = tbl[w & 0xFFFF].offset;

            if (x >= D_L00_001BF140.i18)
                *(int *)(x + hi) = (int)(base + *(int *)(q + 4));
            q += 8;
        }
    }

    /* section 0x78: paths */
    if (((int *)hdr)[0x78 / 4]) {
        char *q = SECTION_00618(0x78);
        char *src;
        int size;
        int i;

        D_L00_001B1FA4 = *(int *)q;
        src = q + *(int *)(q + 4);
        size = *(int *)(q + 8);
        D_L00_001B1FA8 = heap;
        heap += size;
        q += 0x10;
        heap = ALIGN64_00618(heap);
        if (size)
            func_00282B50(D_L00_001B1FA8, src, size);
        for (i = 0; i < D_L00_001B1FA4; i++) {
            D_L00_001FDA80[i] = D_L00_001B1FA8 + *(int *)q;
            q += 4;
        }
    }

    /* section 0x7C: rails */
    if (((int *)hdr)[0x7C / 4]) {
        char *q = SECTION_00618(0x7C);
        char *src;
        char *copy;
        int n;
        int size;
        int i;

        n = *(int *)q;
        D_L00_001B16C4 = n;
        src = q + *(int *)(q + 4);
        size = *(int *)(q + 8);
        D_L00_001B16C0 = (Rail00618 *)heap;
        heap += n << 5;
        q += 0x10;
        heap = ALIGN64_00618(heap);
        if (n > 0) {
            Rail00618 *e = D_L00_001B16C0;

            i = n;
            do {
                qcopy(e, q);
                q += 0x10;
                e->i14 = *(int *)q;
                q += 0x10;
                e++;
            } while (--i != 0);
        }
        copy = heap;
        heap += size;
        heap = ALIGN64_00618(heap);
        if (size)
            func_00282B50(copy, src, size);
        for (i = 0; i < D_L00_001B16C4; i++) {
            D_L00_001B16C0[i].data = copy + *(int *)q;
            q += 4;
        }
    }

    /* section 0x74: clip volumes, 0x90-byte records from 0x80-byte sources */
    if (((int *)hdr)[0x74 / 4]) {
        char *q = SECTION_00618(0x74);
        int n = *(int *)q;
        int i;

        D_L00_001B1F84 = heap;
        D_L00_001B1F88 = n;
        q += 0x10;
        heap += n * 0x90;
        heap = ALIGN64_00618(heap);
        if (n)
            func_00282A60(D_L00_001B1F84, 0, n * 0x90);
        for (i = 0; i < D_L00_001B1F88; i++) {
            func_00282AB0(D_L00_001B1F84 + i * 0x90, q, 0x90);
            q += 0x80;
        }
    }

    /* sections 0x68, 0x6C, 0x70: cuboids, spheres and cylinders */
    if (((int *)hdr)[0x68 / 4]) {
        char *q = SECTION_00618(0x68);
        int n = *(int *)q;
        int i;

        D_L00_001B1F8C = heap;
        q += 0x10;
        D_L00_001B1F90 = n;
        heap += n << 7;
        heap = ALIGN64_00618(heap);
        if (n)
            func_00282A60(D_L00_001B1F8C, 0, n << 7);
        for (i = 0; i < D_L00_001B1F90; i++) {
            func_00282AB0(D_L00_001B1F8C + (i << 7), q, 0x80);
            q += 0x80;
        }
    }
    if (((int *)hdr)[0x6C / 4]) {
        char *q = SECTION_00618(0x6C);
        int n = *(int *)q;
        int i;

        D_L00_001B1F94 = heap;
        q += 0x10;
        D_L00_001B1F98 = n;
        heap += n << 7;
        heap = ALIGN64_00618(heap);
        if (n)
            func_00282A60(D_L00_001B1F94, 0, n << 7);
        for (i = 0; i < D_L00_001B1F98; i++) {
            func_00282AB0(D_L00_001B1F94 + (i << 7), q, 0x80);
            q += 0x80;
        }
    }
    if (((int *)hdr)[0x70 / 4]) {
        char *q = SECTION_00618(0x70);
        int n = *(int *)q;
        int i;

        D_L00_001B1F9C = heap;
        q += 0x10;
        D_L00_001B1FA0 = n;
        heap += n << 7;
        heap = ALIGN64_00618(heap);
        if (n)
            func_00282A60(D_L00_001B1F9C, 0, n << 7);
        for (i = 0; i < D_L00_001B1FA0; i++) {
            func_00282AB0(D_L00_001B1F9C + (i << 7), q, 0x80);
            q += 0x80;
        }
    }

    /* section 0x88 */
    if (((int *)hdr)[0x88 / 4]) {
        char *s = SECTION_00618(0x88);
        int size = *(int *)s;

        D_L00_001B1880 = heap;
        s += 0x10;
        size += 0x4000;
        heap += size;
        func_00282AB0(D_L00_001B1880, s, size);
        heap = ALIGN64_00618(heap);
    }

    /* section 0x80 */
    if (((int *)hdr)[0x80 / 4]) {
        char *s = SECTION_00618(0x80);
        int n = *(int *)s;

        D_L00_001B1CD8 = heap;
        s += 0x10;
        D_L00_001B1CD4 = n;
        heap = (char *)(((int)heap + (n << 4) + 0x83F) & 0xFFFFFFC0u);
        if (n)
            func_00282AB0(D_L00_001B1CD8, s, (n << 4) + 0x800);
        else
            func_00282AB0(D_L00_001B1CD8, s, 0x800);
    }

    /* section 0x8C */
    if (((int *)hdr)[0x8C / 4]) {
        char *s = SECTION_00618(0x8C);
        int n = *(int *)s;

        D_L00_001B1F40 = heap;
        s += 0x10;
        D_L00_001B1F10 = n;
        heap += n << 5;
        heap = ALIGN64_00618(heap);
        if (n)
            func_00282AB0(D_L00_001B1F40, s, n << 5);
    }
    D_L00_001B20B0 = heap;
    D_L00_001BF140.mark64 = heap;
    heap += 0x20000;
    D_L00_001B20B8 = -1;
    D_L00_001B20B4 = 0;
    D_L00_001B20BC = 0;
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
            m->i64 = (int)func_L00_003603C0;
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
        char *s;
        int size;
        int i;

        s = SECTION_00618(0x98);
        D_L00_001B1B00 = (Groups00618 *)heap;
        size = *(int *)s;
        heap += size;
        func_00282AB0(D_L00_001B1B00, s + 4, size);
        if (D_L00_001B1B00->p4)
            D_L00_001B1B00->p4 += (int)D_L00_001B1B00;
        else
            D_L00_001B1B00->p4 = 0;
        if (D_L00_001B1B00->p8)
            D_L00_001B1B00->p8 += (int)D_L00_001B1B00;
        else
            D_L00_001B1B00->p8 = 0;
        if (D_L00_001B1B00->pC)
            D_L00_001B1B00->pC += (int)D_L00_001B1B00;
        else
            D_L00_001B1B00->pC = 0;
        if (D_L00_001B1B00->p10)
            D_L00_001B1B00->p10 += (int)D_L00_001B1B00;
        else
            D_L00_001B1B00->p10 = 0;
        if (D_L00_001B1B00->p14)
            D_L00_001B1B00->p14 += (int)D_L00_001B1B00;
        else
            D_L00_001B1B00->p14 = 0;
        for (i = 0; i < D_L00_001B1B00->count; i++) {
            GroupEntry00618 *e;

            e = (GroupEntry00618 *)D_L00_001B1B00 + i;
            if (e[1].h0)
                e[1].iC += (int)D_L00_001B1B00->p4;
            else
                e[1].iC = 0;
            e = (GroupEntry00618 *)D_L00_001B1B00 + i;
            if (e[1].h2)
                e[1].i10 += (int)D_L00_001B1B00->p8;
            else
                e[1].i10 = 0;
            e = (GroupEntry00618 *)D_L00_001B1B00 + i;
            if (e[1].h4)
                e[1].i14 += (int)D_L00_001B1B00->pC;
            else
                e[1].i14 = 0;
            e = (GroupEntry00618 *)D_L00_001B1B00 + i;
            if (e[1].h6)
                e[1].i18 += (int)D_L00_001B1B00->p10;
            else
                e[1].i18 = 0;
            e = (GroupEntry00618 *)D_L00_001B1B00 + i;
            if (e[1].h8)
                e[1].i1C += (int)D_L00_001B1B00->p14;
            else
                e[1].i1C = 0;
        }
        {
            int bytes;

            D_L00_001B1AFC = (int)heap;
            bytes = D_L00_001B1B00->count * 0x1C;
            heap += bytes;
            func_00282A60((void *)D_L00_001B1AFC, 0, bytes);
        }
        {
            int j;

            for (j = 0; j < D_L00_001B1B00->count; j++)
                *(int *)((j << 2) + D_L00_001B1AFC) = D_L00_001B1AFC + (D_L00_001B1B00->count << 2) + j * 0x18;
        }
    }

    if (D_L00_001B1A40 && ((int *)hdr)[0x90 / 4]) {
        int *q = (int *)SECTION_00618(0x90);
        int *q0;
        int n1;
        int n2;
        int n3;
        int bad1 = 1;
        int bad2;
        unsigned short *table;

        q0 = q;
        n1 = q[0];
        n2 = q[1];
        n3 = q[2];
        q += 4;
        if (D_L00_001C9340.count) {
            q += n1 * 2;
            if (D_L00_001C9340.i18 == n1)
                bad1 = 0;
            D_L00_001C9340.i1C = bad1 == 0;
        } else if (D_L00_001B24D4 == n1) {
            int i;

            bad1 = 0;
            for (i = 0; i < n1; i++) {
                if (((Tfrag00618 *)D_L00_001B24D0)[i].b3D != q[1])
                    bad1 = 1;
                q += 2;
            }
        } else {
            q += n1 * 2;
        }
        bad2 = 1;
        if (D_L00_001B2518 - D_L00_001B2514 == n2) {
            int i;

            bad2 = 0;
            for (i = 0; i < n2; i++) {
                int id = (unsigned short)q[1];

                if (D_L00_001B2514[i].h10 != id)
                    bad2 = 1;
                q += 2;
            }
        } else {
            q += n2 * 2;
        }
        {
            Moby00618 *m;
            int i;

            table = D_L00_001B19F0;
            func_00282A60(table, -1, 0x10000);
            for (i = 0; i < n3; i++) {
                if ((unsigned)(q[i * 2 + 1] + 0x4000) < 0x8000)
                    table[q[i * 2 + 1] + 0x4000] = q[i * 2];
            }
            for (m = D_L00_001B1E9C[0]; m->state != 0xFF; m++) {
                if (m->h36 != 0x7F80) {
                    if ((unsigned)(m->hB2 + 0x4000) < 0x8000) {
                        short v = table[m->hB2 + 0x4000];

                        if (v < 0)
                            m->h36 = 0x7F80;
                        else
                            m->h36 = ((v >> 3) << 8) | (1 << (v & 7));
                    } else {
                        m->h36 = 0x7F80;
                    }
                }
            }
        }
        if (bad1) {
            if (D_L00_001B24D4 > 0) {
                unsigned short *e = (unsigned short *)(D_L00_001B24D0 + 0x3A);
                int left = D_L00_001B24D4;

                do {
                    *e = 0x7F80;
                    e = (unsigned short *)((char *)e + 0x40);
                } while (--left);
            }
        } else if (D_L00_001C9340.count) {
            int i;

            q = q0 + 4;
            for (i = 0; i < n1; i++) {
                int w = q[0];

                D_L00_001C9340.bits[i] = ((w >> 3) << 8) | (1 << (w & 7));
                q += 2;
            }
        } else {
            int i;

            q = q0 + 4;
            for (i = 0; i < n1; i++) {
                int w = q[0];

                ((Tfrag00618 *)D_L00_001B24D0)[i].h3A = ((w >> 3) << 8) | (1 << (w & 7));
                q += 2;
            }
        }
        if (bad2) {
            Tie00618 *t;
            int i;

            table = D_L00_001B19F0;
            q = &q0[n1 * 2 + 4];
            func_00282A60(table, 0xFFFEFFFE, 0x8000);
            for (i = 0; i < n2; i++) {
                if ((unsigned)q[i * 2 + 1] < 0x4000)
                    table[q[i * 2 + 1]] = q[i * 2];
            }
            for (t = D_L00_001B2514; t != D_L00_001B2518; t++) {
                int id = t->h10;

                if ((unsigned)id < 0x4000) {
                    short v = table[id];

                    if (v < 0)
                        t->h10 = 0x7F80;
                    else
                        t->h10 = ((v >> 3) << 8) | (1 << (v & 7));
                } else {
                    t->h10 = 0x7F80;
                }
            }
        } else {
            int i;

            q = &q0[n1 * 2 + 4];
            for (i = 0; i < n2; i++) {
                int w = q[0];

                D_L00_001B2514[i].h10 = ((w >> 3) << 8) | (1 << (w & 7));
                q += 2;
            }
        }
        D_L00_001B1A50 = 2;
    } else {
        Moby00618 *moby;
        Tie00618 *tie;

        for (moby = D_L00_001B1E9C[0]; moby != D_L00_001B1EA4; moby++)
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
        D_L00_001B1A50 = 0;
        D_L00_001C9340.i1C = 0;
    }
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
        char *hero = D_00189E20;

        *(long long *)((char *)m + 0x38) = *(long long *)(*(char **)(hero + 0x2290) + 0x38);
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
