/* Claude Opus 5.5 (xhigh), 3 November 2026: FAILED, 1496/1496 bytes,
 * 0/1 USA v1.01 places (142 cdiff lines). Standalone game unit profile:
 * -O2 -G2 -ffunction-sections -mastra-quad-saves (src/core/001185E8.c).
 * Same size as retail; every block's code shape matches. Fixes over the
 * 1472-byte draft: the fraction loop exits with `goto round` (a break as last
 * insn rotated it and lost the hoisted 10.0 in $s7); the integer loop keeps
 * its top test as `while (++e < 163) { ...; if (f < 1.0) break; }`; the
 * scale-down loop is a rotated `while ((value *= 10.0) < 1.0 && e >= -1020)
 * e--; e--;` (beql slot); `if (ndigits != 0)` / `if (ch != 'f')` arm order;
 * the '.' shift loop reuses n (retail $s2, giv len + p); `n = u.i[0];
 * n &= ~0xFFFF;` truncates straight into $s2.
 * Left: (1) retail has a once-through loop note before the switch (no back
 * edge): it is a sched2 barrier, so param spills and all saves precede the
 * extraction, and $L17 at 0x678 gets the .p2align 3 nop at 0x674. A
 * diagnostic do { ... } while (0) around the dispatch reproduces both (60
 * lines left) but is forbidden; the original construct is unknown.
 * (2) e is $s5 and eps/precision $s4, retail the reverse: eps (9 refs, live
 * 70) outranks e (34 refs, live 472) in the global queue. (3) Integer loop
 * store `p[n] = digit + '0'`: retail emits the value (v1) before the address
 * (v0) and puts the floatsidf a0 move in the jal slot, n++ after the call;
 * here sched1 keeps address first and n++ fills the slot. n++ position and
 * p[n++] made no difference. All declarations follow.
 */
#include "common.h"

extern char D_0013C080[];

extern char D_0013A490[];
extern char D_0013A498[];
extern char D_0013A4A0[];
extern char D_0013A4A8[];

extern int func_00118460(char *buf, int len);

extern char *func_00118548(int value, char *buf, unsigned int base);

extern double func_00117650(double);

extern double func_00117848(double, double);

char *func_001185E8(double value, int ndigits, char ch, int dot) {
    union {
        double d;
        int i[2];
    } u;
    char *p;
    char c;
    double f;
    double eps;
    int e;
    int n;
    int i;
    int j;
    int digit;
    int len;
    int precision;

    u.d = value;
    n = u.i[0];
    n &= ~0xFFFF;
    switch (n) {
    case 0x7FF00000:
        return D_0013A490;
    case 0xFFF00000:
        return D_0013A498;
    case 0x7FF80000:
    case 0x7FFC0000:
    case 0xFFFC0000:
        return D_0013A4A0;
    case 0xFFF80000:
        return D_0013A4A8;
    }

    precision = ndigits;
    e = 0;
    n = 0;
    if (value < 0) {
        D_0013C080[0] = '-';
        p = D_0013C080 + 1;
        value = -value;
    } else {
        p = D_0013C080;
    }

    if (value >= 1.0) {
        f = func_00117650(value);
        value = value - f;
        while (++e < 163) {
            digit = (int)func_00117848(f, 10.0);
            p[n] = digit + '0';
            f = (f - (double)digit) * 0.1;
            n++;
            if (f < 1.0)
                break;
        }
        for (digit = 0, j = n - 1; digit < j; digit++, j--) {
            c = p[digit];
            p[digit] = p[j];
            p[j] = c;
        }
    }
    e = n;

    if (e == 0) {
        if (ch != 'f') {
            if (value != 0) {
                while ((value *= 10.0) < 1.0 && e >= -1020)
                    e--;
                e--;
            }
            if (value >= 1.0) {
                value = value * 0.1;
                precision = precision + 1;
            }
        } else {
            p[0] = '0';
            n = 1;
        }
    }

    if (e < 0) {
        len = precision;
    } else if (ch != 'f') {
        len = precision + 1;
    } else {
        len = precision + (e > 0 ? e : 1);
    }

    eps = 5.5511151231257827e-17;
    for (;;) {
        value *= 10.0;
        digit = (int)value;
        value -= (double)digit;
        eps *= 10.0;
        if (n >= len || value < eps || value > 1.0 - eps)
            goto round;
        p[n++] = digit + '0';
    }
round:
    if (value >= 0.5)
        digit = digit + 1;
    p[n] = digit + '0';
    n++;
    while (n <= len) {
        p[n] = '0';
        n++;
    }
    if (func_00118460(p, len + 1) == 0) {
        p[0] = '1';
        e = e + 1;
        len = len + 1;
    }
    if (ndigits != 0) {
        i = 1;
        if (ch == 'f' && e > 0)
            i = e;
        for (n = len; i < n; n--)
            p[n] = p[n - 1];
        p[i] = '.';
    } else {
        len = len - 1;
    }
    if (dot == 0)
        goto skip;
    while (len != 0 && p[len] == '0') len--;
    if (p[len] == '.') len--;
skip:
    if (ch != 'f') {
        p[++len] = ch;
        if (e >= 0) {
            if (e != 0) e--;
            p[++len] = '+';
            if (e < 10) p[++len] = '0';
        } else {
            p[++len] = '-';
            if (e > -10) p[++len] = '0';
            e = -e;
        }
        func_00118548(e, p + ++len, 10);
    } else {
        p[len + 1] = 0;
    }
    return D_0013C080;
}
