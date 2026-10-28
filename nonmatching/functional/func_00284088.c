/* functional: medium. Only one captured call, so not every branch is exercised. Builds a GIF packet (header words, a context-derived register word, then 16 quads of 4 words each) in the buffer at 0x1A6AF0; branches on arg0/arg1/flags exactly as retail; the 0xA0 divide guard (break) is dead code (constant divisor) and left out; same writes in a different order, bytes differ only in codegen. */
extern long D_001A6AF0[] __attribute__((nosda));
extern char *D_001A742C __attribute__((sda));
extern unsigned char D_001A7BB1 __attribute__((sda));
extern int D_001A7BB8 __attribute__((sda));

void func_00284088(int arg0, int arg1) {
    long *p = D_001A6AF0;
    char *ctx = D_001A742C;
    long v;
    int sel, w, i;
    long t2, t4;
    p[0] = 0x308B400000000001L;
    p[1] = 0xEEE;
    p[2] = 0x30000;
    p[3] = 0x47;
    p[4] = 0x100000261L;
    p[5] = 0x14;
    v = ((long)(*(short *)(ctx + 0x156)) << 5)
        | ((long)((*(unsigned short *)(ctx + 0x150) >> 6) & 0x3F) << 14)
        | ((long)(*(short *)(ctx + 0x154)) << 20)
        | 0xEA8000000L;
    p[6] = v;
    p[7] = 6;
    p[8] = 0x4400000000008010L;
    p[9] = 0x5353;
    if (arg0 == 0) {
        sel = D_001A7BB1 != 0;
    } else {
        sel = arg1;
    }
    w = *(short *)(ctx + 0x15A);
    if (sel) {
        w = w << 3;
    } else {
        w = ((w * 0x73) / 0xA0) << 3;
    }
    ctx = D_001A742C;
    t4 = (long)(0x7FF8 - w) << 16;
    t2 = (long)(w + 0x7FF8) << 16;
    p = D_001A6AF0 + 10;
    for (i = 0; i < 16; i++) {
        int a, b, c;
        if (D_001A7BB8 != 0) {
            a = i * *(short *)(ctx + 0x150);
            b = i * 0x280 + 0x6BF8;
            c = (i + 1) * 0x280 + 0x6BF8;
        } else {
            a = i * *(short *)(ctx + 0x150);
            b = (i << 9) + 0x6FF8;
            c = ((i + 1) << 9) + 0x6FF8;
        }
        p[0] = a;
        p[1] = (long)b | t4;
        p[2] = (long)((i + 1) * *(short *)(ctx + 0x150)) | 0x1A000000L;
        p[3] = (long)c | t2;
        p += 4;
    }
}
