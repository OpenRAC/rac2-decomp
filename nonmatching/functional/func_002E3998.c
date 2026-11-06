/* functional: high. Written from the assembly; same calls, arguments and order (fcheck SAME on 4 captured calls). buf is an alloca of (count & 0x1FFFFFFF) rounded up to 16 bytes, filled by func_002E4388. */
typedef unsigned char u8;

extern int D_001ABDE0;          /* $gp - 0x3210: the buffer toggle, 0 or 1 */
extern int D_001ABDD8[2];       /* $gp - 0x3218: the two buffers */
extern char *D_001B22A8 __attribute__((sda));

extern void func_002E4388(void *, int, void *);
extern void func_0029CF58(int, int, int);
extern void func_0029CF78(void);
extern int func_002E3E54(int, int, int, int);
extern void func_002E40C8(int, int, int, int);

#define REC(o, i) ((char *)(o) + 0x20 + (i) * 32)

void func_002E3998(char *obj)
{
    int count = *(int *)obj;
    unsigned int size = (((unsigned int)count << 3) >> 3) + 0xF;
    u8 *buf;
    int i;

    buf = (u8 *)__builtin_alloca((size >> 4) << 4);
    if (count == 0)
        return;

    func_002E4388(obj + 0x10, count, buf);
    *(int *)(D_001B22A8 + 0) = 0x30000007;
    *(int *)(D_001B22A8 + 4) = 0x139370;
    *(int *)(D_001B22A8 + 8) = 0;
    *(int *)(D_001B22A8 + 12) = 0x50000007;
    D_001B22A8 = D_001B22A8 + 0x10;
    D_001ABDE0 = 1 - D_001ABDE0;
    if (buf[0] == 1)
        func_0029CF58(*(int *)REC(obj, 0), (short)*(unsigned short *)(REC(obj, 0) + 0xE) >> 4, D_001ABDD8[D_001ABDE0]);

    if (*(int *)obj <= 0)
        return;
    i = 0;
    do {
        int chk;

        if (buf[i] == 1)
            func_0029CF78();
        D_001ABDE0 = 1 - D_001ABDE0;
        if (i + 1 < *(int *)obj) {
            if (buf[i + 1] == 1)
                func_0029CF58(*(int *)REC(obj, i + 1), (short)*(unsigned short *)(REC(obj, i + 1) + 0xE) >> 4,
                              D_001ABDD8[D_001ABDE0]);
            chk = buf[i];
        } else {
            chk = buf[i];
        }
        if (chk == 1) {
            char *r = REC(obj, i);
            int t = D_001ABDD8[1 - D_001ABDE0];
            short h24 = *(short *)(r + 4), h26 = *(short *)(r + 6), h28 = *(short *)(r + 8);
            short h2a = *(short *)(r + 0xA), h2c = *(short *)(r + 0xC);

            if (func_002E3E54(t + h28, 0x70002000, h24, h2c) == 0)
                func_002E40C8(h26, t + h2c, t + h2a, 0x70002000);
        }
        i++;
    } while (i < *(int *)obj);
}
