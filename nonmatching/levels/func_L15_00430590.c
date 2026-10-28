/* func_L15_00430590 - 588 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   func_L15_00430590 (588 B). Dropped as far (508 B vs 588 B, ~99 masked
   lines): draft.c is a partial decode (slot release via the 0x70-byte table
   at D_00188660, gate on func_00282948, the menu counter block with gp
   globals 0x1B1520 table / 0x1B15C8..15CC / 0x1B1578..157C / 0x1A904C, pad
   bits 0x40/0x10 of D_00138324). It leaves out the retail block after
   func_0029B758-style pad 0x40 handling that sets gp[0x25D8] to 1/2/3 from
   G[0], G[1], G[2] (D_L15_001B1520/1524/1528) and then calls
   func_L15_0042FD40; the movn clamp `idx = t0<3 ? t0 : 2` comes out as `movn`
   already; the 0x1A79F8 update reads absolute and writes via $gp in retail
   (needs an alias name for the same address). Goes in L15_00315428-g8.c. */

typedef struct { int pad[0x88 / 4]; u8 *owner; } Rec_L15_00430590;
extern u8 *D_001B261C;
extern int D_001A8F00;
extern unsigned char D_001A7A0A;
extern int D_001A79F8 __attribute__((sda));
extern int D_001B36A4;
extern int D_L15_001B15C8 __attribute__((sda));
extern int D_L15_001B15CC __attribute__((sda));
extern int D_L15_001B15BC __attribute__((sda));
extern int D_L15_001B157C __attribute__((sda));
extern int D_L15_001B1578 __attribute__((sda));
extern int D_L15_001A904C __attribute__((sda));
extern int D_L15_001B15D8[] __attribute__((sda));
extern int D_00138324;
extern u8 D_00188660[];
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern void func_0027D330(int);
extern void func_0029B758(int, int);
extern void func_L15_00432008(void);
extern void func_0029B3E0(int, int);
extern void func_L05_00379F48(int);
extern void func_L15_0042FD40(u8 *);
extern void func_002B49E0(int, int, int, int, int);

void func_L15_00430590(u8 *a0, int a1) {
    u8 *s1 = *(u8 **)(a0 + 0x68);
    u8 *mob = D_001B261C + (*(int *)(s1 + 0x20) << 8);
    u8 *s0 = *(u8 **)(mob + 0x68);
    int rec_i = *(int *)(s0 + 0x270);
    u8 *rec;
    int t0;
    int idx;
    int a;
    int pad;

    if (rec_i != -1) {
        rec = D_00188660 + rec_i * 0x70;
        if (*(u8 **)(rec + 0x88) == mob && rec[0x74] != 0) {
            func_002E59F8(rec_i);
        }
        *(int *)(s0 + 0x270) = -1;
    }
    if (D_001A8F00 == 2) {
        return;
    }
    if (func_00282948(s1 + 0x6C) == 0) {
        return;
    }
    if (D_L15_001A904C != 0 && D_L15_001B15CC == 0) {
        func_0027D330(0x1E);
        func_0029B758(0, 0x430168);
        t0 = (&D_L15_001B1520)[a1];
        idx = t0 < 3 ? t0 : 2;
        D_L15_001B15CC = 1;
        D_001B36A4 = a1;
        D_L15_001B157C = 0;
        D_L15_001B1578 = 0;
        a = D_L15_001B15D8[a1 * 3 + idx];
        if (D_001A7A0A != 0) {
            a *= 10;
        }
        (&D_L15_001B1520)[a1] = t0 + 1;
        D_001A79F8 += a;
        func_L15_00432008();
        func_0029B3E0(0, -1);
    }
    func_L05_00379F48(1);
    if (func_00282948(s1 + 0x50) != 0) {
        *(int *)(s1 + 0x50) = 0x1518;
        return;
    }
    pad = D_00138324;
    if (pad & 0x40) {
        D_L15_001B15CC = 0;
        *(int *)(s1 + 0x50) = 0x1518;
        func_0027D330(0x1E);
        func_L05_00379F48(0);
        *(int *)(s1 + 0x6C) = 0x78;
        func_L15_0042FD40(a0);
    } else if (pad & 0x10) {
        func_002B49E0(3, 1, 4, 0, 0);
    }
}
