#include "common.h"
#include "structs.h"

extern int r1_func_0011D960(void);

extern void r1_func_0011D9A8(void);

typedef struct {
    unsigned char pad0[0x838];
    int unk838;
    int unk83C;
    unsigned char pad840[0x18];
    void *cbData;
} MpegDec;

extern char r1_D_00153888[];

extern void func_0012C3B0(void *);

extern void r1_func_0012BC78(int, void *);

extern void r1_func_0012C468(void *, void *);

#define IPU_CTRL   ((volatile unsigned int *)0x10002010)

#define IPU_BP     ((volatile unsigned int *)0x10002020)

#define IPU_TOP    ((unsigned long *)0x10002030)

#define D3_CHCR    ((volatile unsigned int *)0x1000B400)

#define D3_QWC     ((volatile unsigned int *)0x1000B420)

#define D4_CHCR    ((volatile unsigned int *)0x1000B000)

#define D4_QWC     ((volatile unsigned int *)0x1000B020)

#define D_ENABLER  ((volatile unsigned int *)0x1000F520)

#define D_ENABLEW  ((volatile unsigned int *)0x1000F590)

extern int func_0012B1C0(void *);

/* func_0012C508 returns a short: its epilogue sign-extends $v0. */
extern short func_0012C508(int, int);

struct MpegDecoder;
extern void r1_func_0012C430(void *, char *, int);
extern void r1_func_00125880(struct MpegDecoder *d, int bx, int by, int mb_type, int motion_type,
                          int pmv[2][2][2], int mvfs[2][2], int *dmvector);
extern void r1_func_0012A0F8(void *);
extern char r1_D_001537E8[];
typedef struct {
    char pad0[0x128];
    int unk128;
    int unk12C;
    int unk130;
    int unk134;
    int unk138;
    int unk13C;
} Elem00125630;
typedef struct {
    int unk0;
    int pad4[3];
    int unk10;
} Ref00125630;
typedef struct {
    char pad0[0x11C];
    int unk11C;
    char pad120[0xC];
    int unk12C;
    char pad130[0x44];
    int unk174;
    char pad178[0x48];
    Ref00125630 *unk1C0;
    char pad1C4[0xC];
    Ref00125630 *unk1D0;
    char pad1D4[0xC];
    Ref00125630 *unk1E0;
    char pad1E4[0x3AC];
    Elem00125630 e[2];
    int unk810;
} Dec00125630;

/* rac1-decomp src/core/00125630.c: func_00129450 */
/* Motion-compensate one macroblock (or wait for the intra IDCT) and record its output slot. */
int func_00129450(void *arg0, int mbAddr, int arg2, int mbType, int motionType,
                  void *pmv, void *mvfs, void *dmv) {
    Dec00125630 *d = (Dec00125630 *)arg0;
    int intra;
    int x;
    int y;
    int bx;
    int by;
    Ref00125630 *ref;

    intra = mbType & 1;
    y = mbAddr / d->unk12C;
    x = mbAddr % d->unk12C;
    by = y * 16;
    bx = x * 16;
    if (intra) {
        while ((*(volatile unsigned int *)0x1000D400 >> 8) & 1)
            ;
        d->e[d->unk810].unk138 = 0;
    } else {
        if ((unsigned int)(motionType - 1) >= 3) {
            r1_func_0012C430(d, r1_D_001537E8, motionType);
            d->unk11C = 1;
            return 0;
        }
        r1_func_00125880((struct MpegDecoder *)d, bx, by, mbType, motionType,
                      pmv, mvfs, dmv);
        while ((*(volatile unsigned int *)0x1000D400 >> 8) & 1)
            ;
        r1_func_0012A0F8(d);
        d->e[d->unk810].unk138 = 1;
    }
    if (arg2 == 1 && (mbType & 2)) {
        d->e[d->unk810].unk134 = arg2;
    } else {
        d->e[d->unk810].unk134 = 0;
    }
    d->e[d->unk810].unk130 = intra;
    if (d->unk174 == 3) {
        d->e[d->unk810].unk128 = d->unk1C0->unk0 + (x * d->unk1C0->unk10 + y) * 0x180;
    } else {
        if (d->unk174 == 2) {
            ref = d->unk1E0;
        } else {
            ref = d->unk1D0;
        }
        d->e[d->unk810].unk128 = ref->unk0 + (x * ref->unk10 + y) * 0x180;
    }
    return 1;
}

/* libmpeg. func_001296A0 is rac1-decomp src/core/00125630.c func_00125880
   (_getAllRefs) and func_00129DA8 is Lombyte (GPL-3.0) src/assembly/sdk/library/
   _getRef0.c; both keep RAC2's position relative to RAC1 (RAC2 = RAC1 + 0x3E20)
   at the same sizes. Every field offset below was re-measured against RAC2's
   own accesses, not inherited:
     ref_images 0x1B8 (`lw $a1,0x1CC($s1)` = ref_images[5]),
     mc 0x590, cur 0x810 (`lw $v0,0x810($t8)`), work 0x81C (`lw $a0,0x81C($t8)`),
     n 0x12C (`sw $zero,0x6BC(...)`, mc + 0x12C),
     queue y[4] at 0x48 and c[4] at 0xB8 (`addiu $a0,$a0,0x48`, `$a0,0xB8`),
     frame base 0 (`lw $t1,0x0($fp)`) and width 0x10 (`lw $a1,0x10($fp)`).
   Fifth to eighth integer arguments arrive in $t0-$t3 (the SDK compiler's EE
   convention): motion_type, pmv, mvfs, dmvector here; dx, dy, fieldpred, avg
   read from 0xB0/0xB8/0xC0/0xC8($sp) in func_00129DA8.
   The error strings are at 0x13BA20/0x13BA40/0x13BA60 and the two MC routine
   tables at 0x137ED0/0x137EF0. */

typedef struct {
    u8 *base; /* 0x00 */
    u8 pad04[0xC];
    int width; /* 0x10 */
} MpegRefImageC;

typedef void (*MpegMcFuncC)(void);

typedef struct {
    u8 *addr;
    int x;
    int n0;
    int n1;
    int step;
    u8 *p0;
    u8 *p1;
} MpegMcFetchC; /* 0x1C */

typedef struct {
    u8 *buf; /* 0x00 */
    int pad04;
    u8 *yref[4]; /* 0x08 */
    u8 *cref[4]; /* 0x18 */
    MpegMcFuncC yfunc[4]; /* 0x28 */
    MpegMcFuncC cfunc[4]; /* 0x38 */
    MpegMcFetchC y[4]; /* 0x48 */
    MpegMcFetchC c[4]; /* 0xB8 */
    int pad128;
    int n; /* 0x12C */
    u8 pad130[0x10];
} MpegMcQueueC; /* 0x140 */

typedef struct {
    u8 pad000[0x120];
    int second_field; /* 0x120 */
    u8 pad124[0x150 - 0x124];
    int picture_coding_type; /* 0x150 */
    u8 pad154[0x174 - 0x154];
    int picture_structure; /* 0x174 */
    u8 pad178[0x1B8 - 0x178];
    MpegRefImageC *ref_images[12]; /* 0x1B8 */
    u8 pad1E8[0x590 - 0x1E8];
    MpegMcQueueC mc[2]; /* 0x590 */
    int cur; /* 0x810 */
    u8 pad814[0x81C - 0x814];
    u8 *work; /* 0x81C */
} MpegDecoderC;

extern void func_00129DA8(MpegDecoderC *d, MpegRefImageC *ref, int sfield, int dfield,
                          int yofs, int h, int bx, int by, int dx, int dy,
                          int fieldpred, int avg);

extern void func_0012B3E0(MpegDecoderC *d, int DMV[][2], int *dmvector, int mvx,
                          int mvy);

/* _errMessage takes one argument, this call site hands it three; the alias is
   the only spelling that keeps the extra two live in $a1/$a2. */
extern void func_00130250_msg(MpegDecoderC *d, char *fmt, int code) __asm__("func_00130250");

extern char D_0013BA20[];

extern char D_0013BA40[];

extern char D_0013BA60[];

extern MpegMcFuncC D_00137ED0[];

extern MpegMcFuncC D_00137EF0[];

void func_001296A0(MpegDecoderC *d, int bx, int by, int mb_type, int motion_type,
                   int pmv[2][2][2], int mvfs[2][2], int *dmvector) {
    int dmv[2][2];
    MpegRefImageC *refs[2][2];
    int one = 1;
    int avg;
    int currentfield;
    int same = one;

    avg = 0;

    d->mc[d->cur].n = 0;

    if ((mb_type & 8) || d->picture_coding_type == 2) {
        if (d->picture_structure == 3) {
            if (motion_type == 2 || !(mb_type & 8)) {
                func_00129DA8(d, d->ref_images[0], 0, 0, 0, 16, bx, by, pmv[0][0][0],
                              pmv[0][0][1], 0, 0);
            } else if (motion_type == same) {
                func_00129DA8(d, d->ref_images[0], mvfs[0][0], 0, 0, 8, bx, by,
                              pmv[0][0][0], pmv[0][0][1] >> 1, same, 0);
                func_00129DA8(d, d->ref_images[0], mvfs[1][0], 1, 0, 8, bx, by,
                              pmv[1][0][0], pmv[1][0][1] >> 1, same, 0);
            } else if (motion_type == 3) {
                func_0012B3E0(d, dmv, dmvector, pmv[0][0][0], pmv[0][0][1] >> 1);
                func_00129DA8(d, d->ref_images[0], 0, 0, 0, 8, bx, by, pmv[0][0][0],
                              pmv[0][0][1] >> 1, same, 0);
                func_00129DA8(d, d->ref_images[0], 1, 0, 0, 8, bx, by, dmv[0][0],
                              dmv[0][1], same, one);
                func_00129DA8(d, d->ref_images[0], 1, 1, 0, 8, bx, by, pmv[0][0][0],
                              pmv[0][0][1] >> 1, same, 0);
                func_00129DA8(d, d->ref_images[0], 0, 1, 0, 8, bx, by, dmv[1][0],
                              dmv[1][1], same, one);
            } else {
                func_00130250_msg(d, D_0013BA20, motion_type);
            }
        } else {
            currentfield = d->picture_structure == 2;
            /* Keep the retail stack order: two field choices per reference set. */
            refs[0][0] = d->ref_images[4];
            refs[0][1] = d->ref_images[8];
            refs[1][0] = d->ref_images[5];
            refs[1][1] = d->ref_images[9];
            one = 2;
            same = 0;
            if (d->picture_coding_type == one && d->second_field) {
                same = currentfield != mvfs[0][0];
            }
            if (motion_type == 1 || !(mb_type & 8)) {
                func_00129DA8(d, refs[same][mvfs[0][0]], 0, 0, 0, 16, bx, by,
                              pmv[0][0][0], pmv[0][0][1], 0, 0);
            } else if (motion_type == 2) {
                func_00129DA8(d, refs[same][mvfs[0][0]], 0, 0, 0, 8, bx, by,
                              pmv[0][0][0], pmv[0][0][1], 0, 0);
                same = d->picture_coding_type == motion_type && d->second_field &&
                       currentfield != mvfs[1][0];
                func_00129DA8(d, refs[same][mvfs[1][0]], 0, 0, 8, 8, bx, by,
                              pmv[1][0][0], pmv[1][0][1], 0, 0);
            } else if (motion_type == 3) {
                same = d->second_field ? motion_type - 2 : 0;
                func_0012B3E0(d, dmv, dmvector, pmv[0][0][0], pmv[0][0][1]);
                func_00129DA8(d, refs[0][currentfield], 0, 0, 0, 16, bx, by,
                              pmv[0][0][0], pmv[0][0][1], 0, 0);
                func_00129DA8(d, refs[same][!currentfield], 0, 0, 0, 16, bx, by,
                              dmv[0][0], dmv[0][1], 0, 1);
            } else {
                func_00130250_msg(d, D_0013BA40, motion_type);
            }
        }
        avg = 1;
    }

    if (mb_type & 4) {
        if (d->picture_structure == 3) {
            same = 1;
            if (motion_type == 2) {
                func_00129DA8(d, d->ref_images[1], 0, 0, 0, 16, bx, by, pmv[0][1][0],
                              pmv[0][1][1], 0, avg);
            } else {
                func_00129DA8(d, d->ref_images[1], mvfs[0][1], 0, 0, 8, bx, by,
                              pmv[0][1][0], pmv[0][1][1] >> 1, same, avg);
                func_00129DA8(d, d->ref_images[1], mvfs[1][1], 1, 0, 8, bx, by,
                              pmv[1][1][0], pmv[1][1][1] >> 1, same, avg);
            }
        } else if (motion_type == 1) {
            func_00129DA8(d, mvfs[0][1] ? d->ref_images[9] : d->ref_images[5], 0, 0, 0,
                          16, bx, by, pmv[0][1][0], pmv[0][1][1], 0, avg);
        } else if (motion_type == 2) {
            func_00129DA8(d, mvfs[0][1] ? d->ref_images[9] : d->ref_images[5], 0, 0, 0,
                          8, bx, by, pmv[0][1][0], pmv[0][1][1], 0, avg);
            func_00129DA8(d, mvfs[1][1] ? d->ref_images[9] : d->ref_images[5], 0, 0, 8,
                          8, bx, by, pmv[1][1][0], pmv[1][1][1], 0, avg);
        } else {
            func_00130250_msg(d, D_0013BA60, motion_type);
        }
    }
}

void func_00129DA8(MpegDecoderC *d, MpegRefImageC *ref, int sfield, int dfield,
                   int yofs, int h, int bx, int by, int dx, int dy, int fieldpred,
                   int avg) {
    MpegMcFetchC *ye;
    MpegMcFetchC *ce;
    int n;
    u8 *buf;
    u8 *cbuf;
    int x, y, xm, ym, xr;
    int cxm, cym, cxr;
    int cdx, cdy;
    int cyofs;
    int xh, yh;
    int k;
    int ch;
    u8 *work;
    int yidx;
    int mb;
    u8 *base;

    work = d->work;
    x = (dx >> 1) + bx;
    n = d->mc[d->cur].n;
    ye = &d->mc[d->cur].y[n];
    ce = &d->mc[d->cur].c[n];
    if (fieldpred) {
        y = ((dy >> 1) * 2 + yofs) + (by + sfield);
    } else {
        y = ((dy >> 1) + yofs) + (by + sfield);
    }
    xm = x >> 4;
    ym = y >> 4;
    mb = xm * ref->width + ym;
    xr = x - xm * 16;
    y = y - ym * 16;
    ye->x = xr;
    ye->addr = work + (dfield + yofs) * 32;
    yh = dy & 1;
    xh = dx & 1;
    if (yh) {
        if (y + (h << fieldpred) > 15) {
            k = (16 >> fieldpred) - (y >> fieldpred) - 1;
            ye->n0 = k;
            ye->n1 = h - k;
        } else {
            ye->n0 = h;
            ye->n1 = 0;
        }
    } else {
        if (y + (h << fieldpred) > 16) {
            k = (16 >> fieldpred) - (y >> fieldpred);
            ye->n0 = k;
            ye->n1 = h - k;
        } else {
            ye->n0 = h;
            ye->n1 = 0;
        }
    }
    buf = d->mc[d->cur].buf + n * 0x600;
    ye->p0 = buf + y * 16;
    ye->p1 = buf + (y * 16 + 0x300);
    ye->step = 16 << fieldpred;
    yidx = (avg << 2) | xh << 1 | yh;
    avg <<= 2;

    cdx = dx / 2;
    cdy = dy / 2;
    ch = h >> 1;
    cyofs = yofs >> 1;
    x = (cdx >> 1) + (bx >> 1);
    if (fieldpred) {
        y = ((cdy >> 1) * 2 + cyofs) + ((by >> 1) + sfield);
    } else {
        y = ((cdy >> 1) + cyofs) + ((by >> 1) + sfield);
    }
    xh = cdx & 1;
    cxm = x >> 3;
    cym = y >> 3;
    cxr = x - cxm * 8;
    y = y - cym * 8;
    yh = cdy & 1;
    ce->x = cxr;
    ce->addr = work + ((dfield + cyofs) * 16 + 0x200);
    if (yh) {
        if (y + (ch << fieldpred) > 7) {
            k = (8 >> fieldpred) - (y >> fieldpred) - 1;
            ce->n0 = k;
            ce->n1 = ch - k;
        } else {
            ce->n0 = ch;
            ce->n1 = 0;
        }
    } else {
        if (y + (ch << fieldpred) > 8) {
            k = (8 >> fieldpred) - (y >> fieldpred);
            ce->n0 = k;
            ce->n1 = ch - k;
        } else {
            ce->n0 = ch;
            ce->n1 = 0;
        }
    }
    cbuf = ((cxm - xm) * 2 + (cym - ym)) * 0x180 + buf;
    base = ref->base;
    ce->p0 = cbuf + (y * 8 + 0x100);
    ce->p1 = cbuf + (y * 8 + 0x400);
    ce->step = 8 << fieldpred;
    d->mc[d->cur].yfunc[n] = D_00137ED0[yidx];
    d->mc[d->cur].yref[n] = base + mb * 0x180;
    d->mc[d->cur].cref[n] = base + (mb + ref->width) * 0x180;
    d->mc[d->cur].cfunc[n] = D_00137EF0[avg | xh << 1 | yh];
    d->mc[d->cur].n++;
}

extern void r1_func_0012C468(void *, void *);
extern void r1_func_00127318(int, int);
extern void r1_func_001272B8(int, int, int);
extern char r1_D_00153870[];
typedef struct {
    int unk0;
    int unk4;
    char pad8[0x20];
    void (*fa[4])(void *);
    void (*fb[4])(void *);
    char a[4][0x1C];
    char b[4][0x1C];
    int unk128;
    int count;
    int unk130;
    int pad134;
    int unk138;
    int unk13C;
} Elem001263A8;
typedef struct {
    char pad0[0x590];
    Elem001263A8 e[2];
    char pad810[0xC];
    int unk81C;
} Dec001263A8;


/* rac1-decomp src/core/00125630.c: func_0012A1C8 */
/* Run a channel's per-block callbacks, then hand its buffer to the output routine. */
void func_0012A1C8(void *arg0, int idx) {
    Dec001263A8 *p = (Dec001263A8 *)arg0;
    int i;

    if (p->e[idx].unk138 != 0) {
        for (i = 0; i < p->e[idx].count; i++) {
            p->e[idx].fa[i](p->e[idx].a[i]);
            p->e[idx].fb[i](p->e[idx].b[i]);
        }
    }
    if (p->e[idx].unk130 != 0 && p->e[idx].unk13C != 0) {
        r1_func_0012C468(p, r1_D_00153870);
    }
    if (p->e[idx].unk130 != 0) {
        r1_func_00127318(p->e[idx].unk128, p->e[idx].unk4);
    } else if (p->e[idx].unk13C != 0) {
        r1_func_00127318(p->e[idx].unk128, p->unk81C);
    } else {
        r1_func_001272B8(p->e[idx].unk128, p->unk81C, p->e[idx].unk4);
    }
}

ASM_FUNC("asm/core", func_0012A3E8);

ASM_FUNC("asm/core", func_0012A460);

ASM_FUNC("asm/core", func_0012A4F8);

ASM_FUNC("asm/core", func_0012A5B0);

ASM_FUNC("asm/core", func_0012A680);

ASM_FUNC("asm/core", func_0012A730);

ASM_FUNC("asm/core", func_0012A7E8);

ASM_FUNC("asm/core", func_0012A8E0);

ASM_FUNC("asm/core", func_0012A9E0);

ASM_FUNC("asm/core", func_0012AA80);

ASM_FUNC("asm/core", func_0012AB30);

ASM_FUNC("asm/core", func_0012AC10);

ASM_FUNC("asm/core", func_0012ACF8);

ASM_FUNC("asm/core", func_0012ADD0);

ASM_FUNC("asm/core", func_0012AEA0);

ASM_FUNC("asm/core", func_0012AFC0);

ASM_FUNC("asm/core", func_0012B0D8);

/* rac1-decomp src/core/00125630.c: func_00127378 */
void func_0012B198(int arg0) {
    unsigned int *p = (unsigned int *)0x10002010;
    *p = (*p & 0xFF7FFFFF) | (arg0 << 23);
}

/* rac1-decomp src/core/00125630.c: func_001273A0 */
/* _waitBdecOut (libmpeg). Adapted from Lombyte (GPL-3.0) for PAL. */
int func_0012B1C0(void *arg0) {
    MpegDec *d = arg0;
    int cb1[8];
    int cb2[8];
    int ret;
    int intr;
    unsigned int bp;
    long top;
    unsigned int rest;

    ret = 1;
    func_0012C3B0(d);
    if (*D4_QWC != 0 && !(*IPU_CTRL & 0x4000)) {
        do {
            if (*D3_QWC == 0 && !(*D3_CHCR & 0x100)) {
                cb1[0] = 1;
                r1_func_0012BC78((int)d->cbData, cb1);
            }
        } while (*D4_QWC != 0 && !(*IPU_CTRL & 0x4000));
    }
    bp = *IPU_BP;
    top = *IPU_TOP;
    d->unk838 = top;
    if (top < 0) {
        rest = bp & 0x1F;
        d->unk83C = rest ? 32 - rest : 0;
    } else {
        d->unk83C = 32;
    }
    if (*IPU_CTRL & 0x4000) {
        r1_func_0012C468(d, r1_D_00153888);
        cb2[0] = 2;
        r1_func_0012BC78((int)d->cbData, cb2);
        *(unsigned int *)0x10002010 = 0x40000000;
        cb2[0] = 3;
        r1_func_0012BC78((int)d->cbData, cb2);
        intr = r1_func_0011D960();
        *D_ENABLEW = *D_ENABLER | 0x10000;
        *D4_CHCR = 0;
        *D_ENABLEW = *D_ENABLER & ~0x10000;
        if (intr) {
            r1_func_0011D9A8();
        }
        ret = 0;
        *D4_QWC = 0;
    }
    return ret;
}

/* rac1-decomp src/core/00125630.c: func_001275A0 */
/* Returns its callee's value: retail keeps the frame and calls, and
   2.9-ee turns a void one-call function into a bare tail jump (8 bytes
   against 28). */
short func_0012B3C0(int arg0) {
    return func_0012C508(arg0, 3);
}
