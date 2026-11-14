/* func_L05_0042B2C0 (2128 bytes; Feltzin System and three more levels): the ring-strip builder.
 * A FAKEMATCH unit (owner rulings of 13 and 14 November 2026; config/fakematch.tsv). The C is plain:
 * no volatile, no register pins. What is not the authors' is listed at each site:
 * - the order in which the first scheduling pass issues the instructions is given to the compiler
 *   as a list (#pragma rac2_sched1_order with -frac2-sched1-order): no general rule or source form
 *   found reproduces retail's order, which decides the register allocation and reload's scratch
 *   registers;
 * - two unused locals and one do { } while (0) group.
 * It builds with tools/compiler/transformers/l05_42b2c0_rules.py. The list names insn UIDs, so it
 * holds for this source and these flags only: any change to the function needs a new list. */
#include "common.h"
typedef unsigned int QBC __attribute__((mode(TI)));
typedef union { QBC q; float v[4]; } VBC;
extern VBC D_L05_00270AE0[32];
extern float D_L05_0026ECE0[][3], D_L05_002700E0[][2], D_L05_00270D60[][2];
extern unsigned D_L05_0026FBE0[], D_L05_00270CE0[];
extern int D_L05_001B1724 __attribute__((sda));
extern void ref_L05_0042B2C0_00(void *, void *, float);
extern void ref_L05_0042B2C0_01(void *, void *, float);
extern void ref_L05_0042B2C0_02(void *, void *, void *);
extern void ref_L05_0042B2C0_03(void *, void *, void *);
extern unsigned long long ref_L05_0042B2C0_04(int);
extern void ref_L05_0042B2C0_05(int, unsigned long long);
extern void ref_L05_0042B2C0_06(void);
extern void ref_L05_0042B2C0_07(int, void *, void *, void *, int);
/* The first scheduling pass's order, one insn UID per place (see the unit comment). */
#pragma rac2_sched1_order 16 45 39 29 10 6 8 14 22 42 32 34 36 12 18 20
#pragma rac2_sched1_order 56 1561 145 58 140 52 1564 62 1567 63 1800 54 60 70 72 66
#pragma rac2_sched1_order 68 1570 1753 74 80 84 86 1573 77 88 90 93 1576 103 101 99
#pragma rac2_sched1_order 105 117 108 110 119 121 123 1585 1588 125 1579 1761 130 1582 131 138
#pragma rac2_sched1_order 128 133 1770 1782 162 164 166 247 168 177 179 181 183 196 198 200
#pragma rac2_sched1_order 1797 202 217 230 219 241 1779 1767 149 260 262 1746 1728 305 1809 1726
#pragma rac2_sched1_order 297 269 1734 286 299 301 1730 282 288 308 1742 1752 1817 272 274 279
#pragma rac2_sched1_order 303 1737 1732 1733 1744 1740 1736 1750 1738 1748 1811 1820 1741 1807 1814 322
#pragma rac2_sched1_order 324 326 369 328 372 342 338 331 340 344 357 353 355 359 362 375
#pragma rac2_sched1_order 364 376 1828 1829 380 396 458 482 502 424 469 476 480 483 500 401
#pragma rac2_sched1_order 426 408 503 415 520 478 445 532 522 430 498 417 523 403 518 410
#pragma rac2_sched1_order 538 449 432 558 631 549 485 505 1684 1686 451 525 540 636 551 460
#pragma rac2_sched1_order 560 464 1621 1622 1802 1672 1674 578 574 576 1646 466 626 1603 562 633
#pragma rac2_sched1_order 1676 583 1648 1688 588 593 599 1698 639 1634 609 604 1600 628 1713 1719
#pragma rac2_sched1_order 1725 669 770 680 772 691 774 712 1694 733 761 756 992 671 986 682
#pragma rac2_sched1_order 693 714 1682 735 1642 758 776 1668 785 787 789 791 802 829 804 1691
#pragma rac2_sched1_order 831 643 833 805 921 834 923 807 924 816 836 859 878 861 898 880
#pragma rac2_sched1_order 900 928 930 941 1679 952 1639 961 1665 972 1722 983 1716 1710 644 1010
#pragma rac2_sched1_order 1129 1017 1056 1019 1106 1021 1064 1132 1145 1034 1047 1023 1066 1114 1049 1095
#pragma rac2_sched1_order 1036 1058 1068 1148 1116 1097 1083 1150 1177 1070 1183 1153 1228 1099 1108 1155
#pragma rac2_sched1_order 1194 1118 1205 1158 1214 1185 1216 1160 1347 1120 1349 1196 1351 1207 1361 1234
#pragma rac2_sched1_order 1335 1328 1230 1232 1290 1301 1338 1330 1218 1245 1256 1267 1278 1353 312 313
#pragma rac2_sched1_order 1371 1428 1373 1431 1377 1379 1381 1605 1383 1387 1390 1607 1385 1392 1394 1397
#pragma rac2_sched1_order 1399 1401 1404 1406 1408 1411 1413 1415 1418 1420 1422 1425 1609 1612 1610 1613
#pragma rac2_sched1_order 1615 1616 1478 1445 1827 1462 1544 1470 1476 1480 1482 1484 1486 1489 1492 1499
#pragma rac2_sched1_order 1496 1501 1435
/* FAKEMATCH: the #pragma rac2_sched1_order list above fixes the pre-reload order of this function's insns */
void func_L05_0042B2C0(VBC *origin, VBC *axis, int texture, unsigned color,
 float advance, float radius, float stepU, float stepV, float startV, float startU)
{
    /* FAKEMATCH: q and w are unused; they keep the pseudo register numbers, which break allocation ties */
    float *p, *q, *r, *w, *t, *e1, (*ee)[2];
    VBC *ring, *ae;
    VBC unit, center, delta, radial, rotation, inverse, rotation2, inverse2;
    float u, v, nextU, nextV;
    int k, i, out, remaining, base, n, row;

    unit.q = 0;
    unit.v[2] = unit.v[3] = 1.0f;
    out = 0;
    u = startU;
    qcopy_nc(&center, origin);
    ref_L05_0042B2C0_00(&delta, axis, advance);
    ring = D_L05_00270AE0;
    ref_L05_0042B2C0_00(&radial, &unit, radius);
    radial.v[3] = 0;
    ref_L05_0042B2C0_01(&rotation, axis, 0.202683404f);
    ref_L05_0042B2C0_00(&inverse, &rotation, -1.0f);
    inverse.v[3] = rotation.v[3];

    ref_L05_0042B2C0_02(&ring[0], &center, &radial);
        D_L05_00270CE0[0] = color;
        D_L05_00270D60[0][1] = startV;
        D_L05_00270D60[0][0] = u;
        v = startV + stepU;
    for (k = 1, i = 29; i >= 0; i--, k++) {
        ref_L05_0042B2C0_03(&radial, &rotation, &radial);
        ref_L05_0042B2C0_03(&radial, &radial, &inverse);
        ref_L05_0042B2C0_02(&ring[k], &center, &radial);
        D_L05_00270D60[k][1] = v;
        v += stepU;
        D_L05_00270CE0[k] = color;
        D_L05_00270D60[k][0] = startU;
    }
        { VBC *qs = D_L05_00270AE0; VBC *qd = &D_L05_00270AE0[31]; qcopy(qd, qs); }
        u += stepV;
        D_L05_00270D60[31][1] = v;
        D_L05_00270D60[31][0] = startU;
        D_L05_00270CE0[31] = D_L05_00270CE0[0];
        ref_L05_0042B2C0_02(&center, &center, &delta);
        nextV = startV + stepU;
    for (row = 1; row < 6; row++) {
        ref_L05_0042B2C0_00(&radial, &unit, radius);
        radial.v[3] = 0;
        ref_L05_0042B2C0_01(&rotation2, axis, 0.202683404f);
        ref_L05_0042B2C0_00(&inverse2, &rotation2, -1.0f);
        inverse2.v[3] = rotation2.v[3];
        {
        int first;
        v = startV;
        first = out + 1;
        if (row == 5) color &= 0xFFFFFF;
        ee = D_L05_002700E0;
        ae = D_L05_00270AE0;
        r = D_L05_0026ECE0[out];
        r[0] = D_L05_00270AE0[0].v[0];
        r[1] = D_L05_00270AE0[0].v[1];
        r[2] = D_L05_00270AE0[0].v[2];
        D_L05_002700E0[out][0] = D_L05_00270D60[0][0];
        D_L05_002700E0[out][1] = D_L05_00270D60[0][1];
        D_L05_0026FBE0[out] = D_L05_00270CE0[0];
        out = first;
        D_L05_0026ECE0[out][0] = center.v[0] + radial.v[0];
        D_L05_0026ECE0[out][1] = center.v[1] + radial.v[1];
        D_L05_0026ECE0[out][2] = center.v[2] + radial.v[2];
        D_L05_002700E0[out][1] = v;
        D_L05_002700E0[out][0] = u;
        D_L05_0026FBE0[out] = color;
        { float *t = D_L05_0026ECE0[out]; float w0 = t[0], w1 = t[1], w2 = t[2];
        D_L05_00270AE0[0].v[0] = w0;
        D_L05_00270AE0[0].v[1] = w1;
        D_L05_00270AE0[0].v[2] = w2; }
        D_L05_00270AE0[0].v[3] = 0;
        D_L05_00270D60[0][0] = u;
        D_L05_00270CE0[0] = color;
        D_L05_00270D60[0][1] = D_L05_002700E0[out][1];
        out++;
        nextU = u + stepV;
        v = nextV;

        for (i = 1; i < 31; i++) {
            e1 = &ee[0][1]; /* FAKEMATCH: loop-invariant set inside the inner loop (ee = E0 base per row): loop moves it and the 00E0 giv's add_val becomes (plus ee 4), so the giv init is retail's (out*8 + 4) + E0 instead of out*8 + (E0+4) */
            p = D_L05_0026ECE0[out];
            p[0] = ae[i].v[0];
            p[1] = ae[i].v[1];
            p[2] = ae[i].v[2];
            D_L05_0026FBE0[out] = D_L05_00270CE0[i];
            e1[out * 2 - 1] = D_L05_00270D60[i][0];
            e1[out * 2] = D_L05_00270D60[i][1];
            out++;
            ref_L05_0042B2C0_03(&radial, &rotation2, &radial);
            ref_L05_0042B2C0_03(&radial, &radial, &inverse2);
            D_L05_0026ECE0[out][0] = center.v[0] + radial.v[0];
            e1[out * 2] = v;
            D_L05_0026ECE0[out][1] = center.v[1] + radial.v[1];
            D_L05_00270D60[i][1] = e1[out * 2];
            v += stepU;
            ae[i].v[0] = D_L05_0026ECE0[out][0];
            t = D_L05_0026ECE0[out];
            ae[i].v[1] = t[1];
            D_L05_0026ECE0[out][2] = ae[i].v[2] = center.v[2] + radial.v[2];
            D_L05_0026FBE0[out] = color;
            e1[out * 2 - 1] = u;
            ae[i].v[3] = 0;
            D_L05_00270CE0[i] = color;
            D_L05_00270D60[i][0] = u;
            out++;
        }

        {
        float *sp, *sq, *sw;
        unsigned sc;
        sp = D_L05_0026ECE0[out];
        sp[0] = D_L05_00270AE0[i].v[0];
        sp[1] = D_L05_00270AE0[i].v[1];
        sp[2] = D_L05_00270AE0[i].v[2];
        D_L05_002700E0[out][0] = D_L05_00270D60[i][0];
        D_L05_002700E0[out][1] = D_L05_00270D60[i][1];
        D_L05_0026FBE0[out] = D_L05_00270CE0[i];
        sq = D_L05_0026ECE0[first];
        out++;
        /* FAKEMATCH: do { } while (0) keeps cse from merging this pointer with the reload pointer below (-frac2-cse2-loop-end-forgets-arith); retail forms the address twice */
        do {
        sw = D_L05_0026ECE0[out];
        sw[0] = sq[0];
        sw[1] = sq[1];
        sw[2] = sq[2];
        } while (0);
        D_L05_002700E0[out][1] = v;
        D_L05_002700E0[out][0] = u;
        sc = D_L05_0026FBE0[first];
        D_L05_0026FBE0[out] = sc;
        { float *st = D_L05_0026ECE0[out]; float t0 = st[0], t1 = st[1], t2 = st[2];
        D_L05_00270AE0[i].v[0] = t0;
        D_L05_00270AE0[i].v[1] = t1;
        D_L05_00270AE0[i].v[2] = t2;
        D_L05_00270AE0[i].v[3] = 0; }
        D_L05_00270D60[i][0] = u;
        D_L05_00270CE0[i] = sc;
        D_L05_00270D60[i][1] = D_L05_002700E0[out][1];
        }
        out++;
        u = nextU;
        ref_L05_0042B2C0_02(&center, &center, &delta);
        }
    }

    ref_L05_0042B2C0_05(6, ref_L05_0042B2C0_04(texture));
    ref_L05_0042B2C0_05(0x42, 0x8000000040ULL | ((long long)D_L05_001B1724 << 2));
    ref_L05_0042B2C0_05(8, 0);
    ref_L05_0042B2C0_05(0x14, 0xFF9000000260ULL);
    ref_L05_0042B2C0_05(0x47, 0x53001);
    ref_L05_0042B2C0_05(0x4A, 0);
    ref_L05_0042B2C0_06();
        remaining = 320;
        base = 0;
    while (1) {
        n = remaining < 149 ? remaining : 148;
        ref_L05_0042B2C0_07(n, D_L05_0026ECE0[base], &D_L05_0026FBE0[base], D_L05_002700E0[base], 1);
        remaining -= n;
        if (remaining > 0) {
            remaining += 2;
            base += n - 2;
        } else
            break;
    }
}
