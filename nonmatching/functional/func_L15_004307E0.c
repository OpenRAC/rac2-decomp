/* functional: medium. Written from the assembly: plain floats, 16-byte copies as four ints, the six 4-float scratch vectors are one local array; the data words are named by address and their roles are taken from their use here. */

extern int D_L15_001B1534;                  /* set once the first frame has run */
extern int D_L15_00221E3C;
extern int D_L15_001B2148;
extern int D_L15_001B15BC;                  /* 0: waiting, else: the hit has been placed */
extern int D_L15_001B15D0;
extern int D_L15_001B1520;
extern int D_L15_001B15AC;
extern float D_L15_001B1550[4];             /* the placed position */
extern float D_L15_001B1540[4];             /* its orientation */
extern char *D_L15_001B261C;                /* the moby table: 0x100 bytes each */
extern char D_L15_001BFC00[];

extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(int);
extern unsigned char **func_L05_00379EB8(void);
extern int func_L00_004272A0(void);
extern void func_L05_0037B280(void *, int);
extern unsigned char *func_L05_00379ED0(int);
extern int func_L10_0037D200(void *);
extern int func_00282948(void *);
extern void func_L05_0037B108(void);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern float func_00282E48(void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_002AB6D8(void *, void *);
extern void func_L05_00442828(void *, void *, int);
extern void func_L15_00432008(void);
extern void func_0029B3E0(int, int);
extern void func_L00_003294F0(void *, int);
extern void func_L05_00379F48(int);
extern void func_002AD7B8(int);
extern void func_L15_00430590(void *, int);

static void copy16_004307E0(void *dst, void *src)
{
    ((int *)dst)[0] = ((int *)src)[0];
    ((int *)dst)[1] = ((int *)src)[1];
    ((int *)dst)[2] = ((int *)src)[2];
    ((int *)dst)[3] = ((int *)src)[3];
}

/* Per-frame update of a controller object (`self`, its variables at +104). Its first frame resets
   the global state and hides every object with id 4625. Then, unless the player is already
   dead (func_L10_0037D200) or the stage counter D_L15_001B2148 is under 6: in the waiting phase
   it counts the timer at vars+108 down and then places the effect object whose id is in vars+32 (a
   position copy, an offset towards where it was hit, an orientation built from the cross
   product) and moves to state 3; afterwards, with D_L15_001B15D0 set, it restarts the timer, runs
   the reset calls and shows the object at vars+40; with it clear it calls func_L15_00430590 when
   the timer runs out. */
void func_L15_004307E0(char *self)
{
    char *vars = *(char **)(self + 104);
    float buf[24];                  /* 0: offset, 4: probe end, 8: (0,0,1), 12: edge, 16: cross, 20: (0,0,1) copy */
    unsigned char **list;
    int count, i;

    if (D_L15_001B1534 == 0) {
        D_L15_00221E3C = 0;
        D_L15_001B1534 = 1;
        func_002B7320();
        func_L05_0037B210();
        func_L05_00379F18(0);
        *(int *)(vars + 108) = 30;
        list = func_L05_00379EB8();
        count = func_L00_004272A0();
        for (i = 0; i < count; i++) {
            if (*(short *)(list[i] + 170) == 4625) {
                func_L05_0037B280(list[i], 1);
            }
        }
    }

    if (func_L10_0037D200(func_L05_00379ED0(4625)) != 0) {
        return;
    }
    if (D_L15_001B2148 < 6) {
        return;
    }

    if (D_L15_001B15BC == 0) {
        char *moby, *pos;
        float f20;

        if (func_00282948(vars + 108) == 0) {
            return;
        }
        *(int *)(vars + 108) = 60;
        func_L05_0037B108();
        moby = D_L15_001B261C + (*(int *)(vars + 32) << 8);
        pos = moby + 16;
        copy16_004307E0(D_L15_001B1550, pos);
        func_00282F20(buf, moby + 192, 196.0f);
        func_00282CC0(buf + 4, pos, buf);
        f20 = 25.0f;
        if (func_002761F8(pos, buf + 4, 0, moby, 0) != 0) {
            char *other = *(char **)(D_L15_001BFC00 + 24);

            if (other != 0 && *(short *)(other + 170) == 4625) {
                f20 = func_00282E48(D_L15_001BFC00 + 32, pos);
            }
        }
        moby += 192;
        if (f20 < 16.0f) {
            f20 = -32.0f;
        } else {
            f20 = f20 * 0.5f;
        }
        func_00282F20(buf, moby, f20);
        func_00282CC0(D_L15_001B1550, D_L15_001B1550, buf);
        buf[8] = 0.0f;
        buf[9] = 0.0f;
        buf[10] = 1.0f;
        buf[11] = 0.0f;
        D_L15_001B1550[2] = D_L15_001B1550[2] - 16.0f;
        copy16_004307E0(buf + 12, moby);
        copy16_004307E0(buf + 20, buf + 8);
        func_00282DD8(buf + 16, buf + 12, buf + 20);
        buf[15] = 0.0f;
        buf[23] = 0.0f;
        buf[19] = 0.0f;
        func_002AB6D8(buf + 12, D_L15_001B1540);
        func_L05_00442828(D_L15_001B1550, D_L15_001B1540, 300);
        self[32] = 3;
        D_L15_001B15BC = 1;
        return;
    }

    if (D_L15_001B15D0 == 0) {
        if (func_00282948(vars + 108) == 0) {
            return;
        }
        func_L05_0037B210();
        func_L15_00430590(self, 0);
        return;
    }
    if (func_00282948(vars + 108) == 0) {
        return;
    }
    *(int *)(vars + 108) = 10;
    D_L15_001B1520 = D_L15_001B1520 + 1;
    func_L15_00432008();
    func_0029B3E0(0, -1);
    D_L15_001B1520 = D_L15_001B1520 - 1;
    func_L00_003294F0(D_L15_001B261C + (*(int *)(vars + 40) << 8), 1);
    D_L15_001B15AC = 0;
    D_L15_001B15D0 = 0;
    func_L05_00379F48(1);
    func_002AD7B8(16);
}
