/* functional: medium. Written from the assembly (no draft existed); same calls with the same arguments in the same order, same stores to the output (3 doublewords) and to D_001A72D0. The scratch frame is addressed by byte offset (W) as retail does. Format switch (0x13, 0x14 upload the texture; others only build the MIPTBP words) follows the branches one for one. */
typedef unsigned long long u64;

extern int D_001A72D0;           /* $gp - 0x7D20: GS texture memory cursor */

extern void func_00282A60(void *, unsigned int, int);
extern int func_00282A18(int);
extern int func_00126288(void *, short, short, short, short, short, short, short);
extern int func_001265B0(void *, void *);
extern int func_001244B8(int, int);
extern void func_0011AEA0(int);

#define W(o) (*(int *)((char *)L + (o)))

int func_00291850(char *obj, u64 *out)
{
    int L[0x18];                 /* sp + 0 .. 0x5F */
    char gs[0x60];               /* sp + 0x60: the GsLoadImage */
    int fmt, i, n, base;
    char *s0 = 0;

    func_00282A60(L, 0, 0x54);
    fmt = *(int *)(obj + 0x10);
    if (fmt == 2 || fmt == 0) {
        W(0) = 0;
        W(0x14) = 0;
    } else if (fmt == 1) {
    } else if (fmt >= 3 && fmt < 0x15) {
        if (fmt >= 0x13) {
            W(0) = (int)(obj + 0x20);
            if (fmt == 0x14)
                W(0x14) = *(int *)(obj + 0x14) ? 0x20 : 0x40;
            else
                W(0x14) = *(int *)(obj + 0x14) ? 0x200 : 0x400;
        }
    }
    W(0x4C) = func_00282A18(*(int *)(obj + 8));
    W(0x50) = func_00282A18(*(int *)(obj + 0xC));
    W(4) = (int)(obj + (W(0x14) + 0x20));

    fmt = *(int *)(obj + 0x10);
    if (fmt == 2) {
        W(0x18) = (*(int *)(obj + 8) * *(int *)(obj + 0xC)) << 1;
    } else if (fmt < 3) {
        if (fmt == 0)
            W(0x18) = (*(int *)(obj + 8) * *(int *)(obj + 0xC)) << 2;
    } else if (fmt == 0x13) {
        W(0x18) = *(int *)(obj + 8) * *(int *)(obj + 0xC);
    } else if (fmt == 0x14) {
        W(0x18) = (*(int *)(obj + 8) * *(int *)(obj + 0xC)) >> 1;
    }

    fmt = *(int *)(obj + 0x10);
    if (fmt == 0x13 || fmt == 0x14) {
        int cur = D_001A72D0;

        W(0x28) = cur >> 8;
        s0 = gs;
        if (fmt == 0x14) {
            D_001A72D0 = cur + 0x100;
            func_00126288(gs, (short)W(0x28), 1, *(short *)(obj + 0x14), 0, 0, 8, 2);
        } else {
            D_001A72D0 = cur + W(0x14);
            func_00126288(gs, (short)W(0x28), 1, *(short *)(obj + 0x14), 0, 0, 0x10, 0x10);
        }
        func_0011AEA0(0);
        func_001265B0(gs, (void *)W(0));
        func_001244B8(0, 0);
    }

    n = *(int *)(obj + 0x1C);
    if (1 < n) {
        for (i = 0; i < n - 1; i++) {
            int v = W(0x18 + 4 * i);

            W(8 + 4 * i) = W(4 + 4 * i) + v;
            W(0x18 + 4 * i + 4) = v >> 2;
        }
    }
    if (*(int *)(obj + 0x1C) > 0) {
        for (i = 0; ; ) {
            int v, sz;

            v = *(int *)(obj + 8) >> (i + 6);
            W(0x3C + 4 * i) = v;
            if (v <= 0)
                W(0x3C + 4 * i) = 1;
            W(0x2C + 4 * i) = D_001A72D0 >> 8;
            func_00126288(gs, (short)W(0x2C + 4 * i), (short)W(0x3C + 4 * i), *(short *)(obj + 0x10), 0, 0,
                          (short)(*(int *)(obj + 8) >> i), (short)(*(int *)(obj + 0xC) >> i));
            func_0011AEA0(0);
            func_001265B0(gs, (void *)W(4 + 4 * i));
            func_001244B8(0, 0);
            base = D_001A72D0;
            sz = W(0x18) >> (2 * i);
            if (!(0xFF < sz))
                sz = 0x100;
            i++;
            D_001A72D0 = base + sz;
            if (!(i < *(int *)(obj + 0x1C)))
                break;
        }
    }

    out[0] = (u64)(long long)W(0x2C)
           | ((u64)(long long)W(0x3C) << 14)
           | ((u64)(long long)*(int *)(obj + 0x10) << 20)
           | ((u64)(long long)W(0x4C) << 26)
           | ((u64)(long long)W(0x50) << 30)
           | ((u64)(long long)W(0x28) << 37 | (u64)0x8000 << 19)
           | ((u64)(long long)*(int *)(obj + 0x14) << 51)
           | ((u64)-1 << 63);
    out[1] = ((u64)(long long)(*(int *)(obj + 0x1C) - 1) << 2) | 0xFFA0000000E0ULL;
    out[2] = (u64)(long long)W(0x30)
           | ((u64)(long long)W(0x40) << 14)
           | ((u64)(long long)W(0x34) << 20)
           | ((u64)(long long)W(0x44) << 34)
           | ((u64)(long long)W(0x38) << 40)
           | ((u64)(long long)W(0x48) << 54);
    return -1;
}
