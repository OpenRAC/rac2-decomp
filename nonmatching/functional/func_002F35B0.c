/* functional: high. Hand-written retail (s registers kept in their upper halves, register helpers 0x2F3CF8 DMA wait, 0x2F3D20 best fit, 0x2F3E40 smallest size) written out in C on the same scratchpad layout, with the same DMA register stores in the same order; the 4-lane MMI best-fit search is done lane by lane, which picks the same entry (sizes and the gap are 32-bit signed, ties go to the later entry, as pminw/pmaxw and the lane compares do). Not reproduced: the misaligned read retail would make at -1 when no size fits the gap (best fit is only called with gap >= the smallest size, so one always fits). */

/* GS memory slot allocator (rac2 NTSC-U, 0x2F35B0). The slots are a doubly linked list of 64-bit nodes in the
   scratchpad at 0x70002000 (offsets kept in D_001B21E0 head, D_001B21E4 tail, D_001B21E8 end): low halfwords
   start and size, high word record index (bits 0-11), prev (12-21) and next (22-31) node offset / 8, 0x3FF none.
   List A (D_001B21CC bytes of 4-byte entries at D_00218480) holds the records in use, list B (D_001B21D0
   bytes of halfword record indices at D_00219480, bit 15 = drop) the records that want a slot; records are
   32 bytes at D_001B21B4 (+20 slot start, +22 size, +31 0xFF = no slot). Nodes of records not in list A are freed
   (array compacted), then list B's records are placed best fit into the gaps between slots, then appended in
   0x10000 units at the end; the node array goes back to D_0021AC80 by DMA. */

extern char *D_001B21B4;
extern int D_001B21CC;
extern int D_001B21D0;
extern int D_001B21E0;
extern int D_001B21E4;
extern int D_001B21E8;
extern char D_00218480[];
extern char D_00219480[];
extern char D_0021AC80[];

#define SPR_002F35B0 0x70000000u
#define NODE_002F35B0 (SPR_002F35B0 + 0x2000u)
#define S8_002F35B0(a) (*(signed char *)(unsigned long)(unsigned int)(a))
#define U8_002F35B0(a) (*(unsigned char *)(unsigned long)(unsigned int)(a))
#define U16_002F35B0(a) (*(unsigned short *)(unsigned long)(unsigned int)(a))
#define U32_002F35B0(a) (*(unsigned int *)(unsigned long)(unsigned int)(a))
#define U64_002F35B0(a) (*(unsigned long *)(unsigned long)(unsigned int)(a))
#define D8_CHCR_002F35B0 (*(volatile unsigned int *)0x1000D000)
#define D8_MADR_002F35B0 (*(volatile unsigned int *)0x1000D010)
#define D8_QWC_002F35B0 (*(volatile unsigned int *)0x1000D020)
#define D8_SADR_002F35B0 (*(volatile unsigned int *)0x1000D080)
#define D9_CHCR_002F35B0 (*(volatile unsigned int *)0x1000D400)
#define D9_MADR_002F35B0 (*(volatile unsigned int *)0x1000D410)
#define D9_QWC_002F35B0 (*(volatile unsigned int *)0x1000D420)
#define D9_SADR_002F35B0 (*(volatile unsigned int *)0x1000D480)

/* Retail 0x2F3E40: the smallest of the n / 2 sizes at 0x70000800 (read in pairs, the pad is 0xFFFF), 0x40000000 when n is 0. */
static int min_size_002F35B0(int n)
{
    int m = 0x40000000;
    unsigned int p = SPR_002F35B0 + 0x800;

    if (n != 0) {
        do {
            int a = U16_002F35B0(p);
            int b = U16_002F35B0(p + 2);
            n -= 4;
            p += 4;
            if (a < m) {
                m = a;
            }
            if (b < m) {
                m = b;
            }
        } while (n > 0);
    }
    return m;
}

void func_002F35B0(void)
{
    char *rec = D_001B21B4;
    unsigned int s7 = D_001B21E0;
    unsigned int t8 = D_001B21E4;
    unsigned int t9 = D_001B21E8;
    unsigned int at, a3, p, e;
    unsigned int q;
    unsigned long v0;
    int s2, s3, s5, s6;
    unsigned int s4;

    /* list A in at 0x70000000 */
    q = (unsigned int)(D_001B21CC + 12) >> 4;
    D9_SADR_002F35B0 = SPR_002F35B0;
    D9_MADR_002F35B0 = (unsigned int)(unsigned long)D_00218480;
    D9_QWC_002F35B0 = q;
    if (q != 0) {
        D9_CHCR_002F35B0 = 0x100;
        while (D9_CHCR_002F35B0 & 0x100) {
        }
    }

    /* the node array in at 0x70002000; mark list A's records at 0x70001000 */
    D9_SADR_002F35B0 = NODE_002F35B0;
    if (t9 != 0) {
        D9_MADR_002F35B0 = (unsigned int)(unsigned long)D_0021AC80;
        D9_QWC_002F35B0 = (t9 + 8) >> 4;
        D9_CHCR_002F35B0 = 0x100;
        for (at = SPR_002F35B0 + 0x1000; at != SPR_002F35B0 + 0x2000; at += 8) {
            U64_002F35B0(at) = 0;
        }
        e = SPR_002F35B0 + D_001B21CC;
        if (D_001B21CC != 0) {
            for (at = SPR_002F35B0; at != e; at += 4) {
                U8_002F35B0(SPR_002F35B0 + 0x1000 + U16_002F35B0(at)) = 1;
            }
        }
    }
    while (D9_CHCR_002F35B0 & 0x100) {
    }

    /* list B in at 0x70000000 */
    q = (unsigned int)(D_001B21D0 + 14) >> 4;
    D9_SADR_002F35B0 = SPR_002F35B0;
    D9_MADR_002F35B0 = (unsigned int)(unsigned long)D_00219480;
    D9_QWC_002F35B0 = q;
    if (q != 0) {
        D9_CHCR_002F35B0 = 0x100;
        while (D9_CHCR_002F35B0 & 0x100) {
        }
    }

    if (t9 == 0) {
        s7 = (unsigned int)-1;
        t8 = (unsigned int)-1;
        t9 = NODE_002F35B0;
    } else {
        /* records list B drops are marked -1 */
        e = SPR_002F35B0 + D_001B21D0;
        for (at = SPR_002F35B0; at != e; at += 2) {
            unsigned int h = U16_002F35B0(at);
            if (h & 0x8000) {
                U8_002F35B0(SPR_002F35B0 + 0x1000 + (h & 0x7FFF)) = 0xFF;
            }
        }
        s7 += NODE_002F35B0;
        t8 += NODE_002F35B0;
        t9 += NODE_002F35B0;
        /* free the nodes of records not in list A */
        at = s7;
        for (;;) {
            unsigned int idx;
            int flag;
            char *r;

            v0 = U64_002F35B0(at);
            idx = (unsigned int)(v0 >> 32) & 0xFFF;
            r = rec + idx * 32;
            flag = S8_002F35B0(SPR_002F35B0 + 0x1000 + idx);
            a3 = ((unsigned int)(v0 >> 54) << 3) + 0x2000;
            if (flag > 0) {
                if (at == t8) {
                    break;
                }
                at = a3 + SPR_002F35B0;
                continue;
            }
            if (flag == 0) {
                *(unsigned char *)(r + 31) = 0xFF;
            }
            *(unsigned short *)(r + 20) = 0xFFFF;
            if (s7 == t8) {
                U64_002F35B0(at) = 0;
                s7 = (unsigned int)-1;
                t8 = (unsigned int)-1;
                t9 = NODE_002F35B0;
                break;
            }
            if (at == s7) {
                s7 = NODE_002F35B0 + ((unsigned int)(v0 >> 54) << 3);
            } else {
                p = NODE_002F35B0 + ((unsigned int)(v0 >> 41) & 0x1FF8);
                U64_002F35B0(p) = (U64_002F35B0(p) & ~(0x3FFUL << 54)) | ((v0 >> 54) << 54);
            }
            if (at == t8) {
                t8 = NODE_002F35B0 + ((unsigned int)(v0 >> 41) & 0x1FF8);
            } else {
                p = NODE_002F35B0 + ((unsigned int)(v0 >> 51) & 0x1FF8);
                U64_002F35B0(p) = (U64_002F35B0(p) & ~(0x3FFUL << 44)) | (((v0 >> 44) << 54) >> 10);
            }
            p = t9 - 8;
            a3 = (unsigned int)(v0 >> 54) << 3;
            if (at == p) {
                /* the freed node is the array's last */
                t9 -= 8;
                U64_002F35B0(at) = 0;
                a3 += 0x2000;
                if (a3 == 0x3FF8) {
                    break;
                }
                at = a3 + SPR_002F35B0;
                continue;
            }
            /* move the array's last node into the freed one */
            v0 = U64_002F35B0(p);
            U64_002F35B0(at) = v0;
            a3 = a3 + 0x2000 + SPR_002F35B0;
            if (p == a3) {
                a3 = at;
            }
            if (p == s7) {
                s7 = at;
            } else {
                unsigned int pv = NODE_002F35B0 + ((unsigned int)(v0 >> 41) & 0x1FF8);
                U64_002F35B0(pv) = (U64_002F35B0(pv) & ~(0x3FFUL << 54)) | ((unsigned long)(at & 0x1FF8) << 51);
            }
            if (t9 - 8 == t8) {
                t8 = at;
            } else {
                unsigned int nx = NODE_002F35B0 + ((unsigned int)(v0 >> 51) & 0x1FF8);
                U64_002F35B0(nx) = (U64_002F35B0(nx) & ~(0x3FFUL << 44)) | ((unsigned long)(at & 0x1FF8) << 41);
            }
            t9 -= 8;
            at = a3;
            U64_002F35B0(t9) = 0;
            if (at == SPR_002F35B0 + 0x3FF8) {
                break;
            }
        }
    }

    s5 = D_001B21D0;
    if (s5 != 0) {
        /* sizes of list B's records at 0x70000800, padded with 0xFFFF to 8 bytes */
        U64_002F35B0(SPR_002F35B0 + 0x800 + ((unsigned int)s5 & ~7u)) = ~0UL;
        e = SPR_002F35B0 + s5;
        at = SPR_002F35B0;
        do {
            U16_002F35B0(at + 0x800) = *(unsigned short *)(rec + (U16_002F35B0(at) & 0x7FFF) * 32 + 22);
            at += 2;
        } while (at != e);

        if ((int)s7 >= 0) {
            /* best fit into the gaps before each node */
            s4 = s7;
            s2 = 0;
            s6 = min_size_002F35B0(s5);
            s3 = U16_002F35B0(s4) - s2;
            for (;;) {
                if (s3 - s6 < 0) {
                    unsigned int w;
                    if (s4 == t8) {
                        s2 = U16_002F35B0(t8) + U16_002F35B0(t8 + 2);
                        s3 = 0x10000 - s2;
                        goto append;
                    }
                    w = U32_002F35B0(s4 + 4);
                    s2 = U16_002F35B0(s4);
                    s3 = U16_002F35B0(s4 + 2);
                    s4 = SPR_002F35B0 + ((w >> 22) << 3) + 0x2000;
                    s2 = s2 + s3;
                    s3 = U16_002F35B0(s4) - s2;
                    continue;
                }
                {
                    /* retail 0x2F3D20: the largest size <= the gap (the later one on a tie) */
                    unsigned int t2 = SPR_002F35B0 + 0x800;
                    unsigned int t3 = t2 + ((unsigned int)(s5 + 6) & 0xFFF8);
                    unsigned int t7 = (unsigned int)-1;
                    unsigned int ri, w, prev, last;
                    int best = 0;
                    int k, sz, m, lsz, lb;
                    char *r;

                    do {
                        for (k = 0; k < 4; k++) {
                            sz = U16_002F35B0(t2 + k * 2);
                            m = sz < s3 ? sz : s3;
                            if (m < best) {
                                m = best;
                            }
                            if (m == sz) {
                                t7 = t2 - 0x800 + k * 2;
                                best = sz;
                            }
                        }
                        t2 += 8;
                    } while (t2 != t3);
                    ri = U16_002F35B0(t7);
                    s5 -= 2;
                    last = SPR_002F35B0 + s5;
                    lsz = U16_002F35B0(last + 0x800);
                    lb = U16_002F35B0(last);
                    U16_002F35B0(t7) = lb;
                    ri &= 0x7FFF;
                    U16_002F35B0(t7 + 0x800) = lsz;
                    U16_002F35B0(last + 0x800) = 0xFFFF;
                    if ((best & 0xFFFF) == s6) {
                        s6 = min_size_002F35B0(s5);
                    }

                    /* a new node before s4 */
                    U16_002F35B0(t9) = s2;
                    s3 -= best;
                    U16_002F35B0(t9 + 2) = best;
                    r = rec + ri * 32;
                    *(unsigned short *)(r + 20) = s2;
                    s2 += best;
                    w = U32_002F35B0(s4 + 4);
                    prev = w & 0x3FF000;
                    U32_002F35B0(t9 + 4) = ri | prev | (((s4 >> 3) & 0x3FF) << 22);
                    w ^= prev;
                    if (s4 == s7) {
                        s7 = t9;
                    } else {
                        unsigned int pv = SPR_002F35B0 + (prev >> 9) + 0x2000;
                        U64_002F35B0(pv) = ((U64_002F35B0(pv) << 10) >> 10) | ((unsigned long)((t9 >> 3) & 0x3FF) << 54);
                    }
                    U32_002F35B0(s4 + 4) = w | (((t9 >> 3) & 0x3FF) << 12);
                    t9 += 8;
                    if (s5 == 0) {
                        goto done;
                    }
                }
            }
        } else {
            /* empty list: the last record of list B starts it at 0 */
            unsigned int ri;
            int sz;

            s5 -= 2;
            s2 = 0;
            e = SPR_002F35B0 + s5;
            s3 = 0x10000;
            ri = U16_002F35B0(e);
            s7 = t9;
            sz = U16_002F35B0(e + 0x800);
            t8 = t9;
            ri &= 0x7FFF;
            U16_002F35B0(t9) = s2;
            U16_002F35B0(t9 + 2) = sz;
            s3 -= sz;
            *(unsigned short *)(rec + ri * 32 + 20) = s2;
            s2 += sz;
            U32_002F35B0(t9 + 4) = ri | 0xFFFFF000u;
            t9 += 8;
            if (s5 == 0) {
                goto done;
            }
        }
    append:
        /* the rest after the tail, while they fit in 0x10000 */
        do {
            unsigned int ri;
            int sz;

            s5 -= 2;
            e = SPR_002F35B0 + s5;
            sz = U16_002F35B0(e + 0x800);
            ri = U16_002F35B0(e);
            U16_002F35B0(t9) = s2;
            U16_002F35B0(t9 + 2) = sz;
            if (s3 - sz < 0) {
                *(unsigned char *)(rec + (ri & 0x7FFF) * 32 + 31) = 255;
            } else {
                unsigned int w;
                ri &= 0x7FFF;
                s3 -= sz;
                *(unsigned short *)(rec + ri * 32 + 20) = s2;
                s2 += sz;
                w = U32_002F35B0(t8 + 4);
                U32_002F35B0(t8 + 4) = ((w << 10) >> 10) | (((t9 >> 3) & 0x3FF) << 22);
                U32_002F35B0(t9 + 4) = ri | (((t8 >> 3) & 0x3FF) << 12) | 0xFFC00000u;
                t8 = t9;
                t9 += 8;
            }
        } while (s5 > 0);
    }

done:
    if ((int)s7 < 0) {
        t9 = 0;
    } else {
        at = NODE_002F35B0;
        D8_SADR_002F35B0 = at;
        D8_MADR_002F35B0 = (unsigned int)(unsigned long)D_0021AC80;
        D8_QWC_002F35B0 = (t9 - SPR_002F35B0 - 8184) >> 4;
        s7 -= at;
        t8 -= at;
        t9 -= at;
        D8_CHCR_002F35B0 = 0x100;
        while (D8_CHCR_002F35B0 & 0x100) {
        }
    }
    D_001B21E0 = s7;
    D_001B21E4 = t8;
    D_001B21E8 = t9;
}
