#include "common.h"
#include "structs.h"

extern void func_00130288(void *, void *);

extern void func_00130240(void *);

extern void func_0012FB70(void *);
extern unsigned int func_0012FB80(void *, void *, unsigned int, unsigned int);
extern void func_001306D0(unsigned int *, unsigned int *, unsigned int *, unsigned int *,
                          unsigned int *, unsigned int *, unsigned int *, unsigned int *,
                          unsigned int *, int, int, int, int, int);

/* rac1-decomp src/core/0012AC80.c: func_0012C468 */
void func_00130288(void *arg0, void *arg1) {
    char *a = (char *)arg0;
    void *t = *(void **)(a + 0x858);
    /* the arg0 null test is retail's, after it has already dereferenced
       arg0 -- one of the "dead-looking guards" that must be written out */
    if (t != 0 && arg0 != 0 && *(int *)(a + 0xC) != 0) {
        int buf[4];
        buf[0] = 0;
        buf[1] = (int)arg1;
        func_0012FA98(t, buf);
    } else {
        func_00130240(arg1);
    }
}

/* rac1-decomp src/core/0012AC80.c: func_0012C4C0 */
/* Store the two sizes and their 16-pixel macroblock counts. (An old note
   here recorded 4/32 with the 0x4/0x8 stores swapped; the function is
   exact under both compilers now.) */
int func_001302E0(void *arg0, int arg1, int arg2) {
    char *p = (char *)arg0;
    *(int *)(p + 0x4) = arg1;
    *(int *)(p + 0x8) = arg2;
    *(int *)(p + 0xC) = arg1 >> 4;
    *(int *)(p + 0x10) = arg2 >> 4;
    return 1;
}

extern void r1_func_0012C468();

extern void r1_func_0012C990();

extern char r1_D_00153BE8[];

extern void r1_func_0012C608(void *);

extern void r1_func_0012C990(void *, int, int);

extern int r1_func_00128A58(void *, int);

extern void r1_func_00128E68(void *);

extern void r1_func_00128560(void *, unsigned int);

extern char r1_D_001330C0[];

extern void r1_func_0012C468(void *, void *);

extern void r1_func_0012C468(void *, void *);

extern void r1_func_00128590(void *);

extern char r1_D_00133100[];

/* rac1-decomp src/core/0012AC80.c: func_0012C4E0 */
/*
 * _sequenceHeader (libmpeg.a:init.o): ISO/IEC 13818-2 6.2.2.1
 * sequence_header(), hardware-VLC variant matching mpeg2decode's
 * gethdr.c almost line for line but reading combined bitfields in one
 * Get_Bits (r1_func_00128A58) call each: a 32-bit fetch for
 * horizontal_size/vertical_size/aspect_ratio_information/frame_rate_code
 * (only the two sizes are kept, at +0x124/+0x128; a vertical_size
 * reading >= 0xAF1 is reported through r1_func_0012C468) and a 30-bit fetch
 * for bit_rate_value/marker_bit/vbv_buffer_size/constrained_parameters_
 * flag (bit_rate_value kept at +0x134, vbv_buffer_size at +0x138).
 * load_intra/non_intra_quantizer_matrix (+0x840/+0x844) gate the IPU
 * matrix load (r1_func_00128590/r1_func_00128560) or, when clear, _setDefaultQM
 * (r1_func_0012C990) with the reference decoder's default table. Ends with
 * extensionAndUserData (r1_func_00128E68) and a tail call into _initSeq
 * (r1_func_0012C608) with the object read back from +0x858.
 */
void func_00130300(void *arg0) {
    char *s = (char *)arg0;
    unsigned int v;
    int mid;
    unsigned int flag;

    *(unsigned int *)(s + 0xD4) = 0;

    v = r1_func_00128A58(s, 0x20);
    *(unsigned int *)(s + 0x124) = v >> 20;
    mid = (v >> 8) & 0xFFF;
    *(unsigned int *)(s + 0x128) = mid;
    if (mid >= 0xAF1) {
        r1_func_0012C468(s, r1_D_00153BE8);
    }

    v = r1_func_00128A58(s, 0x1E);
    *(unsigned int *)(s + 0x134) = v >> 12;
    *(unsigned int *)(s + 0x138) = (v >> 1) & 0x3FF;

    flag = r1_func_00128A58(s, 1);
    *(unsigned int *)(s + 0x840) = flag;
    if (flag != 0) {
        r1_func_00128590(s);
        r1_func_00128560(s, 0x50000000);
        r1_func_00128590(s);
    } else {
        r1_func_0012C990(s, 0x50000000, (int)r1_D_001330C0);
    }

    flag = r1_func_00128A58(s, 1);
    *(unsigned int *)(s + 0x844) = flag;
    if (flag != 0) {
        r1_func_00128590(s);
        r1_func_00128560(s, 0x58000000);
        r1_func_00128590(s);
    } else {
        r1_func_0012C990(s, 0x58000000, (int)r1_D_00133100);
    }

    r1_func_00128E68(s);
    r1_func_0012C608(*(void **)(s + 0x858));
}

/* rac1-decomp src/core/0012AC80.c: mpeg_init_seq (func_0012C608) */
void func_00130428(void *arg0) {
    int *a = (int *)arg0;
    char *s = *(char **)((char *)arg0 + 0x40);
    int f = *(int *)(s + 0x848);
    int h, mbw, mbh;
    unsigned int n, t;
    unsigned int *q0, *q1, *q2, *q3, *q4, *q5, *q6, *q7, *q8;

    if (f == 0) {
        *(int *)(s + 0x174) = 3;
        *(int *)(s + 0x13C) = 1;
        *(int *)(s + 0x140) = 1;
        *(int *)(s + 0x188) = 1;
        *(int *)(s + 0x17C) = 1;
        *(int *)(s + 0x144) = 5;
    }
    *(int *)(s + 0x12C) = (*(int *)(s + 0x124) + 0xF) >> 4;
    if (f != 0 && *(int *)(s + 0x13C) == 0)
        h = ((*(int *)(s + 0x128) + 0x1F) >> 5) << 1;
    else
        h = (*(int *)(s + 0x128) + 0xF) >> 4;
    *(int *)(s + 0x130) = h;
    mbh = h << 4;
    mbw = *(int *)(s + 0x12C) << 4;
    {
    unsigned int *p;
    if (mbw != a[0]) {
        p = (unsigned int *)(s + 0x528);
    } else {
        if (mbh == a[1])
            return;
        p = (unsigned int *)(s + 0x528);
    }
    a[0] = mbw;
    a[1] = mbh;
    if ((mbw & 0xF) && (mbw & 0xE))
        p = q8;
    q8 = p;
    t = mbh * 0x180;
    q0 = (unsigned int *)(s + 0x1E8);
    q1 = (unsigned int *)(s + 0x250);
    q2 = (unsigned int *)(s + 0x2B8);
    q3 = (unsigned int *)(s + 0x320);
    q4 = (unsigned int *)(s + 0x388);
    q5 = (unsigned int *)(s + 0x3F0);
    q6 = (unsigned int *)(s + 0x458);
    q7 = (unsigned int *)(s + 0x4C0);
    n = (mbw * t) >> 8;
    func_0012FB70(s + 0x108);
    *(unsigned int *)(s + 0xFC) = func_0012FB80(s, s + 0x108, n, 0x40);
    *(unsigned int *)(s + 0x100) = func_0012FB80(s, s + 0x108, n, 0x40);
    *(unsigned int *)(s + 0x104) = func_0012FB80(s, s + 0x108, n, 0x40);
    func_001306D0(q0, q1, q2,
                  q3, q4, q5,
                  q6, q7, q8,
                  *(int *)(s + 0xFC), *(int *)(s + 0x100), *(int *)(s + 0x104), mbw, mbh);
    func_001302E0(q0, mbw, mbh);
    func_001302E0(q1, mbw, mbh);
    func_001302E0(q2, mbw, mbh);
    func_001302E0(q3, mbw, mbh >> 1);
    func_001302E0(q4, mbw, mbh >> 1);
    func_001302E0(q5, mbw, mbh >> 1);
    func_001302E0(q6, mbw, mbh >> 1);
    func_001302E0(q7, mbw, mbh >> 1);
    func_001302E0(q8, mbw, mbh >> 1);
    }
}



/* rac1-decomp src/core/0012AC80.c: func_001306D0 */
void func_001306D0(unsigned int *o0, unsigned int *o1, unsigned int *o2, unsigned int *o3,
                   unsigned int *o4, unsigned int *o5, unsigned int *o6, unsigned int *o7,
                   unsigned int *o8, int a, int b, int c, int w, int h) {
    unsigned int x = (a & 0xFFFFFFF) | 0x20000000;
    unsigned int y = (b & 0xFFFFFFF) | 0x20000000;
    unsigned int z = (c & 0xFFFFFFF) | 0x20000000;
    int q = (w * h) / 512;
    int s6, s7, s8;
    s6 = q * 384; s6 += a;
    s7 = q * 384; s7 += b;
    s8 = q * 384; s8 += c;
    *o0 = x; *o1 = y; *o2 = z; *o3 = x; *o4 = y; *o5 = z;
    *o6 = (s6 & 0xFFFFFFF) | 0x20000000;
    *o7 = (s7 & 0xFFFFFFF) | 0x20000000;
    *o8 = (s8 & 0xFFFFFFF) | 0x20000000;
}

extern int r1_func_0011D960(void);
extern void r1_func_0011D9A8(void);
extern void r1_func_00128590(void *);
extern void r1_func_00128560(void *, unsigned int);
extern void func_001307B0(void *, int, int);

/* rac1-decomp src/core/0012AC80.c: func_001307B0 */
/* _setDefaultQM: tell the callback (type 2) that the default quantiser
   matrix load starts, then with the IPU idle and reset, DMA the matrix
   at addr to IPU_TO (tag 4 qwords, chcr 0x101) with interrupts held
   off, send command cmd and wait, and report type 3. Adapted from
   Lombyte's project (GPL-3.0) for PAL. */
void func_001307B0(void *arg, int cmd, int addr) {
    char *mp = arg;
    int cb[8];
    int intr;

    cb[0] = 2;
    r1_func_0012BC78(*(void **)(mp + 0x858), cb);
    r1_func_00128590(mp);
    *(volatile int *)0x10002000 = 0;
    r1_func_00128590(mp);
    intr = r1_func_0011D960();
    *(volatile int *)0x1000B410 = addr & 0x0FFFFFFF;
    *(volatile int *)0x1000B420 = 4;
    *(volatile int *)0x1000B400 = 0x101;
    if (intr != 0) {
        r1_func_0011D9A8();
    }
    r1_func_00128560(mp, cmd);
    r1_func_00128590(mp);
    cb[0] = 3;
    r1_func_0012BC78(*(void **)(mp + 0x858), cb);
}
