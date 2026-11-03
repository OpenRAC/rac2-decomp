/* Complete C near miss; not linked and no matching credit.
 * Tier: opus-2 (Claude Opus 5.5, xhigh), task v2201, 2026-11-03 (supersedes opus-1's v2143 draft, 109 rows).
 * Build as src/levels/shared/L05_00417D48-g8.c (game -O2 -G8; no extra flags).
 * Best check.py: 1204/1204 bytes, 0 of 4 places match, first difference +0xEC,
 * 101 of 301 rows differ (us).
 * Needed declarations (below): D_001A7AF0, D_L05_001B34F0 and D_L05_001B3510 MACRO_ADDR;
 * D_0018B650 and the selector tables D_L05_001A8F70..FA0 nosda; D_L05_001B3500 plain;
 * func_L05_0041C708 (char *, float, int, int); one reused masked-index variable `flags`;
 * o+0x68 is a struct (State_L05_00417D48) accessed through members.
 * Fixed since v2143: case-0 tail store order (0x58, 0x54, 0x5C, 0xA0 in source order),
 * case-1 `slt` (compare the two calls directly), qcopy registers (MACRO_ADDR destination),
 * and the struct-member state: with cast-pointer stores, sched1 keeps the D_001A7AF0 and table
 * loads below `st+0x50 = func_L05_00432080()`; struct-member stores do not alias a fixed scalar
 * (alias.c fixed_scalar_and_varying_struct_p), so they rise above it as in retail.
 * Remaining: (1) the shifted selector index `flags` is v0 here (a2 with cast pointers); retail
 * a3 in every segment. Retail's >>6 segment holds the F88 table base in a2 while flags is live,
 * so a2 conflicts with flags there; ours puts that base in v1 and D in a0.
 * (2) Segment 1: retail loads D_001A7AF0 into v1 before the D_0018B650 store and builds the
 * F70 table base in a0. (3) The >>7 segment's D load and reorg's skip of the merge reload.
 * Next: make the per-segment local registers (D v1/v0, table base a0/a2) come out as retail's.
 * Try struct members for o as well, or a different statement order for the 0x50 store.
 */
#include "common.h"

extern void func_L05_00418200(char *);
extern void func_00282C88(char *);
extern unsigned int D_001A7AF0 MACRO_ADDR;
extern char *D_0018B650 __attribute__((nosda));
extern char D_L05_001B34F0[] MACRO_ADDR;
extern char D_L05_001B3510[] MACRO_ADDR;
extern float D_L05_001B3500;
extern short D_L05_001A8F70[] __attribute__((nosda));
extern short D_L05_001A8F78[] __attribute__((nosda));
extern short D_L05_001A8F80[] __attribute__((nosda));
extern short D_L05_001A8F88[] __attribute__((nosda));
extern short D_L05_001A8F90[] __attribute__((nosda));
extern short D_L05_001A8F98[] __attribute__((nosda));
extern short D_L05_001A8FA0[] __attribute__((nosda));
extern char *func_L05_0041C708(char *, float, int, int);
extern char *func_L05_00432080(char *, float);
extern int func_002ED8A0(int);
extern int func_L05_0037AC00(void);
extern int func_L05_0037AC40(void);
extern int func_00282948(char *);
extern int func_002E59B0(char *, int);
extern int func_002E5CF8(int, int, char *);
extern void func_L05_00418288(char *);
extern void func_L00_004450C0(char *);

typedef struct {
    int f0;
    int f4;
    short f8;
    short fA;
    char padC[0x8];
    int f14;
    int f18;
    int f1C;
    char pad20[0x10];
    int f30;
    int f34;
    int f38;
    int f3C;
    char * f40;
    char * f44;
    char * f48;
    char * f4C;
    char * f50;
    int f54;
    int f58;
    int f5C;
    char pad60[0x40];
    int fA0;
    char padA4[0x8];
    char * fAC;
    char padB0[0x140];
    char * f1F0;
    char * f1F4;
    char * f1F8;
    char * f1FC;
    char * f200;
    char * f204;
    char * f208;
    int f20C;
    int f210;
    char pad214[0x4C];
    int f260;
    int f264;
    int f268;
    int f26C;
    int f270;
    char * f274;
    char * f278;
    int f27C;
} State_L05_00417D48;

void func_L05_00417D48(char *o)
{
    State_L05_00417D48 *st = *(State_L05_00417D48 **)(o + 0x68);
    int mode = *(unsigned char *)(o + 0x20);
    int id;
    unsigned int flags;

    switch (mode) {
    case 0:
        st->f30 = -1;
        st->f270 = -1;
        st->f260 = 1;
        st->f264 = 0x3840;
        st->f0 = 0;
        st->f4 = 0;
        st->f8 = 0;
        st->fA = 0;
        st->f20C = 0;
        st->f210 = 0;
        st->f14 = 0;
        st->f18 = 0;
        st->f1C = 0;
        st->f34 = 0;
        st->f38 = 0;
        st->f3C = 0;
        st->f268 = 0;
        st->f26C = 0;
        st->f27C = 0;
        *(unsigned char *)(o + 0x20) = 1;
        *(unsigned short *)(o + 0x34) |= 0x100;
        func_L05_00418200(o);
        func_00282C88(D_L05_001B34F0);
        D_0018B650 = o;
        flags = D_001A7AF0 & 3;
        D_L05_001B3500 = 0;
        *(unsigned short *)(o + 0x34) |= 0x41;
        st->f40 = func_L05_0041C708(o, 0.05f, 0, D_L05_001A8F70[flags]);
        if (st->f40) *(int *)(st->f40 + 0x98) = 0;
        flags = (D_001A7AF0 >> 2) & 3;
        id = D_L05_001A8F78[flags];
        st->f44 = func_L05_0041C708(o, 0.05f, 0, id);
        st->f48 = func_L05_0041C708(o, 0.05f, 1, id);
        if (st->f44) *(int *)(st->f44 + 0x98) = 0;
        if (st->f48) *(int *)(st->f48 + 0x98) = 0;
        flags = (D_001A7AF0 >> 4) & 3;
        st->f4C = func_L05_0041C708(o, 0.05f, 0, D_L05_001A8F80[flags]);
        if (st->f4C) *(int *)(st->f4C + 0x98) = 0;
        st->f50 = func_L05_00432080(o, 0.05f);
        flags = (D_001A7AF0 >> 6) & 1;
        id = D_L05_001A8F88[flags];
        st->fAC = func_L05_0041C708(o, 0.05f, 0, id);
        st->f1F0 = func_L05_0041C708(o, 0.05f, 1, id);
        if (st->fAC) *(int *)(st->fAC + 0x98) = 0;
        if (st->f1F0) *(int *)(st->f1F0 + 0x98) = 0;
        flags = (D_001A7AF0 >> 9) & 1;
        id = D_L05_001A8F98[flags];
        st->f1F4 = func_L05_0041C708(o, 0.05f, 0, id);
        st->f1F8 = func_L05_0041C708(o, 0.05f, 1, id);
        if (st->f1F4) *(int *)(st->f1F4 + 0x98) = 0;
        if (st->f1F8) *(int *)(st->f1F8 + 0x98) = 0;
        if (func_002ED8A0(3)) {
            flags = (D_001A7AF0 >> 7) & 3;
            id = D_L05_001A8F90[flags];
            if (id) {
                st->f1FC = func_L05_0041C708(o, 0.05f, 0, id);
                st->f200 = func_L05_0041C708(o, 0.05f, 1, id);
                if (st->f1FC) *(int *)(st->f1FC + 0x98) = 0;
                if (st->f200) *(int *)(st->f200 + 0x98) = 0;
            }
        }
        flags = (D_001A7AF0 >> 10) & 3;
        id = D_L05_001A8FA0[flags];
        st->f204 = func_L05_0041C708(o, 0.05f, 0, id);
        st->f208 = func_L05_0041C708(o, 0.05f, 1, id);
        if (st->f204) *(int *)(st->f204 + 0x98) = 0;
        if (st->f208) *(int *)(st->f208 + 0x98) = 0;
        if (func_002ED8A0(4) != -1) {
            st->f274 = func_L05_0041C708(o, 0.05f, 0, 0x10E2);
            if (st->f274) *(int *)(st->f274 + 0x98) = 0;
        }
        if (func_002ED8A0(5) != -1) {
            st->f278 = func_L05_0041C708(o, 0.05f, 0, 0x10E4);
            if (st->f278) *(int *)(st->f278 + 0x98) = 0;
        }
        st->f58 = 70;
        st->f54 = 60;
        st->f5C = 0;
        st->fA0 = 0;
        break;
    case 1:
        if (func_L05_0037AC00() < func_L05_0037AC40()) st->f260 = mode;
        if (st->f260) {
            if (func_00282948((char *)&st->f264)) st->f268 = mode;
        }
        if (!func_002E59B0(o, st->f30)) st->f30 = func_002E5CF8(0, 4, o);
        func_L05_00418288(o);
        qcopy(D_L05_001B3510, o + 0x10);
        func_L00_004450C0(o);
        break;
    }
}
