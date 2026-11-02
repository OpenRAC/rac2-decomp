/* functional: high. Same scan of the 32 48-byte entries (flag 4), double buffer at D_001B22A0[1 - D_001B22B4], same calls in order; differs from retail in register use and in reading the counter at 0x1B1658 absolutely instead of one gp-relative read. */
typedef struct {
    int pad0[7];
    unsigned int flags;
    short a, b, c, d;
    int pad1[2];
} Ent280710;
extern Ent280710 D_001B8A10[];
extern int D_001B1658;
extern int D_001B22A0[];
extern int D_001B22B4;
extern void func_00285708(short, short, short, short, int);
extern void func_001244B8(int, int);
extern void func_00280670(int, int);

void func_00280710(void)
{
    int buf[2];
    int cur = 0;
    int last = -1;
    int i, j, s;

    if (D_001B1658 == 0)
        return;
    buf[0] = D_001B22A0[1 - D_001B22B4];
    buf[1] = buf[0] + 0x40000;
    for (i = 31; i >= 0; i--) {
        if (D_001B8A10[i].flags & 4) {
            last = i;
            func_00285708(D_001B8A10[i].a, D_001B8A10[i].b, D_001B8A10[i].c, D_001B8A10[i].d, buf[cur]);
            func_001244B8(0, 0);
        }
    }
    s = last;
    if (s == -1)
        return;
    while (s >= 0) {
        cur = 1 - cur;
        last = -1;
        for (j = s - 1; j >= 0; j--) {
            if (D_001B8A10[j].flags & 4) {
                last = j;
                func_00285708(D_001B8A10[j].a, D_001B8A10[j].b, D_001B8A10[j].c, D_001B8A10[j].d, buf[cur]);
            }
        }
        func_00280670(buf[1 - cur], s);
        if (D_001B8A10[s].flags & 1) {
            D_001B8A10[s].flags &= ~5;
            D_001B1658--;
        }
        if (last >= 0)
            func_001244B8(0, 0);
        s = last;
    }
}
