/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* 2026-10-25 ADDRESS follow-up: retained best prior C, not matching.
 * Baseline reproduced 1000/1008 bytes, 0/27 US placements. Approved qcopy
 * transfers, no-force-mem and no-rerun-loop-opt each measured 1000 bytes.
 * A truthful 0xB0 record/field-at-use loop measured 952 bytes and did not
 * reproduce retail. Original independent pointer lifetimes are retained.
 * Both seven-word gathers remain gathers around the resident clear; no
 * volatile, artificial uses, missing stores or padding were introduced.
 * Reopen only with independently measured resident-base alias/lifetime data
 * or an allocator trace identifying a changed real pseudo. Other releases
 * have no canonical catalogue entry; absence awards no matching credit.
 */
/* Retained reconstruction, 23 October 2026: 1000/1008 bytes, 0/27 USA v1.01.
 * The canonical name is absent from PAL and USA v2.00 catalogues.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy.
 * Eight meaningful source/profile experiments were bounded: retaining a single
 * full resident-base pointer spills and makes a 0xA0 frame; direct references
 * recover retail's 0x90 frame. Typed resident fields shorten the body to 984,
 * -fno-gcse and -fno-schedule-insns give 996, and splitting the local storage
 * leaves this 1000-byte result. The remaining mismatch includes high/base
 * address lifetimes, register allocation, joins and scheduling, not two nops.
 * Reopen with an independently supported resident-data alias/lifetime model.
 * The absolute mode word and its SDA reference denote the same resident word.
 */
#include "include_asm.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;

extern unsigned char D_00189E20[0x2540];
extern int D_001A79F0[];
extern int ref_L00_002A4928_00 __attribute__((sda));
extern int D_001A7398[];
extern int D_001A7A00[];
extern unsigned char D_001A7AFA[];
extern char *D_L00_001B1E9C[];
extern char *D_L00_001B1EA0[];
extern Quad D_L00_001BF220;
extern Quad D_00152C70[];
extern unsigned char D_L00_0025BE10[];
extern int D_L00_001A8FF0[];
extern Quad D_L00_001B1B10;

extern void func_00282A60(void *, int, int);
extern void func_002833F0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_00282C88(Quad *);
extern void func_L00_002B4900(void);
extern void func_L00_002A9460(void);
extern void func_L00_002D23C0(int, int);
extern void func_L00_002D5EB8(void);
extern int func_002A7820(int, int);

#define STATE(type, offset) (*(type *)(D_00189E20 + (offset)))

/* Reset the resident player state and its level records. Retail performs two
   gathers into the local words around the clear; neither loop is a scatter. */
void func_L00_002A4928(void)
{
    int words[8];
    Vector near, far;
    int *out = words;
    unsigned char *slot = D_00189E20 + 0x1248;
    unsigned char *after_clear;
    int count = 6;
    char *object;
    char *end;
    char *basis;
    char *axis;
    int mode;
    unsigned char *flag;
    unsigned char *a, *b, *c, *d, *e, *f;
    int *last;

    do {
        *out++ = *(int *)slot;
        slot += 0x50;
    } while (--count >= 0);
    func_00282A60(D_00189E20, 0, 0x2540);
    count = 6;
    after_clear = D_00189E20 + 0x1248;
    out = words;
    do {
        *out++ = *(int *)after_clear;
        after_clear += 0x50;
    } while (--count >= 0);

    object = D_L00_001B1E9C[0];
    end = D_L00_001B1EA0[0];
    if (object < end) {
        basis = object + 0xC0;
        axis = object + 0xF0;
        do {
            if (*(short *)(object + 0xAA) == 0) {
                STATE(char *, 0x2290) = object;
                func_002833F0(basis, axis);
                func_00282F20(&far, STATE(char *, 0x2290) + 0xE0, -3.0f);
                func_00282F20(&near, STATE(char *, 0x2290) + 0xE0, 1.0f);
                func_00282CC0(&near, &near, D_00189E20 + 0x80);
                func_00282CC0(&far, &far, D_00189E20 + 0x80);
                if (func_002761F8(&near, &far, 2, STATE(char *, 0x2290), 0) != 0)
                    STATE(Quad, 0x80) = D_L00_001BF220;
                *(unsigned short *)(STATE(char *, 0x2290) + 0x34) |= 2;
                STATE(char *, 0xC18) = STATE(char *, 0x2290);
                STATE(float, 0x98) = *(float *)(STATE(char *, 0x2290) + 0xF8);
                STATE(Quad, 0x80) = *(Quad *)(STATE(char *, 0x2290) + 0x10);
                func_L00_002B4900();
                func_L00_002A9460();
                func_L00_002D23C0(0, 0);
                D_00152C70[0] = STATE(Quad, 0x80);
                D_00152C70[1] = STATE(Quad, 0x90);
                mode = ref_L00_002A4928_00;
                goto selected;
            }
            object += 0x100;
            basis += 0x100;
            axis += 0x100;
        } while (object < end);
    }
    mode = D_001A79F0[0];
selected:
    if (mode == 1 || mode == 8)
        *(unsigned char *)(STATE(char *, 0x2290) + 0x7E) |= 1;
    *(unsigned char *)(STATE(char *, 0x2290) + 0x62) = 0xFF;
    if (D_001A7398[0] == 0)
        D_001A7398[0] = 30;

    flag = D_L00_0025BE10 + 1;
    a = D_L00_0025BE10 + 0x60;
    b = D_L00_0025BE10 + 0x40;
    c = D_L00_0025BE10 + 0x50;
    d = D_L00_0025BE10 + 0x90;
    e = D_L00_0025BE10 + 0x70;
    f = D_L00_0025BE10 + 0x80;
    count = 39;
    do {
        *flag = 0;
        func_00282C88((Quad *)a); a += 0xB0;
        flag += 0xB0;
        func_00282C88((Quad *)b); b += 0xB0;
        --count;
        func_00282C88((Quad *)c); c += 0xB0;
        func_00282C88((Quad *)d); d += 0xB0;
        func_00282C88((Quad *)e); e += 0xB0;
        func_00282C88((Quad *)f); f += 0xB0;
    } while (count >= 0);

    last = (int *)(D_00189E20 + 0x244C);
    count = 8;
    do { *last-- = -1; } while (--count >= 0);
    STATE(float, 0x24A4) = 2.125f;
    STATE(float, 0x24A8) = 1.25f;
    if (D_001A7A00[0] == 0)
        func_L00_002D5EB8();
    STATE(int, 0x24D0) = 4;
    STATE(int, 0x24CC) = D_001A7A00[0];
    STATE(unsigned short, 0x24D4) = STATE(unsigned short, 0x24CC);
    STATE(int, 0x11A0) = func_002A7820(180, 300);
    STATE(float, 0x11A4) = 0.007f;
    STATE(float, 0x11A8) = 0.3f;
    STATE(float, 0xEB0) = 0.97f;
    if (D_L00_001A8FF0[0] != 0)
        STATE(Quad, 0xB0) = D_L00_001B1B10;
    STATE(int, 0x18D4) = 0;
    if (D_001A7AFA[0] == 0)
        STATE(short, 0x24FC) = 1;
}
