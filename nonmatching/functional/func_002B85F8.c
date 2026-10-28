/* functional: medium. Same state machine, calls and stores as retail by reading the assembly; byte layout differs. The 4-byte copies read the stack buffer past what the callee wrote, as retail does (dead stack content) */
typedef unsigned char u8;
extern void func_002B8888(u8 *);
extern char D_00138180[];
extern int func_00128C18(int);
extern int func_00128B28(int, void *);
extern int func_00128F48(int, void *);
extern int func_00128A48(int, void *);
extern void func_00128FD0(int, int, void *, int, void *);
extern void func_002B88F0(void *, void *, int);
extern int D_001A7428[];

void func_002B85F8(void *base)
{
    unsigned char *p = base;
    unsigned char b[0x40];
    int mode = *(int *)(p + 0x1B0);
    int r;
    int n;
    int i;

    *(int *)(p + 0x1A0) = 0;
    *(int *)(p + 0x1AC) = *(int *)(p + 0x348);
    *(int *)(p + 0x1B0) = 0;
    *(int *)(p + 0x1BC) = mode;
    r = func_00128C18(*(int *)(p + 0x194));
    *(int *)(p + 0x19C) = r;

    if (r != 1) {
        func_002B8888(p);
        *(int *)(p + 0x198) = 0;
        p[0x189] = 0;
    } else {
        int st = *(int *)(p + 0x198);
        if (st == 1) {
            int s1 = func_00128A48(*(int *)(p + 0x194), b);
            short h = 0;
            if (p[0x184] & 2)
                h = p[0x189];
            if (p[0x184] & 1)
                h = (short)(h << 1) | (p[0x188] & 1);
            func_00128FD0(*(int *)(p + 0x194), 1, p + 0x184, 2, &h);
            func_002B88F0(p, b, s1);
            p[0x189] = 0;
        } else if (st < 2) {
            if (st == 0) {
                n = func_00128B28(*(int *)(p + 0x194), b);
                *(int *)(p + 0x1DC) = (*(int *)b == -1) ? 0x79 : 0;
                if (n < 5) {
                    for (i = 0; i < n; i++)
                        p[0x180 + i] = b[i];
                    *(int *)(p + 0x198) = 1;
                } else {
                    n = 0;
                    *(int *)(p + 0x198) = 2;
                }
                for (i = n; i < 4; i++)
                    p[0x180 + i] = b[i];
                n = func_00128F48(*(int *)(p + 0x194), b);
                if (n < 5) {
                    for (i = 0; i < n; i++)
                        p[0x184 + i] = b[i];
                } else {
                    n = 0;
                }
                for (i = n; i < 4; i++)
                    p[0x184 + i] = b[i];
                func_002B8888(p);
            }
            p[0x189] = 0;
        } else {
            if (st == 2)
                func_002B8888(p);
            p[0x189] = 0;
        }
    }
    p[0x188] = 0;
    D_001A7428[0] = *(int *)(D_00138180 + 0x19C) == 0;
}
